# File Setup
SRC_DIR = src
INC_DIR = include
EXAMPLES_DIR = examples
BUILD_DIR = build
LINKER_SCRIPT = linker/rm4x.ld

# Compiler Configuration
PREFIX = arm-none-eabi-
CC = $(PREFIX)gcc
AS = $(PREFIX)as
LD = $(PREFIX)ld
OBJCOPY = $(PREFIX)objcopy
AR = $(PREFIX)ar

MCU = cortex-r4
FPU = -mfloat-abi=hard -mfpu=vfpv3-d16

CFLAGS = -mcpu=$(MCU) $(FPU) \
         -I$(INC_DIR) \
         -Wall -Wextra \
         -g -O3 \
         -ffunction-sections -fdata-sections \
         -ffreestanding

LDFLAGS = -T$(LINKER_SCRIPT) \
        -Wl,--gc-sections \
        -Wl,-Map=$(BUILD_DIR)/output.map \
        -nostdlib -ffreestanding

C_SOURCES = $(wildcard $(SRC_DIR)/*.c)
ASM_SOURCES = $(wildcard $(SRC_DIR)/*.s)

OBJECTS = $(C_SOURCES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o) \
          $(ASM_SOURCES:$(SRC_DIR)/%.s=$(BUILD_DIR)/%.o)

LIB_TARGET = $(BUILD_DIR)/librm4x.a

# Build the library
lib: $(LIB_TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.s | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIB_TARGET): $(OBJECTS)
	$(AR) rcs $@ $^

# Build a specific example: make example EXAMPLE=blinker
example: $(LIB_TARGET)
ifndef EXAMPLE
	$(error EXAMPLE not specified. Usage: make example EXAMPLE=blink)
endif
	$(CC) $(CFLAGS) $(LDFLAGS) $(EXAMPLES_DIR)/$(EXAMPLE).c $(LIB_TARGET) -o $(BUILD_DIR)/$(EXAMPLE).elf
	$(OBJCOPY) -O binary $(BUILD_DIR)/$(EXAMPLE).elf $(BUILD_DIR)/$(EXAMPLE).bin

clean:
	rm -rf $(BUILD_DIR)

.PHONY: lib example clean debug
