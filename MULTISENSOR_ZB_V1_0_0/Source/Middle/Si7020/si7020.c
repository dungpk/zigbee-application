/*
 * si7020.c
 *
 *  Created on: Apr 11, 2022
 *      Author: Dung
 */

/*                              INCLUDE FILES                                 */
/******************************************************************************/
#include <stdio.h>
#include "stdint.h"
#include <string.h>
#include "em_device.h"
#include "em_chip.h"
#include "em_i2c.h"
#include "em_cmu.h"
#include "em_emu.h"
#include "em_gpio.h"
#include "bsp.h"
#include "si7020.h"
#include "app/framework/include/af.h"

/******************************************************************************/
/*                     EXPORTED TYPES and DEFINITIONS                         */
/******************************************************************************/
/******************************************************************************/
/*                              PRIVATE DATA                                  */
/******************************************************************************/

uint8_t count_temp = 0;
uint8_t count_humi = 0;
EmberEventControl TemHumEventControl;


/******************************************************************************/
/*                              EXPORTED DATA                                 */
/******************************************************************************/


/******************************************************************************/
/*                            PRIVATE FUNCTIONS                               */
/******************************************************************************/



// Transmission flags
volatile bool i2c_startTx;

/***************************************************************************//**
 * @brief Enable clocks
 ******************************************************************************/



void initI2C(void)
{
  // Use default settings
  I2C_Init_TypeDef i2cInit = I2C_INIT_DEFAULT;

  CMU_ClockEnable(cmuClock_I2C0, true);

  // Using PA5 (SDA) and PA6 (SCL)
  GPIO_PinModeSet(gpioPortB, 0, gpioModeWiredAndPullUpFilter, 1);
  GPIO_PinModeSet(gpioPortB, 1, gpioModeWiredAndPullUpFilter, 1);

  //Clear CLK pin
  for(uint8_t i = 0; i < 9; i ++){
	  GPIO_PinOutSet(gpioPortB, 0);
	  GPIO_PinOutClear(gpioPortB, 0);
  }
  // Route I2C pins to GPIO
  GPIO->I2CROUTE[0].SDAROUTE = (GPIO->I2CROUTE[0].SDAROUTE & ~_GPIO_I2C_SDAROUTE_MASK)
                        | (gpioPortB << _GPIO_I2C_SDAROUTE_PORT_SHIFT
                        | (1 << _GPIO_I2C_SDAROUTE_PIN_SHIFT));
  GPIO->I2CROUTE[0].SCLROUTE = (GPIO->I2CROUTE[0].SCLROUTE & ~_GPIO_I2C_SCLROUTE_MASK)
                        | (gpioPortB << _GPIO_I2C_SCLROUTE_PORT_SHIFT
                        | (0 << _GPIO_I2C_SCLROUTE_PIN_SHIFT));
  GPIO->I2CROUTE[0].ROUTEEN = GPIO_I2C_ROUTEEN_SDAPEN | GPIO_I2C_ROUTEEN_SCLPEN;

  i2cInit.enable = true;
  i2cInit.master = true;

  i2cInit.freq = I2C_FREQ_STANDARD_MAX;
  i2cInit.refFreq = 0;
  i2cInit.clhr = i2cClockHLRStandard;

  // Initialize the I2C
  I2C_Init(I2C0, &i2cInit);

  // Set the status flags and index
//  i2c_startTx = false;

  // Enable automatic STOP on NACK
//  I2C0->CTRL = I2C_CTRL_AUTOSN;
}

/***************************************************************************//**
 * @brief I2C read numBytes from follower device starting at target address
 ******************************************************************************/
void I2C_LeaderRead(uint16_t followerAddress, uint8_t targetAddress, uint8_t *rxBuff, uint8_t numBytes)
{
  // Transfer structure
  I2C_TransferSeq_TypeDef i2cTransfer;
  I2C_TransferReturn_TypeDef result;

  // Initialize I2C transfer
  i2cTransfer.addr          = followerAddress;
  i2cTransfer.flags         = I2C_FLAG_WRITE_READ; // must write target address before reading
  i2cTransfer.buf[0].data   = &targetAddress;
  i2cTransfer.buf[0].len    = 1;
  i2cTransfer.buf[1].data   = rxBuff;
  i2cTransfer.buf[1].len    = numBytes;

  result = I2C_TransferInit(I2C0, &i2cTransfer);

  while (result == i2cTransferInProgress) {
    result = I2C_Transfer(I2C0);
  }
  if (result != i2cTransferDone)
  {
  }
}


void TemHumSensor_Init(void)
{
	initI2C();
	emberEventControlSetActive(TemHumEventControl);
}

void TemHumEventHandle(void)
{
	count_temp++;
	count_humi++;
	uint16_t Humi = 30;
	uint16_t Temp =30;
	uint8_t data[2] = {0};
	uint16_t humi_temp_code;
	I2C_LeaderRead(0x80,0xE5,data,2);
	humi_temp_code = ((uint16_t)(data[0])<<8) + data[1];
	Humi = (uint8_t)(humi_temp_code *125/65536 -6);
	if(Humi >=99)
	{
		Humi = 99;
	}
	I2C_LeaderRead(0x80,0xE3,data,2);
	humi_temp_code = ((uint16_t)(data[0])<<8) + data[1];
	Temp =  (uint8_t)(175.72*humi_temp_code/65536 - 46.85);

	if(count_temp == 5)
	{
		emberAfCorePrintln("Temp = %d oC",Temp);
		count_temp = 0;
	}
	if(count_humi == 10)
	{
		emberAfCorePrintln("Humi = %d %%",Humi);
		count_humi = 0;
	}
	emberEventControlSetInactive(TemHumEventControl);
	emberEventControlSetDelayMS(TemHumEventControl,1000);
}



