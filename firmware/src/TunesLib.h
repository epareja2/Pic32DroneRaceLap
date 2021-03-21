/* 
 * File:   TunesLib.h
 * Author: epare
 *
 * Created on 12 de mayo de 2020, 04:37 PM
 */

#ifndef TUNESLIB_H
#define	TUNESLIB_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "Beep.h"
  
  /********************************************************************
  /*      CONFIGURATION MODULE CONSTANTS
  /*********************************************************************/

  static const uint16_t  TuneArray[69] = {As3, SIL, As3, SIL, As3, 
                                        F4, C5, 
                                        As4, A4, G4, F5, C5, 
                                        As4, A4, G4, F5, C5, 
                                        As4, A4, As4, G4, C4, SIL, C4, SIL , C4, 
                                        F4, C5,
                                        As4, A4, G4, F5, C5, 

                                        As4, A4, G4, F5, C5, 
                                        As4, A4, As4, G4, C4, SIL, C4, 

                                        D4, SIL , D4, As4, A4, G4, F4, SIL,
                                        F4, G4, A4, G4, D4, E4, C4, SIL, C4,
                                        D4, SIL, D4, As4, A4, G4, F4};


static const int16_t   TuneDelay[69] = {  4,	16,	4,	16,	4,
                                          1,  1,  
                                          4,	4,	4,	1,	2,				
                                          4,	4,	4,	1,	2,				
                                          4,	4,	4,	1,	4,	16,	4,	16,	4,

                                          1,	1,							
                                          4,	4,	4,	1,	2,				

                                          4,	4,	4,	1,	2,				
                                          4,	4,	4,	1,	4,	16,	8,		

                                          2,	16,	2,	4,	4,	4,	4,	16,
                                          4,	4,	4,	2,	4,	4,  4,	16,	8,
                                          2,	16,	4,	4,	4,	4,	4};


static const uint16_t  MarioTune[41] = {E4,SIL, E4, SIL, E4, SIL,C4, E4, SIL, G4, SIL, SIL, G3, SIL, SIL, C4, SIL, G3, SIL, E3, SIL, A3, SIL, B3, SIL, As3, A3, SIL,G3,E4,G4,A4,SIL,F4,G4,SIL,E4,SIL,C4,D4,B3};
static const int16_t  MarioDelay[41] = {4, 16, 4,  4,  4,   4,  4,  4,  4,   4 ,  4,   2,   4,  4,   2,  4,  2,  4,   4  ,4,   2,   4,   2,  4,   2,   4,   4,  2,  2, 2, 2,  4, 4, 4, 4 , 4, 4 ,4 , 4, 4 ,4};


static const uint16_t GOTTune[130] = {
G4,	 C4,	 Ds4,	 F4,	 G4,	 C4,	 Ds4,	 F4,
G4,	 C4,	 Ds4,	 F4,	 G4,	 C4,	 Ds4,	 F4,
G4,	 C4,	 E4,	 F4,	 G4,	 C4,	 E4,	 F4,
G4,	 C4,	 E4,	 F4,	 G4,	 C4,	 E4,	 F4,
G4,	 C4,	//5					
							
Ds4,	 F4,	 G4,	 C4,	 Ds4,	 F4,	 //6	
D4,	 //7 and 8						
F4,	 As3,						
Ds4,	 D4,	 F4,	 As3,				
Ds4,	 D4,	 C4,	 //11 and 12				
							
//repeats from 5							
G4,	 C4,	//5					
							
Ds4,	 F4,	 G4,	 C4	, Ds4,	 F4,	 //6	
D4,	 //7 and 8						
F4,	 As3,						
Ds4,	 D4,	 F4,	 As3,				
Ds4,	 D4,	 C4	, //11 and 12				
G4,	 C4	,					
Ds4,	 F4,	 G4,	 C4,	 Ds4,	 F4	,	
							
D4,	//15						
F4,	 As3,						
D4,	 Ds4,	 D4,	 As3,				
C4,							
C5	,						
As4	,						
C4,							
G4	,						
Ds4	,						
Ds4,	 F4,						
G4,							
							
C5,	//28						
As4	,						
C4	,						
G4	,						
Ds4	,						
Ds4,	 D4,						
C5,	 G4,	 Gs4,	 As4,	 C5,	 G4,	 Gs4,	 As4,
C5,	 G4,	 Gs4,	 As4,	 C5,	 G4,	 Gs4,	 As4,
							
SIL,	 Gs5,	 As5,	 C6,	 G5,	 Gs5,	 As5,	
C6,	 G5,	 Gs5,	 As5,	 C6,	 G5,	 Gs5,	 As5,
  
};

static const int16_t GOTDelay[130] = {
8,8,16,16,8,8,16,16,
8,8,16,16,8,8,16,16,
8,8,16,16,8,8,16,16,
8,8,16,16,8,8,16,16,
-4,-4,

16,16,4,4,16,16,
-1,
-4,-4,
16,16,4,-4,
16,16,-1,


-4,-4,

16,16,4,4,16,16,
-1,
-4,-4,
16,16,4,-4,
16,16,-1,
-4,-4,
16,16,4,4,16,16,

-2,
-4,-4,
-8,-8,-8,-8,
-1,
-2,
-2,
-2,
-2,
-2,
-4,-4,
-1,

-2,
-2,
-2,
-2,
-2,
-4,-4,
8,8,16,16,8,8,16,16,
8,8,16,16,8,8,16,16,

4,16,16,8,8,16,16,
8,16,16,16,8,8,16,16
  
};
  /*********************************************************************
  /*      TYPE DEFINITIONS             
  /*********************************************************************/


  /*********************************************************************
  /*            PUBLIC FUNCTION DECLARATIONS                  
  /*********************************************************************/



#ifdef	__cplusplus
}
#endif

#endif	/* TUNESLIB_H */

