/*
 * led_display.c
 *
 *  Created on: Oct 6, 2021
 *      Author: ACER
 */
#include "main.h"
# define ON 		GPIO_PIN_RESET
# define OFF 	    GPIO_PIN_SET
void led_display(uint8_t MAX_RED_TIMER,uint8_t MAX_YELLOW_TIMER,uint8_t MAX_GREEN_TIMER,uint8_t total_value){
	////////////////////////////////HORIZONTAL///////////////////////////////////////////
	if(total_value >(MAX_GREEN_TIMER+MAX_YELLOW_TIMER)){
		HAL_GPIO_WritePin(H_RED_GPIO_Port, H_RED_PIN, ON);
		HAL_GPIO_WritePin(H_GREEN_GPIO_Port, H_GREEN_PIN, OFF);
		HAL_GPIO_WritePin(H_YELLOW_GPIO_Port, H_YELLOW_PIN, OFF);

	}
	else if(total_value >MAX_YELLOW_TIMER)
	{
		HAL_GPIO_WritePin(H_RED_GPIO_Port, H_RED_PIN, OFF);
		HAL_GPIO_WritePin(H_GREEN_GPIO_Port, H_GREEN_PIN, ON);
		HAL_GPIO_WritePin(H_YELLOW_GPIO_Port, H_YELLOW_PIN, OFF);
	}
	else if(total_value <=MAX_YELLOW_TIMER)
	{
		HAL_GPIO_WritePin(H_RED_GPIO_Port, H_RED_PIN, OFF);
		HAL_GPIO_WritePin(H_GREEN_GPIO_Port, H_GREEN_PIN, OFF);
		HAL_GPIO_WritePin(H_YELLOW_GPIO_Port, H_YELLOW_PIN, ON);
	}
	////////////////////////////////VERTICAL/////////////////////////////////////////////
	if(total_value >(MAX_RED_TIMER+MAX_YELLOW_TIMER)){
		HAL_GPIO_WritePin(V_RED_GPIO_Port, V_RED_PIN, OFF);
		HAL_GPIO_WritePin(V_GREEN_GPIO_Port, V_GREEN_PIN, ON);
		HAL_GPIO_WritePin(V_YELLOW_GPIO_Port, V_YELLOW_PIN, OFF);
	}
	else if(total_value >MAX_RED_TIMER)
	{
		HAL_GPIO_WritePin(V_RED_GPIO_Port, V_RED_PIN, OFF);
		HAL_GPIO_WritePin(V_GREEN_GPIO_Port, V_GREEN_PIN, OFF);
		HAL_GPIO_WritePin(V_YELLOW_GPIO_Port, V_YELLOW_PIN, ON);
	}
	else if(total_value <=MAX_RED_TIMER)
	{
		HAL_GPIO_WritePin(V_RED_GPIO_Port, V_RED_PIN, ON);
		HAL_GPIO_WritePin(V_GREEN_GPIO_Port, V_GREEN_PIN, OFF);
		HAL_GPIO_WritePin(V_YELLOW_GPIO_Port, V_YELLOW_PIN, OFF);
	}

}
