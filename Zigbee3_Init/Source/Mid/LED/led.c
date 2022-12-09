/*******************************************************************************
 *
 * Description: Lab3
 * Project name: led.c
 *
 *
 * Last Changed By:  $Author: dungpk $
 * Revision:         $Revision: 1.0 $
 * Last Changed:     $Date: 12/3/2022 $
 *
 ******************************************************************************/

#include "app/framework/include/af.h"
#include "led.h"
#include "em_timer.h"



typedef struct {
  GPIO_Port_TypeDef   port;
  unsigned int        pin;
  bool 				  ledBlinkMode;
  bool				  ledDim;
  ledColor_e		  color;
  uint32_t 			  onTime;
  uint32_t			  offTime;
  uint32_t			  dimLevel;
  uint8_t			  blinkTime;
} ledArray_t;

ledArray_t led_Array[LED_RGB_COUNT][LED_RGB_ELEMENT] = {LED_RGB_1, LED_RGB_2};

ledArray_t ledAction[LED_RGB_COUNT];
uint32_t freq =0;

static void dimLedHandle(ledNumber ledIndex);

/**
 * @func    ledInit
 * @brief   Initialize LED
 * @param   None
 * @retval  None
 */
void ledInit(void)
{

	CMU_ClockEnable(cmuClock_GPIO, true);
	for(int i = 0;i <LED_RGB_COUNT;i++)
	{
		for(int j = 0; j< LED_RGB_ELEMENT;j++)
		{
			GPIO_PinModeSet(led_Array[i][j].port, led_Array[i][j].pin,
							gpioModePushPull,0);
		}
	}
	turnOffRBGLed(LED1);
	turnOffRBGLed(LED2);
}

/**
 * @func    timer_init
 * @brief   PWM for dimer LED
 * @param   None
 * @retval  None
 */
void timer_init(void)
{
	TIMER_Init_TypeDef timerInit = TIMER_DIM_INIT;
	CMU_ClockEnable(cmuClock_TIMER3, true);
	timerInit.prescale = (TIMER_Prescale_TypeDef)_TIMER_CFG_PRESC_DIV1;
	do{

		freq = CMU_ClockFreqGet(cmuClock_EM01GRPACLK);

		freq /= (timerInit.prescale + 1);

		timerInit.prescale++;
		TIMER_Init(TIMER3 ,&timerInit);
	}while((timerInit.prescale <= timerPrescale1024)&& (freq > 2000000));

	TIMER_IntEnable(TIMER3, _TIMER_IF_OF_MASK);
	NVIC_EnableIRQ(TIMER3_IRQn);

	TIMER3->CMD = TIMER_CMD_STOP;
}
/**
 * @func    TIMER3_IRQHandler
 * @brief   Handler Interrupt
 * @param   None
 * @retval  None
 */
void TIMER3_IRQHandler(void)
{
//	emberAfCorePrintln("TIMER HANDLER: \n");
	TIMER3->CMD = TIMER_CMD_STOP;
	for(uint8_t i=0;i<LED_RGB_COUNT;i++)
	{
		if(ledAction[i].ledBlinkMode == LED_DIM)
		{
			dimLedHandle(i);
			break;
		}

	}
	TIMER_IntClear(TIMER3, _TIMER_IF_OF_MASK);
}

/**
 * @func    turnOffRBGLed
 * @brief   turn Off LED
 * @param   None
 * @retval  None
 */
void turnOffRBGLed(ledNumber index)
{
	for(int j=0;j<LED_RGB_ELEMENT;j++)
	{
		GPIO_PinOutSet(led_Array[index][j].port, led_Array[index][j].pin);
	}
}

/**
 * @func    turnOnLed
 * @brief   turn On LED
 * @param   ledNumber, ledColor_e
 * @retval  None
 */
void turnOnLed(ledNumber index, ledColor_e color)
{
	for(int j=0;j<LED_RGB_ELEMENT;j++)
	{
		if(((color >> j) & 0x01) == 1)
		{
			GPIO_PinOutClear(led_Array[index][j].port, led_Array[index][j].pin);
		}
		else{
			GPIO_PinOutSet(led_Array[index][j].port, led_Array[index][j].pin);
		}
	}
}

/**
 * @func    dimLedHandle
 * @brief   Handler Dim led
 * @param   ledNumber
 * @retval  None
 */
static void dimLedHandle(ledNumber ledIndex)
{
	uint32_t cycles;
	if(ledAction[ledIndex].ledDim)
	{
		for(int i = 0; i < LED_RGB_ELEMENT; i++)
		{
			if( ((ledAction[ledIndex].color >> i )& 0x01) == 1)
			{
				GPIO_PinOutClear(led_Array[ledIndex][i].port, led_Array[ledIndex][i].pin);
			}
			else
			{
				GPIO_PinOutSet(led_Array[ledIndex][i].port, led_Array[ledIndex][i].pin);
			}
		}
	ledAction[ledIndex].ledDim = false;
	cycles = ledAction[ledIndex].dimLevel;
	}else
	{
		for(int j = 0;j<LED_RGB_ELEMENT;j++)
		{
			GPIO_PinOutSet(led_Array[ledIndex][j].port, led_Array[ledIndex][j].pin);
		}

		ledAction[ledIndex].ledDim = true;
		cycles = LED_RGB_DIM_T - ledAction[ledIndex].dimLevel;
	}
	LED_SetChangeDimStatetTime(cycles);
}

/**
 * @func    LED_SetChangeDimStatetTime
 * @brief   Caculation Period dim led
 * @param   ledNumber
 * @retval  None
 */
void LED_SetChangeDimStatetTime(uint32_t time)
{
	uint32_t totalTicks;
	totalTicks = (((uint32_t)freq * time) + 500000) / 1000000;

	TIMER_CounterSet(TIMER3, 0);
	TIMER_TopSet(TIMER3, totalTicks);

	TIMER3->CMD = TIMER_CMD_START;
}
/**
 * @func    dimLED
 * @brief   dim LED
 * @param   None
 * @retval  None
 */
void dimLED(ledNumber ledIndex, ledColor_e color, uint8_t level)
{
	TIMER_Reset(TIMER3);
	if(level >= 100)
	{
		level = 100;
	}
	ledAction[ledIndex].ledBlinkMode = LED_DIM;
	ledAction[ledIndex].color = color;
	ledAction[ledIndex].dimLevel = level;
	ledAction[ledIndex].ledDim = false;

	LED_SetChangeDimStatetTime(LED_RGB_DIM_T-level);
}
