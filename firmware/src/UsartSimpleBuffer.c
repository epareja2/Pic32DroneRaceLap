/*********************************************************************
 *
 *             Microchip XC32 Firmware -  HID Version 1.0
 *
 *********************************************************************
 * FileName:        UsartSimpleBuffer.c
 * Dependencies:    must have the USART Handle
 * Processor:       PIC32MX  - PIC32MZ
 * Compiler:        xc32 2.40 +
 * Company:         Ernesto Pareja J.
 *
 *
 * Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Ernesto Pareja J     2 Marzo 2020    Original.
 ********************************************************************/

/***********************  I N C L U D E S ************************************/
#include <stdint.h>
#include "usart/drv_usart.h"
#include "usart/drv_usart_definitions.h"
#include "UsartSimpleBuffer.h"


/*********************** I M P L E M E N T A T I O N**************************/


  /*********************************************************************
   * Function:        void NewFunction(void)
   * PreCondition:    None
   * Input:           None
   * Output:          None
   * Side Effects:    None
   * Overview:        None
   * Note:            None
   ********************************************************************/
void usartInitBuffer(USART_SIMPLE_BUFF * buff){
  buff->firstIndex = 0;
  buff->lastIndex = 0;
  buff->Locked = false;
}


/*********************************************************************
 ********************************************************************/
void usartSetBufferRxCallBack(USART_SIMPLE_BUFF * buff, void * CallBack){
  if (CallBack != NULL) {
    buff->EndBufferRxCallback = CallBack;
  }
}

/*********************************************************************
 ********************************************************************/
uint8_t usartAddByte(USART_SIMPLE_BUFF * buff, uint8_t Data){
  uint8_t lastIndex;
  lastIndex = buff->lastIndex;
  if ( lastIndex < MAX_BUFFER_SIZE) {
    buff->Buff[lastIndex] = Data;
    buff->lastIndex++;
    if ((buff->Buff[lastIndex-1] == buff->pattern[0]) && (Data == buff->pattern[1])) {
      buff->EndBufferRxCallback((uint8_t)lastIndex);
    }
    return true;
  } else {
    return false;
  }
}

/*********************************************************************
********************************************************************/
uint8_t usartGetByte(USART_SIMPLE_BUFF * buff) {
  uint8_t result = 0xFF;
  if (buff->firstIndex < buff->lastIndex) {
    result = buff->Buff[buff->firstIndex];
    buff->firstIndex++;
  }
  return result;
}

/*********************************************************************
********************************************************************/
uint8_t usartGetBuffSize(USART_SIMPLE_BUFF * buff){
  uint8_t result;
  result = buff->lastIndex - buff->firstIndex ;
  return result;
}


  