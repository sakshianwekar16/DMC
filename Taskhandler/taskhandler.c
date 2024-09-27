#include <stdio.h>
#include <stdint.h>
#include "sharedData.h"
#include "taskhandler.h"
#include "math.h"  // Include this for external math functions
#include "Protection.h"
#include "measurement.h"
#include "VoltageCalculation.h"
#include"VoltageProtection.h"
#include "CurrentCalculation.h"
#include"CurrentProtection.h"
#include"initialconfig.h"
#include"brake.h"

MEASURED_t Measured;
PROTECTION_t Protection;

// Function to handle hall position and protection
void handle_hall(uint8_t hall) {
    // Update hall position
    Measured.hallPosition = hall;

    // Check hall protection and update protection status
    Protection.faults.hallInvalid = check_hall_protection(hall);
}

// Main loop or fast loop function

void update_ADC(uint32_t current,uint32_t voltage,uint32_t throttle,uint32_t temperature){
	 Measured.Current.raw = current;
	 Measured.Voltage.raw = voltage;
	 Measured.throttle.raw =throttle;
     Measured.temperature.raw =temperature;
}
void fast_loop(void) {

    // Calculate current and voltage
    Measured.Current.calculated = calculate_current(Measured.Current.raw);
    Measured.Voltage.calculated = calculate_voltage(Measured.Voltage.raw);
    Measured.throttle.calculated =calculate_throttle(Measured.throttle.raw,Fixedvalue.MAX_RPM);
    Measured.temperature.calculated =measure_temperature(Measured.temperature.raw);
    Protection.faults.overVolt = check_overvoltage(Measured.Voltage.calculated);
    Protection.faults.underVolt = check_undervoltage(Measured.Voltage.calculated);

    // Call the current protection check
    Protection.faults.overCurrent = check_overCurrent(Measured.Current.calculated);
    Protection.faults.throttle = check_throttle(Measured.throttle.calculated);
    Protection.faults.overTemperature = check_overTemperature(Measured.temperature.calculated);

}


void update_brakevalue(uint8_t brake){
    Measured.brakeRaw = brake;
}
// Slow loop function to check brake status and adjust RPM accordingly
void slow_loop(void) {
   Measured.TargetRPM = update_rpm_based_on_brake_status(Measured.brakeRaw); 
      
}
