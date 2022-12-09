#ifndef HAL_CONFIG_H
#define HAL_CONFIG_H

#include "em_device.h"
#include "hal-config-types.h"

// This file is auto-generated by Hardware Configurator in Simplicity Studio.
// Any content between $[ and ]$ will be replaced whenever the file is regenerated.
// Content outside these regions will be preserved.

// $[ACMP0]
// [ACMP0]$

// $[ACMP1]
// [ACMP1]$

// $[ANTDIV]
// [ANTDIV]$

// $[BTL_BUTTON]
// [BTL_BUTTON]$

// $[BUTTON]
// [BUTTON]$

// $[CMU]
#define HAL_CLK_HFCLK_SOURCE                  (HAL_CLK_HFCLK_SOURCE_HFXO)
#define HAL_CLK_PLL_CONFIGURATION             (HAL_CLK_PLL_CONFIGURATION_40MHZ)
#define HAL_CLK_EM01CLK_SOURCE                (HAL_CLK_HFCLK_SOURCE_HFRCODPLL)
#define HAL_CLK_EM23CLK_SOURCE                (HAL_CLK_LFCLK_SOURCE_LFRCO)
#define HAL_CLK_EM4CLK_SOURCE                 (HAL_CLK_LFCLK_SOURCE_LFRCO)
#define HAL_CLK_RTCCCLK_SOURCE                (HAL_CLK_LFCLK_SOURCE_LFRCO)
#define HAL_CLK_WDOGCLK_SOURCE                (HAL_CLK_LFCLK_SOURCE_LFRCO)
#define BSP_CLK_HFXO_PRESENT                  (1)
#define BSP_CLK_HFXO_FREQ                     (38400000UL)
#define BSP_CLK_HFXO_INIT                      CMU_HFXOINIT_DEFAULT
#define BSP_CLK_HFXO_CTUNE                    (-1)
#define BSP_CLK_LFXO_PRESENT                  (0)
#define BSP_CLK_LFXO_INIT                      CMU_LFXOINIT_DEFAULT
#define BSP_CLK_LFXO_FREQ                     (32768U)
#define BSP_CLK_LFXO_CTUNE                    (0U)
// [CMU]$

// $[COEX]
// [COEX]$

// $[EMU]
// [EMU]$

// $[EXTFLASH]
// [EXTFLASH]$

// $[EZRADIOPRO]
// [EZRADIOPRO]$

// $[FEM]
// [FEM]$

// $[GPIO]
// [GPIO]$

// $[I2C0]
// [I2C0]$

// $[I2C1]
// [I2C1]$

// $[I2CSENSOR]
// [I2CSENSOR]$

// $[IADC0]
// [IADC0]$

// $[IOEXP]
// [IOEXP]$

// $[LED]
// [LED]$

// $[LETIMER0]
// [LETIMER0]$

// $[LFXO]
// [LFXO]$

// $[MODEM]
// [MODEM]$

// $[PA]
#define HAL_PA_ENABLE                         (1)

#define HAL_PA_CURVE_HEADER                    "pa_curves_efr32.h"
#define HAL_PA_POWER                          (252U)
#define HAL_PA_RAMP                           (10UL)
#define BSP_PA_VOLTAGE                        (1000U)
#define HAL_PA_SELECTION                      (HAL_PA_SELECTION_2P4_MP)
// [PA]$

// $[PORTIO]
// [PORTIO]$

// $[PRS]
// [PRS]$

// $[PTI]
// [PTI]$

// $[SERIAL]
#define BSP_SERIAL_APP_PORT                   (HAL_SERIAL_PORT_USART0)
#define HAL_SERIAL_RXWAKE_ENABLE              (0)
#define HAL_SERIAL_IDLE_WAKE_ENABLE           (1)
#define HAL_SERIAL_USART0_ENABLE              (1)
#define HAL_SERIAL_USART1_ENABLE              (0)
#define HAL_SERIAL_USART2_ENABLE              (0)
#define BSP_SERIAL_APP_TX_PIN                 (5U)
#define BSP_SERIAL_APP_TX_PORT                (gpioPortA)

#define BSP_SERIAL_APP_RX_PIN                 (6U)
#define BSP_SERIAL_APP_RX_PORT                (gpioPortA)

#define BSP_SERIAL_APP_CTS_PIN                (2U)
#define BSP_SERIAL_APP_CTS_PORT               (gpioPortA)

#define BSP_SERIAL_APP_RTS_PIN                (3U)
#define BSP_SERIAL_APP_RTS_PORT               (gpioPortA)

#define HAL_SERIAL_APP_BAUD_RATE              (115200UL)
#define HAL_SERIAL_APP_FLOW_CONTROL           (HAL_USART_FLOW_CONTROL_NONE)
#define HAL_SERIAL_APP_RXSTOP                 (16UL)
#define HAL_SERIAL_APP_RXSTART                (16UL)
#define HAL_SERIAL_APP_TX_QUEUE_SIZE          (128UL)
#define HAL_SERIAL_APP_RX_QUEUE_SIZE          (128UL)
// [SERIAL]$

// $[SPIDISPLAY]
// [SPIDISPLAY]$

// $[SPINCP]
// [SPINCP]$

// $[TIMER0]
// [TIMER0]$

// $[TIMER1]
// [TIMER1]$

// $[TIMER2]
// [TIMER2]$

// $[TIMER3]
// [TIMER3]$

// $[UARTNCP]
#define BSP_UARTNCP_USART_PORT                (HAL_SERIAL_PORT_USART0)
#define BSP_UARTNCP_TX_PIN                    (5U)
#define BSP_UARTNCP_TX_PORT                   (gpioPortA)

#define BSP_UARTNCP_RX_PIN                    (6U)
#define BSP_UARTNCP_RX_PORT                   (gpioPortA)

#define BSP_UARTNCP_CTS_PIN                   (2U)
#define BSP_UARTNCP_CTS_PORT                  (gpioPortA)

#define BSP_UARTNCP_RTS_PIN                   (3U)
#define BSP_UARTNCP_RTS_PORT                  (gpioPortA)

#define HAL_UARTNCP_BAUD_RATE                 (115200UL)
#define HAL_UARTNCP_FLOW_CONTROL              (HAL_USART_FLOW_CONTROL_NONE)
#define HAL_UARTNCP_RXSTOP                    (16UL)
#define HAL_UARTNCP_RXSTART                   (16UL)
#define HAL_UARTNCP_TX_QUEUE_SIZE             (128UL)
#define HAL_UARTNCP_RX_QUEUE_SIZE             (128UL)
// [UARTNCP]$

// $[USART0]
#define PORTIO_USART0_CTS_PIN                 (2U)
#define PORTIO_USART0_CTS_PORT                (gpioPortA)

#define PORTIO_USART0_RTS_PIN                 (3U)
#define PORTIO_USART0_RTS_PORT                (gpioPortA)

#define PORTIO_USART0_RX_PIN                  (6U)
#define PORTIO_USART0_RX_PORT                 (gpioPortA)

#define PORTIO_USART0_TX_PIN                  (5U)
#define PORTIO_USART0_TX_PORT                 (gpioPortA)

#define HAL_USART0_ENABLE                     (1)

#define BSP_USART0_TX_PIN                     (5U)
#define BSP_USART0_TX_PORT                    (gpioPortA)

#define BSP_USART0_RX_PIN                     (6U)
#define BSP_USART0_RX_PORT                    (gpioPortA)

#define BSP_USART0_CTS_PIN                    (2U)
#define BSP_USART0_CTS_PORT                   (gpioPortA)

#define BSP_USART0_RTS_PIN                    (3U)
#define BSP_USART0_RTS_PORT                   (gpioPortA)

#define HAL_USART0_BAUD_RATE                  (115200UL)
#define HAL_USART0_FLOW_CONTROL               (HAL_USART_FLOW_CONTROL_NONE)
#define HAL_USART0_RXSTOP                     (16UL)
#define HAL_USART0_RXSTART                    (16UL)
#define HAL_USART0_TX_QUEUE_SIZE              (128UL)
#define HAL_USART0_RX_QUEUE_SIZE              (128UL)
// [USART0]$

// $[USART1]
// [USART1]$

// $[USART2]
// [USART2]$

// $[VCOM]
#define HAL_VCOM_ENABLE                       (1)

#define BSP_VCOM_ENABLE_PIN                   (0U)
#define BSP_VCOM_ENABLE_PORT                  (gpioPortA)

// [VCOM]$

// $[VUART]
#define HAL_SERIAL_VUART_ENABLE               (1)

#define HAL_VUART_TYPE                        (HAL_VUART_TYPE_SWO)
// [VUART]$

// $[WDOG]
#define HAL_WDOG_ENABLE                       (1)

// [WDOG]$

#if defined(_SILICON_LABS_MODULE)
#include "sl_module.h"
#endif

#endif /* HAL_CONFIG_H */

