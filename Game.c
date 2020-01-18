#include <LPC17xx.H>                    /* NXP LPC17xx definitions            */
#include <stdlib.h>
#include <stdio.h>
#include "string.h"
#include "GLCD.h"
#include "LED.h"
#include "ADC.h"
#include "KBD.h"

#include "enemy.c" 
#include "spaceship.c" 
#include "spaceshipHurt.c" 
#include "white.c"

#define __FI        1                    /* Font index 16x24               */
#define __USE_LCD   0										/* Uncomment to use the LCD */

//ITM Stimulus Port definitions for printf /
#define ITM_Port8(n)    (*((volatile unsigned char *)(0xE0000000+4*n)))
#define ITM_Port16(n)   (*((volatile unsigned short*)(0xE0000000+4*n)))
#define ITM_Port32(n)   (*((volatile unsigned long *)(0xE0000000+4*n)))

#define DEMCR           (*((volatile unsigned long *)(0xE000EDFC)))
#define TRCENA          0x01000000




void delay(int t){
int i = 0;
	while(i<t) 	//c: while(i<100000000)
		i++;
}

char text1[10]; //c: char text1[10];
char levelT[10];
/*----------------------------------------------------------------------------
  Main Program
 *----------------------------------------------------------------------------*/
int Game (void) {                       /* Main Program                       */
	int state = 1;
	int num     = -1; 
  int dir     =  1;
	int level = 0;
	int levelCount = 1;
	int lives = 4; 
	
	int x;
	int y;
	int n = 5;
  int x2;
	int y2;
	int shipx = 6; 
	int shipy = 151;
  double t;
	
	uint32_t joystickInit = 0;

  LED_Init();                                /* LED Initialization            */
  KBD_Init();																/* Joystick Initialization			*/
  GLCD_Init();                             /* Initialize graphical LCD (if enabled  */	


sprintf(text1, "Lives: %d ", lives);       /* format text for print out     */

while (1) {                                /* Loop forever */
			GLCD_Clear(White);

			while(get_button() != KBD_SELECT) {
			GLCD_SetBackColor(White); 
			
				level++; 
				if((level%3) == 0){
					n++;
				}
				if((level%10) == 0){
					levelCount++;
					sprintf(levelT, "Level: %d ", levelCount);      
				}

			/*Generate a random number,x, from 1 to 220*/ 
				for (y = 1; y < 340; y+=n){
					srand((unsigned) level);
					x = rand()%220+1;		
						x2 = y; 
						y2 = x;
						GLCD_Bitmap (x,   y, 50,  51, ENEMY_PIXEL_DATA); 
						GLCD_Bitmap (x2,  y2, 50,  51, ENEMY_PIXEL_DATA); 
						
						if( get_button() == KBD_RIGHT){
							GLCD_Bitmap (  shipx,   shipy, 50,  39, SHIP_PIXEL_DATA); 
							if(shipx <= 260){
								shipx=shipx+20; 
							}
								GLCD_Bitmap (  shipx-20, shipy, 50,  51, WHITE_PIXEL_DATA); 				
						}
						if( get_button() == KBD_UP){ 
							GLCD_Bitmap ( shipx,   shipy, 50,  39, SHIP_PIXEL_DATA); 
							if(shipy >= 20){
								shipy-=20;
							}
							GLCD_Bitmap (  shipx, shipy+20, 50,  51, WHITE_PIXEL_DATA); 		
						}
						if( get_button() == KBD_DOWN){
							GLCD_Bitmap (  shipx,   shipy, 50,  39, SHIP_PIXEL_DATA); 
							if(shipy <= 190){
								shipy+=20; 
							}
							GLCD_Bitmap (  shipx, shipy-20, 50,  51, WHITE_PIXEL_DATA); 					
						}
						
						if (get_button() == KBD_LEFT){
							GLCD_Bitmap (  shipx,   shipy, 50,  39, SHIP_PIXEL_DATA); 
							if(shipx >= 10){
								shipx=shipx-20; 
							}
							GLCD_Bitmap (  shipx+20, shipy, 50,  51, WHITE_PIXEL_DATA); 				
						}
						if(((y > (shipy-35)) && (y < (shipy+35)) && (x > (shipx-35)) && (x < (shipx+35)))){
									GLCD_Bitmap (  shipx,   shipy, 50,  39, HURT_PIXEL_DATA); 	
									GLCD_Bitmap (  x,   y, 50,  51, WHITE_PIXEL_DATA);
									lives--; 
									sprintf(text1, "Lives: %d ", lives);      
									break;
						}
						if((y2 > (shipy-35)) && (y2 < (shipy+35)) && (x2 > (shipx-35)) && (x2 < (shipx+35))){
									GLCD_Bitmap (  shipx,   shipy, 50,  39, HURT_PIXEL_DATA); 		
									GLCD_Bitmap (  x2,   y2, 50,  51, WHITE_PIXEL_DATA); 
									lives--; 
									sprintf(text1, "Lives: %d ", lives);      
									break;							
						}
						GLCD_Bitmap (  x2-55,   y2, 50,  51, WHITE_PIXEL_DATA); 
						GLCD_Bitmap (  x,   y-55, 50,  51, WHITE_PIXEL_DATA); 
						GLCD_Bitmap (shipx,   shipy, 50,  39, SHIP_PIXEL_DATA); 
						GLCD_SetTextColor(Black);
						GLCD_DisplayString(0, 10, __FI, (unsigned char *)text1);
				}
				GLCD_ClearLn (9,1); 
				GLCD_Bitmap (  x2,   y2, 50,  51, WHITE_PIXEL_DATA); 
				GLCD_Bitmap (  x,   y, 50,  51, WHITE_PIXEL_DATA); 

				if ( lives == 0){
						delay(3000000);
						GLCD_Clear(White);
						GLCD_Bitmap (127,   150, 50,  39, HURT_PIXEL_DATA); 
						GLCD_SetTextColor(Black);
					  GLCD_DisplayString(4, 0, __FI, "    GAME  OVER!    ");
			      GLCD_SetTextColor(Red);
					  GLCD_DisplayString(5, 0, __FI, "     YOU LOSE!    ");
						delay(10000000);
						GLCD_SetTextColor(Red);
					  GLCD_DisplayString(4, 0, __FI, "    GAME  OVER!    ");
			      GLCD_SetTextColor(Black);
					  GLCD_DisplayString(5, 0, __FI, "     YOU LOSE!    ");
						delay(10000000);
						GLCD_SetTextColor(Black);
					  GLCD_DisplayString(4, 0, __FI, "    GAME  OVER!    ");
			      GLCD_SetTextColor(Red);
					  GLCD_DisplayString(5, 0, __FI, "     YOU LOSE!    ");
						delay(10000000);
						GLCD_SetTextColor(Red);
					  GLCD_DisplayString(4, 0, __FI, "    GAME  OVER!    ");
			      GLCD_SetTextColor(Black);
					  GLCD_DisplayString(5, 0, __FI, "     YOU LOSE!    ");

					  delay(50000000); 
						GLCD_Clear(White);
						GLCD_SetBackColor(Blue);
						GLCD_SetTextColor(White);
						GLCD_DisplayString(0, 0, __FI, " COE718 Media Center 	");
						GLCD_DisplayString(1, 0, __FI, "     Game Menu       	");
						GLCD_SetTextColor(White);
						GLCD_SetBackColor(Blue);
						GLCD_DisplayString(3, 0, __FI, "  1.Space Game        ");
						GLCD_DisplayString(4, 0, __FI, "  2.Copy Game         ");
						GLCD_DisplayString(5, 0, __FI, "  3.Main Menu         ");
						GLCD_SetBackColor(White);
						GLCD_SetTextColor(Blue);
						GLCD_DisplayString(8, 0, __FI, "Use joystick up/down	");
						GLCD_DisplayString(9, 0, __FI, "Select w/ right     	");
						return 0;
				}
				if ( level%10 == 0){
						GLCD_Clear(Black);
						GLCD_SetBackColor(Black);
						GLCD_SetTextColor(White);
						GLCD_DisplayString(5, 6, __FI, (unsigned char *)levelT);
					  delay(57000000);
						GLCD_Clear(White);
				}
				
		}
		GLCD_Clear(White);
		GLCD_SetBackColor(Blue);
		GLCD_SetTextColor(White);
		GLCD_DisplayString(0, 0, __FI, " COE718 Media Center 	");
		GLCD_DisplayString(1, 0, __FI, "     Game Menu       	");
		GLCD_SetTextColor(White);
		GLCD_SetBackColor(Blue);
		GLCD_DisplayString(3, 0, __FI, "  1.Space Game        ");
		GLCD_DisplayString(4, 0, __FI, "  2.Copy Game         ");
		GLCD_DisplayString(5, 0, __FI, "  3.Main Menu         ");
		GLCD_SetBackColor(White);
		GLCD_SetTextColor(Blue);
		GLCD_DisplayString(8, 0, __FI, "Use joystick up/down	");
		GLCD_DisplayString(9, 0, __FI, "Select w/ right     	");
		return 0;
		}
	
		
	}



