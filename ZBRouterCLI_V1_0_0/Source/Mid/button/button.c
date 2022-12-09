/*
 * button.c
 *
 *  Created on: Mar 23, 2022
 *      Author: Dung
 */
#include "app/framework/include/af.h"
#include "button.h"

uint8_t state_button0 = 0;
uint8_t state_button1 = 0;

buttonCallbackFunction btnCallbackFunc = NULL;

EmberEventControl		firstButtonStateChangeEventControl;
EmberEventControl		secondButtonStateChangeEventControl;

void firstButtonStateChangeEventControlHandler(void);
void secondButtonStateChangeEventControlHandler(void);

void buttonInit(buttonCallbackFunction callbackInit);

/******************************************************************************/
/*                            EXPORTED FUNCTIONS                              */
/******************************************************************************/

	void buttonInit(buttonCallbackFunction callbackInit){
		emberAfCorePrintln("Button Init !");
		if(callbackInit != NULL){
			btnCallbackFunc = callbackInit;
		}
	}

	/** @brief Hal Button Isr
	 *
	 * This callback is called by the framework whenever a button is pressed on the
	 * device. This callback is called within ISR context.
	 *
	 * @param button The button which has changed state, either BUTTON0 or BUTTON1
	 * as defined in the appropriate BOARD_HEADER.  Ver.: always
	 * @param state The new state of the button referenced by the button parameter,
	 * either ::BUTTON_PRESSED if the button has been pressed or ::BUTTON_RELEASED
	 * if the button has been released.  Ver.: always
	 */
	void emberAfHalButtonIsrCallback(uint8_t button, uint8_t state)
	{
		if(state == 1)
		{
			if(button == BUTTON0)
			{
				state_button0++;
				emberEventControlSetInactive(firstButtonStateChangeEventControl);
				emberEventControlSetActive(firstButtonStateChangeEventControl);
				emberEventControlSetDelayMS(firstButtonStateChangeEventControl,500);
			}
			else
			{
				state_button1++;
				emberEventControlSetInactive(secondButtonStateChangeEventControl);
				emberEventControlSetActive(secondButtonStateChangeEventControl);
				emberEventControlSetDelayMS(secondButtonStateChangeEventControl,500);
			}
		}
	}


	void firstButtonStateChangeEventControlHandler(void)
	{
		emberEventControlSetInactive(firstButtonStateChangeEventControl);
		btnCallbackFunc(BUTTON0,state_button0);
		state_button0 = 0;
	}

	void secondButtonStateChangeEventControlHandler(void)
		{
			emberEventControlSetInactive(secondButtonStateChangeEventControl);
			btnCallbackFunc(BUTTON1,state_button1);
			state_button1 = 0;
		}





