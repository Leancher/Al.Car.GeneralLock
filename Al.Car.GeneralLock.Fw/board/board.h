#ifndef BOARD_H_
#define BOARD_H_

#include <avr/io.h>

typedef unsigned char byte;

void unused_pin_init();

void door_switch_enable();
int door_switch_is_pressed();

void trunk_button_enable();
int trunk_button_is_pressed();

void rc_open_enable();
int rc_open_is_pressed();

void rc_close_enable();
int rc_close_is_pressed();

void board_led_set_state(byte state);
void trunk_actuator_set_state(byte state);
void indicator_set_state(byte state);
void driver_locker_1_enable(byte state);
void driver_locker_2_enable(byte state);
void driver_door_handle_enable(byte state)

void driver_in_1_set_state(byte state);
void driver_in_2_set_state(byte state);
void driver_in_3_set_state(byte state);
void driver_in_4_set_state(byte state);

void button_door_1_enable();
int button_door_1_is_pressed();
void button_door_2_enable();
int button_door_2_is_pressed();
void button_door_3_enable();
int button_door_3_is_pressed();
void button_door_4_enable();
int button_door_4_is_pressed();
void door_terminal_enable();
int door_terminal_is_pressed();
void stop_terminal_enable();
int stop_terminal_is_pressed();

#endif /* BOARD_H_ */