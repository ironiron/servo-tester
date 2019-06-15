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
#include <avr/wdt.h>

#define button (1<<PB1)
#define output (1<<PB0)
#define potenciometer (1<<PB4)
#define set_output PORTB|=(1<<PB0)
#define clear_output PORTB&=~(1<<PB0)
#define TCNT0_BASE 105 // tick resolution for manipulating PWM lenght is 150, thus 255-150=105.

//SPI related
#define SET_SS PORTB|=(1<<PB5)
#define SET_CLOCK PORTB|=(1<<PB2)
#define SET_MOSI PORTB|=(1<<PB3)

#define RESET_SS PORTB&=~(1<<PB5)
#define RESET_CLOCK PORTB&=~(1<<PB2)
#define RESET_MOSI PORTB&=~(1<<PB3)


volatile uint8_t adc=0;
volatile uint8_t remember=0;
volatile uint16_t ticks=0;
volatile uint8_t position=0;
volatile uint8_t overflows_left=0;

enum current_mode {normal, neutral, oscillating} current_mode;
enum direction {left, right} direction;
enum state {waiting, PWM, PWM_overflows} state;
	
void _send_SPI(uint8_t data)
{
	//CPOL=0
	//CPHA=0
	RESET_CLOCK;
	RESET_MOSI;
	RESET_SS;
	for(uint8_t i=0;i<8;i++)
	{
		if((data<<i) & 0x0f)
		{
			SET_MOSI;
		}
		else
		{
			RESET_MOSI;
		}
		SET_CLOCK;
		_delay_us(10);
		RESET_CLOCK;
		_delay_us(10);
	}
	SET_SS;
	
}

void calculate_ticks(void)
{
	switch (current_mode)
	{
		case normal:
		ticks=adc*3/2+75;// 1 adc=10ms; add 75 so begins counting fom 0,5ms.
		
		break;
		
		case neutral:
		ticks=225;//one tick is 6,(6)us, so 225ticks=1,5ms
		overflows_left=0;
		break;
		
		case oscillating:
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
		if(position==0)position=1;
		ticks=position*3/2+75;// 1 adc=10ms
		
		break;
	}
			if(ticks>0xff)
			{
				overflows_left=ticks/0xff;
				ticks=ticks%255;
			}
	
}
	
void set_timer_generating(void)
{
	TCCR0B = (1<<CS01); /*up-counting prescaler 8, interrupt enable*/
}

void set_timer_waiting(void)
{
	TCCR0B = (1<<CS02); /*up-counting prescaler 256, interrupt enable*/
	TCNT0=162; /*interrupt every 19,8 ms (f_cpu= 1200000 Hz)*/
}

ISR(TIM0_OVF_vect)
{
	
	switch(state)
	{
		case waiting:
			set_timer_generating();
			if (overflows_left!=0)//check if more than 0xff ticks are required
			{
				state=PWM_overflows;
				overflows_left--;
				//TCNT0 already set to 0 by default.
			}
			else
			{
				state=PWM;
				TCNT0=0xff-ticks;
			}
			set_output;
		break;
		
		case PWM:
			clear_output;
			state=waiting;
			set_timer_waiting();
			calculate_ticks();
		break;
		
		case PWM_overflows:
			if (overflows_left!=0)
			{
				overflows_left--;
			}
			else
			{
				TCNT0=0xff-ticks;
				state=PWM;
			}
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

ISR(WDT_vect)
{
	_send_SPI(0x78);
	_send_SPI(0x20);
}

int main(void)
{
    	DDRB |= output;
	PORTB |=button;

	DDRB |= (1<<PB2)|(1<<PB3)|(1<<PB5);
	
	GIMSK |=(1<<INT0); /*interrupt on low level*/
	
	set_timer_waiting();
	state=waiting;
	
	TIMSK0 |= (1<<TOIE0);
	
	ADCSRA |=(1<<ADEN) | (1<<ADPS2);		 /*prescaler 16 */
	ADMUX |=(1<<MUX1); /*input- PB4*/
	
	wdt_enable(WDTO_120MS);
	WDTCR |= (1<<WDTIE);
//WDTCR |= (0<<WDP3) | (1<<WDP2) | (0<<WDP1) | (1<<WDP0);

// Set watchdog timer in interrupt mode
// WDTCR |= (1<<WDTIE);
// WDTCR |= (0<<WDE);
	sei();
	
    while(1)
    {
		ADCSRA |=(1<<ADSC);
		while(ADCSRA & (1<<ADSC))
		adc=ADC/5;	/*result- over 200*/
		if(adc>200)
		{
			adc=200;
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