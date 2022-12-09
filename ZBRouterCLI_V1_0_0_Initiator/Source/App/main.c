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

bool RECEIVE_HandleOnOffCluster(EmberAfClusterCommand* cmd); //Hàm nhận command và xử lý
uint8_t checkBindingTable(uint8_t localEndpoint);//kiểm tra thiết bị đã được binding hay chưa
void SEND_BindingInitToTarget(uint8_t localEndpoint, bool value); //Hàm gửi bản tin từ init đến target


/************************************
 *************** Hàm Main ***********
 ***********************************/
void emberAfMainInitCallback(void)
{
	ledInit();//Hàm khởi tạo led cho thiết bị
	emberAfCorePrintln("Main Init Callback !");
}


/*****************************************************
 * Hàm nhận và xử lý bản từ thiết bị khác ************
 ****************************************************/
boolean emberAfPreCommandReceivedCallback(EmberAfClusterCommand* cmd)
{
	if(cmd->clusterSpecific)
	{
		switch(cmd->apsFrame->clusterId)
		{
			case ZCL_ON_OFF_CLUSTER_ID: //Trường hợp on-off
				RECEIVE_HandleOnOffCluster(cmd);
				break;
			case ZCL_LEVEL_CONTROL_CLUSTER_ID: //Trường hợp điều khiển theo level
				//RECEIVE_HandleLevelControlCluster(cmd);
				break;
			default:
				break;
		}
	}
	return false;
}
/**********************************************
 ****** Hàm xử lý khi được nhận lệnh ON-OFF ***
 **********************************************/
bool RECEIVE_HandleOnOffCluster(EmberAfClusterCommand* cmd)
{
	uint8_t commandID = cmd->commandId;
	/************************************ON-OFF LED******************************************************************************************/
	uint8_t localEndpoint = 0x01;
	switch(commandID)
	{
	case ZCL_OFF_COMMAND_ID: //Nhận lệnh OFF từ theiets bị gửi
		emberAfCorePrintln("Turn off LED");
		switch (cmd->type) {
			case EMBER_INCOMING_UNICAST: //Trường hợp nhận bản tin unicast
				emberAfCorePrintln("Unicast");
				offLed(LED_1); //tắt led 1
				offLed(LED_2);//tắt led 2
				emberAfCorePrintln("check: %d",checkBindingTable(localEndpoint));
				if(checkBindingTable(localEndpoint)>=1) //Kiểm tra xem thiết bị có đang binding không
				{
					emberAfCorePrintln("send to target");
					SEND_BindingInitToTarget(localEndpoint, false); // gửi bản tin chuyển tiếp từ initiator đến target
				}
				break;
			case EMBER_INCOMING_MULTICAST: //Trường hợp nhận bản tin multicast
				emberAfCorePrintln("Multicast");
				offLed(LED_1);
				offLed(LED_2);
				break;
			default:
				break;
		}

		break;
	case ZCL_ON_COMMAND_ID: //Nhận lệnh OFF từ thiết bị gửi

		emberAfCorePrintln("Turn on LED");
		switch (cmd->type) {
			case EMBER_INCOMING_UNICAST: //Trường hợp bản tin nhạn được là bản tin unicast
				emberAfCorePrintln("Unicast");
				onLed(LED_2, ledGreen); //Bật led green 1
				if(checkBindingTable(localEndpoint)>=1) //Kiểm tra bảng binding xem có đang binding không
				{
					emberAfCorePrintln("send to target");
					SEND_BindingInitToTarget(localEndpoint, true); //Gửi bản tin on led từ initiator đến target
				}
				break;
			case EMBER_INCOMING_MULTICAST: //Trường hợp nhận bản tin unicast
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
		if(emberGetBindingRemoteNodeId(i) != EMBER_SLEEPY_BROADCAST_ADDRESS){
			emberGetBinding(i, &binding);
			if(binding.local == localEndpoint && (binding.type == EMBER_UNICAST_BINDING))
			{
				index++;
			}
		}
	}
	return index;
}

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


