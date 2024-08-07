/*******************************************************************************************************/
/* Author            : GP_FOTA_TEAM                                                                    */
/* Version           : V0.0.0                                                                          */
/* Data              : 15 Dec 2023                                                                     */
/* Description       : MRCC_Program.c --> implementations                                              */
/*******************************************************************************************************/


/*******************************************************************************************************/
/*                                      Standard Types LIB                                             */
#include "../../Libraries/STD_TYPES.h"
#include "../../Libraries/BIT_MATH.h"
/*******************************************************************************************************/
/*                                      MCAL Components                                                */
#include "MRCC_private.h"
#include "MRCC_interface.h"
#include "MRCC_config.h"

/*******************************************************************************************************/
/*                                      Functions Implementations                                      */
/*******************************************************************************************************/

void MRCC_voidEnablePeripheralClock(BusName_t BusName , u8 Copy_u8PerNum )
{
	
	switch(BusName)
	{
		case AHB1_BUS:  SET_BIT(RCC_AHB1ENR,Copy_u8PerNum );         break ;
		case AHB2_BUS:  SET_BIT(RCC_AHB2ENR,Copy_u8PerNum );         break ;
		case APB1_BUS:  SET_BIT(RCC_APB1ENR,Copy_u8PerNum );         break ;
		case APB2_BUS:  SET_BIT(RCC_APB2ENR,Copy_u8PerNum );         break ;
		default :     /*   ERROR   */          break ;
		
	}
}
/*******************************************************************************************************/


void MRCC_voidDisablePeripheralClock(BusName_t BusName , u8 Copy_u8PerNum )
{
	switch(BusName)
	{
		case AHB1_BUS:  CLR_BIT(RCC_AHB1ENR,Copy_u8PerNum );         break ;
		case AHB2_BUS:  CLR_BIT(RCC_AHB2ENR,Copy_u8PerNum );         break ;
		case APB1_BUS:  CLR_BIT(RCC_APB1ENR,Copy_u8PerNum );         break ;
		case APB2_BUS:  CLR_BIT(RCC_APB2ENR,Copy_u8PerNum );         break ;
		default :     /* ERROR */          break ;
		
	}
}

/*******************************************************************************************************/

void MRCC_voidEnableSecuritySystem(void)
{
	SET_BIT( RCC_CR  , CSSON);
	
}
/*******************************************************************************************************/


void MRCC_voidDisableSecuritySystem(void)
{
	CLR_BIT( RCC_CR  , CSSON);
	
}
/*******************************************************************************************************/

void MRCC_voidInitSystemClk(void)
{
	/********** HSI **********/
#if CLKSRC == HSI 
	/* 1- EN HSI */
	SET_BIT(MRCC->CR , 0U);
	/* 2- CLK SYS --> HSI */
	CLR_BIT(MRCC->CFGR, 0U);
	CLR_BIT(MRCC->CFGR, 1U);
	/********** HSE **********/
#elif CLKSRC == HSE
	
	#if HSE_SRC == CRYSTAL 
	/* 1- EN HSE */
		SET_BIT(MRCC->CR , 16U);
		/* 2- Disable BYP */
		CLR_BIT(MRCC->CR,18U);
		/* 3- CLK SYS --> HSE */
		SET_BIT(MRCC->CFGR, 0U);
		CLR_BIT(MRCC->CFGR, 1U);

	#elif HSE_SRC == RC 
		/* 1- EN HSE */
		SET_BIT(MRCC->CR , 16U);
		/* 2- Enable BYP */
		SET_BIT(MRCC->CR,18U);
		/* 3- CLK SYS --> HSE */
		SET_BIT(MRCC->CFGR, 0U);
		CLR_BIT(MRCC->CFGR, 1U);
	#else 
    /* Error*/
	#endif
	
	/********** PLL **********/
#elif CLKSRC == PLL	

    #if PLL_SRC == HSE_PLL
     /*1-Enable HSE */
			SET_BIT(MRCC->CR,16U);
			/* while ( GET_BIT(RCC_CR, 17)==0);*/
			/*2- EN PLL*/
			SET_BIT(MRCC->,24U);
			/* while ( GET_BIT(RCC_CR, 25)==0);*/
			/* 3- PLL From HSE */
			SET_BIT(MRCC->PLLCFGR, 22U);
			/* 4- System Clk  PLL */
			CLR_BIT(MRCC->CFGR,0U);
			SET_BIT(MRCC->CFGR,1U);
 
    #elif PLL_SRC == HSI_PLL
            /*Enable HSI */
		     SET_BIT(MRCC->CR,0U);
			/*2- EN PLL*/
			SET_BIT(MRCC->CR,24U);
			/* 3- PLL From HSI */
			CLR_BIT(MRCC->PLLCFGR, 22U);
			/* 4- System Clk  PLL */
			CLR_BIT(MRCC->CFGR,0U);
			SET_BIT(MRCC->CFGR,1U);
    #else 
            /* Error*/
	#endif
/****************************************************/

#else 
/* Error*/
#endif // The End Of Big IF	
}

/*******************************************************************************************************/

void MRCC_voidInitClock(CLKSrcName_t Copy_tClkSrc , HSESrc_t Copy_tHSESrc ,PLLSrc_t Copy_tPLLSrc )
{
	switch(Copy_tClkSrc)
	{
		case HSE :
		switch(Copy_tHSESrc)
		{
		  case HSE_CRYSTAL :
			/*1-Enable HSE */
			SET_BIT(RCC_CR,16U);
			/* while ( GET_BIT(RCC_CR, 17)==0);*/
			/*Disable BYP*/
			CLR_BIT(RCC_CR,18U);
			/* Input system Clk*/
			SET_BIT(RCC_CFGR,0U);
			CLR_BIT(RCC_CFGR,1U);
		  break ;
		  /************************************************/
          case HSE_RC :
			/*Enable HSE */
			SET_BIT(RCC_CR,16U);
            /*2-Disable BYP*/
			SET_BIT(RCC_CR,18U);
				/* Input system Clk*/
			SET_BIT(RCC_CFGR,0U);
			CLR_BIT(RCC_CFGR,1U);

		  break ;

		  /*********************************************/
		  default :  break ;
		}
	    break ;
		/*******************/
		case HSI :
		/*Enable HSI */
		SET_BIT(RCC_CR,0U);
		/* Input system Clk*/
		CLR_BIT(RCC_CFGR,0U);
		CLR_BIT(RCC_CFGR,1U);
	    break ;
		/********************/
		case PLL :
		switch(Copy_tPLLSrc)
		{
			case HSE_PLL:
			/*1-Enable HSE */
			SET_BIT(RCC_CR,16U);
			/* while ( GET_BIT(RCC_CR, 17)==0);*/
			/*2- EN PLL*/
			SET_BIT(RCC_CR,24U);
			/* while ( GET_BIT(RCC_CR, 25)==0);*/
			/**/
			SET_BIT(RCC_PLLCFGR, 22U);
			
			CLR_BIT(RCC_CFGR,0U);
			SET_BIT(RCC_CFGR,1U);
			
			break ;
			
			/**************************/
			
			case HSI_PLL :
			/*Enable HSI */
		     SET_BIT(RCC_CR,0U);
			/*2- EN PLL*/
			SET_BIT(RCC_CR,24U);
			
			CLR_BIT(RCC_PLLCFGR, 22U);
			
			CLR_BIT(RCC_CFGR,0U);
			SET_BIT(RCC_CFGR,1U);
			
			break ;
		}

	    break ;
		
	}
	
}
