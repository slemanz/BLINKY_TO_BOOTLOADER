CC=arm-none-eabi-gcc
MACH=cortex-m4
CFLAGS= -c -mcpu=$(MACH) -mthumb -std=gnu11 -Wall -O0
LDFLAGS= -nostdlib -T stm32_ls.ld -Wl,-Map=final.map
OBJCOPY=arm-none-eabi-objcopy

INCLUDES= -I Drivers/Inc/


all: Build/main.o Build/stm32_startup.o final.elf

# target and recipe
# to analyze the .o: 
#	arm-none-eabi-objdump -h main.o
#	arm-none-eabi-objdump -d main.o > main_log
Build/main.o: Src/main.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ 

Build/gpio.o: Drivers/Src/gpio.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ 

Build/stm32_startup.o: stm32_startup.c
	$(CC) $(CFLAGS) -o $@ $^ 

Build/systick.o: Drivers/Src/systick.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ 

final.elf: Build/main.o Build/stm32_startup.o Build/gpio.o Build/systick.o
	$(CC) $(LDFLAGS) -o $@ $^
	$(OBJCOPY) -O binary final.elf Build/flash.bin
	$(OBJCOPY) -O binary final.elf ~/opt/SEGGER/flash.bin




clean:
	rm -rf *.o *.elf *.map Build/*.o