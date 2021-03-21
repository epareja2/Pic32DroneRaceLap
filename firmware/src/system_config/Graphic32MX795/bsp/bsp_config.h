/*******************************************************************************
  Board Support Package Header File.

  Company:      
    Microchip Technology Inc.

  File Name:    
    bsp_config.h

  Summary:      
    Board Support Package Header file for PIC32MX USB Starter Kit II when used
    along with the Graphics PICtail Plus Epson S1D13517 Board and a VGA display.

  Description:
    This file contains constants, macros, type definitions and function
    declarations required by the BSP for PIC32MX USB Starter Kit II when used
    along with the Graphics PICtail Plus Epson S1D13517 Board and a VGA display.
*******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2014 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED AS IS WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
*******************************************************************************/

#ifndef BSP_CONFIG_H
#define BSP_CONFIG_H
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

// *****************************************************************************
// *****************************************************************************
// Section: Constants and Type Definitions.
// *****************************************************************************
// *****************************************************************************

#if defined (__PIC32MX__) // This is a test
//#define DisplayPortConfig(Dir)      TRISE = (Dir)
//#define DisplayPort(value)          LATE = (value)
//#define DisplayPortRead()           PORTE
//
//#define DispLatchConfig()           TRISDCLR = _TRISD_TRISD10_MASK // To load the LAtch 74HC573
//#define DispLatchSet()              LATDSET = _LATD_LATD10_MASK
//#define DispLatchClr()              LATDCLR = _LATD_LATD10_MASK
//
//// Definitions for reset pin
//#define DisplayResetConfig()        TRISGCLR = _TRISG_TRISG8_MASK
//#define DisplayResetEnable()        LATGCLR = _LATG_LATG8_MASK
//#define DisplayResetDisable()       LATGSET = _LATG_LATG8_MASK
//
//// Definitions for RS pin
//#define DisplayCmdDataConfig()      TRISFCLR = _TRISF_TRISF4_MASK
//#define DisplaySetCommand()         LATFCLR = _LATF_LATF4_MASK
//#define DisplaySetData()            LATFSET = _LATF_LATF4_MASK
//
//// Definitions for CS pin
//#define DisplayConfig()             TRISFCLR = _TRISF_TRISF5_MASK
//#define DisplayEnable()             LATFCLR = _LATF_LATF5_MASK
//#define DisplayDisable()            LATFSET = _LATF_LATF5_MASK
//
//// Definitions for backlight control pin
//#define DisplayBacklightConfig()    (TRISGbits.TRISG9 = 0)
//#define DisplayBacklightOn()        (LATGbits.LATG9 = BACKLIGHT_ENABLE_LEVEL)
//#define DisplayBacklightOff()       (LATGbits.LATG9 = BACKLIGHT_DISABLE_LEVEL)
//
//// Definitions for POWER ON pin
//#define DisplayPowerConfig()        
//#define DisplayPowerOn()            
//#define DisplayPowerOff()           
//
//#define DisplayWRConfig()           TRISGCLR = _TRISG_TRISG6_MASK
//#define DisplayWRSet()              LATGCLR = _LATG_LATG6_MASK
//#define DisplayWRClr()              LATGSET = _LATG_LATG6_MASK
//
//#define DisplayRDConfig()           TRISGCLR = _TRISG_TRISG7_MASK
//#define DisplayRDSet()              LATGCLR = _LATG_LATG7_MASK
//#define DisplayRDClr()              LATGSET = _LATG_LATG7_MASK
//
#endif


// Definitions for PushButtons
#define UP_BTN                      PORTBbits.RB2
#define DOWN_BTN                    PORTBbits.RB3
#define LEFT_BTN                    PORTBbits.RB4
#define RIGHT_BTN                   PORTBbits.RB5
#define BUTTON_TRIS_MASK            0b00111100

// Definitions for FLASH CS pin
#define DisplayFlashConfig()        TRISFCLR = _TRISF_TRISF5_MASK
#define DisplayFlashEnable()        LATFCLR = _LATF_LATF5_MASK
#define DisplayFlashDisable()       LATFSET = _LATF_LATF5_MASK


// 25LC1024 EEPROM HARDWARE DEFINITION
#define EEPROM_CS_TRIS   TRISDbits.TRISD6
#define EEPROM_CS_LAT    LATDbits.LATD6
#define EEPROM_WP_LAT    LATDbits.LATD9
#define EEPROM_HOLD_LAT  LATDbits.LATD11

#define EEPROM_SCK_TRIS  TRISDbits.TRISD1
#define EEPROM_SDO_TRIS  TRISDbits.TRISD2
#define EEPROM_SDI_TRIS  TRISDbits.TRISD3
#define EEPROM_WP_TRIS   TRISDbits.TRISD9
#define EEPROM_HOLD_TRIS TRISDbits.TRISD11

#define EEPROM_CS_Enable()      EEPROM_CS_LAT = 0
#define EEPROM_CS_Disable()     EEPROM_CS_LAT = 1
#define EEPROM_WP_Enable()      EEPROM_WP_LAT = 0
#define EEPROM_WP_Disable()     EEPROM_WP_LAT = 1
#define EEPROM_HOLD_Enable()    EEPROM_HOLD_LAT = 0
#define EEPROM_HOLD_Disable()   EEPROM_HOLD_LAT = 1



// ADS7843 Touch Screen Controller
#define ADS7843_MSDI_TRIS TRISDbits.TRISD2
#define ADS7843_MSDI      PORTDbits.RD2
#define ADS7843_MSDO_TRIS TRISDbits.TRISD3
#define ADS7843_MSDO      LATDbits.LATD3
#define ADS7843_CLK_TRIS  TRISDbits.TRISD1
#define ADS7843_CLK       LATDbits.LATD1
#define ADS7843_CS_TRIS   TRISDbits.TRISD5
#define ADS7843_CS        LATDbits.LATD5
#define ADS7843_IRQ_TRIS  TRISDbits.TRISD0
#define ADS7843_IRQ       PORTDbits.RD0
#define ADS7843_BUSY_TRIS TRISDbits.TRISD7
#define ADS7843_BUSY      PORTDbits.RD7


//#define ADS7843_Enable()  ADS7843_CS = 0;
//#define ADS7843_Disable() ADS7843_CS = 1;

#define ADS7843_Enable()  PLIB_PORTS_PinClear( PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_5);//ADS7843_CS = 0;
#define ADS7843_Disable() PLIB_PORTS_PinSet( PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_5);//ADS7843_CS = 1;

//SD Card Controller
#define SD_CS_TRIS        TRISDbits.TRISD4
#define SD_CS             LATDbits.LATD4




#endif //BSP_CONFIG_H

/*******************************************************************************
 End of File
*/
