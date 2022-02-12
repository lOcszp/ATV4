/*
 * app.c
 *
 *  Created on: Feb 10, 2022
 *      Author: lukaz
 */

#include <stdint.h>
#include <stdbool.h>
#include "app.h"
#include "main.h"
#include "hw.h"

#define APP_DEBOUNCING_TIME_MS 50

volatile uint32_t led_time_on_ms = 100;
volatile uint32_t led_time_off_ms = 100;

bool app_started = false;

void app_switch_interrupt(bool switch_port)
{

	static uint32_t debouncing_time_ms = 0;
	static bool switch0_state = 0;
	static bool switch1_state = 0;

	if (!app_started)
		return;



	if((hw_tick_ms_get() - debouncing_time_ms) >= APP_DEBOUNCING_TIME_MS)
	{
		if (switch_port == 0) {
			if (switch0_state == 0) {
				switch0_state = 1;
			}
			else {
				switch0_state = 0;
			}
		}
		else {
			if (switch1_state == 0) {
				switch1_state = 1;
			}
			else {
				switch1_state = 0;
			}
		}


		if (switch0_state == 0 && switch1_state == 0)
		{
			led_time_on_ms = 100;
			led_time_off_ms = 100;
		}
		else if (switch0_state == 0 && switch1_state == 1)
		{
			led_time_on_ms = 300;
			led_time_off_ms = 150;
		}
		else if (switch0_state == 1 && switch1_state == 0)
		{
			led_time_on_ms = 600;
			led_time_off_ms = 300;
		}
		else if (switch0_state == 1 && switch1_state == 1)
		{
			led_time_on_ms = 900;
			led_time_off_ms = 450;

		}

		/*
		if(led_time_on_ms == 400){
			led_time_on_ms = 100;
			//led_time_off_ms = 500;

		}

		else{
			led_time_on_ms = 400;
			//led_time_off_ms = 100;

		}*/

		debouncing_time_ms = hw_tick_ms_get();

	}
}



void app_tick_1ms(void)
{
	static uint32_t led_time_cnt_ms = 0;
	static bool cont = 0;

	if (!app_started)
		return;

	led_time_cnt_ms++;
	if((cont == 0) && (led_time_cnt_ms >= led_time_on_ms))
	{
		led_time_cnt_ms = 0;
		hw_led_state_set(true);
		cont = 1;
	}
	else if((cont == 1) && (led_time_cnt_ms >= led_time_off_ms))
	{
		led_time_cnt_ms = 0;
		hw_led_state_set(false);
		cont = 0;

	}
}


void app_init(void)
{

	app_started = true;

}

void app_loop(void)
{

	hw_cpu_sleep();
}
