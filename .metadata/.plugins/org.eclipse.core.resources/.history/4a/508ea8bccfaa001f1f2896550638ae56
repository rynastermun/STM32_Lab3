/*
 * software_timer.c
 *
 *  Created on: Nov 23, 2024
 *      Author: ADMIN PC
 */
#include"software_timer.h"

#define TIMER_CYCLE 10

int timer1_counter = 0;
int timer1_flag = 0;

int timer2_counter = 0;
int timer2_flag = 0;

int timer3_counter = 0;
int timer3_flag = 0;

void setTimer1(int duration)
{
	timer1_counter = duration / TIMER_CYCLE;
	timer1_flag = 0;
}

void setTimer2(int duration)
{
	timer2_counter = duration / TIMER_CYCLE;
	timer2_flag = 0;
}

void setTimer3()
{
	timer3_counter = SCAN_DURATION / TIMER_CYCLE;
	timer3_flag = 0;
}

void timer1Run()
{
	if (timer1_counter > 0)
	{
		timer1_counter--;
		if (timer1_counter <= 0)
		{
			timer1_flag = 1;
		}

	}
}

void timer2Run()
{
	if (timer2_counter > 0)
	{
		timer2_counter--;
		if (timer2_counter <= 0)
		{
			timer2_flag = 1;
		}

	}
}

void timer3Run()
{
	if (timer3_counter > 0)
	{
		timer3_counter--;
		if (timer3_counter <= 0)
		{
			timer3_flag = 1;
		}

	}
}
