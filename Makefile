# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -std=c99 -O2

# Source directories
PROTECTION_DIR = ProtectionHandler
MEASUREMENT_DIR = MeasurementHandler
MAIN_DIR = .

# Target executables
HALL_TARGET = halltest
THROTTLE_TARGET = throttletest
MEASUREMENT_TARGET = measurementtest
VOLTAGE_TARGET = voltageprotectiontest

# Source files
HALL_SRCS = $(PROTECTION_DIR)/Protection.c $(MAIN_DIR)/protection_main.c
THROTTLE_SRCS = $(PROTECTION_DIR)/Protection.c $(MAIN_DIR)/throttle_main.c
MEASUREMENT_SRCS = $(MEASUREMENT_DIR)/measurement.c $(MAIN_DIR)/measurement_main.c
VOLTAGEP_SRCS = $(PROTECTION_DIR)/Protection.c $(MAIN_DIR)/voltage_main.c

# Object files
HALL_OBJS = $(HALL_SRCS:%.c=$(MAIN_DIR)/%.o)
THROTTLE_OBJS = $(THROTTLE_SRCS:%.c=$(MAIN_DIR)/%.o)
MEASUREMENT_OBJS = $(MEASUREMENT_SRCS:%.c=$(MAIN_DIR)/%.o)
VOLTAGEP_OBJS = $(VOLTAGEP_SRCS:%.c=$(MAIN_DIR)/%.o)

# Default target
all: $(HALL_TARGET) $(THROTTLE_TARGET) $(MEASUREMENT_TARGET) $(VOLTAGE_TARGET)

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

# Rule to build object files for ProtectionHandler
$(PROTECTION_DIR)/%.o: $(PROTECTION_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to build object files for MeasurementHandler
$(MEASUREMENT_DIR)/%.o: $(MEASUREMENT_DIR)/%.c
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

# Clean up build files
clean:
	rm -f $(HALL_OBJS) $(THROTTLE_OBJS) $(MEASUREMENT_OBJS) $(VOLTAGEP_OBJS) $(HALL_TARGET) $(THROTTLE_TARGET) $(MEASUREMENT_TARGET) $(VOLTAGE_TARGET)

# PHONY targets to avoid conflicts with file names
.PHONY: all clean run_halltest run_throttletest run_measurementtest run_voltagetest


