/*******************************************************************************
 *
 * Description: Assigment3
 * Project name: Assigment3
 *
 *
 * Last Changed By:  $Author: dungpk $
 * Revision:         $Revision: 1.0 $
 * Last Changed:     $Date: 12/3/2022 $
 *
 ******************************************************************************/
#include "app/framework/include/af.h"
#include "Source/Mid/LED/led.h"
#include "protocol/zigbee/stack/include/binding-table.h"


void SEND_BindingInitToTarget(uint8_t localEndpoint, bool value);
uint8_t checkBindingTable(uint8_t localEndpoint);
boolean emberAfPreCommandReceivedCallback(EmberAfClusterCommand* cmd);
bool RECEIVE_HandleLevelControlCluster(EmberAfClusterCommand* cmd);
bool RECEIVE_HandleOnOffCluster(EmberAfClusterCommand* cmd);

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
	ledInit();
	timer_init();
}

/** @brief Pre Command Received
 *
 * This callback is the second in the Application Framework's message processing
 * chain. At this point in the processing of incoming over-the-air messages, the
 * application has determined that the incoming message is a ZCL command. It
 * parses enough of the message to populate an EmberAfClusterCommand struct. The
 * Application Framework defines this struct value in a local scope to the
 * command processing but also makes it available through a global pointer
 * called emberAfCurrentCommand, in app/framework/util/util.c. When command
 * processing is complete, this pointer is cleared.
 *
 * @param cmd   Ver.: always
 */
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
				RECEIVE_HandleLevelControlCluster(cmd);
				break;
			default:
				break;
		}
	}
	return false;
}

/*
 * @function 			: RECEIVE_HandleLevelControlCluster
 *
 * @brief				: Handler LED Level
 *
 * @parameter			: EmberAfClusterCommand
 *
 * @return value		: True or false
 */
bool RECEIVE_HandleLevelControlCluster(EmberAfClusterCommand* cmd)
{
	uint8_t commandID = cmd->commandId;
	uint8_t endPoint  = cmd->apsFrame -> destinationEndpoint;
	uint8_t payloadOffset = cmd->payloadStartIndex;		// Gan offset = startindex
	uint8_t level;
	uint16_t transitionTime;
	emberAfCorePrintln("ClusterID: 0x%2X", cmd->apsFrame->clusterId);
/******************************************LEVEL CONTROL LED***************************************************************************/
		switch(commandID)
			{

				case ZCL_MOVE_TO_LEVEL_COMMAND_ID:
					if(cmd->bufLen < payloadOffset + 1u)
					{
						return EMBER_ZCL_STATUS_MALFORMED_COMMAND;
					}
					level = emberAfGetInt8u(cmd->buffer, payloadOffset, cmd->bufLen);		// Lay 1 byte gia tri cua level control
					transitionTime = emberAfGetInt16u(cmd->buffer, payloadOffset+1, cmd->bufLen);
					emberAfCorePrintln(" RECEIVE_HandleLevelControlCluster LEVEL = %d, time: 0x%2X\n", level, transitionTime);

					if(endPoint == 1)
					{
						if(level >=80)
						{
							emberAfCorePrintln("LED GREEN");
							turnOnLed(LED1, ledGreen);
						}else if(level>=40)
						{
							emberAfCorePrintln("LED RED");
							turnOnLed(LED1, ledRed);
						}else if(level>0)
						{
							emberAfCorePrintln("LED BLUE");
							turnOnLed(LED1, ledBlue);
						}else
						{
							emberAfCorePrintln("turn 0ff");
							turnOffRBGLed(LED1);
						}

					}
					else if(endPoint == 2)
					{
						emberAfCorePrintln("DIM LED");
						dimLED(LED2, ledRed, level);
					}
					break;
				default:
					break;
				}
		return false;
}

/*
 * @function 			: RECEIVE_HandleOnOffCluster
 *
 * @brief				: Handler LED ON/OFF
 *
 * @parameter			: cmd
 *
 * @return value		: True or false
 */
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
				turnOnLed(LED2, ledOff);
				emberAfCorePrintln("check: %d",checkBindingTable(localEndpoint));
				if(checkBindingTable(localEndpoint)>=1)
				{
					emberAfCorePrintln("Send command off to target");
					SEND_BindingInitToTarget(localEndpoint, false);
				}

				break;
			case EMBER_INCOMING_MULTICAST:
				emberAfCorePrintln("Multicast");
				turnOnLed(LED1, ledOff);
				turnOnLed(LED2, ledOff);
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
				turnOnLed(LED2, ledGreen);
				emberAfCorePrintln("check: %d",checkBindingTable(localEndpoint));
				if(checkBindingTable(localEndpoint) >= 1)
				{
					emberAfCorePrintln("Send command on to target");
					SEND_BindingInitToTarget(localEndpoint, true);
				}
				break;
			case EMBER_INCOMING_MULTICAST:
				emberAfCorePrintln("Multicast");
				turnOnLed(LED2, ledGreen);
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

/*
 * @function 			: checkBindingTable
 *
 * @brief				: API support to check information on binding table.
 *
 * @parameter			: localEndpoint
 *
 * @return value		: True or false
 */
uint8_t checkBindingTable(uint8_t localEndpoint)
{
	uint8_t index = 0;
	for(uint8_t i=0; i< EMBER_BINDING_TABLE_SIZE; i++)
	{
		EmberBindingTableEntry binding;
		if(emberGetBindingRemoteNodeId(i) != EMBER_SLEEPY_BROADCAST_ADDRESS)
		{
			emberGetBinding(i, &binding);
			if((binding.local == localEndpoint) && (binding.type == EMBER_UNICAST_BINDING))
			{
				index++;
			}
		}
	}
	return index;
}

/*
 * @function 			: SEND_BindingInitToTarget
 *
 * @brief				: Send command Initiator to Target
 *
 * @parameter			: localEndpoint, value
 *
 * @return value		: NONE
 */

void SEND_BindingInitToTarget(uint8_t localEndpoint, bool value)
{
	EmberStatus status = EMBER_INVALID_BINDING_INDEX;
	uint8_t indexNodeID = checkBindingTable(localEndpoint)-1;
	uint16_t currentTargetNodeID = emberGetBindingRemoteNodeId(indexNodeID);
	emberAfCorePrintln("index: 0x%2X",indexNodeID);
	emberAfCorePrintln("node id: 0x%2X",currentTargetNodeID);
	EmberBindingTableEntry binding;
	for(uint8_t i = 0; i< EMBER_BINDING_TABLE_SIZE ; i++)
		{

			status = emberGetBinding(i, &binding);
			// check status send
			if(status != EMBER_SUCCESS)
			{
				return;
			}
		}
	emberGetBinding(indexNodeID, &binding);
	emberAfCorePrintln("local ep: 0x%X",binding.local);
	emberAfCorePrintln("remote ep: 0x%X",binding.remote);

	if((currentTargetNodeID != EMBER_SLEEPY_BROADCAST_ADDRESS) &&
			 (currentTargetNodeID != EMBER_RX_ON_WHEN_IDLE_BROADCAST_ADDRESS) &&
			 (currentTargetNodeID != EMBER_BROADCAST_ADDRESS))
	{
			switch (value) {
				case true:
					emberAfCorePrintln("SEND ON INIT TO TARGET");
					emberAfFillCommandOnOffClusterOn();
					emberAfSetCommandEndpoints(binding.local, binding.remote);
					emberAfSendCommandUnicast(EMBER_OUTGOING_DIRECT, currentTargetNodeID);
					break;
				case false:
					emberAfCorePrintln("SEND OFF INIT TO TARGET");
					emberAfFillCommandOnOffClusterOff();
					emberAfSetCommandEndpoints(binding.local, binding.remote);
					emberAfSendCommandUnicast(EMBER_OUTGOING_DIRECT, currentTargetNodeID);
					break;
			}
	}
}
