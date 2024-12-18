/*
 * hardware.h
 *
 *  Created on: Nov 20, 2024
 *      Author: ADMIN PC
 */

#ifndef INC_LED_H_
#define INC_LED_H_

#include "main.h"

#define GREEN0	GPIO_PIN_1
#define AMBER0	GPIO_PIN_2
#define RED0	GPIO_PIN_3
#define GREEN1	GPIO_PIN_4
#define AMBER1	GPIO_PIN_5
#define RED1	GPIO_PIN_6

//hiển thị led 7 đoạn
void display7SEG(int num);
void update7SEG(int index);

extern int valueSEG12;//Biến lưu giá trị hiển thị led 7 đoạn ở led 1 và 2
extern int valueSEG34;//Biến lưu giá trị hiển thị led 7 đoạn ở led 3 và 4

//bật tắt đèn giao thông
void led_on(int pin);
void led_off(int pin);

//nhấp nháy đèn giao thông
void blink_red();
void blink_amber();
void blink_green();

#endif /* INC_LED_H_ */
