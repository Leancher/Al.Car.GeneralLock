#include "board.h"

#define getbit(port, bit)		((port) &   (1 << (bit)))
#define setbit(port,bit,val)	{if ((val)) {(port)|= (1 << (bit));} else {(port) &= ~(1 << (bit));}}

//Инициализация неиспользуемых выводов для экономии энергии
void unused_pin_init()
{
	setbit(DDRA,0,0);
	setbit(PORTA,0,1);
	setbit(DDRA,1,0);
	setbit(PORTA,1,1);	
	setbit(DDRA,2,0);
	setbit(PORTA,2,1);
	setbit(DDRA,3,0);
	setbit(PORTA,3,1);	
	
	setbit(DDRB,0,0);
	setbit(PORTB,0,1);	
	setbit(DDRB,1,0);
	setbit(PORTB,1,1);
	setbit(DDRB,2,0);
	setbit(PORTB,2,1);	
	setbit(DDRB,3,0);
	setbit(PORTB,3,1);	
	setbit(DDRB,4,0);
	setbit(PORTB,4,1);
	setbit(DDRB,5,1);
	setbit(PORTB,5,0);
	setbit(DDRB,6,1);
	setbit(PORTB,6,0);
	setbit(DDRB,7,1);
	setbit(PORTB,7,0);	
	
	setbit(DDRD,0,0);
	setbit(PORTD,0,1);
	setbit(DDRD,1,0);
	setbit(PORTD,1,1);
	setbit(DDRD,7,1);
	setbit(PORTD,7,0);
}

//Установка вывода как входа
void door_switch_enable()
{
	setbit(DDRD,4,0);
	setbit(PORTD,4,1);
}

//Получение нажатия кнопки
int is_door_switch_pressed()
{
	if (getbit(PIND,4)) {return 0;}
	return 1;	
}

//Установка вывода как входа
//Кнопка открытия багажника
void trunk_button_enable()
{
	setbit(DDRD,5,0);
	setbit(PORTD,5,1);	
}

//Получение нажатия кнопки
int is_trunk_button_pressed()
{
	if (getbit(PIND,5)) {return 0;}
	return 1;
}

void alarm_open_enable()
{
	setbit(DDRD,2,0);
	setbit(PORTD,2,1);	
}

int is_alarm_open_pressed()
{
	if (getbit(PIND,2)) {return 0;}
	return 1;
}

void alarm_close_enable()
{
	setbit(DDRD,3,0);
	setbit(PORTD,3,1);	
}

int is_alarm_close_pressed()
{
	if (getbit(PIND,3)) {return 0;}
	return 1;
}

void indicator_set_state(byte state)
{
	setbit(DDRD,6,1);
	setbit(PORTD,6,state);
}

void trunk_actuator_set_state(byte state)
{
	setbit(DDRA,7,1);
	setbit(PORTA,7,state);
}

//Включить драйверы
void relay_drivers_set_state(byte state)
{
	setbit(DDRA,4,1);
	setbit(PORTA,4,state);	
}

void driver_1_set_state(byte state)
{
	setbit(DDRA,5,1);
	setbit(PORTA,5,state);
}

void driver_2_set_state(byte state)
{
	setbit(DDRA,6,1);
	setbit(PORTA,6,state);
}

void driver_in_1_set_state(byte state)
{
	setbit(PORTC,0,1);
	setbit(PORTC,0,state);
}

void driver_in_2_set_state(byte state)
{
	setbit(PORTC,1,1);
	setbit(PORTC,1,state);
}

void driver_in_3_set_state(byte state)
{
	setbit(PORTC,6,1);
	setbit(PORTC,6,state);
}

void driver_in_4_set_state(byte state)
{
	setbit(PORTC,7,1);
	setbit(PORTC,7,state);
}
