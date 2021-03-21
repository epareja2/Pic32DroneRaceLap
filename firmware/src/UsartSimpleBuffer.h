/* 
 * File:   UsarSimpleBuffer.h
 * Author: epareja
 *
 * Created on 2 de marzo de 2020, 07:47 PM
 */

#ifndef USARSIMPLEBUFFER_H
#define	USARSIMPLEBUFFER_H

#ifdef	__cplusplus
extern "C" {
#endif

#define MAX_BUFFER_SIZE   64    // MAXIMUM BUFFER SIZE

  typedef enum {
    RX_BUFFER_TYPE,
    TX_BUFFER_TYPE,
  } BUFFER_TYPE;
  
typedef struct {
  uint8_t Buff[MAX_BUFFER_SIZE];
  uint8_t firstIndex;
  uint8_t lastIndex;
  uint8_t Locked;
  uint8_t lastByte;
  uint8_t pattern[2];
  uint32_t timeStamp; // Para detectar timeouts
  BUFFER_TYPE type;
  /* Callback function for end of Read operation  */
  void  (*EndBufferRxCallback) ( uint8_t nReadBytes );
} USART_SIMPLE_BUFF;


/*********************************************************************
 ********************************************************************/
void usartInitBuffer(USART_SIMPLE_BUFF * buff);
void usartSetBufferRxCallBack(USART_SIMPLE_BUFF * buff, void * CallBack);
uint8_t usartAddByte(USART_SIMPLE_BUFF * buff, uint8_t Data);
uint8_t usartBuffGetSize(USART_SIMPLE_BUFF * buff);
uint8_t usartGetByte(USART_SIMPLE_BUFF * buff);
uint8_t usartGetBuffSize(USART_SIMPLE_BUFF * buff);


#ifdef	__cplusplus
}
#endif

#endif	/* USARSIMPLEBUFFER_H */

