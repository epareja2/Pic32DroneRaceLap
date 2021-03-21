/* 
 * File:   PilotUnit.h
 * Author: epare
 *
 * Created on 7 de abril de 2020, 08:48 PM
 */

#ifndef PILOTUNIT_H
#define	PILOTUNIT_H

#ifdef	__cplusplus
extern "C" {
#endif


/*************************************************************************
 *                   INCLUDES
 *************************************************************************/
#include <xc.h>
#include <stdint.h>
#include "RX5808.h"


/*************************************************************************
 *                   CONSTANT AND TYPE DEFINITIONS
 *************************************************************************/

typedef struct{
  uint8_t   id;
  uint8_t   Name[20];
  uint8_t   NickName[10];
  bool      Enabled;
  uint16_t  maxRssi;
  uint16_t  minRssi;
  uint16_t  ThrHigh; // Threshold High Level
  uint16_t  ThrLow; // Threshold low Level
  uint8_t   Band;  // Index of the band array from 0 to MAX_BANDS
  uint8_t   Channel; // From 0 to 7 (Real channels are from 1 to 8)
  uint16_t  Freq;
  
} PILOT_DATA;


#define THRESHOLD_HIGH  25.0    // % from maxRSSI that will detect a crossing lines
#define THRESHOLD_LOW   30.0    // % from minRSSI that will detect a going away from crossing line

#define MAX_PILOTS  4

/*************************************************************************
 *                   GLOBAL VARIABLES DEFINITIONS
 *************************************************************************/
PILOT_DATA PilotData[MAX_PILOTS]; //


/*************************************************************************
 *                   FUNNCTION DECLARATIONS
 *************************************************************************/
void PilotDataInit(void);
void ConfigPilotModuleWndInitialize(void);
void LoadPilotConfigData_eeprom(uint8_t PilotId);
void LoadAllPilotConfigData_eeprom(void);
void PilotUnit_OnLoadConfigData(uint16_t nBytes);
bool SaveFreqPilotConfigData(uint8_t PilotId, void * SaveCallBack);
bool SavePilotConfigData(uint8_t PilotId, void * SaveCallBack);
bool SaveAllPilotsConfigData(void * SaveCallBack);
bool SaveEnablePilotConfigData(uint8_t PilotId, void * SaveCallBack);
bool IsPilotDataLoaded(void);




#ifdef	__cplusplus
}
#endif

#endif	/* PILOTUNIT_H */

