CC=arm-none-eabi-gcc
MACH=cortex-m4
CFLAGS= -c -mcpu=$(MACH) -mthumb -mfloat-abi=soft -std=gnu11 -Wall -O0 
LDFLAGS =  -mcpu=$(MACH) -mthumb -mfloat-abi=soft --specs=nano.specs -T stm32_ls.ld -Wl,-Map=final.map
OBJCOPY=arm-none-eabi-objcopy
#CFLAGS = -c -mcpu=$(MACH) -mthumb -std=gnu11 -Wall -O0 -mfloat-abi=hard -mfpu=fpv4-sp-d16

###########################################
#				 INCLUDES

INCLUDES= -I Drivers/Inc/ \
-I Inc/



############################################
# Source files

OBJS		+= Build/bootloader.o
OBJS		+= Build/syscalls.o
OBJS		+= Build/stm32_startup.o

all: Build/final.elf

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
	$(OBJCOPY) -O binary Build/final.elf Build/bootloader.bin
	python3 pad_bootloader.py


clean:
	rm -rf *.o *.map Build/*.o