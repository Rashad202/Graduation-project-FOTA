/*******************************************************************************************************/
/* Author            : GP_FOTA_TEAM                                                                    */
/* Version           : V0.0.0                                                                          */
/* Data              : 3 Feb 2024                                                                      */
/* Description       : MTIMER_interface.h --> implementations                                          */
/* Module  Features  : 																				   */
/*      01- MTIMER_vStartTime                                                                          */
/*      02- MTIMER_vCntTimer                                                                           */
/*      03- MTIMER_vDelayms                                                                            */
/*      04- MTIMER_vPeriodicMS                                                                         */
/*      05- MTIMER_vPWM                                                                                */
/*      06- MTIMER_vICU                                                                                */
/*      07- MTIMER_GET_ICU                                                                             */
/*      08- MTIMER_CallBack                                                                            */
/*******************************************************************************************************/

/*******************************************************************************************************/
/*                                   guard of file will call on time in .c                             */
/*******************************************************************************************************/
#ifndef MTIMER_interface_H_
#define MTIMER_interface_H_

/*******************************************************************************************************/
/*                                    Include files needed for MTIMER_Int.h 		                   */
/*******************************************************************************************************/
#include"../../Libraries/STD_TYPES.h" //Standard Types Lib
#include "../MGPIO/MGPIO_interface.h"
/*******************************************************************************************************/
/*                                   enum for Timer numbers   					                       */
/*								    TIMER 1, TIMER2  												   */
/*								TIMER3, TIMER4, TIMER5,												   */
/* 		   						TIMER9, TIMER10, TIMER11'											   */
/*******************************************************************************************************/
typedef enum{
	TIMER1=1,
	TIMER2,
	TIMER3,
	TIMER4,
	TIMER5,
	TIMER9,
	TIMER10,
	TIMER11,
}Enum_TIMER_NUM;
/*******************************************************************************************************/

/*******************************************************************************************************/
/*                                   enum for Timer channel numbers   					               */
/*			  FOR TIMER 1, TIMER2, TIMER3, TIMER4, TIMER5 ==> CH1,CH2,CH3,CH4				           */
/* 									FOR TIMER9            ==> CH1,CH2 								   */
/* 									FOR TIMER10, TIMER11  ==> CH1					   				   */
/*******************************************************************************************************/
typedef enum{
	CH1=1,
	CH2,
	CH3,
	CH4,
}Enum_TIMER_CHs;
/*******************************************************************************************************/

/*******************************************************************************************************/

typedef enum {
	milli,  /**< Milliseconds */
	sec,    /**< Seconds */
} Enum_TIMER_Unit;

/*******************************************************************************************************/

typedef enum {
	StopTimer,     /**< Stop the timer */
	ContinueTimer, /**< Continue or start the timer */
} Enum_Timer_Cont;
/*******************************************************************************************************/


/*******************************************************************************************************/
//   Timer and Channel Pin Mapping:
/* Timer and Channel Pin Mapping:
   TIMER1, CH1 -> Port A, Pin 8
   TIMER1, CH2 -> Port A, Pin 9
   TIMER1, CH3 -> Port A, Pin 10
   TIMER1, CH4 -> Port A, Pin 11

   TIMER2, CH1 -> Port A, Pin 15
   TIMER2, CH2 -> Port B, Pin 3
   TIMER2, CH3 -> Port A, Pin 2
   TIMER2, CH4 -> Port A, Pin 3

   TIMER3, CH1 -> Port A, Pin 6
   TIMER3, CH2 -> Port A, Pin 7
   TIMER3, CH3 -> Port B, Pin 0
   TIMER3, CH4 -> Port B, Pin 1

   TIMER4, CH1 -> Port B, Pin 6
   TIMER4, CH2 -> Port B, Pin 7
   TIMER4, CH3 -> Port B, Pin 8
   TIMER4, CH4 -> Port B, Pin 9

   TIMER5, CH1 -> Port A, Pin 0
   TIMER5, CH2 -> Port A, Pin 1
   TIMER5, CH3 -> Port A, Pin 2
   TIMER5, CH4 -> Port A, Pin 3

   TIMER9, CH1 -> Port A, Pin 2
   TIMER9, CH2 -> Port A, Pin 3

   TIMER10, CH1 -> Port B, Pin 8

   TIMER11, CH1 -> Port B, Pin 9
 */


volatile static u8 TIMER_PORT_MAP[TIMER11][CH4]=
{
		/*TIMER 1*/
		{	GPIOA_PORT,	GPIOA_PORT,	GPIOA_PORT,	GPIOA_PORT	},

		/* TIMER2 */
		{	GPIOA_PORT,	GPIOB_PORT,	GPIOA_PORT,	GPIOA_PORT	},

		/* TIMER3 */
		{	GPIOA_PORT,	GPIOA_PORT,	GPIOB_PORT,	GPIOB_PORT	},

		/* TIMER4 */
		{	GPIOB_PORT,	GPIOB_PORT,	GPIOB_PORT,	GPIOB_PORT	},

		/* TIMER5 */
		{	GPIOA_PORT,	GPIOA_PORT,	GPIOA_PORT,	GPIOA_PORT	},

		/* TIMER9 */
		{	GPIOA_PORT,	GPIOA_PORT,	GPIOA_PORT,	GPIOA_PORT	},

		/* TIMER10 */
		{	GPIOB_PORT,	GPIOB_PORT,	GPIOA_PORT,	GPIOA_PORT	},

		/* TIMER11 */
		{	GPIOB_PORT,	GPIOB_PORT,	GPIOA_PORT,	GPIOA_PORT	},
};

volatile static u8 TIMER_PIN_MAP[TIMER11][CH4]=
{
		/*TIMER 1*/
		{	PIN_8,	PIN_9,	PIN_10,	PIN_11	},

		/* TIMER2 */
		{	PIN_15,	PIN_3,	PIN_2,	PIN_3	},

		/* TIMER3 */
		{	PIN_6,	PIN_7,	PIN_0,	PIN_1	},

		/* TIMER4 */
		{	PIN_6,	PIN_7,	PIN_8,	PIN_9	},

		/* TIMER5 */
		{	PIN_0,	PIN_1,	PIN_2,	PIN_3	},

		/* TIMER9 */
		{	PIN_2,	PIN_3,	PIN_2,	PIN_3	},

		/* TIMER10 */
		{	PIN_8,	PIN_8,	PIN_8,	PIN_8	},

		/* TIMER11 */
		{	PIN_9,	PIN_9,	PIN_9,	PIN_9	}
};

volatile static u8 TIMER_AF[TIMER11]=
{
		ALTFN_1,ALTFN_1,
		ALTFN_2,ALTFN_2,ALTFN_2,
		ALTFN_3,ALTFN_3,ALTFN_3
};
/*******************************************************************************************************/



/*******************************************************************************************************/
/*                                          APIs                                                       */
/*******************************************************************************************************/


/*******************************************************************************************************/
/*                                      01- MTIMER_vStartTime                                          */
/*-----------------------------------------------------------------------------------------------------*/
void MTIMER_vStartTime(Enum_TIMER_NUM Copy_u8TimerNum);
/*******************************************************************************************************/

/*******************************************************************************************************/
/*                       				 02- MTIMER_vContTimer                                         */
/*-----------------------------------------------------------------------------------------------------*/
void MTIMER_vCntTimer(Enum_TIMER_NUM Copy_u8TimerNum, Enum_Timer_Cont Copy_u8TimerCont);
/*******************************************************************************************************/

/*******************************************************************************************************/
/*                                      03- MTIMER_vDelayms                                  		   */
/*-----------------------------------------------------------------------------------------------------*/
void MTIMER_vDelayms(Enum_TIMER_NUM Copy_u8TimerNum, u32 Copy_u32Delayms);
/*******************************************************************************************************/

/*******************************************************************************************************/
/*                                      04- MTIMER_vPeriodicMS                                         */
/*-----------------------------------------------------------------------------------------------------*/
void MTIMER_vPeriodicMS(Enum_TIMER_NUM Copy_u8TimerNum, u32 Copy_u32Delay);
/*******************************************************************************************************/

/*******************************************************************************************************/
/*                                      05- MTIMER_vPWM                                       		   */
/*-----------------------------------------------------------------------------------------------------*/
void MTIMER_vPWM(Enum_TIMER_NUM Copy_u8TimerNum, Enum_TIMER_CHs Copy_u8Channel, u16 Copy_u16TotalTime_uSec, u16 Copy_u16PositiveDutyCycle_uSec);
/*******************************************************************************************************/

/*******************************************************************************************************/
/*                                      06- MTIMER_vICU                                       		   */
/*-----------------------------------------------------------------------------------------------------*/
void MTIMER_vICU(Enum_TIMER_NUM Copy_u8TimerNum, Enum_TIMER_CHs Copy_u8Channel);
/*******************************************************************************************************/

/*******************************************************************************************************/
/*                                      07- MTIMER_GET_ICU                                       	   */
/*----------------------------------------------------------------------------------------------------*/
u32 MTIMER_GET_ICU(Enum_TIMER_NUM Copy_u8TimerNum, Enum_TIMER_CHs Copy_u8Channel);
/*******************************************************************************************************/

/*******************************************************************************************************/
/*                                      08- MTIMER_CallBack                                       	   */
/*-----------------------------------------------------------------------------------------------------*/
void MTIMER_CallBack(Enum_TIMER_NUM Copy_u8TimerNum, void (*ptr)(void));
/*******************************************************************************************************/



#endif /* MTIMER_interface_H_ */
