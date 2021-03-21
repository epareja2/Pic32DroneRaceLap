/*******************************************************************************
  MPLAB Harmony System Configuration Header

  File Name:
    system_config.h

  Summary:
    Build-time configuration header for the system defined by this MPLAB Harmony
    project.

  Description:
    An MPLAB Project may have multiple configurations.  This file defines the
    build-time options for a single configuration.

  Remarks:
    This configuration header must not define any prototypes or data
    definitions (or include any files that do).  It only provides macro
    definitions for build-time configuration options that are not instantiated
    until used by another MPLAB Harmony module or application.

    Created with MPLAB Harmony Version 2.06
*******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013-2015 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED AS IS WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
*******************************************************************************/
// DOM-IGNORE-END

#ifndef _SYSTEM_CONFIG_H
#define _SYSTEM_CONFIG_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
/*  This section Includes other configuration headers necessary to completely
    define this configuration.
*/
#include "bsp.h"


// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: System Service Configuration
// *****************************************************************************
// *****************************************************************************
// *****************************************************************************
/* Common System Service Configuration Options
*/
#define SYS_VERSION_STR           "2.06"
#define SYS_VERSION               20600

// *****************************************************************************
/* Clock System Service Configuration Options
*/
#define SYS_CLK_FREQ                        120000000ul
#define SYS_CLK_BUS_PERIPHERAL_1            120000000ul
#define SYS_CLK_UPLL_BEFORE_DIV2_FREQ       48000000ul
#define SYS_CLK_CONFIG_PRIMARY_XTAL         20000000ul
#define SYS_CLK_CONFIG_SECONDARY_XTAL       32768ul
   
/*** Ports System Service Configuration ***/
#define SYS_PORT_AD1PCFG        ~0xf
#define SYS_PORT_CNPUE          0x3
#define SYS_PORT_CNEN           0x0
#define SYS_PORT_B_TRIS         0x558F
#define SYS_PORT_B_LAT          0xA030
#define SYS_PORT_B_ODC          0x0000

#define SYS_PORT_C_TRIS         0xFFFF
#define SYS_PORT_C_LAT          0x0000
#define SYS_PORT_C_ODC          0x0000

#define SYS_PORT_D_TRIS         0xF18F
#define SYS_PORT_D_LAT          0x0470
#define SYS_PORT_D_ODC          0x0000

#define SYS_PORT_E_TRIS         0xFFFF
#define SYS_PORT_E_LAT          0x0000
#define SYS_PORT_E_ODC          0x0000

#define SYS_PORT_F_TRIS         0xFFCC
#define SYS_PORT_F_LAT          0x0020
#define SYS_PORT_F_ODC          0x0000

#define SYS_PORT_G_TRIS         0xFC3F
#define SYS_PORT_G_LAT          0x0300
#define SYS_PORT_G_ODC          0x0000


/*** Interrupt System Service Configuration ***/
#define SYS_INT                     true

// *****************************************************************************
// *****************************************************************************
// Section: Driver Configuration
// *****************************************************************************
// *****************************************************************************

/*** SPI Driver Configuration ***/
#define DRV_SPI_NUMBER_OF_MODULES		3
/*** Driver Compilation and static configuration options. ***/
/*** Select SPI compilation units.***/
#define DRV_SPI_POLLED 				0
#define DRV_SPI_ISR 				1
#define DRV_SPI_MASTER 				1
#define DRV_SPI_SLAVE 				0
#define DRV_SPI_RM 					1
#define DRV_SPI_EBM 				0
#define DRV_SPI_8BIT 				1
#define DRV_SPI_16BIT 				0
#define DRV_SPI_32BIT 				0
#define DRV_SPI_DMA 				0

/*** SPI Driver Static Allocation Options ***/
#define DRV_SPI_INSTANCES_NUMBER 		1
#define DRV_SPI_CLIENTS_NUMBER 			3
#define DRV_SPI_ELEMENTS_PER_QUEUE 		10
/* SPI Driver Instance 0 Configuration */
#define DRV_SPI_SPI_ID_IDX0 				SPI_ID_3
#define DRV_SPI_TASK_MODE_IDX0 				DRV_SPI_TASK_MODE_ISR
#define DRV_SPI_SPI_MODE_IDX0				DRV_SPI_MODE_MASTER
#define DRV_SPI_ALLOW_IDLE_RUN_IDX0			true
#define DRV_SPI_SPI_PROTOCOL_TYPE_IDX0 		DRV_SPI_PROTOCOL_TYPE_STANDARD
#define DRV_SPI_COMM_WIDTH_IDX0 			SPI_COMMUNICATION_WIDTH_8BITS
#define DRV_SPI_SPI_CLOCK_IDX0 				CLK_BUS_PERIPHERAL_1
#define DRV_SPI_BAUD_RATE_IDX0 				1000000
#define DRV_SPI_BUFFER_TYPE_IDX0 			DRV_SPI_BUFFER_TYPE_STANDARD
#define DRV_SPI_CLOCK_MODE_IDX0 			DRV_SPI_CLOCK_MODE_IDLE_LOW_EDGE_FALL
#define DRV_SPI_INPUT_PHASE_IDX0 			SPI_INPUT_SAMPLING_PHASE_IN_MIDDLE
#define DRV_SPI_TRANSMIT_DUMMY_BYTE_VALUE_IDX0      0x00

#define DRV_SPI_TX_INT_SOURCE_IDX0 			INT_SOURCE_SPI_3_TRANSMIT
#define DRV_SPI_RX_INT_SOURCE_IDX0 			INT_SOURCE_SPI_3_RECEIVE
#define DRV_SPI_ERROR_INT_SOURCE_IDX0 		INT_SOURCE_SPI_3_ERROR
#define DRV_SPI_INT_VECTOR_IDX0				INT_VECTOR_SPI3
#define DRV_SPI_INT_PRIORITY_IDX0			INT_PRIORITY_LEVEL1
#define DRV_SPI_INT_SUB_PRIORITY_IDX0		INT_SUBPRIORITY_LEVEL0        
#define DRV_SPI_QUEUE_SIZE_IDX0 			10
#define DRV_SPI_RESERVED_JOB_IDX0 			1
/*** Timer Driver Configuration ***/
#define DRV_TMR_INTERRUPT_MODE             true

/*** Timer Driver 0 Configuration ***/
#define DRV_TMR_PERIPHERAL_ID_IDX0          TMR_ID_2
#define DRV_TMR_INTERRUPT_SOURCE_IDX0       INT_SOURCE_TIMER_2
#define DRV_TMR_INTERRUPT_VECTOR_IDX0       INT_VECTOR_T2
#define DRV_TMR_ISR_VECTOR_IDX0             _TIMER_2_VECTOR
#define DRV_TMR_INTERRUPT_PRIORITY_IDX0     INT_PRIORITY_LEVEL3
#define DRV_TMR_INTERRUPT_SUB_PRIORITY_IDX0 INT_SUBPRIORITY_LEVEL0
#define DRV_TMR_CLOCK_SOURCE_IDX0           DRV_TMR_CLKSOURCE_INTERNAL
#define DRV_TMR_PRESCALE_IDX0               TMR_PRESCALE_VALUE_64
#define DRV_TMR_OPERATION_MODE_IDX0         DRV_TMR_OPERATION_MODE_16_BIT
#define DRV_TMR_ASYNC_WRITE_ENABLE_IDX0     false
#define DRV_TMR_POWER_STATE_IDX0            

#define DRV_TMR_PERIPHERAL_ID_IDX1          TMR_ID_3
#define DRV_TMR_INTERRUPT_SOURCE_IDX1       INT_SOURCE_TIMER_3
#define DRV_TMR_INTERRUPT_VECTOR_IDX1       INT_VECTOR_T3
#define DRV_TMR_ISR_VECTOR_IDX1             _TIMER_3_VECTOR
#define DRV_TMR_INTERRUPT_PRIORITY_IDX1     INT_PRIORITY_LEVEL3
#define DRV_TMR_INTERRUPT_SUB_PRIORITY_IDX1 INT_SUBPRIORITY_LEVEL2
#define DRV_TMR_CLOCK_SOURCE_IDX1           DRV_TMR_CLKSOURCE_INTERNAL
#define DRV_TMR_PRESCALE_IDX1               TMR_PRESCALE_VALUE_16
#define DRV_TMR_OPERATION_MODE_IDX1         DRV_TMR_OPERATION_MODE_16_BIT

#define DRV_TMR_ASYNC_WRITE_ENABLE_IDX1     false
#define DRV_TMR_POWER_STATE_IDX1            
/*** Timer Driver 2 Configuration ***/
#define DRV_TMR_PERIPHERAL_ID_IDX2          TMR_ID_1
#define DRV_TMR_INTERRUPT_SOURCE_IDX2       INT_SOURCE_TIMER_1
#define DRV_TMR_INTERRUPT_VECTOR_IDX2       INT_VECTOR_T1
#define DRV_TMR_ISR_VECTOR_IDX2             _TIMER_1_VECTOR
#define DRV_TMR_INTERRUPT_PRIORITY_IDX2     INT_PRIORITY_LEVEL1
#define DRV_TMR_INTERRUPT_SUB_PRIORITY_IDX2 INT_SUBPRIORITY_LEVEL0
#define DRV_TMR_CLOCK_SOURCE_IDX2           DRV_TMR_CLKSOURCE_INTERNAL
#define DRV_TMR_PRESCALE_IDX2               TMR_PRESCALE_VALUE_8
#define DRV_TMR_OPERATION_MODE_IDX2         DRV_TMR_OPERATION_MODE_16_BIT
#define DRV_TMR_ASYNC_WRITE_ENABLE_IDX2     false
#define DRV_TMR_POWER_STATE_IDX2            

 
/*** ADS7843 Touch Driver Configuration ***/

#define DRV_TOUCH_TYPE_RESISTIVE                    true
#define DRV_TOUCH_ADS7843_CALIBRATION_SCALE_FACTOR 8
#define DRV_TOUCH_ADS7843_CALIBRATION_INSET        20

/*** Display resolution configuration  ***/
#define DISP_ORIENTATION        GFX_ORIENTATION_180 // Defined in the Graphic Driver module


#define DISP_HOR_RESOLUTION     240 // Pixels in horizontal position
#define DISP_VER_RESOLUTION     320 // Pixels in horizontal position



// **** Calibration PARAMETERS ***** ///
#define TOUCH_SAMPLE_POINTS               4
#define TOUCH_DIAMETER                    10
#define TOUCH_CALIBRATION_DELAY           300
#define TOUCH_CALIBRATION_SCALE_FACTOR    8
#define TOUCH_PRESS_THRESHOLD             
#define TOUCH_CALIBRATION_DELAY           300


// **** Default Calibration Points : Must be calculated and sstored in NVM ***** ///
#define TOUCHCAL_ULX                             0x00C0
#define TOUCHCAL_ULY                             0x00D4
#define TOUCHCAL_URX                             0x037C
#define TOUCHCAL_URY                             0x00D7
#define TOUCHCAL_LLX                             0x00B9
#define TOUCHCAL_LLY                             0x0350
#define TOUCHCAL_LRX                             0x035A
#define TOUCHCAL_LRY                             0x0333



// *****************************************************************************
/* USART Driver Configuration Options
*/
#define DRV_USART_INTERRUPT_MODE                    true

#define DRV_USART_BYTE_MODEL_SUPPORT                true

#define DRV_USART_READ_WRITE_MODEL_SUPPORT          false

#define DRV_USART_BUFFER_QUEUE_SUPPORT              false

#define DRV_USART_CLIENTS_NUMBER                    1
#define DRV_USART_INSTANCES_NUMBER                  1

#define DRV_USART_PERIPHERAL_ID_IDX0                USART_ID_5
#define DRV_USART_OPER_MODE_IDX0                    DRV_USART_OPERATION_MODE_NORMAL
#define DRV_USART_OPER_MODE_DATA_IDX0               
#define DRV_USART_INIT_FLAG_WAKE_ON_START_IDX0      false
#define DRV_USART_INIT_FLAG_AUTO_BAUD_IDX0          false
#define DRV_USART_INIT_FLAG_STOP_IN_IDLE_IDX0       false
#define DRV_USART_INIT_FLAGS_IDX0                   0
#define DRV_USART_BRG_CLOCK_IDX0                    120000000
#define DRV_USART_BAUD_RATE_IDX0                    57600
#define DRV_USART_LINE_CNTRL_IDX0                   DRV_USART_LINE_CONTROL_8NONE1
#define DRV_USART_HANDSHAKE_MODE_IDX0               DRV_USART_HANDSHAKE_NONE
#define DRV_USART_LINES_ENABLE_IDX0                 USART_ENABLE_TX_RX_USED
#define DRV_USART_XMIT_INT_SRC_IDX0                 INT_SOURCE_USART_5_TRANSMIT
#define DRV_USART_RCV_INT_SRC_IDX0                  INT_SOURCE_USART_5_RECEIVE
#define DRV_USART_ERR_INT_SRC_IDX0                  INT_SOURCE_USART_5_ERROR
#define DRV_USART_INT_VECTOR_IDX0                   INT_VECTOR_UART5
#define DRV_USART_INT_PRIORITY_IDX0                 INT_PRIORITY_LEVEL1
#define DRV_USART_INT_SUB_PRIORITY_IDX0             INT_SUBPRIORITY_LEVEL0


#define DRV_USART_POWER_STATE_IDX0                  SYS_MODULE_POWER_RUN_FULL


// *****************************************************************************
// *****************************************************************************
// Section: Middleware & Other Library Configuration
// *****************************************************************************
// *****************************************************************************

/*** USB Driver Configuration ***/


/* Enables Device Support */
#define DRV_USBFS_DEVICE_SUPPORT      true

/* Disable Host Support */
#define DRV_USBFS_HOST_SUPPORT      false

/* Maximum USB driver instances */
#define DRV_USBFS_INSTANCES_NUMBER    1

/* Interrupt mode Disabled */
#define DRV_USBFS_INTERRUPT_MODE      false


/* Number of Endpoints used */
#define DRV_USBFS_ENDPOINTS_NUMBER    3




/*** USB Device Stack Configuration ***/










/* The USB Device Layer will not initialize the USB Driver */
#define USB_DEVICE_DRIVER_INITIALIZE_EXPLICIT

/* Maximum device layer instances */
#define USB_DEVICE_INSTANCES_NUMBER     1

/* EP0 size in bytes */
#define USB_DEVICE_EP0_BUFFER_SIZE      8

/* Enable SOF Events */ 
#define USB_DEVICE_SOF_EVENT_ENABLE     









/* Maximum instances of CDC function driver */
#define USB_DEVICE_CDC_INSTANCES_NUMBER     1










/* CDC Transfer Queue Size for both read and
   write. Applicable to all instances of the
   function driver */
#define USB_DEVICE_CDC_QUEUE_DEPTH_COMBINED 3



// *****************************************************************************
/* BSP Configuration Options
*/
#define BSP_OSC_FREQUENCY 20000000


// *****************************************************************************
// *****************************************************************************
// Section: Application Configuration
// *****************************************************************************
// *****************************************************************************
/*** Application Defined Pins ***/

/*** Functions for BSP_LED_1 pin ***/
#define BSP_LED_1Toggle() PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_F, PORTS_BIT_POS_0)
#define BSP_LED_1On() PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_F, PORTS_BIT_POS_0)
#define BSP_LED_1Off() PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_F, PORTS_BIT_POS_0)
#define BSP_LED_1StateGet() PLIB_PORTS_PinGetLatched(PORTS_ID_0, PORT_CHANNEL_F, PORTS_BIT_POS_0)

/*** Functions for BSP_LED_2 pin ***/
#define BSP_LED_2Toggle() PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_F, PORTS_BIT_POS_1)
#define BSP_LED_2On() PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_F, PORTS_BIT_POS_1)
#define BSP_LED_2Off() PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_F, PORTS_BIT_POS_1)
#define BSP_LED_2StateGet() PLIB_PORTS_PinGetLatched(PORTS_ID_0, PORT_CHANNEL_F, PORTS_BIT_POS_1)

/*** Functions for BTN2_EXT pin ***/
#define BTN2_EXTStateGet() PLIB_PORTS_PinGet(PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_10)

/*** Functions for BTN3_EXT pin ***/
#define BTN3_EXTStateGet() PLIB_PORTS_PinGet(PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_12)

/*** Functions for BSP_SWITCH_1 pin ***/
#define BSP_SWITCH_1StateGet() PLIB_PORTS_PinGet(PORTS_ID_0, PORT_CHANNEL_C, PORTS_BIT_POS_13)

/*** Functions for BSP_SWITCH_2 pin ***/
#define BSP_SWITCH_2StateGet() PLIB_PORTS_PinGet(PORTS_ID_0, PORT_CHANNEL_C, PORTS_BIT_POS_14)

/*** Functions for DATA_5808_temp pin ***/
#define DATA_5808_tempToggle() PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_9)
#define DATA_5808_tempOn() PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_9)
#define DATA_5808_tempOff() PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_9)
#define DATA_5808_tempStateGet() PLIB_PORTS_PinGetLatched(PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_9)
#define DATA_5808_tempStateSet(Value) PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_9, Value)

/*** Functions for BUZZ pin ***/
#define BUZZToggle() PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_4)
#define BUZZOn() PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_4)
#define BUZZOff() PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_4)
#define BUZZStateGet() PLIB_PORTS_PinGetLatched(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_4)
#define BUZZStateSet(Value) PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_4, Value)

/*** Functions for CS_TOUCH pin ***/
#define CS_TOUCHToggle() PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_5)
#define CS_TOUCHOn() PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_5)
#define CS_TOUCHOff() PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_5)
#define CS_TOUCHStateGet() PLIB_PORTS_PinGetLatched(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_5)
#define CS_TOUCHStateSet(Value) PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_5, Value)

/*** Functions for CS_EEPROM pin ***/
#define CS_EEPROMToggle() PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_6)
#define CS_EEPROMOn() PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_6)
#define CS_EEPROMOff() PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_6)
#define CS_EEPROMStateGet() PLIB_PORTS_PinGetLatched(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_6)
#define CS_EEPROMStateSet(Value) PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_6, Value)

/*** Functions for T_BUSY pin ***/
#define T_BUSYStateGet() PLIB_PORTS_PinGet(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_7)


/*** Audio Decoders Configuration ***/

/* Customize buffer size depends on device SRAM */
#define DECODER_MAX_INPUT_BUFFER_SIZE (1024*7)
#define DECODER_MAX_OUTPUT_BUFFER_SIZE (1024*7)


/*** Application Instance 0 Configuration ***/

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif // _SYSTEM_CONFIG_H
/*******************************************************************************
 End of File
*/
