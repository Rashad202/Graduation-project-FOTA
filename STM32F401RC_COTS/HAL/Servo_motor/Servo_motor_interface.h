/*******************************************************************************************************/
/* Author            : GP_FOTA_TEAM                                                                    */
/* Version           : V1.0.3                                                                          */
/* Data              : 28 Dec 2023                                                                     */
/* Description       : HSERVO_Interface.h --> implementations                                          */
/* Module  Features  :                                                                                 */
/*      01- HSERVO_vServoInit                                                                          */
/*      02- HSERVO_vServoDeg                                                                           */
/*******************************************************************************************************/

/*******************************************************************************************************/
/*                                   guard of file will call on time in .c                             */
/*******************************************************************************************************/
#ifndef HAL_SERVO_MOTOR_SERVO_MOTOR_INTERFACE_H_
#define HAL_SERVO_MOTOR_SERVO_MOTOR_INTERFACE_H_

/*******************************************************************************************************/
/*                                    Include files needed for HSERVO_Int.h 		                   */
/*******************************************************************************************************/
#include"../../Libraries/STD_TYPES.h" //Standard Types Lib
#include "../../MCAL/MTIMER/MTIMER_interface.h" // TIMER (Timer Control)

/*******************************************************************************************************/
/*                                      defines                      		                           */
/*******************************************************************************************************/
#define NO_TURN 82
//#define LEFT    65
#define LEFT    65
//#define RIGHT  	105
#define RIGHT  	100

/*******************************************************************************************************/
/*                                          APIs                                                       */
/*******************************************************************************************************/

/*******************************************************************************************************/
/*                                      01- HSERVO_vServoInit                                          */
/*-----------------------------------------------------------------------------------------------------*/
/**
 * @note This function configures the specified TIMER and channel to generate PWM signals suitable for
 * 		 servo control.Ensure that the corresponding timer and channel are available for servo control
 * 		 on the selected microcontroller.
 *       Additionally, adjust the servo-specific parameters, such as PWM frequency and duty cycle,
 *        based on servo specifications.
 */
void HSERVO_vServoInit(u8 Copy_u8TimerNum,u8 Copy_u8ChannelNum);
/******************************************************************************************************/

/******************************************************************************************************/
/*                                      01- HSERVO_vServoDeg                                          */
/*----------------------------------------------------------------------------------------------------*/
/**
 * @note This function adjusts the PWM signal sent to the specified servo motor to achieve the desired angle.
 *       Ensure that the servo motor is initialized using HSERVO_vServoInit before calling this function.
 *       Additionally, consider the servo motor specifications and adjust the PWM signal parameters accordingly.
 *       PWM signal:	20msec FullTime		(0.5 => 2.5msec) Duty Cycle for 0 to 180 Deg.
 */
void HSERVO_vServoDeg(u8 Copy_s8Deg);
/******************************************************************************************************/

#endif /* HAL_SERVO_MOTOR_SERVO_MOTOR_INTERFACE_H_ */
