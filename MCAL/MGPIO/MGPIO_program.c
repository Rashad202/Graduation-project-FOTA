/*******************************************************************************************************/
/* Author            : GP_FOTA_TEAM                                                                    */
/* Version           : V0.0.0                                                                          */
/* Data              : 15 Dec 2023                                                                     */
/* Description       : MGPIO_Program.c --> implementations                                             */
/*******************************************************************************************************/


/*                                      Standard Types LIB                                             */
#include "../../Libraries/STD_TYPES.h"
#include "../../Libraries/BIT_MATH.h"

/*                                      MCAL Components                                                */
#include "MGPIO_private.h"
#include "MGPIO_interface.h"
#include "MGPIO_config.h"

/*                                      Functions Implementations                                      */
void MGPIO_voidSetPinMode(u8 Copy_u8PortName ,u8 Copy_u8PinNum ,u8 Copy_u8Mode  ){
	
	switch(Copy_u8PortName)
	{
	  case GPIOA_PORT : MGPIOA->MODER |= (u32) ( Copy_u8Mode << ( 2U* Copy_u8PinNum )) ; break;
	  case GPIOB_PORT : MGPIOB->MODER |= (u32) ( Copy_u8Mode << ( 2U* Copy_u8PinNum )) ; break;
	  case GPIOC_PORT : MGPIOC->MODER |= (u32) ( Copy_u8Mode << ( 2U* Copy_u8PinNum )) ; break;
	  case GPIOD_PORT : MGPIOD->MODER |= (u32) ( Copy_u8Mode << ( 2U* Copy_u8PinNum )) ; break;
	  case GPIOE_PORT : MGPIOE->MODER |= (u32) ( Copy_u8Mode << ( 2U* Copy_u8PinNum )) ; break;
	  case GPIOH_PORT : MGPIOH->MODER |= (u32) ( Copy_u8Mode << ( 2U* Copy_u8PinNum )) ; break;
	  default : /*ERROR*/ break ;
    }
}


/*******************************************************************************************************/


void MGPIO_voidSetPinOutPutType(u8 Copy_u8PortName ,u8 Copy_u8PinNum ,u8 Copy_u8OutPutType  ){
	
	switch(Copy_u8PortName)
	{
	  case GPIOA_PORT : MGPIOA->OTYPER |= (u32) ( Copy_u8OutPutType << ( Copy_u8PinNum )) ; break;
	  case GPIOB_PORT : MGPIOB->OTYPER |= (u32) ( Copy_u8OutPutType << ( Copy_u8PinNum )) ; break;
	  case GPIOC_PORT : MGPIOC->OTYPER |= (u32) ( Copy_u8OutPutType << ( Copy_u8PinNum )) ; break;
	  case GPIOD_PORT : MGPIOD->OTYPER |= (u32) ( Copy_u8OutPutType << ( Copy_u8PinNum )) ; break;
	  case GPIOE_PORT : MGPIOE->OTYPER |= (u32) ( Copy_u8OutPutType << ( Copy_u8PinNum )) ; break;
	  case GPIOH_PORT : MGPIOH->OTYPER |= (u32) ( Copy_u8OutPutType << ( Copy_u8PinNum )) ; break;
	  default : /*ERROR*/ break ;
     }
	
}


/*******************************************************************************************************/


void MGPIO_voidSetPinOutSpeed(u8 Copy_u8PortName ,u32 Copy_u8PinNum ,u32 Copy_u8OutSpeed ){
	
	switch(Copy_u8PortName)
	{
	  case GPIOA_PORT : MGPIOA->OSPEEDR |= (u32) ( Copy_u8OutSpeed << ( 2U* Copy_u8PinNum )) ; break;
	  case GPIOB_PORT : MGPIOB->OSPEEDR |= (u32) ( Copy_u8OutSpeed << ( 2U* Copy_u8PinNum )) ; break;
	  case GPIOC_PORT : MGPIOC->OSPEEDR |= (u32) ( Copy_u8OutSpeed << ( 2U* Copy_u8PinNum )) ; break;
	  case GPIOD_PORT : MGPIOD->OSPEEDR |= (u32) ( Copy_u8OutSpeed << ( 2U* Copy_u8PinNum )) ; break;
	  case GPIOE_PORT : MGPIOE->OSPEEDR |= (u32) ( Copy_u8OutSpeed << ( 2U* Copy_u8PinNum )) ; break;
	  case GPIOH_PORT : MGPIOH->OSPEEDR |= (u32) ( Copy_u8OutSpeed << ( 2U* Copy_u8PinNum )) ; break;
	  default : /*ERROR*/ break ;
	}
}

/*******************************************************************************************************/


void MGPIO_voidSetPullType(u8 Copy_u8PortName ,u32 Copy_u8PinNum ,u32 Copy_u8PullType )
{
	
		switch(Copy_u8PortName)
	{
	  case GPIOA_PORT : MGPIOA->PUPDR   |= (u32) ( Copy_u8PullType << ( 2U* Copy_u8PinNum )) ; break;
	  case GPIOB_PORT : MGPIOB->PUPDR   |= (u32) ( Copy_u8PullType << ( 2U* Copy_u8PinNum )) ; break;
	  case GPIOC_PORT : MGPIOC->PUPDR   |= (u32) ( Copy_u8PullType << ( 2U* Copy_u8PinNum )) ; break;
	  case GPIOD_PORT : MGPIOD->PUPDR   |= (u32) ( Copy_u8PullType << ( 2U* Copy_u8PinNum )) ; break;
	  case GPIOE_PORT : MGPIOE->PUPDR   |= (u32) ( Copy_u8PullType << ( 2U* Copy_u8PinNum )) ; break;
	  case GPIOH_PORT : MGPIOH->PUPDR   |= (u32) ( Copy_u8PullType << ( 2U* Copy_u8PinNum )) ; break;
	  default : /*ERROR*/ break ;
	}
	
}

/*******************************************************************************************************/


u8 MGPIO_u8ReadData(u8 Copy_u8PORT ,u8 Copy_u8PIN)
{
	u8 L_u8Data = 0 ;
	switch(Copy_u8PORT)
	{ 
	  case GPIOA_PORT :L_u8Data= GET_BIT(MGPIOA->IDR,Copy_u8PIN ) ; break;
	  
	  case GPIOB_PORT :L_u8Data= GET_BIT(MGPIOB->IDR,Copy_u8PIN ) ; break;
	  
	  case GPIOC_PORT :L_u8Data= GET_BIT(MGPIOC->IDR,Copy_u8PIN ) ; break;
	  
	  case GPIOD_PORT :L_u8Data= GET_BIT(MGPIOD->IDR,Copy_u8PIN) ; break;
	  
	  case GPIOE_PORT :L_u8Data= GET_BIT(MGPIOE->IDR,Copy_u8PIN) ; break;
	  
	  case GPIOH_PORT :L_u8Data= GET_BIT(MGPIOH->IDR,Copy_u8PIN) ; break;
	  default : /*ERROR*/ break ;
		
	}
	return L_u8Data;
	
}

/*******************************************************************************************************/


void MGPIO_voidWriteData(u8 Copy_u8PortName ,u8 Copy_u8PinNum ,u8 Copy_u8State)
{

	if(Copy_u8State==HIGH)
	{
		switch(Copy_u8PortName)
		{
		case GPIOA_PORT :  SET_BIT(MGPIOA ->ODR,Copy_u8PinNum); break;
		
		case GPIOB_PORT :  SET_BIT(MGPIOB ->ODR,Copy_u8PinNum); break;
		
		case GPIOC_PORT :  SET_BIT(MGPIOC ->ODR,Copy_u8PinNum); break;
		
		case GPIOD_PORT :  SET_BIT(MGPIOD ->ODR,Copy_u8PinNum); break;
		
		case GPIOE_PORT :  SET_BIT(MGPIOE ->ODR,Copy_u8PinNum); break;
		
		case GPIOH_PORT :  SET_BIT(MGPIOH ->ODR,Copy_u8PinNum); break;
		
		default : /*ERROR*/ break ;
		}
		
	}
	else{
		switch(Copy_u8PortName)
		{
		case GPIOA_PORT :  CLR_BIT(MGPIOA ->ODR,Copy_u8PinNum); break;
		
		case GPIOB_PORT :  CLR_BIT(MGPIOB ->ODR,Copy_u8PinNum); break;
		
		case GPIOC_PORT :  CLR_BIT(MGPIOC ->ODR,Copy_u8PinNum); break;
		
		case GPIOD_PORT :  CLR_BIT(MGPIOD ->ODR,Copy_u8PinNum); break;
		
		case GPIOE_PORT :  CLR_BIT(MGPIOE ->ODR,Copy_u8PinNum); break;
		
		case GPIOH_PORT :  CLR_BIT(MGPIOH ->ODR,Copy_u8PinNum); break;
		
		default : /*ERROR*/ break ;
		}
	}
}
/*******************************************************************************************************/


void MGPIO_voidToggleData(u8 Copy_u8PortName ,u8 Copy_u8PinNum)
{

		switch(Copy_u8PortName)
		{
		case GPIOA_PORT :  TOG_BIT(MGPIOA ->ODR,Copy_u8PinNum); break;

		case GPIOB_PORT :  TOG_BIT(MGPIOB ->ODR,Copy_u8PinNum); break;

		case GPIOC_PORT :  TOG_BIT(MGPIOC ->ODR,Copy_u8PinNum); break;

		case GPIOD_PORT :  TOG_BIT(MGPIOD ->ODR,Copy_u8PinNum); break;

		case GPIOE_PORT :  TOG_BIT(MGPIOE ->ODR,Copy_u8PinNum); break;

		case GPIOH_PORT :  TOG_BIT(MGPIOH ->ODR,Copy_u8PinNum); break;

		default : /*ERROR*/ break ;
		}

}


/*******************************************************************************************************/


void MGPIO_voidPinLock(u8 Copy_u8PortNum ,u8 Copy_u8PinNum )
{
  switch(Copy_u8PortNum)	
  {
	  case GPIOA_PORT  :
							SET_BIT(MGPIOA->LCKR,Copy_u8PinNum );
							SET_BIT(MGPIOA->LCKR,_LUCKED_PIN );
							while(!(GET_BIT(MGPIOA->LCKR,_LUCKED_PIN)));
	  
	  break ; 
	  /*************************************************/
	  case GPIOB_PORT  :
							SET_BIT(MGPIOB->LCKR,Copy_u8PinNum );
							SET_BIT(MGPIOB->LCKR,_LUCKED_PIN );
							while(!(GET_BIT(MGPIOB->LCKR,_LUCKED_PIN)));
	  
	  break ; 
	  /*************************************************/
	    case GPIOC_PORT  :
							SET_BIT(MGPIOC->LCKR,Copy_u8PinNum );
							SET_BIT(MGPIOC->LCKR,_LUCKED_PIN );
							while(!(GET_BIT(MGPIOC->LCKR,_LUCKED_PIN)));
	  
	  break ; 
	  /*************************************************/
	  case GPIOD_PORT  :
							SET_BIT(MGPIOD->LCKR,Copy_u8PinNum );
							SET_BIT(MGPIOD->LCKR,_LUCKED_PIN );
							while(!(GET_BIT(MGPIOD->LCKR,_LUCKED_PIN)));
	  
	  break ;
     /*************************************************/	 
	case GPIOE_PORT  :
							SET_BIT(MGPIOE->LCKR,Copy_u8PinNum );
							SET_BIT(MGPIOE->LCKR,_LUCKED_PIN );
							while(!(GET_BIT(MGPIOE->LCKR,_LUCKED_PIN)));
	  
	  break ;
	  /*************************************************/	
	  case GPIOH_PORT  :
							SET_BIT(MGPIOH->LCKR,Copy_u8PinNum );
							SET_BIT(MGPIOH->LCKR,_LUCKED_PIN );
							while(!(GET_BIT(MGPIOH->LCKR,_LUCKED_PIN)));
	  
	  break ;
	  /*************************************************/	
  }
	
}

/*******************************************************************************************************/

void MGPIO_vDirectSetReset(u8 Copy_u8PortName , u8 Copy_u8PinNum, u8 Copy_u8State)
{
	if(Copy_u8State == HIGH)
	{
		switch (Copy_u8PortName)
		{
			case GPIOA_PORT: MGPIOA->BSRR = (1U<<Copy_u8PinNum); break;
			case GPIOB_PORT: MGPIOB->BSRR = (1U<<Copy_u8PinNum); break;
			case GPIOC_PORT: MGPIOC->BSRR = (1U<<Copy_u8PinNum); break;
			case GPIOD_PORT: MGPIOD->BSRR = (1U<<Copy_u8PinNum); break;
			case GPIOE_PORT: MGPIOE->BSRR = (1U<<Copy_u8PinNum); break;
			case GPIOH_PORT: MGPIOH->BSRR = (1U<<Copy_u8PinNum); break;
		}
	}
	else
	{
		Copy_u8PinNum += 16;
		switch (Copy_u8PortName)
		{
			case GPIOA_PORT: MGPIOA->BSRR = (1U<<Copy_u8PinNum); break;
			case GPIOB_PORT: MGPIOB->BSRR = (1U<<Copy_u8PinNum); break;
			case GPIOC_PORT: MGPIOC->BSRR = (1U<<Copy_u8PinNum); break;
			case GPIOD_PORT: MGPIOD->BSRR = (1U<<Copy_u8PinNum); break;
			case GPIOE_PORT: MGPIOE->BSRR = (1U<<Copy_u8PinNum); break;
			case GPIOH_PORT: MGPIOH->BSRR = (1U<<Copy_u8PinNum); break;
		}
	}
}
/*******************************************************************************************************/


void MGPIO_voidSetPinAltFn( u8 Copy_u8PortNum ,u8 Copy_u8PinNum, u8 Copy_u8ALF )
{
	if(Copy_u8PinNum <=7U)
	{
		switch(Copy_u8PortNum )
		{
			 case GPIOA_PORT  : MGPIOA->AFRL |=(u32)(Copy_u8ALF <<(4U* Copy_u8PinNum)); break ;
			 case GPIOB_PORT  : MGPIOB->AFRL |=(u32)(Copy_u8ALF <<(4U* Copy_u8PinNum)); break ;
			 case GPIOC_PORT  : MGPIOC->AFRL |=(u32)(Copy_u8ALF <<(4U* Copy_u8PinNum)); break ;
			 case GPIOD_PORT  : MGPIOD->AFRL |=(u32)(Copy_u8ALF <<(4U* Copy_u8PinNum)); break ;
			 case GPIOE_PORT  : MGPIOE->AFRL |=(u32)(Copy_u8ALF <<(4U* Copy_u8PinNum)); break ;
			 case GPIOH_PORT  : MGPIOH->AFRL |=(u32)(Copy_u8ALF <<(4U* Copy_u8PinNum)); break ;
			 default : break ;
		}
		
	}
	// 8 : 15
	// i need 8 = 0 & 15 = 7
	
	else
	{
	switch(Copy_u8PortNum )
		{
			 case GPIOA_PORT  : MGPIOA->AFRH |=(u32)(Copy_u8ALF <<(4U* (Copy_u8PinNum % 8U))); break ;
			 case GPIOB_PORT  : MGPIOB->AFRH |=(u32)(Copy_u8ALF <<(4U* (Copy_u8PinNum % 8U ))); break ;
			 case GPIOC_PORT  : MGPIOC->AFRH |=(u32)(Copy_u8ALF <<(4U* (Copy_u8PinNum % 8U))); break ;
			 case GPIOD_PORT  : MGPIOD->AFRH |=(u32)(Copy_u8ALF <<(4U* (Copy_u8PinNum % 8U ))); break ;
			 case GPIOE_PORT  : MGPIOE->AFRH |=(u32)(Copy_u8ALF <<(4U* (Copy_u8PinNum % 8U ))); break ;
			 case GPIOH_PORT  : MGPIOH->AFRH |=(u32)(Copy_u8ALF <<(4U* (Copy_u8PinNum % 8U))); break ;
			 default : break ;
		}	
		
		
	}

	
}

/*#####################################################################################################*/
/*                                              END OF FUNCTIONS                                       */
/*#####################################################################################################*/

