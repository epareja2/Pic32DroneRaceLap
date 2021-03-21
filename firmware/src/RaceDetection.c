/*! \file *********************************************************************
 *
 * - File:               RaceDetection.c
 * - Compiler:           MPLABX X32 V2.30  MPLAB 5.3  Harmony 2.06
 * - Supported devices:  
 *
 * \author               Ernesto Pareja  (epare)
 *
 * REVISION HISTORY:
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Author            Date      Comments on that revision
 *----------------------------------------------------------------------
 * Epareja       12 de mayo de 2020, 11:53 PM  Creation of file 
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
#include "RX5808.h"
#include "PilotUnit.h"
#include "RaceDetection.h"
#include "app.h"
#include "Beep.h"
#include "EEProm_Address.h"
#include "driver/eeprom/SPI_EEprom_Drv.h"






/*********************************************************************
 /*                      GLOBAL VARIABLES        
 /*********************************************************************/

/*********************************************************************
 /*                      LOCAL CONSTANT DEFINITIONS
 /*********************************************************************/

/*********************************************************************
 /*                      PRIVATE FUNCTION DECLARATIONS        
 /*********************************************************************/
void SortArray(uint32_t arr[], uint8_t order[], uint8_t n);
void Race_ShowPodium(void);


/*********************************************************************
 /*                      CODE IMPLEMENTATION        
 /*********************************************************************/

/*********************************************************************
 * Function:        void RaceTasks(void)
 * @brief 
 * @param 
 * @retval None 
 * @exam      
 * @note            
 ********************************************************************/
void RaceTasks(void) {
  laString TempStr;
  uint8_t i; 
  bool AllPilotsFinish;
  uint8_t BeepNumStr[2];
  static uint32_t LastTime = 0;
  static uint8_t StartBeepCounter; // se encarga de contar regresivamente desde RaceData.StartBeep hasta 0

  
  switch (RaceData.state) {
    case RACE_IDLE :{
      
      break;
    }
    case RACE_STARTED:   
    case RACE_WAIT_TO_CROSSLINE:{
      if ((GET_TICKS() - LastTime ) > (10 * _1mSEG_TICKS)) { // Actualiza el dato cada 10ms
        LastTime = GET_TICKS();
      
        if (RaceData.RaceTime_ms < ( MAX_RACE_TIMEOUT) ) { // if the race hasn't timed out check the pilot laps
          for (i = 0; i < MAX_PILOTS; i++) {
            if (RaceData.PilotState[i] != PILOT_FINISHED) {
              LapDetection(i);
            }
          }
          if (RaceData.FinishTime_ms != 0) { // Es diferente de cero cuando el primer piloto termine la carrera
            if ((RaceData.RaceTime_ms - RaceData.FinishTime_ms) > (MAX_FINISH_TIME_OUT)){
              Nop();
              RaceData.state = RACE_FINISHED;
            }
          }
          AllPilotsFinish = true;
          for (i = 0; i < MAX_PILOTS; i++) {
            if ( (PilotData[i].Enabled) && (RaceData.PilotState[i]!=PILOT_FINISHED) ) {
              Nop();
              AllPilotsFinish = false;
              break; // Ends the FOR loop
            }
          }
          if (AllPilotsFinish){
            Nop();
            RaceData.state = RACE_FINISHED;
          }

        } else {
          RaceData.state = RACE_TIME_OUT;
        }
      }
      break;
    }
    
    case RACE_FINISHED: {
      Nop();
      break;
    }
    case RACE_TIME_OUT:{
      
      break;
    }
    // Estado para iniciar la carrera
    case RACE_PREPARE_START: {
      StartBeepCounter = RaceData.StartBeepsCount; // inicializa el contador en el setup configurado
      RaceData.state = RACE_SEMAPHORE;
      RaceData.SemaphoreTime = GET_TICKS() + (SEMAPHORE_TIME * _1mSEG_TICKS);
      break;
    }
    
    case RACE_SEMAPHORE:{
      if (GET_TICKS() > RaceData.SemaphoreTime){
        StartBeepCounter--;
        if (StartBeepCounter >= 1) { 
          sprintf(BeepNumStr,"%d",StartBeepCounter);
          TempStr = laString_CreateFromCharBuffer(BeepNumStr,&Calibri_Bold_20);
          laLabelWidget_SetText(TimeCountLbl, TempStr);
          laString_Destroy(&TempStr);
          RaceData.SemaphoreTime = GET_TICKS() + (SEMAPHORE_TIME * _1mSEG_TICKS);
          RaceData.state  = RACE_SEMAPHORE;
          Beep(SEMAPHORE1_TONE, SEMAPHORE_TIME - 200);
        } else {
          TempStr = laString_CreateFromCharBuffer("0",&Calibri_Bold_20);
          laLabelWidget_SetText(TimeCountLbl, TempStr);
          laString_Destroy(&TempStr);
  //        RaceData.SemaphoreTime = GET_TICKS() + (SEMAPHORE_TIME * _1mSEG_TICKS);
          RaceData.state  = RACE_STARTED;
          RaceData.RaceTime_ms = 0;
          Beep(SEMAPHORE2_TONE, (uint16_t )(SEMAPHORE_TIME*1.5) - 200);
          
        }
        
      }
      break;
    }

  }
}



/*********************************************************************
 * @brief 
 * @param 
 * @retval None 
 * @exam      
 * @note            
 *********************************************************************/
void LapDetection(uint8_t Pilot){
  uint32_t TimeToCompare;
  
  if (((RaceData.state == RACE_STARTED) || (RaceData.state == RACE_WAIT_TO_CROSSLINE) ) && (PilotData[Pilot].Enabled == true) ){
    
    if (rx5808_data.RSSI[Pilot] > PilotData[Pilot].ThrHigh) {
      if (RaceData.LapCount[Pilot] == 0) {
        TimeToCompare = 0;
      } else {
        TimeToCompare = RaceData.LapTime[Pilot][RaceData.LapCount[Pilot]-1];
      }
      
      if ( (RaceData.RaceTime_ms - TimeToCompare ) > (RaceData.MinRaceLapTime*1000) )  { // Tiempo de vuelta mínimo alcanzado?
        if (RaceData.DebounceRSSI[Pilot] == 0) { // Entra aquí solo la primera vez
          RaceData.DebounceRSSI[Pilot] = RaceData.RaceTime_ms + DEBOUNCE_RSSI_TIME;
        } 
        if (RaceData.RaceTime_ms > RaceData.DebounceRSSI[Pilot]) { // Tiempo mínimo para superar el thresshold
          RaceData.DebounceRSSI[Pilot] = 0;
          RaceData.PilotState[Pilot] = PILOT_CROSSING;
          if (RaceData.CountFirstPass == true) {
              RaceData.CrossStartLine[Pilot] = true;  //Set the first crossing line flag
              RaceData.DebounceRSSI[Pilot]=0; // RACE_STARTED
              RaceData.LapTime[Pilot][RaceData.LapCount[Pilot]] = RaceData.RaceTime_ms;
              RaceData.LapCount[Pilot]++;
              if (RaceData.LapDetectedCB != NULL) {
                RaceData.LapDetectedCB(Pilot, RaceData.LapCount[Pilot] - 1);
              }
              if (RaceData.LapCount[Pilot] >= RaceData.LapsToRace) { // Es la última vuelta?
                RaceData.PilotState[Pilot] = PILOT_FINISHED;
                PlayTune(&FinishRaceTones[0],&LapDelays[0], 3, 1000, false );
                if (RaceData.FinishTime_ms == 0)
                  RaceData.FinishTime_ms = RaceData.RaceTime_ms; // Asigna el tiempo de terminación del primer piloto
              } else { // Si nno es la última vuelta entonces toca la melodía de cada piloto
                PlayTune(&LapTones[Pilot][0],&LapDelays[0], 3, 1000, false );
              }
            
          } else { // No cuenta la primera vuelta
            if (RaceData.CrossStartLine[Pilot] == false) {
              RaceData.CrossStartLine[Pilot] = true;  //Set the first crossing line flag
            } else { // We have to register a new lap
              RaceData.DebounceRSSI[Pilot]=0; // RACE_STARTED
              RaceData.LapTime[Pilot][RaceData.LapCount[Pilot]] = RaceData.RaceTime_ms;
              RaceData.LapCount[Pilot]++;
              PlayTune(&LapTones[Pilot][0],&LapDelays[0], 3, 1000, false );
              if (RaceData.LapDetectedCB != NULL) {
                RaceData.LapDetectedCB(Pilot, RaceData.LapCount[Pilot] - 1);
              }
            }
          }
        } 
      } else {
        // No ha cumplido el tiempo mínimo entre vueltas
         RaceData.PilotState[Pilot] = PILOT_APROACHING; 
      }
    } else { // RSSI Leves is below the maxRSSI
      RaceData.DebounceRSSI[Pilot] = 0;
      if (RaceData.PilotState[Pilot]== PILOT_CROSSING) {
        RaceData.PilotState[Pilot] = PILOT_LEAVING; 
      } else {
        if (rx5808_data.RSSI[Pilot] <= ((PilotData[Pilot].minRssi) + MIN_RSSI_OFFSET)){
          RaceData.PilotState[Pilot] = PILOT_ABANDON;
        }
      }
    }
  }
}

/*********************************************************************
 * @brief 
 * @param 
 * @retval None 
 * @exam      
 * @note            
 *********************************************************************/
void InitPilotRaceData(void){
  uint8_t i;
  for (i = 0; i < MAX_PILOTS; i++) {
    RaceData.LapTime[i][0] = 0;
    RaceData.LapCount[i] = 0;
    RaceData.CrossStartLine[i] = false;
    RaceData.DebounceRSSI[i] = 0;
    RaceData.PilotState[i]=PILOT_INIT;
  }
  
}


/*********************************************************************
 * @brief 
 * @param 
 * @retval None 
 * @exam      
 * @note            
 *********************************************************************/
void StartRace(void) {
  RaceData.state  = RACE_PREPARE_START;
  RaceData.FinishTime_ms = 0;
  InitPilotRaceData();
  laWidget_SetVisible ((laWidget *)FinalStatsPanel, false);
}

/*********************************************************************
 * @brief Asigna la función de Call Back cuando detecte una vuelta para
 *        poder informar al usuario o a capas superiores del software
 * @param {pointer} CB : Es un puntero a una función definida como está en 
 *        el ejemplo con dos párámetros de entrada.
 *   
 * @retval None 
 * @exam      
 *    void RaceStartWnd_LapCompleted(uint8_t PilotId, uint8_t Lap);
 *    SetLapDetectionCB(&RaceStartWnd_LapCompleted);
 * @note            
 *********************************************************************/
void SetLapDetectionCB(void * CB){
  RaceData.LapDetectedCB = CB;
}


/*********************************************************************
 * @brief 
 * @param 
 * @retval None 
 * @exam      
 * @note            
 *********************************************************************/
bool SaveRaceData_EEPROM(void * SaveCallBack){
  volatile uint32_t Address;
  volatile uint8_t *pData;
  volatile uint8_t size;
  
  pData = &RaceData.raceType;
  Address = ADDR_RACE_DATA_INIT;
//  size = ADDR_RACE_DATA_END - ADDR_RACE_DATA_INIT;
  if (SPI_EEPROM_InitWrite((uint8_t *)pData, Address, 5, SaveCallBack) == EEPROM_OK)
    return true;
  else
    return false;
}

bool LoadRaceData_EEPROM(void * LoadCallBack){
  volatile uint32_t Address;
  Address = ADDR_RACE_DATA_INIT;
  if (LoadCallBack != NULL) {
    SPI_EEPROM_InitRead((uint8_t *)&RaceData.raceType,ADDR_RACE_DATA_INIT,
                     5 ,LoadCallBack);
  } else {
    SPI_EEPROM_InitRead((uint8_t *)&RaceData.raceType,ADDR_RACE_DATA_INIT,
                     5 ,&OnLoadRaceData);
  }
  if (RaceData.StartBeepsCount < 1  || RaceData.StartBeepsCount > 10) {
    RaceData.StartBeepsCount = 3;
  }
  if (RaceData.LapsToRace > MAX_LAPS) {
    RaceData.LapsToRace = MAX_LAPS;
  }
  
}


/*********************************************************************
 * @brief 
 * @param 
 * @retval None 
 * @exam      
 * @note            
 *********************************************************************/
void OnLoadRaceData(uint8_t nBytes){
  
}


/*********************************************************************
 * @brief Devuelve un puntero a un array con el orden de los pilots según
 *        el tiempo que terminaron la carrera
 * @param Puntero a uint8_t que deberá tener un número máximo de (MAX_PILOTS) elementos
 * @retval 
 * @exam    
 * uint8_t Podium[MAX_PILOTS];
 * Race_GetPodiumOrder(&Podium);  
 * @note            
 *********************************************************************/
void Race_GetPodiumOrder(uint8_t * Podium){
  uint32_t TempPodio[MAX_PILOTS];
  uint8_t  TempOrder[MAX_PILOTS];
  uint8_t i,j;
  uint8_t Lap;
  
  for (i = 0; i < MAX_PILOTS; i++) {
    if (PilotData[i].Enabled   ) {
      if ((RaceData.LapCount[i]) == RaceData.LapsToRace) {
        if (RaceData.LapCount[i] == 0) {
          Lap = 0;
        } else {
          Lap = RaceData.LapCount[i] - 1;
        }
        TempPodio[i] = RaceData.LapTime[i][Lap];
      } else {
        TempPodio[i] = 0xFFFFFFFA; // Is when a drone started a rece but didn't finish all the laps
      }
    } else {
      TempPodio[i] = 0xFFFFFFFF; // MAX 32 bit Value
    }
      TempOrder[i] = i;
  }

  SortArray(TempPodio, TempOrder, MAX_PILOTS);
  for (i = 0; i < MAX_PILOTS; i++) {
    Podium[i] = TempOrder[i];
  }  
}

/*********************************************************************
 * @brief 
 * @param 
 * @retval None 
 * @exam      
 * @note            
 *********************************************************************/
void SortArray(uint32_t arr[], uint8_t order[], uint8_t n) { 
  uint8_t i;
  uint32_t TempValue;
  uint8_t TempIndex;
  
  // Base case 
  if (n == 1) 
      return; 

  // One pass of bubble sort. After 
  // this pass, the largest element 
  // is moved (or bubbled) to end. 
  for (i=0; i<n-1; i++) 
    if (arr[i] > arr[i+1]) {
      TempValue = arr[i];
      arr[i] =  arr[i+1];
      arr[i+1] = TempValue;
      TempIndex = order[i];
      order[i] = order[i+1];
      order[i+1] = TempIndex;
    }

    // Largest element is fixed, 
    // recur for remaining array 
    SortArray(arr, order, n-1); 
} 
