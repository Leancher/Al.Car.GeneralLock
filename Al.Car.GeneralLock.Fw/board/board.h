#ifndef BOARD_H_
#define BOARD_H_

#include <avr/io.h>
#include "../refs/bwl_adc.h"

#define ADC_VOLT_MULTIPLIER_MV		(68+2)/2 * 1.1
typedef unsigned char byte;

void unused_pin_init();
void adc_init_voltage_acc();
void button_stop_enable();
byte button_stop_is_pressed();
void door_terminal_enable();
byte door_teminal_is_pressed();
void relay_siren_set_state(byte state);
void door_switch_enable();
byte door_switch_is_pressed();
void button_trunk_enable();
byte button_trunk_is_pressed();
void keychain_open_enable();
byte keychain_open_is_pressed();
void keychain_close_enable();
byte keychain_close_is_pressed();
void board_led_set_state(byte state);
void trunk_actuator_set_state(byte state);
void indicator_set_state(byte state);
void driver_locker_1_set_state(byte state);
void driver_locker_2_set_state(byte state);
void driver_door_handle_enable(byte state);
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