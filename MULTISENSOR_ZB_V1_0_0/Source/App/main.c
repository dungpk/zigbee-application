/*
 * main.c
 *
 *  Created on: Apr 11, 2022
 *      Author: Dung
 */
#include "app/framework/include/af.h"
#include "Source/Middle/button/button.h"
#include "Source/Middle/LDR/ldr.h"
#include "Source/Middle/Si7020/si7020.h"

void buttonCallbackHandler(uint8_t,btnState_e);

void emberAfMainInitCallback(void)
{
	LightSensor_Init();
	TemHumSensor_Init();
	emberAfCorePrintln("Main Init Callback !");
	buttonInit(buttonCallbackHandler);

}

/** @brief Main Init
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
void buttonCallbackHandler(uint8_t button,btnState_e state)
{

	switch(state)
	{
	case press_1:
		if(button == BUTTON0)
		{

			emberAfCorePrintln("SW1 is Press_1");
		}
		else
		{
			emberAfCorePrintln("SW2 is Press_1");

		}
		break;

	case press_2:
		if(button == BUTTON0)
		{
			emberAfCorePrintln("SW1 is Press_2");


		}
		else
		{
			emberAfCorePrintln("SW2 is Press_2");

		}
		break;

	case press_3:
		if(button == BUTTON0)
		{
			emberAfCorePrintln("SW1 is Press_3");

		}
		break;
	default :
		break;
	}

}







