/*******************************************************************************************************/
/* Author            : GP_FOTA_TEAM                                                                    */
/* Version           : V0.0.0                                                                          */
/* Data              : 15 Dec 2023                                                                     */
/* Description       : MSTK_Program.c --> implementations                                              */
/* Module  Features  :                                                                                 */
/*      01- MSTK_voidInit                                                                              */
/*      02- MSTK_voidStart                                                                             */
/*      03- MSTK_voidINTStatus                                                                         */
/*      04- MSTK_u8ReadFlag                                                                            */
/*      05- MSTK_VidSetCallBack                                                                        */
/*******************************************************************************************************/

/*******************************************************************************************************/
/*                                      Standard Types LIB                                             */
#include "../../Libraries/STD_TYPES.h"
#include "../../Libraries/BIT_MATH.h"

/*******************************************************************************************************/
/*                                      MCAL Components                                                */
#include "MSYSTICK_Private.h"
#include "MSYSTICK_Interface.h"
#include "MSYSTICK_Config.h"

/*******************************************************************************************************/
static void (* MSTK_CallBack) (void) = NULL;
static u8	MSTK_u8ModeOfInterval;

/*******************************************************************************************************/
/*                                      01- MSTK_voidInit                                              */
void MSTK_voidInit( void ){

	#if CLK_SOURCE_CONFIG == PROCCESOR_CLK_AHB
	SET_BIT(MSTK->CTRL , CLKSOURCE);
	#elif CLK_SOURCE_CONFIG == PROCCESOR_CLK_AHB_DIV8
	CLR_BIT(MSTK->CTRL , CLKSOURCE);
	#endif
}

/*******************************************************************************************************/
/*                                      02- MSTK_voidStart                                              */
void MSTK_voidStart( u32 Copy_PreloadValue ){

	//Load Reload Value
	MSTK->LOAD = Copy_PreloadValue;
	/* Clear Val Register     */
	MSTK->VAL  = 0 ;
	/* Enable Systick    */
	SET_BIT( MSTK->CTRL , 0 );
	/*  POLL On the Counter Flag */
	while(GET_BIT( MSTK->CTRL , COUNTFLAG ) == 0);

	/*		Stop Timer 						*/
	CLR_BIT(MSTK->CTRL , 0);
	/* Clear Load Reload      */
	MSTK->LOAD = 0;
	/* Clear Val Register     */
	MSTK->VAL  = 0 ;

}

/*******************************************************************************************************/
/*                                      03- MSTK_voidStopInterval                                              */
void MSTK_voidStopInterval(void) 
{
    /*	Stop Timer 	*/
	CLR_BIT(MSTK->CTRL , 0);
	/* Clear Load Reload      */
	MSTK->LOAD = 0;
	/* Clear Val Register     */
	MSTK->VAL  = 0 ;
}
/*******************************************************************************************************/
/*                                      03- MSTK_voidReSetInterval                                             */
void MSTK_voidReSetInterval( u32 Copy_PreloadValue ){

	/* Clear Load Reload      */
	MSTK->LOAD = 0;
	/* Clear Val Register     */
	MSTK->VAL  = 0 ;

	//Load Reload Value
	MSTK->LOAD = Copy_PreloadValue;
	/* Clear Val Register     */
	MSTK->VAL  = 0 ;
	/* Enable Systick    */
	SET_BIT( MSTK->CTRL , 0 );
	/*  POLL On the Counter Flag */
	while(GET_BIT( MSTK->CTRL , COUNTFLAG ) == 0);

	/*		Stop Timer 						*/
	CLR_BIT(MSTK->CTRL , 0);
	/* Clear Load Reload      */
	MSTK->LOAD = 0;
	/* Clear Val Register     */
	MSTK->VAL  = 0 ;

}

/*******************************************************************************************************/
/*                                      04- MSTK_voidSetIntervalSingle                                              */
void	MSTK_voidSetIntervalSingle(u32 Ticks,void (*Copy_ptr)(void))
{
	/*		Load Ticks to Load Register		*/
	MSTK->LOAD	= Ticks;
	/*		Start Timer 					*/
	SET_BIT(MSTK->CTRL , 0);
	/*		Save CallBack					*/
	MSTK_CallBack = Copy_ptr;
	/*		Software Flage to indicate which callback will execute	*/
	MSTK_u8ModeOfInterval = MSTK_SINGLE_INTERVAL;
	/*		SysTick Interrupt Enable PIE	*/
	SET_BIT(MSTK->CTRL , 1);

}

/*******************************************************************************************************/
/*                                      05- MSTK_voidSetIntervalPeriodic                                              */
void	MSTK_voidSetIntervalPeriodic(u32 Ticks,void (*Copy_ptr)(void))
{
	/*		Load Ticks to Load Register		*/
	MSTK->LOAD	= Ticks;
	/*		Start Timer 					*/
	SET_BIT(MSTK->CTRL , 0);
	/*		Save CallBack					*/
	MSTK_CallBack = Copy_ptr;
	/*		Software Flage to indicate which callback will execute	*/
	MSTK_u8ModeOfInterval = MSTK_PERIOD_INTERVAL;
	/*		SysTick Interrupt Enable PIE	*/
	SET_BIT(MSTK->CTRL , 1);

}

/*******************************************************************************************************/
/*                                      06- MSTK_u8ReadFlag                                            */

u8 MSTK_u8ReadFlag( void ){

	return ( GET_BIT( MSTK->CTRL , COUNTFLAG ) );

}

/*******************************************************************************************************/
/*                                      07- MSTK_u32GetCurrentValue                                              */
u32 MSTK_u32GetCurrentValue(void){
	u32 local_u32CurrentValue;
	local_u32CurrentValue = MSTK->VAL;
	return local_u32CurrentValue;
}

/*******************************************************************************************************/
/*                                      08- MSTK_u32GetCurrentValue                                              */
u32 MSTK_u32GetElapsedTime(void){
	u32 local_u32ElapsedTime;
	local_u32ElapsedTime = MSTK->LOAD - MSTK->VAL;
	return local_u32ElapsedTime;
}

/*******************************************************************************************************/
/*                                      09- _delay_ms                                              */
void _delay_ms( u32 Copy_u32Time ){

	MSTK_voidInit();
	/*	1- Disable the Interrupt 	*/
	CLR_BIT(MSTK->CTRL , 1);
	
	MSTK_voidStart( Copy_u32Time * 2000 );
	/*    Stop Timer      */
	MSTK_voidStopInterval();

}

/*******************************************************************************************************/
/*                                      10- _delay_us                                              */
void _delay_us( u32 Copy_u32Time ){

	MSTK_voidInit();
	/*	1- Disable the Interrupt 	*/
	CLR_BIT(MSTK->CTRL , 1);
	
	MSTK_voidStart( Copy_u32Time * 2);
	/*    Stop Timer      */
	MSTK_voidStopInterval();
}


/*******************************************************************************************************/
/*                                      //Core Peripheral                                              */

void	SysTick_Handler(void)
{
	u8 Local_u8Temp = 0;
	if(MSTK_u8ModeOfInterval == MSTK_SINGLE_INTERVAL)
	{
		/*	1- Disable the Interrupt 	*/
			CLR_BIT(MSTK->CTRL , 1);
		/*	2- Stop the timer			*/
			CLR_BIT(MSTK->CTRL , 0);
			MSTK->LOAD	= 0;
			MSTK->VAL	= 0;
	}
	 /*Execute Action to be done after the time passed*/
	if(MSTK_CallBack !=NULL)
	{	
	MSTK_CallBack();
	}
	/*	Clear Interrupt Flag by reading the Flag */
	Local_u8Temp	=	GET_BIT(MSTK->CTRL , COUNTFLAG);
}
