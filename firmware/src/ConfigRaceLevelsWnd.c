/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.c

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */
#include "app.h"
#include "RX5808.h"
#include "ConfigRaceLevelsWnd.h"
#include "gfx/libaria/inc/libaria_utils.h"
#include "system_config/Graphic32MX795/framework/gfx/libaria/libaria_init.h"
#include "PilotUnit.h"
#include "driver/eeprom/SPI_EEprom_Drv.h"


/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
static uint8_t PilotIndex;



/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */
void InitCalibrationRSSILevels_Btn_ReleasedEvent(laButtonWidget* btn);
void SetRSSIBarValues(void);
void SetBarMarkers(uint8_t Sector);
void SetRSSILables(void);
bool SaveConfigToEEPROM(uint8_t PilotId);
void SaveConfig_OnEnd(uint16_t nBytes);
void PilotEnable_OnClick(laButtonWidget* btn);
void OnSaveEnable(uint16_t nBytes);


/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */



/*********************************************************************
 * @brief 
 * @param 
 * @retval None 
 * Overview:        
 * @note            
 *********************************************************************/
void ConfigRaceLevelsWndInitialize(void){
  laScreen* screen;

  screen = (laScreen*)laContext_GetActive()->screenList.values[ConfigRaceLevelsWnd_ID];
  laScreen_SetShowEventCallback(screen, &ConfigRaceLevelWnd_OnShow); // Set CallBack function
  laScreen_SetHideEventCallback(screen,&ConfigRaceLevelWnd_OnHide);
  ConfigRaceLevelData.state = INITIALIZED;
  ConfigRaceLevelData.BarArray[0] = RSSI0Bar;
  ConfigRaceLevelData.BarArray[1] = RSSI1Bar;
  ConfigRaceLevelData.BarArray[2] = RSSI2Bar;
  ConfigRaceLevelData.BarArray[3] = RSSI3Bar;
  ConfigRaceLevelData.LabelRSSIArray[0] = RSSI0Lbl;
  ConfigRaceLevelData.LabelRSSIArray[1] = RSSI1Lbl;
  ConfigRaceLevelData.LabelRSSIArray[2] = RSSI2Lbl;
  ConfigRaceLevelData.LabelRSSIArray[3] = RSSI3Lbl;
}



/*********************************************************************
 * @brief 
 * @param 
 * @retval None 
 * Overview:        
 * @note            
 *********************************************************************/
void ConfigRaceLevelWndTasks(void){
  uint8_t Str[5];
  laString str0,str1,str2,str3;
  uint8_t i;
  

  switch (ConfigRaceLevelData.state) {
    case INITIALIZED: {
      ConfigRaceLevelData.state = IDLE;
      /* TO DO*/ // código al iniciar el módulo
      for (i=0; i<MAX_PILOTS; i++) {
        if (PilotData[i].Enabled) {
          ConfigRaceLevelData.offLevelRSSI[i]= 1023; // Se pone inicialmentee muy alta para que la función ponga el mínimo valor
        }
      }
      break;
    }
    case IDLE: {
      PilotIndex = 0; // Set the index to 0 for saving into eeprom memory when needed

//      for (i=0; i<MAX_PILOTS;i++){
//        sprintf(Str,"%d",rx5808_data.RSSI[i]);
//        laLabelWidget_SetText(ConfigRaceLevelData.LabelRSSIArray[i],laString_CreateFromCharBuffer(Str,&Calibri_Bold_20));
//      }
      break;
    }
    case GETTING_OFF_LEVEL : {
      for (i=0; i<MAX_PILOTS;i++){
        if (PilotData[i].Enabled) {
          if (ConfigRaceLevelData.offLevelRSSI[i] > rx5808_data.RSSI[i]) {
            ConfigRaceLevelData.offLevelRSSI[i] = rx5808_data.RSSI[i];
          }
        }
      }
      
      break;
    }
    case GETTING_AVERAGE: {
      
      break;
    }
    case GETTING_ON_FAR_LEVEL : {
      for (i=0; i<MAX_PILOTS;i++){
        if (PilotData[i].Enabled) {
          if (rx5808_data.RSSI[i] < PilotData[i].minRssi){
            PilotData[i].minRssi = rx5808_data.RSSI[i];
            PilotData[i].ThrLow = PilotData[i].minRssi + (uint16_t )((float)PilotData[i].minRssi*(THRESHOLD_LOW/100.0));
          }
        }
      }
      break;
    }
    
    case GETTING_MAX_LEVEL : {
      for (i=0; i<MAX_PILOTS;i++){
        if (PilotData[i].Enabled) {
          if (PilotData[i].maxRssi < rx5808_data.RSSI[i]){
            PilotData[i].maxRssi = rx5808_data.RSSI[i];
            PilotData[i].ThrHigh = PilotData[i].maxRssi - (uint16_t )(PilotData[i].maxRssi*(THRESHOLD_HIGH/100.0));
          }
        }
      }
      break;
    }
    
    case SAVING_DATA_EEPROM: {
      if (PilotIndex < MAX_PILOTS) {
        if (PilotData[PilotIndex].Enabled) {
          if (!SPI_EEPROM_IsActive()) {
            SaveConfigToEEPROM(PilotIndex);
            ConfigRaceLevelData.state = WAIT_SAVING_DATA_EEPROM;
            PilotIndex++;
          }
        } else {
          PilotIndex++;
        }
      } else {
        ConfigRaceLevelData.state = CALIBRATION_ENDED;
      }
      break;
    }
    
    case WAIT_SAVING_DATA_EEPROM: {
      Nop();
      break;
    }
    
    case CALIBRATION_ENDED : {
      ConfigRaceLevelData.state = IDLE; // Returns to idle state
      str0 = laString_CreateFromCharBuffer("Leyendo RSSI",&Calibri_Bold_20);
      laLabelWidget_SetText(StatusLbl,str0);
      laString_Destroy(&str0);
      laButtonWidget_SetText(InitCalibrationRSSILevels_Btn,
                      laString_CreateFromID(string_TouchStartLbl));

      break;
    }
  }
  
  SetRSSIBarValues();
  SetRSSILables();
  for (i = 0; i < MAX_PILOTS; i++) {
    SetBarMarkers(i);
  }
  
}

/*********************************************************************
 * @brief 
 * @param 
 * @retval None 
 * Overview:        
 * @note            
 *********************************************************************/
void InitCalibrationRSSILevels_Btn_ReleasedEvent(laButtonWidget* btn) {
  laString StrTemp;
  uint16_t i;
    
  
  switch (ConfigRaceLevelData.state) {
    case IDLE: {
      ConfigRaceLevelData.state = GETTING_OFF_LEVEL;
      StrTemp = laString_CreateFromCharBuffer("Turn OFF VTX",&Calibri_Bold_20);
      laLabelWidget_SetText(StatusLbl,StrTemp);
      StrTemp = laString_CreateFromCharBuffer("Next",&Calibri_Bold_20);
      laButtonWidget_SetText(InitCalibrationRSSILevels_Btn, StrTemp);
      laString_Destroy(&StrTemp);
      
      for (i = 0; i < MAX_PILOTS; i++) {
        if (PilotData[i].Enabled) {
          PilotData[i].maxRssi=0;
          PilotData[i].minRssi=1023;
        }
      }

      break;
    }
    case GETTING_OFF_LEVEL:{
      ConfigRaceLevelData.state = GETTING_MAX_LEVEL;
      laLabelWidget_SetText(StatusLbl,laString_CreateFromCharBuffer("Get MAX VTX Level",&Calibri_Bold_20));
      break;
    }

    case GETTING_MAX_LEVEL : {
      ConfigRaceLevelData.state = GETTING_ON_FAR_LEVEL;
      laLabelWidget_SetText(StatusLbl,laString_CreateFromCharBuffer("Get FAR VTX Level",&Calibri_Bold_20));
      laButtonWidget_SetText(InitCalibrationRSSILevels_Btn, laString_CreateFromID(string_SaveStr));
      break;
    }
    
    case GETTING_ON_FAR_LEVEL: {
      ConfigRaceLevelData.state = SAVING_DATA_EEPROM;
      laLabelWidget_SetText(StatusLbl,laString_CreateFromCharBuffer("Calib. Done!",&Calibri_Bold_20));
      
      break;
    }
    
    case SAVING_DATA_EEPROM: {
      break;
    }

    case WAIT_SAVING_DATA_EEPROM:{
      // Empty status to wait for a EEPROM Write to finish
      // The status is changed in the callback function SaveConfig_OnEnd();
      break;
    }
    
    case CALIBRATION_ENDED:{
      laLabelWidget_SetText(StatusLbl,laString_CreateFromCharBuffer("Saved to memory",&Calibri_Bold_20));
      break;
    }
  }
}


/*********************************************************************
 * @brief 
 * @param 
 * @retval None 
 * Overview:        
 * @note            
 *********************************************************************/
void SetRSSIBarValues(void){
  uint8_t barValue[MAX_PILOTS];
  
//  for (i = 0; i < MAX_PILOTS; i++) {
//    barValue[i] = (uint8_t)((100.0 * rx5808_data.RSSI[i])/(float)PilotData[i].maxRssi);
//    laProgressBarWidget_SetValue(ConfigRaceLevelData.BarArray[i],barValue[i]);
//    sprintf(Str,"%d",rx5808_data.RSSI[i]);
//    laLabelWidget_SetText(ConfigRaceLevelData.LabelRSSIArray[i],laString_CreateFromCharBuffer(Str,&Calibri_Bold_20));
//  }
    barValue[0] = (uint8_t)((100.0 * rx5808_data.RSSI[0])/(float)PilotData[0].maxRssi);
    laProgressBarWidget_SetValue(RSSI0Bar,barValue[0]);

    barValue[1] = (uint8_t)((100.0 * rx5808_data.RSSI[1])/(float)PilotData[1].maxRssi);
    laProgressBarWidget_SetValue(RSSI1Bar,barValue[1]);

    barValue[2] = (uint8_t)((100.0 * rx5808_data.RSSI[2])/(float)PilotData[2].maxRssi);
    laProgressBarWidget_SetValue(RSSI2Bar,barValue[2]);

    barValue[3] = (uint8_t)((100.0 * rx5808_data.RSSI[3])/(float)PilotData[3].maxRssi);
    laProgressBarWidget_SetValue(RSSI3Bar,barValue[3]);
    
}


void SetRSSILables(void){
  uint8_t Str[5];
  laString str0,str1,str2,str3;

  sprintf(Str,"%d",rx5808_data.RSSI[0]);
  str0 = laString_CreateFromCharBuffer(Str,&Calibri_Bold_20);
  laLabelWidget_SetText(RSSI0Lbl,str0);
  laString_Destroy(&str0);

  sprintf(Str,"%d",rx5808_data.RSSI[1]);
  str1 = laString_CreateFromCharBuffer(Str,&Calibri_Bold_20);
  laLabelWidget_SetText(RSSI1Lbl,str1);
  laString_Destroy(&str1);

  sprintf(Str,"%d",rx5808_data.RSSI[2]);
  str2 = laString_CreateFromCharBuffer(Str,&Calibri_Bold_20);
  laLabelWidget_SetText(RSSI2Lbl,str2);
  laString_Destroy(&str2);

  sprintf(Str,"%d",rx5808_data.RSSI[3]);
  str3 = laString_CreateFromCharBuffer(Str,&Calibri_Bold_20);
  laLabelWidget_SetText(RSSI3Lbl,str3);
  laString_Destroy(&str3);

}
/*********************************************************************
 * @brief 
 * @param 
 * @retval None 
 * Overview:        
 * @note            
 *********************************************************************/
void SetBarMarkers(uint8_t Sector){
  uint16_t  MaxPosValue;
  uint16_t  yPos,xPos;
  uint16_t  Pos;
  float     factor;
  
  MaxPosValue =  laWidget_GetWidth((laWidget *)RSSI0Bar);
  switch (Sector){
    case 0: {
      yPos = laWidget_GetY((laWidget *)MinRSSI0Line);
      xPos = laWidget_GetX((laWidget *)RSSI0Bar);
      factor = ( (float)MaxPosValue / PilotData[0].maxRssi);
      Pos = (uint16_t)(PilotData[0].ThrLow * factor);
      laWidget_SetPosition((laWidget *)MinRSSI0Line,xPos+Pos,yPos);

      Pos = (uint16_t)(PilotData[0].ThrHigh * factor);
      laWidget_SetPosition((laWidget *)MaxRSSI0Line,xPos+Pos,yPos);
      break;
      
    }
    case 1: {
      yPos = laWidget_GetY((laWidget *)MinRSSI1Line);
      xPos = laWidget_GetX((laWidget *)RSSI1Bar);
      factor = ( (float)MaxPosValue / PilotData[1].maxRssi);
      Pos = (uint16_t)(PilotData[1].ThrLow * factor);
      laWidget_SetPosition((laWidget *)MinRSSI1Line,xPos+Pos,yPos);

      Pos = (uint16_t)(PilotData[1].ThrHigh * factor);
      laWidget_SetPosition((laWidget *)MaxRSSI1Line,xPos+Pos,yPos);
      break;
    }
    
    case 2: {
      yPos = laWidget_GetY((laWidget *)MinRSSI2Line);
      xPos = laWidget_GetX((laWidget *)RSSI2Bar);
      factor = ( (float)MaxPosValue / PilotData[2].maxRssi);
      Pos = (uint16_t)(PilotData[2].ThrLow * factor);
      laWidget_SetPosition((laWidget *)MinRSSI2Line,xPos+Pos,yPos);
      
      Pos = (uint16_t)(PilotData[2].ThrHigh * factor);
      laWidget_SetPosition((laWidget *)MaxRSSI2Line,xPos+Pos,yPos);
      break;
    }
    
    case 3: {
      yPos = laWidget_GetY((laWidget *)MinRSSI3Line);
      xPos = laWidget_GetX((laWidget *)RSSI3Bar);
      factor = ( (float)MaxPosValue / PilotData[3].maxRssi);
      Pos = (uint16_t)(PilotData[3].ThrLow * factor);
      laWidget_SetPosition((laWidget *)MinRSSI3Line,xPos+Pos,yPos);
      
      Pos = (uint16_t)(PilotData[3].ThrHigh * factor);
      laWidget_SetPosition((laWidget *)MaxRSSI3Line,xPos+Pos,yPos);
 
      break;
    }

  }
  


}


/*********************************************************************
 * @brief 
 * @param 
 * @retval None 
 * Overview:        
 * @note            
 *********************************************************************/
void ConfigRaceLevelWnd_OnShow(laScreen* screen) {
  uint8_t Data[10];
  
  ConfigRaceLevelData.state = IDLE;
  laButtonWidget_SetReleasedEventCallback(InitCalibrationRSSILevels_Btn, &InitCalibrationRSSILevels_Btn_ReleasedEvent);
  laButtonWidget_SetReleasedEventCallback(ExitConfigLevelBtn, &ExitConfigLevelBtn_ReleasedEvent);
  
  sprintf(Data,"%c%d",BandCode[PilotData[0].Band],PilotData[0].Channel+1);
  laLabelWidget_SetText(Band0Lbl,laString_CreateFromCharBuffer(Data,&Calibri_Bold_20));
  sprintf(Data,"%c%d",BandCode[PilotData[1].Band],PilotData[1].Channel+1);
  laLabelWidget_SetText(Band1Lbl,laString_CreateFromCharBuffer(Data,&Calibri_Bold_20));
  sprintf(Data,"%c%d",BandCode[PilotData[2].Band],PilotData[2].Channel+1);
  laLabelWidget_SetText(Band2Lbl,laString_CreateFromCharBuffer(Data,&Calibri_Bold_20));
  sprintf(Data,"%c%d",BandCode[PilotData[3].Band],PilotData[3].Channel+1);
  laLabelWidget_SetText(Band3Lbl,laString_CreateFromCharBuffer(Data,&Calibri_Bold_20));
  laButtonWidget_SetPressed(Pilot0Enable,PilotData[0].Enabled);
  laButtonWidget_SetPressed(Pilot1Enable,PilotData[1].Enabled);
  laButtonWidget_SetPressed(Pilot2Enable,PilotData[2].Enabled);
  laButtonWidget_SetPressed(Pilot3Enable,PilotData[3].Enabled);
  laButtonWidget_SetReleasedEventCallback(Pilot0Enable, &PilotEnable_OnClick);
  laButtonWidget_SetPressedEventCallback(Pilot0Enable, &PilotEnable_OnClick);
  laButtonWidget_SetReleasedEventCallback(Pilot1Enable, &PilotEnable_OnClick);
  laButtonWidget_SetPressedEventCallback(Pilot1Enable, &PilotEnable_OnClick);
  laButtonWidget_SetReleasedEventCallback(Pilot2Enable, &PilotEnable_OnClick);
  laButtonWidget_SetPressedEventCallback(Pilot2Enable, &PilotEnable_OnClick);
  laButtonWidget_SetReleasedEventCallback(Pilot3Enable, &PilotEnable_OnClick);
  laButtonWidget_SetPressedEventCallback(Pilot3Enable, &PilotEnable_OnClick);
}

/*********************************************************************
 * @brief 
 * @param 
 * @retval None 
 * Overview:        
 * @note            
 *********************************************************************/
void ConfigRaceLevelWnd_OnHide(laScreen* screen) {
  
}


/*********************************************************************
 * @brief 
 * @param 
 * @retval None 
 * Overview:        
 * @note            
 *********************************************************************/
bool SaveConfigToEEPROM(uint8_t PilotId){
  if (SavePilotConfigData(PilotId, &SaveConfig_OnEnd)) {
    return true;
  } else
    return false; // Informs the calling rouotine that the saving could not be programmed yet
}

/*********************************************************************
 * @brief Call back function for saving data to eeprom
 * @param 
 * @retval None 
 * Overview:        
 * @note            
 *********************************************************************/
void SaveConfig_OnEnd(uint16_t nBytes){
  ConfigRaceLevelData.state = SAVING_DATA_EEPROM; // Continúa tratando de escribir los siguientes PilotDatas
}


/*********************************************************************
// ExitConfigLevelBtn - ReleasedEvent
*********************************************************************/
void PilotEnable_OnClick(laButtonWidget* btn) {
  uint8_t index;
  if (btn == Pilot0Enable) {
    index = 0;
  } else if (btn == Pilot1Enable) {
    index = 1;
  } else if (btn == Pilot2Enable) {
    index = 2;
  } else if (btn == Pilot3Enable) {
    index = 3;
  }
  PilotData[index].Enabled = laButtonWidget_GetPressed(btn);
  SaveEnablePilotConfigData(index,&OnSaveEnable);
}

/*********************************************************************
// On Save the Enable state of a pilotData into EEPROM
*********************************************************************/
void OnSaveEnable(uint16_t nBytes){
  
}
/* *****************************************************************************
 End of File
 */
