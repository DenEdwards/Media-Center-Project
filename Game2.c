#include <LPC17xx.H>                    /* NXP LPC17xx definitions            */
#include <stdlib.h>
#include <stdio.h>
#include <time.h> 
#include "string.h"
#include "GLCD.h"
#include "LED.h"
#include "ADC.h"
#include "KBD.h"


#define __FI        1                    /* Font index 16x24               */
#define __USE_LCD   0										/* Uncomment to use the LCD */

//ITM Stimulus Port definitions for printf /
#define ITM_Port8(n)    (*((volatile unsigned char *)(0xE0000000+4*n)))
#define ITM_Port16(n)   (*((volatile unsigned short*)(0xE0000000+4*n)))
#define ITM_Port32(n)   (*((volatile unsigned long *)(0xE0000000+4*n)))

#define DEMCR           (*((volatile unsigned long *)(0xE000EDFC)))
#define TRCENA          0x01000000




void delay2(int t){
int i = 0;
	while(i<t) 	
		i++;
}

char text2[10]; //c: char text1[10];



int lose(void){
						delay2(3000000);
						GLCD_Clear(White);
						GLCD_SetTextColor(Black);
						GLCD_SetBackColor(White);
					  GLCD_DisplayString(4, 0, __FI, "    GAME  OVER!    ");
			      GLCD_SetTextColor(Red);
					  GLCD_DisplayString(5, 0, __FI, "     YOU LOSE!    ");
						delay2(10000000);
						GLCD_SetTextColor(Red);
					  GLCD_DisplayString(4, 0, __FI, "    GAME  OVER!    ");
			      GLCD_SetTextColor(Black);
					  GLCD_DisplayString(5, 0, __FI, "     YOU LOSE!    ");
						delay2(10000000);
						GLCD_SetTextColor(Black);
					  GLCD_DisplayString(4, 0, __FI, "    GAME  OVER!    ");
			      GLCD_SetTextColor(Red);
					  GLCD_DisplayString(5, 0, __FI, "     YOU LOSE!    ");
						delay2(10000000);
						GLCD_SetTextColor(Red);
					  GLCD_DisplayString(4, 0, __FI, "    GAME  OVER!    ");
			      GLCD_SetTextColor(Black);
					  GLCD_DisplayString(5, 0, __FI, "     YOU LOSE!    ");

					  delay2(100000000); //c: delay2();
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
						GLCD_DisplayString(8, 0, __FI, "Use joystick2 up/down");
						GLCD_DisplayString(9, 0, __FI, "Select w/ right     ");
						return 0;
}

/*----------------------------------------------------------------------------
  Main Program
 *----------------------------------------------------------------------------*/
int Game2 (void) {                       /* Main Program                       */
	
	int x;
	int on1 = 0;
	int on2 = 0;
	int on3 = 0;
	int on4 = 0;
	int round;
	int n = 30000000;
	uint32_t joystickInit = 0;

  LED_Init();                                /* LED Initialization            */
	KBD_Init();																/* Joystick Initialization			*/
  GLCD_Init();                             /* Initialize graphical LCD (if enabled  */	


	
while (1) {                                /* Loop forever */
	while(get_button() != KBD_SELECT) {
		
			GLCD_Clear(Black);
			GLCD_SetTextColor(White);
			GLCD_SetBackColor(Black);
			GLCD_DisplayString(4, 1, __FI, "Hold the joystyick");		
			GLCD_DisplayString(5, 1, __FI, "in direction shown");	
			GLCD_DisplayString(6, 1, __FI, "quick before time");
			GLCD_DisplayString(7, 3, __FI, "runs out!");			
			delay2(90000000);
			GLCD_Clear(White);
		GLCD_SetBackColor(White); 		
		for (round = 1; round < 15; round++){
					srand( (unsigned)(round));
					x = (rand() % (12 - 1 + 1)) + 1;				
					
					if(x == 3 || x == 6 || x == 9){
							if(on3 == 1){
								GLCD_Clear(Green);
								GLCD_SetTextColor(Black);
								GLCD_SetBackColor(Green);
								on3 = 0;
							}
							else{
								GLCD_Clear(Yellow);
								GLCD_SetTextColor(Black);
								GLCD_SetBackColor(Yellow);
								on3 = 1;
							}
					    GLCD_DisplayString(4,6, __FI, "DOWN V");
							delay2(n);					
							if(get_button() == KBD_DOWN){
								GLCD_DisplayString(5, 6, __FI, "GOOD!");
								delay2(30000000);
							}
							else{
								GLCD_DisplayString(5, 6, __FI, "WRONG!");	
								delay2(30000000);
								return (lose());
							}
						}
					
						if(x == 1 || x == 5 || x== 11){
							if(on1 == 1){
								GLCD_Clear(Blue);
								GLCD_SetTextColor(White);
								GLCD_SetBackColor(Blue);
								on1 = 0;
							}else{
								on1 = 1;
								GLCD_Clear(Red);
								GLCD_SetTextColor(White);
								GLCD_SetBackColor(Red);
							}
							GLCD_DisplayString(4,7, __FI, "UP ^");
							delay2(n);
							
							if(get_button() == KBD_UP){
								GLCD_DisplayString(5, 6, __FI, "GOOD!");
								delay2(30000000);
							}
							
							else{
								GLCD_DisplayString(5, 6, __FI, "WRONG!");	
								delay2(30000000);
								return (lose());
							}
						}
						
						if(x == 2 || x == 7 || x ==  10){
							if(on2 == 1){
								GLCD_Clear(Red);
								GLCD_SetTextColor(White);
								GLCD_SetBackColor(Red);
								on2 = 0;
							}else{
								on2 = 1;
								GLCD_Clear(Blue);
								GLCD_SetTextColor(White);
								GLCD_SetBackColor(Blue);
							}
							GLCD_DisplayString(4,6, __FI, "RIGHT >");
							delay2(n);					
							if(get_button() == KBD_RIGHT){
								GLCD_DisplayString(5, 6, __FI, "GOOD!");
								delay2(30000000);
							}
							else{
								GLCD_DisplayString(5, 6, __FI, "WRONG!");	
								delay2(30000000);
								return (lose());
							}
						}
						
						
						if(x == 4 || x == 8 || x == 12){
							if(on4 == 1){
								GLCD_Clear(Yellow);
								GLCD_SetTextColor(Black);
								GLCD_SetBackColor(Yellow);
								on4 = 0;
							}else{
								on4 = 1;
								GLCD_Clear(Green);
								GLCD_SetTextColor(Black);
								GLCD_SetBackColor(Green);
							}
							GLCD_DisplayString(4,6, __FI, "LEFT <");
							delay2(n);					
							if(get_button() == KBD_LEFT){
								GLCD_DisplayString(5,6, __FI, "GOOD!");
								delay2(30000000);
							}
							
							else{
								GLCD_DisplayString(5,6, __FI, "WRONG!");	
								delay2(30000000);
								return (lose());
							}
						}
		}
		GLCD_Clear(Green);
		GLCD_SetTextColor(Black);
		GLCD_SetBackColor(Green);
		GLCD_DisplayString(4, 0, __FI, "      YOU  WIN!    ");		
		delay2(30000000);
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
}





