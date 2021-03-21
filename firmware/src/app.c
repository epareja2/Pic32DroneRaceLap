/*******************************************************************************
  MPLAB Harmony Application Source File
  
  Company:
    Microchip Technology Inc.
  
  File Name:
    app.c

  Summary:
    This file contains the source code for the MPLAB Harmony a pplication.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It 
    implements the logic of the application's state machine and it may call 
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called.  That is the responsibility of the configuration-specific system
    files.
 *******************************************************************************/

#include "system_config.h"


#include "bsp.h"


// DOM-IGNORE-BEGIN
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
// DOM-IGNORE-END


// *****************************************************************************
// *****************************************************************************
// Section: Included Files 
// *****************************************************************************
// *****************************************************************************

#include "app.h"
#include <string.h>
#include "driver/tmr/drv_tmr_static.h"
#include "gfx/libaria/inc/libaria_context.h"
#include "gfx/libaria/inc/libaria_string.h"
#include "gfx/libaria/libaria_init.h"
#include "drv_spi.h"
#include "driver/eeprom/SPI_EEprom_Drv.h"
#include "ScreenTasks/TouchWnd.h"
#include "ConfigPilotModuleWnd.h"
#include "ConfigRaceLevelsWnd.h"
#include "ScreenTasks/ConfigRaceThrLevelsWnd.h"
#include "ScreenTasks/RaceStartWnd.h"
#include "EEProm_Address.h"
#include "RX5808.h"
#include "Utils.h"
#include "Beep.h"
#include "TunesLib.h"
#include "RaceDetection.h"
#include "UsartSimpleBuffer.h"
#include "ScreenTasks/WiFiTestWnd.h"



// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************
const uint8_t __attribute__((aligned(16))) switchPromptUSB[] = "\r\nEL BOTON FUE PRESIONADO";

// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the APP_Initialize function.
    
    Application strings and buffers are be defined outside this structure.
*/
#define APP_MAKE_BUFFER_DMA_READY  
#define APP_READ_BUFFER_SIZE 64 // MAx USB CDC serial buffer size and USART

APP_DATA appData;
static char charBuff[30];
uint8_t APP_MAKE_BUFFER_DMA_READY readBuffer[APP_READ_BUFFER_SIZE] ;
uint8_t APP_MAKE_BUFFER_DMA_READY uartReceivedData;
//static const uint16_t  TuneArray[21] = {C3, D3, E3, F3, G3, A3, B3, C4, D4, E4, F4, G4, A4 , B4, C5, D5, E5, F5, G5, A5, B5};
//static const uint16_t   TuneDelay[21] = {1, 1,  1,  1,  1,  1,   1,  1,  1, 1 , 1 , 1 , 1 ,   1,  1, 1 ,  1, 1,  1,  1,  1 };
bool TuneSwitch =true;



// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

/* TODO:  Add any necessary callback functions.
*/

void EndEEPROMWriteCallback(uint16_t nReadBytes );
void EndEEPROMReadCallback(uint16_t nReadBytes );
//void APP_BufferEventHandlerUsart(DRV_USART_BUFFER_EVENT buffEvent,
//                            DRV_USART_BUFFER_HANDLE hBuffer,
//                            uintptr_t context );
void APP_USARTReceiveEventHandler(const SYS_MODULE_INDEX index);
void APP_USARTTransmitEventHandler(const SYS_MODULE_INDEX index);
void APP_USARTErrorEventHandler(const SYS_MODULE_INDEX index);
void OnTouchCalibrationLoad(uint16_t nReadBytes );
void USART_RXBufferComplete(uint8_t nbytes);
void APP_CDC_Tasks(void);
void APP_USART_Task( void );


  
// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************


/* TODO:  Add any necessary local functions.
*/


// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************


/*******************************************************************************
  Function:
    void APP_Initialize ( void )

  Remarks:
    See prototype in app.h.
 */
void APP_Initialize ( void ) {
  volatile size;
  volatile Addr;
  /* Place the App state machine in its initial state. */
  appData.state = APP_STATE_INIT;
  appData.cdc_state = CDC_WAIT_FOR_STARTUP;
  appData.usart1State = USART_STATE_INIT;
  appData.KeyDebounce = 0;
  appData.mSeg = 0;
  appData.isPilotDataLoaded = false;
  SPI_EEPROM_Init();
  SPI_EEPROM_drv_Open(DRV_SPI_INDEX_0);
//    memset(&charBuff[0],0,30);
  size = sizeof(DRV_ASD7843_CALIBRATION_MATRIX);
  Addr = ADDR_TOUCH_MATRIX_CALIB_INIT;
  SPI_EEPROM_InitRead(&charBuff[0], Addr, size ,&OnTouchCalibrationLoad);
  PilotDataInit(); // Load from EEPROM the PilotData
  TouchWndInitialize();
  ConfigPilotWnd_Initialize();
  ConfigRaceLevelsWndInitialize();
  ConfigRaceThrLevelsWndInitialize();
  RaceStartWnd_Initialize();
  RaceParamWnd_Initialize();
  WiFiTestWnd_Initialize();

  BeepInitialize();

  RX5808_Setup(); // Initialize the RX5808 unit
  
  /* Device Layer Handle  */
  appData.deviceHandle = USB_DEVICE_HANDLE_INVALID;

  /* USART Driver Handle */
  appData.usartHandle = DRV_HANDLE_INVALID;

  /* CDC Instance index for this app object00*/
  appData.cdcInstance = USB_DEVICE_CDC_INDEX_0;

  /* device configured status */
  appData.isConfigured = false;

  /* Initial get line coding state */
  appData.getLineCodingData.dwDTERate = 9600;
  appData.getLineCodingData.bDataBits = 8;
  appData.getLineCodingData.bParityType = 0;
  appData.getLineCodingData.bCharFormat = 0;

  /* Read Transfer Handle */
  appData.readTransferHandle = USB_DEVICE_CDC_TRANSFER_HANDLE_INVALID;

  /* Write Transfer Handle */
  appData.writeTransferHandle = USB_DEVICE_CDC_TRANSFER_HANDLE_INVALID;

  /* Intialize the read complete flag */
  appData.isReadComplete = true;

  /*Initialize the write complete flag*/
  appData.isWriteComplete = true;

  /*Initialize the buffer pointers */
  appData.readBuffer = &readBuffer[0];

  appData.uartReceivedData = &uartReceivedData;

  appData.uartTxCount = 0;

  /* Initialize the Set Line coding flags */
  appData.isBaudrateDataReceived = false; 
  appData.isSetLineCodingCommandInProgress = false;   
}


/*******************************************************
 * USB CDC Device Events - Application Event Handler
 *******************************************************/

USB_DEVICE_CDC_EVENT_RESPONSE APP_USBDeviceCDCEventHandler
(
    USB_DEVICE_CDC_INDEX index ,
    USB_DEVICE_CDC_EVENT event ,
    void * pData,
    uintptr_t userData
)
{
    APP_DATA * appDataObject;
    appDataObject = (APP_DATA *)userData;
    USB_CDC_CONTROL_LINE_STATE * controlLineStateData;
    USB_DEVICE_CDC_EVENT_DATA_READ_COMPLETE * eventDataRead; 
    
    switch ( event )
    {
        case USB_DEVICE_CDC_EVENT_GET_LINE_CODING:

            /* This means the host wants to know the current line
             * coding. This is a control transfer request. Use the
             * USB_DEVICE_ControlSend() function to send the data to
             * host.  */

             USB_DEVICE_ControlSend(appDataObject->deviceHandle,
                    &appDataObject->getLineCodingData, sizeof(USB_CDC_LINE_CODING));

            break;

        case USB_DEVICE_CDC_EVENT_SET_LINE_CODING:

            /* This means the host wants to set the line coding.
             * This is a control transfer request. Use the
             * USB_DEVICE_ControlReceive() function to receive the
             * data from the host */
            appData.isSetLineCodingCommandInProgress = true; 
            appData.isBaudrateDataReceived = false; 
            USB_DEVICE_ControlReceive(appDataObject->deviceHandle,
                    &appDataObject->setLineCodingData, sizeof(USB_CDC_LINE_CODING));

            break;

        case USB_DEVICE_CDC_EVENT_SET_CONTROL_LINE_STATE:

            /* This means the host is setting the control line state.
             * Read the control line state. We will accept this request
             * for now. */

            controlLineStateData = (USB_CDC_CONTROL_LINE_STATE *)pData;
            appDataObject->controlLineStateData.dtr = controlLineStateData->dtr;
            appDataObject->controlLineStateData.carrier = controlLineStateData->carrier;

            USB_DEVICE_ControlStatus(appDataObject->deviceHandle, USB_DEVICE_CONTROL_STATUS_OK);

            break;

        case USB_DEVICE_CDC_EVENT_SEND_BREAK:

            /* This means that the host is requesting that a break of the
             * specified duration be sent. Read the break duration */

            appDataObject->breakData = ((USB_DEVICE_CDC_EVENT_DATA_SEND_BREAK *)pData)->breakDuration;
            
            /* Complete the control transfer by sending a ZLP  */
            USB_DEVICE_ControlStatus(appDataObject->deviceHandle, USB_DEVICE_CONTROL_STATUS_OK);

            break;

        case USB_DEVICE_CDC_EVENT_READ_COMPLETE:

            /* This means that the host has sent some data*/
            eventDataRead = (USB_DEVICE_CDC_EVENT_DATA_READ_COMPLETE *)pData;
            appDataObject->isReadComplete = true;
            appDataObject->numBytesRead = eventDataRead->length; 
            if (appDataObject->numBytesRead > 0) {
              BSP_LEDOn ( BSP_LED_1 );
              BSP_LEDOn ( BSP_LED_2  );
            }
            break;

        case USB_DEVICE_CDC_EVENT_CONTROL_TRANSFER_DATA_RECEIVED:

            /* The data stage of the last control transfer is
             * complete. For now we accept all the data */

                USB_DEVICE_ControlStatus(appDataObject->deviceHandle, USB_DEVICE_CONTROL_STATUS_OK);
            break;

        case USB_DEVICE_CDC_EVENT_CONTROL_TRANSFER_DATA_SENT:

            /* This means the GET LINE CODING function data is valid. We dont
             * do much with this data in this demo. */
            break;
            
        case USB_DEVICE_CDC_EVENT_WRITE_COMPLETE:

            /* This means that the data write got completed. We can schedule
             * the next read. */

            appDataObject->isWriteComplete = true;
            break;

        default:
            break;
    }

    return USB_DEVICE_CDC_EVENT_RESPONSE_NONE;
}

/*******************************************************
 * USB Device Layer Events - Application Event Handler
 *******************************************************/
void APP_USBDeviceEventHandler ( USB_DEVICE_EVENT event, void * eventData, uintptr_t context)
{
    USB_DEVICE_EVENT_DATA_CONFIGURED *configuredEventData;
    
    switch ( event )
    {
        case USB_DEVICE_EVENT_SOF:

            /* This event is used for switch debounce. This flag is reset
             * by the switch process routine. */
          //  appData.sofEventHasOccurred = true;
            break;

        case USB_DEVICE_EVENT_RESET:
        case USB_DEVICE_EVENT_DECONFIGURED:

            /* USB device is reset or device is deconfigured.
             * This means that USB device layer is about to deininitialize
             * all function drivers. Update LEDs to indicate
             * reset/deconfigured state. */

            BSP_LEDOn ( BSP_LED_1 );
            BSP_LEDOn ( BSP_LED_2  );
//            BSP_LEDOff( APP_USB_LED_3  );

            appData.isConfigured = false;

            break;

        case USB_DEVICE_EVENT_CONFIGURED:

            /* Check the configuratio. We only support configuration 1 */
            configuredEventData = (USB_DEVICE_EVENT_DATA_CONFIGURED*)eventData;
            if ( configuredEventData->configurationValue == 1)
            {
                /* Update LED to show configured state */
                BSP_LEDOff ( BSP_LED_1 );
                BSP_LEDOff ( BSP_LED_2 );
                //BSP_LEDOn ( APP_USB_LED_3 );

                /* Register the CDC Device application event handler here.
                 * Note how the appData object pointer is passed as the
                 * user data */

                USB_DEVICE_CDC_EventHandlerSet(USB_DEVICE_CDC_INDEX_0, APP_USBDeviceCDCEventHandler, (uintptr_t)&appData);

                /* Mark that the device is now configured */
                appData.isConfigured = true;

            }
            break;

        case USB_DEVICE_EVENT_SUSPENDED:

            /* Update LEDs */
            BSP_LEDOff ( BSP_LED_1 );
            BSP_LEDOn ( BSP_LED_2  );
//            BSP_LEDOn( APP_USB_LED_3  );
            break;

        
        case USB_DEVICE_EVENT_POWER_DETECTED:

            /* VBUS was detected. We can attach the device */
            USB_DEVICE_Attach(appData.deviceHandle);
            break;

        case USB_DEVICE_EVENT_POWER_REMOVED:
            
            /* VBUS is not available any more. Detach the device. */
            USB_DEVICE_Detach(appData.deviceHandle);
            break;

        case USB_DEVICE_EVENT_RESUMED:
        case USB_DEVICE_EVENT_ERROR:
        default:
            break;
    }
}


/*****************************************************
 * This function is called in every step of the
 * application state machine.
 *****************************************************/
bool APP_StateReset(void) {
    /* This function returns true if the device
     * was reset  */

    bool retVal;

    if(appData.isConfigured == false)
    {
        appData.state = APP_STATE_WAIT_FOR_CONFIGURATION;
        appData.readTransferHandle = USB_DEVICE_CDC_TRANSFER_HANDLE_INVALID;
        appData.writeTransferHandle = USB_DEVICE_CDC_TRANSFER_HANDLE_INVALID;
        appData.isReadComplete = true;
        appData.isWriteComplete = true;
        retVal = true;
        
        appData.isSetLineCodingCommandInProgress = false; 
        appData.isBaudrateDataReceived = false; 
    }
    else
    {
        retVal = false;
    }

    return(retVal);
}

/***************************************************************************
 * This function Handles the Set Line coding command from Host.  
 ***************************************************************************/
void _APP_SetLineCodingHandler(void)
{
    DRV_USART_BAUD_SET_RESULT resultUsartBaurateSet = DRV_USART_BAUD_SET_ERROR; 

    resultUsartBaurateSet = DRV_USART_BaudSet(appData.usartHandle, appData.setLineCodingData.dwDTERate);

    if (resultUsartBaurateSet == DRV_USART_BAUD_SET_SUCCESS)
    {
        /* Baudrate is changed successfully. Update Baudrate info in the 
         * Get line coding structure. */   
        appData.getLineCodingData.dwDTERate = appData.setLineCodingData.dwDTERate;

        /* Acknowledge the Status stage of the Control transfer */
        USB_DEVICE_ControlStatus(appData.deviceHandle, USB_DEVICE_CONTROL_STATUS_OK);
    }
    else
    {
        /* Baudrate was not set. There are two ways that an unsupported 
         * baud rate could be handled.  The first is just to ignore the 
         * request and ACK the control transfer.  That is what is currently 
         * implemented below. */  
         USB_DEVICE_ControlStatus(appData.deviceHandle, USB_DEVICE_CONTROL_STATUS_OK);


        /* The second possible method is to stall the STATUS stage of the 
         * request. STALLing the STATUS stage will cause an exception to be 
         * thrown in the requesting application. Some programs, like 
         * HyperTerminal, handle the exception properly and give a pop-up 
         * box indicating that the request settings are not valid.  Any 
         * application that does not handle the exception correctly will 
         * likely crash when this request fails.  For the sake of example 
         * the code required to STALL the status stage of the request is 
         * provided below.  It has been left out so that this demo does not 
         * cause applications without the required exception handling to 
         * crash.*/
         //USB_DEVICE_ControlStatus(appData.deviceHandle, USB_DEVICE_CONTROL_STATUS_ERROR);
    }
}


void APP_RTOS_Tasks (void){
  if ((RaceData.state == RACE_STARTED) || (RaceData.state == RACE_WAIT_TO_CROSSLINE)){
    RaceData.RaceTime_ms++;
  }
  BeepTasks();
}


/******************************************************************************
  Function:
    void APP_Tasks ( void )

  Remarks:
    See prototype in app.h.
*****************************************************************************/
void APP_Tasks ( void ) {
  uint8_t i;

  APP_CDC_Tasks();
  APP_USART_Task();
  RX5808_Tasks();
  
  
  
  /* Check the application's current state. */
  switch ( appData.state ) {
    /* Application's initial state. */
    case APP_STATE_INIT: {
      bool appInitialized = true;
      BSP_LED_1On();

      if (appInitialized) {
        /* Check if there was a Baudrate change request from Host */
        if ((appData.isConfigured) && (appData.isBaudrateDataReceived)) {
          appData.isBaudrateDataReceived = false; 
          _APP_SetLineCodingHandler();
        }

        appData.cdc_state = CDC_STATE_INIT; //Inicia el proceso de conección del CDC
//                laContext_SetActiveScreenChangedCallback(&APP_ScreenChangeCallBack);
        appData.usartHandle = DRV_USART_Open(DRV_USART_INDEX_0,
            (DRV_IO_INTENT_EXCLUSIVE|DRV_IO_INTENT_READWRITE|DRV_IO_INTENT_NONBLOCKING));
        
//        if (appData.usartHandle != DRV_HANDLE_INVALID) {
//          DRV_USART_BufferEventHandlerSet(appData.usartHandle,APP_BufferEventHandlerUsart,(uintptr_t)1);
//        }
        
        if (appData.usartHandle != DRV_HANDLE_INVALID) {
          DRV_USART_ByteReceiveCallbackSet(DRV_USART_INDEX_0, APP_USARTReceiveEventHandler);
          DRV_USART_ByteTransmitCallbackSet(DRV_USART_INDEX_0, APP_USARTTransmitEventHandler);
          DRV_USART_ByteErrorCallbackSet(DRV_USART_INDEX_0, APP_USARTErrorEventHandler);
        }
        
        usartInitBuffer(&appData.usartRxSimpleBuff);
        usartSetBufferRxCallBack(&appData.usartRxSimpleBuff,&USART_RXBufferComplete);
        appData.usartRxSimpleBuff.pattern[0] = '\r';
        appData.usartRxSimpleBuff.pattern[1] = '\n';
        
        DRV_TMR0_Start();
        BeepInitialize();
        DRV_TMR2_Start();
        // Checks if the button 1 is pressed to start a touch screen calibration process
        if (BSP_SWITCH_1StateGet() == 0) {
          appData.screen  = APP_CALIBRATE_TOUCH;
          laContext_SetActiveScreen(TouchCalibrationWnd_ID);
          TouchWnd_state = START_CALIBRATING;
        }
        appData.screen  = APP_MAIN_SCREEN;
        appData.state  = APP_EEPROM_READ_CONFIG_PILOT;
      }
      break;
    }
    
    case APP_EEPROM_READ_CONFIG_PILOT: {
      if (!SPI_EEPROM_IsActive()) {
        /*TODO*/ // Poner un TimeOut para no bloquear el programa si hay falla de EEPROM
        LoadAllPilotConfigData_eeprom();
        appData.state = APP_PROGRAM_RX5808_MODULES;
      }
      break;
    }
    
    case APP_PROGRAM_RX5808_MODULES: {
      if (IsPilotDataLoaded()){
        for (i=0;i<MAX_PILOTS;i++){
          RX5808_SetChannel(i,PilotData[i].Band, PilotData[i].Channel); // 
        }
        appData.state = APP_READ_RACE_CONFIG_DATA;
      }
      break;
    }
    
    case APP_READ_RACE_CONFIG_DATA: {
      if (!SPI_EEPROM_IsActive()) {
        LoadRaceData_EEPROM(NULL);
        appData.state = APP_STATE_SERVICE_TASKS;
      }      
      break;
    }

    case APP_STATE_SERVICE_TASKS: {
      switch (laContext_GetActiveScreen()->id) {
        case  MainWnd_ID: {
          if (BSP_SWITCH_1StateGet() == 0 ) {
            appData.KeyDebounce++;
            Nop();
            if (appData.KeyDebounce > 100 ){
              appData.KeyDebounce=0;
              USART_Send_string();
            } 
          } 
//          if (BTN3_EXTStateGet() == 0 ) {
//            laContext_SetActiveScreen(ConfigPilotWnd_ID);
//          }
          
          Nop();
          break;
        }
        case TouchCalibrationWnd_ID: {
          TouchWndTasks();
          break;
        }

        case ConfigPilotWnd_ID: {
          ConfigPilotModuleTasks();
          appData.usart1State = USART_STATE_WAIT_RX;
          break;
        }

        case ConfigRaceLevelsWnd_ID: {
          ConfigRaceLevelWndTasks();
          break;
        }
        case ConfigThrLevelWnd_ID: {
          ConfigRaceThrLevelWndTasks();
          break;
        }

        case RaceWnd_ID: {
          RaceTasks();
          RaceStartWnd_Tasks();
          break;
        }
        
        case RaceConfigWnd_ID: {
          RaceParamWnd_Tasks();
          break;
        }
        case WifiTesting_ID: {
          WiFiTestWnd_Tasks();
          break;
        }
        
      }

//          DRV_TOUCH_ADS7843_Calibrate(&appData.TouchCalBack);

        break;
    }

    /* The default state should never be executed. */
    default: {
        /* TODO: Handle error in application's state machine. */
        break;
    }
  }
}

 
void BeepStart(void){
  if (TuneSwitch == false) {
    PlayTune(&MarioTune[0], &MarioDelay[0], sizeof(MarioTune)/sizeof (uint16_t), 500, false);
  } else {
    PlayTune(&GOTTune[0], &GOTDelay[0], sizeof(GOTTune)/sizeof (uint16_t), 2000, false);
  }
  TuneSwitch = !TuneSwitch;
}


/*********************************************************************
 * @brief 
 * @param 
 * @retval None 
 * Overview:        
 * @note            
 ********************************************************************/
void APP_CDC_Tasks(void){
  int i; 
  switch(appData.cdc_state) {
    case CDC_WAIT_FOR_STARTUP:
      
      break;
    case CDC_STATE_INIT:

      /* Open the device layer */
      appData.deviceHandle = USB_DEVICE_Open( USB_DEVICE_INDEX_0, DRV_IO_INTENT_READWRITE );

      if(appData.deviceHandle != USB_DEVICE_HANDLE_INVALID)
      {
          /* Register a callback with device layer to get event notification (for end point 0) */
          USB_DEVICE_EventHandlerSet(appData.deviceHandle, APP_USBDeviceEventHandler, 0);

          appData.cdc_state = CDC_WAIT_FOR_CONFIGURATION;
      }
      else
      {
          /* The Device Layer is not ready to be opened. We should try
           * again later. */
      }

      break;

    case CDC_WAIT_FOR_CONFIGURATION:

      /* Check if the device was configured */
      if(appData.isConfigured)
      {
          /* If the device is configured then lets start reading */
          appData.cdc_state = CDC_SCHEDULE_READ;
      }
      break;

    case CDC_SCHEDULE_READ:

//      if(APP_StateReset())
//      {
//          break;
//      }

      /* If a read is complete, then schedule a read
       * else wait for the current read to complete */

      appData.cdc_state = CDC_WAIT_FOR_READ_COMPLETE;
      if(appData.isReadComplete == true)
      {
          appData.isReadComplete = false;
          appData.readTransferHandle =  USB_DEVICE_CDC_TRANSFER_HANDLE_INVALID;

          USB_DEVICE_CDC_Read (USB_DEVICE_CDC_INDEX_0,
                  &appData.readTransferHandle, appData.readBuffer,
                  APP_READ_BUFFER_SIZE);

          if(appData.readTransferHandle == USB_DEVICE_CDC_TRANSFER_HANDLE_INVALID)
          {
              appData.cdc_state = CDC_STATE_ERROR;
              break;
          } else {
            asm("Nop");
          }
      }

      break;

    case CDC_WAIT_FOR_READ_COMPLETE:
      if(APP_StateReset())
      {
          break;
      }

 //     APP_ProcessSwitchPress();

      /* Check if a character was received or a switch was pressed.
       * The isReadComplete flag gets updated in the CDC event handler. */

      if(appData.isReadComplete || appData.isSwitchPressed)
      {
          appData.cdc_state = CDC_SCHEDULE_WRITE;
      }

      break;


    case CDC_SCHEDULE_WRITE:

      if(APP_StateReset())
      {
          break;
      }

      /* Setup the write */

      appData.writeTransferHandle = USB_DEVICE_CDC_TRANSFER_HANDLE_INVALID;
      appData.isWriteComplete = false;
      appData.cdc_state = CDC_WAIT_FOR_WRITE_COMPLETE;

      if(appData.isSwitchPressed)
      {
        /* If the switch was pressed, then send the switch prompt*/
        appData.isSwitchPressed = false;
        USB_DEVICE_CDC_Write(USB_DEVICE_CDC_INDEX_0,
                &appData.writeTransferHandle, switchPromptUSB, 23,
                USB_DEVICE_CDC_TRANSFER_FLAGS_DATA_COMPLETE);
      }
      else
      {
        /* Else echo each received character by adding 1 */
        for(i=0; i<appData.numBytesRead; i++)
        {
          if((appData.readBuffer[i] != '/r') && (appData.readBuffer[i+1] != '/n')) {
            usartAddByte(&appData.usartTxSimpleBuff,appData.readBuffer[i]);

          } else {
            usartAddByte(&appData.usartTxSimpleBuff,'/r');
            usartAddByte(&appData.usartTxSimpleBuff,'/n');
            
            usartInitBuffer(&appData.usartTxSimpleBuff); // Inicializa el buffer de transmisión
            
          }
        }
        // Sends Echo to USB CDC
        USB_DEVICE_CDC_Write(USB_DEVICE_CDC_INDEX_0,
                &appData.writeTransferHandle,
                appData.readBuffer, appData.numBytesRead,
                USB_DEVICE_CDC_TRANSFER_FLAGS_DATA_COMPLETE);
        
      }

//      appData.uartTxCount += DRV_USART_Write(appData.usartHandle, 
//              &appData.readBuffer[appData.uartTxCount], appData.readLength - appData.uartTxCount);

      if(appData.uartTxCount >= appData.readLength)
      {
          /* This means we have sent all the data. We schedule the next
           * CDC Read. */

          appData.isReadComplete = false;
          appData.uartTxCount = 0;
          USB_DEVICE_CDC_Read (appData.cdcInstance, &appData.readTransferHandle,
              appData.readBuffer, APP_READ_BUFFER_SIZE);

          appData.state = APP_STATE_CHECK_UART_RECEIVE;
      }
      break;

    case CDC_WAIT_FOR_WRITE_COMPLETE:

      if(APP_StateReset())
      {
          break;
      }

      /* Check if a character was sent. The isWriteComplete
       * flag gets updated in the CDC event handler */

      if(appData.isWriteComplete == true)
      {
          appData.cdc_state = CDC_SCHEDULE_READ;
      }

      break;

    case CDC_STATE_ERROR:
      break;
    default:
      break;
  }
  
}



/*********************************************************************
 * @brief 
 * @param 
 * @retval None 
 * Overview:        
 * @note            
 ********************************************************************/
void EndEEPROMWriteCallback(uint16_t nReadBytes ){
  
}

void OnTouchCalibrationLoad(uint16_t nReadBytes ){
  DRV_TOUCH_ADS7843_TouchLoadCalibration((DRV_ASD7843_CALIBRATION_MATRIX *)&charBuff[0]);
}

/*********************************************************************
 * @brief 
 * @param 
 * @retval None 
 * Overview:        
 * @note            
 ********************************************************************/
void EndEEPROMReadCallback(uint16_t nReadBytes ){
  
}





/******************************************************************************
  Function:
    void APP_USART_Tasks ( void )

 Precondition: APP_Tasks() should have been called.

  Remarks:
    This task state machine registers the transmit and receive functionality
    of the USART1 to the USART driver.
 *****************************************************************************/
void APP_USART_Task( void ) {
    uint8_t num_of_bytes=0;

    switch(appData.usart1State)
    {

      case USART_STATE_INIT: {
        if (appData.state == APP_STATE_SERVICE_TASKS) {
          appData.usart1State = USART_STATE_SET_RX;
        }
        break;
      }
      
      case USART_STATE_IDLE: {
        /* Wait till State machine is Resetted by external event like Button press.*/

        Nop();
        break;
      }
      

      case USART_STATE_SET_RX:{
        /*USART1 RX*/

        /* Add application Rx buffer to Usart1Driver Rx buffer and wait*/
//        DRV_USART_BufferAddRead(appData.usartHandle,&(appData.drvUsartRxBufHandle),
//        (uint8_t*)&appData.drvUsartRxBuffer[0],MAX_NUM_OF_USART_BYTES);

        appData.usart1State = USART_STATE_WAIT_RX;
        
        break;
      }
      
      case USART_STATE_WAIT_RX: {
        
        break;
      }
      

        case USART_STATE_SET_TX:
        {

            /*USART1 TX*/

            /* Populate the application Tx buffer for Tx over USART1*/
            for(num_of_bytes = 0; num_of_bytes <= MAX_NUM_OF_USART_BYTES; num_of_bytes++)
            {
                appData.drvUsartTxBuffer[num_of_bytes] = num_of_bytes;
            }


            /* Add application transmit buffer to Usart1 Tx buffer and transmit*/
//            DRV_USART_BufferAddWrite(appData.usartHandle,&(appData.drvUsartTxBufHandle),
//            (uint8_t*)&appData.drvUsartTxBuffer[0],MAX_NUM_OF_USART_BYTES);

            appData.usart1State = USART_STATE_WAIT_FOR_TX_COMPLETION;

        }break;

        case USART_STATE_WAIT_FOR_TX_COMPLETION:
        {

          Nop();

        }break;

        

        default:
        break;
    }
}


void USART_Send_string(void) {
  uint8_t data;
  uint8_t i;
  /* Add the received data on USART2 to the write buffer and transmit back to USART1*/
//  DRV_USART_BufferAddWrite(appData.usartHandle,&(appData.drvUsartTxBufHandle),switchPromptUSB, 25);
  usartInitBuffer(&appData.usartTxSimpleBuff);
  for (i = 0; i < sizeof(switchPromptUSB); i++) {
    usartAddByte(&appData.usartTxSimpleBuff,switchPromptUSB[i]);
  }
  Nop();
  if( !(DRV_USART_TRANSFER_STATUS_TRANSMIT_FULL & DRV_USART_TransferStatus(appData.usartHandle)) ) {
    DRV_USART_WriteByte(appData.usartHandle, usartGetByte(&appData.usartTxSimpleBuff));
  }
  

}

void USART_SetUp_Read(void) {
//  DRV_USART_BufferAddRead(appData.usartHandle,&appData.drvUsartRxBufHandle,&appData.drvUsartRxBuffer ,10);
//  DRV_USART_BufferAddRead(appData.usartHandle,&(appData.drvUsartRxBufHandle),(uint8_t*)&appData.drvUsartRxBuffer[0],10);
//  appData.usart1State = USART_STATE_WAIT_RX;
}

/******************************************************************************
  Function:
    void APP_BufferEventHandlerUsart ( DRV_USART_BUFFER_EVENT,
                DRV_USART_BUFFER_HANDLE,  uintptr_t );

   Remarks:
    This routine is callback function for the USART1 buffer events. Driver
    uses the application Tx or Rx buffer reference along with the client handle
    to notify the buffer events to the application. This is USART1 buffer
    event handler. This call back function to be registerd with the driver
    using DRV_USART_BufferAddRead(); or DRV_USART_BufferAddWrite();
 */


//void APP_BufferEventHandlerUsart(DRV_USART_BUFFER_EVENT buffEvent,
//                            DRV_USART_BUFFER_HANDLE hBuffer,
//                            uintptr_t context ) {
//  uint8_t index;
//  DRV_USART_ERROR UsartError;
//  uint8_t nBytes;
//  laString str2;
//  uint8_t Data[10];  // Variable para almacenar buffer de lectura y escritura a EEPROM
//  switch(buffEvent) {	
//    /* Buffer event is completed successfully */
//    case DRV_USART_BUFFER_EVENT_COMPLETE: {
//      if (hBuffer == appData.drvUsartRxBufHandle) {
//        if (appData.usart1State == USART_STATE_WAIT_RX) {
//          appData.usart1State = USART_STATE_IDLE;
//          nBytes = DRV_USART_BufferCompletedBytesGet(hBuffer);
//          for (index = 0; index < nBytes; index++) {
//            Data[index] = appData.drvUsartRxBuffer[index];
//          }
//          Data[index+1] = '\0';
//
//        //  str = laString_CreateFromCharBuffer(Data,GFXU_StringFontIndexLookup(&stringTable, string_BaudLbl, 0));
//          str2 = laString_CreateFromCharBuffer(Data,&Calibri_Bold_20);
//          laTextFieldWidget_SetText(USART_RXTxt,str2);
//          laString_Destroy(&str2);          
//          
//          Nop();
//        }
//      } else if(hBuffer == appData.drvUsartTxBufHandle) {
//        
//        Nop();
//      }
//      break;
//    }
//
//    /* Buffer event has some error */
//    case DRV_USART_BUFFER_EVENT_ERROR:
//      UsartError = DRV_USART_ErrorGet(appData.usartHandle);
//      switch(UsartError) {
//        case DRV_USART_ERROR_NONE:
//          break;
//          
//        case DRV_USART_ERROR_RECEIVE_OVERRUN :
//          Nop();
//          break;
//          
//        case DRV_USART_ERROR_PARITY :
//          Nop();
//          break;
//        case DRV_USART_ERROR_FRAMING :
//          Nop();
//          break;
//        default :
//          Nop();
//          break;
//      }
//      break;
//
//   default:
//      Nop();
//      break;
//  }
//}

// Event Processing Technique. Event is received when
// a byte is received.

void APP_USARTReceiveEventHandler(const SYS_MODULE_INDEX index) {
    // Byte has been Received. Handle the event.
    // Read byte using DRV_USART_ReadByte.
  uint8_t dataReceived;

  
  while( DRV_USART_TRANSFER_STATUS_RECEIVER_DATA_PRESENT & DRV_USART_TransferStatus(appData.usartHandle) ) {
    dataReceived = DRV_USART_ReadByte(appData.usartHandle);
    usartAddByte(&appData.usartRxSimpleBuff,dataReceived);
  }  
  
}        

void APP_USARTTransmitEventHandler(const SYS_MODULE_INDEX index) {
    // Byte has been Received. Handle the event.
    // Read byte using DRV_USART_ReadByte.
  
  while(usartGetBuffSize(&appData.usartTxSimpleBuff) != 0 ){
    if( !(DRV_USART_TRANSFER_STATUS_TRANSMIT_FULL & DRV_USART_TransferStatus(appData.usartHandle)) ) {
      DRV_USART_WriteByte(appData.usartHandle, usartGetByte(&appData.usartTxSimpleBuff));
    }
  }  
  
}        

void APP_USARTErrorEventHandler(const SYS_MODULE_INDEX index){
  Nop();
}

void USART_RXBufferComplete(uint8_t nbytes){
//  laString str2;
////  str = laString_CreateFromCharBuffer(Data,GFXU_StringFontIndexLookup(&stringTable, string_BaudLbl, 0));
//  str2 = laString_CreateFromCharBuffer((char *)&appData.usartRxSimpleBuff.Buff,&Calibri_Bold_20);
//  laTextFieldWidget_SetText(USART_RXTxt,str2);
//  laString_Destroy(&str2);          
//  
}

void ClearStrOnClick(void){
//  laString str2;
////  str = laString_CreateFromCharBuffer(Data,GFXU_StringFontIndexLookup(&stringTable, string_BaudLbl, 0));
//  str2 = laString_CreateFromCharBuffer("",&Calibri_Bold_20);
//  laTextFieldWidget_SetText(USART_RXTxt,str2);
//  laString_Destroy(&str2);          
//  usartInitBuffer(&appData.usartRxSimpleBuff);
}
/*******************************************************************************
 End of File
 */
