/*
* Al.Car.GeneralLock
*
* Created: 25.04.2015 11:16:48
*  Author: Андрей
*/

#include <avr/io.h>

# define F_CPU 16000UL//4000000UL
#include <avr/power.h>
#include <util/delay.h>
#include <avr/wdt.h>

#include "board/board.h"

// D2/PD2 - Indicator
// D3/PD3 - Trunk button - Button 1
// D4/PD4 - Door button -  Button 2
// D5/PD5 - Alarm open  -  Button 3
// D6/PD6 - Alarm close  - button 4
// D7/PD7 - L298-1-In3
// D8/PB0 - L298-1-In4
// D9/PB1 - L298-1-In2
// D10/PB2 - L298-1-In1
// A5/PC5 - L293-In1
// A4/PC4 - Door switch button - Button 5
// A3/PC3 - L298-2-In4
// A2/PC2 - L298-2-In3
// A1/PC1 - L298-2-In1
// A0/PC0 - L298-2-In2

int _current_state_device=1;
#define ACTUATOR_HOLD 500
typedef unsigned char byte;

int get_state_door_switch()
{
	door_switch_enable();
	_delay_ms(1);
	return is_door_switch_pressed();
}

int get_state_trunk_button()
{
	trunk_button_enable();
	_delay_ms(1);
	return is_trunk_button_pressed();
}

int get_state_alarm_open()
{
	alarm_open_enable();
	_delay_ms(1);
	return is_alarm_open_pressed();
}

int get_state_alarm_close()
{
	alarm_close_enable();
	_delay_ms(1);
	return is_alarm_close_pressed();
}

void button_enable()
{
	door_switch_enable();
	trunk_button_enable();
	alarm_close_enable();
	alarm_open_enable();
}

void drivers_disable()
{
	drivers_turn_off();
		
	driver_1_disable();
	driver_2_disable();	
	
	reset_driver_in_1();
	reset_driver_in_2();
	reset_driver_in_3();
	reset_driver_in_4();
	_delay_ms(1);	
}

void actuator_1_set_state_1()
{
	drivers_turn_on();
	_delay_ms(1);	
	driver_1_enable();
	_delay_ms(1);	
	set_driver_in_1();
	_delay_ms(1);
	reset_driver_in_2();
	_delay_ms(ACTUATOR_HOLD);
	drivers_disable();	
}

void actuator_1_set_state_0()
{
	drivers_turn_on();
	_delay_ms(1);
	driver_1_enable();
	_delay_ms(1);
	reset_driver_in_1();
	_delay_ms(1);
	set_driver_in_2();
	_delay_ms(ACTUATOR_HOLD);
	drivers_disable();
}

void actuator_2_set_state_1()
{
	drivers_turn_on();
	_delay_ms(1);
	driver_1_enable();
	_delay_ms(1);
	set_driver_in_3();
	_delay_ms(1);
	reset_driver_in_4();
	_delay_ms(ACTUATOR_HOLD);
	drivers_disable();
}

void actuator_2_set_state_0()
{
	drivers_turn_on();
	_delay_ms(1);
	driver_1_enable();
	_delay_ms(1);
	reset_driver_in_3();
	_delay_ms(1);
	set_driver_in_4();
	_delay_ms(ACTUATOR_HOLD);
	drivers_disable();
}

void actuator_3_set_state_1()
{
	drivers_turn_on();
	_delay_ms(1);
	driver_2_enable();
	_delay_ms(1);
	set_driver_in_1();
	_delay_ms(1);
	reset_driver_in_2();
	_delay_ms(ACTUATOR_HOLD);
	drivers_disable();
}

void actuator_3_set_state_0()
{
	drivers_turn_on();
	_delay_ms(1);
	driver_2_enable();
	_delay_ms(1);
	reset_driver_in_1();
	_delay_ms(1);
	set_driver_in_2();
	_delay_ms(ACTUATOR_HOLD);
	drivers_disable();
}

void actuator_4_set_state_1()
{
	drivers_turn_on();
	_delay_ms(1);
	driver_2_enable();
	_delay_ms(1);
	set_driver_in_3();
	_delay_ms(1);
	reset_driver_in_4();
	_delay_ms(ACTUATOR_HOLD);
	drivers_disable();
}

void actuator_4_set_state_0()
{
	drivers_turn_on();
	_delay_ms(1);
	driver_2_enable();
	_delay_ms(1);
	reset_driver_in_3();
	_delay_ms(1);
	set_driver_in_4();
	_delay_ms(ACTUATOR_HOLD);
	drivers_disable();
}

void change_state_indicator()
{
	if (_current_state_device==1)
	{
		set_state_indicator(1);
	}
	else
	{
		set_state_indicator(0);
	}
}

void set_state_door(byte _state)
{
	if (_state==1)
	{
		actuator_1_set_state_1();
		actuator_2_set_state_1();
		actuator_3_set_state_1();
		actuator_4_set_state_1();
	}
	else
	{
		actuator_1_set_state_0();
		actuator_2_set_state_0();
		actuator_3_set_state_0();
		actuator_4_set_state_0();
	}
}

void unlock_trunk()
{
	if (_current_state_device==1)
	{
		trunk_actuator_set();
		_delay_ms(500);
		trunk_actuator_reset();
	}
	return;
}

void change_state_device()
{
	//Уставновка состояния замков на противоположное от значения текущего состояния
	if (_current_state_device==1) set_state_door(0);
	if (_current_state_device==0) set_state_door(1);
	//Переключаем текущее состояние
	if (_current_state_device==1)
	{
		_current_state_device=0;
	}
	else
	{
		_current_state_device=1;
	}
}

void car_alarm_deactivated()
{
	set_state_door(1);
	_current_state_device=1;
	return;
}

void car_alarm_activated()
{
	set_state_door(0);
	_current_state_device=2;
	return;
}

int main ()
{
	//Отключение неиспользуемых функций
	PRR0=(1<<PRTWI)||(1<<PRTIM2)||(1<<PRTIM0)||(1<<PRUSART1)||(1<<PRTIM1)||(1<<PRSPI)||(1<<PRUSART0)||(1<<PRADC);
	unused_pin_init();
	
	wdt_enable(WDTO_8S);
	
	drivers_disable();
	
	button_enable();
	
	//Инициализация выходов для актуатора двери багажника
	trunk_actuator_reset();
	//При включении устройства открыть все двери
	set_state_door(1);
	
	while (1)
	{
		//currentStateDevice=0 - lock all doors
		//currentStateDevice=1 - unlock all doors
		//currentStateDevice=2 - car alarm actived
	
		wdt_reset();
		
		
		if (get_state_trunk_button()==1) unlock_trunk();
		if (get_state_door_switch()==1) change_state_device();
		if (get_state_alarm_close()==1) car_alarm_activated();
		if (get_state_alarm_open()==1) car_alarm_deactivated();

		change_state_indicator();

		_delay_ms(50);
	}
}