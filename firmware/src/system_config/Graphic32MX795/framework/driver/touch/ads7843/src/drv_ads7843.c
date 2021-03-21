/*******************************************************************************
 Touch Driver Interface ADS7843 File

  File Name:
    drv_ads7843.c

  Summary:
    ADS7843 Touch Driver interface file.

  Description:

 ******************************************************************************/

#include "system_config.h"
#include <stdlib.h>
#include "system_definitions.h"
#include "framework/driver/touch/ads7843/drv_ads7843_local.h"
#include "framework/driver/touch/ads7843/drv_ads7843.h"
#include <cp0defs.h>


#if defined DRV_ADS7843_USE_SPI_MODULE
  #include "drv_touch.h"
  #include "drv_spi.h"
#endif


#ifndef GET_TICKS
  #define GET_TICKS() _CP0_GET_COUNT()
#endif
#ifndef _1SEG_TICKS
  #define _1SEG_TICKS      (SYS_CLK_FREQ*1.0/2)
#endif

#ifndef _1mSEG_TICKS
  #define _1mSEG_TICKS     (SYS_CLK_FREQ*1.0/2)/1000
#endif


#ifdef ENABLE_DEBUG_TOUCHSCREEN
void TouchScreenResistiveTestXY(void);
#endif
//////////////////////// GLOBAL VARIABLES ////////////////////////////

//#define CALIBRATION_DELAY   300				                // delay between calibration touch points

// Current ADC values for X and Y channels
volatile short adcX = -1;
volatile short adcY = -1;
volatile short adcZ = -1;
static  short LastX = -1;
static  short LastY = -1;
//static uint16_t TH = DRV_TOUCH_ADS7843_PRESS_THRESHOLD;



// copy of the stored or sampled raw points (this is the calibration data stored)
/*      xRawTouch[0] - x sample from upper left corner; 
        xRawTouch[1] - x sample from upper right corner
        xRawTouch[2] - x sample from lower right corner
        xRawTouch[3] - x sample from lower left corner
        yRawTouch[0] - y sample from upper left corner; 
        yRawTouch[1] - y sample from upper right corner
        yRawTouch[2] - y sample from lower right corner
        yRawTouch[3] - y sample from lower left corner
 */

/* MTCH6301 Driver instance object */
static DRV_ADS7843_OBJECT        ads7843_DrvData;

/* */
static DRV_ADS7843_CLIENT_OBJECT sADS7843ClientInstances[1];

volatile short xRawTouch[DRV_ADS7843_CALIBRATION_POINTS] = { TOUCHCAL_ULX, 
                                                         TOUCHCAL_URX, 
                                                         TOUCHCAL_LRX };

volatile short yRawTouch[DRV_ADS7843_CALIBRATION_POINTS] = { TOUCHCAL_ULY, 
                                                         TOUCHCAL_URY, 
                                                         TOUCHCAL_LRY };
/* Matriz de coeficientes de calibracion */
DRV_ASD7843_CALIBRATION_MATRIX  CalibMatrix;

/*********************************************************************
 /*                      CALL BACK FUNCTIONS FOR SPI DRIVER        
 /*********************************************************************/
#if defined DRV_ADS7843_USE_SPI_MODULE
void _ADS7843_SPI_OnEndEventHandler(DRV_SPI_BUFFER_EVENT buffEvent,
                      DRV_SPI_BUFFER_HANDLE hBufferEvent,
                      void* context ); 
void _ADS7843_SPI_OnStartEventHandler(DRV_SPI_BUFFER_EVENT buffEvent,
                      DRV_SPI_BUFFER_HANDLE hBufferEvent,
                      void* context ); 
void _ADS7843_OnSPIEvent(DRV_SPI_BUFFER_EVENT buffEvent,
                      DRV_SPI_BUFFER_HANDLE hBufferEvent,
                      void* context );
DRV_ADS7843_SPI_STATES _ADS7843_SPI_ReadData(void);
uint16_t _ADS7843ReadData(uint8_t Cmd);
uint16_t _ADS7843_CalcPressure(uint16_t RXpoint,uint16_t Z1, uint16_t Z2);
  


#endif


// *****************************************************************************
// Section: ADC10Bit Driver Interface Routines
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
// *****************************************************************************
// Section: Initialization
// *****************************************************************************
// *****************************************************************************
/* Function:
    SYS_MODULE_OBJ DRV_TOUCH_ADS7843_Initialize ( const SYS_MODULE_INDEX index,
                                           const SYS_MODULE_INIT * const init )

  Summary:
    Initializes and ADS7843 psuedo controller.

  Description:
    This function initializes the ADS7843 psuedo controller.
*********************************************************************************/
SYS_MODULE_OBJ DRV_TOUCH_ADS7843_Initialize( const SYS_MODULE_INDEX index,
                                              const SYS_MODULE_INIT * const init )
{
    DRV_ADS7843_OBJECT * pDrvInstance = (DRV_ADS7843_OBJECT *) NULL;
    DRV_TOUCH_SAMPLE_POINTS samplePoints;

    if (index >= 1)
    {
        SYS_ASSERT(false, "ADS7843 Driver: Attempting to initialize an instance number greater than the max");
        return SYS_MODULE_OBJ_INVALID;
    }

    pDrvInstance = ( DRV_ADS7843_OBJECT *)&ads7843_DrvData;

    const DRV_TOUCH_INIT * const pInit = (const DRV_TOUCH_INIT * const)init;

    _DRV_TOUCH_ADS7843_HardwareInit(0);

    ads7843_DrvData.status                = SYS_STATUS_READY;
    ads7843_DrvData.touchId               = pInit->touchId;
    ads7843_DrvData.verticalResolution    = pInit->verticalResolution;
    ads7843_DrvData.horizontalResolution  = pInit->horizontalResolution;
    ads7843_DrvData.touchStatus           = DRV_TOUCH_POSITION_NONE;
    ads7843_DrvData.MustReadTouch         = 0;
    ads7843_DrvData.calibrationState      = TOUCH_CALIB_UNINIT; // Uninitialized state
#if defined DRV_ADS7843_USE_SPI_MODULE
    ads7843_DrvData.spiState              = ADS7843_SPI_READY;
    
    ads7843_DrvData.drvCallBacks.baudRate = 0;
    ads7843_DrvData.drvCallBacks.operationStarting = _ADS7843_SPI_OnStartEventHandler;
    ads7843_DrvData.drvCallBacks.operationEnded = _ADS7843_SPI_OnEndEventHandler;
    
#else
    ads7843_DrvData.spiState              = ADS7843_SPI_NOT_USED;
#endif
    // set the state of the statemachine to start the sampling
//    ads7843_DrvData.state = DRV_ADS7843_STATE_SET_X;
    
    samplePoints.touchCalUlx = TOUCHCAL_ULX;
    samplePoints.touchCalUly = TOUCHCAL_ULY;

    samplePoints.touchCalUrx = TOUCHCAL_URX;
    samplePoints.touchCalUry = TOUCHCAL_URY;

    samplePoints.touchCalLrx = TOUCHCAL_LRX;
    samplePoints.touchCalLry = TOUCHCAL_LRY;

    samplePoints.touchCalLlx = TOUCHCAL_LLX;
    samplePoints.touchCalLly = TOUCHCAL_LLY;

    DRV_TOUCH_ADS7843_CalibrationSet(&samplePoints);

    return (SYS_MODULE_OBJ)pDrvInstance;
}


/*********************************************************************
 * @name  void DRV_TOUCH_ADS7843_Deinitialize ( SYS_MODULE_OBJ object );
 * @brief 
 * @param 
 * @retval None 
 * Overview:        
 * @note            
 ********************************************************************/
void DRV_TOUCH_ADS7843_Deinitialize ( SYS_MODULE_OBJ object ) {
  DRV_ADS7843_OBJECT * pDrvInstance = (DRV_ADS7843_OBJECT *) NULL;
  pDrvInstance = (DRV_ADS7843_OBJECT *) &ads7843_DrvData;
}

// *****************************************************************************
/* Function:
    void DRV_TOUCH_ADS7843_Tasks ( SYS_MODULE_OBJ object );

  Summary:
    Maintains the driver's state machine and implements its task queue
    processing.

  Description:
	This routine is used to maintain the driver's internal state
	machine and implement its command queue processing. It is always called
  from SYS_Tasks() function. This routine detects a touch press position.
 ****************************************************************************/
void DRV_TOUCH_ADS7843_Tasks ( SYS_MODULE_OBJ object ) {

#if defined DRV_ADS7843_USE_SPI_MODULE  
  switch (ads7843_DrvData.state) {
    case ADS7843_IDLE: {
//      if ((ads7843_DrvData.MustReadTouch == 1) && (T_INTStateGet() == 0)){
      if (ads7843_DrvData.MustReadTouch == 1){
        ads7843_DrvData.MustReadTouch = 0;
        ads7843_DrvData.state = ADS7843_READING;
        ads7843_DrvData.spiState = ADS7843_SPI_INIT_SEQUENCE;
      }
    } break;
    
    case ADS7843_READING: {
      if (_ADS7843_SPI_ReadData() == ADS7843_SPI_DATA_READY){
        ads7843_DrvData.state = ADS7843_DATA_OK;
      }
    } break;
    
    case ADS7843_DATA_OK:{
      DRV_TOUCH_ADS7843_SPI_PositionDetect();
      ads7843_DrvData.state = ADS7843_IDLE;
      
    } break;
      
    default : {
      
    }
  }
  
  // call the calibration tasks routine if the state is different than TOUCH_CALIB_UNINIT
  if (ads7843_DrvData.calibrationState != TOUCH_CALIB_UNINIT) {
    DRV_TOUCH_ASD7843_CalibrationTasks();
  }
  
#else 
  DRV_TOUCH_ADS7843_PositionDetect(); // Call the blocking function
  
#endif
}


// *****************************************************************************
/* Function:
    void DRV_TOUCH_ADS7843_SetTouchFlag(void);

  Summary:
    Sets the read touch hardware 

  Description:
 ****************************************************************************/
void DRV_TOUCH_ADS7843_SetTouchFlag(void) {
  DRV_ADS7843_OBJECT * pDrvInstance;
  pDrvInstance = (DRV_ADS7843_OBJECT *) &ads7843_DrvData;
  ads7843_DrvData.MustReadTouch = 1;
}

/**************************************************************************
  Function:
       SYS_STATUS DRV_TOUCH_ADS7843_Status ( SYS_MODULE_OBJ object )

  Summary:
    Provides the current status of the ADS7843 driver module.

  Description:
    This function provides the current status of the ADS7843 driver module.
 ****************************************************************************/
SYS_STATUS DRV_TOUCH_ADS7843_Status ( SYS_MODULE_OBJ object ) {
//    DRV_ADS7843_OBJECT * pDrvInstance = (DRV_ADS7843_OBJECT *)object;    
  return ads7843_DrvData.status;
}

// *****************************************************************************
// *****************************************************************************
// Section: ADC10Bit Driver Client Routines
// *****************************************************************************
// *****************************************************************************
// *****************************************************************************

/**************************************************************************
  Function:
       DRV_HANDLE DRV_TOUCH_ADS7843_Open ( const SYS_MODULE_INDEX drvIndex,
                                const DRV_IO_INTENT    intent )

  Summary:
    Opens the specified ADS7843 driver instance and returns a handle to it.

  Description:
    This routine opens the specified ADS7843 driver instance and provides a
    handle that must be provided to all other client-level operations to
    identify the caller and the instance of the driver. The ioIntent
    parameter defines how the client interacts with this driver instance.
 ******************************************************************************/
DRV_HANDLE DRV_TOUCH_ADS7843_Open ( const SYS_MODULE_INDEX index, const DRV_IO_INTENT intent ) {
  DRV_ADS7843_OBJECT * pDrvInstance = (DRV_ADS7843_OBJECT *)&ads7843_DrvData;

  if (index >= 1) {
    SYS_ASSERT(false, "ADS7843 Driver: Attempting to open an instance number greater than the max");
    return DRV_HANDLE_INVALID;
  }

  DRV_ADS7843_CLIENT_OBJECT * pClient = &sADS7843ClientInstances[index];
  if (pClient == NULL) {
    SYS_ASSERT(false, "ADS7843 Driver: Couldn't find a free client to open");
    return DRV_HANDLE_INVALID;
  }

  pClient->driverObject = pDrvInstance;
  pClient->intent = intent;

  if ((intent & DRV_IO_INTENT_EXCLUSIVE) == DRV_IO_INTENT_EXCLUSIVE) {
    ads7843_DrvData.isExclusive = true;
  }
  ads7843_DrvData.numClients++;
#if defined DRV_ADS7843_USE_SPI_MODULE    
  ads7843_DrvData.spiId = DRV_SPI_INDEX_0;
  ads7843_DrvData.drvSPIHandle = DRV_SPI_Open(ads7843_DrvData.spiId,DRV_IO_INTENT_READWRITE);
  if(ads7843_DrvData.drvSPIHandle != DRV_HANDLE_INVALID)  {
    ads7843_DrvData.spiState = ADS7843_SPI_READY;

    DRV_SPI_ClientConfigure(ads7843_DrvData.drvSPIHandle, &ads7843_DrvData.drvCallBacks);
  }
  else {
    ads7843_DrvData.spiState = ADS7843_SPI_OPEN_ERROR;
  }
#endif

  return (DRV_HANDLE)pClient;
}

// *****************************************************************************
/* Function:
    void DRV_TOUCH_ADS7843_Close ( DRV_HANDLE handle )

  Summary:
    Closes an opened instance of the ADS7843 driver

  Description:
    This function closes an opened instance of the ADS7843 driver, invalidating
    the handle.
******************************************************************************/
void DRV_TOUCH_ADS7843_Close ( DRV_HANDLE handle ) {
  //TODO: Revisar esta funcion pues no parece que haga nulos los objetos
  DRV_ADS7843_CLIENT_OBJECT * pClient = (DRV_ADS7843_CLIENT_OBJECT *)handle;
  if ( pClient != &sADS7843ClientInstances[0] )  {
    SYS_ASSERT(false, "ADS7843 Driver: Trying to close a client to a driver that is outside the range of client handles")
    return;
  }
  return;
}


/*********************************************************************
 * @brief DRV_ADS7843_SPI_STATES _ADS7843_SPI_ReadData(void)
 * @param 
 * @retval None 
 * Overview: Reads the Touch Controller position via SPI Driver
 * @note            
 ********************************************************************/
DRV_ADS7843_SPI_STATES _ADS7843_SPI_ReadData(void){
  uint16_t Temp;
  uint8_t TempIndex;
  DRV_ADS7843_OBJECT * pDrvInstance = (DRV_ADS7843_OBJECT *)&ads7843_DrvData;
  
  switch (ads7843_DrvData.spiState) {
    case ADS7843_SPI_INIT_SEQUENCE: {
      ads7843_DrvData.touchIndex = 0;
      //break;
    }
    case ADS7843_SPI_SEND_COMMAND_X: {
      ads7843_DrvData.drvSPITXbuffer[0] = ADS7843_READ_X;
      ads7843_DrvData.drvSPITXbuffer[1] = 0; 
      ads7843_DrvData.drvSPITXbuffer[2] = 0; 
      ads7843_DrvData.spiState = ADS7843_SPI_WAIT_FOR_COMMAND_X;
      // This function read and write to SPI simultaneously. The first read byte is a dummy byte and
      // should be discarted when processing the SPI response 
      ads7843_DrvData.drvSPIRDBUFHandle = DRV_SPI_BufferAddWriteRead(ads7843_DrvData.drvSPIHandle,
                                                    (uint8_t *)&ads7843_DrvData.drvSPITXbuffer,
                                                    3,
                                                    (uint8_t *)&ads7843_DrvData.drvSPIRXbuffer,
                                                    3,
                                                    _ADS7843_OnSPIEvent,
                                                    pDrvInstance);
      ads7843_DrvData.spiTimeOut=0;
      
    }break;
    
    case ADS7843_SPI_WAIT_FOR_COMMAND_X: {
      // Keep in loop until the ADS7843_OnSPIEvent get's the response from touch
      ads7843_DrvData.spiState = ADS7843_SPI_WAIT_FOR_COMMAND_X;
      // TODO: Se debe poner un timeout por si hay algun problema de hardware poder avisar
      ads7843_DrvData.spiTimeOut++;
      if (ads7843_DrvData.spiTimeOut > DRV_ADS7843_MAX_SPI_TIME_OUT){
        ads7843_DrvData.spiState = ADS7843_SPI_TIME_OUT;
      }
    }break;
    
    case ADS7843_SPI_GET_READ_X:{
//      ADS7843_Disable();
      Temp = (ads7843_DrvData.drvSPIRXbuffer[1] << 8) | (ads7843_DrvData.drvSPIRXbuffer[2]);
      ads7843_DrvData.data[ads7843_DrvData.touchIndex].xPoint = (Temp >> 3) & 0xFFF;
      ads7843_DrvData.data[ads7843_DrvData.touchIndex].xPoint >>= 2; // Rotate 2 bits left and result is 10 bits (1024 max)
    };
    
    case ADS7843_SPI_SEND_COMMAND_Y: {
      ads7843_DrvData.drvSPITXbuffer[0] = ADS7843_READ_Y;
      ads7843_DrvData.drvSPITXbuffer[1] = 0; 
      ads7843_DrvData.drvSPITXbuffer[2] = 0; 
      
      ads7843_DrvData.spiState = ADS7843_SPI_WAIT_FOR_COMMAND_Y;
      // This function read and write to SPI simultaneously. The first read byte is a dummy byte and
      // should be discarted when processing the SPI response 
      ads7843_DrvData.drvSPIRDBUFHandle = DRV_SPI_BufferAddWriteRead(ads7843_DrvData.drvSPIHandle,
                                                    (uint8_t *)&ads7843_DrvData.drvSPITXbuffer,
                                                    3,
                                                    (uint8_t *)&ads7843_DrvData.drvSPIRXbuffer,
                                                    3,
                                                    _ADS7843_OnSPIEvent,
                                                    pDrvInstance);
      ads7843_DrvData.spiTimeOut=0;
    }break;
    
    case ADS7843_SPI_WAIT_FOR_COMMAND_Y: {
      // Keep in loop until the ADS7843_OnSPIEvent get's the response from touch
      ads7843_DrvData.spiState = ADS7843_SPI_WAIT_FOR_COMMAND_Y;
      // TODO: Se debe poner un timeout por si hay algun problema de hardware poder avisar
      ads7843_DrvData.spiTimeOut++;
      if (ads7843_DrvData.spiTimeOut > DRV_ADS7843_MAX_SPI_TIME_OUT){
        ads7843_DrvData.spiState = ADS7843_SPI_TIME_OUT;
        
      }
      
    }break;
    
    case ADS7843_SPI_GET_READ_Y:{
      
#if defined USE_PRESSURE_READING
      ads7843_DrvData.spiState = ADS7843_SPI_SEND_COMMAND_Z1;
      Temp = (ads7843_DrvData.drvSPIRXbuffer[1] << 8) | (ads7843_DrvData.drvSPIRXbuffer[2])  ;
      ads7843_DrvData.data[ads7843_DrvData.touchIndex].yPoint = (Temp >> 3) & 0xFFF;
      // There is no break so it continues sending ZTouch
#else
      
      ADS7843_Disable();
      ads7843_DrvData.spiState = ADS7843_SPI_READY;
      Temp = (ads7843_DrvData.drvSPIRXbuffer[1] << 8) | (ads7843_DrvData.drvSPIRXbuffer[2])  ;
      ads7843_DrvData.data[ads7843_DrvData.touchIndex].yPoint = (Temp >> 3) & 0xFFF;
      ads7843_DrvData.data[ads7843_DrvData.touchIndex].yPoint >>= 2; // Rotate 2 bits left and result is 10 bits (1024 max)
      if (ads7843_DrvData.touchIndex>=(DRV_ADS7843_FILTER_SAMPLE_POINTS-1)){
        ads7843_DrvData.spiState = ADS7843_SPI_DATA_READY;
        ads7843_DrvData.touchIndex = 0;
        return ADS7843_SPI_DATA_READY;
      } else {
        ads7843_DrvData.spiState = ADS7843_SPI_SEND_COMMAND_X; // Reads another touch point
        ads7843_DrvData.touchIndex++;
      }
      break;
#endif
    }

#if defined USE_PRESSURE_READING
    case ADS7843_SPI_SEND_COMMAND_Z1: {
      ads7843_DrvData.drvSPITXbuffer[0] = ADS7843_READ_Z1;
      ads7843_DrvData.drvSPITXbuffer[1] = 0; 
      ads7843_DrvData.drvSPITXbuffer[2] = 0; 
      
      ads7843_DrvData.spiState = ADS7843_SPI_WAIT_FOR_COMMAND_Z1;
      // This function read and write to SPI simultaneously. The first read byte is a dummy byte and
      // should be discarted when processing the SPI response 
      ads7843_DrvData.drvSPIRDBUFHandle = DRV_SPI_BufferAddWriteRead(ads7843_DrvData.drvSPIHandle,
                                                    (uint8_t *)&ads7843_DrvData.drvSPITXbuffer,
                                                    3,
                                                    (uint8_t *)&ads7843_DrvData.drvSPIRXbuffer,
                                                    3,
                                                    _ADS7843_OnSPIEvent,
                                                    pDrvInstance);
      ads7843_DrvData.spiTimeOut=0;
    } break;
    
    case   ADS7843_SPI_WAIT_FOR_COMMAND_Z1: {
      // Keep in loop until the ADS7843_OnSPIEvent get's the response from touch
      ads7843_DrvData.spiState = ADS7843_SPI_WAIT_FOR_COMMAND_Z1;
      // TODO: Se debe poner un timeout por si hay algun problema de hardware poder avisar
      ads7843_DrvData.spiTimeOut++;
      if (ads7843_DrvData.spiTimeOut > DRV_ADS7843_MAX_SPI_TIME_OUT){
        ads7843_DrvData.spiState = ADS7843_SPI_TIME_OUT;
        
      }
    }break;
    
    case ADS7843_SPI_GET_READ_Z1 :{
      Temp = (ads7843_DrvData.drvSPIRXbuffer[1] << 8) | (ads7843_DrvData.drvSPIRXbuffer[2]);
      ads7843_DrvData.data[ads7843_DrvData.touchIndex].zPoint = (Temp >> 3) & 0xFFF;
      // break; // There is no break here so it continues sending the Z2 command
    }
    
    case ADS7843_SPI_SEND_COMMAND_Z2 :{
      ads7843_DrvData.drvSPITXbuffer[0] = ADS7843_READ_Z2;
      ads7843_DrvData.drvSPITXbuffer[1] = 0; 
      ads7843_DrvData.drvSPITXbuffer[2] = 0; 
      
      ads7843_DrvData.spiState = ADS7843_SPI_WAIT_FOR_COMMAND_Z2;
      // This function read and write to SPI simultaneously. The first read byte is a dummy byte and
      // should be discarted when processing the SPI response 
      ads7843_DrvData.drvSPIRDBUFHandle = DRV_SPI_BufferAddWriteRead(ads7843_DrvData.drvSPIHandle,
                                                    (uint8_t *)&ads7843_DrvData.drvSPITXbuffer,
                                                    3,
                                                    (uint8_t *)&ads7843_DrvData.drvSPIRXbuffer,
                                                    3,
                                                    _ADS7843_OnSPIEvent,
                                                    pDrvInstance);
      ads7843_DrvData.spiTimeOut=0;
      
    } break;
    case ADS7843_SPI_WAIT_FOR_COMMAND_Z2:{
      // Keep in loop until the ADS7843_OnSPIEvent get's the response from touch
      ads7843_DrvData.spiState = ADS7843_SPI_WAIT_FOR_COMMAND_Z2;
      // TODO: Se debe poner un timeout por si hay algun problema de hardware poder avisar
      ads7843_DrvData.spiTimeOut++;
      if (ads7843_DrvData.spiTimeOut > DRV_ADS7843_MAX_SPI_TIME_OUT){
        ads7843_DrvData.spiState = ADS7843_SPI_TIME_OUT;
        
      }
    } break;
    
    case ADS7843_SPI_GET_READ_Z2 :{
      TempIndex = ads7843_DrvData.touchIndex;
      Temp = (ads7843_DrvData.drvSPIRXbuffer[1] << 8) | (ads7843_DrvData.drvSPIRXbuffer[2]);
      Temp = (Temp >> 3) & 0xFFF;
      Temp = _ADS7843_CalcPressure(ads7843_DrvData.data[TempIndex].xPoint, 
                            ads7843_DrvData.data[TempIndex].zPoint,
                            Temp);
      ads7843_DrvData.data[TempIndex].zPoint = Temp;
      if (ads7843_DrvData.touchIndex>=(DRV_ADS7843_FILTER_SAMPLE_POINTS-1)){
        ads7843_DrvData.spiState = ADS7843_SPI_DATA_READY;
        ads7843_DrvData.touchIndex = 0;
        return ADS7843_SPI_DATA_READY;
      } else {
        ads7843_DrvData.spiState = ADS7843_SPI_SEND_COMMAND_X; // Reads another touch point
        ads7843_DrvData.touchIndex++;
      }
    }break;
    
#endif // Del if defined USE_PRESSURE_READINGS
    case ADS7843_SPI_TIME_OUT : {
      return ADS7843_SPI_TIME_OUT;
    }break;
    
    default: {
      
    }
  }
  return (ads7843_DrvData.spiState);
}

/*********************************************************************
 * Function:        uint16_t _ADS7843ReadData(uint8_t Cmd)
 * PreCondition:    None
 * Input:           None
 * Output:          None
 * Side Effects:    None
 * Overview:        None
 * Note:            None
 ********************************************************************/
uint16_t _ADS7843ReadData(uint8_t Cmd){
  uint8_t i, cycle;
  uint16_t TempRead;
  uint8_t TempCmd;
  
  ADS7843_Enable();

  Nop(); Nop(); Nop(); Nop();
  for (cycle = 0 ; i < 2; i++) {
    TempRead = 0;
    TempCmd = Cmd;
    for (i = 0; i < 8; i++) {
      ADS7843_MSDO = (TempCmd&0x80) ? 1 : 0;
      Nop(); Nop(); Nop(); Nop();
      Nop(); Nop(); Nop(); Nop();
      Nop(); Nop(); Nop(); Nop();
      Nop(); Nop(); Nop(); Nop();
      ADS7843_CLK = 1;
      TempCmd  <<= 1;
      Nop();
      ADS7843_CLK = 0;
      Nop(); Nop(); Nop(); Nop();
      Nop(); Nop(); Nop(); Nop();
      Nop(); Nop(); Nop(); Nop();
      Nop(); Nop(); Nop(); Nop();
    }

    ADS7843_MSDO = 0;

    for (i = 0; i < 16; i++) { // Lee 16 bits pero solo 12 MSb son efectivos
      Nop(); Nop(); Nop(); Nop();
      Nop(); Nop(); Nop(); Nop();
      Nop(); Nop(); Nop(); Nop();
      Nop(); Nop(); Nop(); Nop();
      TempRead |= ADS7843_MSDI;
      Nop(); Nop(); Nop(); Nop();
      Nop(); Nop(); Nop(); Nop();
      Nop(); Nop(); Nop(); Nop();
      Nop(); Nop(); Nop(); Nop();
      ADS7843_CLK = 1;
      TempRead  <<= 1;
      Nop(); Nop(); Nop(); Nop();
      Nop(); Nop(); Nop(); Nop();
      Nop(); Nop(); Nop(); Nop();
      Nop(); Nop(); Nop(); Nop();
      ADS7843_CLK = 0;
    }

    TempRead >>= 4; // rota 4 bits a la derecha.
    TempRead &= 0x0FFF;

  }

  ADS7843_Disable();

  return TempRead;
}


#if defined USE_PRESSURE_READING
/*********************************************************************
 * Function:  ui16 _ADS7843_CalcPressure(uint16_t Z1, uint16_t Z2)
 * @brief 
 * @param 
 * @retval None 
 * Overview:        
 * @note            
 ********************************************************************/
uint16_t _ADS7843_CalcPressure(uint16_t RXpoint, uint16_t Z1, uint16_t Z2){
  float ZTouch;
  ZTouch = (float)((Z2*1.0) / Z1);
  ZTouch = (ZTouch - 1) * RXpoint * DRV_TOUCH_X_PLATE_RESISTANCE ; // X Resistance in Ohms
  ZTouch = ZTouch / 4096.0;
  return (uint16_t ) ZTouch;
}
#endif

/*********************************************************************
 * Function:  ui8 DRV_TOUCH_ADS7843_SPI_PositionDetect(void)
 * @brief 
 * @param 
 * @retval None 
 * Overview:        
 * @note            
 ********************************************************************/
uint8_t  DRV_TOUCH_ADS7843_SPI_PositionDetect(void){
  uint32_t TempX =0;
  uint32_t TempY =0;
  uint32_t TempZ =0;
  uint8_t k;

  for (k=0; k<DRV_ADS7843_FILTER_SAMPLE_POINTS; k++){
    TempX += ads7843_DrvData.data[k].xPoint;
    TempY += ads7843_DrvData.data[k].yPoint;
#if defined USE_PRESSURE_READING
    TempZ += ads7843_DrvData.data[k].zPoint;
#endif
  }
//  TempX = (uint32_t) ((TempX*1.0) / DRV_ADS7843_FILTER_SAMPLE_POINTS);
  adcX = (TempX >> DRV_ADS7843_FILTER_SAMPLE_SHIFT_VAL);
  adcY = (TempY >> DRV_ADS7843_FILTER_SAMPLE_SHIFT_VAL);
#if defined USE_PRESSURE_READING
  adcZ = (TempZ>>3);
#endif

//  if ((adcZ != 0) && (adcZ <= 1000)){
  if (ADS7843_IRQ == 0) {
    if ( (adcX != -1) && (adcY != -1)  ) {
      LastX = adcX;
      LastY = adcY;
      ads7843_DrvData.touchStatus = DRV_TOUCH_POSITION_SINGLE ;    
    } else {
      adcX = -1;
      adcY = -1;
      ads7843_DrvData.touchStatus = DRV_TOUCH_POSITION_SINGLE ;    
    }
    ads7843_DrvData.penState = DRV_TOUCH_PEN_DOWN;
    return 1;
  } else {
    if ((LastX != -1) &&(LastY!= -1)) {
      ads7843_DrvData.touchStatus = DRV_TOUCH_POSITION_SINGLE ;    
    } else {
      ads7843_DrvData.touchStatus = DRV_TOUCH_POSITION_NONE ;    
    }
    ads7843_DrvData.penState = DRV_TOUCH_PEN_UP;

    adcX = -1;
    adcY = -1;
    LastX = -1;
    LastY = -1;
  }
  return (0);    
}


/*****************************************************************************
  Summary:
  Description:
  Remarks:
 ***********************************************************************************/
short DRV_TOUCH_ADS7843_PositionDetect(void) {
  uint16_t TempX,TempY;
  uint8_t k;
//  DRV_ADS7843_OBJECT * pDrvInstance = (DRV_ADS7843_OBJECT *) &ads7843_DrvData;

  if (ads7843_DrvData.MustReadTouch == 1) { // This flag is set in the APP module when called APP_TouchTimer() within the Timer interrupt
    ads7843_DrvData.MustReadTouch=0;
    if (ADS7843_IRQ == 0) {
      TempX=0;TempY=0;
      for(k=0;k<8;k++){
        TempX+=_ADS7843ReadData(ADS7843_READ_X);
      }
      for(k=0;k<8;k++){
        TempY+=_ADS7843ReadData(ADS7843_READ_Y); 
      }

      adcX = (TempX>>3);
      adcY = (TempY>>3);
      
      
      if ( (adcX != -1) && (adcY != -1)  ) {
        LastX = adcX;
        LastY = adcY;
        ads7843_DrvData.touchStatus = DRV_TOUCH_POSITION_SINGLE ;    
      } else {
        adcX = -1;
        adcY = -1;
        ads7843_DrvData.touchStatus = DRV_TOUCH_POSITION_SINGLE ;    
      }
      ads7843_DrvData.penState = DRV_TOUCH_PEN_DOWN;
      return 1;
    } else {
      if ((LastX != -1) &&(LastY!= -1)) {
        ads7843_DrvData.touchStatus = DRV_TOUCH_POSITION_SINGLE ;    
      } else {
        ads7843_DrvData.touchStatus = DRV_TOUCH_POSITION_NONE ;    
      }
      ads7843_DrvData.penState = DRV_TOUCH_PEN_UP;

      adcX = -1;
      adcY = -1;
      LastX = -1;
      LastY = -1;
    }
    return (0);
  } else {
    ads7843_DrvData.touchStatus = DRV_TOUCH_POSITION_NONE ;    
    ads7843_DrvData.penState = DRV_TOUCH_PEN_UNKNOWN;
    return 0;
    
  }

}

/*********************************************************************
 * @brief 
 * @param 
 * @retval None 
 * Overview:        
 * @note            
 ********************************************************************/
DRV_TOUCH_PEN_STATE DRV_TOUCH_ADS7843_TouchPenGet(uint8_t touchNumber) {
//  DRV_ADS7843_OBJECT * pDrvInstance = (DRV_ADS7843_OBJECT *) &ads7843_DrvData;
  
  return (ads7843_DrvData.penState);
}



/*********************************************************************
  Function:
    DRV_TOUCH_POSITION_SINGLE DRV_TOUCH_ADS7843_TouchStatus( const SYS_MODULE_INDEX index )

  Summary:
    Returns the status of the current touch input.

  Description:
    It returns the status of the current touch input.

  Parameters
    None.

  Returns
    It returns the status of the current touch input.
******************************************************************************/
DRV_TOUCH_POSITION_STATUS DRV_TOUCH_ADS7843_TouchStatus( const SYS_MODULE_INDEX index )
{
//    DRV_ADS7843_OBJECT * pDrvInstance = (DRV_ADS7843_OBJECT *)&ads7843_DrvData[index];
    return (ads7843_DrvData.touchStatus);
}


/*********************************************************************
  Function:
    void DRV_TOUCH_ADS7843_TouchDataRead( const SYS_MODULE_INDEX index )

  Summary:
    Notifies the driver that the current touch data has been read

  Description:
    Notifies the driver that the current touch data has been read

  Parameters
    None.

  Returns
    None.
******************************************************************************/
void DRV_TOUCH_ADS7843_TouchDataRead( const SYS_MODULE_INDEX index ) {
//  DRV_ADS7843_OBJECT * pDrvInstance = (DRV_ADS7843_OBJECT *)&ads7843_DrvData[index];
  ads7843_DrvData.touchStatus = DRV_TOUCH_POSITION_NONE;
    
}




/*********************************************************************
 * Function: short DRV_TOUCH_ADS7843_TouchGetX( uint8_t touchNumber )
 *
 * PreCondition: none
 *
 * Input: none
 *
 * Output: x coordinate
 *
 * Side Effects: none
 *
 * Overview: returns x coordinate if touch screen is pressed
 *           and -1 if not
 *
 * Note: none
 *
 ********************************************************************/
short DRV_TOUCH_ADS7843_TouchGetX( uint8_t touchNumber ) {
  long xResult;
  long xPosActual;
  long yPosActual;
  
  xPosActual =  DRV_TOUCH_ADS7843_TouchGetRawX();
  yPosActual = DRV_TOUCH_ADS7843_TouchGetRawY();
  
//  if( CalibMatrix.Divider != 0 ) {
  if(( CalibMatrix.Divider != 0 ) && (xPosActual != -1) && (yPosActual !=-1)) {

          /* Operation order is important since we are doing integer */
          /*  math. Make sure you add all terms together before      */
          /*  dividing, so that the remainder is not rounded off     */
          /*  prematurely.                                           */

    xResult = ( (CalibMatrix.An * xPosActual) + 
                      (CalibMatrix.Bn * yPosActual) + 
                       CalibMatrix.Cn 
                    ) / CalibMatrix.Divider ;
    if (xResult <0) {
      xResult = -1;
    }

  }  else  {
    xResult = -1 ;
  }

  return( (short) xResult ) ;
}

/*********************************************************************
 * Function: short DRV_TOUCH_ADS7843_TouchGetRawX()
 *
 * PreCondition: none
 *
 * Input: none
 *
 * Output: x coordinate
 *
 * Side Effects: none
 *
 * Overview: returns x coordinate if touch screen is pressed
 *           and -1 if not
 *
 * Note: none
 *
 ********************************************************************/
short DRV_TOUCH_ADS7843_TouchGetRawX(void)
{
#ifdef TOUCHSCREEN_RESISTIVE_SWAP_XY
    return adcY;
#else
    return adcX;
#endif
}

/*********************************************************************
 * Function: short DRV_TOUCH_ADS7843_TouchGetY( uint8_t touchNumber )
 *
 * PreCondition: none
 *
 * Input: none
 *
 * Output: y coordinate
 *
 * Side Effects: none
 *
 * Overview: returns y coordinate if touch screen is pressed
 *           and -1 if not
 *
 * Note: none
 *
 ********************************************************************/
short DRV_TOUCH_ADS7843_TouchGetY( uint8_t touchNumber ) {
  long yResult;
  long xPosActual;
  long yPosActual;
  
  xPosActual =  DRV_TOUCH_ADS7843_TouchGetRawX();
  yPosActual = DRV_TOUCH_ADS7843_TouchGetRawY();
  
//  if( CalibMatrix.Divider != 0 ) {
  if(( CalibMatrix.Divider != 0 ) && (xPosActual != -1) && (yPosActual !=-1)) {

          /* Operation order is important since we are doing integer */
          /*  math. Make sure you add all terms together before      */
          /*  dividing, so that the remainder is not rounded off     */
          /*  prematurely.                                           */

//ads7843_DrvData.dispCalibPoints  Screen
//ads7843_DrvData.sampleCalibPoints  Display
    
    yResult = ( (CalibMatrix.Dn * xPosActual) + 
                      (CalibMatrix.En * yPosActual) + 
                       CalibMatrix.Fn 
                    ) / CalibMatrix.Divider ;
    if (yResult <0) {
      yResult = -1;
    }

  } else {
    yResult = -1 ;
  }

  return( (short) yResult ) ;

}

/*********************************************************************
 * Function: short DRV_TOUCH_ADS7843_TouchGetRawY()
 *
 * PreCondition: none
 *
 * Input: none
 *
 * Output: y coordinate
 *
 * Side Effects: none
 *
 * Overview: returns y coordinate if touch screen is pressed
 *           and -1 if not
 *
 * Note: none
 *
 ********************************************************************/
short DRV_TOUCH_ADS7843_TouchGetRawY(void) {
#ifdef TOUCHSCREEN_RESISTIVE_SWAP_XY
    return adcX;
#else
    return adcY;
#endif
}


/*********************************************************************
 * Function:  uint16_t DRV_TOUCH_ADS7843_TouchGetZ( uint8_t touchNumber)
 * @brief 
 * @param 
 * @retval None 
 * Overview:        
 * @note            
 ********************************************************************/
#if defined USE_PRESSURE_READING
uint16_t DRV_TOUCH_ADS7843_TouchGetZ( uint8_t touchNumber){
  return adcZ;
}
#endif


//*********************************************************************
/* Function:
    void DRV_TOUCH_ADS7843_TouchStoreCalibration(void)
	
   Summary:
     Stores calibration parameters into Non-volatile Memory.
   
   Description:
     This function stores calibration parameters into Non-volatile Memory.
   
   Preconditions:
     The NVM initialization function must be called before calling this function.
   
   Parameters:
     None.
   
   Returns:
     None.

   Remarks:
     This API is deprecated and its funcationality is handled via SYSTEM_INITIALIZATION
**************************************************************************/
void DRV_TOUCH_ADS7843_TouchStoreCalibration(void)
{


}

/*********************************************************************
 * Function: void DRV_TOUCH_ADS7843_CalibrationSet(void)
 *
 * PreCondition: Non-volatile memory initialization function must be called before
 *
 * Input: none
 *
 * Output: none
 *
 * Side Effects: none
 *
 * Overview: loads calibration parameters from non-volatile memory
 *
 * Note: none
 *
 ********************************************************************/
void DRV_TOUCH_ADS7843_CalibrationSet(DRV_TOUCH_SAMPLE_POINTS * samplePoints)
{

    xRawTouch[0] = samplePoints->touchCalUlx;
    yRawTouch[0] = samplePoints->touchCalUly;

    xRawTouch[1] = samplePoints->touchCalUrx;
    yRawTouch[1] = samplePoints->touchCalUry;

    xRawTouch[3] = samplePoints->touchCalLlx;
    yRawTouch[3] = samplePoints->touchCalLly;

    xRawTouch[2] = samplePoints->touchCalLrx;
    yRawTouch[2] = samplePoints->touchCalLry;

//    _DRV_TOUCH_ADS7843_CalculateCalPoints();

}

// *****************************************************************************
// *****************************************************************************
// Section: Local functinos
// *****************************************************************************
// *****************************************************************************

/*********************************************************************
 * Function: void _TouchHardwareInit(void)
 *
 * PreCondition: none
 *
 * Input: none
 *
 * Output: none
 *
 * Side Effects: none
 *
 * Overview: Initializes touch screen module.
 *
 * Note: none
 // ADS7843 Touch Screen Controller
#define ADS7843_MSDI_TRIS TRISDbits.TRISD2
#define ADS7843_MSDI      PORTDbits.RD2
#define ADS7843_MSDO_TRIS TRISDbits.TRISD3
#define ADS7843_MSDO      LATDbits.LATD3
#define ADS7843_CLK_TRIS  TRISDbits.TRISD1
#define ADS7843_CLK       LATDbits.LATD1
#define ADS7843_CS_TRIS   TRISDbits.TRISD5
#define ADS7843_CS        LATDbits.LATD5
#define ADS7843_IRQ_TRIS  TRISDbits.TRISD0
#define ADS7843_IRQ       PORTDbits.RD0
#define ADS7843_BUSY_TRIS TRISDbits.TRISD7
#define ADS7843_BUSY      PORTDbits.RD7
#define ADS7843_Enable()  ADS7843_CS = 0;
#define ADS7843_Disable() ADS7843_CS = 1;

 ********************************************************************/
void _DRV_TOUCH_ADS7843_HardwareInit(void *initValues) {
  ADS7843_CS        = 1; 
  ADS7843_CS_TRIS   = 0;
  ADS7843_CLK       = 0;
  ADS7843_CLK_TRIS  = 0;
  ADS7843_MSDI_TRIS = 1;
  ADS7843_MSDO_TRIS = 0;
  ADS7843_MSDO      = 0;
  ADS7843_IRQ_TRIS  = 1;
  ADS7843_BUSY_TRIS = 1;
}




/**********************************************************************
 *
 *     Function: setCalibrationMatrix()
 *
 *  Description: Calling this function with valid input data
 *                in the display and screen input arguments 
 *                causes the calibration factors between the
 *                screen and display points to be calculated,
 *                and the output argument - matrixPtr - to be 
 *                populated.
 *
 *               This function needs to be called only when new
 *                calibration factors are desired.
 *               
 *  
 *  Argument(s): displayPtr (input) - Pointer to an array of three 
 *                                     sample, reference points.
 *               screenPtr (input) - Pointer to the array of touch 
 *                                    screen points corresponding 
 *                                    to the reference display points.
 *               matrixPtr (output) - Pointer to the calibration 
 *                                     matrix computed for the set 
 *                                     of points being provided.
 *
 *
 *  From the article text, recall that the matrix coefficients are
 *   resolved to be the following:
 *
 *
 *      Divider =  (Xs0 - Xs2)*(Ys1 - Ys2) - (Xs1 - Xs2)*(Ys0 - Ys2)
 *
 *
 *
 *                 (Xd0 - Xd2)*(Ys1 - Ys2) - (Xd1 - Xd2)*(Ys0 - Ys2)
 *            A = ---------------------------------------------------
 *                                   Divider
 *
 *
 *                 (Xs0 - Xs2)*(Xd1 - Xd2) - (Xd0 - Xd2)*(Xs1 - Xs2)
 *            B = ---------------------------------------------------
 *                                   Divider
 *
 *
 *                 Ys0*(Xs2*Xd1 - Xs1*Xd2) + 
 *                             Ys1*(Xs0*Xd2 - Xs2*Xd0) + 
 *                                           Ys2*(Xs1*Xd0 - Xs0*Xd1)
 *            C = ---------------------------------------------------
 *                                   Divider
 *
 *
 *                 (Yd0 - Yd2)*(Ys1 - Ys2) - (Yd1 - Yd2)*(Ys0 - Ys2)
 *            D = ---------------------------------------------------
 *                                   Divider
 *
 *
 *                 (Xs0 - Xs2)*(Yd1 - Yd2) - (Yd0 - Yd2)*(Xs1 - Xs2)
 *            E = ---------------------------------------------------
 *                                   Divider
 *
 *
 *                 Ys0*(Xs2*Yd1 - Xs1*Yd2) + 
 *                             Ys1*(Xs0*Yd2 - Xs2*Yd0) + 
 *                                           Ys2*(Xs1*Yd0 - Xs0*Yd1)
 *            F = ---------------------------------------------------
 *                                   Divider
 *
 *
 *       Return: OK - the calibration matrix was correctly 
 *                     calculated and its value is in the 
 *                     output argument.
 *               NOT_OK - an error was detected and the 
 *                         function failed to return a valid
 *                         set of matrix values.
 *                        The only time this sample code returns
 *                        NOT_OK is when Divider == 0
 *
 *
 *
 *                 NOTE!    NOTE!    NOTE!
 *
 *  setCalibrationMatrix() and getDisplayPoint() will do fine
 *  for you as they are, provided that your digitizer         
 *  resolution does not exceed 10 bits (1024 values).  Higher
 *  resolutions may cause the integer operations to overflow
 *  and return incorrect values.  If you wish to use these   
 *  functions with digitizer resolutions of 12 bits (4096    
 *  values) you will either have to a) use 64-bit signed     
 *  integer variables and math, or b) judiciously modify the 
 *  operations to scale results by a factor of 2 or even 4.  
 *
 *
 */
bool _DRV_TOUCH_ADS7843_setCalibrationMatrix( void ) {
  bool  retValue = true;

  CalibMatrix.Divider = ((ads7843_DrvData.sampleCalibPoints[0].xPoint - ads7843_DrvData.sampleCalibPoints[2].xPoint) * 
                         (ads7843_DrvData.sampleCalibPoints[1].yPoint - ads7843_DrvData.sampleCalibPoints[2].yPoint)) - 
                        ((ads7843_DrvData.sampleCalibPoints[1].xPoint - ads7843_DrvData.sampleCalibPoints[2].xPoint) * 
                         (ads7843_DrvData.sampleCalibPoints[0].yPoint - ads7843_DrvData.sampleCalibPoints[2].yPoint)) ;

  if( CalibMatrix.Divider == 0 ) {
      retValue = false ;
  } else {
    CalibMatrix.An = ((ads7843_DrvData.dispCalibPoints[0].xPoint - ads7843_DrvData.dispCalibPoints[2].xPoint) * 
                    (ads7843_DrvData.sampleCalibPoints[1].yPoint - ads7843_DrvData.sampleCalibPoints[2].yPoint)) - 
                    ((ads7843_DrvData.dispCalibPoints[1].xPoint - ads7843_DrvData.dispCalibPoints[2].xPoint) * 
                    (ads7843_DrvData.sampleCalibPoints[0].yPoint - ads7843_DrvData.sampleCalibPoints[2].yPoint)) ;

    CalibMatrix.Bn = ((ads7843_DrvData.sampleCalibPoints[0].xPoint - ads7843_DrvData.sampleCalibPoints[2].xPoint) * (ads7843_DrvData.dispCalibPoints[1].xPoint - ads7843_DrvData.dispCalibPoints[2].xPoint)) - 
                    ((ads7843_DrvData.dispCalibPoints[0].xPoint - ads7843_DrvData.dispCalibPoints[2].xPoint) * (ads7843_DrvData.sampleCalibPoints[1].xPoint - ads7843_DrvData.sampleCalibPoints[2].xPoint)) ;

    CalibMatrix.Cn = (ads7843_DrvData.sampleCalibPoints[2].xPoint * ads7843_DrvData.dispCalibPoints[1].xPoint - ads7843_DrvData.sampleCalibPoints[1].xPoint * ads7843_DrvData.dispCalibPoints[2].xPoint) * ads7843_DrvData.sampleCalibPoints[0].yPoint +
                    (ads7843_DrvData.sampleCalibPoints[0].xPoint * ads7843_DrvData.dispCalibPoints[2].xPoint - ads7843_DrvData.sampleCalibPoints[2].xPoint * ads7843_DrvData.dispCalibPoints[0].xPoint) * ads7843_DrvData.sampleCalibPoints[1].yPoint +
                    (ads7843_DrvData.sampleCalibPoints[1].xPoint * ads7843_DrvData.dispCalibPoints[0].xPoint - ads7843_DrvData.sampleCalibPoints[0].xPoint * ads7843_DrvData.dispCalibPoints[1].xPoint) * ads7843_DrvData.sampleCalibPoints[2].yPoint ;

    CalibMatrix.Dn = ((ads7843_DrvData.dispCalibPoints[0].yPoint - ads7843_DrvData.dispCalibPoints[2].yPoint) * (ads7843_DrvData.sampleCalibPoints[1].yPoint - ads7843_DrvData.sampleCalibPoints[2].yPoint)) - 
                    ((ads7843_DrvData.dispCalibPoints[1].yPoint - ads7843_DrvData.dispCalibPoints[2].yPoint) * (ads7843_DrvData.sampleCalibPoints[0].yPoint - ads7843_DrvData.sampleCalibPoints[2].yPoint)) ;

    CalibMatrix.En = ((ads7843_DrvData.sampleCalibPoints[0].xPoint - ads7843_DrvData.sampleCalibPoints[2].xPoint) * (ads7843_DrvData.dispCalibPoints[1].yPoint - ads7843_DrvData.dispCalibPoints[2].yPoint)) - 
                    ((ads7843_DrvData.dispCalibPoints[0].yPoint - ads7843_DrvData.dispCalibPoints[2].yPoint) * (ads7843_DrvData.sampleCalibPoints[1].xPoint - ads7843_DrvData.sampleCalibPoints[2].xPoint)) ;

    CalibMatrix.Fn = (ads7843_DrvData.sampleCalibPoints[2].xPoint * ads7843_DrvData.dispCalibPoints[1].yPoint - ads7843_DrvData.sampleCalibPoints[1].xPoint * ads7843_DrvData.dispCalibPoints[2].yPoint) * ads7843_DrvData.sampleCalibPoints[0].yPoint +
                    (ads7843_DrvData.sampleCalibPoints[0].xPoint * ads7843_DrvData.dispCalibPoints[2].yPoint - ads7843_DrvData.sampleCalibPoints[2].xPoint * ads7843_DrvData.dispCalibPoints[0].yPoint) * ads7843_DrvData.sampleCalibPoints[1].yPoint +
                    (ads7843_DrvData.sampleCalibPoints[1].xPoint * ads7843_DrvData.dispCalibPoints[0].yPoint - ads7843_DrvData.sampleCalibPoints[0].xPoint * ads7843_DrvData.dispCalibPoints[1].yPoint) * ads7843_DrvData.sampleCalibPoints[2].yPoint ;
  }

  return( retValue ) ;

} /* end of _DRV_TOUCH_ADS7843_setCalibrationMatrix() */





//*********************************************************************
/* Function:
     void DRV_TOUCH_ADS7843_TouchLoadCalibration(void)
  	
   Summary:
     Loads calibration parameters from Non-volatile Memory.
   
   Description:
     This function loads calibration parameters from Non-volatile Memory.
   
   Preconditions:
     The NVM initialization function must be called before calling this function.
   
   Parameters:
     None.
   Returns:
     None.
**************************************************************************/
void DRV_TOUCH_ADS7843_TouchLoadCalibration(DRV_ASD7843_CALIBRATION_MATRIX * Matrix){
  memcpy( (void *)&CalibMatrix, Matrix, sizeof(DRV_ASD7843_CALIBRATION_MATRIX));
//  uint8_t i;
//  for (i = 0; i < sizeof(DRV_ASD7843_CALIBRATION_MATRIX); i++) {
//    CalibMatrix[i] = Matrix[i];
//  }
  
}


/*********************************************************************
 * @brief int8_t DRV_TOUCH_ADS7843_CalibrationStart(void)
 * @param none
 * @retval bool if TURE the touch calibration started OK. 
 *              If FALSE a touch calibration is in process 
 * Overview: Starts a touch calibration machine state        
 * @note            
 *********************************************************************/
bool DRV_TOUCH_ADS7843_CalibrationStart(void){
  if ((ads7843_DrvData.calibrationState == TOUCH_CALIB_UNINIT) || 
      (ads7843_DrvData.calibrationState == TOUCH_CALIB_END) ) {
    ads7843_DrvData.calibrationState = TOUCH_CALIB_INIT;
    return true;
  } else {
    return false; // it's not ready for calibration
  }
}

/*********************************************************************
 * @brief  void DRV_TOUCH_ASD7843_CalibrationTasks(void)
 * @param  None
 * @retval None 
 * Overview: Touch calibration tasks to performe the calibration process       
 * @note            
 *********************************************************************/
void DRV_TOUCH_ASD7843_CalibrationTasks(void){
  static uint32_t timeTics;
  
  switch (ads7843_DrvData.calibrationState) {
    case TOUCH_CALIB_UNINIT: {
      
      break;
    }

    case TOUCH_CALIB_INIT: {
      // Asigna los puntos del display a usar como calibracion
      ads7843_DrvData.dispCalibPoints[0].xPoint = CALIB_X_DISP_POINT_0;
      ads7843_DrvData.dispCalibPoints[0].yPoint = CALIB_Y_DISP_POINT_0;
      ads7843_DrvData.dispCalibPoints[1].xPoint = CALIB_X_DISP_POINT_1;
      ads7843_DrvData.dispCalibPoints[1].yPoint = CALIB_Y_DISP_POINT_1;
      ads7843_DrvData.dispCalibPoints[2].xPoint = CALIB_X_DISP_POINT_2;
      ads7843_DrvData.dispCalibPoints[2].yPoint = CALIB_Y_DISP_POINT_2;


      if (ads7843_DrvData.calibrationFn_ptr.initProcessPromptCallback != NULL) {
          ads7843_DrvData.calibrationFn_ptr.initProcessPromptCallback();
      }
      ads7843_DrvData.calibrationState = TOUCH_CALIB_DRAW_POINT1;
      break;
    }
    
    case TOUCH_CALIB_DRAW_POINT1: {
      if (ads7843_DrvData.calibrationFn_ptr.firstPromptCallback != NULL) {
          ads7843_DrvData.calibrationFn_ptr.firstPromptCallback(&ads7843_DrvData.dispCalibPoints[0],DRAW_POINT);
      }
      ads7843_DrvData.calibrationState = TOUCH_CALIB_WAIT_PRESS1;
      timeTics = GET_TICKS();
    }
    
    case TOUCH_CALIB_WAIT_PRESS1:{
      if (ads7843_DrvData.penState == DRV_TOUCH_PEN_DOWN) {
        if (ads7843_DrvData.calibrationFn_ptr.firstPromptCallback != NULL) {
            ads7843_DrvData.calibrationFn_ptr.firstPromptCallback(&ads7843_DrvData.dispCalibPoints[0],TOUCH_PRESSED);
        }
        if ((GET_TICKS() - timeTics) >= _1SEG_TICKS) {
          ads7843_DrvData.calibrationState = TOUCH_CALIB_WAIT_LIFT1;
          xRawTouch[0] = DRV_TOUCH_ADS7843_TouchGetRawX();
          ads7843_DrvData.sampleCalibPoints[0].xPoint = xRawTouch[0];
          yRawTouch[0] = DRV_TOUCH_ADS7843_TouchGetRawY();
          ads7843_DrvData.sampleCalibPoints[0].yPoint = yRawTouch[0];

          if (ads7843_DrvData.calibrationFn_ptr.firstPromptCallback != NULL) {
              ads7843_DrvData.calibrationFn_ptr.firstPromptCallback(&ads7843_DrvData.dispCalibPoints[0],TOUCH_LIFT);
          }

        }
      } else {
        timeTics = GET_TICKS();
      }
    }break;
    
    case TOUCH_CALIB_WAIT_LIFT1: {
      if (ads7843_DrvData.penState == DRV_TOUCH_PEN_UP) {
        ads7843_DrvData.calibrationState = TOUCH_CALIB_DRAW_POINT2;
      }      
    } break;
    
    case TOUCH_CALIB_DRAW_POINT2: {
      // debe leer el punto y pintar el otro llamando la CB
      
      if (ads7843_DrvData.calibrationFn_ptr.secondPromptCallback != NULL) {
          ads7843_DrvData.calibrationFn_ptr.secondPromptCallback(&ads7843_DrvData.dispCalibPoints[1],DRAW_POINT);
      }
      ads7843_DrvData.calibrationState = TOUCH_CALIB_WAIT_PRESS2;
      timeTics = GET_TICKS();
    }break;

    case TOUCH_CALIB_WAIT_PRESS2:{
      if (ads7843_DrvData.penState == DRV_TOUCH_PEN_DOWN) {
        if (ads7843_DrvData.calibrationFn_ptr.secondPromptCallback != NULL) {
            ads7843_DrvData.calibrationFn_ptr.secondPromptCallback(&ads7843_DrvData.dispCalibPoints[1],TOUCH_PRESSED);
        }
        if ((GET_TICKS() - timeTics) >= _1SEG_TICKS) {
          ads7843_DrvData.calibrationState = TOUCH_CALIB_WAIT_LIFT2;
          xRawTouch[1] = DRV_TOUCH_ADS7843_TouchGetRawX();
          ads7843_DrvData.sampleCalibPoints[1].xPoint = xRawTouch[1];
          yRawTouch[1] = DRV_TOUCH_ADS7843_TouchGetRawY();
          ads7843_DrvData.sampleCalibPoints[1].yPoint = yRawTouch[1];
          if (ads7843_DrvData.calibrationFn_ptr.secondPromptCallback != NULL) {
              ads7843_DrvData.calibrationFn_ptr.secondPromptCallback(&ads7843_DrvData.dispCalibPoints[1],TOUCH_LIFT);
          }
        }
      } else {
        timeTics = GET_TICKS();
      }
    }break;
    
    case TOUCH_CALIB_WAIT_LIFT2: {
      if (ads7843_DrvData.penState == DRV_TOUCH_PEN_UP) {
        ads7843_DrvData.calibrationState = TOUCH_CALIB_DRAW_POINT3;
      }      
    } break;
    
    case TOUCH_CALIB_DRAW_POINT3 : {
      if (ads7843_DrvData.calibrationFn_ptr.thirdPromptCallback!= NULL) {
          ads7843_DrvData.calibrationFn_ptr.thirdPromptCallback(&ads7843_DrvData.dispCalibPoints[2],DRAW_POINT);
      }
      ads7843_DrvData.calibrationState = TOUCH_CALIB_WAIT_PRESS3;
      timeTics = GET_TICKS();
    }break;

    case TOUCH_CALIB_WAIT_PRESS3:{
      if (ads7843_DrvData.penState == DRV_TOUCH_PEN_DOWN) {
        if (ads7843_DrvData.calibrationFn_ptr.thirdPromptCallback!= NULL) {
            ads7843_DrvData.calibrationFn_ptr.thirdPromptCallback(&ads7843_DrvData.dispCalibPoints[2],TOUCH_PRESSED);
        }
        if ((GET_TICKS() - timeTics) >= _1SEG_TICKS) {
          ads7843_DrvData.calibrationState = TOUCH_CALIB_WAIT_LIFT3;
          xRawTouch[2] = DRV_TOUCH_ADS7843_TouchGetRawX();
          ads7843_DrvData.sampleCalibPoints[2].xPoint = xRawTouch[2];
          yRawTouch[2] = DRV_TOUCH_ADS7843_TouchGetRawY();
          ads7843_DrvData.sampleCalibPoints[2].yPoint = yRawTouch[2];
          if (ads7843_DrvData.calibrationFn_ptr.thirdPromptCallback!= NULL) {
              ads7843_DrvData.calibrationFn_ptr.thirdPromptCallback(&ads7843_DrvData.dispCalibPoints[2],TOUCH_LIFT);
          }
       }
      } else {
        timeTics = GET_TICKS();
      }
      
    }break;
    
    case TOUCH_CALIB_WAIT_LIFT3: {
      if (ads7843_DrvData.penState == DRV_TOUCH_PEN_UP) {
        ads7843_DrvData.calibrationState = TOUCH_CALIB_CALCULATE_MATRIX;
      }      
      
      
    } break;

    case TOUCH_CALIB_CALCULATE_MATRIX : {
      if (_DRV_TOUCH_ADS7843_setCalibrationMatrix() == true) {
        ads7843_DrvData.calibrationState = TOUCH_CALIB_CALIBRATED;    
      }
    }break;

    case TOUCH_CALIB_CALIBRATED: {
      if (ads7843_DrvData.calibrationFn_ptr.completeCallback!= NULL) {
          ads7843_DrvData.calibrationFn_ptr.completeCallback();
      }
      ads7843_DrvData.calibrationState = TOUCH_CALIB_STORE_NVM;
    }break;
    
    case TOUCH_CALIB_STORE_NVM:{
      // TODO: Poner un callback para grabar en EEPROM o en NVM
      ads7843_DrvData.calibrationState = TOUCH_CALIB_END;
      if (ads7843_DrvData.calibrationFn_ptr.NVMSaveCalibration!= NULL){
        ads7843_DrvData.calibrationFn_ptr.NVMSaveCalibration(&CalibMatrix);
      }
    }
    
    
    default : {
      
    }
  }
}

/*********************************************************************
 * @brief void DRV_TOUCH_ADS7843_CalibrationSetCallBack(const DRV_TOUCH_ADS7843_CALIBRATION_PROMPT_CALLBACK* cb)
 * @param A pointer to a DRV_TOUCH_ADS7843_CALIBRATION_PROMPT_CALLBACK structure
 *        that contains the pointer to a user call back functions
 * @retval None
 * @Overview: 
 * @Example:
 *   const DRV_TOUCH_ADS7843_CALIBRATION_PROMPT_CALLBACK cb = {
    .initProcessPromptCallback = &TouchWnd_InitCalibrationProcess,
    .firstPromptCallback = &TouchWnd_FirstCalibrationPoint,
    .secondPromptCallback = &TouchWnd_SecondCalibrationPoint,
    .thirdPromptCallback = &TouchWnd_ThirdCalibrationPoint,
    .completeCallback = &TouchWnd_CalibrationComplete,
  };
  DRV_TOUCH_ADS7843_CalibrationSetCallBack(&cb);
     
 * @note            
 *********************************************************************/
void DRV_TOUCH_ADS7843_CalibrationSetCallBack(const DRV_TOUCH_ADS7843_CALIBRATION_PROMPT_CALLBACK* cb){
  if (cb->initProcessPromptCallback != NULL){
    ads7843_DrvData.calibrationFn_ptr.initProcessPromptCallback = cb->initProcessPromptCallback;
  }
  if (cb->firstPromptCallback != NULL) {
    ads7843_DrvData.calibrationFn_ptr.firstPromptCallback = cb->firstPromptCallback;
  }
  if (cb->secondPromptCallback != NULL){
    ads7843_DrvData.calibrationFn_ptr.secondPromptCallback = cb->secondPromptCallback;
  }
  if (cb->thirdPromptCallback != NULL) {
    ads7843_DrvData.calibrationFn_ptr.thirdPromptCallback = cb->thirdPromptCallback;
  }
  if (cb->completeCallback != NULL){
    ads7843_DrvData.calibrationFn_ptr.completeCallback = cb->completeCallback;
  }
  if (cb->NVMSaveCalibration != NULL){
    ads7843_DrvData.calibrationFn_ptr.NVMSaveCalibration= cb->NVMSaveCalibration;
  }
}



/*********************************************************************
 * @brief 
 * @param 
 * @retval None 
 * Overview:        
 * @note  Callback functions when a write _ read sequence is finished
 ********************************************************************/
void _ADS7843_SPI_OnEndEventHandler(DRV_SPI_BUFFER_EVENT buffEvent,
                      DRV_SPI_BUFFER_HANDLE hBufferEvent,
                      void* context ) 
{
  switch(buffEvent) {
    case DRV_SPI_BUFFER_EVENT_COMPLETE: {
      ADS7843_Disable();
      break;
    }
    default: {
      // no deberia llegar aqui nunca
    }
  }
}

/*********************************************************************
 * @brief void _ADS7843_OnSPIEvent(DRV_SPI_BUFFER_EVENT buffEvent,
                      DRV_SPI_BUFFER_HANDLE hBufferEvent,
                      void* context )
 * @param DRV_SPI_BUFFER_EVENT buffEvent
 * This is the event fired by this call back and could be
 *      Buffer is pending to get processed 
    DRV_SPI_BUFFER_EVENT_PENDING,

    /* Buffer is being processed 
    DRV_SPI_BUFFER_EVENT_PROCESSING,

    /* All data from or to the buffer was transferred successfully. 
    DRV_SPI_BUFFER_EVENT_COMPLETE,

    /* There was an error while processing the buffer transfer request.
    DRV_SPI_BUFFER_EVENT_ERROR
 * 
 * @param DRV_SPI_BUFFER_HANDLE hBufferEvent
 * This is the handle to the SPI buffer that started the comunications
 * 
 * @param void* context 
 * 
 * @retval None 
 * Overview:        
 * @note  Callback function when all the bytes are writeen and received from
 *        the ADS7843 via SPI
 ********************************************************************/
void _ADS7843_OnSPIEvent(DRV_SPI_BUFFER_EVENT buffEvent,
                      DRV_SPI_BUFFER_HANDLE hBufferEvent,
                      void* context )
{
  if (buffEvent == DRV_SPI_BUFFER_EVENT_COMPLETE) {
    ads7843_DrvData.spiState++; // Goes to the next SPI State
    ads7843_DrvData.spiTimeOut = 0;
  }
}
  
/*********************************************************************
 * @brief _ADS7843_SPI_OnStartEventHandler(DRV_SPI_BUFFER_EVENT buffEvent,
                      DRV_SPI_BUFFER_HANDLE hBufferEvent,
                      void* context )
 * @param DRV_SPI_BUFFER_EVENT buffEvent
 * This is the event fired by this call back and could be
 *      Buffer is pending to get processed 
    DRV_SPI_BUFFER_EVENT_PENDING,

    /* Buffer is being processed 
    DRV_SPI_BUFFER_EVENT_PROCESSING,

    /* All data from or to the buffer was transferred successfully. 
    DRV_SPI_BUFFER_EVENT_COMPLETE,

    /* There was an error while processing the buffer transfer request.
    DRV_SPI_BUFFER_EVENT_ERROR
 * 
 * @param DRV_SPI_BUFFER_HANDLE hBufferEvent
 * This is the handle to the SPI buffer that started the comunications
 * 
 * @param void* context 
 * This is a pointer to a void structure that is passed for reference to be able to
 * read someting specific in the callback. It helps identify the packet
 * @retval None 
 * Overview:        
 * @note  Callback functions to get the SPI events ONStart and ONEnd
 ********************************************************************/
void _ADS7843_SPI_OnStartEventHandler(DRV_SPI_BUFFER_EVENT buffEvent,
                      DRV_SPI_BUFFER_HANDLE hBufferEvent,
                      void* context )
{
  if (buffEvent == DRV_SPI_BUFFER_EVENT_PROCESSING) {
      ADS7843_Enable();
  }
}


/*******************************************************************************
 End of File
*/

