/* 
 * File:   ConfigRaceLevelsWnd.h
 * Author: epare
 *
 * Created on 10 de abril de 2020, 09:25 AM
 */

#ifndef _CONFIGRACETHRLEVELSWND_H
#define	_CONFIGRACETHRLEVELSWND_H





/*************************************************************************
 *                   INCLUDES
 *************************************************************************/
#include <stdint.h>
#include "../app.h"
#include "../PilotUnit.h"
#include "gfx/libaria/libaria.h"



/*************************************************************************
 *                   CONSTANT AND TYPE DEFINITIONS
 *************************************************************************/
typedef enum {
  TRH_INITIALIZED,
  TRH_IDLE,
  TRH_SAVING_DATA_EEPROM,
  TRH_SAVE_DONE,
} CONFIG_RACE_THR_LEVEL_STATES;

typedef struct{
  bool  Enabled; // true if the pilot is enabled
  CONFIG_RACE_THR_LEVEL_STATES state;
  uint8_t PilotId;
  
} CONFIG_RACE_THR_LEVEL_DATA;



/*************************************************************************
 *                   GLOBAL VARIABLES DEFINITIONS
 *************************************************************************/
CONFIG_RACE_THR_LEVEL_DATA ConfigRaceThrLevelData;
/*************************************************************************
 *                   FUNNCTION DECLARATIONS
 *************************************************************************/
void ConfigRaceThrLevelsWndInitialize(void);
void ConfigRaceThrLevelWndTasks(void);



#endif	/* CONFIGRACELEVELSWND_H */

