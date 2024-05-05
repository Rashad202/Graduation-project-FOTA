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


/*******************************************************************************************************/
/*                                      MCAL-HAL Components                                            */
/*******************************************************************************************************/

//#include "../../Libraries/BIT_MATH.h"

#include "../../MCAL/MGPIO/MGPIO_interface.h"
#include "../../MCAL/MGPIO/MGPIO_Config.h"
#include "../../MCAL/MTIMER/MTIMER_interface.h"
#include "../../MCAL/MEXTI/MEXTI_interface.h"
#include "../../MCAL/MNVIC/MNVIC_interface.h"
#include "../../MCAL/MSTK/MSYSTICK_interface.h"

#include "MotorDriver_interface.h"

/*******************************************************************************************************/
/*                                      Functions Implementations                                      */
/*******************************************************************************************************/


/*******************************************************************************************************/
/*                                      01- HAL_MOTOR_Init                               			   */
/*-----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> ***                  													   */
/*                                                                                                     */
/* 2- Function Input       -> *** 									                   				   */
/* 3- Function Return      -> No Thing                                                                 */
/*******************************************************************************************************/
void HAL_MOTOR_Init(const MotorX_t *Motor){
	MRCC_voidEnablePeripheralClock(AHB1_BUS, Motor->Motor_Port_1);
	MRCC_voidEnablePeripheralClock(AHB1_BUS, Motor->Motor_Port_2);
	MGPIO_voidSetPinMode(Motor->Motor_Port_1,Motor->Motor_Pin_1, MODE_OUTPUT);
	MGPIO_voidSetPinMode(Motor->Motor_Port_2,Motor->Motor_Pin_2, MODE_OUTPUT);

	if(Motor->Motor_Timer==TIMER4){
		MRCC_voidEnablePeripheralClock(AHB1_BUS, PERIPHERAL_EN_GPIOB);
		MRCC_voidEnablePeripheralClock(APB1_BUS, PERIPHERAL_EN_TIM4) ;
		MTIMER_vStartTime(TIMER4);
	}
	else{
		//
	}
}

/*******************************************************************************************************/
/*                                      02- HAL_MOTOR_MOVE                               			   */
/*-----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> ***                  													   */
/*                                                                                                     */
/* 2- Function Input       -> *** 									                   				   */
/* 3- Function Return      -> No Thing                                                                 */
/*******************************************************************************************************/
void HAL_MOTOR_MOVE(const MotorX_t *Motor ,u8 DIRCTION ,u8 SPEED){

	switch(DIRCTION){
	case BACKWARD :
		MGPIO_voidWriteData(Motor->Motor_Port_1,Motor->Motor_Pin_1, HIGH);
		MGPIO_voidWriteData(Motor->Motor_Port_2,Motor->Motor_Pin_2, LOW);
		break;
	case FORWARD:
		MGPIO_voidWriteData(Motor->Motor_Port_1,Motor->Motor_Pin_1, LOW);
		MGPIO_voidWriteData(Motor->Motor_Port_2,Motor->Motor_Pin_2, HIGH);
		break;
	case STOP:
		MGPIO_voidWriteData(Motor->Motor_Port_1,Motor->Motor_Pin_1, LOW);
		MGPIO_voidWriteData(Motor->Motor_Port_2,Motor->Motor_Pin_2, LOW);
		SPEED=0;
		break;
	}

	MTIMER_vPWM(Motor->Motor_Timer, Motor->Motor_Chanel, 100, SPEED);

}
/*******************************************************************************************************/
/*                                      03- HAL_MOTOR_STOP                               			   */
/*-----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> ***                  													   */
/*                                                                                                     */
/* 2- Function Input       -> *** 									                   				   */
/* 3- Function Return      -> No Thing                                                                 */
/*******************************************************************************************************/
void HAL_MOTOR_STOP(const MotorX_t *Motor){
	MGPIO_voidWriteData(Motor->Motor_Port_1,Motor->Motor_Pin_1, LOW);
	MGPIO_voidWriteData(Motor->Motor_Port_2,Motor->Motor_Pin_2, LOW);
}


/*#####################################################################################################*/
/*                                              END OF FUNCTIONS                                       */
/*#####################################################################################################*/
