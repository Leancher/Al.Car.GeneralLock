#include "board.h"

#define getbit(port, bit)		((port) &   (1 << (bit)))
#define setbit(port,bit,val)	{if ((val)) {(port)|= (1 << (bit));} else {(port) &= ~(1 << (bit));}}

//Инициализация неиспользуемых выводов для экономии энергии
// void unused_pin_init()
// {
// 	setbit(DDRA,0,0);
// 	setbit(PORTA,0,1);
// 	setbit(DDRA,1,0);
// 	setbit(PORTA,1,1);	
// 	setbit(DDRA,2,0);
// 	setbit(PORTA,2,1);
// 	setbit(DDRA,3,0);
// 	setbit(PORTA,3,1);	
// 	
// 	setbit(DDRB,0,0);
// 	setbit(PORTB,0,1);	
// 	setbit(DDRB,1,0);
// 	setbit(PORTB,1,1);
// 	setbit(DDRB,2,0);
// 	setbit(PORTB,2,1);	
// 	setbit(DDRB,3,0);
// 	setbit(PORTB,3,1);	
// 	setbit(DDRB,4,0);
// 	setbit(PORTB,4,1);
// 	setbit(DDRB,5,1);
// 	setbit(PORTB,5,0);
// 	setbit(DDRB,6,1);
// 	setbit(PORTB,6,0);
// 	setbit(DDRB,7,1);
// 	setbit(PORTB,7,0);	
// 	
// 	setbit(DDRD,0,0);
// 	setbit(PORTD,0,1);
// 	setbit(DDRD,1,0);
// 	setbit(PORTD,1,1);
// 	setbit(DDRD,7,1);
// 	setbit(PORTD,7,0);
// }

void adc_init_voltage_acc()
{
	adc_init(6, ADC_ADJUST_RIGHT, ADC_REFS_INTERNAL_1_1,  ADC_PRESCALER_32);
}

void button_stop_enable()
{
	setbit(DDRC,6,0);
	setbit(PORTC,6,1);
}

byte pedal_stop_is_pressed()
{
	if (getbit(PINC,6)) {return 1;}
	return 0;
}

void door_sensor_enable()
{
	setbit(DDRC,7,0);
	setbit(PORTC,7,1);
}

byte door_is_open()
{
	if (getbit(PINC,7)) {return 0;}
	return 1;
}

void relay_siren_set_state(byte state)
{
	setbit(DDRC,1,1);
	setbit(PORTC,1,state);	
}

void door_switch_enable()
{
	setbit(DDRD,6,0);
	setbit(PORTD,6,1);
}

byte door_switch_is_pressed()
{
	if (getbit(PIND,6)) {return 0;}
	return 1;	
}

void button_trunk_enable()
{
	setbit(DDRA,7,0);
	setbit(PORTA,7,1);	
}

byte button_trunk_is_pressed()
{
	if (getbit(PINA,7)) {return 0;}
	return 1;
}

void keychain_open_enable()
{
	setbit(DDRA,5,0);
	setbit(PORTA,5,1);	
}

byte keychain_open_is_pressed()
{
	if (getbit(PINA,5)) {return 0;}
	return 1;
}

void keychain_close_enable()
{
	setbit(DDRA,4,0);
	setbit(PORTA,4,1);	
}

byte keychain_close_is_pressed()
{
	if (getbit(PINA,4)) {return 0;}
	return 1;
}

void board_led_set_state(byte state)
{
	setbit(DDRD,7,1);
	setbit(PORTD,7,state);
}

void trunk_actuator_set_state(byte state)
{
	setbit(DDRC,0,1);
	setbit(PORTC,0,state);
}

void indicator_set_state(byte state)
{
	setbit(DDRB,7,1);
	setbit(PORTB,7,state);	
}

void driver_locker_1_set_state(byte state)
{
	setbit(DDRB,0,1);
	setbit(PORTB,0,state);
}

void driver_locker_2_set_state(byte state)
{
	setbit(DDRB,1,1);
	setbit(PORTB,1,state);
}

void driver_door_handle_enable(byte state)
{
	setbit(DDRB,6,1);
	setbit(PORTB,6,state);
}

void driver_in_1_set_state(byte state)
{
	setbit(DDRB,2,1);
	setbit(PORTB,2,state);
}

void driver_in_2_set_state(byte state)
{
	setbit(DDRB,3,1);
	setbit(PORTB,3,state);
}

void driver_in_3_set_state(byte state)
{
	setbit(DDRB,4,1);
	setbit(PORTB,4,state);
}

void driver_in_4_set_state(byte state)
{
	setbit(DDRB,5,1);
	setbit(PORTB,5,state);
}

void button_door_1_enable()
{
	setbit(DDRA,0,0);
	setbit(PORTA,0,1);
}

int button_door_1_is_pressed()
{
	if (getbit(PINA,0)) {return 0;}
	return 1;
}

void button_door_2_enable()
{
	setbit(DDRA,1,0);
	setbit(PORTA,1,1);
}

int button_door_2_is_pressed()
{
	if (getbit(PINA,1)) {return 0;}
	return 1;
}

void button_door_3_enable()
{
	setbit(DDRA,2,0);
	setbit(PORTA,2,1);
}

int button_door_3_is_pressed()
{
	if (getbit(PINA,2)) {return 0;}
	return 1;
}

void button_door_4_enable()
{
	setbit(DDRA,3,0);
	setbit(PORTA,3,1);
}

int button_door_4_is_pressed()
{
	if (getbit(PINA,3)) {return 0;}
	return 1;
}