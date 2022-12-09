/*
 * button.c
 *
 *  Created on: Apr 11, 2022
 *      Author: Dung
 *
 */
#include "app/framework/include/af.h"
#include "button.h"

buttonCallbackFunction btnCallbackFunc = NULL;

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
	btnCallbackFunc(button,state);
}
