#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

void main()
{
    DDRB = 0xff;

    PORTB |= (1 << 5);
    _delay_ms(1000);
    PORTB &= ~(1 << 5);
    _delay_ms(1000);


}

