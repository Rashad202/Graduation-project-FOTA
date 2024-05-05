/*******************************************************************************************************/
/* Author            : GP_FOTA_TEAM                    			                                       */
/* Version           : V0.0.0                                                                          */
/* Data              : 23 Apr 2024                                                                     */
/* Description       : MotorDriver_Program.c --> implementations                                       */
/* Module  Features  :                                                                                 */
/*      01- HAL_MOTOR_Init                                                                    		   */
/*      02- HAL_MOTOR_MOVE                                                                 			   */
/*      03- HAL_MOTOR_STOP                                                                  		   */
/*******************************************************************************************************/

#ifndef HAL_MOTOR_H_
#define HAL_MOTOR_H_



/*******************************************************************************************************/
/*                                      Standard Types LIB 					                           */
/*******************************************************************************************************/
#include "../../Libraries/STD_TYPES.h"

/*******************************************************************************************************/
/*                                      MCAL Components                                                */
/*******************************************************************************************************/
#include "../../MCAL/MTIMER/MTIMER_interface.h"

/*******************************************************************************************************/
/*                                      HAL Components                                                 */
/*******************************************************************************************************/
//#include "../../MCAL/MGPIO/MGPIO_interface.h"
#include "../../MCAL/MRCC/MRCC_interface.h"
#include "MotorDriver_private.h"
#include "MotorDriver_Config.h"

/*******************************************************************************************************/
/*                                      defines                      		                           */
/*******************************************************************************************************/
#define STOP 	  0
#define FORWARD   1
#define BACKWARD  2
/*******************************************************************************************************/

/*Function To initialize Motor port , pin ,timer and channel */
void HAL_MOTOR_Init(const MotorX_t *Motor);
/*Function To move the motor */
void HAL_MOTOR_MOVE(const MotorX_t *Motor ,u8 DIRCTION ,u8 SPEED);
/*Function To stop the motor */
void HAL_MOTOR_STOP(const MotorX_t *Motor);





#endif /*HAL_MOTOR_H_*/
