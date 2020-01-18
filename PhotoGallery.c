#include <LPC17xx.H>                    /* NXP LPC17xx definitions            */
#include <stdlib.h>
#include <stdio.h>
#include "string.h"
#include "GLCD.h"
#include "LED.h"
#include "ADC.h"
#include "KBD.h"

#include "keanu.c"
#include "tap.c"


#define __FI        1                    /* Font index 16x24               */
#define __USE_LCD   0										/* Uncomment to use the LCD */


//ITM Stimulus Port definitions for printf //////////////////
#define ITM_Port8(n)    (*((volatile unsigned char *)(0xE0000000+4*n)))
#define ITM_Port16(n)   (*((volatile unsigned short*)(0xE0000000+4*n)))
#define ITM_Port32(n)   (*((volatile unsigned long *)(0xE0000000+4*n)))

#define DEMCR           (*((volatile unsigned long *)(0xE000EDFC)))
#define TRCENA          0x01000000
	
int PhotoGallery (void) {                      
	int state = 1;
  	int photo = 0;
	int photoIn= 0;
	
		GLCD_Clear(White);
		phtoto = 0;
		photoIn= 0;
		while(get_button() != KBD_SELECT){
			if( get_button() == KBD_RIGHT){
				if(photo != 2){
					photo++;
				  	photoIn = 0;
				}
			}

			if( get_button() == KBD_LEFT){
				if(photo != -1){
					photo--;
					phtotoIn = 0;
				}
			}	
			
			if(photo == 0 && photoIn == 0){
				photoIn = 1;
				#ifdef __USE_LCD
					GLCD_Clear  (White);
					GLCD_Bitmap (  0,   0, 310,  174, KEANU_PIXEL_DATA);
				#endif					
			}
			if(photo == 1 && photoIn == 0){
				photoIn = 1;
				#ifdef __USE_LCD
					GLCD_Clear  (White);
					GLCD_Bitmap (  0,   0, 310,  174, TAP_PIXEL_DATA);
				#endif
			}
		}
		GLCD_Clear(White);
		GLCD_SetBackColor(Blue);
		GLCD_SetTextColor(White);
		GLCD_DisplayString(0, 0, __FI, "    Media Center     ");
		GLCD_DisplayString(1, 0, __FI, "     Main Menu       ");
		GLCD_SetTextColor(White);
		GLCD_SetBackColor(Blue);
		GLCD_DisplayString(3, 0, __FI, "  1.Photo Gallery     ");
		GLCD_DisplayString(4, 0, __FI, "  2.Audio Player      ");
		GLCD_DisplayString(5, 0, __FI, "  3.Game Menu         ");
		GLCD_SetBackColor(White);
		GLCD_SetTextColor(Blue);
		GLCD_DisplayString(8, 0, __FI, "Use joystick up/down");
		GLCD_DisplayString(9, 0, __FI, "Select w/ right     ");
		return 0;
}


