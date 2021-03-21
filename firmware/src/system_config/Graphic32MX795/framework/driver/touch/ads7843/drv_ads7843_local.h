/*******************************************************************************
 Touch ads7843 Driver Local Interface File
 
  Company:
    Ernesto Pareja J

  File Name:
    drv_ads7843_local.h

  Summary:
    Touch ads7843 Driver interface header file.

  Description:
    This header file describes the macros, data structure and prototypes of the 
    touch ads7843 driver interface.
 ******************************************************************************/


// DOM-IGNORE-BEGIN
// DOM-IGNORE-END

#ifndef _DRV_TOUCH_ADS7843_LOCAL_H
#define _DRV_TOUCH_ADS7843_LOCAL_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include  <cp0defs.h>
#include "driver/touch/drv_touch.h"
#include "drv_ads7843.h"
#include "osal/osal.h"
#include "system/int/sys_int.h"
#include "system/debug/sys_debug.h"

// *****************************************************************************
/* 

  Summary:
    

  Description:
    

  Remarks:
    use this scale factor to avoid working in floating point numbers

*/
#define ADS7843_FREQ  2000000           /* ADS7843 DCLK frequency. */
#define HALFTIME      SYS_CLK_FREQ / ADS7843_FREQ / 4


#define SCALE_FACTOR (1<<DRV_TOUCH_ADS7843_CALIBRATION_SCALE_FACTOR)

#if (DISP_ORIENTATION == 90)
    #define ADC_MaxXGet() (DISP_VER_RESOLUTION - 1)
    #define ADC_MaxYGet() (DISP_HOR_RESOLUTION - 1)
#elif (DISP_ORIENTATION == 270)
    #define ADC_MaxXGet() (DISP_VER_RESOLUTION - 1)
    #define ADC_MaxYGet() (DISP_HOR_RESOLUTION - 1)
#elif (DISP_ORIENTATION == 0)
    #define ADC_MaxXGet() (DISP_HOR_RESOLUTION - 1)
    #define ADC_MaxYGet() (DISP_VER_RESOLUTION - 1)
#elif (DISP_ORIENTATION == 180)
    #define ADC_MaxXGet() (DISP_HOR_RESOLUTION - 1)
    #define ADC_MaxYGet() (DISP_VER_RESOLUTION - 1)
#endif


#define   DRV_ADS7843_USE_SPI_MODULE    // Use the hardware SPI Module
  

#undef USE_PRESSURE_READING    // Z Pressure is not enabled

// ***** ADS7843 READ CODES WITH DIFERENTIAL READING CONFIG ******
#define ADS7843_READ_X          0b11010000 // IRQ Enable    / 12 bits /Dif Reading 
#define ADS7843_READ_Y          0b10010000 // IRQ Enable    / 12 bits /Dif Reading    
#if defined USE_PRESSURE_READING
  #define ADS7843_READ_Z1       0b10111000 // IRQ Enable    / 8 bits /Dif Reading 
  #define ADS7843_READ_Z2       0b11001000 // IRQ Enable    / 8 bits /Dif Reading
#endif




// Display coordinates to 3 points used in the calibration process
#define CALIB_X_DISP_POINT_0  50
#define CALIB_Y_DISP_POINT_0  50
#define CALIB_X_DISP_POINT_1  190
#define CALIB_Y_DISP_POINT_1  110
#define CALIB_X_DISP_POINT_2  110
#define CALIB_Y_DISP_POINT_2  270

/*****************************************************************************
  Summary:
  Description:
  Remarks:
*****************************************************************************/
#define CAL_X_INSET    (((ADC_MaxXGet()+1)*(DRV_TOUCH_ADS7843_CALIBRATION_INSET>>1))/100)

/*****************************************************************************
  Summary:
  Description:
  Remarks:
******************************************************************************/
#define CAL_Y_INSET    (((ADC_MaxYGet()+1)*(DRV_TOUCH_ADS7843_CALIBRATION_INSET>>1))/100)

/*****************************************************************************
  Summary:
  Description:
  Remarks:
******************************************************************************/
#define DRV_ADS7843_CALIBRATION_POINTS     3 // Calibration points
#define DRV_ADS7843_FILTER_SAMPLE_POINTS    4 // Points to make the average of the reading
#define DRV_ADS7843_FILTER_SAMPLE_SHIFT_VAL 2 // Index to shif the average result for easy dividing by 22, 4, 8 depending on sample points
#define DRV_ADS7843_MAX_SPI_TIME_OUT    150000 // Max cicles for waiting for touch controller to respond



/* */
typedef enum {
  ADS7843_IDLE,
  ADS7843_READING,
  ADS7843_DATA_OK,
} DRV_ADS7843_STATES;

/* */
typedef enum {
  ADS7843_SPI_OPEN_ERROR    = -3,
  ADS7843_SPI_TIME_OUT      = -2,
  ADS7843_SPI_NOT_USED      = -1,
  ADS7843_SPI_READY         =  0,
  ADS7843_SPI_INIT_SEQUENCE,
  ADS7843_SPI_SEND_COMMAND_X,
  ADS7843_SPI_WAIT_FOR_COMMAND_X,
  ADS7843_SPI_GET_READ_X,
  ADS7843_SPI_SEND_COMMAND_Y,
  ADS7843_SPI_WAIT_FOR_COMMAND_Y,
  ADS7843_SPI_GET_READ_Y,
#if defined USE_PRESSURE_READING
  ADS7843_SPI_SEND_COMMAND_Z1,
  ADS7843_SPI_WAIT_FOR_COMMAND_Z1,
  ADS7843_SPI_GET_READ_Z1,
  ADS7843_SPI_SEND_COMMAND_Z2,
  ADS7843_SPI_WAIT_FOR_COMMAND_Z2,
  ADS7843_SPI_GET_READ_Z2,
#endif
  ADS7843_SPI_DATA_READY,
} DRV_ADS7843_SPI_STATES;


/* */
typedef enum {
  TOUCH_CALIB_UNINIT = -1,
  TOUCH_CALIB_INIT = 0,
  TOUCH_CALIB_DRAW_POINT1,
  TOUCH_CALIB_WAIT_PRESS1,
  TOUCH_CALIB_WAIT_LIFT1,
  TOUCH_CALIB_DRAW_POINT2,
  TOUCH_CALIB_WAIT_PRESS2,
  TOUCH_CALIB_WAIT_LIFT2,
  TOUCH_CALIB_DRAW_POINT3,
  TOUCH_CALIB_WAIT_PRESS3,
  TOUCH_CALIB_WAIT_LIFT3,
  TOUCH_CALIB_CALCULATE_MATRIX,
  TOUCH_CALIB_CALIBRATED,
  TOUCH_CALIB_STORE_NVM,
  TOUCH_CALIB_END,
} DRV_ADS7843_CALIBRATION_STATES;


/*****************************************************************************
  Summary:
  Description:
  Remarks:
******************************************************************************/
typedef struct {
  /* */
  SYS_STATUS       status;
  
  /* */
  SYS_MODULE_INDEX touchId;

  /* */
  bool              isExclusive;

  /* */
  uint8_t           numClients;

  /* */
  uint8_t          orientation;          

  /* */
  uint16_t          horizontalResolution; 

  /* */
  uint16_t                  verticalResolution;

  /* Reading State*/
  DRV_ADS7843_STATES        state;
  
  /* Flag to read the touch screen controller*/ 
  bool                      MustReadTouch;

  /* Touch status */
  DRV_TOUCH_POSITION_STATUS touchStatus;

  DRV_TOUCH_PEN_STATE       penState;

  /* Index of the SPI PORT*/
  SYS_MODULE_INDEX          spiId;
    
  /* Driver Handle del SPI module*/
  DRV_HANDLE                drvSPIHandle;
  
  /* Estado del driver*/
  DRV_ADS7843_SPI_STATES    spiState;
  
  /* State machine for calibration process*/
  DRV_ADS7843_CALIBRATION_STATES calibrationState;
  
  /* Time out counter to break a falt transmision*/
  uint32_t                  spiTimeOut;
  
  /* Callback function for envents on SPI operation Start and STOP */
  DRV_SPI_CLIENT_DATA       drvCallBacks;

    /* Read buffer handle */
  DRV_SPI_BUFFER_HANDLE   drvSPIRDBUFHandle;

  /* SPI Driver TX buffer  */
  uint8_t           drvSPITXbuffer[3];

  /* SPI Driver RX buffer  */
  uint8_t           drvSPIRXbuffer[4]; //ADS7843 returns 2 bytes for the maximum 12 bits resolution


  /* Historia de los ultimos puntos para hacer filtro*/
  DRV_ADS7843_TOUCH_POINT_DATA    data[DRV_ADS7843_FILTER_SAMPLE_POINTS];

  /* Indice del array de puntos capturados*/
  uint8_t                   touchIndex;
  
  /* Estructura de punteros a funciones de calibraci?n*/
  DRV_TOUCH_ADS7843_CALIBRATION_PROMPT_CALLBACK calibrationFn_ptr;
  
  /* Coordenadas de los puntos ideales del display usados en la calibraci?n*/
  DRV_ADS7843_TOUCH_POINT_DATA dispCalibPoints[DRV_ADS7843_CALIBRATION_POINTS];

  /* Coordenadas de los puntos leidos del touch en la calibraci?n*/
  DRV_ADS7843_TOUCH_POINT_DATA sampleCalibPoints[DRV_ADS7843_CALIBRATION_POINTS];
  
} DRV_ADS7843_OBJECT;

/*****************************************************************************
  Summary:
  Description:
  Remarks:
******************************************************************************/
typedef struct {
    /* Driver Object associated with the client */
    DRV_ADS7843_OBJECT * driverObject;

    /* The intent with which the client was opened */
    DRV_IO_INTENT         intent;

} DRV_ADS7843_CLIENT_OBJECT;

//******************************************************************************
// Local functions
//******************************************************************************
void  _DRV_TOUCH_ADS7843_HardwareInit       (void *initValues);
void  _DRV_TOUCH_ADS7843_CalculateCalPoints (void);
uint16_t ADS7843ReadData(uint8_t Cmd);

#endif

/*******************************************************************************
 End of File
*/

