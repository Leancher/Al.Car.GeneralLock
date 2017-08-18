/*
* Al.Car.GeneralLock
*
* Created: 25.04.2015 11:16:48
*  Author: Андрей
*/

#include <avr/io.h>

# define F_CPU 1000000UL//4000000UL
#include <avr/power.h>
#include <util/delay.h>
#include <avr/wdt.h>

#include "board/board.h"

#define ACTUATOR_HOLD 300
#define SIREN_BEEP_DURATION 100

int car_driver_presence=0;
int state_doors=1;
typedef unsigned char byte;

int get_voltage()
{
	int val=0;
	val=adc_read_average(3)*ADC_VOLT_MULTIPLIER_MV;//+DIODE_CORRECTION;
	return val;
}

void drivers_disable()
{
	driver_in_1_set_state(0);
	driver_in_2_set_state(0);
	driver_in_3_set_state(0);
	driver_in_4_set_state(0);
	_delay_ms(1);	
}

void door_1_unlock()
{
	driver_in_1_set_state(1);
	_delay_ms(1);
	driver_in_2_set_state(0);
	_delay_ms(ACTUATOR_HOLD);	
}

void door_1_lock()
{
	driver_in_1_set_state(0);
	_delay_ms(1);
	driver_in_2_set_state(1);
	_delay_ms(ACTUATOR_HOLD);
}

void door_2_unlock()
{
	driver_in_3_set_state(1);
	_delay_ms(1);
	driver_in_4_set_state(0);
	_delay_ms(ACTUATOR_HOLD);
}

void door_2_lock()
{
	driver_in_3_set_state(0);
	_delay_ms(1);
	driver_in_4_set_state(1);
	_delay_ms(ACTUATOR_HOLD);
}

void door_3_unlock()
{
	driver_in_1_set_state(1);
	_delay_ms(1);
	driver_in_2_set_state(0);
	_delay_ms(ACTUATOR_HOLD);
}

void door_3_lock()
{
	driver_in_1_set_state(0);
	_delay_ms(1);
	driver_in_2_set_state(1);
	_delay_ms(ACTUATOR_HOLD);
}

void door_4_unlock()
{
	driver_in_3_set_state(1);
	_delay_ms(1);
	driver_in_4_set_state(0);
	_delay_ms(ACTUATOR_HOLD);
}

void door_4_lock()
{
	driver_in_3_set_state(0);
	_delay_ms(1);
	driver_in_4_set_state(1);
	_delay_ms(ACTUATOR_HOLD);
}



void set_state_door(byte state)
{
	if (state==1)
	{
		driver_locker_1_set_state(1);
		_delay_ms(1);
		door_1_unlock();
		drivers_disable();
		door_2_unlock();
		drivers_disable();
		driver_locker_1_set_state(0);

		driver_locker_2_set_state(1);
		_delay_ms(1);
		door_3_unlock();
		drivers_disable();
		door_4_unlock();
	}
	else
	{
		driver_locker_1_set_state(1);
		_delay_ms(1);		
		door_1_lock();
		drivers_disable();
		door_2_lock();
		drivers_disable();
		driver_locker_1_set_state(0);

		driver_locker_2_set_state(1);
		_delay_ms(1);
		door_3_lock();
		drivers_disable();
		door_4_lock();
	}
	drivers_disable();
	driver_locker_2_set_state(0);
}

void unlock_trunk()
{
	if (state_doors==1)
	{
		trunk_actuator_set_state(1);
		_delay_ms(500);
		trunk_actuator_set_state(0);
	}
}

void change_state_indicator()
{
	if (state_doors==1)
	{
		indicator_set_state(1);
		board_led_set_state(1);
	}
	else
	{
		indicator_set_state(0);
		board_led_set_state(0);
	}
}

void change_state_device()
{
	//Уставновка состояния замков на противоположное от значения текущего состояния
	if (state_doors==1) set_state_door(0);
	if (state_doors==0) set_state_door(1);
	//Переключаем текущее состояние
	if (state_doors==1)
	{
		state_doors=0;
	}
	else
	{
		state_doors=1;
		car_driver_presence=0;
	}
}

void siren_beep(int count)
{
	for (int index=0;index<count;index++)
	{
		relay_siren_set_state(1);
		_delay_ms(SIREN_BEEP_DURATION);
		relay_siren_set_state(0);
		_delay_ms(SIREN_BEEP_DURATION);
	}
}

void unlock_doors()
{
	siren_beep(2);
	set_state_door(1);
	state_doors=1;
}

void lock_doors()
{
	siren_beep(1);
	set_state_door(0);
	state_doors=0;
}

void check_car_driver_presence()
{
	static int index=0;
	static int stop_hold=0;
	//Выполняется, если двигатель заведен
	if (get_voltage()>8000)
	{
		if (door_is_open()==1) //Двери открыты (разблокированы вручную)
		{
			car_driver_presence=0;
			state_doors=1; //Уставливаем состояние
			if (pedal_stop_is_pressed()==1) stop_hold=1; //Фиксируем удержание педали
			return; //Если двери открыты, ничего не делаем
		}
		
		if (state_doors==0)//Если двери закрыты, то выходим из функции
		{
			//Педаль нажата до открытия дверей, фиксируем состояние, чтобы двери не заблокирвоались сразу после 
			if (pedal_stop_is_pressed()==1) stop_hold=1;
			return; //Ничего не делаем
		}		
		//Кнопкой разблокировали двери (состояние 1)
		//Педаль отпустили, сбросить состояние
		if (pedal_stop_is_pressed()==0) stop_hold=0;
		//Педаль все еще удерживается, выходим, чтобы не заблокирваоть дверь раньше
		if (stop_hold==1) return;

		if (car_driver_presence==0)
		{
			if (pedal_stop_is_pressed()==1)
			{
				//Задержка перед блокировкой дверей
				if (index<20) 
				{
					index++;
					return;
				}
				index=0;
				car_driver_presence=1;
				set_state_door(0);
				state_doors=0;
			}
		}
	}
	else
	{
		//Двери уже разблокирвоаны, сбрасываем состояние
		if (state_doors==1) car_driver_presence=0;

		if (car_driver_presence==1)
		{
			set_state_door(1);
			state_doors=1;			
		}
	}
}

void button_enable()
{
	door_switch_enable();
	button_trunk_enable();
	keychain_close_enable();
	keychain_open_enable();
	button_stop_enable();
	door_sensor_enable();
	door_switch_enable();
}

void board_init()
{
	//Отключение неиспользуемых функций
	//PRR0=(1<<PRTWI)||(1<<PRTIM2)||(1<<PRTIM0)||(1<<PRUSART1)||(1<<PRTIM1)||(1<<PRSPI)||(1<<PRUSART0)||(1<<PRADC);
	//unused_pin_init();	
	drivers_disable();
	button_enable();
	//Инициализация выходов для актуатора двери багажника
	trunk_actuator_set_state(0);
	//При включении устройства открыть все двери
	set_state_door(1);
	adc_init_voltage_acc();
	//Задержка для инициализации радиобрелка
	_delay_ms(1200);	
}

int main ()
{
	wdt_enable(WDTO_8S);
	board_init();
	while (1)
	{
		wdt_reset();
 		if (button_trunk_is_pressed()==1) unlock_trunk();
 		if (door_switch_is_pressed()==1) change_state_device();
 		if (keychain_close_is_pressed()==1) lock_doors();
 		if (keychain_open_is_pressed()==1) unlock_doors();
		check_car_driver_presence();
 		change_state_indicator();
		
		_delay_ms(50);
	}
}