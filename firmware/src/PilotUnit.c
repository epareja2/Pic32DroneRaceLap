/*! \file *********************************************************************
 *
 * - File:               PilotUnit.c
 * - Compiler:           MPLABX X32 V2.30  MPLAB 5.3  Harmony 2.06
 * - Supported devices:  
 *
 * \author               Ernesto Pareja  (epareja)
 *
 * REVISION HISTORY:
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Author            Date      Comments on that revision
 *----------------------------------------------------------------------
 * Epareja       7 de Abril de 2020, 9:05 PM  Creation of file (Cuarentena Coronavirus)
 * 
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * ADDITIONAL NOTES:
 *
 *****************************************************************************/
 


/*********************************************************************
 /*                      INCLUDES        
 /*********************************************************************/
#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include "PilotUnit.h"
#include "RX5808.h"
#include "EEProm_Address.h"
#include "driver/eeprom/SPI_EEprom_Drv.h"
#include "app.h"





/*********************************************************************
 /*                      GLOBAL VARIABLES        
 /*********************************************************************/
bool  isPilotDataConfigLoaded;

/*********************************************************************
 /*                      PRIVATE FUNCTION DECLARATIONS        
 /*********************************************************************/

/*********************************************************************
 /*                      CODE IMPLEMENTATION        
 /*********************************************************************/



void PilotDataInit(void){
  isPilotDataConfigLoaded = false;
  LoadAllPilotConfigData_eeprom();
}


/*********************************************************************
 * @brief 
 * @param 
 * @retval None 
 * Overview:        
 * @note  
 ********************************************************************/
void LoadPilotConfigData_eeprom(uint8_t PilotId){
  SPI_EEPROM_InitRead((uint8_t *)&PilotData[PilotId],(ADDR_PILOTS_DATA_INIT + sizeof(PILOT_DATA)*PilotId),
                      sizeof(PILOT_DATA),&PilotUnit_OnLoadConfigData);
}

 
/*********************************************************************
 * @brief 
 * @param 
 * @retval None 
 * Overview:        
 * @note  
 ********************************************************************/
void LoadAllPilotConfigData_eeprom(void){
  volatile uint16_t  size;
  volatile uint8_t Addr;
  size = sizeof(PILOT_DATA);
  size = size * MAX_PILOTS; 
  Addr = ADDR_PILOTS_DATA_INIT;
  SPI_EEPROM_InitRead((uint8_t *)&PilotData[0], Addr,
                     size ,&PilotUnit_OnLoadConfigData);
  
}


bool IsPilotDataLoaded(void){

  return isPilotDataConfigLoaded;
}

/*********************************************************************
 * @brief Callback function thas is called when the saving in eeprom
 *        is completed
 * @param nBytes: The number of bytes that was actually written into eeprom
 * @retval None 
 * Overview:        
 * @note  
 ********************************************************************/
void PilotUnit_OnLoadConfigData(uint16_t nBytes){
  uint8_t i;
  for (i = 0; i < MAX_PILOTS; i++) {
    if ( (PilotData[i].Band < MAX_BANDS) && (PilotData[i].Channel < 8)) {
      PilotData[i].Freq = RX5808_GetFreqGHZ(PilotData[i].Band, PilotData[i].Channel);
    }

  }
  isPilotDataConfigLoaded = true; // variable global
}


/*********************************************************************
 * @brief 
 * @param 
 * @retval None 
 * Overview:        
 * @note  
 ********************************************************************/
bool SaveFreqPilotConfigData(uint8_t PilotId, void * SaveCallBack){
  uint32_t Address;
  uint8_t Offset;
  uint8_t *p1, *p2;
  
  p1 = &PilotData[0].Band;
  p2 = (uint8_t *)&PilotData[0];
  Offset =   p1 - p2; // Calcula el offset de la estructura donde inicia el campo Band
  Address = sizeof (PILOT_DATA);
  Address = ADDR_PILOTS_DATA_INIT + (Address * PilotId); 
  Address = Address + Offset; // Calcula la dirección donde lo va a guardar en eeprom
  PilotData[PilotId].Freq = RX5808_GetFreqGHZ(PilotData[PilotId].Band,PilotData[PilotId].Channel); // Ensure the correct freq value
  if (SPI_EEPROM_InitWrite((uint8_t *)&PilotData[PilotId].Band, Address, 2, SaveCallBack) == EEPROM_OK)
    return true;
  else
    return false;
}


/*********************************************************************
 * @brief 
 * @param 
 * @retval None 
 * Overview:        
 * @note  
 ********************************************************************/
bool SaveEnablePilotConfigData(uint8_t PilotId, void * SaveCallBack){
  volatile uint32_t Address;
  volatile uint8_t Offset;
  volatile uint8_t *p1, *p2;
  p1 = (uint8_t *)&PilotData[0].Enabled;
  p2 = (uint8_t *)&PilotData[0];
  Offset =   p1 - p2; // Calcula el offset de la estructura donde inicia el campo Band
  Address = sizeof (PILOT_DATA);
  Address = ADDR_PILOTS_DATA_INIT + (Address * PilotId); 
  Address = Address + Offset; // Calcula la dirección donde lo va a guardar en eeprom
  if (SPI_EEPROM_InitWrite((uint8_t *)&PilotData[PilotId].Enabled, Address, 1, SaveCallBack) == EEPROM_OK)
    return true;
  else
    return false;
}

/*********************************************************************
 * @brief 
 * @param 
 * @retval None 
 * Overview:        
 * @note  
 ********************************************************************/
bool SavePilotConfigData(uint8_t PilotId, void * SaveCallBack){
  volatile uint32_t Address;
  
  Address = (sizeof(PILOT_DATA)*PilotId); // Calcula la dirección donde lo va a guardar en eeprom
  Address = Address + ADDR_PILOTS_DATA_INIT;
  if (SPI_EEPROM_InitWrite((uint8_t *)&PilotData[PilotId],Address, sizeof(PILOT_DATA), SaveCallBack) == EEPROM_OK)
    return true;
  else
    return false;
}

/*********************************************************************
 * @brief 
 * @param 
 * @retval None 
 * Overview:        
 * @note  
 ********************************************************************/
bool SaveAllPilotsConfigData(void * SaveCallBack){
  uint32_t Address;
  
  Address = ADDR_PILOTS_DATA_INIT; // Calcula la dirección donde lo va a guardar en eeprom
  if (SPI_EEPROM_InitWrite((uint8_t *)&PilotData[0],Address, sizeof(PILOT_DATA)*MAX_PILOTS, SaveCallBack) == EEPROM_OK)
    return true;
  else
    return false;
  
  
}
