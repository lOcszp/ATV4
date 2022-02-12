/*
 * hw.c
 *
 *  Created on: Feb 10, 2022
 *      Author: lukaz
 */

#include <stdint.h>
#include <stdbool.h>
#include "main.h"
#include "app.h"
#include "hw.h"

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	bool switch_port;
	if(GPIO_Pin == USER_SW0_Pin){
		switch_port = 0;
		app_switch_interrupt(switch_port);
	}
	if(GPIO_Pin == USER_SW1_Pin){
		switch_port = 1;
		app_switch_interrupt(switch_port);
	}
}

bool hw_switch0_state_get(void)
{
	GPIO_PinState switch0_state = HAL_GPIO_ReadPin(USER_SW0_GPIO_Port, USER_SW0_Pin);
	if (switch0_state == GPIO_PIN_SET){
		return true;
	}
	else{
		return false;
	}
}

bool hw_switch1_state_get(void)
{
	GPIO_PinState switch1_state = HAL_GPIO_ReadPin(USER_SW1_GPIO_Port, USER_SW1_Pin);
	if (switch1_state == GPIO_PIN_SET){
		return true;
	}
	else{
		return false;
	}
}

void hw_led_toggle(void)
{

	HAL_GPIO_TogglePin(USER_LED_GPIO_Port, USER_LED_Pin);

}


void hw_led_state_set (bool state)
{
	GPIO_PinState led_status = state ? GPIO_PIN_RESET : GPIO_PIN_SET;
	HAL_GPIO_WritePin(USER_LED_GPIO_Port, USER_LED_Pin, led_status);

}

void hw_delay_ms (uint32_t time_ms)
{
	HAL_Delay(time_ms);
}

uint32_t hw_tick_ms_get(void)
{
	return HAL_GetTick();
}

void hw_cpu_sleep(void)
{
	__WFI();
}

