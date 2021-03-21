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
/* Section: Included Files                                                    */
/* ************************************************************************** */
#include "app.h"
#include "RX5808.h"
#include "ConfigPilotModuleWnd.h"
#include "gfx/libaria/inc/libaria_utils.h"
#include "PilotUnit.h"
#include "EEProm_Address.h"
#include "driver/eeprom/SPI_EEprom_Drv.h"
#include "gfx/utils/inc/gfxu_image_jpg_common.h"

/* This section lists the other files that are included in this file.
 */


/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */



/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */
void _FillModuloList(void);
void _UpdateFreqLbl(void);
void ConfigPilotWndOnShow(laScreen* screen);
void _EmptyModuloList(void);
void ConfigPilotWndOnHide(laScreen* screen);
void ModuloList_SelectionChangedEvent(laListWidget* img, uint32_t idx, laBool selected);
void SendFreqBtn_OnClick(laButtonWidget* btn);
void ChannelBtn_OnClick(laButtonWidget* btn);
void BandBtn_OnClick(laButtonWidget* btn);
void DropDownBtn_ReleasedEvent(laButtonWidget* btn);
void ConfigPilotModuleWnd_OnSavePilotDataEnd( uint16_t nBytes);





/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */

void ConfigPilotWnd_Initialize(void){
  laScreen* screen;

  screen = (laScreen*)laContext_GetActive()->screenList.values[ConfigPilotWnd_ID];
  laScreen_SetShowEventCallback(screen, &ConfigPilotWndOnShow); // Set CallBack function
  laScreen_SetHideEventCallback(screen,&ConfigPilotWndOnHide);
  ConfigPilotData.PilotModule = 0;
}

/*********************************************************************
 * @brief 
 * @param 
 * @retval None 
 * Overview:        
 * @note            
 *********************************************************************/
void ConfigPilotModuleTasks(void){
  laString str2;
  uint8_t Data[8];
  
  if ( laWidget_GetVisible((laWidget *)ModuloList)) {
    Nop(); // Do nthing if any of the lists are visible.
  } else { // If none of the lists are visible then update the RSSI Label
    if (RX5808_GetState() == RX5808_RSSI_READY) {
      sprintf(Data,"%d",RX5808_GetRSSIData(ConfigPilotData.PilotModule));
      RX5808_SetState(RX5808_IDLE);

      str2 = laString_CreateFromCharBuffer(Data,&Calibri_Bold_20);
      laLabelWidget_SetText(RSSI_lbl,str2);
      laString_Destroy(&str2);          
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
void ConfigPilotWndOnShow(laScreen* screen) {
  uint8_t Band, Channel;
  uint8_t Str[15];
  uint32_t Freq;
  laString StrTemp;
  
  ConfigPilotData.state = LOADING_SCREEN_DATA;
	_FillModuloList();
  laListWidget_SetSelectedItemChangedEventCallback(ModuloList, &ModuloList_SelectionChangedEvent);
  laButtonWidget_SetReleasedEventCallback(ModuleDropDownBtn, &DropDownBtn_ReleasedEvent);

  laButtonWidget_SetReleasedEventCallback(BandDownBtn, &BandBtn_OnClick);
  laButtonWidget_SetReleasedEventCallback(BandUpBtn, &BandBtn_OnClick);
  laButtonWidget_SetReleasedEventCallback(ChannelDownBtn, &ChannelBtn_OnClick);
  laButtonWidget_SetReleasedEventCallback(ChannelUpBtn, &ChannelBtn_OnClick);

  
  laButtonWidget_SetReleasedEventCallback(SendFreqBtn, &SendFreqBtn_OnClick);
  Freq = RX5808_GetChannel(ConfigPilotData.PilotModule); // Reads from the hardware to ensure the RX Channel stored there at the begining of the app
  RX5808_GetBandChannel(Freq, &ConfigPilotData.Band, &ConfigPilotData.Channel);
  if (Band != 0xFF) {
    sprintf(Str,"Piloto %d",ConfigPilotData.PilotModule+1);
    StrTemp = laString_CreateFromCharBuffer(Str,&Calibri_Bold_20);
    laTextFieldWidget_SetText(ModuleEdit,StrTemp);
    laString_Destroy(&StrTemp);
    laListWidget_SetItemSelected(ModuloList, ConfigPilotData.PilotModule, true);
    
    sprintf(Str,"Banda %c",BandCode[ConfigPilotData.Band]);
    StrTemp = laString_CreateFromCharBuffer(Str,&Calibri_Bold_20);
    laTextFieldWidget_SetText(BandEdit,StrTemp);
    laString_Destroy(&StrTemp);

    sprintf(Str,"CH %d",ConfigPilotData.Channel+1);
    StrTemp = laString_CreateFromCharBuffer(Str,&Calibri_Bold_20);
    laTextFieldWidget_SetText(ChannelEdit, StrTemp);
    laString_Destroy(&StrTemp);
    
    _UpdateFreqLbl();
  } 
  ConfigPilotData.state = RUNNING;
}

/*********************************************************************
 * @brief 
 * @param 
 * @retval None 
 * Overview:        
 * @note            
 *********************************************************************/
void ConfigPilotWndOnHide(laScreen* screen) {
  _EmptyModuloList();
}

/*********************************************************************
 * @brief 
 * @param 
 * @retval None 
 * Overview:        
 * @note            
 *********************************************************************/
void ChannelBtn_OnClick(laButtonWidget* btn){
	uint8_t Str[10];
  if (btn == ChannelDownBtn ) {
    ConfigPilotData.Channel--;
    if (ConfigPilotData.Channel>=254) { // This is because I used an unsigned byte for this variable.
      ConfigPilotData.Channel = MAX_VTX_CHANNELS-1; // Hace un rollup hasta el máximo
    }
  } else if (btn == ChannelUpBtn) {
		ConfigPilotData.Channel++;
    if (ConfigPilotData.Channel >= MAX_VTX_CHANNELS) {
			ConfigPilotData.Channel = 0;
    }
  }
	sprintf(Str,"CH %d",ConfigPilotData.Channel+1);
	laTextFieldWidget_SetText(ChannelEdit, laString_CreateFromCharBuffer(Str,&Calibri_Bold_20));
  _UpdateFreqLbl();
}

/*********************************************************************
 * @brief 
 * @param 
 * @retval None 
 * Overview:        
 * @note            
 *********************************************************************/
void BandBtn_OnClick(laButtonWidget* btn){
	uint8_t Str[6];
  if (btn == BandDownBtn ) {
    ConfigPilotData.Band--;
    if (ConfigPilotData.Band>=254) { // This is because I used an unsigned byte for this variable.
      ConfigPilotData.Band = MAX_BANDS-1; // Hace un rollup hasta el máximo
    }
  } else if (btn == BandUpBtn) {
		ConfigPilotData.Band++;
    if (ConfigPilotData.Band >= MAX_BANDS) {
			ConfigPilotData.Band = 0;
    }
  }
	
	sprintf(Str,"Banda %c",BandCode[ConfigPilotData.Band]);
	laTextFieldWidget_SetText(BandEdit, laString_CreateFromCharBuffer(Str,&Calibri_Bold_20));
  _UpdateFreqLbl();
 
}


/*********************************************************************
 * @brief 
 * @param 
 * @retval None 
 * Overview:        
 * @note            
 *********************************************************************/// ModuloList - SelectionChangedEvent
void ModuloList_SelectionChangedEvent(laListWidget* img, uint32_t idx, laBool selected) {
  uint8_t Str[15];
  uint8_t Band, Channel;
  uint32_t Freq;
  laString StrTemp;
  
  // Only enters if it's already loaded the data into screen objects
  if (ConfigPilotData.state != LOADING_SCREEN_DATA) {
    ConfigPilotData.state = RUNNING; // Para habilitar la actualización del RSSI 
    ConfigPilotData.PilotModule = laListWidget_GetLastSelectedItem((laListWidget*)ModuloList);
    if (selected) {
      ConfigPilotData.PilotModule = idx;
      Freq = RX5808_GetChannel(ConfigPilotData.PilotModule);
      RX5808_GetBandChannel(Freq, &Band, &Channel);
      //Se agrega esta comparación porque la frecuencia del canal F8 es igual a la de R7 entonces si 
      // Es alguno de estos canales lo que lee segun la frecuencia entonces lo iguala a lo que tenga configurado
      // en la variable de piloto.
      if ((BandCode[Band] == 'F' && Channel == 7) && (BandCode[Band] == 'R' && Channel == 6)){
        Band = PilotData[ConfigPilotData.PilotModule].Band;
        Channel = ConfigPilotData.Channel;
      }
      if (Band == PilotData[ConfigPilotData.PilotModule].Band) {
        if (Band != 0xFF) {
          ConfigPilotData.Band = Band;
          ConfigPilotData.Channel = Channel;
        } 
        sprintf(Str,"Banda %c",BandCode[ConfigPilotData.Band]);
        laTextFieldWidget_SetText(BandEdit, laString_CreateFromCharBuffer(Str,&Calibri_Bold_20));

        sprintf(Str,"CH %d",ConfigPilotData.Channel+1);
        laTextFieldWidget_SetText(ChannelEdit, laString_CreateFromCharBuffer(Str,&Calibri_Bold_20));
      } else{
        laTextFieldWidget_SetText(BandEdit, laString_CreateFromCharBuffer("Error",&Calibri_Bold_20));
        laTextFieldWidget_SetText(ChannelEdit, laString_CreateFromCharBuffer("Error",&Calibri_Bold_20));
      }
    _UpdateFreqLbl();
      
    }
    laWidget_SetVisible((laWidget*)ModuloList, false); // hide the Pilot List
    sprintf(Str,"Piloto %d",ConfigPilotData.PilotModule+1);
    StrTemp = laString_CreateFromCharBuffer(Str,&Calibri_Bold_20);
    laTextFieldWidget_SetText(ModuleEdit,StrTemp);
    laString_Destroy(&StrTemp);
    laContext_RedrawAll();
  }
}


/*********************************************************************
 * @brief 
 * @param 
 * @retval None 
 * Overview:        
 * @note            
 *********************************************************************/
void DropDownBtn_ReleasedEvent(laButtonWidget* btn) {
  laBool  visible;
  
	visible = laWidget_GetVisible((laWidget *)ModuloList);
	laWidget_SetVisible((laWidget*) ModuloList, !visible);

}




void _UpdateFreqLbl(void){
  uint8_t Str[10];
  laString StrTemp;

  sprintf(Str,"%dMHz",RX5808_GetFreqGHZ(ConfigPilotData.Band, ConfigPilotData.Channel));
  StrTemp = laString_CreateFromCharBuffer(Str,&Calibri_Bold_20);
  laLabelWidget_SetText(FreqLbl, StrTemp);
  laString_Destroy(&StrTemp);

  
}
/*********************************************************************
 * @brief 
 * @param 
 * @retval None 
 * Overview:        
 * @note            
 *********************************************************************/
void SendFreqBtn_OnClick(laButtonWidget* btn){
  
  
  RX5808_SetChannel(ConfigPilotData.PilotModule, ConfigPilotData.Band, ConfigPilotData.Channel);
  if (ConfigPilotData.PilotModule < MAX_PILOTS) {
    PilotData[ConfigPilotData.PilotModule].Band = ConfigPilotData.Band;
    PilotData[ConfigPilotData.PilotModule].Channel = ConfigPilotData.Channel;
    PilotData[ConfigPilotData.PilotModule].Freq = RX5808_GetFreqGHZ(ConfigPilotData.Band,ConfigPilotData.Channel); // Ensure the correct freq value
    SaveFreqPilotConfigData(ConfigPilotData.PilotModule, &ConfigPilotModuleWnd_OnSavePilotDataEnd); // Graba en EEPROM solo la Banda y Canal
  }
  
}

void ConfigPilotModuleWnd_OnSavePilotDataEnd( uint16_t nBytes){
  laContext_RedrawAll(); // Forza el update de toda la pantalla
}



/*********************************************************************
 * @brief 
 * @param 
 * @retval None 
 * Overview:        
 * @note            
 *********************************************************************/
void _FillModuloList(void) {
  uint8_t index;
  uint8_t Str [10];

  
  for (index = 0; index < 4; index++) {
    laListWidget_AppendItem(ModuloList);
    sprintf(Str,"Piloto %d",index + 1);
    laListWidget_SetItemText(ModuloList, index, laString_CreateFromCharBuffer(Str,&Calibri_Bold_20));
  }
}

/*********************************************************************
 * @brief 
 * @param 
 * @retval None 
 * Overview:        
 * @note            
 *********************************************************************/
void _EmptyModuloList(void){
  laListWidget_RemoveAllItems(ModuloList);
}
/* *****************************************************************************
 End of File
 */
