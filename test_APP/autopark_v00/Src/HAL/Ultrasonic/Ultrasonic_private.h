/*
 * Ultrasonic_private.h
 *
 *  Created on: Apr 23, 2024
 *      Author: LENOVO
 */

#ifndef HAL_ULTRASONIC_ULTRASONIC_PRIVATE_H_
#define HAL_ULTRASONIC_ULTRASONIC_PRIVATE_H_

/*******************************************************************************************************/
/*                                      Standard Types LIB                                             */
/*******************************************************************************************************/
#include "../../Libraries/STD_TYPES.h"

/*#####################################################################################################*/
/*#####################################################################################################*/


typedef struct{
	volatile u32 UltraS_Trigger_port;
	volatile u32 UltraS_Trigger_Pin;
}UltraSX_t;





#endif /* HAL_ULTRASONIC_ULTRASONIC_PRIVATE_H_ */
