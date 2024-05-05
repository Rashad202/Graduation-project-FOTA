/*******************************************************************************************************/
/* Author            : GP_FOTA_TEAM                    			                                       */
/* Version           : V0.0.0                                                                          */
/* Data              : 23 Apr 2024                                                                     */
/* Description       : MotorDriver_Program.c --> implementations                                       */
/*******************************************************************************************************/

#ifndef HAL_MOTORDRIVER_MOTORDRIVER_CONFIG_H_
#define HAL_MOTORDRIVER_MOTORDRIVER_CONFIG_H_

/*******************************************************************************************************/
/*                                      MCAL Components                                                */
/*******************************************************************************************************/
#include "../../MCAL/MGPIO/MGPIO_interface.h"
#include "../../MCAL/MTIMER/MTIMER_interface.h"

/*******************************************************************************************************/
/*                                      HAL Components                                                 */
/*******************************************************************************************************/
#include "MotorDriver_private.h"

/*******************************************************************************************************/
/*******************************************************************************************************/


static const MotorX_t Motor_1 ={
		GPIOB_PORT,
		PIN_12,
		GPIOB_PORT,
		PIN_13,
		TIMER4,
		CH1,
};


#endif /* HAL_MOTORDRIVER_MOTORDRIVER_CONFIG_H_ */