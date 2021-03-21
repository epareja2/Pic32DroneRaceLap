/* 
 * File:   RaceDetection.h
 * Author: epare
 *
 * Created on 12 de mayo de 2020, 11:53 PM
 */

#ifndef RACEDETECTION_H
#define	RACEDETECTION_H

#ifdef	__cplusplus
extern "C" {
#endif
  
#include "PilotUnit.h"
#include "RX5808.h"
#include "Beep.h"

  /********************************************************************
  /*      CONFIGURATION MODULE CONSTANTS
  /*********************************************************************/
#define MAX_RACE_TIMEOUT    10*60*1000     //Expresado en segundos (10 minutos) Tiempo total de carrera para Timeout
#define MAX_FINISH_TIME_OUT 2*60*1000   // Tiempo para terminar después que el primer corredor termine
#define MIN_RACE_LAP_TIME   5000     // Mínimo tiempo para registrar una vuelta - TODO: Confiurarlo por usuario
#define MAX_LAPS            8
#define DEBOUNCE_RSSI_TIME  10        //ms to wait for the RSSI to be over maxRSSI
#define MAX_SAMPLES_RSSI    16
#define MIN_RSSI_OFFSET     10        // To detect the off VTX rssi + this value to mark a pilot as leave.
  
#define SEMAPHORE_TIME    1000      //ms to BEEP when starting a race

#define SEMAPHORE1_TONE   C5
#define SEMAPHORE2_TONE   D5
#define SEMAPHORE3_TONE   E5
  
  
static const uint16_t  LapTones[MAX_PILOTS][3] = {{A4, F5, B5} , {A5, E5, C5} , {C5, A5, E5}, {E5, A4, E5}};
static const int16_t  LapDelays[3] = {200, 200, 200 };
static const uint16_t  FinishRaceTones[3] = {E4, D4, C4};



  /*********************************************************************
  /*      TYPE DEFINITIONS             
  /*********************************************************************/

  typedef enum {
    
    RACE_IDLE,
    RACE_STARTED,
    RACE_WAIT_TO_CROSSLINE,
    RACE_TIME_OUT,
    RACE_PREPARE_START,
    RACE_SEMAPHORE,
    RACE_STOPPED,
    RACE_FINISHED,
  } T_RACE_STATES;
  
  typedef enum{
    RACE_EACH_LAP_TIME = 0,
    RACE_CUMULATIVE_TIME,
  } T_RACE_TYPE;
  
  typedef enum{
    PILOT_INIT,
    PILOT_LEAVING,
    PILOT_APROACHING,
    PILOT_CROSSING,
    PILOT_AWAY,
    PILOT_ABANDON,
    PILOT_FINISHED,
  }T_PILOT_RACE_STATE;
  
 
  typedef struct {
    uint8_t     idRace;
    uint8_t     numPilots;
    T_RACE_TYPE raceType;
    uint8_t     LapsToRace; // The laps that are programmed to this race
    uint8_t     MinRaceLapTime; // Tiempo mínimo de vuelta.
    bool        CountFirstPass; //
    uint8_t     StartBeepsCount; // Número de pitidos al inicio de la carrera
    uint32_t    RaceTime_ms;
    uint32_t    FinishTime_ms; // Time when the first pilot finish the LapsToRace
    T_RACE_STATES state;
    uint32_t    LapTime[MAX_PILOTS][MAX_LAPS]; // TODO: Optimizar a 16 bits para medir los 
    uint8_t     LapCount[MAX_PILOTS];
    uint32_t    SemaphoreTime;
    bool        CrossStartLine[MAX_PILOTS]; // Dice si cruzó la meta la primera vez
    uint32_t    DebounceRSSI[MAX_PILOTS]; // To count a debounce when maxRSSI is reached to count a lap
    T_PILOT_RACE_STATE PilotState[MAX_PILOTS];
//    uint16_t    historicRSSI[MAX_PILOTS][MAX_SAMPLES_RSSI];
//    uint8_t     historicRSSI_index[MAX_PILOTS];
    void (*LapDetectedCB) (uint8_t PilotId, uint8_t Lap);
  } T_RACE_DATA;
  
  
  /*********************************************************************
  /*            GLOBAL VARIABLE DECLARATIONS                  
  /*********************************************************************/
T_RACE_DATA   RaceData; // Handle the race data  
  
  /*********************************************************************
  /*            PUBLIC FUNCTION DECLARATIONS                  
  /*********************************************************************/
void LapDetection(uint8_t Pilot);
void InitPilotRaceData(void);
void RaceTasks(void);
void StartRace(void);
void SetLapDetectionCB(void * CB);
bool SaveRaceData_EEPROM(void * SaveCallBack);
bool LoadRaceData_EEPROM(void * LoadCallBack);
void OnLoadRaceData(uint8_t nBytes);
void Race_GetPodiumOrder(uint8_t * Podium);


#ifdef	__cplusplus
}
#endif

#endif	/* RACEDETECTION_H */

