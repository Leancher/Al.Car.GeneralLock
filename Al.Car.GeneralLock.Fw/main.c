/*
* Al.Car.GeneralLock
*
* Created: 25.04.2015 11:16:48
*  Author: Андрей
*/

#include <avr/io.h>

# define F_CPU 8000000UL//4000000UL
#include <avr/power.h>
#include <util/delay.h>
#include <avr/wdt.h>

#include "board/board.h"

int _current_state_device=1;
#define ACTUATOR_HOLD 300
typedef unsigned char byte;

int get_state_door_switch()
{
	door_switch_enable();
	_delay_ms(1);
	return door_switch_is_pressed();
}

int get_state_trunk_button()
{
	trunk_button_enable();
	_delay_ms(1);
	return trunk_button_is_pressed();
}

int get_state_alarm_open()
{
	rc_open_enable();
	_delay_ms(1);
	return rc_open_is_pressed();
}

int get_state_alarm_close()
{
	rc_close_enable();
	_delay_ms(1);
	return rc_close_is_pressed();
}

void button_enable()
{
	door_switch_enable();
	trunk_button_enable();
	rc_close_enable();
	rc_open_enable();
}

void drivers_disable()
{
	driver_in_1_set_state(0);
	driver_in_2_set_state(0);
	driver_in_3_set_state(0);
	driver_in_4_set_state(0);
	_delay_ms(1);	
}

void actuator_1_set_state_1()
{
	driver_in_1_set_state(1);
	_delay_ms(1);
	driver_in_2_set_state(0);
	_delay_ms(ACTUATOR_HOLD);	
}

void actuator_1_set_state_0()
{
	driver_in_1_set_state(0);
	_delay_ms(1);
	driver_in_2_set_state(1);
	_delay_ms(ACTUATOR_HOLD);
}

void actuator_2_set_state_1()
{
	driver_in_3_set_state(1);
	_delay_ms(1);
	driver_in_4_set_state(0);
	_delay_ms(ACTUATOR_HOLD);
}

void actuator_2_set_state_0()
{
	driver_in_3_set_state(0);
	_delay_ms(1);
	driver_in_4_set_state(1);
	_delay_ms(ACTUATOR_HOLD);
}

void actuator_3_set_state_1()
{
	driver_in_1_set_state(1);
	_delay_ms(1);
	driver_in_2_set_state(0);
	_delay_ms(ACTUATOR_HOLD);
}

void actuator_3_set_state_0()
{
	driver_in_1_set_state(0);
	_delay_ms(1);
	driver_in_2_set_state(1);
	_delay_ms(ACTUATOR_HOLD);
}

void actuator_4_set_state_1()
{
	driver_in_3_set_state(1);
	_delay_ms(1);
	driver_in_4_set_state(0);
	_delay_ms(ACTUATOR_HOLD);
}

void actuator_4_set_state_0()
{
	driver_in_3_set_state(0);
	_delay_ms(1);
	driver_in_4_set_state(1);
	_delay_ms(ACTUATOR_HOLD);
}

void change_state_indicator()
{
	if (_current_state_device==1)
	{
		board_led_set_state(1);
	}
	else
	{
		board_led_set_state(0);
	}
}

void set_state_door(byte state)
{
	if (state==1)
	{
		driver_locker_1_set_state(1);
		_delay_ms(1);
		actuator_1_set_state_1();
		drivers_disable();
		actuator_2_set_state_1();
		drivers_disable();
		driver_locker_1_set_state(0);

		driver_locker_2_set_state(1);
		_delay_ms(1);
		actuator_3_set_state_1();
		drivers_disable();
		actuator_4_set_state_1();
		drivers_disable();
		driver_locker_2_set_state(0);
	}
	else
	{
		driver_locker_1_set_state(1);
		_delay_ms(1);		
		actuator_1_set_state_0();
		drivers_disable();
		actuator_2_set_state_0();
		drivers_disable();
		driver_locker_1_set_state(0);

		driver_locker_2_set_state(1);
		_delay_ms(1);
		actuator_3_set_state_0();
		drivers_disable();
		actuator_4_set_state_0();
		drivers_disable();
		driver_locker_2_set_state(0);
	}
	drivers_disable();
}

void unlock_trunk()
{
	if (_current_state_device==1)
	{
		trunk_actuator_set_state(1);
		_delay_ms(500);
		trunk_actuator_set_state(0);
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
	_current_state_device=0;
	return;
}

int main ()
{
	//Отключение неиспользуемых функций
	//PRR0=(1<<PRTWI)||(1<<PRTIM2)||(1<<PRTIM0)||(1<<PRUSART1)||(1<<PRTIM1)||(1<<PRSPI)||(1<<PRUSART0)||(1<<PRADC);
//	unused_pin_init();
	
	wdt_enable(WDTO_8S);
	
	drivers_disable();
	
	button_enable();
	
	//Инициализация выходов для актуатора двери багажника
	//trunk_actuator_set_state(0);
	//При включении устройства открыть все двери
	//set_state_door(1);
	
// 	driver_locker_1_set_state(1);
// 	driver_in_1_set_state(0);
// 	_delay_ms(500);
// 	driver_in_1_set_state(1);
// 	driver_locker_1_set_state(0);

	while (1)
	{
		//currentStateDevice=0 - lock all doors
		//currentStateDevice=1 - unlock all doors
		//currentStateDevice=2 - car alarm actived
	
		wdt_reset();
		
		
// 		if (get_state_trunk_button()==1) unlock_trunk();
 		if (get_state_door_switch()==1) change_state_device();
// 		if (get_state_alarm_close()==1) car_alarm_activated();
// 		if (get_state_alarm_open()==1) car_alarm_deactivated();
// 
 		change_state_indicator();

		_delay_ms(50);
	}
}