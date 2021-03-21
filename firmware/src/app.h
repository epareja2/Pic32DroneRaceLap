/*******************************************************************************
  MPLAB Harmony Application Header File

  Company:
    Microchip Technology Inc.

  File Name:
    app.h

  Summary:
    This header file provides prototypes and definitions for the application.

  Description:
    This header file provides function prototypes and data type definitions for
    the application.  Some of these are required by the system (such as the
    "APP_Initialize" and "APP_Tasks" prototypes) and some of them are only used
    internally by the application (such as the "APP_STATES" definition).  Both
    are defined here for convenience.
*******************************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013-2014 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
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
//DOM-IGNORE-END

#ifndef _APP_H
#define _APP_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "system_config.h"
#include "system_definitions.h"
#include "gfx/libaria/inc/libaria_screen.h"
#include "UsarSimpleBuffer.h"
#include "RaceDetection.h"



// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif
// DOM-IGNORE-END 

#define GET_TICKS()       _CP0_GET_COUNT()
#define _1SEG_TICKS      (SYS_CLK_FREQ*1.0/2)
#define _1mSEG_TICKS     (SYS_CLK_FREQ*1.0/2)/1000
#define _1uSEG_TICKS     (SYS_CLK_FREQ*1.0/2)/1000000
  
// *****************************************************************************
// *****************************************************************************
// Section: Type Definitions
// *****************************************************************************
// *****************************************************************************
#define MAX_NUM_OF_USART_BYTES        8
#define MAX_NUM_OF_USART_BYTES_IN_BUF (MAX_NUM_OF_USART_BYTES + 4)

 
// *****************************************************************************
// *****************************************************************************
// Section: Type Definitions
// *****************************************************************************
// *****************************************************************************

/* Available screens of the APP*/
typedef enum {
  APP_CALIBRATE_TOUCH,
  APP_MAIN_SCREEN,
} APP_SCREENS;
  
typedef enum
{
	/* Application's state machine's initial state. */
	APP_STATE_INIT=0,
	APP_STATE_SERVICE_TASKS,
//  APP_EEPROM_WRITE_WAIT,
//  APP_EEPROM_READ_WAIT,
  APP_EEPROM_READ_CONFIG_PILOT,
  APP_PROGRAM_RX5808_MODULES,
  APP_READ_RACE_CONFIG_DATA,
    
  /* TODO: Define states used by the application state machine. */
  /* Application waits for device configuration*/
  APP_STATE_WAIT_FOR_CONFIGURATION,

  /* Check if we got data from CDC */
  APP_STATE_CHECK_CDC_READ,

  /* A character is received from the UART */
  APP_STATE_CHECK_UART_RECEIVE,

  /* Application Error state*/
  APP_STATE_ERROR

} APP_STATES;

typedef enum {
  CDC_WAIT_FOR_STARTUP =0,
  CDC_STATE_INIT,
  CDC_WAIT_FOR_CONFIGURATION,
  CDC_SCHEDULE_READ,
  CDC_WAIT_FOR_READ_COMPLETE,
  CDC_SCHEDULE_WRITE,
  CDC_WAIT_FOR_WRITE_COMPLETE,
  CDC_STATE_ERROR,
} CDC_STATES;

typedef enum{
  USART_STATE_INIT,
  USART_STATE_SENDING_DATA,
  USART_STATE_WAIT_RX,
  USART_STATE_WATING_TO_SEND,
  USART_STATE_IDLE,
  USART_STATE_SET_RX,
  USART_STATE_SET_TX,
  USART_STATE_WAIT_FOR_TX_COMPLETION,
    
} USART_STATES;
// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    Application strings and buffers are be defined outside this structure.
 */

typedef struct
{
    /* The application's current state */
    APP_STATES state;
    APP_SCREENS screen;
    uint16_t BeepTimer;
    CDC_STATES cdc_state;
    USART_STATES usart1State;
    /* TODO: Define any additional data used by the application. */
    uint16_t KeyDebounce;

    /* Device layer handle returned by device layer open function */
    USB_DEVICE_HANDLE deviceHandle;

    /* Application CDC Instance */
    USB_DEVICE_CDC_INDEX cdcInstance;

    /* Application USART Driver handle */
    DRV_HANDLE usartHandle;
    
    /* Simle USAR Buffer for ByteModel*/
    USART_SIMPLE_BUFF usartRxSimpleBuff;
    USART_SIMPLE_BUFF usartTxSimpleBuff;

    /* Device configured state */
    bool isConfigured;

    /* Application CDC read buffer */
    uint8_t * readBuffer;

    /* Set Line Coding Data */
    USB_CDC_LINE_CODING setLineCodingData;

    /* Get Line Coding Data */
    USB_CDC_LINE_CODING getLineCodingData;

    /* Control Line State */
    USB_CDC_CONTROL_LINE_STATE controlLineStateData;

    /* Break data */
    uint16_t breakData;

    /* Read transfer handle */
    USB_DEVICE_CDC_TRANSFER_HANDLE readTransferHandle;

    /* Write transfer handle */
    USB_DEVICE_CDC_TRANSFER_HANDLE writeTransferHandle;

    /* True if a character was read */
    bool isReadComplete;

    /* True if a character was written*/
    bool isWriteComplete;
    /* Write buffer handle */
    DRV_USART_BUFFER_HANDLE   drvUsartTxBufHandle;

    /* Read buffer handle */
    DRV_USART_BUFFER_HANDLE   drvUsartRxBufHandle;

    /* UART1 TX buffer  */
    uint8_t  drvUsartTxBuffer[MAX_NUM_OF_USART_BYTES_IN_BUF];

    /* UART1 RX buffer  */
    uint8_t  drvUsartRxBuffer[MAX_NUM_OF_USART_BYTES_IN_BUF];
    
    
    /* UART2 received data */
    uint8_t * uartReceivedData;

    /* Read Buffer Length*/
    size_t readLength;

    /* Number of bytes read from Host */ 
    uint32_t numBytesRead; 

    /* Current UART TX Count*/
    size_t uartTxCount;
    
    /* This flag is uses to check if Host has requested to change baudrate*/
    bool isBaudrateDataReceived;
    
    /* This flag used to check if the Set Line coding command is in progress */
    bool isSetLineCodingCommandInProgress; 

    /* True is switch was pressed */
    bool isSwitchPressed;
    
// Specific application variables
    bool  isPilotDataLoaded; // Cargó los datos de piloto de eeprom
    
    //Time base for all the routines
    uint32_t mSeg;

} APP_DATA;




// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Routines
// *****************************************************************************
// *****************************************************************************
/* These routines are called by drivers when certain events occur.
*/
	
// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_Initialize ( void )

  Summary:
     MPLAB Harmony application initialization routine.

  Description:
    This function initializes the Harmony application.  It places the 
    application in its initial state and prepares it to run so that its 
    APP_Tasks function can be called.

  Precondition:
    All other system initialization routines should be called before calling
    this routine (in "SYS_Initialize").

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    APP_Initialize();
    </code>

  Remarks:
    This routine must be called from the SYS_Initialize function.
*/

void APP_Initialize ( void );


/*******************************************************************************
  Function:
    void APP_Tasks ( void )

  Summary:
    MPLAB Harmony Demo application tasks function

  Description:
    This routine is the Harmony Demo application's tasks function.  It
    defines the application's state machine and core logic.

  Precondition:
    The system and application initialization ("SYS_Initialize") should be
    called before calling this.

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    APP_Tasks();
    </code>

  Remarks:
    This routine must be called from SYS_Tasks() routine.
 */
void APP_RTOS_Tasks (void);
void APP_Tasks( void );
void USART_Send_string(void);


#endif /* _APP_H */

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

/*******************************************************************************
 End of File
 */

