/*******************************************************************************
 *
 * Description: Lab1
 * Project name: led.h
 *
 *
 * Last Changed By:  $Author: dungpk $
 * Revision:         $Revision: 1.0 $
 * Last Changed:     $Date: 23/2/2021 $
 *
 ******************************************************************************/

#ifndef SOURCE_MID_LED_H_
#define SOURCE_MID_LED_H_

/******************************************************************************/
/*                     		DEFINITIONS            				              */
/******************************************************************************/
#define LED_RGB_COUNT				2
#define LED_RGB_ELEMENT				3

#define LED_PORT_1					gpioPortA
#define LED_BLUE_PIN_1				(0U)
#define LED_GREEN_PIN_1				(3U)
#define LED_RED_PIN_1				(4U)

#define LED_PORT_2					gpioPortD
#define LED_BLUE_PIN_2				(2U)
#define LED_GREEN_PIN_2				(1U)
#define LED_RED_PIN_2				(0U)

#define LED_RGB_1                       { { LED_PORT_1, LED_RED_PIN_1 }, { LED_PORT_1, LED_GREEN_PIN_1 }, { LED_PORT_1, LED_BLUE_PIN_1 } }
#define LED_RGB_2                       { { LED_PORT_2, LED_RED_PIN_2 }, { LED_PORT_2, LED_GREEN_PIN_2 }, { LED_PORT_2, LED_BLUE_PIN_2 } }



typedef enum{
	LED1,
	LED2
}ledNumber;
typedef enum
{
	ledOff 				= 0x000,
	ledRed				= BIT(0),
	ledGreen			= BIT(1),
	ledBlue				= BIT(2),
	ledPink				= ledRed  | ledBlue,
	ledyellow			= ledGreen| ledRed,
	ledRGB				= ledRed  | ledGreen | ledBlue
}ledColor_e;

typedef enum
{
	red,
	green,
	blue,
	off
}ledState_e;

enum{
	LED_FREE,
	LED_TOGGLE
};

/* Function prototypes -----------------------------------------------*/
void ledInit(void);
void turnOffRBGLed(ledNumber index);
void toggleLedHandle(ledNumber ledIndex);
void toggleLed(ledNumber ledIndex, ledColor_e color, uint8_t toggleTime, uint32_t onTimeMs, uint32_t offTimeMs);
#endif /* SOURCE_MID_LED_H_ */
