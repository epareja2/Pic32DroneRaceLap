/* 
 * File:   ConfigRaceLevelsWnd.h
 * Author: epare
 *
 * Created on 10 de abril de 2020, 09:25 AM
 */

#ifndef _CONFIGRACELEVELSWND_H
#define	_CONFIGRACELEVELSWND_H





/*************************************************************************
 *                   INCLUDES
 *************************************************************************/
#include <stdint.h>
#include "app.h"
#include "PilotUnit.h"
#include "gfx/libaria/libaria.h"



/*************************************************************************
 *                   CONSTANT AND TYPE DEFINITIONS
 *************************************************************************/
typedef enum {
  INITIALIZED,
  IDLE,
  GETTING_OFF_LEVEL,
  GETTING_ON_FAR_LEVEL,
  GETTING_MAX_LEVEL,
  CALIBRATION_ENDED,
  GETTING_AVERAGE,
  SAVING_DATA_EEPROM,
  WAIT_SAVING_DATA_EEPROM,
} CONFIG_RACE_LEVEL_STATES;

typedef struct{
  bool  Enabled; // true if the pilot is enabled
  CONFIG_RACE_LEVEL_STATES state;
  CONFIG_RACE_LEVEL_STATES nextState;
  uint16_t offLevelRSSI[MAX_PILOTS];
  uint16_t farLevelRSSI[MAX_PILOTS];
  uint16_t nearLevelRSSI[MAX_PILOTS];
  uint16_t averageRSSI[MAX_PILOTS];
  laProgressBarWidget * BarArray[MAX_PILOTS];
  laLabelWidget * LabelRSSIArray[MAX_PILOTS];
  
} CONFIG_RACE_LEVEL_DATA;



/*************************************************************************
 *                   GLOBAL VARIABLES DEFINITIONS
 *************************************************************************/
CONFIG_RACE_LEVEL_DATA ConfigRaceLevelData;
/*************************************************************************
 *                   FUNNCTION DECLARATIONS
 *************************************************************************/
void ConfigRaceLevelsWndInitialize(void);
void ConfigRaceLevelWnd_OnShow(laScreen* screen);
void ConfigRaceLevelWnd_OnHide(laScreen* screen);


/*********************************************************************
 * @brief Check the DemoWnd State machine
 * @param none
 * @retval None 
 * Overview:        
 * @note            
 *********************************************************************/
void ConfigRaceLevelWndTasks(void);



#endif	/* CONFIGRACELEVELSWND_H */

