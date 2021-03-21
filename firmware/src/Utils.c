/* ************************************************************************** */
/** Utils.c

  @Company
    Ernesto Pareja

  @File Name
    Utils.c

  @Summary
    Generic functions utility

  @Description
    
 */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */
#include <stdint.h>
#include <stdbool.h>
#include "Utils.h"
#include "app.h"

/* ************************************************************************** */
/* GLOBAL UNIT VARIABLES
/* ************************************************************************** */


/* ************************************************************************** */
/* LOCAL DEFINITIONS
/* ************************************************************************** */


/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */

/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */


/*********************************************************************
 * @brief Converts a laString to a C ANSI string
 * @param SourceStr : Is a pointer to a laString structure
 *        destStr : is a pointer to the destination uint8_t char 
 * @retval returns the ansi c char in the pointer given by destStr 
 * Overview:        
 * @note            
 *********************************************************************/
void GetCharFrom_laString(laString * souceStr, uint8_t * destStr){
  uint8_t Index = 0;

  if (souceStr->data != NULL) {
    while (souceStr->data[Index] != 0) {
      destStr[Index] = (uint8_t) (souceStr->data[Index]);
      Index++;
    };
    destStr[Index]='\0'; // Terminates with null character
  } else {
    destStr[0]='\0'; 
  }
  
}


/*********************************************************************
 * @brief 
 * @param 
 * @retval None 
 * @exam      
 * @note            
 *********************************************************************/
void TicksToTime(uint32_t Ticks, T_TIME * time){
  time->ms = Ticks / (uint32_t)(_1mSEG_TICKS);
  time->seg = ( time->ms / 1000) % 1000;
  time->min = (uint8_t) (time->seg / 60);
  //  time->ms = Ticks  % 1000;
//  time->ms = ((uint32_t)(Ticks / _1mSEG_TICKS)) % 1000;
//  time->seg = ((uint16_t )(time->ms / 1000)) % 60;
//  time->min = (uint8_t)(time->seg / 60);
}


/*********************************************************************
 * @brief Convierte los ms en formato T_TIME
 * @param 
 * @retval None 
 * @exam      
 * @note            
 *********************************************************************/
void MsToTime(uint32_t ms, T_TIME * time){
  uint16_t  temp_seg;
  uint16_t  temp_min;
  uint16_t  temp_hor;
    
  time->ms = ms % 1000;
  temp_seg = ms / 1000;
  time->seg = temp_seg % 60;
  temp_min = (temp_seg / 60);
  time->min = (uint8_t)(temp_min) % 60;
  temp_hor = temp_min / 60;
  time->hor = (uint8_t)(temp_hor) % 60;
}