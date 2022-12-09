/*
 * ldr.h
 *
 *  Created on: Apr 11, 2022
 *      Author: Dung
 */

#ifndef MIDDLE_LDR_LDR_H_
#define MIDDLE_LDR_LDR_H_

/******************************************************************************/
/*                              INCLUDE FILES                                 */
/******************************************************************************/
#include <stdint.h>

/******************************************************************************/
/*                     EXPORTED TYPES and DEFINITIONS                         */
/******************************************************************************/

#define NUM_SAMPLES                 10

// Set CLK_ADC to 10MHz
#define CLK_SRC_ADC_FREQ			20000000 // CLK_SRC_ADC
#define CLK_ADC_FREQ                10000000 // CLK_ADC - 10MHz max in normal mode

#define IADC_INPUT_0_PORT_PIN    	 iadcPosInputPortCPin5;

#define IADC_INPUT_0_BUS         	 CDBUSALLOC
#define IADC_INPUT_0_BUSALLOC     	 GPIO_CDBUSALLOC_CDEVEN0_ADC0
#define IADC_INPUT_1_BUS         	 CDBUSALLOC
#define IADC_INPUT_1_BUSALLOC    	 GPIO_CDBUSALLOC_CDODD0_ADC0

#define IADC_SCALE_OFFSET_MAX_NEG  	 0x00020000UL // 18-bit 2's compliment
#define IADC_SCALE_OFFSET_ZERO    	 0x00000000UL

// Push-buttons are active-low
#define PB_PRESSED (0)

/******************************************************************************/
/*                              PRIVATE DATA                                  */
/******************************************************************************/

/******************************************************************************/
/*                              EXPORTED DATA                                 */
/******************************************************************************/
/******************************************************************************/
/*                            EXPORTED FUNCTIONS                              */
/******************************************************************************/


/**
 * @func   LDRInit
 * @brief  Initializes module light sensor
 * @param  None
 * @retval None
 */
void LDRInit();

/**
 * @func   LightSensor_MeasureUseDMAMode
 * @brief  Measure value ADC in mode DMA
 * @param  None
 * @retval Value of ADC
 */

uint16_t IADCAverageConversion(uint32_t numSamples);


/**
 * @func   LightSensor_Init
 * @brief  Initializes module light sensor
 * @param  None
 * @retval None
 */
void LightSensor_Init();


#endif /* MIDDLE_LDR_LDR_H_ */
