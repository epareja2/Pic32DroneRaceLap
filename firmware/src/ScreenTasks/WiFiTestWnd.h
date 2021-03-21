/* 
 * File:   WiFiTestWnd.h
 * Author: epare
 *
 * Created on 17 de junio de 2020, 05:49 PM
 */

#ifndef WIFITESTWND_H
#define	WIFITESTWND_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>  

/********************************************************************
/*      CONFIGURATION MODULE CONSTANTS
/*********************************************************************/


/*********************************************************************
/*      TYPE DEFINITIONS             
/*********************************************************************/
//const uint8_t * AT_Commands[6] = {"AT", "AT+RST", "AT+", "FAIL", "no change", "Linked", "Unlink"};

/*********************************************************************
/*            GLOBAL VARIABLE DECLARATIONS                  
/*********************************************************************/



/*********************************************************************
/*            PUBLIC FUNCTION DECLARATIONS                  
/*********************************************************************/
void WiFiTestWnd_Initialize(void);
void WiFiTestWnd_Tasks(void);


#ifdef	__cplusplus
}
#endif

#endif	/* WIFITESTWND_H */

