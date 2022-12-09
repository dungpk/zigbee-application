/*
 * led.c
 *
 *  Created on: Apr 10, 2022
 *      Author: Dung
 */

#include "app/framework/include/af.h"
#include "led.h"
#include "em_timer.h"


/******************************************************************************/
/*                     EXPORTED TYPES and DEFINITIONS                         */
/******************************************************************************/

typedef struct
{
	GPIO_Port_TypeDef	port;
	unsigned int 		pin;
}ledStruct;

typedef struct{
	uint32_t onTime;
	uint32_t offTime;
	uint8_t blinkTime;

}ledBlink_t ;

typedef struct{
	ledBlink_t ledBlink;

}ledAct_t;

typedef struct {
	uint8_t ledBlinkMode;
	uint8_t color;
	ledAct_t ledAct;

} ledActionInfo_t;

/******************************************************************************/
/*                              PRIVATE DATA                                  */
/******************************************************************************/

ledStruct ledRgbArray[LED_RGB_COUNT][LED_RGB_ELEMENT] = {LED_RGB_1,LED_RGB_2};

ledActionInfo_t ledAction[LED_RGB_COUNT];

EmberEventControl led1ToggleEventControl,led2ToggleEventControl;
EmberEventControl	*ledEventControl[LED_RGB_COUNT];

/******************************************************************************/
/*                            PRIVATE FUNCTIONS                               */
/******************************************************************************/

void ledInit(void);
void onLed(ledNumber ledIndex,ledColor color);
void offLed(ledNumber ledIndex);
static void toggleLedHandle(ledNumber ledIndex);
void toggleLed(ledNumber ledIndex,ledColor color,uint8_t toggleTime,uint32_t onTimeMs,uint32_t offTimeMs);
void led1ToggleEventHandle(void);
void led2ToggleEventHandle(void);


/******************************************************************************/
/*                            EXPORTED FUNCTIONS                              */
/******************************************************************************/

void ledInit(void)
{

	ledEventControl[LED_1] = (EmberEventControl *)&led1ToggleEventControl;
	ledEventControl[LED_2] = (EmberEventControl *)&led2ToggleEventControl;

	CMU_ClockEnable(cmuClock_GPIO,true);
	for(int i=0;i<LED_RGB_COUNT;i++)
	{
		for(int j=0;j<LED_RGB_ELEMENT;j++)
		{
			GPIO_PinModeSet(ledRgbArray[i][j].port,
							ledRgbArray[i][j].pin,
							gpioModePushPull,
							0);
		}
	}
	offLed(LED_1);
	offLed(LED_2);
}

void onLed(ledNumber ledIndex,ledColor color)
{
	for(int i=0;i<LED_RGB_ELEMENT;i++)
	{
		if( ((color >> i) & 0x01) == 1 )
		{
			GPIO_PinOutClear(ledRgbArray[ledIndex][i].port,ledRgbArray[ledIndex][i].pin);
		}
		else
		{
			GPIO_PinOutSet(ledRgbArray[ledIndex][i].port,ledRgbArray[ledIndex][i].pin);
		}
	}
}


void offLed(ledNumber ledIndex)
{
	for(int j=0;j<LED_RGB_ELEMENT;j++)
	{
		GPIO_PinOutSet(ledRgbArray[ledIndex][j].port,ledRgbArray[ledIndex][j].pin);
	}
}


void toggleLed(ledNumber ledIndex,ledColor color,uint8_t toggleTime,uint32_t onTimeMs,uint32_t offTimeMs)
{
	//LED_TimeReset();
	emberEventControlSetInactive(*ledEventControl[ledIndex]);
	ledAction[ledIndex].ledBlinkMode = LED_TOGGLE;
	ledAction[ledIndex].color = color;

	ledAction[ledIndex].ledAct.ledBlink.onTime = onTimeMs;
	ledAction[ledIndex].ledAct.ledBlink.offTime = offTimeMs;
	ledAction[ledIndex].ledAct.ledBlink.blinkTime = toggleTime*2;
	emberEventControlSetActive(*ledEventControl[ledIndex]);
}

static void toggleLedHandle(ledNumber ledIndex)
{

	if(ledAction[ledIndex].ledAct.ledBlink.blinkTime !=0)
	{
		if(ledAction[ledIndex].ledAct.ledBlink.blinkTime % 2 == 0)
		{
			for(int i =0;i<LED_RGB_ELEMENT;i++)
			{
				if( ((ledAction[ledIndex].color >>i) & 0x01) ==1)
				{
					GPIO_PinOutClear(ledRgbArray[ledIndex][i].port,ledRgbArray[ledIndex][i].pin);
				}
				else
				{
					GPIO_PinOutSet(ledRgbArray[ledIndex][i].port,ledRgbArray[ledIndex][i].pin);
				}
			}
			emberEventControlSetDelayMS(*ledEventControl[ledIndex],ledAction[ledIndex].ledAct.ledBlink.onTime);
		}
		else
		{
			for(int j = 0;j<LED_RGB_ELEMENT;j++)
			{
				GPIO_PinOutSet(ledRgbArray[ledIndex][j].port,ledRgbArray[ledIndex][j].pin);
			}
			emberEventControlSetDelayMS(*ledEventControl[ledIndex],ledAction[ledIndex].ledAct.ledBlink.offTime);
		}
		ledAction[ledIndex].ledAct.ledBlink.blinkTime--;
	}
	else
	{
		emberEventControlSetActive(*ledEventControl[ledIndex]);
		ledAction[ledIndex].ledBlinkMode = LED_FREE;
		for(int j=0;j<LED_RGB_ELEMENT;j++)
		{
			GPIO_PinOutSet(ledRgbArray[ledIndex][j].port,ledRgbArray[ledIndex][j].pin);
		}
	}

}



void led1ToggleEventHandle(void)
{
	toggleLedHandle(LED_1);
}
void led2ToggleEventHandle(void)
{
	toggleLedHandle(LED_2);
}





