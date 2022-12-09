/*
 * button.h
 *
 *  Created on: Apr 11, 2022
 *      Author: Dung
 */

#ifndef MIDDLE_BUTTON_BUTTON_H_
#define MIDDLE_BUTTON_BUTTON_H_

typedef enum
{
	release,
	press_1,
	press_2,
	press_3,
}btnState_e;


typedef void(*buttonCallbackFunction)(uint8_t,btnState_e);

void buttonInit(buttonCallbackFunction);

#endif /* MIDDLE_BUTTON_BUTTON_H_ */
