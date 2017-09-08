/*
 * tester_serw.c
 *
 * Created: 2015-01-10 17:53:29
 *  Author: Rafał Mazurkiewicz
 tester serw wysyła co ok. 20ms impuls o długości 0,5-2,5ms do serwa.
 Potencjometr na PB4
 Przycisk na PB1 INT0. długie (>1s) naciśnięcie serwo oscyluje, krótkie stoi w neutrum 
 powrót do pracy swobodnej potencjometrem, bądź przyciskiem jeśli był tryb oscylacji.
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
volatile uint8_t lenght=0;
enum current_mode {normal, neutral, oscillating} current_mode;
enum direction {left, right} direction;

ISR(TIM0_OVF_vect)
{
	TCNT0=177;// interrupt every 19,9 ms
	
	switch (current_mode)
	{
		case normal:
		set_output;
		for(ticks=0;ticks<adc;ticks++)_delay_us(10);
		_delay_us(500);
		clear_output;
		break;
		
		case neutral:
		set_output;
		_delay_us(500);//because maximum is 768 us
		_delay_us(500);
		_delay_us(500);//delay =1.5ms
		clear_output;
		break;
		
		case oscillating:
		set_output;
		for(ticks=0;ticks<lenght;ticks++)_delay_us(10);
		_delay_us(500);
		clear_output;
		adc=adc/20;
		if(direction==left)
		{
			if(lenght-adc<0)lenght=0;
			else lenght=lenght-adc;
		}
		else 
		{
			if(lenght+adc>200)lenght=200;
			else lenght=lenght+adc;
		}
		if(lenght==200)direction=left;
		if(lenght==0)direction=right;
		break;
	}
}

ISR(INT0_vect)
{
	cli();
	_delay_ms(200);//debouncing
	remember=adc;
	current_mode=neutral;
	while(!(PINB & button))
	{
		ticks++;
		_delay_ms(10);
		if(ticks>100)
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
	
	GIMSK |=(1<<INT0);//interrupt on low level
	
	TCCR0B |= (1<<CS02); //up-counting prescaler 256
	TIMSK0 |= (1<<TOIE0);
	
	ADCSRA |=(1<<ADEN) | (1<<ADPS2);		// prescaler-16 
	ADMUX |=(1<<MUX1); //input- PB4
	sei();
    while(1)
    {
		ADCSRA |=(1<<ADSC);
		while(ADCSRA & (1<<ADSC))
		adc=ADC/5;	//result- almost 200
		if(remember-adc>50||remember+adc<50)
		if(current_mode==neutral)current_mode=normal;
    }
}