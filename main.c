

//Macro definition
#ifndef __LEDSTAT_H_
#define __LEDSTAT_H_
#define LED_ON 	(0x01)			/**< LED state HIGH */
#define LED_OFF	(0x00)			/**< LED state LOW */


#define LED_PORT (PORTB)    /**< LED Port Number */
#define LED_PIN  (PORTB0)   /**< LED Pin number  */
#define SENSOR_ON !(PIND&(1<<PD0)) // Switch1 ON
#define HEAT_ON !(PIND&(1<<PD1)) // Switch2 ON

/**
 * Function Definitions
 */

/**
 * @brief Change the state of the LED Pin according to the value of state
 *
 * @param state Pin level to which the LED Pin should be set
 */

#endif /** __LEDSTAT_H_ */
#include <avr/io.h>
#include <util/delay.h>
#ifndef __OUTPWM_H__
#define __OUTPWM_H__
#include<avr/io.h>
/**
 * @brief Function definition
 *
 * @param temp_value
 * @return char
 */
char OutPWM(uint16_t temp_value);
void InitPWM(void);
#endif
void ledstat(uint8_t state);
void InitLED(void);

void InitPWM(void)
{
    /*Configuring the registers and ports*/
    TCCR1A|=(1<<COM1A1)|(1<<WGM10)|(1<<WGM11);
    TCCR1B|=(1<<WGM12)|(1<<CS11)|(1<<CS10);
    DDRB|=(1<<PB1);

}
/**
 * @brief Output with respect to analog input
 *
 * @param ADC_val
 */
char OutPWM (uint16_t ADC_val)
{

    char temperature;

    if((ADC_val>=0) && (ADC_val<=209)){

        OCR1A = 205; //20% duty cycle
        temperature = 20;
        _delay_ms(20);
    }
    else if((ADC_val>=210) && (ADC_val<=509)){

        OCR1A = 410; //40% duty cycle
        temperature = 25;
       _delay_ms(20);
    }
    else if((ADC_val>=510) && (ADC_val<=709)){

        OCR1A = 717;//70% duty cycle
        temperature = 29;
        _delay_ms(20);
    }
    else if((ADC_val>=710) && (ADC_val<=1024)){

        OCR1A = 973; //95% duty cycle
        temperature = 33;
        _delay_ms(20);
    }
    else{
        OCR1A = 0; //0% output
        temperature = 0;
    }
    return temperature;
}
void ledstat(uint8_t state)
{
	LED_PORT = (state << LED_PIN);
}
void InitLED(void)
{
	DDRB|=(1<<PB0);
    DDRD&=~(1<<PD0);
    PORTD|=(1<<PD0);
    PORTD|=(1<<PD1);
}
uint16_t ReadADC(uint8_t ch)
{
    //Select ADC Channel ch must be 0-7
    ADMUX&=0xf8;
    ch=ch&0b00000111;
    ADMUX|=ch;
    //Start single conversion
    ADCSRA|=(1<<ADSC);
    //Wait for conversion to complete
    while(!(ADCSRA & (1<<ADIF)));
    //Clear ADIF by writing one to it
    ADCSRA|=(1<<ADIF);
    return(ADC);
}
void InitADC()
{
    ADMUX=(1<<REFS0);
    ADCSRA=(1<<ADEN)|(7<<ADPS0);

}
void InitUART(uint16_t ubrr_value){

    UBRR0L = ubrr_value;
    UBRR0H = (ubrr_value>>8)&(0x00ff);
    UCSR0C = (1<<UMSEL00)|(1<<UCSZ01)|(1<<UCSZ01);

    UCSR0B = (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0)|(1<<TXCIE0);

}

/**
 * @brief write data on UART ports
 *
 * @param data
 */
void UARTwrite(char data)
{
    while(!(UCSR0A & (1<<UDRE0)))
    {

    }
    UDR0 = data;
}

void peripheral_init(void)
{
    /*Configure LED and Switch pins*/
    InitLED();
    /*Configure ADC registers and pins*/
    InitADC();
    /*Configure PWM registers and pins*/
    InitPWM();
    /*Configure UART serial communication pin*/
    InitUART(103);
}
int main(void)
{
peripheral_init();
    // Insert code

    uint16_t temp;
    while(1)
    {
        temp=ReadADC(0);
        _delay_ms(200);
    }

    return 0;
}
