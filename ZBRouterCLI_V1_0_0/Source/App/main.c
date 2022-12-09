/*
 * main.c
 *
 *  Created on: Apr 19, 2022
 *      Author: Dung
 */
#include "app/framework/include/af.h"
#include "stdint.h"
#include "stdio.h"
#include "Source/Mid/Led/led.h"
#include "Source/Mid/button/button.h"
#include "em_timer.h"
#include "protocol/zigbee/stack/include/binding-table.h"


boolean emberAfPreCommandReceivedCallback(EmberAfClusterCommand* cmd);
bool RECEIVE_HandleOnOffCluster(EmberAfClusterCommand* cmd);
void emberAfMainInitCallback(void)
{
	ledInit();
	emberAfCorePrintln("Main Init Callback !");
}


boolean emberAfPreCommandReceivedCallback(EmberAfClusterCommand* cmd)
{
	if(cmd->clusterSpecific)
	{
		switch(cmd->apsFrame->clusterId)
		{
			case ZCL_ON_OFF_CLUSTER_ID:
				RECEIVE_HandleOnOffCluster(cmd);
				break;
			case ZCL_LEVEL_CONTROL_CLUSTER_ID:
				//RECEIVE_HandleLevelControlCluster(cmd);
				break;
			default:
				break;
		}
	}
	return false;
}


bool RECEIVE_HandleOnOffCluster(EmberAfClusterCommand* cmd)
{
	uint8_t commandID = cmd->commandId;
	/************************************ON-OFF LED******************************************************************************************/
	uint8_t localEndpoint = 0x01;
	switch(commandID)
	{
	case ZCL_OFF_COMMAND_ID:
		emberAfCorePrintln("Turn off LED");
		switch (cmd->type) {
			case EMBER_INCOMING_UNICAST:
				emberAfCorePrintln("Unicast");
				offLed(LED_2);
				offLed(LED_1);

				break;
			case EMBER_INCOMING_MULTICAST:
				emberAfCorePrintln("Multicast");
				offLed(LED_2);
				offLed(LED_1);
				break;
			default:
				break;
		}

		break;
	case ZCL_ON_COMMAND_ID:

		emberAfCorePrintln("Turn on LED");
		switch (cmd->type) {
			case EMBER_INCOMING_UNICAST:
				emberAfCorePrintln("Unicast");
				onLed(LED_2, ledGreen);
				break;
			case EMBER_INCOMING_MULTICAST:
				emberAfCorePrintln("Multicast");
				onLed(LED_2, ledGreen);
				break;
			default:
				break;
		}
		break;
	default:
		break;
	}
	return false;
}

