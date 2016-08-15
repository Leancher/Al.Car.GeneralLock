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

void set_state_indicator(byte _state)
{
	setbit(DDRD,6,1);
	setbit(PORTD,6,_state);
}

void trunk_actuator_set()
{
	setbit(DDRA,7,1);
	setbit(PORTA,7,1);
}

void trunk_actuator_reset()
{
	setbit(DDRA,7,1);
	setbit(PORTA,7,0);	
}

//Включить драйверы
void drivers_turn_on()
{
	setbit(DDRA,4,1);
	setbit(PORTA,4,1);	
}

//Выключить драйверы
void drivers_turn_off()
{
	setbit(DDRA,4,1);
	setbit(PORTA,4,0);	
}

//Активация драйвера 1
void driver_1_enable()
{
	setbit(DDRA,5,1);
	setbit(PORTA,5,1);
}

//Деактивация драйвера 1
void driver_1_disable()
{
	setbit(DDRA,5,1);
	setbit(PORTA,5,0);
}

//Активация драйвера 2
void driver_2_enable()
{
	setbit(DDRA,6,1);
	setbit(PORTA,6,1);
}

//Деактивация драйвера 2
void driver_2_disable()
{
	setbit(DDRA,6,1);
	setbit(PORTA,6,0);
}

void set_driver_in_1()
{
	setbit(PORTC,0,1);
	setbit(PORTC,0,1);
}

void reset_driver_in_1()
{
	setbit(PORTC,0,1);
	setbit(PORTC,0,0);
}

void set_driver_in_2()
{
	setbit(PORTC,1,1);
	setbit(PORTC,1,1);
}

void reset_driver_in_2()
{
	setbit(PORTC,1,1);
	setbit(PORTC,1,0);
}

void set_driver_in_3()
{
	setbit(PORTC,6,1);
	setbit(PORTC,6,1);
}

void reset_driver_in_3()
{
	setbit(PORTC,6,1);
	setbit(PORTC,6,0);
}

void set_driver_in_4()
{
	setbit(PORTC,7,1);
	setbit(PORTC,7,1);
}

void reset_driver_in_4()
{
	setbit(PORTC,7,1);
	setbit(PORTC,7,0);
}
