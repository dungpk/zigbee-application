/*
 * led.h
 *
 *  Created on: Apr 11, 2022
 *      Author: Dung
 */

#ifndef MIDDLE_LED_LED_H_
#define MIDDLE_LED_LED_H_

#define LED_RGB_COUNT		2
#define LED_RGB_ELEMENT		3

#define LED_PORT_1			gpioPortA
#define LED_BLUE_PIN_1		(0U)
#define LED_GREEN_PIN_1		(3U)
#define LED_RED_PIN_1		(4U)

#define LED_PORT_2			gpioPortD
#define LED_BLUE_PIN_2		(2U)
#define	LED_GREEN_PIN_2		(1U)
#define LED_RED_PIN_2		(0U)

#define LED_RGB_1			{ {LED_PORT_1,LED_BLUE_PIN_1} , {LED_PORT_1,LED_GREEN_PIN_1}  ,{LED_PORT_1,LED_RED_PIN_1} }
#define LED_RGB_2			{ {LED_PORT_2,LED_BLUE_PIN_2} , {LED_PORT_2,LED_GREEN_PIN_2}  ,{LED_PORT_2,LED_RED_PIN_2} }

#define LED_TOGGLE			1
#define LED_FREE			0

typedef enum
{
	ledOff		= 0x000,
	ledBlue		= BIT(0),
	ledGreen	= BIT(1),
	ledRed		= BIT(2),
	ledPink		= BIT(0) | BIT(2),
	ledYellow	= BIT(2) | BIT(1)
}ledColor;


typedef enum
{
	LED_1,
	LED_2
}ledNumber;


void ledInit(void);
void onLed(ledNumber ledIndex,ledColor color);
void offLed(ledNumber ledIndex);
void toggleLed(ledNumber ledIndex,ledColor color,uint8_t toggleTime,uint32_t onTimeMs,uint32_t offTimeMs);


#endif /* MIDDLE_LED_LED_H_ */
