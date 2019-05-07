#define UART_BAUDRATE	9600
#define BAUD_PRESCALE	((F_CPU / 16 / UART_BAUDRATE) - 1)

#include <avr/io.h>
#include <util/delay.h>

void uart_init(void) {
	// Set baud rate
	UBRR0L = BAUD_PRESCALE;
	UBRR0H = BAUD_PRESCALE >> 8;

	UCSR0C = (1<<UCSZ01) | (1<<UCSZ00); // Set frame format: 8data, 1 stop bit
	UCSR0B = (1<<RXEN0)  | (1<<TXEN0);  // Enable receiver and transmitter
}

void uart_tx(unsigned char data) {
	while(!(UCSR0A & (1<<UDRE0))); // Wait for empty transmit buffer
	UDR0 = data; //Put data into buffer, sends the data
}

uint8_t uart_rx(void) {
	while(!(UCSR0A & (1<<RXC0))); // Wait for data to be received
	return UDR0; // Get and return received data from buffer
}

void put_str(char* str, uint8_t size) {
	for (uint8_t i=0; i<size; i++)
		uart_tx(str[i]);
}

int	main(void) {
	char str[14] = "Hello World!\n";

	uart_init();
	for(;;) {
		put_str(str, 13);
		_delay_ms(500);
	}
}
