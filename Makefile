# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -std=c99 -O2

# Source directories
PROTECTION_DIR = ProtectionHandler
MEASUREMENT_DIR = MeasurementHandler
DRIVINGHANDLER_DIR = DrivingHandler
MAIN_DIR = .

# Target executables
HALL_TARGET = halltest
THROTTLE_TARGET = throttletest
MEASUREMENT_TARGET = measurementtest
VOLTAGE_TARGET = voltageprotectiontest
CURRENT_TARGET = currentprotectiontest
CALCULATEVOLTAGE = measurevoltage
CALCULATECURRENT = measurecurrent
BRAKE_TARGET = braketest # Fixed the target name for brake test

# Source files
HALL_SRCS = $(PROTECTION_DIR)/Protection.c $(MAIN_DIR)/protection_main.c
THROTTLE_SRCS = $(PROTECTION_DIR)/Protection.c $(MAIN_DIR)/throttle_main.c
MEASUREMENT_SRCS = $(MEASUREMENT_DIR)/measurement.c $(MAIN_DIR)/measurement_main.c
VOLTAGEP_SRCS = $(PROTECTION_DIR)/Protection.c $(MAIN_DIR)/voltage_main.c
CURRENTP_SRCS = $(PROTECTION_DIR)/Protection.c $(MAIN_DIR)/Current_main.c
MEASUREVOLTAGE_SRCS = $(MEASUREMENT_DIR)/measurement.c $(MAIN_DIR)/calculatevoltage_main.c
MEASURECURRENT_SRCS = $(MEASUREMENT_DIR)/measurement.c $(MAIN_DIR)/calculatecurrent_main.c
BRAKE_SRCS = $(DRIVINGHANDLER_DIR)/brake.c $(MAIN_DIR)/driving_main.c

# Object files
HALL_OBJS = $(HALL_SRCS:%.c=$(MAIN_DIR)/%.o)
THROTTLE_OBJS = $(THROTTLE_SRCS:%.c=$(MAIN_DIR)/%.o)
MEASUREMENT_OBJS = $(MEASUREMENT_SRCS:%.c=$(MAIN_DIR)/%.o)
VOLTAGEP_OBJS = $(VOLTAGEP_SRCS:%.c=$(MAIN_DIR)/%.o)
CURRENTP_OBJS = $(CURRENTP_SRCS:%.c=$(MAIN_DIR)/%.o)
MEASUREVOLTAGE_OBJS = $(MEASUREVOLTAGE_SRCS:%.c=$(MAIN_DIR)/%.o)
MEASURECURRENT_OBJS = $(MEASURECURRENT_SRCS:%.c=$(MAIN_DIR)/%.o)
BRAKE_OBJS = $(BRAKE_SRCS:%.c=$(MAIN_DIR)/%.o)

# Default target
all: $(HALL_TARGET) $(THROTTLE_TARGET) $(MEASUREMENT_TARGET) $(VOLTAGE_TARGET) $(CURRENT_TARGET) $(CALCULATEVOLTAGE) $(CALCULATECURRENT) $(BRAKE_TARGET)

# Rule to build the halltest target
$(HALL_TARGET): $(HALL_OBJS)
	$(CC) $(CFLAGS) -o $(HALL_TARGET) $(HALL_OBJS)

# Rule to build the throttletest target
$(THROTTLE_TARGET): $(THROTTLE_OBJS)
	$(CC) $(CFLAGS) -o $(THROTTLE_TARGET) $(THROTTLE_OBJS)

# Rule to build the measurementtest target
$(MEASUREMENT_TARGET): $(MEASUREMENT_OBJS)
	$(CC) $(CFLAGS) -o $(MEASUREMENT_TARGET) $(MEASUREMENT_OBJS)

# Rule to build the voltageprotectiontest target
$(VOLTAGE_TARGET): $(VOLTAGEP_OBJS)
	$(CC) $(CFLAGS) -o $(VOLTAGE_TARGET) $(VOLTAGEP_OBJS)

# Rule to build the currentprotectiontest target
$(CURRENT_TARGET): $(CURRENTP_OBJS)
	$(CC) $(CFLAGS) -o $(CURRENT_TARGET) $(CURRENTP_OBJS)

# Rule to build the voltagecalculation target
$(CALCULATEVOLTAGE): $(MEASUREVOLTAGE_OBJS)
	$(CC) $(CFLAGS) -o $(CALCULATEVOLTAGE) $(MEASUREVOLTAGE_OBJS)

# Rule to build the currentcalculation target
$(CALCULATECURRENT): $(MEASURECURRENT_OBJS)
	$(CC) $(CFLAGS) -o $(CALCULATECURRENT) $(MEASURECURRENT_OBJS)

# Rule to build the brake test target
$(BRAKE_TARGET): $(BRAKE_OBJS)
	$(CC) $(CFLAGS) -o $(BRAKE_TARGET) $(BRAKE_OBJS)

# Rule to build object files for ProtectionHandler
$(PROTECTION_DIR)/%.o: $(PROTECTION_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to build object files for MeasurementHandler
$(MEASUREMENT_DIR)/%.o: $(MEASUREMENT_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to build object files for DrivingHandler
$(DRIVINGHANDLER_DIR)/%.o: $(DRIVINGHANDLER_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to build object files for the main directory
$(MAIN_DIR)/%.o: $(MAIN_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to run halltest
run_halltest: $(HALL_TARGET)
	./$(HALL_TARGET)

# Rule to run throttletest
run_throttletest: $(THROTTLE_TARGET)
	./$(THROTTLE_TARGET)

# Rule to run measurementtest
run_measurementtest: $(MEASUREMENT_TARGET)
	./$(MEASUREMENT_TARGET)

# Rule to run voltageprotectiontest
run_voltagetest: $(VOLTAGE_TARGET)
	./$(VOLTAGE_TARGET)

# Rule to run currentprotectiontest
run_currenttest: $(CURRENT_TARGET)
	./$(CURRENT_TARGET)

# Rule to run voltagecalculation
run_voltagemeasurement: $(CALCULATEVOLTAGE)
	./$(CALCULATEVOLTAGE)

# Rule to run currentcalculation
run_currentmeasurement: $(CALCULATECURRENT)
	./$(CALCULATECURRENT)

# Rule to run brake test
run_braketest: $(BRAKE_TARGET)
	./$(BRAKE_TARGET)

# Clean up build files
clean:
	rm -f $(HALL_OBJS) $(THROTTLE_OBJS) $(MEASUREMENT_OBJS) $(VOLTAGEP_OBJS) $(CURRENTP_OBJS) $(MEASUREVOLTAGE_OBJS) $(MEASURECURRENT_OBJS) $(BRAKE_OBJS) $(HALL_TARGET) $(THROTTLE_TARGET) $(MEASUREMENT_TARGET) $(VOLTAGE_TARGET) $(CURRENT_TARGET) $(CALCULATEVOLTAGE) $(CALCULATECURRENT) $(BRAKE_TARGET)

# PHONY targets to avoid conflicts with file names
.PHONY: all clean run_halltest run_throttletest run_measurementtest run_voltagetest run_currenttest run_voltagemeasurement run_currentmeasurement run_braketest
