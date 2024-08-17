CC=arm-none-eabi-gcc
MACH=cortex-m4
CFLAGS= -c -mcpu=$(MACH) -mthumb -std=gnu11 -O0

all: main.o stm32_startup.o

# target and recipe
# to analyze the .o: 
#	arm-none-eabi-objdump -h main.o
#	arm-none-eabi-objdump -d main.o > main_log
main.o: Src/main.c
	$(CC) $(CFLAGS) -o $@ $^ 

stm32_startup.o: stm32_startup.c
	$(CC) $(CFLAGS) -o $@ $^ 

clean:
	rm -rf *.o *.elf