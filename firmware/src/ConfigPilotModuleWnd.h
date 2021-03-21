/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

#ifndef _CONFIG_PILOT_MODULE_WND_H    /* Guard against multiple inclusion */
#define _CONFIG_PILOT_MODULE_WND_H

/*************************************************************************
 *                   INCLUDES
 *************************************************************************/
#include "gfx/libaria/libaria.h"
//#include "gfx/libaria/inc/libaria_screen.h"



/*************************************************************************
 *                   CONSTANT AND TYPE DEFINITIONS
 *************************************************************************/
typedef enum {
  RUNNING,
  LOADING_SCREEN_DATA,
    LOADING_DROPDOWN,
} CONFIG_PILOT_STATES;


typedef struct{
  CONFIG_PILOT_STATES state;
  
  uint8_t PilotModule; // rx5808 id module
  uint8_t Band;
  uint8_t Channel;
  
  
} CONFIG_PILOT_WND;


/*************************************************************************
 *                   GLOBAL VARIABLES DEFINITIONS
 *************************************************************************/
CONFIG_PILOT_WND ConfigPilotData; //

/*************************************************************************
 *                   FUNNCTION DECLARATIONS
 *************************************************************************/


/*********************************************************************
 * @brief 
 * @param none
 * @retval None 
 * Overview:        
 * @note            
 *********************************************************************/
void ConfigPilotModuleTasks(void);


 
#endif /* _CONFIG_PILOT_MODULE_WND_H */

/* *****************************************************************************
 End of File
 */
