#include <stdio.h>
#include <stdint.h>  // Include for uint32_t
#include "measurement.h"
#include "VoltageCalculation.h"
#include "CurrentCalculation.h"
#include "math.h"
#include "sharedData.h"
#include"initialconfig.h"
#include "define.h"
#include "gpio.h"

//FIXED_VALS_t fixedvalue;
//MotorRun_t MotorRun;
uint32_t adc_to_rpm(uint32_t adc_value, uint32_t max_rpm, uint32_t adc_max_value, uint32_t throttle_start_adc) {
    // Ensure the ADC value is within valid range
    if (adc_value < throttle_start_adc) {
        adc_value = throttle_start_adc; // If ADC value is below the throttle start, use the throttle start value
    } else if (adc_value > adc_max_value) {
        adc_value = adc_max_value;
    }

    // Calculate the effective ADC range above throttle start
    uint32_t effective_adc_range = adc_max_value - throttle_start_adc;
    uint32_t effective_adc_value = adc_value - throttle_start_adc;

    // Calculate RPM
    return (effective_adc_value * max_rpm) / effective_adc_range;
}

// Function to calculate RPM based on ADC value
uint32_t calculate_throttle(uint32_t adc_value,uint32_t max_rpm) {
    
    // Calculate RPM
    return adc_to_rpm(adc_value,FixedValue.max_rpm, FixedValue.adc_max_value, FixedValue.throttle_start_adc);
}

// Function to calculate the input voltage based on ADC value
uint32_t calculate_voltage(uint32_t adc_value) {
//	HAL_GPIO_WritePin(Buzzer_GPIO_Port, Buzzer_Pin, GPIO_PIN_SET);
    // Calculate the output voltage from ADC value
    uint32_t Vout = (adc_value * FixedValue.ref_voltage) / FixedValue.adcResolution;
//	uint32_t Vout = adc_value * 0.08056640625 ;

    // Calculate the input voltage based on the voltage divider formula
//    uint32_t voltage = (Vout * (FixedValue.r1 + FixedValue.r2)) / FixedValue.r2;
      uint32_t voltage = Vout * 18;
    return voltage;
//    HAL_GPIO_WritePin(Buzzer_GPIO_Port, Buzzer_Pin, GPIO_PIN_RESET);
}


uint32_t calculate_current(uint32_t adc_value) {
    // Apply a simple low-pass filter to smooth out the current measurement
    int32_t difference = adc_value - FixedValue.filtered_current;
    int32_t filtered_increment = difference / (1 << FixedValue.filter_shift);
    FixedValue.filtered_current += filtered_increment;

    // Calculate the actual current value in amperes
    int32_t current = ((FixedValue.filtered_current * FixedValue.ref_voltage) /FixedValue.current_calibrationFactor);
//    uint32_t current = ((FixedValue.filtered_current * FixedValue.ref_voltage) /174);
    // Return current as an unsigned int, assuming it's appropriate for your needs
    return current;
}

uint32_t measure_temperature(uint32_t adc_value){
    uint32_t temperature =((FixedValue.v25 - FixedValue.vsense* adc_value)/FixedValue.avg_slope + 25.0f);
    return temperature;
}

void calculateMotorPeriod(uint32_t cap){
	if (cap >MAX_HALL_PERIOD + 100){
		return;
	}
	else if (cap < 450)
	{
		return;
	}
	Measured.motorPeriod.periodBeforeClamp = cap;
	if (cap < MIN_HALL_PERIOD)
	{
		cap = MIN_HALL_PERIOD;
	}
	else if (cap > MAX_HALL_PERIOD)
	{
		cap = MAX_HALL_PERIOD;
	}
	Measured.motorPeriod.periodBeforeFilter = cap;

}

void resetMotorPeriod(void){
	Measured.motorPeriod.periodBeforeFilter = MAX_HALL_PERIOD;
}

void filterMotorPeriod(void){
	Measured.motorPeriod.period = ((50 * Measured.motorPeriod.periodBeforeFilter) + (14 * Measured.motorPeriod.period)) >> 6;
}

// To get motor RPM
void calculateMotorSpeed(uint32_t cap){
	// I guess this could be optimized
	Measured.motorSpeed.counter++;
	Measured.motorSpeed.acc += cap;

	// Filter for speed
	if ((6 == MotorRun.hallstate) && Measured.motorSpeed.counter >= 6){		// should try some better logic
		if (0 == Measured.motorSpeed.acc){
			Measured.motorSpeed.acc = 1;
		}
		Measured.motorSpeed.speedWithoutFilter = (int16_t) (SPEED_MULTI / Measured.motorSpeed.acc);
		Measured.motorSpeed.counter = 0;
		Measured.motorSpeed.acc = 0;
	}
}

void filterMotorSpeed(void){
	Measured.motorSpeed.speed = ((30 * Measured.motorSpeed.speed) + (34 * Measured.motorSpeed.speedWithoutFilter)) >> 6;
}

const int PhaseValues[8] = {0, PHASE_FOUR, PHASE_TWO, PHASE_THREE, PHASE_ZERO, PHASE_FIVE, PHASE_ONE, 0};
const int ReversePhaseValues[8] = {0, PHASE_ZERO, PHASE_FOUR, PHASE_FIVE, PHASE_TWO, PHASE_ONE, PHASE_THREE, 0};
const int ForwardPhaseValues[8] = {0, PHASE_FOUR, PHASE_TWO, PHASE_THREE, PHASE_ZERO, PHASE_FIVE, PHASE_ONE, 0};
void getHallAngle(uint8_t hall){
//	MotorRun.phase =PhaseValues[hp]+ MotorRun.phaseOffset;
	if(MotorRun.runDirectionFlag == REVERSE){
		MotorRun.phase = ReversePhaseValues[hall] + MotorRun.reverseOffset;
	} else{
		MotorRun.phase = ForwardPhaseValues[hall] + MotorRun.forwardOffset;
	}
	MotorRun.phase += MotorRun.phaseAdv.advanceAngle;
}
