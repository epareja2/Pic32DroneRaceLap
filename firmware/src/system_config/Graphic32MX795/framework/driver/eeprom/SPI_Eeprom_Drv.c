/*! \file *********************************************************************
 *
 * \brief "DESCRIPCION DEL MODULO".
 *
 * "DESCRIPCION MAS AMPLIA"
 *
 * - File:               SPI_Eeprom_Drv.c
 * - Compiler:           MPLABX X32 V1.44  MPLAB 4.05  Harmony 2.04b
 * - Supported devices:  
 *
 * \author               Ernesto Pareja  (epareja)
 *
 * REVISION HISTORY:
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Author            Date      Comments on that revision
 *----------------------------------------------------------------------
 * Epareja       18 de noviembre de 2017, 10:25 PM  Creation of file
 * 
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * ADDITIONAL NOTES:
 *
 *****************************************************************************/



/*********************************************************************
 /*                      INCLUDES        
 /*********************************************************************/
#include <stdint.h>
#include "drv_spi.h"
#include "SPI_EEprom_Drv.h"
#include "system/debug/sys_debug.h"





/*********************************************************************
 /*                      GLOBAL VARIABLES        
 /*********************************************************************/
EEPROM_DRV_DATA SPI_eepromDrvData =  {
  .state = EEPROM_UNINITIALIZED  //Initialize appData structure. 

};

/*********************************************************************
 /*                      PRIVATE FUNCTION DECLARATIONS        
 /*********************************************************************/
void SPI_OnEndEventHandler(DRV_SPI_BUFFER_EVENT buffEvent,
                      DRV_SPI_BUFFER_HANDLE hBufferEvent,
                      void* context ); 
void SPI_OnStartEventHandler(DRV_SPI_BUFFER_EVENT buffEvent,
                      DRV_SPI_BUFFER_HANDLE hBufferEvent,
                      void* context ); 

uint8_t SPI_EEPROM_WritingTasks(void);
uint8_t SPI_EEPROM_ReadingTasks(void);
uint8_t SPI_EEPROM_StatusTasks(void);


/*********************************************************************
 /*                      CODE IMPLEMENTATION        
 /*********************************************************************/


/*********************************************************************
/*                        CALLBACK FUNCTION FOR SPI DRIVER
/*********************************************************************/


/*********************************************************************
 * @brief void SPI_EEPROM_SetCallBack((void*)OnWriteEnd , (void *) OnReadEnd);
 * @param 
 * @retval None 
 * Overview:        
 * @note  Callback functions to get the SPI events ONStart and ONEnd
 ********************************************************************/
void SPI_EEPROM_SetCallBack(void * OnWriteEnd , void * OnReadEnd){
  SPI_eepromDrvData.EndEEPROMWriteCallback = OnWriteEnd;
  SPI_eepromDrvData.EndEEPROMReadCallback = OnReadEnd;
}


/*********************************************************************
 * @brief 
 * @param 
 * @retval None 
 * Overview:        
 * @note  Callback functions to get the SPI events ONStart and ONEnd
 ********************************************************************/
void SPI_OnStartEventHandler(DRV_SPI_BUFFER_EVENT buffEvent,
                      DRV_SPI_BUFFER_HANDLE hBufferEvent,
                      void* context ) 
{
  switch(buffEvent) {
    case DRV_SPI_BUFFER_EVENT_PROCESSING: {
      Nop();
      EEPROM_CS_Enable();
      break;
    }
    default: {
      // no debería llegar aquí nunca
    }
  }
}



/*********************************************************************
 * @brief 
 * @param 
 * @retval None 
 * Overview:        
 * @note  Callback functions to get the SPI events ONStart and ONEnd
 ********************************************************************/
void SPI_OnEndEventHandler(DRV_SPI_BUFFER_EVENT buffEvent,
                      DRV_SPI_BUFFER_HANDLE hBufferEvent,
                      void* context ) 
{
  switch(buffEvent) {
    case DRV_SPI_BUFFER_EVENT_COMPLETE: {
      Nop();
      EEPROM_CS_Disable();
      break;
    }
    default: {
      // no debería llegar aquí nunca
    }
  }
}


/*********************************************************************
 * @brief void SPI_EEPROM_Init(void);
 * @param None
 * @retval None 
 * Overview:        
 * @note            
 ********************************************************************/
void SPI_EEPROM_Init(void){
  EEPROM_HOLD_Disable();
  EEPROM_WP_Disable();
  EEPROM_CS_Disable();

  EEPROM_CS_TRIS = 0; // Output
  EEPROM_WP_TRIS = 0;
  EEPROM_HOLD_TRIS = 0;

  SPI_eepromDrvData.state = EEPROM_INITIALIZED;
  SPI_eepromDrvData.drvSPIHandle = DRV_HANDLE_INVALID;
  SPI_eepromDrvData.drvCallBacks.baudRate = 0;
  SPI_eepromDrvData.drvCallBacks.operationStarting = SPI_OnStartEventHandler;
  SPI_eepromDrvData.drvCallBacks.operationEnded = SPI_OnEndEventHandler;
  
}


/*********************************************************************
 * @brief bool SPI_EEPROM_drv_Open(uint8_t drv_index);
 * @param 
 * @retval None 
 * Overview:        
 * @note            
 ********************************************************************/
EEPROM_RESULT SPI_EEPROM_drv_Open(SYS_MODULE_INDEX drv_index){
  SPI_eepromDrvData.drvSPIHandle = DRV_SPI_Open(drv_index,
                                                DRV_IO_INTENT_READWRITE );
  if(SPI_eepromDrvData.drvSPIHandle != DRV_HANDLE_INVALID)  {
    SPI_eepromDrvData.state = EEPROM_INITIALIZED;
    DRV_SPI_ClientConfigure(SPI_eepromDrvData.drvSPIHandle, &SPI_eepromDrvData.drvCallBacks);

  }
  else {
    SPI_eepromDrvData.state = EEPROM_ERROR;
  }
}


/*********************************************************************
 * @brief EEPROM_RESULT SPI_EEPROM_Close(uint8_t drv_index);
 * @param 
 * @retval None 
 * Overview:        
 * @note            
 ********************************************************************/
EEPROM_RESULT SPI_EEPROM_drv_Close(SYS_MODULE_INDEX drv_index){
  SPI_eepromDrvData.state = EEPROM_INITIALIZED;
  if (SPI_eepromDrvData.drvSPIHandle != NULL) {
    DRV_SPI_Close(SPI_eepromDrvData.drvSPIHandle);
  }
}

/*********************************************************************
 * @brief EEPROM_RESULT SPI_EEPROM_Close(uint8_t drv_index);
 * @param 
 * @retval None 
 * Overview:        
 * @note            
 ********************************************************************/
bool SPI_EEPROM_Check_Transfer_Status(DRV_SPI_BUFFER_HANDLE drvBufferHandle) {
  if(DRV_SPI_BUFFER_EVENT_COMPLETE & DRV_SPI_BufferStatus (drvBufferHandle)) {
    return true;
  } else {
    return false;
  }
}


/*********************************************************************
 * @brief 
 * @param 
 * @retval None 
 * Overview:        
 * @note            
 ********************************************************************/
void  SPI_EEPROM_Tasks(void){
  switch (SPI_eepromDrvData.state){
    case EEPROM_READING: {
      if (SPI_EEPROM_ReadingTasks() == true) {
        SPI_eepromDrvData.state = EEPROM_READY;
      }
    } break;
    
    case EEPROM_WRITING: {
      if (SPI_EEPROM_WritingTasks() == true) {
        SPI_eepromDrvData.state = EEPROM_READY;
      }
      
    }break;
    
    case EEPROM_ERASING: {
      
    }break;
    
    default: {
    }
  }
}



/*********************************************************************
 * @brief 
 * @param 
 * @retval None 
 * Overview:        
 * @note            
 ********************************************************************/
uint8_t SPI_EEPROM_StatusTasks(void){
  uint8_t num_of_bytes;
  switch(SPI_eepromDrvData.writeState) {
    case WR_SEND_WRITE_INIT:
    case WR_SEND_WRITE_STATUS_CMD: {
      /* Assert CS Line */
      EEPROM_CS_Enable();

      /* Add Write status op code, data to the buffer */
      SPI_eepromDrvData.drvSPITXbuffer[0] = EEPROM_WRITE_STATUS_OP_CODE;
      SPI_eepromDrvData.drvSPITXbuffer[1] = 0x00; /* EEPROM BP1 = 0, BP0 = 0 */
      SPI_eepromDrvData.drvSPITXbuffer[2] = 0; /* Dummy byte */

      /* Number of bytes to transfer */
      num_of_bytes = 3;

      /* Add to the write buffer and transmit*/
      SPI_EEPROM_Write(&SPI_eepromDrvData.drvSPITXbuffer[0], num_of_bytes);
      SPI_eepromDrvData.writeState = WR_WAIT_FOR_STATUS_REPLY;

      break;
    }
    case WR_WAIT_FOR_STATUS_REPLY: {
        /* Check if the transfer status is success or not */
        if(SPI_EEPROM_Check_Transfer_Status(SPI_eepromDrvData.drvSPIWRBUFHandle)) {
            /* Deassert CS Line */
            EEPROM_CS_Disable();

            SPI_eepromDrvData.writeState = WR_STATUS_COMPLETED;
        }
        else {
            /* Transfer Status - Wait untill staus becomes true*/
            SPI_eepromDrvData.writeState = WR_WAIT_FOR_STATUS_REPLY;
        }
        break;
    }
    case WR_STATUS_COMPLETED: {
      SPI_eepromDrvData.writeState = WR_COMPLETED;
      return true;
    }
  }
  return false;
}


/*********************************************************************
 * @brief 
 * @param 
 * @retval None 
 * Overview:        
 * @note            
 ********************************************************************/
uint8_t SPI_EEPROM_WritingTasks(void){
  uint8_t num_of_bytes;
  static uint16_t dataCount;
  uint16_t loop;
  
  switch(SPI_eepromDrvData.writeState) {
    case WR_SEND_WRITE_INIT: 
    case WR_SEND_WREN_CMD: {

        /* Add Write Enable op code to the buffer */
        SPI_eepromDrvData.drvSPITXbuffer[0] = EEPROM_WRITE_ENABLE_OP_CODE;
//        SPI_eepromDrvData.drvSPITXbuffer[1] = 0; /* Dummy byte */

        /* Number of bytes to transfer */
        num_of_bytes = 1;

        /* Add to the write buffer and transmit*/
        SPI_EEPROM_Write(&SPI_eepromDrvData.drvSPITXbuffer[0], num_of_bytes);
        SPI_eepromDrvData.writeState = WR_ENABLE_STATUS_CHECK;

        break;
    }
    case WR_ENABLE_STATUS_CHECK: {
        /* Check if the transfer status is success or not */
        if(SPI_EEPROM_Check_Transfer_Status(SPI_eepromDrvData.drvSPIWRBUFHandle)) {
            /* Deassert CS Line */
//            EEPROM_CS_Disable();

            SPI_eepromDrvData.writeState = WR_SEND_WRITE_CMD;
        }
        else {
            /* Transfer Status - Wait untill staus becomes true*/
            SPI_eepromDrvData.writeState = WR_ENABLE_STATUS_CHECK;
        }
        break;
    }
    case WR_SEND_WRITE_CMD: {

        // TODO: Se debe verificar que no se escriban datos de páginas diferentes
        
        SPI_eepromDrvData.drvSPITXbuffer[0] = EEPROM_WRITE_COMMAND_OP_CODE;
        SPI_eepromDrvData.drvSPITXbuffer[1] = (SPI_eepromDrvData.Address>>16) & 0xFF; /* Address - 23 - 16 bits */
        SPI_eepromDrvData.drvSPITXbuffer[2] = (SPI_eepromDrvData.Address>>8) & 0xFF; /* Address - 15 - 8 */
        SPI_eepromDrvData.drvSPITXbuffer[3] = SPI_eepromDrvData.Address & 0xFF; /* Address 7- 0 bits*/

        dataCount = 4;

        /* Add the data to the buffer */
        for(loop =0; loop < SPI_eepromDrvData.NDataBytes; loop++) {
          SPI_eepromDrvData.drvSPITXbuffer[dataCount++] = SPI_eepromDrvData.remoteTXbuffer[loop];
        }
        /* Number of bytes to transfer */
        num_of_bytes = dataCount; //opcode + address + data

        /* Add the write buffer and transmit*/
        SPI_EEPROM_Write(&SPI_eepromDrvData.drvSPITXbuffer[0], num_of_bytes);
        SPI_eepromDrvData.writeState = WR_WAIT_FOR_WRITE_COMPLETE;

        break;
        
    }
    case WR_WAIT_FOR_WRITE_COMPLETE: {
        /* Check if the transfer status is success or not */
        if(SPI_EEPROM_Check_Transfer_Status(SPI_eepromDrvData.drvSPIWRBUFHandle)) {
//            EEPROM_CS_Disable();

            SPI_eepromDrvData.writeState = WR_COMPLETED;
        } else {
            /* Transfer Status - Wait untill staus becomes true*/
            SPI_eepromDrvData.writeState = WR_WAIT_FOR_WRITE_COMPLETE;
        }
        break;
    }
    case WR_COMPLETED: {
        /* return done to app task */
        SPI_eepromDrvData.state = EEPROM_READY;
        if (SPI_eepromDrvData.EndEEPROMWriteCallback != NULL) {
          SPI_eepromDrvData.EndEEPROMWriteCallback( SPI_eepromDrvData.NDataBytes); // Calls the Callback function of Main APP
        }
        return true;
        
        break;
    }
    default:
        break;
  }
  return false;
  
}

/*********************************************************************
 * @brief 
 * @param 
 * @retval None 
 * Overview:        
 * @note            
 ********************************************************************/
uint8_t SPI_EEPROM_ReadingTasks(void){
  uint16_t num_of_bytes;
  uint16_t count;

  switch(SPI_eepromDrvData.readState) { 
    /* Send read status commmand to check EEPROM is busy or not! */
    case RD_SEND_READ_INIT:
    case RD_SEND_STATUS_CODE_CMD: {
      /* Assert the CS Line */
//      EEPROM_CS_Enable();
      SPI_eepromDrvData.state = EEPROM_READING;

      /* Add the EEPROM Read STATUS OP Code to the buffer*/
      SPI_eepromDrvData.drvSPITXbuffer[0] = EEPROM_READ_STATUS_OP_CODE;
//      SPI_eepromDrvData.drvSPITXbuffer[1] = 0; /* Dummy byte */

      /* Number of bytes to transfer */
      num_of_bytes = 1;

      /* Add to the write buffer to transmit and the receiver buffer*/
      SPI_EEPROM_WriteRead(&SPI_eepromDrvData.drvSPITXbuffer[0],num_of_bytes,
                           &SPI_eepromDrvData.drvSPIRXbuffer[0],num_of_bytes+1);
      SPI_eepromDrvData.readState = RD_BUSY_STATUS_CHECK;

      break;
    }


    case RD_BUSY_STATUS_CHECK: {
      /* Check if the transfer status is success or not */
      if(SPI_EEPROM_Check_Transfer_Status(SPI_eepromDrvData.drvSPIWRBUFHandle)) {

          //Check if Write in Progress (WIP) is true
          if(SPI_eepromDrvData.drvSPIRXbuffer[1] & 0x01) {
            /* Re-Send status command again to check the busy stautus */
            SPI_eepromDrvData.readState = RD_SEND_STATUS_CODE_CMD;
          } else {
            /* Transmit read command to read data from EEPROM memory */
            SPI_eepromDrvData.readState = RD_SEND_READ_CMD;
          }
      } else {
        /* Transfer Status - Wait untill staus becomes true*/
        SPI_eepromDrvData.readState = RD_BUSY_STATUS_CHECK;
      }
      break;
    }
    case RD_SEND_READ_CMD: {
      /* Add read command op code & 16-bit beginning address to buffer. 
       * This sequence picks the data byte from the selected location and 
       * holds it in the shift register of the SPI interface of the EEPROM */
      SPI_eepromDrvData.drvSPITXbuffer[0] = EEPROM_READ_COMMAND_OP_CODE;
      
      SPI_eepromDrvData.drvSPITXbuffer[1] = (SPI_eepromDrvData.Address>>16) & 0xFF; /* Address - 23 - 16 bits */
      SPI_eepromDrvData.drvSPITXbuffer[2] = (SPI_eepromDrvData.Address>>8) & 0xFF; /* Address - 15 - 8 */
      SPI_eepromDrvData.drvSPITXbuffer[3] = SPI_eepromDrvData.Address & 0xFF; /* Address 7- 0 bits*/

      /* Number of bytes to transfer */
      num_of_bytes = 4;

      /* Add to the write buffer and transmit */
      SPI_EEPROM_WriteRead(&SPI_eepromDrvData.drvSPITXbuffer[0], num_of_bytes,
                           &SPI_eepromDrvData.drvSPIRXbuffer[0],SPI_eepromDrvData.NDataBytes+num_of_bytes);
      SPI_eepromDrvData.readState = RD_WAIT_FOR_DATA;

      break;
    }

    case RD_WAIT_FOR_DATA: {
      /* Check if the transfer status is success or not */
      if(SPI_EEPROM_Check_Transfer_Status(SPI_eepromDrvData.drvSPIWRBUFHandle)) {
        /* Deassert the CS Line */
//        EEPROM_CS_Disable();

        SPI_eepromDrvData.readState = RD_COMPLETE;
      } else {
        /* Transfer Status - Wait untill staus becomes true*/
        SPI_eepromDrvData.readState = RD_WAIT_FOR_DATA;
      }
      break;
    }
    case RD_COMPLETE: {
      /* Copy the received data to the local buffer */
      for(count = 0; count < SPI_eepromDrvData.NDataBytes;count++) {
        // Starts reading in 4 position of the buffer because it reads 4 dummy bytes when sending
        // the COMD and 3 byte address to the memory
        SPI_eepromDrvData.remoteRXbuffer[count] = SPI_eepromDrvData.drvSPIRXbuffer[count+4];
      } 
      SPI_eepromDrvData.state = EEPROM_READY;
      if (SPI_eepromDrvData.EndEEPROMReadCallback != NULL) {
        SPI_eepromDrvData.EndEEPROMReadCallback((uint16_t) count); // Go to the Callback Function in Main APP
      }
      /* return done to app task */
      return true;
      break;
    }
    default:
      break;
  }

  return false;
}


/*********************************************************************
 * @brief EEPROM_RESULT SPI_EEPROM_InitRead(uint8_t * BuffPtr, uint32_t Address, 
 *                                    uint16_t nbytes, void * EndReadCB)
 * @param uint8_t * BuffPtr
 * this is a Pointer to a uint8_t memory location to store the read data.
 * This could be a pointer to a structure also.
 * The buffer needs to be 4 bytes bigger than the bytes read because the use of
 * simultaneously Writing and reading routine of the SPI
 
 * @param uint32_t Address
 * This is the 24 bit eeprom address to begin reading 
 
 * @param uint16_t nbytes
 * The number of bytes that will be read from memory
 * 
 * @param void * EndReadCB
 * Pointer to a user function that is called when the reading is done!
 * Is defined like
 * void  NameOfFuction( uint16_t nReadBytes );
 * 
 * @retval EEPROM_RESULT
 *  EEPROM_OK : The process is started with no problem
 *  EEPROM_FAIL : There was an error because the EEPROM driver is not initialized
 *  EEPROM_IN_PROCESS : another process is still in progress.
 * Overview:        
 * @Example
 * // Define the call back function
 *  void DemoReadEEPromOnEnd(uint16_t nReadBytes );
 * //the use of the function
 *  SPI_EEPROM_InitRead(&Data[0],Address,nBytes,&DemoReadEEPromOnEnd);
 *
 * @note            
 ********************************************************************/
EEPROM_RESULT SPI_EEPROM_InitRead(uint8_t * BuffPtr, uint32_t Address, uint16_t nbytes, void * EndReadCB){

  if ((SPI_eepromDrvData.state == EEPROM_READY) || 
      (SPI_eepromDrvData.state == EEPROM_INITIALIZED)) {
    if (EndReadCB != NULL){
      SPI_eepromDrvData.EndEEPROMReadCallback = EndReadCB;
    }
    SPI_eepromDrvData.Address = Address;
    SPI_eepromDrvData.NDataBytes = nbytes;
    SPI_eepromDrvData.remoteRXbuffer = BuffPtr;
    SPI_eepromDrvData.state = EEPROM_READING;
    SPI_eepromDrvData.readState = RD_SEND_READ_INIT;
    return EEPROM_OK;
  } else if (SPI_eepromDrvData.state == EEPROM_UNINITIALIZED){
    return EEPROM_FAIL;
  } else {
    return EEPROM_IN_PROCESS;
  }
}


/*********************************************************************
 * @brief 
 * @param 
 * @retval None 
 * Overview:        
 * @note            
 ********************************************************************/
EEPROM_RESULT SPI_EEPROM_Read(uint8_t * BuffPtr, uint16_t nbytes){
  /* Add the buffer pointer to read the data from EEPROM */
  SPI_eepromDrvData.drvSPIRDBUFHandle = DRV_SPI_BufferAddRead( SPI_eepromDrvData.drvSPIHandle, 
                                          BuffPtr, 
                                          nbytes, NULL, NULL);
}

/*********************************************************************
 * @brief 
 * @param 
 * @retval None 
 * Overview:        
 * @note            
 ********************************************************************/
bool SPI_EEPROM_IsActive(void){
  return (SPI_eepromDrvData.state != EEPROM_READY);
}


/*********************************************************************
 * @brief 
 * @param 
 * @retval None 
 * Overview:        
 * @note            
 ********************************************************************/
EEPROM_RESULT SPI_EEPROM_Write(uint8_t * BuffPtr, uint16_t nbytes){
  /* Add the buffer to transmit */
  SPI_eepromDrvData.drvSPIWRBUFHandle = DRV_SPI_BufferAddWrite(SPI_eepromDrvData.drvSPIHandle,
                                        BuffPtr, nbytes, NULL, NULL);
  
}

EEPROM_RESULT SPI_EEPROM_WriteRead(uint8_t * BuffOutPtr, uint16_t txBytes,
                                  uint8_t * BuffInPtr, uint16_t rxBytes)
{
  /* Add the buffer to transmit */
  SPI_eepromDrvData.drvSPIWRBUFHandle = DRV_SPI_BufferAddWriteRead(SPI_eepromDrvData.drvSPIHandle,
                                        BuffOutPtr, txBytes, BuffInPtr, rxBytes, NULL, NULL);
  
}

/*********************************************************************
 * @brief 
 * @param 
 * @retval None 
 * Overview:        
 * @note            
 ********************************************************************/
EEPROM_RESULT SPI_EEPROM_InitWrite(uint8_t * BuffPtr, uint32_t Address, uint16_t nbytes, void * EndWriteCB){
  if ((SPI_eepromDrvData.state == EEPROM_READY) ||
      (SPI_eepromDrvData.state == EEPROM_INITIALIZED)) {
    SPI_eepromDrvData.Address = Address;
    SPI_eepromDrvData.NDataBytes = nbytes;
    SPI_eepromDrvData.remoteTXbuffer = BuffPtr;
    SPI_eepromDrvData.state = EEPROM_WRITING;
    SPI_eepromDrvData.writeState = WR_SEND_WRITE_INIT;
    if (EndWriteCB != NULL) {
      SPI_eepromDrvData.EndEEPROMWriteCallback = EndWriteCB;
    }
    
    return EEPROM_OK;
  } else if (SPI_eepromDrvData.state == EEPROM_UNINITIALIZED){
    return EEPROM_FAIL;
  } else {
    return EEPROM_IN_PROCESS;
  }
}

/*********************************************************************
 * @brief 
 * @param 
 * @retval None 
 * Overview:        
 * @note            
 ********************************************************************/
EEPROM_RESULT SPI_EEPROM_ErasePage(uint32_t Address){  // 512 pages of 256 bytes eac
  
}


/*********************************************************************
 * @brief 
 * @param 
 * @retval None 
 * Overview:        
 * @note            
 ********************************************************************/
EEPROM_RESULT SPI_EEPROM_EraseSector(uint32_t Address){  // 4 sectors of 32KB each
 // TODO: Ter  
}


/*********************************************************************
 * @brief 
 * @param 
 * @retval None 
 * Overview:        
 * @note            
 ********************************************************************/
EEPROM_RESULT SPI_EEPROM_EraseChip(void){
  
}


/*********************************************************************
 * @brief 
 * @param 
 * @retval None 
 * Overview:        
 * @note            
 ********************************************************************/
EEPROM_RESULT SPI_EEPROM_PowerDown(void){
  
}


/*********************************************************************
 * @brief 
 * @param 
 * @retval None 
 * Overview:        
 * @note            
 ********************************************************************/
EEPROM_RESULT SPI_EEPROM_PowerUp(void){
  
}


/*********************************************************************
 * @brief 
 * @param 
 * @retval None 
 * Overview:        
 * @note            
 ********************************************************************/
EEPROM_STATES SPI_EEPROM_GetStatus(void){
  return SPI_eepromDrvData.state;  
}








