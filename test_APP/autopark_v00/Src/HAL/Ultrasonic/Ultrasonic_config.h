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


static const UltraSX_t UltraS_t_1 ={
		GPIOA_PORT,
		PIN_8

};

/*******************************************************************************************************/
/*******************************************************************************************************/







#endif /* HAL_ULTRASONIC_ULTRASONIC_CONFIG_H_ */
