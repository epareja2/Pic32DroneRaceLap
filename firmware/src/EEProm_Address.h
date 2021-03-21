/* 
 * File:   EEProm_Address.h
 * Author: epareja
 *
 * Created on 30 de diciembre de 2017, 12:10 AM
 */

#ifndef EEPROM_ADDRESS_H
  #define	EEPROM_ADDRESS_H

  #ifdef	__cplusplus
extern "C" {
  #endif

  /*************************************************************************
   *                   INCLUDES
   *************************************************************************/
#include "PilotUnit.h"
#include "driver/touch/ADS7843/drv_ads7843.h"
#include "RaceDetection.h"

  /*************************************************************************
   *                   PUBLIC CONSTANTS -- MEMORY ADDRESS MAP
   *************************************************************************/
#define ADDR_TOUCH_MATRIX_CALIB_INIT  20
#define ADDR_TOUCH_MATRIX_CALIB_END   ADDR_TOUCH_MATRIX_CALIB_INIT+ sizeof(DRV_ASD7843_CALIBRATION_MATRIX) // 28
#define ADDR_PILOTS_DATA_INIT         ADDR_TOUCH_MATRIX_CALIB_END + 1
#define ADDR_PILOTS_DATA_END          ADDR_PILOTS_DATA_INIT+MAX_PILOTS*sizeof(PILOT_DATA)
#define ADDR_RACE_DATA_INIT           ADDR_PILOTS_DATA_END + 1
#define ADDR_RACE_DATA_END            ADDR_RACE_DATA_INIT + 4 //only 4 bytes 
  /*************************************************************************
   *                   PUBLIC FUNCTIONS
   *************************************************************************/


  /*************************************************************************
   *                   CONSTANTS AND TYPE DEFINITIOS
   *************************************************************************/




  #ifdef	__cplusplus
}
  #endif

#endif	/* EEPROM_ADDRESS_H */

