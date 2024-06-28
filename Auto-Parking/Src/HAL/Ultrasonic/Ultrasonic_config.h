/*******************************************************************************************************/
/* Author            : GP_FOTA_TEAM                                                                    */
/* Version           : V0.0.0                                                                          */
/* Data              : 13 Apr 2024                                                                     */
/* Description       : HULTRA_SONIC_Config.h --> implementations                                       */
/********************************************************************************************************/
#ifndef HAL_ULTRASONIC_ULTRASONIC_CONFIG_H_
#define HAL_ULTRASONIC_ULTRASONIC_CONFIG_H_


//Macros for Trigger pulse width in msec
#define	Trigger_Pulse_Width	20
//Number of ULtrasonic to be used 
#define TOT_ULTRA_SONIC_NUM	6

/*******************************************************************************************************/
/*                                      MCAL Components                                                */
#include "../../MCAL/MGPIO/MGPIO_interface.h"

/*******************************************************************************************************/
/*                                      HAL Components                                                 */
#include "Ultrasonic_private.h"
/*******************************************************************************************************/
//Forward and Backward triger
static const UltraSX_t UltraS_t_F_B ={
		GPIOA_PORT,
		PIN_8

};
/*static const UltraSX_t UltraS_t_F ={
		GPIOB_PORT,
		PIN_15

};*/



/*******************************************************************************************************/
/*******************************************************************************************************/







#endif /* HAL_ULTRASONIC_ULTRASONIC_CONFIG_H_ */
