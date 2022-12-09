/*
 * main.c
 *
 *  Created on: Apr 23, 2022
 *      Author: Dung
 */
#include "app/framework/include/af.h"
#include "stdint.h"
#include "stdio.h"

void emberAfMainInitCallback(void)
{
	emberAfCorePrintln("Main Init Callback !");
}


_Bool emberAfPreCommandReceivedCallback(EmberAfClusterCommand* cmd)
{
	emberAfCorePrintln("USART Callback !");
	if(cmd->clusterSpecific)
		{
			switch(cmd->apsFrame->clusterId)
			{
				case ZCL_ON_OFF_CLUSTER_ID:
					//RECEIVE_HandlerOnOffCluster(cmd);
					break;
				case ZCL_LEVEL_CONTROL_CLUSTER_ID:
					//RECEIVE_HandleLevelControlCluster(cmd);
					break;
				default:
					break;

			}
		}
		return true;
}




