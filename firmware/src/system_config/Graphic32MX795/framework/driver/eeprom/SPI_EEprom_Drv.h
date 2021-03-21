/* 
 * File:   SPI_EEprom_Drv.h
 * Author: epareja
 *
 * Created on 18 de noviembre de 2017, 10:26 PM
 */

#ifndef SPI_EEPROM_DRV_H
  #define	SPI_EEPROM_DRV_H

/*********************************************************************
/*          INCLUDES         
/*********************************************************************/
#include "../driver/spi/drv_spi.h"
  
/*********************************************************************
/*          CONSTANT DEFINITIONS
/*********************************************************************/
#define   MAX_NUM_OF_BYTES_IN_BUF     250

/* EEPROM OP CODES FOR 25LC1024 EEPROM*/
#define EEPROM_WRITE_STATUS_OP_CODE     0b00000001
#define EEPROM_WRITE_COMMAND_OP_CODE    0b00000010
#define EEPROM_READ_COMMAND_OP_CODE     0b00000011
#define EEPROM_READ_STATUS_OP_CODE      0b00000101
#define EEPROM_WRITE_ENABLE_OP_CODE     0b00000110
#define EEPROM_WRITE_DISABLE_OP_CODE    0b00000100
#define EEPROM_PAGE_ERASE_OP_CODE       0b01000010
#define EEPROM_SECTOR_ERASE_OP_CODE     0b11011000
#define EEPROM_CHIP_ERASE_OP_CODE       0b11000111
#define EEPROM_POWER_DOWN_OP_CODE       0b10111001
#define EEPROM_POWER_UP_OP_CODE         0b10101011


/*********************************************************************
/*      TYPE DEFINITIONS             
/*********************************************************************/
typedef unsigned char EEPROM_DATA_TYPE;

typedef enum{
  WR_SEND_WRITE_INIT = 0,
  WR_SEND_WRITE_STATUS_CMD,
  WR_WAIT_FOR_STATUS_REPLY,
  WR_SEND_WREN_CMD,
  WR_ENABLE_STATUS_CHECK,
  WR_SEND_WRITE_CMD,
  WR_WAIT_FOR_WRITE_COMPLETE,
  WR_COMPLETED,
  WR_STATUS_COMPLETED
} EEPROM_WR_STATES;

typedef enum{
  RD_SEND_READ_INIT  = 0,
  RD_SEND_STATUS_CODE_CMD,
//  RD_WAIT_FOR_STATUS_CMD_REPLY,
//  RD_GET_STATUS_DATA,
  RD_BUSY_STATUS_CHECK,
  RD_SEND_READ_CMD,
//  RD_WAIT_FOR_READ_CMD_REPLY,
//  RD_GET_DATA,
  RD_WAIT_FOR_DATA,
  RD_COMPLETE
} EEPROM_RD_STATES;


typedef enum {
  EEPROM_OK,
  EEPROM_FAIL,
  EEPROM_IN_PROCESS,
} EEPROM_RESULT;



typedef enum  {
  EEPROM_CLOSED,
  EEPROM_UNINITIALIZED,
  EEPROM_INITIALIZED,
  EEPROM_STOPED,
  EEPROM_READY,
  EEPROM_WRITING,
  EEPROM_READING,
  EEPROM_ERASING,
  EEPROM_ERROR,
    
} EEPROM_STATES;
  


typedef struct { 
    /* Application current state */
    EEPROM_STATES              state;
    
    /* Write Buffer current state */
    EEPROM_WR_STATES writeState;
    
    /* Read Buffer current state */
    EEPROM_RD_STATES readState;

    
    /* SPI Driver Handle  */
    DRV_HANDLE              drvSPIHandle;

    /* Write buffer handle */
    DRV_SPI_BUFFER_HANDLE   drvSPIWRBUFHandle;
    
    /* Write and Read Address Start Point */
    uint32_t                Address;
    
    /* Total of bytes to be read or write to EEPROM */
    uint16_t                NDataBytes;

    /* Read buffer handle */
    DRV_SPI_BUFFER_HANDLE   drvSPIRDBUFHandle;

    /* SPI Driver TX buffer  */
    uint8_t           drvSPITXbuffer[MAX_NUM_OF_BYTES_IN_BUF];
    
    /* Pointer to the remote buffer to be written into EEPROM*/
    uint8_t *         remoteTXbuffer;

    /* SPI Driver RX buffer  */
    uint8_t           drvSPIRXbuffer[MAX_NUM_OF_BYTES_IN_BUF];
    
    /* Pointer to the remote buffer to store the data read from EEPROM*/
    uint8_t *         remoteRXbuffer;

    /* Callback function for envents on SPI operation Start and STOP */
    DRV_SPI_CLIENT_DATA drvCallBacks;
    
    /* Callback function for end of Write operation  */
    void  (*EndEEPROMWriteCallback) ( uint16_t nReadBytes );

    /* Callback function for end of Read operation  */
    void  (*EndEEPROMReadCallback) ( uint16_t nReadBytes );
    
    /* Callback function for end of job operation to external app*/
    void (*EndJobHandle) (DRV_SPI_BUFFER_EVENT event,
        DRV_SPI_BUFFER_HANDLE bufferHandle, void * context );
} EEPROM_DRV_DATA;


  
/*********************************************************************
/*            PUBLIC FUNCTION DECLARATIONS                  
/*********************************************************************/
void SPI_EEPROM_Init(void);
EEPROM_RESULT SPI_EEPROM_drv_Open(SYS_MODULE_INDEX drv_index);
EEPROM_RESULT SPI_EEPROM_drv_Close(SYS_MODULE_INDEX drv_index);
void  SPI_EEPROM_Tasks(void);

EEPROM_RESULT SPI_EEPROM_Read(uint8_t * BuffPtr, uint16_t nbytes);
EEPROM_RESULT SPI_EEPROM_InitRead(uint8_t * BuffPtr, uint32_t Address, uint16_t nbytes, void * EndReadCB);
EEPROM_RESULT SPI_EEPROM_Write(uint8_t * BuffPtr, uint16_t nbytes);
EEPROM_RESULT SPI_EEPROM_InitWrite(uint8_t * BuffPtr, uint32_t Address, uint16_t nbytes, void * EndWriteCB);
EEPROM_RESULT SPI_EEPROM_WriteRead(uint8_t * BuffOutPtr, uint16_t txBytes,
                                   uint8_t * BuffInPtr, uint16_t rxBytes);


EEPROM_RESULT SPI_EEPROM_ErasePage(uint32_t Address);  // 512 pages of 256 bytes eac
EEPROM_RESULT SPI_EEPROM_EraseSector(uint32_t Address);  // 4 sectors of 32KB each
EEPROM_RESULT SPI_EEPROM_EraseChip(void);
EEPROM_RESULT SPI_EEPROM_PowerDown(void);
EEPROM_RESULT SPI_EEPROM_PowerUp(void);
EEPROM_STATES SPI_EEPROM_GetStatus(void);
bool SPI_EEPROM_IsActive(void);

void SPI_EEPROM_SetCallBack(void * OnWriteEnd ,void * OnReadEnd);







  /*********************************************************************
   * @brief uint8_t SPI_EEPROM_ReadByte(
   * @param 
   * @retval None 
   * Overview:        
   * @note            
   ********************************************************************/
  


#endif	/* SPI_EEPROM_DRV_H */

