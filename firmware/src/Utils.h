/* 
 * File:   Utils.h
 * Author: epare
 *
 * Created on 22 de abril de 2020, 10:38 PM
 */

#ifndef UTILS_H
#define	UTILS_H


#ifdef	__cplusplus
extern "C" {
#endif

  

/*************************************************************************
 *                   INCLUDES
 *************************************************************************/
#include <stdint.h>
#include <stdbool.h>
#include "gfx/libaria/inc/libaria_string.h"

/*************************************************************************
 *                   CONSTANT AND TYPE DEFINITIONS
 *************************************************************************/
  typedef struct {
    uint16_t ms;
    uint8_t seg;
    uint8_t min;
    uint8_t hor;
  } T_TIME;
  
/*********************************************************************
 * @brief Converts a laString to a C ANSI string
 * @param SourceStr : Is a pointer to a laString structure
 *        destStr : is a pointer to the destination uint8_t char 
 * @retval returns the ansi c char in the pointer given by destStr 
 * Overview:        
 * @note            
 *********************************************************************/
void GetCharFrom_laString(laString * souceStr, uint8_t * destStr);
void TicksToTime(uint32_t Ticks, T_TIME * time);
void MsToTime(uint32_t ms, T_TIME * time);


#ifdef	__cplusplus
}
#endif

#endif	/* UTILS_H */

