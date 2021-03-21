/* 
 * File:   TouchWnd.h
 * Author: epareja
 *
 * Created on 17 de diciembre de 2017, 05:19 PM
 */

#ifndef TOUCHWND_H
  #define	TOUCHWND_H

/*************************************************************************
 *                   INCLUDES
 *************************************************************************/
#include "app.h"
#include "gfx/libaria/libaria.h"


/*************************************************************************
 *                   CONSTANTS AND TYPE DEFINITIOS
 *************************************************************************/
typedef enum {
  READING_XY,
    START_CALIBRATING,
    CALIBRATING,
    END_CALIBRATION,
} TOUCHWND_STATES;

/*************************************************************************
 *                   GLOBAL VARIABLES
 *************************************************************************/
TOUCHWND_STATES TouchWnd_state;


/*************************************************************************
 *                   PUBLIC FUNCTIONS
 *************************************************************************/
void TouchWndTasks(void);
void TouchWndInitialize(void);



#endif	/* TOUCHWND_H */

