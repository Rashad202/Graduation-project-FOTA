/*******************************************************************************************************/
/* Author            : Mohamed Samy Mohamed                                                            */
/* Version           : V0.0.0                                                                          */
/* Data              : 16 Dec 2023                                                                     */
/* Description       : LED_Config.h --> implementations                                                */
/* Features          : LEDs Configuration                                                              */
/*******************************************************************************************************/

#ifndef HAL_LED_LED_CONFIG_H_
#define HAL_LED_LED_CONFIG_H_


/*******************************************************************************************************/
/*                                      MCAL Components                                                */
/*******************************************************************************************************/
#include "../../MCAL/MGPIO/MGPIO_interface.h"

/*******************************************************************************************************/
/*******************************************************************************************************/


/*******************************************************************************************************/
/*                                      HAL Components                                                 */
/*******************************************************************************************************/
#include "LED_private.h"

/*******************************************************************************************************/
/*******************************************************************************************************/


/*******************************************************************************************************/
/*                                       LEDs Configuration                                       	   */
/*-----------------------------------------------------------------------------------------------------*/
/*     - Developer can Edit in it                                                                      */
/*     - LEDs _ Defination: Port name and Pin name		                                               */
/*     - Design :                                                                                      */
/*    				- #define	:	NO                                                                 */
/*    				- Union		:	NO                                                                 */
/*    				- Struct	:	YES                                                                */
/*                                                                                                     */
/*******************************************************************************************************/
static const LedX_t Led_0 ={
		GPIOC_PORT,
		PIN_13
};


static const LedX_t Led_1 ={
		GPIOA_PORT,
		PIN_1
};
static const LedX_t Led_2 ={
		GPIOA_PORT,
		PIN_2
};
static const LedX_t Led_3 ={
		GPIOA_PORT,
		PIN_3
};

 /* HAL_LED_LED_CONFG_H_ */
#endif
