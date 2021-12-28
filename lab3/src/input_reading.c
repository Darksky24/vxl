/*
 * input_reading.c
 *
 *  Created on: Oct 6, 2021
 *      Author: ACER
 */
# include "main.h"
# define DURATION_FOR_AUTO_INCREASING 20
# define DURATION_FOR_AUTO_DECREASING 10

# define BUTTON_IS_PRESSED GPIO_PIN_RESET
# define BUTTON_IS_RELEASED GPIO_PIN_SET


static uint8_t counterFor1s = 100;
static uint8_t counterFor500ms = 50;
static uint8_t blinkCounter500ms=50;
static uint8_t flagForButtonPress200ms [NO_OF_BUTTONS];
static uint8_t flagForButtonRelease [NO_OF_BUTTONS];


void button_reading ( void )
{

	//the buffer that the final result is stored after debouncing
	static GPIO_PinState buttonBuffer[NO_OF_BUTTONS];
	// we define two buffers for debouncing
	static GPIO_PinState debounceButtonBuffer1[NO_OF_BUTTONS];
	static GPIO_PinState debounceButtonBuffer2[NO_OF_BUTTONS];

	static int counterForButtonPress200ms[3]={0};
	static int counterForButtonRelease100ms[3]={0};
	////////////////////INPUT_READING////////////////////////////
	for ( uint8_t i = 0; i < NO_OF_BUTTONS ; i ++)
	{
		debounceButtonBuffer2[i] = debounceButtonBuffer1[i];
		//traverse all button to read input signal
		switch (i) {
			case 0:
				debounceButtonBuffer1[i] = HAL_GPIO_ReadPin (BUTTON_1_GPIO_Port , BUTTON_1_Pin ) ;
				break;
			case 1:
				debounceButtonBuffer1[i] = HAL_GPIO_ReadPin (BUTTON_2_GPIO_Port, BUTTON_2_Pin ) ;
				break;
			case 2:
				debounceButtonBuffer1[i] = HAL_GPIO_ReadPin (BUTTON_3_GPIO_Port, BUTTON_3_Pin ) ;
				break;
		}

		if( debounceButtonBuffer1[i] == debounceButtonBuffer2 [i]) buttonBuffer[i] = debounceButtonBuffer1[i];

		if( buttonBuffer[i] == BUTTON_IS_PRESSED )
		{
			// if a button is pressed , we start counting
			flagForButtonRelease[i]=0;
			if( counterForButtonPress200ms[i] < DURATION_FOR_AUTO_INCREASING ) counterForButtonPress200ms[i]++;
			else flagForButtonPress200ms[i]=1;
			//buttonState[i]=BUTTON_PRESSED_MORE_THAN_200ms;
		}
		else	//RELEASE_STATE
		{
			counterForButtonPress200ms[i] = 0;
			if( counterForButtonRelease100ms[i] < DURATION_FOR_AUTO_DECREASING ) counterForButtonRelease100ms[i]++;
			else
			{
				//buttonState[i]=BUTTON_RELEASED;
				counterForButtonRelease100ms[i]=0;
				flagForButtonPress200ms[i]=0;
				flagForButtonRelease[i]=1;
			}
		}

	}
	if(mode==MODE_1) counterFor1s--;
	else{
		if(blinkCounter500ms>=0)blinkCounter500ms--;
	}

	if(flagForButtonPress200ms[1]==1 && mode != MODE_1){
			if(counterFor500ms>=0)counterFor500ms--;
	}
}
unsigned char is_counterFor500ms_equal_0 () {
	if(counterFor500ms<=0){
		counterFor500ms=50;
		return 1;
	}
	else return 0;
}

unsigned char is_blinkCounter500ms_equal_0 () {
	if(blinkCounter500ms<=0){
		blinkCounter500ms=50;
		return 1;
	}
	else return 0;
}

unsigned char is_counterFor1s_equal_0 () {
	if(counterFor1s <= 0){
		counterFor1s=100;
		return 1;
	}
	else return 0;
}


unsigned char is_button_released ( uint8_t index ) {
   if( index >= NO_OF_BUTTONS ) return 0;
   if(flagForButtonRelease[index] ==1 )return 1;
   else return 0;
}


unsigned char is_button_pressed_200ms ( unsigned char index ) {
	if( index >= NO_OF_BUTTONS ) return 0xff ;
	if(flagForButtonPress200ms[index] ==1 )return 1;
	else return 0;
}

