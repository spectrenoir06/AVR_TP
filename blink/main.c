#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

int	main(void) {
	DDRB |= (1 << PIN5); // OUTPUT
	for(;;) {
		PORTB |= (1 << PIN5); // HIGH
		_delay_ms(100);
		PORTB &= ~(1 << PIN5); // LOW
		_delay_ms(100);
	}
}
