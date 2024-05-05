/*******************************************************************************************************/
/* Author            : GP_FOTA_TEAM                    			                                       */
/* Version           : V0.0.0                                                                          */
/* Data              : 23 Apr 2024                                                                     */
/* Description       : MotorDriver_Program.c --> implementations                                       */
/*******************************************************************************************************/


#ifndef HAL_MOTORDRIVER_MOTORDRIVER_PRIVATE_H_
#define HAL_MOTORDRIVER_MOTORDRIVER_PRIVATE_H_

/*******************************************************************************************************/
/*                                      Standard Types LIB                                             */
/*******************************************************************************************************/
#include "../../Libraries/STD_TYPES.h"

/*#####################################################################################################*/
/*#####################################################################################################*/


typedef struct{
	volatile u32 Motor_Port_1;
	volatile u32 Motor_Pin_1;
	volatile u32 Motor_Port_2;
	volatile u32 Motor_Pin_2;
	volatile u32 Motor_Timer;
	volatile u32 Motor_Chanel;
}MotorX_t;


#endif /* HAL_MOTORDRIVER_MOTORDRIVER_PRIVATE_H_ */
