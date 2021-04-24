/*
 */

#include <avr/io.h>

int main(void)
{
    DDRB|=(1<<PB0);

    // Insert code

    while(1)
    {
        if((PIND&(1<<PD0))&&(PIND&(1<<PD1)))
        {
            PORTB|=(1<<PB0);
        }
        else
        {
            PORTB&=~(1<<PB0);
        }
    }


    return 0;
}
