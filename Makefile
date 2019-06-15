PRG = led
OBJ = led.o
MCU_TARGET = atmega328p
OPTIMIZE = -O2
DEFS = 
LIBS = 
CFLAGS=-g -mmcu=$(MCU) -Wall -Wstrict-prototypes -Os -mcall-prologues
#
led.hex : led.elf
     avr-size led.elf
     avr-objcopy -R .eeprom -O ihex led.elfled.hex
led.hex : led.o
avr-gcc $(CFLAGS) -o led.elf -Wl,-Map, led.map led.o
led.o : led.c
     avr-gcc $(CFLAGS) -Os -c led.c
#
