CC=arm-none-eabi-gcc
MACH=cortex-m4
CFLAGS= -c -mcpu=$(MACH) -mthumb -std=gnu11 -Wall -O0
LDFLAGS= -nostdlib -T stm32_ls.ld -Wl,-Map=final.map
OBJCOPY=arm-none-eabi-objcopy

###########################################
#				 INCLUDES

INCLUDES= -I Drivers/Inc/ \
-I Inc/



############################################
# Source files

#OBJS		+= Build/main.o
OBJS		+= Build/timer_test.o
OBJS		+= Build/stm32_startup.o
OBJS		+= Build/gpio.o
OBJS		+= Build/systick.o
OBJS		+= Build/system.o
OBJS		+= Build/timer.o

all: Build/final.elf

# target and recipe
# to analyze the .o: 
#	arm-none-eabi-objdump -h main.o
#	arm-none-eabi-objdump -d main.o > main_log

Build/%.o: Src/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o Build/$(*).o Src/$(*).c

Build/%.o: Src/core/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o Build/$(*).o Src/core/$(*).c

Build/%.o: Drivers/Src/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o Build/$(*).o Drivers/Src/$(*).c

Build/stm32_startup.o: stm32_startup.c
	$(CC) $(CFLAGS) -o $@ $^ 

Build/final.elf: $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^
	$(OBJCOPY) -O binary Build/final.elf Build/flash.bin
	$(OBJCOPY) -O binary Build/final.elf ~/opt/SEGGER/flash.bin


clean:
	rm -rf *.o *.elf *.map Build/*.o