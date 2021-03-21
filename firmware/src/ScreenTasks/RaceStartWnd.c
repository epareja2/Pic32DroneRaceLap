/*! \file *********************************************************************
 *
 * - File:               RaceStart.c
 * - Compiler:           MPLABX X32 V2.30  MPLAB 5.3  Harmony 2.06
 * - Supported devices:  
 *
 * \author               Ernesto Pareja  (epare)
 *
 * REVISION HISTORY:
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Author            Date      Comments on that revision
 *----------------------------------------------------------------------
 * Epareja       18 de mayo de 2020, 09:26 PM  Creation of file 
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
#include "../app.h"
#include <stdint.h>
#include "RaceStartWnd.h"
#include "PilotUnit.h"
#include "gfx/libaria/libaria.h"
#include "gfx/libaria/inc/libaria_utils.h"
#include "Utils.h"
#include "RaceDetection.h"
//#include "gfx/libaria/inc/libaria_string.h"
//#include "gfx/gfx_assets.h"




/*********************************************************************
 /*                      GLOBAL VARIABLES        
 /*********************************************************************/
uint8_t PilotTiming[MAX_PILOTS][MAX_LAPS*10];
bool    OmitPressEnablePilotBtn;


/*********************************************************************
 /*                      LOCAL CONSTANT DEFINITIONS
 /*********************************************************************/

/*********************************************************************
 /*                      PRIVATE FUNCTION DECLARATIONS        
 /*********************************************************************/
void StartRaceBtn_OnClick(laButtonWidget* btn);
void CloseFinalStatsBtn_OnClick(laButtonWidget* btn);
void PressEnablePilots_OnClick(laButtonWidget* btn);
void RaceStartWnd_ShowRaceStats(void);
void RaceLapNumberStringSet(void);

/*********************************************************************
 /*                      CODE IMPLEMENTATION        
 /*********************************************************************/


/*********************************************************************
 * Function:        void RaceStartWnd_Initialize(void)
 * @brief 
 * @param 
 * @retval None 
 * @exam      
 * @note            
 ********************************************************************/
void RaceStartWnd_Initialize(void) {
  laScreen* screen;

  screen = (laScreen*)laContext_GetActive()->screenList.values[RaceWnd_ID];
  laScreen_SetShowEventCallback(screen, &RaceStartWnd_OnShow); // Set CallBack function
  laScreen_SetHideEventCallback(screen,&RaceStartWnd_OnHide);
  
  SetLapDetectionCB(&RaceStartWnd_LapCompleted);

}



/*********************************************************************
 * Function:        void RaceStartWnd_OnShow(void)
 * @brief 
 * @param 
 * @retval None 
 * @exam      
 * @note            
 ********************************************************************/
void RaceStartWnd_OnShow(laScreen* screen) {
  uint8_t i;
  laString TempStr;
  bool Enabled;
  
  laButtonWidget_SetReleasedEventCallback(StartStopRaceBtn, &StartRaceBtn_OnClick);
  laButtonWidget_SetReleasedEventCallback(CloseFinalStatsBtn, &CloseFinalStatsBtn_OnClick);
  
  laButtonWidget_SetReleasedEventCallback(Pilot0EnableBtn, &PressEnablePilots_OnClick);
  laButtonWidget_SetPressedEventCallback(Pilot0EnableBtn, &PressEnablePilots_OnClick);
  laButtonWidget_SetReleasedEventCallback(Pilot1EnableBtn, &PressEnablePilots_OnClick);
  laButtonWidget_SetPressedEventCallback(Pilot1EnableBtn, &PressEnablePilots_OnClick);
  laButtonWidget_SetReleasedEventCallback(Pilot2EnableBtn, &PressEnablePilots_OnClick);
  laButtonWidget_SetPressedEventCallback(Pilot2EnableBtn, &PressEnablePilots_OnClick);
  laButtonWidget_SetReleasedEventCallback(Pilot3EnableBtn, &PressEnablePilots_OnClick);
  laButtonWidget_SetPressedEventCallback(Pilot3EnableBtn, &PressEnablePilots_OnClick);
  
  InitPilotRaceData();
  RaceLapNumberStringSet();
  for (i = 0; i < MAX_PILOTS; i++) {
    PilotTiming[i][0] = '\0';
  }
  TempStr = laString_CreateFromCharBuffer("",&Calibri_14);
  laLabelWidget_SetText(Pilot0TimesLbl,TempStr);
  laLabelWidget_SetText(Pilot1TimesLbl,TempStr);
  laLabelWidget_SetText(Pilot2TimesLbl,TempStr);
  laLabelWidget_SetText(Pilot3TimesLbl,TempStr);
  
  TempStr = laString_CreateFromCharBuffer("0:00.00",&Calibri_14);
  laLabelWidget_SetText(TotalPilot0Lbl,TempStr);
  laLabelWidget_SetText(TotalPilot1Lbl,TempStr);
  laLabelWidget_SetText(TotalPilot2Lbl,TempStr);
  laLabelWidget_SetText(TotalPilot3Lbl,TempStr);

  TempStr = laString_CreateFromCharBuffer("00",&Calibri_Bold_20);
  laLabelWidget_SetText(MSegLbl,TempStr);
  
  laString_Destroy(&TempStr);
  

}

/*********************************************************************
 * Function:        void RaceStartWnd_OnHide(void)
 * @brief 
 * @param 
 * @retval None 
 * @exam      
 * @note            
 ********************************************************************/
void RaceStartWnd_OnHide(laScreen* screen) {
  RaceData.state = RACE_IDLE;
  RaceData.RaceTime_ms = 0;
}

void UpdateRaceTimeLbl(void){
  laString TempStrTime;
  uint8_t TimeCharStr[10];
  T_TIME Time;

  MsToTime(RaceData.RaceTime_ms, &Time);

  sprintf(TimeCharStr,"%.2d:%.2d.",Time.min,Time.seg);
  TempStrTime = laString_CreateFromCharBuffer(TimeCharStr, &Calibri_Bold_20);
  laLabelWidget_SetText(TimeCountLbl,TempStrTime);
  laString_Destroy(&TempStrTime);

  laWidget_SetVisible((laWidget *)MSegLbl, true); // Set visible the label MSeg
  sprintf(TimeCharStr,"%.2d",(uint8_t)(Time.ms/10));
  TempStrTime = laString_CreateFromCharBuffer(TimeCharStr, &Calibri_Bold_20);
  laLabelWidget_SetText(MSegLbl,TempStrTime);
  laString_Destroy(&TempStrTime);

  sprintf(TimeCharStr,"%d",rx5808_data.RSSI[0]);
  TempStrTime = laString_CreateFromCharBuffer(TimeCharStr, &Calibri_Bold_20);
  laLabelWidget_SetText(TotalPilot0Lbl,TempStrTime);
  laString_Destroy(&TempStrTime);

  sprintf(TimeCharStr,"%d",rx5808_data.RSSI[1]);
  TempStrTime = laString_CreateFromCharBuffer(TimeCharStr, &Calibri_Bold_20);
  laLabelWidget_SetText(TotalPilot1Lbl,TempStrTime);
  laString_Destroy(&TempStrTime);

  sprintf(TimeCharStr,"%d",rx5808_data.RSSI[2]);
  TempStrTime = laString_CreateFromCharBuffer(TimeCharStr, &Calibri_Bold_20);
  laLabelWidget_SetText(TotalPilot2Lbl,TempStrTime);
  laString_Destroy(&TempStrTime);

  sprintf(TimeCharStr,"%d",rx5808_data.RSSI[3]);
  TempStrTime = laString_CreateFromCharBuffer(TimeCharStr, &Calibri_Bold_20);
  laLabelWidget_SetText(TotalPilot3Lbl,TempStrTime);
  laString_Destroy(&TempStrTime);
  
  
}

void RaceStartWnd_Tasks(void){
  static uint32_t LastTime = 0;
  uint8_t i;
  
  switch(RaceData.state){
    case RACE_STARTED:
    case RACE_WAIT_TO_CROSSLINE: {
      if ((GET_TICKS() - LastTime ) > (10 * _1mSEG_TICKS)) { // Actualiza el dato cada 10ms
        LastTime = GET_TICKS();
        UpdateRaceTimeLbl();

      }
      break;
    }
    
    case RACE_FINISHED: {
      if (laWidget_GetVisible((laWidget *)FinalStatsPanel) == LA_FALSE){
        UpdateRaceTimeLbl();
        RaceStartWnd_ShowRaceStats();
        
      }
      break;
    }
    
    case RACE_TIME_OUT: {
      
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
void StartRaceBtn_OnClick(laButtonWidget* btn){
  uint8_t i;
  laString TempStr;
  
  if (RaceData.state != RACE_STARTED  && RaceData.state != RACE_WAIT_TO_CROSSLINE) {
    for (i = 0; i < MAX_PILOTS; i++) {
      PilotTiming[i][0] = '\0';
    }
    TempStr = laString_CreateFromCharBuffer("",&Calibri_14);
    laLabelWidget_SetText(Pilot0TimesLbl,TempStr);
    laLabelWidget_SetText(Pilot1TimesLbl,TempStr);
    laLabelWidget_SetText(Pilot2TimesLbl,TempStr);
    laLabelWidget_SetText(Pilot3TimesLbl,TempStr);
    laWidget_SetVisible((laWidget *)MSegLbl, false); // Oculta temporalmente el texto de MSeg
  //  TempStr = laString_CreateFromCharBuffer("00",&Calibri_Bold_20);
  //  laLabelWidget_SetText(MSegLbl,TempStr);
    laButtonWidget_SetText(StartStopRaceBtn, laString_CreateFromID(string_EndRaceBtnStr));
    laString_Destroy(&TempStr);
    RaceLapNumberStringSet();
    StartRace();
  } else {
    RaceData.state = RACE_STOPPED;
    laButtonWidget_SetText(StartStopRaceBtn, laString_CreateFromID(string_StartRaceBtnStr));
    
  }
}

/*********************************************************************
 * @brief 
 * @param 
 * @retval None 
 * @exam      
 * @note            
 *********************************************************************/
void PressEnablePilots_OnClick(laButtonWidget* btn){
  laBool Estado;
  
  Estado = laButtonWidget_GetPressed(btn);
  if (OmitPressEnablePilotBtn == false){
    if (btn == Pilot0EnableBtn) {
      PilotData[0].Enabled = Estado & LA_TRUE;
    } else if (btn == Pilot1EnableBtn){
      PilotData[1].Enabled = Estado & LA_TRUE;
    } else if (btn == Pilot2EnableBtn){
      PilotData[2].Enabled = Estado & LA_TRUE;
    } else if (btn == Pilot3EnableBtn){
      PilotData[3].Enabled = Estado & LA_TRUE;
    }
  }
}


/*********************************************************************
 * @brief Muestra el panel de habilitación de pilotos
 * @param 
 * @retval None 
 * @exam      
 * @note            
 *********************************************************************/
void ShowEnablePanelBtn_OnClik(void){
  uint8_t Data[3];
  laString Str;
  
  laWidget_SetVisible((laWidget *)EnablePilotsPanel,LA_TRUE); 
  OmitPressEnablePilotBtn = true; // Para omitir los eventos de presionar los botones
  laButtonWidget_SetPressed(Pilot0EnableBtn,PilotData[0].Enabled); 
  laButtonWidget_SetPressed(Pilot1EnableBtn,PilotData[1].Enabled);
  laButtonWidget_SetPressed(Pilot2EnableBtn,PilotData[2].Enabled); 
  laButtonWidget_SetPressed(Pilot3EnableBtn,PilotData[3].Enabled); 
  OmitPressEnablePilotBtn = false;
  sprintf(Data,"%c%d", BandCode[PilotData[0].Band], PilotData[0].Channel+1);
  Str = laString_CreateFromCharBuffer(Data,&Calibri_Bold_20);
  laLabelWidget_SetText(Channel0Lbl,Str);
  laString_Destroy(&Str);  

  sprintf(Data,"%c%d", BandCode[PilotData[1].Band], PilotData[1].Channel+1);
  Str = laString_CreateFromCharBuffer(Data,&Calibri_Bold_20);
  laLabelWidget_SetText(Channel1Lbl,Str);
  laString_Destroy(&Str);  

  sprintf(Data,"%c%d", BandCode[PilotData[2].Band], PilotData[2].Channel+1);
  Str = laString_CreateFromCharBuffer(Data,&Calibri_Bold_20);
  laLabelWidget_SetText(Channel2Lbl,Str);
  laString_Destroy(&Str);  

  sprintf(Data,"%c%d", BandCode[PilotData[3].Band], PilotData[3].Channel+1);
  Str = laString_CreateFromCharBuffer(Data,&Calibri_Bold_20);
  laLabelWidget_SetText(Channel3Lbl,Str);
  laString_Destroy(&Str);  
  
}

/*********************************************************************
 * @brief Call Back Function that is called when a new Lap is registered
 *        for an specific pilot
 * @param 
 * @retval None 
 * @exam      
 * @note            
 *********************************************************************/
void RaceStartWnd_LapCompleted(uint8_t PilotId, uint8_t Lap){
  laLabelWidget * LapTextPointer;
  uint32_t TimeToLog;
  laString TempStr;
  uint8_t TimeStr[12];
  T_TIME Time;
  
  switch (PilotId) {
    case 0:{
      LapTextPointer = Pilot0TimesLbl;
      break;
    } 
    case 1:{
      LapTextPointer = Pilot1TimesLbl;
      break;
    } 
    case 2:{
      LapTextPointer = Pilot2TimesLbl;
      break;
    } 
    case 3:{
      LapTextPointer = Pilot3TimesLbl;
      break;
    } 
  }
  
  if(RaceData.raceType == RACE_EACH_LAP_TIME) {
    if (RaceData.LapCount[PilotId] == 1) { // la primera vuelta es 1 y no 0 porque la rutina incrementa el lapcount antes de venir aquí
      TimeToLog = RaceData.LapTime[PilotId][Lap];
    } else {
      TimeToLog = RaceData.LapTime[PilotId][Lap] - RaceData.LapTime[PilotId][Lap-1];
    }
  } else {
    TimeToLog = RaceData.LapTime[PilotId][Lap];
  }
  MsToTime(TimeToLog,&Time); // LapCount - 1 because the lap inndex was incremented before calling this 
  sprintf(TimeStr,"%d:%.2d.%.2d\n\n",Time.min,Time.seg,(uint8_t)(Time.ms/10));
  strcat(&PilotTiming[PilotId][0],&TimeStr);
  TempStr = laString_CreateFromCharBuffer(&PilotTiming[PilotId][0],&Calibri_14);
  laLabelWidget_SetText(LapTextPointer,TempStr);
  laString_Destroy(&TempStr);
  
}

void RaceLapNumberStringSet(void){
  uint8_t i=0;
  uint8_t LapStr[30];
  uint8_t LapIndex=0;
  uint8_t * pStr;
  laString TempStr;
  
  pStr = &LapStr[0];

  do {
    *pStr = (LapIndex+1) +0x30; // Convierte al chr
    pStr++;
    *pStr = '\n';
    pStr++;
    *pStr = '\n';
    pStr++;
    LapIndex++;
  }while (LapIndex < RaceData.LapsToRace);
  *pStr = '\0'; // Null terminating char
  TempStr = laString_CreateFromCharBuffer(LapStr,&Calibri_14);
  laLabelWidget_SetText(LapsNumbersLbl,TempStr);
  laString_Destroy(&TempStr);
}

/*********************************************************************
 * Function:        void CloseFinalStatsBtn_OnClick(laButtonWidget* btn);
 * @brief 
 * @param 
 * @retval None 
 * @exam      
 * @note            
 ********************************************************************/
void CloseFinalStatsBtn_OnClick(laButtonWidget* btn){
  laWidget_SetVisible((laWidget *)FinalStatsPanel, false);
  RaceData.state = RACE_IDLE;
}


/*********************************************************************
 * @brief 
 * @param 
 * @retval None 
 * @exam      
 * @note            
 *********************************************************************/
void RaceStartWnd_ShowRaceStats(void){
  uint8_t i;
  uint8_t Data[15];
  laString TempStr, TempStr2;
  T_TIME  Time;
  uint8_t FinishOrder[MAX_PILOTS];
  uint32_t TimeToLog;
  laLabelWidget * TotalLbls[MAX_PILOTS];
  laLabelWidget * PilotTimeLbl[MAX_PILOTS];
  laLabelWidget * PilotNumberLbl[MAX_PILOTS];
  
  TotalLbls[0] = TotalPilot0Lbl;
  TotalLbls[1] = TotalPilot1Lbl;
  TotalLbls[2] = TotalPilot2Lbl;
  TotalLbls[3] = TotalPilot3Lbl;
  
  PilotTimeLbl[0] = _1TimeLbl;
  PilotTimeLbl[1] = _2TimeLbl;
  PilotTimeLbl[2] = _3TimeLbl;
  PilotTimeLbl[3] = _4TimeLbl;
    
  PilotNumberLbl[0] = _1PlaceLbl;
  PilotNumberLbl[1] = _2PlaceLbl;
  PilotNumberLbl[2] = _3PlaceLbl;
  PilotNumberLbl[3] = _4PlaceLbl;
    
  laWidget_SetVisible((laWidget *)FinalStatsPanel, true);
  Race_GetPodiumOrder(FinishOrder);
  laButtonWidget_SetText(StartStopRaceBtn, laString_CreateFromID(string_StartRaceBtnStr));
  
  for (i = 0; i < MAX_PILOTS; i++) {
    if ((PilotData[FinishOrder[i]].Enabled) && 
        (RaceData.LapCount[FinishOrder[i]] == RaceData.LapsToRace)) {
      TimeToLog = RaceData.LapTime[FinishOrder[i]][RaceData.LapCount[FinishOrder[i]]-1];
      MsToTime(TimeToLog, &Time);
      sprintf(Data,"%d:%.2d.%.2d",Time.min,Time.seg,(uint8_t)(Time.ms/10));
    } else {
      sprintf(Data,"N/A",Time.min,Time.seg,(uint8_t)(Time.ms/10));
    }
    TempStr = laString_CreateFromCharBuffer(Data,&Calibri_Bold_20);
    laLabelWidget_SetText(PilotTimeLbl[i],TempStr);
    TempStr2 = laString_CreateFromCharBuffer(Data,&Calibri_14);
    laLabelWidget_SetText(TotalLbls[FinishOrder[i]],TempStr2);


    sprintf(Data,"Pilot %d",FinishOrder[i]+1);
    TempStr = laString_CreateFromCharBuffer(Data,&Calibri_Bold_20);
    laLabelWidget_SetText(PilotNumberLbl[i],TempStr);
    
  }
  laString_Destroy(&TempStr);
  laString_Destroy(&TempStr2);
}

