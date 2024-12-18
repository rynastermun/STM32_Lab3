/*
 * button.h
 *
 *  Created on: Nov 23, 2024
 *      Author: ADMIN PC
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "main.h"

//THIẾT LẬP TRẠNG THÁI NHẤN
#define NORMAL_STATE GPIO_PIN_SET
#define PRESSED_STATE GPIO_PIN_RESET
#define LONG_PRESS 200

//SỐ LƯỢNG NÚT VÀ NHÃN CÁC NÚT
#define NUM_OF_BUTTON 3
#define Select 0
#define Duration 1
#define Set 2

void initialButton();
int isSelectPressed();
int isDurationPressed();
int isSetPressed();
void getKeyInput();

#endif /* INC_BUTTON_H_ */
