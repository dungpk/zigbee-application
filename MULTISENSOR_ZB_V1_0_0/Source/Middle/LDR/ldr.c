/*
 * lrd.c
 *
 *  Created on: Apr 7, 2022
 *      Author: Dung
 */

/******************************************************************************/
/******************************************************************************/
/*                              INCLUDE FILES                                 */
/******************************************************************************/

#include "app/framework/include/af.h"
#include <stdio.h>
#include "em_device.h"
#include "em_chip.h"
#include "em_cmu.h"
#include "em_iadc.h"
#include "em_gpio.h"
#include "em_ldma.h"
#include "bsp.h"
#include "ldr.h"
#include "string.h"
#include <stdint.h>
#include "Source/Middle/kalman_filter/kalman_filter.h"


/******************************************************************************/
/*                     EXPORTED TYPES and DEFINITIONS                         */
/******************************************************************************/
/******************************************************************************/
/*                              PRIVATE DATA                                  */
/******************************************************************************/
static char src3[20]= "";
EmberEventControl ldrEventControl;

/******************************************************************************/
/*                              EXPORTED DATA                                 */
/******************************************************************************/


/******************************************************************************/
/*                            PRIVATE FUNCTIONS                               */
/******************************************************************************/


void LDRInit(void);
uint16_t IADCAverageConversion(uint32_t numSamples);
void IADCRescale(uint32_t newScale);
void LightSensor_Init();


/******************************************************************************/
/*                            EXPORTED FUNCTIONS                              */
/******************************************************************************/

/**
 * @func   LDRInit
 * @brief  Initializes module light sensor
 * @param  None
 * @retval None
 */
void LDRInit()
{

	  // Declare init structs
	  IADC_Init_t init = IADC_INIT_DEFAULT;
	  IADC_AllConfigs_t initAllConfigs = IADC_ALLCONFIGS_DEFAULT;
	  IADC_InitSingle_t initSingle = IADC_INITSINGLE_DEFAULT;
	  IADC_SingleInput_t initSingleInput = IADC_SINGLEINPUT_DEFAULT;

	  // Enable IADC0 clock branch
	  CMU_ClockEnable(cmuClock_IADC0, true);

	  // Select clock for IADC
	  CMU_ClockSelectSet(cmuClock_IADCCLK, cmuSelect_FSRCO);  // FSRCO - 20MHz

	  // Modify init structs and initialize
	  init.warmup = iadcWarmupKeepWarm;

	  // Set the HFSCLK prescale value here
	  init.srcClkPrescale = IADC_calcSrcClkPrescale(IADC0,CLK_SRC_ADC_FREQ, 0);

	  // Configuration 0 is used by both scan and single conversions by default
	  // Use unbuffered AVDD as reference
	  initAllConfigs.configs[0].reference = iadcCfgReferenceVddx;
	  initAllConfigs.configs[0].vRef = 3300;

	  // Divides CLK_SRC_ADC to set the CLK_ADC frequency
	  initAllConfigs.configs[0].adcClkPrescale = IADC_calcAdcClkPrescale(IADC0,
	                                             CLK_ADC_FREQ,
	                                             0,
	                                             iadcCfgModeNormal,
	                                             init.srcClkPrescale);

	  initAllConfigs.configs[0].twosComplement = iadcCfgTwosCompBipolar; // Force IADC to use bipolar inputs for conversion

	  // Assign pins to positive and negative inputs in differential mode
	  initSingleInput.posInput   = IADC_INPUT_0_PORT_PIN;

	  // Initialize the IADC
	  IADC_init(IADC0, &init, &initAllConfigs);

	  // Initialize the Single conversion inputs
	  IADC_initSingle(IADC0, &initSingle, &initSingleInput);

	  // Allocate the analog bus for ADC0 inputs
	  GPIO->IADC_INPUT_0_BUS |= IADC_INPUT_0_BUSALLOC;
	  GPIO->IADC_INPUT_1_BUS |= IADC_INPUT_1_BUSALLOC;
}

/**
 * @func   LightSensor_MeasureUseDMAMode
 * @brief  Measure value ADC in mode DMA
 * @param  None
 * @retval Value of ADC
 */

uint16_t IADCAverageConversion(uint32_t numSamples)
{
	uint8_t i;
    double average;
    IADC_Result_t sample;

    // Averaging loop
    average = 0; // reset accumulator
    for(i = 0; i < numSamples; i++)
    {
      // Start IADC conversion
      IADC_command(IADC0, iadcCmdStartSingle);

      // Wait for conversion to be complete
      while((IADC0->STATUS & (_IADC_STATUS_CONVERTING_MASK
                  | _IADC_STATUS_SINGLEFIFODV_MASK)) != IADC_STATUS_SINGLEFIFODV); //while combined status bits 8 & 6 don't equal 1 and 0 respectively

      // Get ADC result
      sample = IADC_pullSingleFifoResult(IADC0);
      average += (int32_t) sample.data;
    }
    average /= NUM_SAMPLES;

    // turn off indicator LED

    return average;
}

/**************************************************************************//**
 * @brief  IADC must be disabled to change scale
 *****************************************************************************/
void IADCRescale(uint32_t newScale)
{
    // Disable the IADC
    IADC0->EN_CLR = IADC_EN_EN;

    // configure new scale settings
    IADC0->CFG[0].SCALE = newScale;

    // Re-enable IADC
    IADC0->EN_SET = IADC_EN_EN;
}


/******************************************
 * Hàm cấu hình adc đọc giá trị ánh sáng **
 ******************************************/
void LightSensor_Init(void)
{
	LDRInit(); //Hàm cấu hình và khởi tạo LDR
	KalmanFilterInit(2,2,0.001); // Hàm khởi tạo bộ lọc kanmal với tham số là _err_measure,err_estimate và _q
	emberEventControlSetActive(ldrEventControl); //Cho phép sự kiện hoạt động
}

/**********************************
 * Hàm xử lý để đo ánh sáng********
 *********************************/
void ldrEventHandle(void)
{
	uint16_t Light = 30; //Khởi tạo biến giá trị ánh sáng
	Light = IADCAverageConversion(NUM_SAMPLES); //Đo giá trị ánh sáng
	for(int i=0;i<5;i++) // Lọc qua bộ lọc kalman
	{
		Light = KalmanFilter_updateEstimate(Light); //Giá trị khi qua bộ lọc
	}
	memset(src3,0,sizeof(src3));
	sprintf(src3,"Light = %d lux",Light);//ép kiểu giá trị thành chuỗi
	emberEventControlSetInactive(ldrEventControl);//tắt sự kiện
	emberAfCorePrintln(src3);//In chuỗi lưu giá trị của ánh sáng
	emberEventControlSetDelayMS(ldrEventControl,1000);//cho phép sự kiện hiển thị ánh sáng hoạt động
}



