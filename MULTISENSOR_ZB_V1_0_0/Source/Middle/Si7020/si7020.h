/*
 * si7020.h
 *
 *  Created on: Apr 11, 2022
 *      Author: Dung
 */

#ifndef MIDDLE_SI7020_SI7020_H_
#define MIDDLE_SI7020_SI7020_H_

#define I2C_FOLLOWER_ADDRESS             0x40
#define HUMIDITY_HMM_REG           	 	0xE5 // Dia chi thanh ghi do am
#define TEMPERATURE_HMM_REG         	0xE3 // Dia chi thanh ghi nhiet do


#define I2C_TXBUFFER_SIZE                 10
#define I2C_RXBUFFER_SIZE                 10


void initI2C(void);
void TemHumSensor_Init(void);
void I2C_LeaderRead(uint16_t followerAddress, uint8_t targetAddress, uint8_t *rxBuff, uint8_t numBytes);

#endif /* MIDDLE_SI7020_SI7020_H_ */
