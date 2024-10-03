CC=arm-none-eabi-gcc
MACH=cortex-m4
CFLAGS= -c -mcpu=$(MACH) -mthumb -mfloat-abi=soft -std=gnu11 -Wall -O0 
LDFLAGS =  -mcpu=$(MACH) -mthumb -mfloat-abi=soft --specs=nano.specs -T stm32_ls.ld -Wl,-Map=Build/final.map
OBJCOPY=arm-none-eabi-objcopy
LINKER_SCRIPT=stm32_ls.ld

###########################################
#				 INCLUDES

INCLUDES+= -I Inc/
INCLUDES+= -I ../drivers/Inc/ 
INCLUDES+= -I ../shared/Inc/



############################################
# Source files

OBJS		+= Build/main.o
OBJS		+= Build/bootloader.o
OBJS		+= Build/stm32_startup.o
OBJS		+= Build/gpio.o
OBJS		+= Build/systick.o
OBJS		+= Build/system.o
OBJS		+= Build/timer.o
OBJS		+= Build/syscalls.o
OBJS		+= Build/uart.o
OBJS		+= Build/ring-buffer.o

all: Build/final.elf

# target and recipe
# to analyze the .o: 
#	arm-none-eabi-objdump -h main.o
#	arm-none-eabi-objdump -d main.o > main_log

Build/%.o: Src/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o Build/$(*).o Src/$(*).c

Build/%.o: Src/%.S
	$(CC) $(CFLAGS) $(INCLUDES) -o Build/$(*).o Src/$(*).S

Build/%.o: ../shared/Src/core/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o Build/$(*).o ../shared/Src/core/$(*).c

Build/%.o: ../shared/Src/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o Build/$(*).o ../shared/Src/$(*).c

Build/%.o: ../drivers/Src/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o Build/$(*).o ../drivers/Src/$(*).c

Build/stm32_startup.o: stm32_startup.c
	$(CC) $(CFLAGS) -o $@ $^ 

Build/final.elf: $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^
	$(OBJCOPY) -O binary Build/final.elf Build/flash.bin
	$(OBJCOPY) -O binary Build/final.elf ~/opt/SEGGER/flash.bin


clean:
	rm -rf *.o *.map Build/*.o