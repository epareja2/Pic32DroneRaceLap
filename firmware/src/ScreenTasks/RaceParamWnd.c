/*! \file *********************************************************************
 *
 * - File:               RaceParamWnd.c
 * - Compiler:           MPLABX X32 V2.30  MPLAB 5.3  Harmony 2.06
 * - Supported devices:  
 *
 * \author               Ernesto Pareja  (epare)
 *
 * REVISION HISTORY:
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Author            Date      Comments on that revision
 *----------------------------------------------------------------------
 * Epareja       25 de mayo de 2020, 04:29 PM  Creation of file 
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
#include "app.h"
#include "PilotUnit.h"
#include "RaceDetection.h"
#include "gfx/libaria/libaria.h"


/*********************************************************************
 /*                      LOCAL CONSTANT DEFINITIONS
 /*********************************************************************/
  typedef enum {
    RACE_PARAM_IDLE,
    RACE_PARAM_SAVING,
    RACE_PARAM_SAVED, 
  } T_RACE_PARAM_STATES;

  
/*********************************************************************
 /*                      PRIVATE FUNCTION DECLARATIONS        
 /*********************************************************************/
void RaceParamWnd_OnShow(laScreen * screen);
void RaceParamWnd_OnHide(laScreen * screen);
void CumulativeTimeChk_CheckedEvent(laRadioButtonWidget* cbox);
void EachRaceTimeChk_CheckedEvent(laRadioButtonWidget* cbox);
void OnRaceDataSaved(uint8_t nbytes);
void ChangeLapsBtn_OnClick(laButtonWidget * btn);
void ChangeStartBeepsBtn_OnClick(laButtonWidget * btn);
void ChangeTLapsMinBtn_OnClick(laButtonWidget * btn);
void SkipFirstLapBtn_OnClick(laButtonWidget * btn);
void SaveRaceParamBtn_OnClick(laButtonWidget * btn);
void SaveRaceParamBtn_OnClick(laButtonWidget * btn);
void SetLapLblText(void);
void SetTLapLblText(void);

/*********************************************************************
 /*                      GLOBAL VARIABLES        
 /*********************************************************************/
/* True if any of the controls changed it's data*/
bool DataHasChanged; 
T_RACE_PARAM_STATES RaceParamState;


/*********************************************************************
 /*                      CODE IMPLEMENTATION        
 /*********************************************************************/

/*********************************************************************
 * @brief 
 * @param 
 * @retval None 
 * @exam      
 * @note            
 *********************************************************************/
void RaceParamWnd_Initialize(void){
  laScreen* screen;

  screen = (laScreen*)laContext_GetActive()->screenList.values[RaceConfigWnd_ID];
  laScreen_SetShowEventCallback(screen, &RaceParamWnd_OnShow); // Set CallBack function
  laScreen_SetHideEventCallback(screen,&RaceParamWnd_OnHide);
  RaceParamState = RACE_PARAM_IDLE;
}

/*********************************************************************
 * @brief 
 * @param 
 * @retval None 
 * @exam      
 * @note            
 *********************************************************************/
void RaceParamWnd_OnShow(laScreen * screen){
  
  laButtonWidget_SetReleasedEventCallback(LapDownBtn, &ChangeLapsBtn_OnClick);
  laButtonWidget_SetReleasedEventCallback(LapUpBtn, &ChangeLapsBtn_OnClick);
  laButtonWidget_SetReleasedEventCallback(StartBeepsDownBtn, &ChangeStartBeepsBtn_OnClick);
  laButtonWidget_SetReleasedEventCallback(StartBeepsUpBtn, &ChangeStartBeepsBtn_OnClick);
  laButtonWidget_SetReleasedEventCallback(LapUpBtn, &ChangeLapsBtn_OnClick);
  laButtonWidget_SetReleasedEventCallback(TLapDownBtn, &ChangeTLapsMinBtn_OnClick);
  laButtonWidget_SetReleasedEventCallback(TLapUpBtn, &ChangeTLapsMinBtn_OnClick);
  laButtonWidget_SetReleasedEventCallback(SkipFirstLapBtn, &SkipFirstLapBtn_OnClick);
  laButtonWidget_SetPressedEventCallback(SkipFirstLapBtn, &SkipFirstLapBtn_OnClick);
  laButtonWidget_SetReleasedEventCallback(SaveRaceParamBtn, &SaveRaceParamBtn_OnClick);
  laRadioButtonWidget_SetSelectedEventCallback(EachRaceTimeChk, &EachRaceTimeChk_CheckedEvent);
  laRadioButtonWidget_SetSelectedEventCallback(CumulativeTimeChk, &CumulativeTimeChk_CheckedEvent);
  
  if (RaceData.raceType == RACE_CUMULATIVE_TIME) {
    laRadioButtonWidget_SetSelected(CumulativeTimeChk);
  } else {
    laRadioButtonWidget_SetSelected(EachRaceTimeChk);
  }
  
  SetLapLblText();
  SetTLapLblText();
  SetStartBeepsLblText();

  laButtonWidget_SetPressed(SkipFirstLapBtn, !RaceData.CountFirstPass);

  
}

/*********************************************************************
 * @brief 
 * @param 
 * @retval None 
 * @exam      
 * @note            
 *********************************************************************/
void RaceParamWnd_OnHide(laScreen * screen){
  if (DataHasChanged) {
    /*TODO: check how to block the screen from hiding*/
  }
}

/*********************************************************************
 * @brief 
 * @param 
 * @retval None 
 * @exam      
 * @note            
 *********************************************************************/
void RaceParamWnd_Tasks(void){
  switch (RaceParamState ){
    case RACE_PARAM_IDLE: {
      if (DataHasChanged) {
        if (laWidget_GetVisible((laWidget *)SaveRaceParamBtn)== false)
          laWidget_SetVisible((laWidget *)SaveRaceParamBtn,true); 
      }
      break;
    }
    
    case RACE_PARAM_SAVING: {
      if (SaveRaceData_EEPROM(&OnRaceDataSaved) == true)
        RaceParamState = RACE_PARAM_IDLE;
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
void ChangeStartBeepsBtn_OnClick(laButtonWidget * btn){
  if (btn == StartBeepsUpBtn) {
    RaceData.StartBeepsCount++;
    if (RaceData.StartBeepsCount > 10) {
      RaceData.StartBeepsCount = 10;
    }
  } else {
    RaceData.StartBeepsCount--;
    if (RaceData.StartBeepsCount < 1) {
      RaceData.StartBeepsCount = 1;
    }
  }
  SetStartBeepsLblText();
}


/*********************************************************************
 * @brief 
 * @param 
 * @retval None 
 * @exam      
 * @note            
 *********************************************************************/
void ChangeLapsBtn_OnClick(laButtonWidget * btn){
  uint8_t LapStr[3];
  laString TempStr;
  
  DataHasChanged = true;
  if (btn == LapDownBtn) {
    if (RaceData.LapsToRace > 0)
      RaceData.LapsToRace--;
    else
      RaceData.LapsToRace = 0;
  } else {
    if (RaceData.LapsToRace < MAX_LAPS)
      RaceData.LapsToRace++;
    else
      RaceData.LapsToRace = MAX_LAPS;
  }

  SetLapLblText();
}

/*********************************************************************
 * Function:        void ChangeTLapsMinBtn_OnClick(laButtonWidget * btn)
 * @brief 
 * @param 
 * @retval None 
 * @exam      
 * @note            
 ********************************************************************/
void ChangeTLapsMinBtn_OnClick(laButtonWidget * btn) {
  uint8_t LapStr[4];
  laString TempStr;
  
  DataHasChanged = true;
  if (btn == TLapDownBtn) {
    if (RaceData.MinRaceLapTime > 1)
      RaceData.MinRaceLapTime --;
    else
      RaceData.MinRaceLapTime = 0;
  } else {
    if (RaceData.MinRaceLapTime  < 99)
      RaceData.MinRaceLapTime ++;
    else
      RaceData.MinRaceLapTime  = 99;
  }

  SetTLapLblText();
}



void SetLapLblText(void){
  uint8_t LapStr[3];
  laString TempStr;
  
  sprintf(LapStr,"%d",RaceData.LapsToRace);
  TempStr = laString_CreateFromCharBuffer(LapStr,&Calibri_Bold_20);
  laLabelWidget_SetText(LapNumberConfLbl, TempStr);
  laString_Destroy(&TempStr);
}

void SetTLapLblText(void){
  uint8_t TLapStr[4];
  laString TempStr;
  
  sprintf(TLapStr,"%d",RaceData.MinRaceLapTime);
  TempStr = laString_CreateFromCharBuffer(TLapStr,&Calibri_Bold_20);
  laLabelWidget_SetText(TVueltaLbl, TempStr);
  laString_Destroy(&TempStr);
}
void SetStartBeepsLblText(void){
  uint8_t TStartBeep[3];
  laString TempStr;
  
  sprintf(TStartBeep,"%d",RaceData.StartBeepsCount);
  TempStr = laString_CreateFromCharBuffer(TStartBeep,&Calibri_Bold_20);
  laLabelWidget_SetText(StartBeepsLbl, TempStr);
  laString_Destroy(&TempStr);
}


/*********************************************************************
 * @brief 
 * @param 
 * @retval None 
 * @exam      
 * @note            
 *********************************************************************/
void SkipFirstLapBtn_OnClick(laButtonWidget * btn){
  DataHasChanged = true;
  RaceData.CountFirstPass = !(laButtonWidget_GetPressed(btn)== LA_TRUE);
}

/*********************************************************************
 * @brief 
 * @param 
 * @retval None 
 * @exam      
 * @note            
 *********************************************************************/
void SaveRaceParamBtn_OnClick(laButtonWidget * btn){
  RaceParamState = RACE_PARAM_SAVING;
}

/*********************************************************************
 * @brief 
 * @param 
 * @retval None 
 * @exam      
 * @note            
 *********************************************************************/
void OnRaceDataSaved(uint8_t nbytes){
  DataHasChanged = false;
  laWidget_SetVisible((laWidget *)SaveRaceParamBtn,false); 
  
}

// CumulativeTimeChk - CheckedEvent
void CumulativeTimeChk_CheckedEvent(laRadioButtonWidget* cbox) {
  DataHasChanged = true;
  RaceData.raceType = RACE_CUMULATIVE_TIME;
}

// EachRaceTimeChk - CheckedEvent
void EachRaceTimeChk_CheckedEvent(laRadioButtonWidget* cbox) {
  DataHasChanged = true;
  RaceData.raceType = RACE_EACH_LAP_TIME;
}


