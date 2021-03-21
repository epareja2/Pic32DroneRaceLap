/* 
 * File:   drv_gfx_ili9325 New.h
 * Author: epareja
 *
 * Created on 25 de octubre de 2017, 10:54 PM
 */

#ifndef DRV_GFX_ILI9325_H 
#define	DRV_GFX_ILI9325_H


#ifdef	__cplusplus
extern "C" {
#endif
  
#include "../framework/gfx/hal/inc/gfx_hal.h"
 
#define DISP_OUTPUT  0x00  // TRIS STATE to the Display Port when Writing
#define DISP_INPUT   0xFF  // TRIS STATE to the Display Port when Readding

#define GFX_LCD_PORT_BITS   8 // 8 bits port interface
  
  
#if defined (__PIC32MX__)

#define DISP_ORIENTATION            GFX_ORIENTATION_180
#define DISP_HOR_RESOLUTION         240
#define DISP_VER_RESOLUTION         320

  
#define DisplayPortConfig(Dir)      TRISE = (Dir)
#define DisplayPort(value)          LATE = (value)
#define DisplayPortRead()           PORTE


#define DispLatchConfig()           TRISDCLR = _TRISD_TRISD10_MASK // To load the LAtch 74HC573
#define DispLatchSet()              LATDSET = _LATD_LATD10_MASK
#define DispLatchClr()              LATDCLR = _LATD_LATD10_MASK

// Definitions for reset pin
#define DisplayResetConfig()        TRISGCLR = _TRISG_TRISG8_MASK
#define DisplayResetEnable()        LATGCLR = _LATG_LATG8_MASK
#define DisplayResetDisable()       LATGSET = _LATG_LATG8_MASK

// Definitions for RS pin
#define DisplayCmdDataConfig()      TRISFCLR = _TRISF_TRISF4_MASK
#define DisplaySetCommand()         LATFCLR = _LATF_LATF4_MASK
#define DisplaySetData()            LATFSET = _LATF_LATF4_MASK

// Definitions for CS pin
#define DisplayConfig()             TRISFCLR = _TRISF_TRISF5_MASK
#define DisplayEnable()             LATFCLR = _LATF_LATF5_MASK
#define DisplayDisable()            LATFSET = _LATF_LATF5_MASK

// Definitions for backlight control pin
#define DisplayBacklightConfig()    (TRISGbits.TRISG9 = 0)
//#define DisplayBacklightOn()        (LATGbits.LATG9 = BACKLIGHT_ENABLE_LEVEL)
//#define DisplayBacklightOff()       (LATGbits.LATG9 = BACKLIGHT_DISABLE_LEVEL)
#define DisplayBacklightOn()        (LATGbits.LATG9 = 0)
#define DisplayBacklightOff()       (LATGbits.LATG9 = 1)

// Definitions for POWER ON pin
#define DisplayPowerConfig()        
#define DisplayPowerOn()            
#define DisplayPowerOff()           

#define DisplayWRConfig()           TRISGCLR = _TRISG_TRISG6_MASK
#define DisplayWRSet()              LATGCLR = _LATG_LATG6_MASK
#define DisplayWRClr()              LATGSET = _LATG_LATG6_MASK

#define DisplayRDConfig()           TRISGCLR = _TRISG_TRISG7_MASK
#define DisplayRDSet()              LATGCLR = _LATG_LATG7_MASK
#define DisplayRDClr()              LATGSET = _LATG_LATG7_MASK

#endif
  
  /*********************************************************************
   /*                   PUBLIC FUNCTION DECLARATIONS
   /*********************************************************************/
void DelayMs(int ms);
void ILI9325_InitHardware(GFX_Context * context);
GFX_Result ILI9325_ClrScreen(GFX_Color color);
static GFX_Result ILI9325_initialize(GFX_Context* context);
//void ILI9325_SetArea(int16_t start_x, int16_t start_y, int16_t end_x, int16_t end_y);
void ILI9325_EnterSleepMode (void);
void ILI9325_ExitSleepMode (void);
void ILI9325_DisplayOff(void);
void ILI9325_DisplayOn(void);
void ILI9325_SetBacklight(uint8_t  intensity); // NOT YET SUPPORTED ON HARDWARE!!!
// function that returns the information for this driver
GFX_Result driverILI9325InfoGet(GFX_DriverInfo* info);
// function that initialized the driver context
GFX_Result driverILI9325ContextInitialize(GFX_Context* context);

#ifdef	__cplusplus
}
#endif

#endif	/* DRV_GFX_ILI9325_NEW_H */

