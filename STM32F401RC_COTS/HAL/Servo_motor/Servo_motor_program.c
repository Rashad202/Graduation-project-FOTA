/*******************************************************************************************************/
/* Author            : GP_FOTA_TEAM                                                                    */
/* Version           : V1.0.3                                                                          */
/* Data              : 28 Dec 2023                                                                     */
/* Description       : HSERVO_Prog.c --> implementations                                          */
/* Module  Features  :                                                                                 */
/*      01- HSERVO_vServoInit                                                                          */
/*      02- HSERVO_vServoDeg                                                                           */
/*******************************************************************************************************/
// Include necessary MCU Abstraction Layer (MCAL) headers
#include "../../MCAL/MTIMER/MTIMER_interface.h" // TIMER (Timer Control)

// Include HSERVO configuration and interface headers
#include "Servo_motor_config.h"
#include "Servo_motor_interface.h"

// Declare an array to store servo information for multiple servos
LOC_SERVO_channel=0 ;
LOC_SERVO_Timer=0 ;


void HSERVO_vServoInit(u8 Copy_u8TimerNum,u8 Copy_u8ChannelNum){
	MTIMER_vStartTime(Copy_u8TimerNum);

	LOC_SERVO_Timer=Copy_u8TimerNum;
	LOC_SERVO_channel=Copy_u8ChannelNum;

}

/**
 * @brief Sets the angle of the servo motor specified by Copy_u8ServoNum to the desired degree.
 *
 * @param Copy_u8ServoNum: Enum_SERVO_NUM representing the servo number.
 * @param Copy_s8Deg: Desired angle in degrees (from -45 to 45).
 */
void HSERVO_vServoDeg( u8 Copy_s8Deg) {
	// Calculate the positive duty cycle corresponding to the desired angle
	u16 Positive_Duty = (100/9)*Copy_s8Deg + 500;
	// Set the PWM signal to control the servo motor
	MTIMER_vPWM(LOC_SERVO_Timer, LOC_SERVO_channel, SERVO_FullPeriod, Positive_Duty);

}




