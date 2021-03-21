/*! \file *********************************************************************
 *
 * \brief "DESCRIPCION DEL MODULO".
 *
 * "DESCRIPCION MAS AMPLIA"
 *
 * - File:               DemoWnd.c
 * - Compiler:           MPLABX 
 * - Supported devices:  
 *
 * \author               Ernesto Pareja  (epareja)
 *
 * REVISION HISTORY:
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Author            Date      Comments on that revision
 *----------------------------------------------------------------------
 * Epareja       17 de diciembre de 2017, 10:59 AM  Creation of file
 * 
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * ADDITIONAL NOTES:
 *
 *****************************************************************************/



/*********************************************************************
 /*                      INCLUDES        
 /*********************************************************************/
#include "DemoWnd.h"
#include "app.h"
#include "driver/eeprom/SPI_EEprom_Drv.h"
#include "gfx/libaria/inc/libaria_utils.h"

/*********************************************************************
 /*                      GLOBAL VARIABLES        
 /*********************************************************************/
DEMO_STATES DemoState;
uint8_t Data[20];  // Variable para almacenar buffer de lectura y escritura a EEPROM

/*********************************************************************
 /*                      PRIVATE FUNCTION DECLARATIONS        
 /*********************************************************************/
void ReadBtn_ReleasedEvent(laButtonWidget* btn);
void DemoReadEEPromOnEnd(uint16_t nReadBytes );
void DemoWriteEEPromOnEnd(uint16_t nReadBytes );
void AddressEditOnFocus(laWidget* widget);
  

/*********************************************************************
 /*                      CODE IMPLEMENTATION        
 /*********************************************************************/

void DemoWndInitialize(void){
  laScreen* screen;
  DemoState = READY;
  screen = (laScreen*)laContext_GetActive()->screenList.values[DemoWnd_ID];
  laScreen_SetShowEventCallback(screen, &DemoWndOnShow); // Set CallBack function
  laScreen_SetHideEventCallback(screen,&DemoWndOnHide);
}

/*********************************************************************
 * @brief Check the DemoWnd State machine
 * @param none
 * @retval None 
 * Overview:        
 * @note            
 *********************************************************************/
void DemoWndTasks(void){
  switch (DemoState) {
    case READY: {
      
      break;
    }
    case READING_EEPROM: {
      
      break;
    }
    
    default : {
      
    }
  }
}

/*********************************************************************
 * @brief This is the callback function for the OnShow Screen
 * @param 
 * @retval None 
 * Overview:        
 * @note            
 *********************************************************************/
void DemoWndOnShow(laScreen* screen) {
  laButtonWidget_SetReleasedEventCallback(ReadBtn, &ReadBtn_ReleasedEvent);
  laContext_SetEditWidget((laWidget*)DataEdit);
  laEditWidget_StartEdit();
//  SPI_EEPROM_SetCallBack(&DemoWriteEEPromOnEnd, &DemoReadEEPromOnEnd);

  if (laKeyPadWidget_SetKeyClickEventCallback(NumKeyPadWidget, &KeyPadOnClick) == LA_SUCCESS) {
    Nop(); // Just for testing and debuging
  } else {
    Nop();
  }
}

/*********************************************************************
 * @brief This is the callback function for the OnHide Screen
 * @param 
 * @retval None 
 * Overview:        
 * @note            
 *********************************************************************/
void DemoWndOnHide(laScreen* screen){
  SPI_EEPROM_SetCallBack(NULL ,NULL);
  
}

/*********************************************************************
 * @brief This is the KeyPad OnClick call back
 * @param 
 * @retval None 
 * Overview:        
 * @note            
 *********************************************************************/
void KeyPadOnClick(laKeyPadWidget* KeyPadObject, laButtonWidget * ButtonObject, 
                   uint32_t row, uint32_t col) 
{
  laString str;
  
  if (row == 2 && col == 3){
    
  } else if (row == 3 && col == 3) {
    
  }
  Nop();
  
  
}


/*********************************************************************
 * @brief 
 * @param 
 * @retval None 
 * Overview:        
 * @note            
 *********************************************************************/
void ReadBtn_ReleasedEvent(laButtonWidget* btn){
  uint32_t Address;
  
  SPI_EEPROM_InitRead(&Data[0],0,13,&DemoReadEEPromOnEnd);
}

/*********************************************************************
 * @brief 
 * @param 
 * @retval None 
 * Overview:        
 * @note            
 *********************************************************************/
void  DemoReadEEPromOnEnd( uint16_t nReadBytes ){
  laString str;
  
//  str = laString_CreateFromCharBuffer(Data,GFXU_StringFontIndexLookup(&stringTable, string_BaudLbl, 0));
  str = laString_CreateFromCharBuffer(Data,&Calibri_14);
  laTextFieldWidget_SetText(AddressEdit,str);
  laString_Destroy(&str);
}


/*********************************************************************
 * @brief 
 * @param 
 * @retval None 
 * Overview:        
 * @note            
 *********************************************************************/
void DemoWriteEEPromOnEnd(uint16_t nReadBytes ){
  
}


/*********************************************************************
 * @brief 
 * @param 
 * @retval None 
 * Overview:        
 * @note            
 *********************************************************************/
  
void AddressEditOnFocus(laWidget* widget){
  
}



