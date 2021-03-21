/* 
 * File:   RaceStartWnd.h
 * Author: epare
 *
 * Created on 18 de mayo de 2020, 09:28 PM
 */

#ifndef RACESTARTWND_H
#define	RACESTARTWND_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>  
#include "gfx/libaria/libaria.h"


  /********************************************************************
  /*      CONFIGURATION MODULE CONSTANTS
  /*********************************************************************/


  /*********************************************************************
  /*      TYPE DEFINITIONS             
  /*********************************************************************/


  /*********************************************************************
  /*            GLOBAL VARIABLE DECLARATIONS                  
  /*********************************************************************/



  /*********************************************************************
  /*            PUBLIC FUNCTION DECLARATIONS                  
  /*********************************************************************/
void RaceStartWnd_OnShow(laScreen* screen);
void RaceStartWnd_OnHide(laScreen* screen);
void RaceStartWnd_Initialize(void);
void RaceStartWnd_LapCompleted(uint8_t PilotId, uint8_t Lap);
void RaceStartWnd_Tasks(void);
void ShowEnablePanelBtn_OnClik(void);


#ifdef	__cplusplus
}
#endif

#endif	/* RACESTARTWND_H */

