/*----------------------------------------------------------------------------
 * Name:    GameMenu.c
 * 

 *----------------------------------------------------------------------------*/

#include <LPC17xx.H>                    // NXP LPC17xx definitions         
#include <stdlib.h>
#include <stdio.h>
#include "string.h"
#include "GLCD.h"
#include "LED.h"
#include "ADC.h"
#include "KBD.h"

#define __FI        1                    // Font index 16x24               
#define __USE_LCD   0										 // Uncomment to use the LCD 

uint32_t joystick2 = 0;
uint32_t joystickInit2 = 0;


extern int Game2(void);
extern int Game(void);
extern int main(void);

//ITM Stimulus Port definitions for printf //////////////////
#define ITM_Port8(n)    (*((volatile unsigned char *)(0xE0000000+4*n)))
#define ITM_Port16(n)   (*((volatile unsigned short*)(0xE0000000+4*n)))
#define ITM_Port32(n)   (*((volatile unsigned long *)(0xE0000000+4*n)))

#define DEMCR           (*((volatile unsigned long *)(0xE000EDFC)))
#define TRCENA          0x01000000

/*----------------------------------------------------------------------------
  Main Program
 *----------------------------------------------------------------------------*/
int GameMenu (void) {                       /* Main Program                       */
int state = 1;
  LED_Init();                                /* LED Initialization            */
	KBD_Init();																/* Joystick Initialization			*/
  GLCD_Init();                             /* Initialize graphical LCD (if enabled  */	

#ifdef __USE_LCD
		GLCD_Clear(White);
		GLCD_SetBackColor(Blue);
		GLCD_SetTextColor(White);
		GLCD_DisplayString(0, 0, __FI, " COE718 Media Center ");
		GLCD_DisplayString(1, 0, __FI, "     Game Menu       ");
		GLCD_SetTextColor(White);
		GLCD_SetBackColor(Blue);
		GLCD_DisplayString(3, 0, __FI, "  1.Space Game        ");
		GLCD_DisplayString(4, 0, __FI, "  2.Copy Game         ");
		GLCD_DisplayString(5, 0, __FI, "  3.Main Menu         ");
		GLCD_SetBackColor(White);
		GLCD_SetTextColor(Blue);
		GLCD_DisplayString(8, 0, __FI, "Use joystick up/down");
		GLCD_DisplayString(9, 0, __FI, "Select w/ right     ");
#endif
	
while (1) {                                /* Loop forever                  */

	 uint32_t joystickInit2 = 0;
   joystick2 = get_button();    // Joystick state
		
	while (joystick2 != joystickInit2){	
		
		if (joystick2 == KBD_UP){
			if (state != 1){
				state++;
			}
		}
		
		if (joystick2 == KBD_DOWN){
			if(state != -1){
				state--;
			}
		}		
		
		if (state == 1){
			
		#ifdef __USE_LCD
		GLCD_SetTextColor(White);
		GLCD_SetBackColor(LightGrey);
		GLCD_DisplayString(3, 0, __FI, "  1.Space Game        ");
		GLCD_SetTextColor(White);
		GLCD_SetBackColor(Blue);
		GLCD_DisplayString(4, 0, __FI, "  2.Copy Game         ");
		GLCD_DisplayString(5, 0, __FI, "  3.Main Menu         ");
		#endif
		}	
		
		if (state == 0){
		
		#ifdef __USE_LCD
		GLCD_SetTextColor(White);
		GLCD_SetBackColor(LightGrey);
		GLCD_DisplayString(4, 0, __FI, "  2.Copy Game         ");
		GLCD_SetTextColor(White);
		GLCD_SetBackColor(Blue);
		GLCD_DisplayString(3, 0, __FI, "  1.Space Game        ");
		GLCD_DisplayString(5, 0, __FI, "  3.Main Menu         ");
		#endif
		}
		
		if (state == -1){
		#ifdef __USE_LCD
		GLCD_SetTextColor(White);
		GLCD_SetBackColor(LightGrey);
		GLCD_DisplayString(5, 0, __FI, "  3.Main Menu         ");
		GLCD_SetTextColor(White);
		GLCD_SetBackColor(Blue);
		GLCD_DisplayString(3, 0, __FI, "  1.Space Game        ");
		GLCD_DisplayString(4, 0, __FI, "  2.Copy Game         ");
		#endif
		}		
	
		if ( state == 1 && joystick2 == KBD_RIGHT){
			Game();		
		}
		joystickInit2 = joystick2;		
		}
		if (state == 0 && joystick2 == KBD_RIGHT){
			Game2();
		}
		if (state == -1 && joystick2 == KBD_RIGHT){
			main();
		}
		
  }
}


