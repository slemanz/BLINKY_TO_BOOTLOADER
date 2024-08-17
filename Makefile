# Define toolchain and options
CC = arm-none-eabi-gcc
LD = arm-none-eabi-ld
OBJCOPY = arm-none-eabi-objcopy
GDB = arm-none-eabi-gdb

# Define output file and directories
TARGET = main.elf
TARGET_BIN = main.bin
LINKER_SCRIPT = linkerscript.ld
SRC_DIR = Src
INC_DIR = Inc
DRIVER_SRC_DIR = Drivers/Src
DRIVER_INC_DIR = Drivers/Inc

# Define source files
SRC_FILES = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(DRIVER_SRC_DIR)/*.c)  $(SRC_DIR)/startup.s
OBJ_FILES = $(SRC_FILES:.c=.o)

# Compiler options
CFLAGS = -Wall -Werror -mcpu=cortex-m4 -mthumb -I$(INC_DIR) -I$(DRIVER_INC_DIR)
LDFLAGS = -T$(LINKER_SCRIPT) -mthumb -Wl,--gc-sections -Wl,-Map=$(TARGET).map

# Target rules
all: $(TARGET) $(TARGET_BIN)

$(TARGET): $(OBJ_FILES)
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET_BIN): $(TARGET)
	$(OBJCOPY) -O binary $(TARGET) $(TARGET_BIN)

clean:
	rm -f $(OBJ_FILES) $(TARGET) $(TARGET_BIN) $(TARGET).map

flash: $(TARGET_BIN)
	# Here you can add commands to flash the binary to your STM32, e.g., using OpenOCD or ST-Link
	# openocd -f interface/stlink.cfg -f target/stm32f4x.cfg -c "program $(TARGET_BIN) verify reset exit"

run: $(TARGET_BIN)
	$(GDB) $(TARGET) -ex "target remote :3333" # Adjust the command based on your GDB setup

.PHONY: all clean flash run