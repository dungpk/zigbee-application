/*
 * send.h
 *
 *  Created on: Mar 15, 2022
 *      Author: dungpk
 */

#ifndef SOURCE_APP_SEND_SEND_H_
#define SOURCE_APP_SEND_SEND_H_

#define MAX_DATA_COMMAND_SIZE					50
#define SOURCE_ENDPOINT_PRIMARY					1
#define DESTINATTION_ENDPOINT					1
#define HC_NETWORK_ADDRESS						0x0000

void SEND_SendCommandUnicast(uint8_t source,
							 uint8_t destination,
							 uint8_t address);
void SEND_OnOffStateReport(uint8_t endpoint, uint8_t value);
void SEND_PIRStateReport(uint8_t endpoint, uint8_t value);
void SEND_ReportInfoHc(void);
void SendZigDevRequest(void);
EmberStatus emberSendZigDevRequest(EmberNodeId destination,
                                   uint16_t clusterId,
                                   EmberApsOption options,
                                   uint8_t *contents,
                                   uint8_t length);
#endif /* SOURCE_APP_SEND_SEND_H_ */
