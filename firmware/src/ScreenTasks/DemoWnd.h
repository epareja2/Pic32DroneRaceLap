/* 
 * File:   DemoWnd.h
 * Author: epareja
 *
 * Created on 17 de diciembre de 2017, 10:58 AM
 */

#ifndef DEMOWND_H
  #define	DEMOWND_H

/*************************************************************************
 *                   INCLUDES
 *************************************************************************/
#include "gfx/libaria/libaria.h"
//#include "gfx/libaria/inc/libaria_screen.h"



/*************************************************************************
 *                   CONSTANT AND TYPE DEFINITIONS
 *************************************************************************/
typedef enum {
  READY,
  READING_EEPROM,
  WRITING_EEPROM,
} DEMO_STATES;


/*************************************************************************
 *                   FUNNCTION DECLARATIONS
 *************************************************************************/

void DemoWndInitialize(void);

/*********************************************************************
 * @brief Check the DemoWnd State machine
 * @param none
 * @retval None 
 * Overview:        
 * @note            
 *********************************************************************/
void DemoWndTasks(void);

/*********************************************************************
 * @brief This is the callback function for the OnShow Screen
 * @param 
 * @retval None 
 * Overview:        
 * @note            
 *********************************************************************/
void DemoWndOnShow(laScreen* screen);
void DemoWndOnHide(laScreen* screen);
void ReadBtn_ReleasedEvent(laButtonWidget* btn);


/*********************************************************************
 * @brief This is the KeyPad OnClick call back
 * @param 
 * @retval None 
 * Overview:        
 * @note            
 *********************************************************************/
void KeyPadOnClick(laKeyPadWidget* KeyPadObject, laButtonWidget * ButtonObject, 
                   uint32_t row, uint32_t col);



#endif	/* DEMOWND_H */

