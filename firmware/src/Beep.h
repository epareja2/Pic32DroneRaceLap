/* 
 * File:   Beep.h
 * Author: epare
 *
 * Created on 25 de abril de 2020, 11:06 PM
 */

#ifndef BEEP_H
#define	BEEP_H

#include <stdint.h>



  /********************************************************************
/*      CONFIGURATION MODULE CONSTANTS
/*********************************************************************/

// Frecuency in Hz of each tone
#define TUNE_TIME_BASE  1000 // ms that correspond to a Black note
#define MIN_FRECUENCY   120
#define MAX_TUNE_NOTE_DIVIDER 64 // MAX note time divider possible - Semifuse

#define SIL    0
#define C3    131
#define Cs3   139
#define D3    147
#define Ds3   156
#define E3    165
#define F3    175
#define Fs3   185
#define G3    196
#define Gs3   208
#define A3    220
#define As3   233
#define B3    247

#define C4    262
#define Cs4   277
#define D4    294
#define Ds4   311
#define E4    330
#define F4    349
#define Fs4   370
#define G4    392
#define Gs4   415
#define A4    440
#define As4   466
#define B4    494

#define C5    523
#define Cs5   554
#define D5    587
#define Ds5   622
#define E5    659
#define F5    698
#define Fs5   740
#define G5    784
#define Gs5   831
#define A5    880
#define As5   932
#define B5    988

#define C6    1046
#define Cs6   1109
#define D6    1175
#define Ds6   1245
#define E6    1319
#define F6    1397
#define Fs6   1480
#define G6    1568
#define Gs6   1661
#define A6    1760
#define As6   1865
#define B6    1976

typedef struct {
  uint16_t * Tune;
  int16_t * Delay; // May accept negative values when playing music dotted notes that represent 50% more time
  uint16_t Lenght;
} T_TUNE;

/*********************************************************************
/*      TYPE DEFINITIONS             
/*********************************************************************/
typedef struct {
  bool     beepActive;
  uint16_t BeepTimer;
  T_TUNE   Tune;
  uint16_t Tempo;
  uint8_t  TuneIndex; 
  bool     Repeat;
} T_BEEP_DATA;

/*********************************************************************
/*      GLOBAL VARIABLES
/*********************************************************************/
T_BEEP_DATA beepData;


  /*********************************************************************
  /*            PUBLIC FUNCTION DECLARATIONS                  
  /*********************************************************************/
void BeepInitialize(void);
void Beep(uint16_t freq, int16_t duration);
void BeepOff(void);
void BeepTasks (void);
//void PlayTune(uint16_t * MelodyData, int16_t * TimeData, uint16_t Len, uint16_t Tempo, bool Repeat);
void PlayTune(const uint16_t * MelodyData, const int16_t * TimeData, uint16_t Len, uint16_t Tempo, bool Repeat);




#endif	/* BEEP_H */

