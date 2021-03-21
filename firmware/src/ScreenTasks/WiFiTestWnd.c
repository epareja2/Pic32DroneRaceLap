/*! \file *********************************************************************
 *
 * - File:               WiFiTestWnd.c
 * - Compiler:           MPLABX X32 V2.30  MPLAB 5.3  Harmony 2.06
 * - Supported devices:  
 *
 * \author               Ernesto Pareja  (epare)
 *
 * REVISION HISTORY:
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Author            Date      Comments on that revision
 *----------------------------------------------------------------------
 * Epareja       17 de junio de 2020, 05:48 PM  Creation of file 
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
#include "WiFiTestWnd.h"
#include "usart/drv_usart.h"
#include "gfx/libaria/libaria.h"


/*********************************************************************
 /*                      GLOBAL VARIABLES        
 /*********************************************************************/


/*********************************************************************
 /*                      LOCAL CONSTANT DEFINITIONS
 /*********************************************************************/
typedef enum  {
  AT = 0,
  AT_RST,
  AT_GMR,
  AT_GSLP,
  ATE,
  AT_UART,
  AT_UART_CUR,
  AT_UART_DEF,
  AT_SLEEP,
  AT_RFPOWER,
  AT_RFVDD,
  AT_CWMODE,  //Wi-Fi mode(sta/AP/sta+AP), [@deprecated]
  AT_CWMODE_CUR,  //Wi-Fi mode(sta/AP/sta+AP). Settings not updated in flash.
  AT_CWMODE_DEF,  //Wi-Fi default mode(sta/AP/sta+AP). Save to flash.
  AT_CWJAP, //Connect to AP, [@deprecated]
  AT_CWJAP_CUR,  //Connect to AP, won?t save to flash
  AT_CWJAP_DEF, //Connect to AP, save to flash
  AT_CWLAPOPT, // Set the configuration of command AT+CWLAP
  AT_CWLAP, // Lists available APs
  AT_CWQAP, // Disconnect from AP
  AT_CWSAP, // Set configuration of ESP8266 soft-AP [@deprecated]
  AT_CWSAP_CUR, // Set current configuration of ESP8266 soft-AP. Settings not updated in flash.
  AT_CWSAP_DEF, // Set configuration of ESP8266 soft-AP. Save changes to flash.
  AT_CWLIF, // Get station IP which is connected to ESP8266 soft-AP  
  AT_CWDHCP_CUR, // Enable/Disable DHCP, changes not save to flash
  AT_CWDHCP_DEF, // Enable/Disable DHCP, save changes to flash
  AT_CWDHCPS_CUR, // Set IP range of DHCP server, changes not save to flash
  AT_CWDHCPS_DEF, // Set IP range of DHCP server, save changes to flash
  AT_CWAUTOCONN, // Connect to AP automatically on power-up  
  AT_CIPSTAMAC_CUR, // Set MAC address of ESP8266 station. Changes not save to flash.
  AT_CIPSTAMAC_DEF, // Set MAC address of ESP8266 station. Save changes to flash.
  AT_CIPAPMAC_CUR, // Set MAC address of ESP8266 soft-AP. Changes not save to flash.
  AT_CIPAPMAC_DEF, // Set MAC address of ESP8266 soft-AP Save changes to flash.
  AT_CIPSTA_CUR, //Set IP address of ESP8266 station. Changes not save to flash.
  AT_CIPSTA_DEF, // Set IP address of ESP8266 station. Save changes to flash.
  AT_CIPAP_CUR, // Set IP address of ESP8266 soft-AP. Changes not save to flash.
  AT_CIPAP_DEF, // Set IP address of ESP8266 soft-AP. Save changes to flash.
  AT_CWSTARTSMART, // Start SmartConfig
  AT_CWSTOPSMART, // Stop SmartConfig
  AT_CWSTARTDISCOVER, // Start the mode that ESP8266 can be found by WeChat
  AT_CWSTOPDISCOVER, // Stop the mode that ESP8266 can be found by WeChat
  AT_WPS, // Set WPS function
  AT_MDNS // Set MDNS function    
} AT_COMMANDS;

const int AT_COMMAND_SIZE = AT_MDNS - AT;

const char * atCommandStr[] = {
  "AT", 
  "AT+RST",
  "AT+GMR",
  "AT_GSLP",
  "ATE",
  "AT+UART",
  "AT+UART_CUR",
  "AT+UART_DEF",
  "AT+SLEEP",
  "AT+RFPOWER",
  "AT+RFVDD",
  "AT+CWMODE",  
  "AT+CWMODE_CUR" ,
  "AT+CWMODE_DEF", 
  "AT+CWJAP", 
  "AT+CWJAP_CUR",  //Co
  "AT+CWJAP_DEF", //Con
  "AT+CWLAPOPT", // Set
  "AT+CWLAP", // Lists 
  "AT+CWQAP", // Discon
  "AT+CWSAP", // Set co
  "AT+CWSAP_CUR", // Se
  "AT+CWSAP_DEF", // Se
  "AT+CWLIF", // Get st
  "AT+CWDHCP_CUR", // E
  "AT+CWDHCP_DEF", // E
  "AT+CWDHCPS_CUR", // 
  "AT+CWDHCPS_DEF", // 
  "AT+CWAUTOCONN", // C
  "AT+CIPSTAMAC_CUR", //
  "AT+CIPSTAMAC_DEF", //
  "AT+CIPAPMAC_CUR", //
  "AT+CIPAPMAC_DEF", //
  "AT+CIPSTA_CUR", //Se
  "AT+CIPSTA_DEF", // S
  "AT+CIPAP_CUR", // Se
  "AT+CIPAP_DEF", // Se
  "AT+CWSTARTSMART", //
  "AT+CWSTOPSMART", // 
  "AT+CWSTARTDISCOVER",
  "AT+CWSTOPDISCOVER", 
  "AT+WPS", // Set WPS 
  "AT+MDNS" // Set MDNS
 };


/*********************************************************************
 /*                      PRIVATE FUNCTION DECLARATIONS        
 /*********************************************************************/
void WiFiTestWnd_OnShow(laScreen * screen);
void WiFiTestWnd_OnHide(laScreen * screen);
void SendATCommandBtn_OnClick(laButtonWidget * btn);
void ClearUSART_TextBtn_OnClick(laButtonWidget * btn);
void LoadATCommandsList(void);

/*********************************************************************
 /*                      CODE IMPLEMENTATION        
 /*********************************************************************/

void WiFiTestWnd_Initialize(void){
  laScreen* screen;

  screen = (laScreen*)laContext_GetActive()->screenList.values[WifiTesting_ID];
  laScreen_SetShowEventCallback(screen, &WiFiTestWnd_OnShow); // Set CallBack function
  laScreen_SetHideEventCallback(screen,&WiFiTestWnd_OnHide);
}


/*********************************************************************
 * @brief 
 * @param 
 * @retval None 
 * @exam      
 * @note            
 *********************************************************************/
void WiFiTestWnd_OnShow(laScreen * screen){
  laButtonWidget_SetReleasedEventCallback(SendATCommandBtn, &SendATCommandBtn_OnClick);
  laButtonWidget_SetReleasedEventCallback(ClearUSART_TextBtn, &ClearUSART_TextBtn_OnClick);
  LoadATCommandsList();
//  usartInitBuffer(&appData.usartTxSimpleBuff); // Inicializa el buffer de transmisión
//  usartInitBuffer(&appData.usartRxSimpleBuff); // Inicializa el buffer de transmisión
}

/*********************************************************************
 * @brief 
 * @param 
 * @retval None 
 * @exam      
 * @note            
 *********************************************************************/
void WiFiTestWnd_OnHide(laScreen * screen){
  
}


void WiFiTestWnd_Tasks(void){
  
}

void SendATCommandBtn_OnClick(laButtonWidget * btn){
  uint8_t index;
  
  laListWidget_GetItemSelected(ATCommandsLst, index);
  
  
}

void ClearUSART_TextBtn_OnClick(laButtonWidget * btn){
  laTextFieldWidget_SetText(USART_TextLbl,laString_CreateFromCharBuffer("",&Calibri_14)); 
}


void LoadATCommandsList(void){
  uint8_t i;
  uint8_t n;
  
  n=AT_COMMAND_SIZE;
  for (i = 0; i < n; i++) {
    laListWidget_AppendItem(ATCommandsLst);
    laListWidget_SetItemText(ATCommandsLst, i, laString_CreateFromCharBuffer(atCommandStr[i],&Calibri_14));
  }

}