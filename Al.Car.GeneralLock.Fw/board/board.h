#ifndef BOARD_H_
#define BOARD_H_

#include <avr/io.h>

typedef unsigned char byte;

void unused_pin_init();

void door_switch_enable();
int is_door_switch_pressed();

void trunk_button_enable();
int is_trunk_button_pressed();

void alarm_open_enable();
int is_alarm_open_pressed();

void alarm_close_enable();
int is_alarm_close_pressed();

void set_state_indicator(byte _state);

void trunk_actuator_set();
void trunk_actuator_reset();

void drivers_turn_on();
void drivers_turn_off();

void driver_1_enable();
void driver_1_disable();

void driver_2_enable();
void driver_2_disable();

void set_driver_in_1();
void reset_driver_in_1();
void set_driver_in_2();
void reset_driver_in_2();
void set_driver_in_3();
void reset_driver_in_3();
void set_driver_in_3();
void reset_driver_in_3();
void set_driver_in_4();
void reset_driver_in_4();

#endif /* BOARD_H_ */