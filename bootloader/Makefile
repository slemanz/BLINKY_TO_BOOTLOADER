CC=arm-none-eabi-gcc
TARGET=bootloader

MACH=-mcpu=cortex-m4
FLOAT=-mfloat-abi=soft

BUILD_DIR = Build
ROOT_DIR = ..

LINKER= -T $(ROOT_DIR)/linkers/STM32F411_BOOT.ld
MAP_FILE= -Wl,-Map=$(BUILD_DIR)/$(TARGET).map

CFLAGS= -c $(MACH) -mthumb $(FLOAT) -std=gnu99 -Wall -O0 \
		--specs=nano.specs -ffunction-sections -fdata-sections

LDFLAGS = $(MACH) -mthumb $(FLOAT) --specs=nosys.specs $(LINKER) $(MAP_FILE) \
			-Wl,--gc-sections -static --specs=nano.specs -Wl,--start-group -lc -lm \
			-Wl,--end-group -Wl,--print-memory-usage

OBJCOPY=arm-none-eabi-objcopy

###########################################
#				 INCLUDES
###########################################

INCLUDES+= -I $(ROOT_DIR)/bootloader/Inc/
INCLUDES+= -I $(ROOT_DIR)/drivers/Inc/ 
INCLUDES+= -I $(ROOT_DIR)/common/Inc/ 
INCLUDES+= -I $(ROOT_DIR)/interface/Inc/

############################################
# 				SOURCE FILES
############################################

OBJS		+= $(BUILD_DIR)/bootloader.o
OBJS		+= $(BUILD_DIR)/syscalls.o
OBJS		+= $(BUILD_DIR)/startup.o
OBJS		+= $(BUILD_DIR)/config_boot.o
OBJS		+= $(BUILD_DIR)/bl-info.o
OBJS		+= $(BUILD_DIR)/bl-flash.o

DRIVERS		+= $(BUILD_DIR)/driver_clock.o
DRIVERS		+= $(BUILD_DIR)/driver_interrupt.o
DRIVERS		+= $(BUILD_DIR)/driver_systick.o
DRIVERS		+= $(BUILD_DIR)/driver_gpio.o
DRIVERS		+= $(BUILD_DIR)/driver_uart.o
DRIVERS		+= $(BUILD_DIR)/driver_flash.o

SHARED		+= $(BUILD_DIR)/crc8.o
SHARED		+= $(BUILD_DIR)/ring-buffer.o
SHARED		+= $(BUILD_DIR)/simple-timer.o

COMMS		+= $(BUILD_DIR)/comms.o

INTERFACE	+= $(BUILD_DIR)/interface_io.o
INTERFACE	+= $(BUILD_DIR)/interface_comm.o
INTERFACE	+= $(BUILD_DIR)/interface_timebase.o

INTERFACE	+= $(BUILD_DIR)/wrapper_io.o
INTERFACE	+= $(BUILD_DIR)/protocol_uart.o



PREREQ = $(BUILD_DIR)/

all: $(PREREQ) $(BUILD_DIR)/$(TARGET).elf

$(PREREQ):
	mkdir $(PREREQ)

$(BUILD_DIR)/%.o: $(ROOT_DIR)/bootloader/Src/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $(BUILD_DIR)/$(*).o $(ROOT_DIR)/bootloader/Src/$(*).c

$(BUILD_DIR)/%.o: $(ROOT_DIR)/drivers/Src/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $(BUILD_DIR)/$(*).o $(ROOT_DIR)/drivers/Src/$(*).c

$(BUILD_DIR)/%.o: $(ROOT_DIR)/common/Src/shared/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $(BUILD_DIR)/$(*).o $(ROOT_DIR)/common/Src/shared/$(*).c

$(BUILD_DIR)/%.o: $(ROOT_DIR)/common/Src/comms/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $(BUILD_DIR)/$(*).o $(ROOT_DIR)/common/Src/comms/$(*).c

$(BUILD_DIR)/%.o: $(ROOT_DIR)/common/Src/core/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $(BUILD_DIR)/$(*).o $(ROOT_DIR)/common/Src/core/$(*).c

$(BUILD_DIR)/%.o: $(ROOT_DIR)/interface/Src/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $(BUILD_DIR)/$(*).o $(ROOT_DIR)/interface/Src/$(*).c

$(BUILD_DIR)/%.o: $(ROOT_DIR)/linkers/*.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $(BUILD_DIR)/$(*).o $(ROOT_DIR)/linkers/$(*).c

# TARGET ELF
$(BUILD_DIR)/$(TARGET).elf: $(OBJS) $(DRIVERS) $(SHARED) $(INTERFACE) $(COMMS)
	$(CC) $(LDFLAGS) -o $@ $^
	$(OBJCOPY) -O binary $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).bin
	arm-none-eabi-size $(BUILD_DIR)/$(TARGET).elf
	python3 pad_bootloader.py

load:
	openocd -f interface/jlink.cfg -c "transport select swd" -f target/stm32f4x.cfg -c init -c "reset init" \
	-c "flash write_image erase Build/$(TARGET).elf" -c "reset run" -c shutdown

clean:
	rm -rf $(BUILD_DIR)/*.map $(BUILD_DIR)/*.o