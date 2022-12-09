/*
 * main.h
 *
 *  Created on: Mar 15, 2022
 *      Author: dungpk
 */

#ifndef SOURCE_APP_MAIN_MAIN_H_
#define SOURCE_APP_MAIN_MAIN_H_
#define LED_ON									1
#define LED_OFF									0
#define PERIOD_SCAN_SENSORLIGHT					5000 	//	ms
#define PERIOD_SCAN_SENSORTEMHUMI				10000	//	ms
typedef enum{
	POWER_ON_STATE,
	REPORT_STATE,
	IDLE_STATE,
	REBOOT_STATE
}systemState;

#endif /* SOURCE_APP_MAIN_MAIN_H_ */
