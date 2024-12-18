/*
 * button.c
 *
 *  Created on: Nov 21, 2024
 *      Author: ADMIN PC
 */

#include "button.h"

int KeyReg[NUM_OF_BUTTON][4]; // Mảng lưu trạng thái của 3 nút, mỗi nút có 3 trạng thái
int ButtonFlag[NUM_OF_BUTTON] = {0, 0, 0}; // Cờ trạng thái cho 3 nút
int buttonPressDuration = 0; //Biến kiểm tra nhấn giữ
int ButtonHoldFlag[NUM_OF_BUTTON]; //Đánh giấu trạng thái nhấn giữ

void initialButton(){
	//KHỞI TẠO CỜ VÀ TRẠNG THÁI CÁC NÚT
	for (int i = 0; i < NUM_OF_BUTTON; i++) {
	        ButtonFlag[i] = 0;
	        for (int j = 0; j < 3; j++) {
	            KeyReg[i][j] = NORMAL_STATE;
	        }
	    }
}

//KIỂM TRA NÚT Select NẾU ĐƯỢC NHẤN
int isSelectPressed() {
    if (ButtonFlag[Select] == 1) {
        ButtonFlag[Select] = 0;
        return 1;
    }
    return 0;
}

//KIỂM TRA NÚT Duration NẾU ĐƯỢC NHẤN
int isDurationPressed() {
    if (ButtonFlag[Duration] == 1) {
        ButtonFlag[Duration] = 0;
        return 1;
    }
    return 0;
}

//KIỂM TRA NÚT Set NẾU ĐƯỢC NHẤN
int isSetPressed() {
    if (ButtonFlag[Set] == 1) {
        ButtonFlag[Set] = 0;
        return 1;
    }
    return 0;
}

//ĐỌC TRẠNG THÁI NÚT VÀ XỬ LÝ DEBOUNCE
void getKeyInput() {
    for (int i = 0; i < NUM_OF_BUTTON; i++) {
        KeyReg[i][0] = KeyReg[i][1];
        KeyReg[i][1] = KeyReg[i][2];

        // Đọc tín hiệu của các nút (thay thế với hàm đọc GPIO thực tế)
        if (i == Select) KeyReg[i][2] = HAL_GPIO_ReadPin(Select_GPIO_Port, Select_Pin);
        else if (i == Duration) KeyReg[i][2] = HAL_GPIO_ReadPin(Duration_GPIO_Port, Duration_Pin);
        else if (i == Set) KeyReg[i][2] = HAL_GPIO_ReadPin(Set_GPIO_Port, Set_Pin);

        // Kiểm tra nếu trạng thái của nút ổn định
        if ((KeyReg[i][0] == KeyReg[i][1]) && (KeyReg[i][1] == KeyReg[i][2])) {
            if (KeyReg[i][3] != KeyReg[i][2]) { // Kiểm tra nhấn thả
                KeyReg[i][3] = KeyReg[i][2]; // Cập nhật trạng thái cũ

                if (KeyReg[i][2] == PRESSED_STATE) {
                    ButtonFlag[i] = 1; // Đánh dấu nút được nhấn
                    ButtonHoldFlag[i] = 0; //Reset trạng thái nhấn giữ
                    buttonPressDuration = 0; // Reset thời gian nhấn giữ khi nhấn lần đầu
                }
            }
            else { // Nếu nút không thay đổi (nhấn giữ)
            	if (KeyReg[i][2] == PRESSED_STATE) {
            		buttonPressDuration++; // Tăng thời gian nhấn giữ

            		if (buttonPressDuration >= LONG_PRESS) { // Kiểm tra nếu thời gian nhấn giữ đã đạt LONG_PRESS
            			ButtonHoldFlag[i] = 1;//Đánh giấu trạng thái nhấn giữ
            			buttonPressDuration = 0;//Reset bộ đếm
            		}
                }
            }
        }
    }
}
