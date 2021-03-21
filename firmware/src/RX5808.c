/*! \file *********************************************************************
 *
 * - File:               RX5808.c
 * - Compiler:           MPLABX X32 V2.30  MPLAB 5.3  Harmony 2.06
 * - Supported devices:  
 *
 * \author               Ernesto Pareja  (epareja)
 *
 * REVISION HISTORY:
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Author            Date      Comments on that revision
 *----------------------------------------------------------------------
 * Epareja       24 de marzo de 2020, 11:33 PM  Creation of file (Inicio de cuarentena Coronavirus)
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
#include "peripheral/adc/plib_adc.h"
#include "peripheral/int/plib_int.h"
#include <stdint.h>
#include "RX5808.h"
#include "system/debug/sys_debug.h"
#include "system/common/sys_common.h"
#include "PilotUnit.h"





/*********************************************************************
 /*                      GLOBAL VARIABLES        
 /*********************************************************************/
uint16_t  AverageRSSI[MAX_PILOTS]; // Vector for calculating RSSI average
uint8_t sampleIndex; 

/*********************************************************************
 /*                      LOCAL CONSTANT DEFINITIONS
 /*********************************************************************/

/*********************************************************************
 /*                      PRIVATE FUNCTION DECLARATIONS        
 /*********************************************************************/
void _RX5808_SendOne(void);
void _RX5808_SendZero(void);

/*********************************************************************
 /*                      CODE IMPLEMENTATION        
 /*********************************************************************/



/*********************************************************************
 * @brief void ShortDelay(UINT32 DelayCount)
 * @param DelayCount: Número de clicks del Core Timer que se van a tener en delay
 * @retval None 
 * Overview:        
 * @note  
 ********************************************************************/
void DelayUs(uint32_t us) {                  // Delay Time (CoreTimer Ticks)
  uint32_t start = _CP0_GET_COUNT();
  uint32_t end = start + SYS_CLK_SystemFrequencyGet() / 1000000 / 2 * us;
  if (end > start) {
    while (_CP0_GET_COUNT() < end);
  } else {
    while (_CP0_GET_COUNT() > start || _CP0_GET_COUNT() < end);
  }

}

RX5808_STATES RX5808_GetState(){
  return rx5808_data.state;
}

void RX5808_SetState(RX5808_STATES state){
  rx5808_data.state = state;
}

uint16_t  RX5808_GetRSSIData(uint8_t Module){
  return rx5808_data.RSSI[Module];
}


/***************************************************************
 *  This function is called when an ADC interrupt is fired
 *  and it acumulates NUM_ADC_SAMPLES samples of each of 
 *  the 4 ADC inputs that are read in each interrupt.
 *  When the num of samples is reached then it stores the 
 *  average value in the RSSI register
 * ************************************************************** */
void  _RSSI_Average(void){
  uint8_t i;
  uint16_t  ADCvalue;
  for (i=0; i<MAX_PILOTS ; i++){
    ADCvalue = DRV_ADC_SamplesRead(i);
    AverageRSSI[i] += ADCvalue;
  }
  sampleIndex++;
  if (sampleIndex >= NUM_ADC_SAMPLES) {
    sampleIndex = 0;
    for (i = 0; i < MAX_PILOTS; i++) {
      rx5808_data.RSSI[i] = AverageRSSI[i]  >> ADC_SAMPLES_DIVIDER;
      AverageRSSI[i]=0;
    }
  }
}

/*********************************************************************
 * @brief void RX5808_Tasks(void);
 * @param 
 * @retval None 
 * Overview:        
 * @note  Tasks routine
 ********************************************************************/
void RX5808_Tasks(void){
  switch (rx5808_data.state){
    case RX5808_IDLE: break;
    case RX5808_READING_RSSI: {
      break;
    }
    case RX5808_FREQ_READY: break;
    case RX5808_SENDING_FREQ: break;
    case RX5808_RSSI_READY :{
      Nop();
      break;
    }
    
    
  }
}

/*********************************************************************
 * @brief 
 * @param 
 * @retval None 
 * Overview:        
 * @note  
 ********************************************************************/
void RX5808_StartScanRSSI(void){
  rx5808_data.state = RX5808_READING_RSSI;
  rx5808_data.ModuleIndex = 0;
  
//  PLIB_ADC_SamplingStart(ADC_ID_1);         
  DRV_ADC_Start();
  
}

/*********************************************************************
 * @brief 
 * @param 
 * @retval None 
 * Overview:        
 * @note  
 ********************************************************************/
void RX5808_SampleReady(void){
  
  rx5808_data.SampleReady = true;
  _RSSI_Average();
//  rx5808_data.RSSI[0] =  ADC1BUF0;
//  rx5808_data.RSSI[1] =  ADC1BUF1;
//  rx5808_data.RSSI[2] =  ADC1BUF2;
//  rx5808_data.RSSI[3] =  ADC1BUF3;
  rx5808_data.state = RX5808_RSSI_READY;
//  DRV_ADC_Stop();
}


/*********************************************************************
 * @brief void SPI_EEPROM_SetCallBack((void*)OnWriteEnd , (void *) OnReadEnd);
 * @param 
 * @retval None 
 * Overview:        
 * @note  Callback functions to get the SPI events ONStart and ONEnd
 ********************************************************************/
void RX5808_Setup(void){
  uint16_t i;
  for (i = 0; i < MAX_PILOTS; i++) {
   rx5808_data.RSSI[i]=0;
   AverageRSSI[i]=0;
  }

  sampleIndex = 0;
  rx5808_data.ModuleIndex = 0;
  rx5808_data.state = RX5808_IDLE;
  
  RX5808_CS0 = 1;
  RX5808_CS1 = 1;
  RX5808_CS2 = 1;
  RX5808_CS3 = 1;
  RX5808_SCK_PIN = 0;
  RX5808_DATA_PIN = 0;
  RX5808_CS0_TRIS  = 0;
  RX5808_CS1_TRIS  = 0;
  RX5808_CS2_TRIS  = 0;
  RX5808_CS3_TRIS  = 0;
  RX5808_DATA_TRIS_PIN =0;
  RX5808_SCK_TRIS_PIN = 0;
  DRV_ADC_Open();
  
  //PowerDown the Video and Audio of the modules
  RX5808_SetRegister(0xA,0xD0DF3,0);
  RX5808_SetRegister(0xA,0xD0DF3,1);
  RX5808_SetRegister(0xA,0xD0DF3,2);
  RX5808_SetRegister(0xA,0xD0DF3,3);
  
}

void _RX5808_SendOne(void){
  RX5808_DATA_PIN = 1;
  DelayUs(1);
  RX5808_SCK_PIN=1;
  DelayUs(1);
  RX5808_SCK_PIN=0;
}

void _RX5808_SendZero(void){
  RX5808_DATA_PIN = 0;
  DelayUs(1);
  RX5808_SCK_PIN=1;
  DelayUs(1);
  RX5808_SCK_PIN=0;
}

/* ***************************************************************************************
 * Gets the frecuency in GHZ according to a given band and Channel passed as a parameter
 * ****************************************************************************************/
uint16_t RX5808_GetFreqGHZ(uint8_t Band, uint8_t Channel){
  uint8_t ChIndex;
  if ( (Band < MAX_BANDS) && (Channel < 8)) {
    ChIndex = (Band<<3) + Channel;
  } else
    ChIndex = 0;
  return channelFreqTable[ChIndex];
  
}


/* ***************************************************************************************
// when sending the R/W bit and the SCK is down, the data is inmediatly driven out the pin
// so when reading the data bit in the loop will read inmediatly the bit and after rise and
// fall the SCK pin. The shift register of the RX5808 is moved in the falling edge of SCK pin
 ****************************************************************************************/
uint8_t _RX5808_ReadBit(void){
  uint8_t value;
  DelayUs(1);
  value = RX5808_DATA_IN;
  RX5808_SCK_PIN=1;
  DelayUs(1);
  RX5808_SCK_PIN=0;
  DelayUs(1);
  return value;
}

/*********************************************************************
 * @brief 
 * @param 
 * @retval None 
 * Overview:        
 * @note  
 *    
     Sends SPI command to receiver module to change frequency.
    
     Format is LSB first, with the following bits in order:
         4 bits - address
         1 bit  - read/write enable
        20 bits - data
    
     Address for frequency select (Synth Register B) is 0x1
     Expected data is (LSB):
         7 bits - A counter divider ratio
          1 bit - seperator
        12 bits - N counter divder ratio
    
     Forumla for calculating N and A is:/
        F_lo = 2 * (N * 32 + A) * (F_osc / R)
        where:
            F_osc = 8 Mhz
            R = 8
    
     Refer to RTC6715 datasheet for further details.
    
 ********************************************************************/
void RX5808_SetChannel(uint8_t Module, uint8_t Band, uint8_t Channel){
  uint8_t i;
  uint32_t ChannelValue;
  uint8_t index;
  
  index = (Band << 3) | Channel; // Band * 8 + Channel
  ChannelValue = channelTable[index];
  
  RX5808_SetRegister(0x01, ChannelValue,Module);

}

//******************************************************************************
//* function: calcFrequencyData
//*         : calculates the frequency value for the syntheziser register B of
//*         : the RTC6751 circuit that is used within the RX5808/RX5880 modules.
//*         : this value is inteded to be loaded to register at adress 1 via SPI
//*         :
//*  Formula: frequency = ( N*32 + A )*2 + 479
//******************************************************************************
uint16_t RX_5808_CalcFrequencyData( uint16_t frequency )
{
  uint16_t N;
  uint8_t A;
  frequency = (frequency - 479) / 2;
  N = frequency >> 5;
  A = frequency % 32;
  return (N << 7) |  A;
}

/*********************************************************************
 * @brief uint16_t RX5808_GetBandChannel(uint16_t RegData)
 * @param RegData : this is the Registry data of the Frecuency in the RX5808 Module
 * @retval This returns the Band from 0 to 7 in the upper nibble and the Channel from 0 to 7
 *         in the lower nibble.
 * Overview: This function decodes the register read from the RX5808 module to 
 *          detect the Band and Channel.
 *          If this returns 0xFF it couldn't find a valid frecuency     
 * @note  There are some channel registers that are similar in different bands
 *            and this function returns the first ocurrance of the closest band.  
 *    frequency = ( N*32 + A )*2 + 479
 ********************************************************************/
void RX5808_GetBandChannel(uint16_t RegData, uint8_t * Band, uint8_t * Channel){
  uint16_t  N;
  uint8_t A;
  uint16_t  Freq;
  uint8_t Diferencia;
  uint8_t Ch,Bd;
  bool Found = false;
  
  N = (RegData >> 7);
  A = RegData & 0x7F;
  Freq = ((N<<5) + A)*2+479;
  
  for (Ch = 0; Ch < 64; Ch++) {
    if (Ch < 32) Diferencia = 1; else Diferencia = 2; // Es porque la banda con mayor diferencia es la R
    if (abs(Freq - channelFreqTable[Ch])<=Diferencia ){
      Bd = (Ch >> 3)& 0x07; // dividido 8
      Ch = Ch % 8;
      Found = true; 
      break;
    } 
  }
  if (Found) {
    *Band = Bd;
    *Channel = Ch;
  } else {
    *Band = 0xFF;
    *Channel = 0xFF;
  }
    
}


/*********************************************************************
 * @brief 
 * @param 
 * @retval None 
 * Overview:        
 * @note  
 ********************************************************************/
uint32_t RX5808_GetChannel(uint8_t Module){
  uint32_t ReadData = 0;

  // A0-A3 (Register 0x01)
  ReadData = RX5808_GetRegister(0x01, Module);
  
  return ReadData;
  
}

uint32_t RX5808_GetRegister(uint8_t Register, uint8_t Module){
  uint32_t ReadData = 0;
  uint8_t i;
  uint32_t tempData;

  RX5808_DATA_TRIS_PIN = 0; // Output 
  switch (Module){
    case 0: RX5808_CS0 = 0; break;
    case 1: RX5808_CS1 = 0; break;
    case 2: RX5808_CS2 = 0; break;
    case 3: RX5808_CS3 = 0; break;
  }

  // A0-A3 (Register 0x01)
  for (i=0; i<4; i++){
    if ((Register & 0x01) == 1) {
      _RX5808_SendOne();
      
    } else {
      _RX5808_SendZero();
    }
    Register = Register >> 1;
  }
  
  // R/W = 1 - Write
  _RX5808_SendZero(); 
  // when sending the R/W bit and the SCK is down, the data is inmediatly driven out the pin
  // so when reading the data bit in the loop will read inmediatly the bit and after rise and
  // fall the SCK pin. The shift register of the RX5808 is moved in the falling edge of SCK pin

  RX5808_DATA_TRIS_PIN = 1; // Input 

  tempData = 0;
  for(i=0; i<20; i++){
    tempData = (_RX5808_ReadBit() << i);
    ReadData = ReadData | tempData;
  }

  switch (Module){
    case 0: RX5808_CS0 = 1; break;
    case 1: RX5808_CS1 = 1; break;
    case 2: RX5808_CS2 = 1; break;
    case 3: RX5808_CS3 = 1; break;
  }

  RX5808_DATA_TRIS_PIN = 0; // Output again!
  
  return ReadData;
  
}



void RX5808_SetRegister(uint8_t Register, uint32_t Value, uint8_t Module){
  uint8_t i;
  
  
  switch (Module){
    case 0: RX5808_CS0 = 0; break;
    case 1: RX5808_CS1 = 0; break;
    case 2: RX5808_CS2 = 0; break;
    case 3: RX5808_CS3 = 0; break;
  }

  // A0-A3 (Register)
  for (i=0; i<4; i++){
    if ((Register & 0x01) == 1) {
      _RX5808_SendOne();
      
    } else {
      _RX5808_SendZero();
    }
    Register = Register >> 1;
  }
  
  // R/W = 1 - Write
  _RX5808_SendOne(); 
  
  // D0-D19
  for (i=0 ; i<20 ;i++){
    if (Value & 0x01) {
      _RX5808_SendOne();
    } else {
      _RX5808_SendZero();
    }
    Value = Value >> 1;
  }


  switch (Module){
    case 0: RX5808_CS0 = 1; break;
    case 1: RX5808_CS1 = 1; break;
    case 2: RX5808_CS2 = 1; break;
    case 3: RX5808_CS3 = 1; break;
  }

}

