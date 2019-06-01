#include <avr/io.h>
#include <util/delay.h>

// 14.2.3

int	main(void) {
	DDRB |= (1 << PIN5); // OUTPUT
	for(;;) {
		PORTB ^= (1 << PIN5);
		_delay_ms(500);
	}
}
