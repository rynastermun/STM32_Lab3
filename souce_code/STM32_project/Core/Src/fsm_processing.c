/*
 * fsm_processing.c
 *
 *  Created on: Nov 23, 2024
 *      Author: ADMIN PC
 */

#include "fsm_processing.h"

//STATE_INIT: Trạng thái ban đầu
//MODE1: Normal mode
//MODE2: Modify time duration for the red LEDs
//MODE3: Modify time duration for the amber LEDs
//MODE4: Modify time duration for the green LEDs
enum TypeOfMode{STATE_INIT, MODE1, MODE2, MODE3, MODE4};
enum TypeOfMode MODE = STATE_INIT;

//Biến status để lưu trạng thái đèn giao thông: 0(đỏ), 1(vàng), 2(xanh)
int status1 = 0;
int status2 = 2;

//Biến count để đếm ngược thời gian
int count1 = 0;
int count2 = 0;
int Index = 0;

//Biến thời gian hiển thị đèn giao thông
int redTime = 5;
int amberTime = 2;
int greenTime = 3;

//Biến đệm để lưu thời gian thay đổi khi nhấn Duration
int timeRedTemp;
int timeGreenTemp;
int timeAmberTemp;

void fsm_processing(){
	//Tăng Mode khi nút Mode được nhấn
	switch(MODE){
	case STATE_INIT:
		if (timer3_flag == 1){
			//Đọc trạng thái nút và xử lý debounce
			getKeyInput();
			setTimer3(10);
		}
		//Khi nhấn nút thì chuyển sang Mode 1
		if (isSelectPressed() == 1){
			MODE = MODE1;
			Index = 0;
			led_off(RED0);
			led_off(RED1);
			led_off(AMBER0);
			led_off(AMBER1);
			led_off(GREEN0);
			led_off(GREEN1);
			break;
		}
		//Hiển thị số 8 trên 4 led 7 đoạn
		valueSEG12 = 88;
		valueSEG34 = 88;

		//Hiển thị tất cả led
		if (timer1_flag == 1){
			if (Index > 3) Index = 0;
			update7SEG(Index++);
			setTimer1(500);
			blink_red();
			blink_amber();
			blink_green();
		}
		break;

	case MODE1:
		if (timer3_flag == 1){
			//Đọc trạng thái nút và xử lý debounce
			getKeyInput();
			setTimer3(10);
		}
		//Khi nhấn nút Mode thì chuyển sang Mode 2
		if (isSelectPressed() == 1){
			MODE = MODE2;
			timeRedTemp = redTime;
			led_off(RED0);
			led_off(RED1);
			Index = 0;
			break;
		}
		if(timer2_flag == 1){ //Led giao thông và cập nhật led 7 đoạn

			//Led trên dưới
			if(count1 == 0){
				if(status1 == 0){//Led đỏ
					led_on(RED0);
					led_off(AMBER0);
					led_off(GREEN0);
					status1 = 2;
					count1 = redTime;
				}
				else if(status1 == 1){//Led vàng
					led_off(RED0);
					led_on(AMBER0);
					led_off(GREEN0);
					status1 = 0;
					count1 = amberTime;
				}
				else if(status1 == 2){//Led xanh
					led_off(RED0);
					led_off(AMBER0);
					led_on(GREEN0);
					status1 = 1;
					count1 = greenTime;
				}
			}

			//Led trái phải
			if(count2 == 0){
				if(status2 == 0){//Led đỏ
					led_on(RED1);
					led_off(AMBER1);
					led_off(GREEN1);
					status2 = 2;
					count2 = redTime;
				}
				else if(status2 == 1){//Led vàng
					led_off(RED1);
					led_on(AMBER1);
					led_off(GREEN1);
					status2 = 0;
					count2 = amberTime;
				}
				else if(status2 == 2){//Led xanh
					led_off(RED1);
					led_off(AMBER1);
					led_on(GREEN1);
					status2 = 1;
					count2 = greenTime;
				}
			}
			count1--;
			count2--;
			valueSEG12 = count1;//Hiển thị đếm ngược led trên dưới
			valueSEG34 = count2;//Hiển thị đếm ngược led trái phải
			setTimer2(1000);
		}
		if(timer1_flag == 1){//Hiển thị led 7 đoạn
			if(Index > 3) Index = 0;
			update7SEG(Index++);
			setTimer1(200);
		}
		break;

	case MODE2:
		//Đọc trạng thái nút và xử lý debounce
		if(timer3_flag == 1){
			getKeyInput();
			setTimer3(10);
		}
		//Khi nhấn nút Mode thì chuyển sang Mode 3
		if(isSelectPressed() == 1){
			MODE = MODE3;
			timeAmberTemp = amberTime;
			Index = 0;
		}
		//Khi nhấn nút Duration sẽ cộng thời gian cho led đỏ
		if(isDurationPressed() == 1){
			timeRedTemp++;
			if(timeRedTemp >= 100) timeRedTemp = 1;
		}
		//Khi nhấn nút Set sẽ cài đặt giá trị thời gian đã chọn
		if(isSetPressed() == 1){
			redTime = timeRedTemp;
		}
		led_off(GREEN0);
		led_off(GREEN1);
		led_off(AMBER0);
		led_off(AMBER1);
		valueSEG12 = 2;
		valueSEG34 = timeRedTemp;
		if(timer1_flag == 1){//Hiển thị led 7 đoạn
			if(Index > 3) Index = 0;
			update7SEG(Index++);
			setTimer1(200);
			blink_red();
		}
		break;

	case MODE3:
		//Đọc trạng thái nút và xử lý debounce
		if(timer3_flag == 1){
			getKeyInput();
			setTimer3(10);
		}
		//Khi nhấn nút Mode thì chuyển sang Mode 4
		if(isSelectPressed() == 1){
			MODE = MODE4;
			timeGreenTemp = greenTime;
			Index = 0;
			break;
		}
		//Khi nhấn nút Duration sẽ cộng thời gian cho led vàng
		if(isDurationPressed() == 1){
			timeAmberTemp++;
			if(timeAmberTemp >= 100) timeAmberTemp = 1;
		}
		//Khi nhấn nút Set sẽ cài đặt giá trị thời gian đã chọn
		if(isSetPressed() == 1){
			amberTime = timeAmberTemp;
		}
		led_off(RED0);
		led_off(RED1);
		led_off(GREEN0);
		led_off(GREEN1);
		valueSEG12 = 3;
		valueSEG34 = timeAmberTemp;
		if(timer1_flag == 1){//Hiển thị led 7 đoạn
			if(Index > 3) Index = 0;
			update7SEG(Index++);
			setTimer1(200);
			blink_amber();
		}
		break;

	case MODE4:
		//Đọc trạng thái nút và xử lý debounce
		if(timer3_flag == 1){
			getKeyInput();
			setTimer3(10);
		}

		//Khi nhấn nút Select sẽ xảy ra 2 trường hợp
		if(isSelectPressed() == 1){
			//Nếu thời gian đèn đỏ bằng thời gian đèn xanh + thời gian đèn vàng sẽ trả về Normal Mode
			if(redTime == greenTime + amberTime){
				MODE = MODE1;
				Index = 0;
				led_off(RED0);
				led_off(RED1);
				led_off(AMBER0);
				led_off(AMBER1);
				led_off(GREEN0);
				led_off(GREEN1);
				break;
			}
			//Nếu không sẽ trả về Mode 2
			else{
				MODE = MODE2;
				timeRedTemp = redTime;
				led_off(RED0);
				led_off(RED1);
				Index = 0;
				break;
			}
		}
//		//Khi nhấn nút Select sẽ chuyển về STATE_INIT
//		if(isSelectPressed() == 1){
//			MODE = STATE_INIT;
//		}
		//Khi nhấn nút Duration sẽ cộng thời gian cho led xanh
		if(isDurationPressed() == 1){
			timeGreenTemp++;
			if(timeGreenTemp >= 100) timeGreenTemp = 1;
		}
		//Khi nhấn nút Set sẽ cài đặt đặt giá trị thời gian đã chọn
		if(isSetPressed() == 1){
			greenTime = timeGreenTemp;
		}
		led_off(RED0);
		led_off(RED1);
		led_off(AMBER0);
		led_off(AMBER1);
		valueSEG12 = 4;
		valueSEG34 = timeGreenTemp;
		if (timer1_flag == 1) // HIỂN THỊ LED 7 ĐOẠN
		{
			if (Index > 3) Index = 0;
			update7SEG(Index++);
			setTimer1(200);
			blink_green();
		}
		break;

	default:
		break;
	}
}
