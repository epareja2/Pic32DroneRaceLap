/*! \file *********************************************************************
 *
 * \brief "DESCRIPCION DEL MODULO".
 *
 * "DESCRIPCION MAS AMPLIA"
 *
 * - File:               TouchWnd.c
 * - Compiler:           MPLABX 
 * - Supported devices:  
 *
 * \author               Ernesto Pareja  (epareja)
 *
 * REVISION HISTORY:
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Author            Date      Comments on that revision
 *----------------------------------------------------------------------
 * Epareja       17 de diciembre de 2017, 05:19 PM  Creation of file
 * 
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * ADDITIONAL NOTES:
 *
 *****************************************************************************/



/*********************************************************************
 /*                      INCLUDES        
 /*********************************************************************/
#include "TouchWnd.h"
#include "app.h"
#include "gfx/libaria/inc/libaria_widget.h"
#include "driver/eeprom/SPI_EEprom_Drv.h"
#include "ads7843/drv_ads7843_local.h"
#include "ads7843/drv_ads7843.h"
//#include "gfx/libaria/inc/libaria_utils.h"
//#include "DemoWnd.h"
#include "../EEProm_Address.h"

/*********************************************************************
 /*                      LOCAL VARIABLES        
 /*********************************************************************/


/*********************************************************************
 /*                      PRIVATE FUNCTION DECLARATIONS        
 /*********************************************************************/
void TouchWnd_InitCalibrationProcess(void);
void TouchWnd_FirstCalibrationPoint(DRV_ADS7843_TOUCH_POINT_DATA * point, DRV_ADS7843_MICRO_STATE state);
void TouchWnd_SecondCalibrationPoint(DRV_ADS7843_TOUCH_POINT_DATA * point, DRV_ADS7843_MICRO_STATE state);
void TouchWnd_ThirdCalibrationPoint(DRV_ADS7843_TOUCH_POINT_DATA * point, DRV_ADS7843_MICRO_STATE state);
void TouchWnd_SaveCalibration(DRV_ASD7843_CALIBRATION_MATRIX * Matrix);
void TouchWnd_CalibrationComplete(void);
void TouchWnd_OnSaveCalibrationEnd( uint16_t nBytes);

void TouchOkBtn_OnRelease(laButtonWidget* btn);
void TouchWndOnShow(laScreen* screen);
void TouchWndOnHide(laScreen* screen);


/*********************************************************************
 /*                      CODE IMPLEMENTATION        
 /*********************************************************************/


/*********************************************************************
 * @brief 
 * @param 
 * @retval None 
 * Overview:        
 * @note            
 *********************************************************************/
void TouchWndInitialize(void){
  laScreen* screen;
  const DRV_TOUCH_ADS7843_CALIBRATION_PROMPT_CALLBACK cb = {
    .initProcessPromptCallback = &TouchWnd_InitCalibrationProcess,
    .firstPromptCallback = &TouchWnd_FirstCalibrationPoint,
    .secondPromptCallback = &TouchWnd_SecondCalibrationPoint,
    .thirdPromptCallback = &TouchWnd_ThirdCalibrationPoint,
    .completeCallback = &TouchWnd_CalibrationComplete,
    .NVMSaveCalibration = &TouchWnd_SaveCalibration,
  };
  DRV_TOUCH_ADS7843_CalibrationSetCallBack(&cb);
  screen = (laScreen*)laContext_GetActive()->screenList.values[TouchCalibrationWnd_ID];
  laScreen_SetShowEventCallback(screen, &TouchWndOnShow); // Set CallBack function
  laScreen_SetHideEventCallback(screen,&TouchWndOnHide);
  TouchWnd_state = READING_XY;
}

/*********************************************************************
 * @brief 
 * @param 
 * @retval None 
 * Overview:        
 * @note            
 *********************************************************************/
void TouchWndOnShow(laScreen* screen) {
  laButtonWidget_SetReleasedEventCallback(TouchOkBtn, &TouchOkBtn_OnRelease);  
  
}

/*********************************************************************
 * @brief 
 * @param 
 * @retval None 
 * Overview:        
 * @note            
 *********************************************************************/
void TouchWndOnHide(laScreen* screen) {
  
}


/*********************************************************************
 * @brief 
 * @param 
 * @retval None 
 * Overview:        
 * @note            
 *********************************************************************/
void TouchWndTasks(void){
  laString str;
  static uint16_t LastXPos, LastYPos;
  uint16_t XPos, YPos;
  char charBuff[20];
  
  switch (TouchWnd_state){
    case READING_XY: {
      XPos = DRV_TOUCH_ADS7843_TouchGetX(0);
      YPos = DRV_TOUCH_ADS7843_TouchGetY(0);
      if ((LastXPos != XPos) || (LastYPos != YPos) ){
        sprintf(charBuff, "(%d,%d)", XPos, YPos);

        str = laString_CreateFromCharBuffer(charBuff, &Calibri_Bold_20);
//          str = laString_CreateFromCharBuffer(charBuff,GFXU_StringFontIndexLookup(&stringTable, string_TouchPointStr, 0));

        laLabelWidget_SetText(TouchPointLbl, str);
        laString_Destroy(&str);
      }
      LastXPos = XPos;
      LastYPos = YPos;

      
    }break;

    case START_CALIBRATING: {
      if (DRV_TOUCH_ADS7843_CalibrationStart());
      TouchWnd_state = CALIBRATING;
    }break;
    
    case CALIBRATING: {
      
    }break;
    
    case END_CALIBRATION :{
      TouchWnd_state = READING_XY;      
    }break;

  }
}




/*********************************************************************
 * @brief 
 * @param 
 * @retval None 
 * Overview:        
 * @note            
 ********************************************************************/
void TouchWnd_InitCalibrationProcess(void){
  
  BSP_LED_1On();
  BSP_LED_2On();
  laWidget_SetVisible((laWidget*) TouchWndCaptionPanel, false);
  
  
//  laWidget_SetPosition((laWidget*) GreenPointImg, 33,46);
  
}


/*********************************************************************
 * @brief 
 * @param 
 * @retval None 
 * Overview:        
 * @note            
 ********************************************************************/
void TouchWnd_FirstCalibrationPoint(DRV_ADS7843_TOUCH_POINT_DATA * point, 
                                    DRV_ADS7843_MICRO_STATE state) 
{
  laString newText;
  uint8_t radius; // Cicle point radius to compensate position
  laString str;
  uint16_t XPos, YPos;
  char charBuff[20];

  BSP_LED_1Off();
  
  switch (state) {
    case DRAW_POINT: {
      radius = laCircleWidget_GetRadius(CirclePoint);
      laImageWidget_SetImage(GreenPointImg, &PuntoVerde);
      newText = laString_CreateFromCharBuffer("Press and release",&Calibri_Bold_20);
      laLabelWidget_SetText(TouchMsg1Lbl, newText);
      newText = laString_CreateFromCharBuffer("on the filled circle",&Calibri_Bold_20);
      laLabelWidget_SetText(TouchMsg2Lbl, newText);
      laWidget_SetPosition((laWidget*) CirclePoint,  point->xPoint - radius,point->yPoint - radius);
      laWidget_SetVisible((laWidget*) CirclePoint, true);
      laWidget_SetVisible((laWidget*) GreenPointImg, true);
      laString_Destroy(&newText);
      break;
    }
    
    case TOUCH_PRESSED:{
      XPos = DRV_TOUCH_ADS7843_TouchGetRawX()*240/1024;
      YPos = DRV_TOUCH_ADS7843_TouchGetRawY()*320/1024;
      sprintf(charBuff, "(%d,%d)", XPos, YPos);

      str = laString_CreateFromCharBuffer(charBuff, &Calibri_Bold_20);
      laLabelWidget_SetText(TouchPointLbl, str);
      laString_Destroy(&str);
      
      break;
    }
    
    case TOUCH_LIFT: {
      laImageWidget_SetImage(GreenPointImg, &PuntoRojo);
    }
    default : {
      
    }
  }
  
}
/*********************************************************************
 * @brief 
 * @param 
 * @retval None 
 * Overview:        
 * @note            
 ********************************************************************/
void TouchWnd_SecondCalibrationPoint(DRV_ADS7843_TOUCH_POINT_DATA * point,
                                     DRV_ADS7843_MICRO_STATE state)
{
  uint8_t radius; // Cicle point radius to compensate position
  laString str;
  uint16_t XPos, YPos;
  char charBuff[20];

  radius = laCircleWidget_GetRadius(CirclePoint);

  BSP_LED_1On();
//  laWidget_SetPosition((laWidget*) CirclePoint, 200,42);
  switch (state) {
    case DRAW_POINT: {
      laImageWidget_SetImage(GreenPointImg, &PuntoVerde);
      radius = laCircleWidget_GetRadius(CirclePoint);
      laWidget_SetPosition((laWidget*) CirclePoint,  point->xPoint - radius,point->yPoint - radius);
      break;
    }
    
    case TOUCH_PRESSED:{
      XPos = DRV_TOUCH_ADS7843_TouchGetRawX()*240/1024;
      YPos = DRV_TOUCH_ADS7843_TouchGetRawY()*320/1024;
      sprintf(charBuff, "(%d,%d)", XPos, YPos);

      str = laString_CreateFromCharBuffer(charBuff, &Calibri_Bold_20);
      laLabelWidget_SetText(TouchPointLbl, str);
      laString_Destroy(&str);
      break;
    }
    
    case TOUCH_LIFT: {
      laImageWidget_SetImage(GreenPointImg, &PuntoRojo);
    }
    default : {
      
    }
  }
  
}
/*********************************************************************
 * @brief 
 * @param 
 * @retval None 
 * Overview:        
 * @note            
 ********************************************************************/
void TouchWnd_ThirdCalibrationPoint(DRV_ADS7843_TOUCH_POINT_DATA * point,
                                    DRV_ADS7843_MICRO_STATE state)
{
  uint8_t radius; // Cicle point radius to compensate position
  laString str;
  uint16_t XPos, YPos;
  char charBuff[20];

  BSP_LED_2Off();
  
  switch (state) {
    case DRAW_POINT: {
      laImageWidget_SetImage(GreenPointImg, &PuntoVerde);
      radius = laCircleWidget_GetRadius(CirclePoint);
      laWidget_SetPosition((laWidget*) CirclePoint,  point->xPoint - radius,point->yPoint-radius);
      break;
    }
    
    case TOUCH_PRESSED:{
      XPos = DRV_TOUCH_ADS7843_TouchGetRawX()*240/1024;
      YPos = DRV_TOUCH_ADS7843_TouchGetRawY()*320/1024;
      sprintf(charBuff, "(%d,%d)", XPos, YPos);

      str = laString_CreateFromCharBuffer(charBuff, &Calibri_Bold_20);
      laLabelWidget_SetText(TouchPointLbl, str);
      laString_Destroy(&str);
      break;
    }
    
    case TOUCH_LIFT: {
      laImageWidget_SetImage(GreenPointImg, &PuntoRojo);
    }
    default : {
      
    }
  }
//  laWidget_SetPosition((laWidget*) CirclePoint,  200,245);
  
}

/*********************************************************************
 * @brief 
 * @param 
 * @retval None 
 * Overview:        
 * @note            
 ********************************************************************/
void TouchWnd_CalibrationComplete(void){
  laString newText;
  laString newText2;

  BSP_LED_2On();
  BSP_LED_1Off();

  TouchWnd_state = END_CALIBRATION;
  laWidget_SetVisible((laWidget*) TouchWndCaptionPanel, true);

  newText = laString_CreateFromID(string_ButtonOK);
  laButtonWidget_SetText(TouchOkBtn, newText);
  newText = laString_CreateFromCharBuffer("Press Ok Button to save",&Calibri_Bold_20);
  laLabelWidget_SetText(TouchMsg1Lbl, newText);
  newText2 = laString_CreateFromCharBuffer("and exit calibration.",&Calibri_Bold_20);
  laLabelWidget_SetText(TouchMsg2Lbl, newText2);
//  laCircleWidget_SetOrigin(CirclePoint,30,42);
  laWidget_SetVisible((laWidget*) CirclePoint, false);
  laString_Destroy(&newText);
  laString_Destroy(&newText2);
  
  
}

/*********************************************************************
 * @brief 
 * @param 
 * @retval None 
 * Overview:        
 * @note             
 *********************************************************************/
void TouchWnd_SaveCalibration(DRV_ASD7843_CALIBRATION_MATRIX * Matrix){
  uint32_t Address;

  Address = ADDR_TOUCH_MATRIX_CALIB_INIT;
  SPI_EEPROM_InitWrite((uint8_t *)Matrix,Address,
          sizeof(DRV_ASD7843_CALIBRATION_MATRIX), &TouchWnd_OnSaveCalibrationEnd);

}


void TouchOkBtn_OnRelease(laButtonWidget* btn){
  if (TouchWnd_state == READING_XY || TouchWnd_state == END_CALIBRATION) {
    TouchWnd_state = START_CALIBRATING;
  } else {
    
  }
  
}

void TouchWnd_OnSaveCalibrationEnd( uint16_t nBytes){
  Nop();
}


