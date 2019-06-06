MCU=atmega328p
F_CPU=16000000UL
CC=avr-gcc
OBJCOPY=avr-objcopy
CFLAGS=-std=c99 -Wall -g -Os -mmcu=${MCU} -DF_CPU=${F_CPU} -I.
TARGET=main
SRCS=main.c

all:
	${CC} ${CFLAGS} -o ${TARGET}.bin ${SRCS}
	${OBJCOPY} -j .text -j .data -O ihex ${TARGET}.bin ${TARGET}.hex

flash: all
	avrdude -p ${MCU} -c arduino -P /dev/ttyUSB0 -b 57600 -D -U flash:w:${TARGET}.hex:i

clean:
	rm -f *.bin *.hex

.PHONY: clean flash
