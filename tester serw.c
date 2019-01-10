/*
 * tester_serw.c
 *
 * Created: 2015-01-10 17:53:29
 *  Author: Rafał Mazurkiewicz
 Servo tester. In period of 20ms sends 0,5-2,5ms impulse to servo.
 potentiometer PB4
 button PB1 INT0 long press (>1s) servo is oscillating, short press- neutrum.
 Return to normal mode by pressing button (if was oscillating), or by moving potentiometer.
 output PB0
 
 tester serw wysyła co ok. 20ms impuls o długości 0,5-2,5ms do serwa.
 Potencjometr na PB4
 Przycisk na PB1 INT0. długie (>1s) naciśnięcie serwo oscyluje, krótkie stoi w neutrum 
 powrót do pracy swobodnej potencjometrem, bądź przyciskiem jeśli wcześniej był w tryb oscylacji.
 wyjście PB0
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define button (1<<PB1)
#define output (1<<PB0)
#define potenciometer (1<<PB4)
#define set_output PORTB|=(1<<PB0)
#define clear_output PORTB&=~(1<<PB0)

volatile uint8_t adc=0;
volatile uint8_t remember=0;
volatile uint8_t ticks=0;
volatile uint8_t position=0;
enum current_mode {normal, neutral, oscillating} current_mode;
enum direction {left, right} direction;

ISR(TIM0_OVF_vect)
{
	TCNT0=162; /*interrupt every 19,8 ms (f_cpu= 1200000 Hz)*/
	
	switch (current_mode)
	{
		case normal:
		if(adc==0)
		{
			adc=1;
		}
		ticks=adc;
		set_output;
		/*asm loop (10us)*/
		asm(
		"1: dec %0" "\n\t"
		
		"nop" "\n\t"
		"nop" "\n\t"
		"nop" "\n\t"
		
		"nop" "\n\t"
		"nop" "\n\t"
		"nop" "\n\t"
		
		"nop" "\n\t"
		"nop" "\n\t"
		"nop" "\n\t"
		
		"brne 1b"
		: "=r" (ticks)
		: "0" (ticks)
		);
		_delay_us(490);
		clear_output;
		break;
		
		case neutral:
		set_output;
		_delay_us(500);
		_delay_us(500);
		_delay_us(500);/*delay =1.5ms (max delay of this func. can be only 637 us at 1,2MHz)*/
		clear_output;
		break;
		
		case oscillating:
		ticks=position;
		set_output;
		/*asm loop (10us)*/
		asm(
		"1: dec %0" "\n\t"

		"nop" "\n\t"
		"nop" "\n\t"
		"nop" "\n\t"
		
		"nop" "\n\t"
		"nop" "\n\t"
		"nop" "\n\t"
		
		"nop" "\n\t"
		"nop" "\n\t"
		"nop" "\n\t"
		
		"brne 1b"
		: "=r" (ticks)
		: "0" (ticks)
		);
		_delay_us(490);
		clear_output;
		adc=adc/20;
		if(direction==left)
		{
			if(position<adc)position=0;// if position-adc<0
			else position=position-adc;
		}
		else 
		{
			if(position+adc>200)position=200;
			else position=position+adc;
		}
		if(position==200)direction=left;
		if(position==0)direction=right;
		if(position==0)position=1;;
		break;
	}
}

ISR(INT0_vect)
{
	cli();
	_delay_ms(100);/*debouncing*/
	remember=adc;
	current_mode=neutral;
	ticks=0;
	while(!(PINB & button))
	{
		ticks++;
		_delay_ms(10);
		if(ticks>100) /* long press >1s */
		{
			current_mode=oscillating;
			ticks=0;
		}
	}
	sei();
}

int main(void)
{
    DDRB |= output;
	PORTB |=button;
	
	GIMSK |=(1<<INT0); /*interrupt on low level*/
	
	TCCR0B |= (1<<CS02); /*up-counting prescaler 256, interrupt enable*/
	TIMSK0 |= (1<<TOIE0);
	
	ADCSRA |=(1<<ADEN) | (1<<ADPS2);		 /*prescaler 16 */
	ADMUX |=(1<<MUX1); /*input- PB4*/
	sei();
	
    while(1)
    {
		ADCSRA |=(1<<ADSC);
		while(ADCSRA & (1<<ADSC))
		adc=ADC/5;	/*result- over 200*/
		if(adc>201)
		{
			adc=201;
		}
		if(remember+30<adc || remember>adc+30)
		{
			if(current_mode==neutral)
			{
				current_mode=normal;
			}
		}
    }
}