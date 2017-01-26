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

void indicator_set_state(byte state);

void trunk_actuator_set_state(byte state);

void relay_drivers_set_state(byte state);

void driver_1_set_state(byte state);

void driver_2_set_state(byte state);

void driver_in_1_set_state(byte state);
void driver_in_2_set_state(byte state);
void driver_in_3_set_state(byte state);
void driver_in_4_set_state(byte state);

#endif /* BOARD_H_ */