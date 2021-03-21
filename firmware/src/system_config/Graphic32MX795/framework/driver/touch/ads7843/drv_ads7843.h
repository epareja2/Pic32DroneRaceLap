/*******************************************************************************
 Touch ads7843 Driver Local Interface File
 
  Company:
 Ernesto Pareja J

  File Name:
    drv_ads7843.h

  Summary:
    Touch ads7843 Driver interface header file.

  Description:
    This header file describes the macros, data structure and prototypes of the 
    touch ads7843 driver interface.
 ******************************************************************************/



#ifndef _DRV_TOUCH_ADS7843_H
#define _DRV_TOUCH_ADS7843_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <xc.h>
#include "driver/touch/drv_touch.h"
#include <stdint.h>

// DOM-IGNORE-BEGIN 
#ifdef __cplusplus
    extern "C" {
#endif
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Macros
// *****************************************************************************
// *****************************************************************************

// Use this macro to debug the touch screen panel 
// this will enable the use of debugging functions in the C file.
// It assumes that the graphics portion is working.
// #define ENABLE_DEBUG_TOUCHSCREEN


/*****************************************************************************
  Macro:
    ADS7843 Driver Handle

  Summary:
    Driver handle.

  Description:
    Touch screen controller interfacing with the 10-bit Analog-to-Digital (ADC)
    converter device.

  Remarks:
    None
*****************************************************************************/
typedef uintptr_t DRV_TOUCH_ADS7843_HANDLE;



// *****************************************************************************
/* Macro: 
    ADS7843 Driver Invalid Handle

  Summary:
    Definition of an invalid handle.

  Description:
    This is the definition of an invalid handle. An invalid handle
    is returned by DRV_ADS7843_RawRead and DRV_ADS7843_RawRead
    functions if the request was not successful.

  Remarks:
    None.
*****************************************************************************/
#define DRV_TOUCH_ADS7843_HANDLE_INVALID ((DRV_TOUCH_ADS7843_HANDLE)(-1))

/* Matriz de transformacion para calibracion segun algoritmo de Carlos E. Vidales*/
typedef struct  {
  int32_t An;     /* A = An/Divider */
  int32_t Bn;     /* B = Bn/Divider */
  int32_t Cn;     /* C = Cn/Divider */
  int32_t Dn;     /* D = Dn/Divider */
  int32_t En;     /* E = En/Divider */
  int32_t Fn;     /* F = Fn/Divider */
  int32_t Divider ;
} DRV_ASD7843_CALIBRATION_MATRIX;

/* Define los puntos del display que va usar como calibracion*/
typedef struct  {
  uint16_t xPos;
  uint16_t yPos;
} DRV_ADS7843_CALIBRATION_POINTS_COORD;

/* */
typedef struct {
  uint16_t xPoint;
  uint16_t yPoint;
#if defined USE_PRESSURE_READING
  uint8_t  zPoint;
#endif
} DRV_ADS7843_TOUCH_POINT_DATA;

/* It's used to tell the callback calibration functions in wich state is it*/
typedef enum  {
  DRAW_POINT,
  TOUCH_PRESSED,
  TOUCH_LIFT,
  TOUCH_END
} DRV_ADS7843_MICRO_STATE;



// *****************************************************************************
/* TOUCH Driver Calibration Initialization Data

  Summary:
    Defines the callback functions required to inform the user of touch and release
    targets.

  Description:
    This data type defines the callback function pointers required to inform
    of touch and release targets. The driver will invoke each callback in sequential
    order. The host code can display graphic and/or textual content to direct the
    user when a where on the LCD display to touch and release.

  Remarks:
    None.
*******************************************************************************/
typedef struct {
    /* init calibration process */
    void         (*initProcessPromptCallback) ( void );

    /* first calibration target */
    void         (*firstPromptCallback) ( DRV_ADS7843_TOUCH_POINT_DATA * point, DRV_ADS7843_MICRO_STATE state);

    /* second calibration target */
    void         (*secondPromptCallback) ( DRV_ADS7843_TOUCH_POINT_DATA * point, DRV_ADS7843_MICRO_STATE state);

    /* third calibration target */
    void         (*thirdPromptCallback) ( DRV_ADS7843_TOUCH_POINT_DATA * point, DRV_ADS7843_MICRO_STATE state);

    /* complete calibration */
    void         (*completeCallback)( void );
    
    /* Save in NVM callback function with the pointer of the matrix as parameter*/
    void         (*NVMSaveCalibration) ( DRV_ASD7843_CALIBRATION_MATRIX * Matrix);

} DRV_TOUCH_ADS7843_CALIBRATION_PROMPT_CALLBACK;


// *****************************************************************************
/* Macro:
    ADS7843 Driver Module Index Numbers

  Summary:
    ADS7843 driver index definitions.

  Description:
    These constants provide the 10-bit ADC Driver index definitions.

  Remarks:
    These constants should be used in place of hard-coded numeric literals.

    These values should be passed into the DRV_ADS7843_Initialize and
    DRV_ADS7843_Open functions to identify the driver instance in use.
*/

#define DRV_TOUCH_ADS7843_INDEX_0         0
#define DRV_TOUCH_ADS7843_INDEX_1         1

#define MAX_X_TOUCH_HISTORY               8
#define MAX_Y_TOUCH_HISTORY               8

// *****************************************************************************
/* Macro:
    ADS7843 Driver Module Index Count

  Summary:
    Number of valid ADS7843 driver indices.

  Description:
    This constant identifies the number of valid 10-bit ADC Driver indices.

  Remarks:
    This constant should be used in place of hard-coded numeric literals.

    This value is derived from device-specific header files defined as part of the
    peripheral libraries.
*/

#define DRV_TOUCH_ADS7843_INDEX_COUNT     2

typedef enum {
  ADS7843_ID_1 = 0,
  ADS7843_NUMBER_OF_MODULES
} DRV_ADS7843_MODULE_ID;





// *****************************************************************************
// *****************************************************************************
// Section: Interface Routines - System Level
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Function:
    SYS_MODULE_OBJ DRV_TOUCH_ADS7843_Initialize( const SYS_MODULE_INDEX index,
                                           const SYS_MODULE_INIT * const init )

  Summary:
    Initializes the 10-bit ADC Driver instance for the specified driver index

  Description:
    This function initializes the 10-bit ADC Driver instance for the specified driver
    index, making it ready for clients to open and use it. The initialization
    data is specified by the 'init' parameter. The initialization may fail if the
    number of driver objects allocated are insufficient or if the specified
    driver instance is already initialized. The driver instance index is
    independent of the 10-bit ADC Driver module ID. For example, driver instance 0 can be
    assigned to ADS78432.  If the driver is built statically, then some of the
    initialization parameters are overridden by configuration macros. Refer to
    the description of the DRV_TOUCH_ADS7843_INIT data structure for more details on
    which members on this data structure are overridden.

  Precondition:
    None.

  Parameters:
    index  - Identifier for the instance to be initialized.  Please note this
             is not the 10-bit ADC Driver ID.  The hardware 10-bit ADC Driver ID 
			 is set in the initialization structure.  This is the index of the 
			 driver index to use.
    init   - Pointer to a data structure containing any data necessary to
             initialize the driver. If this pointer is NULL, the driver
             uses the static initialization override macros for each
             member of the initialization data structure.

  Returns:
    If successful, returns a valid handle to a driver instance object.
    Otherwise, returns SYS_MODULE_OBJ_INVALID.

  Example:
    <code>
    DRV_TOUCH_ADS7843_INIT        init;
    SYS_MODULE_OBJ      objectHandle;

    // Populate the ADS7843 initialization structure
    init.spiId              = ADS7843_ID_1;

    objectHandle = DRV_TOUCH_ADS7843_Initialize(DRV_TOUCH_ADS7843_INDEX_1, (SYS_MODULE_INIT*)usartInitData);
    if (SYS_MODULE_OBJ_INVALID == objectHandle)
    {
        // Handle error
    }
    </code>
  Remarks:
    This routine must be called before any other ADS7843 routine is called.

    This routine should only be called once during system initialization
    unless DRV_TOUCH_ADS7843_Deinitialize is called to deinitialize the driver
    instance. This routine will NEVER block for hardware access.
**************************************************************************/
SYS_MODULE_OBJ DRV_TOUCH_ADS7843_Initialize( const SYS_MODULE_INDEX index,
                                           const SYS_MODULE_INIT * const init );

//*************************************************************************
/*
  Function:
    void DRV_TOUCH_ADS7843_Deinitialize ( SYS_MODULE_OBJ object )

  Summary:
    Deinitializes the specified instance of the ADS7843 driver module.

  Description:
    This function deinitializes the specified instance of the 10-bit ADC Driver 
	module, disabling its operation (and any hardware) and invalidates all of the
    internal data.

  Preconditions:
    DRV_TOUCH_ADS7843_Initialize must have been called before calling this
    routine and a valid SYS_MODULE_OBJ must have been returned.

  Parameters:
    object -  Driver object handle, returned from DRV_TOUCH_ADS7843_Initialize

  Returns:
    None.

  Example:
    <code>
    SYS_MODULE_OBJ      object;     //  Returned from DRV_TOUCH_ADS7843_Initialize
    SYS_STATUS          status;

    DRV_TOUCH_ADS7843_Deinitialize ( object );

    status = DRV_TOUCH_ADS7843_Status( object );
    if( SYS_MODULE_UNINITIALIZED == status )
    {
        // Check again later if you need to know
        // when the driver is deinitialized.
    }
    </code>

  Remarks:
    Once the Initialize operation has been called, the Deinitialize
    operation must be called before the Initialize operation can be called
    again.

    This function will NEVER block waiting for hardware. If the operation
    requires time to allow the hardware to complete, this will be reported
    by the DRV_TOUCH_ADS7843_Status operation. The system has to use 
	DRV_TOUCH_ADS7843_Status to determine when the module is in the ready state.
**************************************************************************/
void DRV_TOUCH_ADS7843_Deinitialize ( SYS_MODULE_OBJ object );


//**************************************************************************
/*
  Function:
    SYS_STATUS DRV_TOUCH_ADS7843_Status ( SYS_MODULE_OBJ object )

  Summary:
    Provides the current status of the ADS7843 driver module.

  Description:
    This function provides the current status of the ADS7843 driver module.

  Preconditions:
    DRV_TOUCH_ADS7843_Initialize must have been called before calling
    this function.

  Parameters:
    object -  Driver object handle, returned from DRV_TOUCH_ADS7843_Initialize

  Returns:
    SYS_STATUS_READY - Indicates that the driver is busy with a previous
    system level operation and cannot start another

  Example:
    <code>
    SYS_MODULE_OBJ      object;     // Returned from DRV_TOUCH_ADS7843_Initialize
    SYS_STATUS          status;

    status = DRV_TOUCH_ADS7843_Status( object );
    if( SYS_STATUS_READY != status )
    {
        // Handle error
    }
    </code>

  Remarks:
    Any value greater than SYS_STATUS_READY is also a normal running state
    in which the driver is ready to accept new operations.

    SYS_MODULE_UNINITIALIZED - Indicates that the driver has been
    deinitialized

    This value is less than SYS_STATUS_ERROR.

    This function can be used to determine when any of the driver's module
    level operations has completed.

    If the status operation returns SYS_STATUS_BUSY, the previous operation
    has not yet completed. Once the status operation returns
    SYS_STATUS_READY, any previous operations have completed.

    The value of SYS_STATUS_ERROR is negative (-1). Any value less than
    that is also an error state.

    This function will NEVER block waiting for hardware.

    If the Status operation returns an error value, the error may be
    cleared by calling the reinitialize operation. If that fails, the
    deinitialize operation will need to be called, followed by the
    initialize operation to return to normal operations.
**************************************************************************/
SYS_STATUS DRV_TOUCH_ADS7843_Status ( SYS_MODULE_OBJ object );


// *****************************************************************************
/* Function:
    void DRV_TOUCH_ADS7843_Tasks ( SYS_MODULE_OBJ object );

  Summary:
    Maintains the driver's state machine and implements its ISR.

  Description:
	This routine is used to maintain the driver's internal state
	machine and implement its transmit ISR for interrupt-driven implementations.
	In polling mode, this function should be called from the SYS_Tasks
	function. In Interrupt mode, this function should be called in the transmit
	interrupt service routine of the USART that is associated with this USART
	driver hardware instance.

  Precondition:
    DRV_TOUCH_ADS7843_Initialize must have been called for the specified
    10-bit ADC Driver instance.

  Parameters:
    object      - Object handle for the specified driver instance (returned from
                  DRV_TOUCH_ADS7843_Initialize)

  Returns:
    None.

  Example:
    <code>
    SYS_MODULE_OBJ      object;     // Returned from DRV_TOUCH_ADS7843_Initialize

    while( true )
    {
        DRV_TOUCH_ADS7843_Tasks ( object );

        // Do other tasks
    }
    </code>

  Remarks:
    This function is normally not called directly by an application.  It is
    called by the system's Tasks routine (SYS_Tasks) or by the appropriate raw
    ISR.

    This function may execute in an ISR context and will never block or access any
    resources that may cause it to block.
**************************************************************************/
void DRV_TOUCH_ADS7843_Tasks ( SYS_MODULE_OBJ object );


/*********************************************************************
 * @brief 
 * @param 
 * @retval None 
 * Overview:        
 * @note            
 ********************************************************************/
DRV_TOUCH_PEN_STATE DRV_TOUCH_ADS7843_TouchPenGet(uint8_t touchNumber);


// *****************************************************************************
// *****************************************************************************
// Section: Interface Routines - Client Level
// *****************************************************************************
// *****************************************************************************
void DRV_TOUCH_ADS7843_SetTouchFlag(void);

//**************************************************************************
/*
  Function:
    DRV_HANDLE DRV_TOUCH_ADS7843_Open ( const SYS_MODULE_INDEX drvIndex,
                                         const DRV_IO_INTENT    intent )

  Summary:
    Opens the specified ADS7843 driver instance and returns a handle to it.
	
  Description:
    This function opens the specified Touch driver instance and provides a
    handle that must be provided to all other client-level operations to
    identify the caller and the instance of the driver. The ioIntent
    parameter defines how the client interacts with this driver instance.

    The DRV_IO_INTENT_BLOCKING and DRV_IO_INTENT_NONBLOCKING ioIntent
    options additionally affect the behavior of the DRV_USART_Read() and
    DRV_USART_Write() functions. If the ioIntent is
    DRV_IO_INTENT_NONBLOCKING, then these function will not block even if
    the required amount of data could not be processed. If the ioIntent is
    DRV_IO_INTENT_BLOCKING, these functions will block until the required
    amount of data is processed.

    If ioIntent is DRV_IO_INTENT_READ, the client will only be read from
    the driver. If ioIntent is DRV_IO_INTENT_WRITE, the client will only be
    able to write to the driver. If the ioIntent in
    DRV_IO_INTENT_READWRITE, the client will be able to do both, read and
    write.

    Specifying a DRV_IO_INTENT_EXCLUSIVE will cause the driver to provide
    exclusive access to this client. The driver cannot be opened by any
    other client.
	
  Preconditions:
    DRV_TOUCH_ADS7843_Initialize must have been called before calling
    this function.
	
  Parameters:
    drvIndex -  Index of the driver initialized with DRV_TOUCH_ADS7843_Initialize.
                Please note this is not the SPI id.
    intent -    Zero or more of the values from the enumeration
                DRV_IO_INTENT ORed together to indicate the intended use of
                the driver
  Returns:
    If successful, the routine returns a valid open-instance handle (a
    number identifying both the caller and the module instance).

    If an error occurs, the return value is DRV_HANDLE_INVALID. An error
    can occur when the following is true:
      * if the number of client objects allocated via
        DRV_TOUCH_ADS7843_CLIENTS_NUMBER is insufficient
      * if the client is trying to open the driver but driver has been
        opened exclusively by another client
      * if the driver hardware instance being opened is not initialized or
        is invalid
		
  Example:
    <code>
    DRV_HANDLE  handle;

    handle = DRV_TOUCH_ADS7843_Open( DRV_TOUCH_ADS7843_INDEX_0, DRV_IO_INTENT_EXCLUSIVE );

    if( DRV_HANDLE_INVALID == handle )
    {
        // Unable to open the driver
    }
    </code>
	
  Remarks:
    The handle returned is valid until the DRV_TOUCH_ADS7843_Close routine is
    called. This routine will NEVER block waiting for hardware. If the
    requested intent flags are not supported, the routine will return
    DRV_HANDLE_INVALID. This function is thread safe in a RTOS application.
    It should not be called in an ISR.
**************************************************************************/

DRV_HANDLE DRV_TOUCH_ADS7843_Open ( const SYS_MODULE_INDEX drvIndex,
                         const DRV_IO_INTENT    intent );

// *****************************************************************************
/* Function:
    void DRV_TOUCH_ADS7843_Close ( DRV_HANDLE handle )

  Summary:
    Closes an opened instance of the 10-bit ADC Driver.

  Description:
    This function closes an opened instance of the 10-bit ADC Driver, invalidating 
	the handle.

  Precondition:
    DRV_TOUCH_ADS7843_Initialize must have been called for the specified
    ADS7843 driver instance.

    DRV_TOUCH_ADS7843_Open must have been called to obtain a valid opened device 
	handle.

  Parameters:
    handle       - A valid open-instance handle, returned from the driver's
                   open routine

  Returns:
    None

  Example:
    <code>
    DRV_HANDLE handle;  // Returned from DRV_TOUCH_ADS7843_Open

    DRV_TOUCH_ADS7843_Close ( handle );
    </code>

  Remarks:
	After calling this routine, the handle passed in "handle" must not be used
    with any of the remaining driver routines.  A new handle must be obtained by
    calling DRV_TOUCH_ADS7843_Open before the caller may use the driver again.  This
    function is thread safe in a RTOS application.

    Usually there is no need for the driver client to verify that the Close
    operation has completed.
**************************************************************************/
void DRV_TOUCH_ADS7843_Close ( DRV_HANDLE handle );


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

**************************************************************************/
DRV_TOUCH_POSITION_STATUS DRV_TOUCH_ADS7843_TouchStatus( const SYS_MODULE_INDEX index );


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

**************************************************************************/
void DRV_TOUCH_ADS7843_TouchDataRead( const SYS_MODULE_INDEX index );
short DRV_TOUCH_ADS7843_TouchGetX( uint8_t touchNumber );
short DRV_TOUCH_ADS7843_TouchGetRawX(void);
short DRV_TOUCH_ADS7843_TouchGetY( uint8_t touchNumber );
short DRV_TOUCH_ADS7843_TouchGetRawY( void );
#if defined USE_PRESSURE_READING
uint16_t DRV_TOUCH_ADS7843_TouchGetZ( uint8_t touchNumber);
#endif



void DRV_TOUCH_ADS7843_TouchStoreCalibration( void );
void DRV_TOUCH_ADS7843_TouchLoadCalibration(DRV_ASD7843_CALIBRATION_MATRIX * Matrix);
void DRV_TOUCH_ADS7843_CalibrationSet(DRV_TOUCH_SAMPLE_POINTS * samplePoints);
void DRV_TOUCH_ASD7843_CalibrationTasks(void);
bool DRV_TOUCH_ADS7843_CalibrationStart(void);
void DRV_TOUCH_ADS7843_Calibrate ( const DRV_TOUCH_ADS7843_CALIBRATION_PROMPT_CALLBACK * prompt );
void DRV_TOUCH_ADS7843_CalibrationSetCallBack(const DRV_TOUCH_ADS7843_CALIBRATION_PROMPT_CALLBACK * cb);



short DRV_TOUCH_ADS7843_PositionDetect(void);
uint8_t  DRV_TOUCH_ADS7843_SPI_PositionDetect(void);

#ifdef __cplusplus
    }
#endif
    
#endif //_DRV_TOUCH_ADS7843_H
