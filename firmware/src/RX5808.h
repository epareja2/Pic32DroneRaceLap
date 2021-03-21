/* 
 * File:   RX5808.h
 * Author: epare
 *
 * Created on 23 de marzo de 2020, 09:27 PM
 */

#ifndef RX5808_H
  #define	RX5808_H

#include <stdint.h>
#include <stdbool.h>
#include "system_config/Graphic32MX795/framework/driver/adc/drv_adc_static.h"

/*********************************************************************
/*      CONFIGURATION MODULE CONSTANTS
/*********************************************************************/
#define MAX_BANDS 6
#define MAX_VTX_CHANNELS  8 //Número de canales en cada banda
#define MAX_PILOTS 4 // Máximo número de pilotos en este módulo
#define NUM_ADC_SAMPLES   16   // Num of AD Samples to average
#define ADC_SAMPLES_DIVIDER 4 // Num of bit positions to make a division by 16

// hardware definitions
#define RX5808_DATA_PIN       LATBbits.LATB9
#define RX5808_DATA_TRIS_PIN  TRISBbits.TRISB9
#define RX5808_DATA_IN        PORTBbits.RB9

#define RX5808_SCK_PIN        LATBbits.LATB11
#define RX5808_SCK_TRIS_PIN   TRISBbits.TRISB11

#define RX5808_CS0            LATBbits.LATB5
#define RX5808_CS1            LATBbits.LATB4
#define RX5808_CS2            LATBbits.LATB13
#define RX5808_CS3            LATBbits.LATB15

#define RX5808_CS0_TRIS       TRISBbits.TRISB5
#define RX5808_CS1_TRIS       TRISBbits.TRISB4
#define RX5808_CS2_TRIS       TRISBbits.TRISB13
#define RX5808_CS3_TRIS       TRISBbits.TRISB15

/*********************************************************************
/*      TYPE DEFINITIONS             
/*********************************************************************/
  
typedef enum  {
  RX5808_IDLE,
  RX5808_SENDING_FREQ,
  RX5808_FREQ_READY,
  RX5808_READING_RSSI,
  RX5808_READING_CHANNEL,
  RX5808_RSSI_READY,
  RX5808_ERROR,
} RX5808_STATES;



typedef struct {
  RX5808_STATES state;
  uint16_t RSSI[MAX_PILOTS];
  uint8_t ModuleIndex;
  bool  SampleReady;
} RX5808_DATA;

 


/*********************************************************************
/*      GLOBAL  VARIABLES
/*********************************************************************/
RX5808_DATA rx5808_data;

  

// Channels to send to the SPI registers
static const uint16_t channelTable[]  = {
    // Channel 1 - 8
    0x2A05, 0x299B, 0x2991, 0x2987, 0x291D, 0x2913, 0x2909, 0x289F, // Band A
    0x2903, 0x290C, 0x2916, 0x291F, 0x2989, 0x2992, 0x299C, 0x2A06, // Band B
    0x2895, 0x288B, 0x2881, 0x2817, 0x2A0F, 0x2A19, 0x2A83, 0x2A8D, // Band E
    0x2906, 0x2910, 0x291A, 0x2984, 0x298E, 0x2998, 0x2A02, 0x2A0C, // Band F / Airwave
    0x281D, 0x288F, 0x2902, 0x2914, 0x2987, 0x2999, 0x2A0C, 0x2A1E, // Raceband
    0x2609, 0x261C, 0x268E, 0x2701, 0x2713, 0x2786, 0x2798, 0x280B, // Band D / 5.3
};

// Channels' MHz Values. Just for reference. Not used in code.
//
static  const uint16_t channelFreqTable[] = {
//     // Channel 1 - 8
     5865, 5845, 5825, 5805, 5785, 5765, 5745, 5725, // Band A
     5733, 5752, 5771, 5790, 5809, 5828, 5847, 5866, // Band B
     5705, 5685, 5665, 5645, 5885, 5905, 5925, 5945, // Band E
     5740, 5760, 5780, 5800, 5820, 5840, 5860, 5880, // Band F / Airwave (F8=5880 se borra para que no se confunda con R7)
     5658, 5695, 5732, 5769, 5806, 5843, 5880, 5917, // Raceband
     5362, 5399, 5436, 5473, 5510, 5547, 5584, 5621, // Band D / 5.3
 };

static const uint8_t BandCode [MAX_BANDS] ={ 'A', 'B', 'E', 'F', 'R', 'D'};

/*********************************************************************
/*            PUBLIC FUNCTION DECLARATIONS                  
/*********************************************************************/
void RX5808_Setup(void);
void RX5808_SetChannel(uint8_t Module, uint8_t Band, uint8_t Channel);
uint32_t RX5808_GetChannel(uint8_t Module);
void RX5808_StartScanRSSI(void);
void RX5808_SampleReady(void);
RX5808_STATES RX5808_GetState();
void RX5808_SetState(RX5808_STATES state);
uint16_t RX5808_GetRSSIData(uint8_t Module);
uint16_t RX_5808_CalcFrequencyData( uint16_t frequency );
uint16_t RX5808_GetFreqGHZ(uint8_t Band, uint8_t Channel);
void RX5808_GetBandChannel(uint16_t RegData, uint8_t * Band, uint8_t * Channel);
uint32_t RX5808_GetRegister(uint8_t Register, uint8_t Module);
void RX5808_SetRegister(uint8_t Register, uint32_t Value ,uint8_t Module);






#endif	/* RX5808_H */

