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
#include "../app.h"
#include "../RX5808.h"
#include "ConfigRaceThrLevelsWnd.h"
#include "gfx/libaria/inc/libaria_utils.h"
#include "gfx/libaria/libaria_init.h"
#include "../PilotUnit.h"
#include "driver/eeprom/SPI_EEprom_Drv.h"
#include "../Utils.h"
#include <stdlib.h>


/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
static uint8_t PilotIndex;



/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */
void ConfigRaceThrLevelWnd_OnShow(laScreen* screen);
void ConfigRaceThrLevelWnd_OnHide(laScreen* screen);
void PilotSelectBtn_OnPressed(laButtonWidget* btn);
void SaveConfigThrLevelBtn_ReleasedEvent(laButtonWidget* btn);
void SetRSSIBarValue(void);
void SetBarMarker(void);
void SetRSSILable(void);
void SaveConfigThr_OnEnd(uint16_t nBytes);
void OnEditFocus (laTextFieldWidget * widget, laBool focus);
void OnEditChange(laTextFieldWidget * widget);
void ProcessValueInput(void);
void KeyPad1OnClick(laKeyPadWidget* KeyPadObject, laButtonWidget * ButtonObject, 
                   uint32_t row, uint32_t col);
void UpdateEditValues(uint8_t PilotId);



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
void ConfigRaceThrLevelsWndInitialize(void){
  laScreen* screen;

  screen = (laScreen*)laContext_GetActive()->screenList.values[ConfigThrLevelWnd_ID];
  laScreen_SetShowEventCallback(screen, &ConfigRaceThrLevelWnd_OnShow); // Set CallBack function
  laScreen_SetHideEventCallback(screen,&ConfigRaceThrLevelWnd_OnHide);
  ConfigRaceThrLevelData.state = TRH_INITIALIZED;
}

/*********************************************************************
 * @brief 
 * @param 
 * @retval None 
 * Overview:        
 * @note            
 *********************************************************************/
void ConfigRaceThrLevelWnd_OnShow(laScreen* screen) {
  laString Str;
  uint8_t Data[15];

  
  ConfigRaceThrLevelData.state = TRH_INITIALIZED;
  ConfigRaceThrLevelData.PilotId = 0;

  laButtonWidget_SetReleasedEventCallback(SaveConfigThrLevelBtn, &SaveConfigThrLevelBtn_ReleasedEvent);
  
  UpdateEditValues(0);
  laButtonWidget_SetPressedEventCallback(Pilot0Btn , &PilotSelectBtn_OnPressed);
  laButtonWidget_SetPressedEventCallback(Pilot1Btn , &PilotSelectBtn_OnPressed);
  laButtonWidget_SetPressedEventCallback(Pilot2Btn , &PilotSelectBtn_OnPressed);
  laButtonWidget_SetPressedEventCallback(Pilot3Btn , &PilotSelectBtn_OnPressed);
  
  laTextFieldWidget_SetFocusChangedEventCallback(MinRSSIThrEdit, &OnEditFocus);
  laTextFieldWidget_SetFocusChangedEventCallback(MaxRSSIThrEdit, &OnEditFocus);
  laTextFieldWidget_SetTextChangedEventCallback(MinRSSIThrEdit, &OnEditChange);
  laTextFieldWidget_SetTextChangedEventCallback(MaxRSSIThrEdit, &OnEditChange);

  laKeyPadWidget_SetKeyClickEventCallback(KeyPad1, &KeyPad1OnClick);
  
  
  sprintf(Data,"%c%d - %dMHz", BandCode[PilotData[ConfigRaceThrLevelData.PilotId].Band],
                              PilotData[ConfigRaceThrLevelData.PilotId].Channel+1,
                              PilotData[ConfigRaceThrLevelData.PilotId].Freq);
  Str = laString_CreateFromCharBuffer(Data,&Calibri_Bold_20);
  laLabelWidget_SetText(BandaLbl,Str);
  laString_Destroy(&Str);  
  SetBarMarker();

//  laContext_SetEditWidget((laWidget*)MaxRSSIThrEdit);
//  laEditWidget_StartEdit();

}

/*********************************************************************
 * @brief 
 * @param 
 * @retval None 
 * Overview:        
 * @note            
 *********************************************************************/
void ConfigRaceThrLevelWnd_OnHide(laScreen* screen) {
  
}


/*********************************************************************
 * @brief 
 * @param 
 * @retval None 
 * Overview:        
 * @note            
 *********************************************************************/
void ConfigRaceThrLevelWndTasks(void){
  switch (ConfigRaceThrLevelData.state) {
    case TRH_INITIALIZED: {
      ConfigRaceThrLevelData.state = TRH_IDLE;
      ConfigRaceThrLevelData.PilotId = 0;
      /* TO DO*/ // código al iniciar el módulo
      break;
    }
    case TRH_IDLE: {
      break;
    }
  
    case TRH_SAVING_DATA_EEPROM: {
      
      break;
    }
    
    case TRH_SAVE_DONE: {
      break;
    }
    
  }
  
  SetRSSIBarValue();
  SetRSSILable();
  
}



void UpdateEditValues(uint8_t PilotId){
  uint8_t Data[6];
  sprintf(Data,"%d",PilotData[PilotId].ThrLow);
  laTextFieldWidget_SetText(MinRSSIThrEdit,laString_CreateFromCharBuffer(Data,&Calibri_Bold_20));
  sprintf(Data,"%d",PilotData[PilotId].ThrHigh);
  laTextFieldWidget_SetText(MaxRSSIThrEdit,laString_CreateFromCharBuffer(Data,&Calibri_Bold_20));
  
}

/*********************************************************************
 * @brief 
 * @param 
 * @retval None 
 * Overview:        
 * @note            
 *********************************************************************/
void SetRSSIBarValue(void){
  uint8_t barValue;
  uint8_t PilotId;
  
  PilotId = ConfigRaceThrLevelData.PilotId;
  barValue = (uint8_t)((100.0 * rx5808_data.RSSI[PilotId])/(float)PilotData[PilotId].maxRssi);
  laProgressBarWidget_SetValue(RSSIBar,barValue);
}


void SetRSSILable(void){
  uint8_t Str[5];
  laString str0;

  sprintf(Str,"%d",rx5808_data.RSSI[ConfigRaceThrLevelData.PilotId]);
  str0 = laString_CreateFromCharBuffer(Str,&Calibri_Bold_20);
  laLabelWidget_SetText(RSSILbl,str0);
  laString_Destroy(&str0);
}


/*********************************************************************
 * @brief 
 * @param 
 * @retval None 
 * Overview:        
 * @note            
 *********************************************************************/
void SetBarMarker(void){
  uint16_t  MaxPosValue;
  uint16_t  yPos,xPos;
  uint16_t  Pos;
  float     factor;
  uint8_t  xSize;
  
  xSize = laWidget_GetWidth((laWidget *)MinRSSILine);
  MaxPosValue =  laWidget_GetWidth((laWidget *)RSSIBar);
  yPos = laWidget_GetY((laWidget *)MinRSSILine);
  xPos = laWidget_GetX((laWidget *)RSSIBar) - (xSize >> 1); // Ajusta la posición a la mitad de la imagen de la flecha
  factor = ( (float)MaxPosValue / PilotData[ConfigRaceThrLevelData.PilotId].maxRssi);
  Pos = (uint16_t)(PilotData[ConfigRaceThrLevelData.PilotId].ThrLow * factor);
  laWidget_SetPosition((laWidget *)MinRSSILine,xPos+Pos,yPos);

  Pos = (uint16_t)(PilotData[ConfigRaceThrLevelData.PilotId].ThrHigh * factor);
  laWidget_SetPosition((laWidget *)MaxRSSILine,xPos+Pos,yPos);  
}



/*********************************************************************
 * @brief 
 * @param 
 * @retval None 
 * Overview:        
 * @note            
 *********************************************************************/
void OnEditFocus (laTextFieldWidget * widget, laBool focus){
  if (focus == LA_TRUE) {
    if ((laContext_GetFocusWidget() == (laWidget *)MinRSSIThrEdit) ||
        ((laContext_GetFocusWidget() == (laWidget *)MaxRSSIThrEdit))){
      laWidget_SetVisible((laWidget *)KeyPad1,focus); // Sets visible the keypad if an edit fields is focused
      laWidget_SetPosition((laWidget *)KeyPad1,55,180);
      
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
void OnEditChange(laTextFieldWidget * widget){
  laString CelValue;
  uint8_t TempValueStr[8];
  uint16_t  intValue;
  
  laString_Initialize(&CelValue);
  laTextFieldWidget_GetText(widget, &CelValue);
  GetCharFrom_laString(&CelValue, TempValueStr);
  intValue = atoi(TempValueStr);
  laString_Destroy(&CelValue);
  if (intValue < 1023) {
    laWidget_SetVisible((laWidget *)SaveConfigThrLevelBtn,true); // Enable the saving button because it changed the values

    if (widget == MinRSSIThrEdit ) {
      PilotData[ConfigRaceThrLevelData.PilotId].ThrLow = intValue;
    } else if (widget == MaxRSSIThrEdit) {
      PilotData[ConfigRaceThrLevelData.PilotId].ThrHigh = intValue;

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
void ProcessValueInput(void){
  
}


/*********************************************************************
 * @brief This is the KeyPad OnClick call back
 * @param 
 * @retval None 
 * Overview:        
 * @note            
 *********************************************************************/
void KeyPad1OnClick(laKeyPadWidget* KeyPadObject, laButtonWidget * ButtonObject, 
                   uint32_t row, uint32_t col) {
  
  if (row == 3 && col == 2){
    laWidget_SetVisible((laWidget *)KeyPadObject, false);
    laWidget_SetPosition((laWidget *)KeyPad1,260,180);
    SetBarMarker();
  }
  
}



/*********************************************************************
 * @brief Call back function for saving data to eeprom
 * @param 
 * @retval None 
 * Overview:        
 * @note            
 *********************************************************************/
void SaveConfigThr_OnEnd(uint16_t nBytes){
  ConfigRaceThrLevelData.state = TRH_IDLE; // Continúa tratando de escribir los siguientes PilotDatas
  laWidget_SetVisible((laWidget *)SaveConfigThrLevelBtn,false); // Enable the saving button because it changed the values
}

/*********************************************************************
// ExitConfigLevelBtn - ReleasedEvent
*********************************************************************/
void SaveConfigThrLevelBtn_ReleasedEvent(laButtonWidget* btn) {
  SavePilotConfigData(ConfigRaceThrLevelData.PilotId, &SaveConfigThr_OnEnd);
  ConfigRaceThrLevelData.state = TRH_SAVING_DATA_EEPROM;
}




/*********************************************************************
// PilotSelectBtn - PressedEvent
*********************************************************************/
void PilotSelectBtn_OnPressed(laButtonWidget* btn) {
  laBool  Pressed;
  laString Str;
  uint8_t Data[15];
  
  Pressed = laButtonWidget_GetPressed(btn);

  laWidget_SetEnabled((laWidget *)Pilot0Btn, true);
  laWidget_SetEnabled((laWidget *)Pilot1Btn, true);
  laWidget_SetEnabled((laWidget *)Pilot2Btn, true);
  laWidget_SetEnabled((laWidget *)Pilot3Btn, true);

  laWidget_SetEnabled((laWidget *)btn, false);
  
  
  if (Pressed == LA_TRUE) {
    if (btn == Pilot0Btn ) {
      ConfigRaceThrLevelData.PilotId = 0;
      laButtonWidget_SetPressed(Pilot1Btn, false);
      laButtonWidget_SetPressed(Pilot2Btn, false);
      laButtonWidget_SetPressed(Pilot3Btn, false);
    } else if (btn == Pilot1Btn) {
      ConfigRaceThrLevelData.PilotId = 1;
      laButtonWidget_SetPressed(Pilot0Btn, false);
      laButtonWidget_SetPressed(Pilot2Btn, false);
      laButtonWidget_SetPressed(Pilot3Btn, false);
    } else if (btn == Pilot2Btn) {
      ConfigRaceThrLevelData.PilotId = 2;
      laButtonWidget_SetPressed(Pilot0Btn, false);
      laButtonWidget_SetPressed(Pilot1Btn, false);
      laButtonWidget_SetPressed(Pilot3Btn, false);
    } else if (btn == Pilot3Btn) {
      ConfigRaceThrLevelData.PilotId = 3;
      laButtonWidget_SetPressed(Pilot0Btn, false);
      laButtonWidget_SetPressed(Pilot1Btn, false);
      laButtonWidget_SetPressed(Pilot2Btn, false);
    }
    
    UpdateEditValues(ConfigRaceThrLevelData.PilotId);
    SetBarMarker();

    sprintf(Data,"%c%d - %dMHz",BandCode[PilotData[ConfigRaceThrLevelData.PilotId].Band],
                                PilotData[ConfigRaceThrLevelData.PilotId].Channel+1,
                                PilotData[ConfigRaceThrLevelData.PilotId].Freq);
    Str = laString_CreateFromCharBuffer(Data,&Calibri_Bold_20);
    laLabelWidget_SetText(BandaLbl,Str);
    laString_Destroy(&Str);
    
    laContext_RedrawAll();
  } else {
//    laButtonWidget_SetPressed(btn, true);
  }
  
//  PilotData[index].Enabled = laButtonWidget_GetPressed(btn);
//  SaveEnablePilotConfigData(index,&OnSaveEnable);
}

/* *****************************************************************************
 End of File
 */
