/*******************************************************************************************************/
/* Author            : GP_FOTA_TEAM                                                                    */
/* Version           : V0.0.0                                                                          */
/* Data              : 21 Dec 2023                                                                     */
/* Description       : MEXTI_Program.c --> implementations                                             */
/*******************************************************************************************************/
/*******************************************************************************************************/
/*                                      Standard Types LIB                                             */
/*******************************************************************************************************/

#include "../Libraries/STD_TYPES.h"
#include "../Libraries/BIT_MATH.h"

/*******************************************************************************************************/
/*                                      MCAL Components                                                */
/*******************************************************************************************************/


#include "MEXTI_private.h"
#include "MEXTI_interface.h"
#include "MEXTI_config.h"

/*                                      Pointer to Function                                            */
static void (*EXTI0_CallBack ) (void) =  NULL ;
static void (*EXTI1_CallBack ) (void) =  NULL ;
static void (*EXTI2_CallBack ) (void) =  NULL ;
static void (*EXTI3_CallBack ) (void) =  NULL ;
static void (*EXTI4_CallBack ) (void) =  NULL ;





/*******************************************************************************************************/
/*                                      Functions Implementations                                      */
/*******************************************************************************************************/

/* Give The Function The Line To Enable It IntTERPUT  */

void MEXIT_voidEnableEXIT(u8 Copy_u8Line)
{

	SET_BIT (EXTI_Ptr ->IMR ,Copy_u8Line);

}

/*******************************************************************************************************/

/* Give The Function The Line To Disable It IntTERPUT  */

void MEXIT_voidDisableEXIT(u8 Copy_u8Line)
{

	CLR_BIT (EXTI_Ptr ->IMR ,Copy_u8Line);

}

/*******************************************************************************************************/

/* Function Make SoftWare INT at Any Line */
// If Interrput Enable (PIE) ON This Line And EXTI_IMR Line Writing By '1' , When it is Set To '0' Set Corresponding Pending
/* IMR = 1 And PR =0 FOR 0:15 Now You Will Have Software Trigger & And It Clear By Put 1 At PR */

void MEXIT_voidSoftwareInterrput(u8 Copy_u8Line)
{
	SET_BIT(EXTI_Ptr->SWIER , Copy_u8Line);								  // It will Be Clear Alone

}

/*******************************************************************************************************/

/* Function To Change Mode And Line At RunTime */
// Signal Latch == Init But Here I can Change The Line And Sense Mode

void MEXTI_voidSetSignalLatch( u8 Copy_u8Line,  u8 Copy_u8EXTISenseMode )
{

	switch(Copy_u8EXTISenseMode)
	{
	case (Rising_Edage):	 
						SET_BIT( EXTI_Ptr -> RTSR, Copy_u8Line );
						break;

	case (Falling_Edage):		
						SET_BIT( EXTI_Ptr -> FTSR, Copy_u8Line );
						break;

	case (On_Change) :
						SET_BIT( EXTI_Ptr -> FTSR, Copy_u8Line );
						SET_BIT( EXTI_Ptr -> RTSR, Copy_u8Line );
						break;

	}
	SET_BIT(EXTI_Ptr->IMR ,Copy_u8Line ) ;
}


/*******************************************************************************************************/

void MEXTI_voidSetEXTIConfiguration(u8 Copy_u8ExtiLine , EXTI_Ports_t Copy_enumGpioPortNum )
{

	switch(Copy_u8ExtiLine)
	{
	case LINE_0:
		SYSCFG->EXTICR1 &=  EXTI_CONFG_MASK1;    //0xFFFFFFF0
		SYSCFG->EXTICR1 |=  Copy_enumGpioPortNum;
		break ;
	case LINE_1:
		SYSCFG->EXTICR1 &=  EXTI_CONFG_MASK2;    //0xFFFFFF0F
		SYSCFG->EXTICR1 |=  Copy_enumGpioPortNum<<4;
		break ;

	case LINE_2:
		SYSCFG->EXTICR1 &=  EXTI_CONFG_MASK3;    //0xFFFFF0FF
		SYSCFG->EXTICR1 |=  Copy_enumGpioPortNum<<8;
		break ;

	case LINE_3:
		SYSCFG->EXTICR1 &=  EXTI_CONFG_MASK4;    //0xFFF0FFF
		SYSCFG->EXTICR1 |=  Copy_enumGpioPortNum<<12;
		break ;

	case LINE_4:
		SYSCFG->EXTICR2 &=  EXTI_CONFG_MASK1;    //0xFFFFFFF0
		SYSCFG->EXTICR2  |=  Copy_enumGpioPortNum;
		break ;
	case LINE_5:
		SYSCFG->EXTICR2 &=  EXTI_CONFG_MASK2;    //0xFFFFFF0F
		SYSCFG->EXTICR2 |=  Copy_enumGpioPortNum<<4;
		break ;

	case LINE_6:
		SYSCFG->EXTICR2 &=  EXTI_CONFG_MASK3;    //0xFFFFF0FF
		SYSCFG->EXTICR2 |=  Copy_enumGpioPortNum<<8;
		break ;

	case LINE_7:
		SYSCFG->EXTICR2 &=  EXTI_CONFG_MASK4;    //0xFFF0FFF
		SYSCFG->EXTICR2 |=  Copy_enumGpioPortNum<<12;
		break ;
		
	case LINE_8:
		SYSCFG->EXTICR3 &=  EXTI_CONFG_MASK1;    //0xFFFFFFF0
		SYSCFG->EXTICR3 |=  Copy_enumGpioPortNum;
		break ;
	case LINE_9:
		SYSCFG->EXTICR3 &=  EXTI_CONFG_MASK2;    //0xFFFFFF0F
		SYSCFG->EXTICR3 |=  Copy_enumGpioPortNum<<4;
		break ;

	case LINE_10:
		SYSCFG->EXTICR3 &=  EXTI_CONFG_MASK3;    //0xFFFFF0FF
		SYSCFG->EXTICR3 |=  Copy_enumGpioPortNum<<8;
		break ;

	case LINE_11:
		SYSCFG->EXTICR3 &=  EXTI_CONFG_MASK4;    //0xFFF0FFF
		SYSCFG->EXTICR3 |=  Copy_enumGpioPortNum<<12;
		break ;	

	case LINE_12:
		SYSCFG->EXTICR4 &=  EXTI_CONFG_MASK1;    //0xFFFFFFF0
		SYSCFG->EXTICR4 |=  Copy_enumGpioPortNum;
		break ;
	case LINE_13:
		SYSCFG->EXTICR4 &=  EXTI_CONFG_MASK2;    //0xFFFFFF0F
		SYSCFG->EXTICR4 |=  Copy_enumGpioPortNum<<4;
		break ;

	case LINE_14:
		SYSCFG->EXTICR4 &=  EXTI_CONFG_MASK3;    //0xFFFFF0FF
		SYSCFG->EXTICR4 |=  Copy_enumGpioPortNum<<8;
		break ;

	case LINE_15:
		SYSCFG->EXTICR4 &=  EXTI_CONFG_MASK4;    //0xFFF0FFF
		SYSCFG->EXTICR4 |=  Copy_enumGpioPortNum<<12;
		break ;			
	default : /*Do Nothing*/   break ;
	}
}

/*******************************************************************************************************/

void MEXTI0_voidSetCallBack( void (*ptr) (void))
{

	EXTI0_CallBack =ptr  ;	// Now The Global EXTI0_Call Will Point TO Any Functiom You Will Pass It To Function Only Give Function It's Name

}

/*******************************************************************************************************/

void MEXTI1_voidSetCallBack( void (*ptr) (void))
{

	EXTI1_CallBack =ptr  ;	// Now The Global EXTI1_Call Will Point TO Any Functiom You Will Pass It To Function Only Give Function It's Name

}

/*******************************************************************************************************/

void MEXTI2_voidSetCallBack( void (*ptr) (void))
{

	EXTI2_CallBack =ptr  ;	// Now The Global EXTI2_Call Will Point TO Any Functiom You Will Pass It To Function Only Give Function It's Name

}

/*******************************************************************************************************/

void MEXTI3_voidSetCallBack( void (*ptr) (void))
{

	EXTI3_CallBack =ptr  ;	// Now The Global EXTI3_Call Will Point TO Any Functiom You Will Pass It To Function Only Give Function It's Name

}
/*******************************************************************************************************/

void MEXTI4_voidSetCallBack( void (*ptr) (void))
{

	EXTI4_CallBack =ptr  ;	// Now The Global EXTI4_Call Will Point TO Any Functiom You Will Pass It To Function Only Give Function It's Name

}
/*******************************************************************************************************/

void EXTI0_IRQHandler(void)								
{
	EXTI0_CallBack();
	SET_BIT( EXTI_Ptr->PR , LINE_0 );					// With Out That It Will Do INT Alaways
}

/*******************************************************************************************************/
void EXTI1_IRQHandler(void)
{
	EXTI1_CallBack();
	SET_BIT( EXTI_Ptr->PR , LINE_1 );					// With Out That It Will Do INT Alaways
}

/*******************************************************************************************************/
void EXTI2_IRQHandler(void)								
{
	EXTI2_CallBack();
	SET_BIT( EXTI_Ptr->PR , LINE_2 );					// With Out That It Will Do INT Alaways
}

/*******************************************************************************************************/
void EXTI3_IRQHandler(void)
{
	EXTI3_CallBack();
	SET_BIT( EXTI_Ptr->PR , LINE_3 );					// With Out That It Will Do INT Alaways
}

/*******************************************************************************************************/
void EXTI4_IRQHandler(void)
{
	EXTI4_CallBack();
	SET_BIT( EXTI_Ptr->PR , LINE_4 );					// With Out That It Will Do INT Alaways
}
/*****************************************************END_FUNCTION*****************************************/
