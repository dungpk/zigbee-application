/*
 * send.c
 *
 *  Created on: Mar 15, 2022
 *      Author: dungpk
 */
#include "app/framework/include/af.h"
#include "send.h"
#include "Source/App/Receive/receive.h"

static void SEND_FillBufferGlobalCommand(EmberAfClusterId clusterID,
								  EmberAfAttributeId attributeID,
								  uint8_t globalCommand,
								  uint8_t* value,
								  uint8_t length,
								  uint8_t dataType);


void SEND_SendCommandUnicast(uint8_t source,
							 uint8_t destination,
							 uint8_t address)
{
	emberAfSetCommandEndpoints(source, destination);
	(void) emberAfSendCommandUnicast(EMBER_OUTGOING_DIRECT, address);
}

void SEND_FillBufferGlobalCommand(EmberAfClusterId clusterID,
								  EmberAfAttributeId attributeID,
								  uint8_t globalCommand,
								  uint8_t* value,
								  uint8_t length,
								  uint8_t dataType)
{
	uint8_t data[MAX_DATA_COMMAND_SIZE];
	data[0] = (uint8_t)(attributeID & 0x00FF);
	data[1] = (uint8_t)((attributeID & 0xFF00)>>8);
	data[2] = EMBER_SUCCESS;
	data[3] = (uint8_t)dataType;
	memcpy(&data[4], value, length);

	(void) emberAfFillExternalBuffer((ZCL_GLOBAL_COMMAND | ZCL_FRAME_CONTROL_CLIENT_TO_SERVER | ZCL_DISABLE_DEFAULT_RESPONSE_MASK),
									  clusterID,
									  globalCommand,
									  "b",
									  data,
									  length + 4);
}

void SEND_ReportInfoHc(void)
{
	uint8_t modelID[4] = {3, 'S', 'W', '1'};
//	uint8_t manufactureID[5] = {4, 'L', 'u', 'm', 'i'};
//	uint8_t version = 1;

	if(emberAfNetworkState() != EMBER_JOINED_NETWORK){
		return;
	}
	SEND_FillBufferGlobalCommand(ZCL_BASIC_CLUSTER_ID,
								 ZCL_MODEL_IDENTIFIER_ATTRIBUTE_ID,
								 ZCL_READ_ATTRIBUTES_RESPONSE_COMMAND_ID,
								 modelID,
								 13,
								 ZCL_CHAR_STRING_ATTRIBUTE_TYPE);
	SEND_SendCommandUnicast(SOURCE_ENDPOINT_PRIMARY,
							DESTINATTION_ENDPOINT,
							HC_NETWORK_ADDRESS);
}

void SEND_OnOffStateReport(uint8_t endpoint, uint8_t value){
	SEND_FillBufferGlobalCommand(ZCL_ON_OFF_CLUSTER_ID,
						   ZCL_ON_OFF_ATTRIBUTE_ID,
						   ZCL_READ_ATTRIBUTES_RESPONSE_COMMAND_ID,
						   (uint8_t*) &value,
						   1,
						   ZCL_BOOLEAN_ATTRIBUTE_TYPE);

	SEND_SendCommandUnicast(endpoint,
								DESTINATTION_ENDPOINT,
								HC_NETWORK_ADDRESS);

	emberAfWriteServerAttribute(endpoint,
								ZCL_ON_OFF_CLUSTER_ID,
								ZCL_ON_OFF_ATTRIBUTE_ID,
								(uint8_t*) &value,
								ZCL_BOOLEAN_ATTRIBUTE_TYPE);
}


void SendZigDevRequest(void)
{
	uint8_t contents[2];
	contents[1] = 0x00;

	emberSendZigDevRequest(0x0000, LEAVE_RESPONSE, EMBER_AF_DEFAULT_APS_OPTIONS, contents, sizeof(contents));
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
