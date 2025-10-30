# File Setup
SRC_DIR = src
INC_DIR = include
BUILD_DIR = build
LINKER_SCRIPT = linker/rm4x.ld

# Compiler Configuration
PREFIX = arm-none-eabi-
CC = $(PREFIX)gcc
AS = $(PREFIX)as
LD = $(PREFIX)ld
OBJCOPY = $(PREFIX)objcopy

MCU = cortex-r4
FPU = -mfloat-abi=hard -mfpu=vfpv3-d16

CFLAGS = -mcpu=$(MCU) $(FPU) -mthumb \
         -I$(INC_DIR) \
         -Wall -Wextra \
         -g -O0 \
         -ffunction-sections -fdata-sections

LDFLAGS = -T$(LINKER_SCRIPT) \
        -Wl,--gc-sections \
        -Wl,-Map=$(BUILD_DIR)/output.map \
        -nostdlib

C_SOURCES = $(wildcard $(SRC_DIR)/*.c)
ASM_SOURCES = $(wildcard $(SRC_DIR)/*.s)

OBJECTS = $(C_SOURCES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o) \
          $(ASM_SOURCES:$(SRC_DIR)/%.s=$(BUILD_DIR)/%.o)

TARGET = $(BUILD_DIR)/firmware

all: $(BUILD_DIR) $(TARGET).elf $(TARGET).bin

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.s
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET).elf: $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJECTS) -o $@

$(TARGET).bin: $(TARGET).elf
	$(OBJCOPY) -O binary $< $@

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean
