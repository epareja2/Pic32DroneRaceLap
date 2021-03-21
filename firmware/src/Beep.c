/*! \file *********************************************************************
 *
 * - File:               Beep.c
 * - Compiler:           MPLABX X32 V2.30  MPLAB 5.3  Harmony 2.06
 * - Supported devices:  
 *
 * \author               Ernesto Pareja  (epare)
 *
 * REVISION HISTORY:
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Author            Date      Comments on that revision
 *----------------------------------------------------------------------
 * Epareja       25 de abril de 2020, 11:05 PM  Creation of file 
 * 
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * ADDITIONAL NOTES:
 *
 *****************************************************************************/



/*********************************************************************
 /*                      INCLUDES        
 /*********************************************************************/
#include <xc.h>
#include <stdint.h>

#include "app.h"
#include "driver/tmr/drv_tmr_static.h"
#include "Utils.h"
#include "Beep.h"




/*********************************************************************
 /*                      GLOBAL VARIABLES        
 /*********************************************************************/


/*********************************************************************
 /*                      LOCAL CONSTANT DEFINITIONS
 /*********************************************************************/

/*********************************************************************
 /*                      PRIVATE FUNCTION DECLARATIONS        
 /*********************************************************************/


/*********************************************************************
 /*                      CODE IMPLEMENTATION        
 /*********************************************************************/


/*********************************************************************
 * @brief 
 * @param 
 * @returns  None 
 * Overview:        
 * @note            
 *********************************************************************/
void BeepInitialize(void){
  beepData.BeepTimer = 0;
  beepData.beepActive = false;
  beepData.TuneIndex = 0;
  TRISDbits.TRISD4 = 0;
  LATDbits.LATD4 = 0; // Apaga el buzzer para que no consuma energía.
}

/*********************************************************************
 * @brief void BeepTasks (void)
 * @param none
 * @returns  None 
 * Overview:        
 * @note      Esta función debe ser llamada en la ISR de la base de tiempo      
 *********************************************************************/
void BeepTasks (void){
  if (beepData.BeepTimer > 0){
    beepData.BeepTimer--;
  } else {
    if ((beepData.beepActive == true) && (beepData.TuneIndex < beepData.Tune.Lenght)) {
      Beep(beepData.Tune.Tune[beepData.TuneIndex],beepData.Tune.Delay[beepData.TuneIndex]);
      beepData.TuneIndex++;
    } else {
      beepData.TuneIndex = 0;
      beepData.beepActive = false;
      BeepOff();
    }
  }
  
}

/*********************************************************************
 * @brief Reproduce un tono en Hz por un tiempo especificado en ms o en divisor de nota musical
 * @param[in] uint16_t freq : This is expressed in Hz and is the tone to be produced
 * @param[in] uint16_t duration: it may be expressed as Note Time Divider 
 *                     (Redonda = 1, blanca = 2, negra=4, corchea=8 , Semicorchea=16, Fusa=32, Semifusa=64)
 *                      If this duration is grater than MAX_TUNE_NOTE_DIVIDER, it will represent the time
 *                      in ms that the sound will last. 
 * @retval None 
 * Overview:        
 * @note      Beep(D4, 500); // Plays D4 note for 500ms
 *            Beep(3400, 1000); //Plays 3400 hz for 1sec
 *********************************************************************/
void Beep(uint16_t freq, int16_t duration){
  uint16_t  TmrValue;
  
  if (freq == SIL) {
    DRV_TMR1_Stop(); // Doesn't play any sound until next Beep call.
  } else {
    if (freq < MIN_FRECUENCY) {
        freq = MIN_FRECUENCY; // Assign the minimum freq for the actual clock configuration
     }
    // se calcula con (2 x freq) porque a la interrupción se cambia de flanco.
    /*TODO*/ // Cambiar el 16 por el preescaler automáticamente
    TmrValue = (uint16_t) (SYS_CLK_SystemFrequencyGet() / (2*freq * 16.0));
    DRV_TMR1_PeriodValueSet(TmrValue);
    DRV_TMR1_Start();
  }
  if (duration > 0){ // Normal note
    if (duration <= MAX_TUNE_NOTE_DIVIDER) {
      beepData.BeepTimer = (uint16_t)(beepData.Tempo / duration);
    } else { // expressed duration in ms
      beepData.BeepTimer = duration; // if the time is expressed as ms goes directly to the controlling variable
    }

  } else { // dotted notes last 50% more time.
    beepData.BeepTimer = (uint16_t)((beepData.Tempo * 1.5 / abs(duration)) );
  }

}



/*********************************************************************
 * @brief void BeepOff(void)
 * @param 
 * @retval None 
 * Overview: Stop the sound frecuency generator        
 * @note            
 *********************************************************************/
void BeepOff(void){
  DRV_TMR1_Stop();
  LATDbits.LATD4 = 0; // Apaga el buzzer para que no consuma energía.
}

/*********************************************************************
 * @brief Plays a Tune passed as parameters that are stored in eeprom or ram
 * @param[in] MelodyData is pointer to an array of uint16_t that has the frecuency to be played
 * @param[in] TimeData is pointer to an array of int16_t that has the time each note will be played
 * @param[in] Len : The array dimension of the tune that will be played
 * @param[in] Tempo:  is the time base for the song. If lower, the song will be played faster. Expressed in ms for a Round note
 * @param[in] Repeat: true if the song will be repited (this has to be completed)
 * @retval None 
 * Overview:        
 * @note            
 * 
 * @exam 
 * static const uint16_t  TuneArray[3] = {C3, D3, E3 };
 * static const uint16_t   TuneDelay[3] = {2, 4,  8};
 * PlayTune(&TuneArray[0], &TuneDelay[0], sizeof(TuneArray)/sizeof (uint16_t), 500, false); 
 *********************************************************************/
void PlayTune(const uint16_t * MelodyData, const int16_t * TimeData, uint16_t Len, uint16_t Tempo, bool Repeat){
  beepData.TuneIndex = 0;
  beepData.beepActive=true;
  beepData.Tune.Tune = MelodyData;
  beepData.Tune.Delay = TimeData;
  beepData.Tune.Lenght  = Len;
  beepData.Tempo = Tempo;
  beepData.Repeat = Repeat;
}