#define UART_BAUDRATE 115200

// #define BAUD_PRESCALE ((F_CPU / 16 / UART_BAUDRATE) - 1) // Async normal     20.3.1
#define BAUD_PRESCALE ((F_CPU / 8 / UART_BAUDRATE) - 1) // Async double speed   20.3.1

#include <avr/io.h>
#include <util/delay.h>

void uart_init(void) {
	UBRR0L = BAUD_PRESCALE; // Set baud rate                                    20.11.5 UBRRnL
	UBRR0H = BAUD_PRESCALE >> 8;

	UCSR0A = 1<<U2X0; // Double speed                                           20.11.2 UCSRnA
	UCSR0B = (1<<RXEN0)  | (1<<TXEN0);  // Enable receiver and transmitter      20.11.3 UCSRnB
	UCSR0C = (1<<UCSZ01) | (1<<UCSZ00); // 8-N-1                                20.11.4 UCSRnC
}

void uart_tx(unsigned char data) {
	while(!(UCSR0A & (1<<UDRE0))); // Wait for empty transmit buffer            20.11.2 UCSRnA
	UDR0 = data; //Put data into buffer, sends the data                         20.11.1 UDRn
}

uint8_t uart_rx(void) {
	while(!(UCSR0A & (1<<RXC0))); // Wait for data to be received               20.11.2 UCSRnA
	return UDR0; // Get and return received data from buffer                    20.11.1 UDRn
}

void put_str(char* str, uint8_t size) {
	do
		uart_tx(*str++);
	while(--size);
}

int	main(void) {
	char str[] = "Hello World!\r\n";

	uart_init();
	for(;;) {
		put_str(str, sizeof(str)-1);
		_delay_ms(1000);
	}
}
