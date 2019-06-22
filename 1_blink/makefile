MCU = atmega328p
F_CPU = 16000000UL
CC = avr-gcc
OBJCOPY = avr-objcopy
CFLAGS = -std=c99 -Wall -Os -ffunction-sections -I.
MCUFLAGS = -mmcu=${MCU} -DF_CPU=${F_CPU}
SERIAL_PORT = /dev/ttyUSB0
FLASH_BAUDRATE = 57600 # new bootloader 115200
TARGET = main

all:
	${CC} ${CFLAGS} ${MCUFLAGS} -o ${TARGET}.bin ${TARGET}.c
	${OBJCOPY} -j .text -j .data -O ihex ${TARGET}.bin ${TARGET}.hex
	avr-size $(TARGET).bin

flash: all
	avrdude -p ${MCU} -c arduino -P $(SERIAL_PORT) -b $(FLASH_BAUDRATE) -D -U flash:w:${TARGET}.hex:i

clean:
	rm -f *.bin *.hex

.PHONY: clean flash
