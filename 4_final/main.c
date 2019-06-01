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

void put_str(const char* str, uint8_t size) {
	do
		uart_tx(*str++);
	while(--size);
}

uint8_t ft_strlen(const char *s) {
	uint8_t c = 0;
	while(*s++)
		++c;
	return c;
}

void print_str(const char* str) {
	uint8_t len = ft_strlen(str);
	put_str(str, len);
}

void getInput(char *str, uint8_t hide) {
	char c;
	char *ptr = str;

	for(uint8_t i=0; i<255; i++) // clear input
		str[i] = 0;

	for(;;) {
		c = uart_rx();
		switch (c) {
			case 0x7F: // del
				if (ptr>str) {
					*ptr = 0;
					--ptr;
					put_str("\b \b", 3);
				}
				break;
			case '\r': // enter
				return;
			default:
				if (ptr< str + 255) {
					*ptr++ = c;
					uart_tx(hide ? '*' : c);
				}
		}
	}
}

int8_t ft_strcmp(const char* s1, const char* s2)
{
	while (*s1 != '\0' && (*s1++ == *s2++));
	return (*(unsigned char *)--s1 - *(unsigned char *)--s2);
}

const char user[255] = "spectre";
const char pass[255] = "secret";

int	main(void) {
	char input[255];

	uart_init();
	DDRB |= (1 << PIN5); // OUTPUT
	for(;;) {
		print_str("\r\nHello please login:\r\n");
		print_str("\tUser: ");

		getInput(input, 0);
		if (!ft_strcmp(user, input)) {
			print_str("\r\n\tPass: ");
			getInput(input, 1);
			if (!ft_strcmp(pass, input)) {
				print_str("\r\nWelcome ");
				print_str(user);
				for(;;) {
					PORTB ^= (1 << PIN5);
					_delay_ms(100);
				}

			} else
				print_str("\r\nWrong password\r\n");
 		} else
			print_str("\r\nNo user found\r\n");
	}
}
