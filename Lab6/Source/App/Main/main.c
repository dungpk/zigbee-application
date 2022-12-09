/*
 * main.c
 *
 *  Created on: Mar 6, 2022
 *      Author: dungpk
 */


#include "app/framework/include/af.h"
#include "Source/Mid/LED/led.h"
#include "Source/Mid/Button/button.h"
#include "protocol/zigbee/stack/include/binding-table.h"
#include "Source/App/Network/network.h"
#include "Source/App/Send/send.h"
#include "Source/App/Receive/receive.h"
#include "main.h"



uint32_t KalmanHumi=0;
uint32_t KalmanTemp=0;
bool networkReady = false;
systemState system_State;

void Main_ButtonPressCallbackHandler(uint8_t button, BUTTON_Event_t pressHandler);
void Main_ButtonHoldCallbackHandler(uint8_t button, BUTTON_Event_t holdingHandler);
void Main_networkEventHandler(uint8_t networkResult);
/* Event **************************************************************/
EmberEventControl readValueSensorLightControl;
EmberEventControl ReadValueTempHumiControl;
EmberEventControl mainStateEventControl;
/** @brief Main Init
 *
 *
 * This function is called from the application's main function. It gives the
 * application a chance to do any initialization required at system startup.
 * Any code that you would normally put into the top of the application's
 * main() routine should be put into this function.
        Note: No callback
 * in the Application Framework is associated with resource cleanup. If you
 * are implementing your application on a Unix host where resource cleanup is
 * a consideration, we expect that you will use the standard Posix system
 * calls, including the use of atexit() and handlers for signals such as
 * SIGTERM, SIGINT, SIGCHLD, SIGPIPE and so on. If you use the signal()
 * function to register your signal handler, please mind the returned value
 * which may be an Application Framework function. If the return value is
 * non-null, please make sure that you call the returned function from your
 * handler to avoid negating the resource cleanup of the Application Framework
 * itself.
 *
 */
void emberAfMainInitCallback(void)
{
	emberAfCorePrintln("Main Init");
	ledInit();
	buttonInit(Main_ButtonHoldCallbackHandler, Main_ButtonPressCallbackHandler);
	Network_Init(Main_networkEventHandler);
	emberEventControlSetActive(mainStateEventControl);
}


/****************************EVENT HANDLER MIDDER********************************************************************/
/*
 * @func	Main_ButtonPressCallbackHandler
 * @brief	Event Button Handler
 * @param	button, pressHandler
 * @retval	None
 */
void Main_ButtonPressCallbackHandler(uint8_t button, BUTTON_Event_t pressHandler)
{
//	if((pressHandler > press_max) && (pressHandler <hold_max))
//	{
//		emberAfCorePrintln("SW %d HOLDING %d s\n",button+1,pressHandler-press_max);
//	} else if((pressHandler > 0) && (pressHandler <press_max))
//	{
//		emberAfCorePrintln("SW %d PRESS_TIME %d s\n",button+1,pressHandler-press_max);
//	}else
//	{
//		emberAfCorePrintln("UNKNOW\n");
//	}
	switch(pressHandler)
	{
	case press_1:
		if(button == SW_1)
		{
			emberAfCorePrintln("Version 1");
			emberAfCorePrintln("SW1: 1 time");
			turnOnLed(LED1,ledBlue);
			SEND_OnOffStateReport(1, LED_ON);

		}
		else
		{
			emberAfCorePrintln("Version 1");
			emberAfCorePrintln("SW2: 1 time");
			SEND_ReportInfoHc();
			toggleLed(LED2,ledPink,3,300,300);
		}
	break;
	case press_2:
		if(button == SW_1)
		{
			emberAfCorePrintln("Version 1");
			emberAfCorePrintln("SW1: 2 times");
			SEND_OnOffStateReport(1, LED_OFF);
			turnOffRBGLed(LED1);
		}
		else
		{
			emberAfCorePrintln("Version 1");
			emberAfCorePrintln("SW2: 2 time");
			toggleLed(LED2,ledyellow,4,500,500);
		}
		break;
	case press_3:
		if(button == SW_1)
		{
			emberAfCorePrintln("SW1: 3 time");
			emberAfCorePrintln("Find and Join");
			NETWORK_FindAndJoin();

		}
		else
		{
			emberAfCorePrintln("SW2: 3 time");
		}
		break;
	case press_4:
		if(button == SW_1)
		{
			emberAfCorePrintln("SW1: 4 time");

		}
		else
		{
			emberAfCorePrintln("SW2: 4 time");
		}
		break;
	case press_5:
		if(button == SW_1)
		{
			emberAfCorePrintln("SW1: 5 time");
			toggleLed(LED1,ledyellow, 2, 200, 200);
			SendZigDevRequest();
			emberClearBindingTable();
			emberLeaveNetwork();
			halReboot();

		}
		else
		{
			emberAfCorePrintln("SW2: 5 time");
			toggleLed(LED2,ledPink,3,300,300);
		}
		break;
	default:
		break;
	}
}

/*
 * @func	Main_ButtonHoldCallbackHandler
 * @brief	Event Button Handler
 * @param	button, holdingHandler
 * @retval	None
 */
void Main_ButtonHoldCallbackHandler(uint8_t button, BUTTON_Event_t holdingHandler)
{
//	emberAfCorePrintln("SW %d HOLDING %d s\n",button+1,holdingHandler-press_max);
	switch(holdingHandler)
	{
	case hold_1s:
		emberAfCorePrintln("SW1: 1 s");
		break;
	case hold_2s:
		emberAfCorePrintln("SW1: 2 s");
		break;
	case hold_3s:
		emberAfCorePrintln("SW1: 3 s");
		break;
	case hold_4s:
		emberAfCorePrintln("SW1: 4 s");
		break;
	case hold_5s:
		emberAfCorePrintln("SW1: 5 s");
		break;

	default:
		break;
	}
}

void mainStateEventHandler(void)
{
	emberEventControlSetInactive(mainStateEventControl);
	EmberNetworkStatus nwkStatusCurrent;
	switch (system_State) {
		case POWER_ON_STATE:
			nwkStatusCurrent = emberAfNetworkState();
			if(nwkStatusCurrent == EMBER_NO_NETWORK)
			{
				toggleLed(LED1,ledRed,3,200,200);
				NETWORK_FindAndJoin();
			}
			system_State = IDLE_STATE;
			break;
		case REPORT_STATE:
			toggleLed(LED1,ledPink,3,300,300);
			networkReady = true;
			system_State = IDLE_STATE;
			SEND_ReportInfoHc();
			break;
		case IDLE_STATE:
			break;
		case REBOOT_STATE:
			system_State = IDLE_STATE;
			halReboot();
			break;
		default:
			break;
	}

}
void Main_networkEventHandler(uint8_t networkResult)
{
	emberAfCorePrintln("Network Event Handle");
	switch (networkResult) {
		case NETWORK_HAS_PARENT:
			emberAfCorePrintln("Network has parent");
			toggleLed(LED1,ledPink,3,300,300);
			networkReady = true;
			system_State = REPORT_STATE;
			emberEventControlSetDelayMS(mainStateEventControl, 1000);
			break;
		case NETWORK_JOIN_FAIL:
			system_State = IDLE_STATE;
			emberAfCorePrintln("Network Join Fail");
			emberEventControlSetDelayMS(mainStateEventControl, 1000);
			break;
		case NETWORK_JOIN_SUCCESS:
			emberAfCorePrintln("Network Join Success");
			toggleLed(LED1,ledPink,3,300,300);
			networkReady =true;
			system_State = REPORT_STATE;
			emberEventControlSetDelayMS(mainStateEventControl, 1000);
			break;
		case NETWORK_LOST_PARENT:
			emberAfCorePrintln("Network lost parent");
			toggleLed(LED1,ledPink,3,300,300);
			system_State = IDLE_STATE;
			emberEventControlSetDelayMS(mainStateEventControl, 1000);
			break;
		case NETWORK_OUT_NETWORK:
			if(networkReady)
			{
				emberAfCorePrintln("Network Out network");
				toggleLed(LED1,ledPink,3,300,300);
				system_State = REBOOT_STATE;
				emberEventControlSetDelayMS(mainStateEventControl, 3000);
			}
			break;
		default:
			break;
	}
}
