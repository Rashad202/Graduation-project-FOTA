/*******************************************************************************************************/
/* Author            : Mohamed Samy Mohamed                                                            */
/* Version           : V0.0.0                                                                          */
/* Data              : 16 Dec 2023                                                                     */
/* Description       : BUZZER_Config.h --> implementations                                                */
/* Features          : BUZZERs Configuration                                                              */
/*******************************************************************************************************/

#ifndef HAL_BUZZER_BUZZER_CONFIG_H_
#define HAL_BUZZER_BUZZER_CONFIG_H_


/*******************************************************************************************************/
/*                                      MCAL Components                                                */
/*******************************************************************************************************/
#include "../../MCAL/MGPIO/MGPIO_interface.h"

/*******************************************************************************************************/
/*******************************************************************************************************/


/*******************************************************************************************************/
/*                                      HAL Components                                                 */
/*******************************************************************************************************/
#include "BUZZER_private.h"

/*******************************************************************************************************/
/*******************************************************************************************************/


/*******************************************************************************************************/
/*                                       BUZZERs Configuration                                       	   */
/*-----------------------------------------------------------------------------------------------------*/
/*     - Developer can Edit in it                                                                      */
/*     - BUZZERs _ Defination: Port name and Pin name		                                               */
/*     - Design :                                                                                      */
/*    				- #define	:	NO                                                                 */
/*    				- Union		:	NO                                                                 */
/*    				- Struct	:	YES                                                                */
/*                                                                                                     */
/*******************************************************************************************************/
static const BUZZERX_t BUZZER_1 ={
		GPIOA_PORT,
		PIN_0
};



 /* HAL_BUZZER_BUZZER_CONFG_H_ */
#endif