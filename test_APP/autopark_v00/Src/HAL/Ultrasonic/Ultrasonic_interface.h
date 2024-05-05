/*******************************************************************************************************/
/* Author            : GP_FOTA_TEAM                                                                    */
/* Version           : V0.0.0                                                                          */
/* Data              : 13 Apr 2024                                                                     */
/* Description       : HULTRA_SONIC_Int.h --> implementations                                          */
/* Module  Features  :																					*/
/* @Functions:																							*/
/*      01- HULTRA_vInitialize                                                                          */
/*      02- HULTRA_vSendTrigger                                                                         */
/*      03- HULTRA_vGetDistance																			*/
/* @TypeDef:																							*/
/* 		@Enums:																							*/
/* 	    	 01- Enum_ULTRA_SONIC_NUM                                                        			*/
/********************************************************************************************************/


/*******************************************************************************************************/
/*                                   guard of file will call on time in .c                             */
/*******************************************************************************************************/

#ifndef HAL_ULTRASONIC_ULTRASONIC_INTERFACE_H_
#define HAL_ULTRASONIC_ULTRASONIC_INTERFACE_H_

/*******************************************************************************************************/
/*                                    Include files needed for HULTRA_SONIC_Int.h 		               */
/*******************************************************************************************************/
#include"../../Libraries/STD_TYPES.h" //Standard Types Lib
#include "../../MCAL/MTIMER/MTIMER_interface.h" // TIMER (Timer Control)
/*******************************************************************************************************/
/*                                      HAL Components                                                 */
/*******************************************************************************************************/
#include "../../MCAL/MGPIO/MGPIO_interface.h"
#include "../../MCAL/MRCC/MRCC_interface.h"
#include "Ultrasonic_private.h"
#include "Ultrasonic_config.h""
/********************************************************************************************************/
/*                                     Enum for ULTRASONIC Numbering        		                    */
/********************************************************************************************************/
typedef	enum{
	ULTRA_SONIC1,ULTRA_SONIC2,ULTRA_SONIC3,
    ULTRA_SONIC4,ULTRA_SONIC5,ULTRA_SONIC6
}Enum_ULTRA_SONIC_NUM;




/******************************************************************************************************/
/*                                          APIs                                                      */
/******************************************************************************************************/

/******************************************************************************************************/
/*                                      01- HULTRA_vInitialize                                        */
/*----------------------------------------------------------------------------------------------------*/
/**
 * @Description  Initialize ultrasonic sensor parameters including GPIO and timer configurations.
 * 
 * @return	void
 * 
 * @note    This function sets up the GPIO pins and configures the specified timer for ultrasonic sensor interfacing.
 *          The ultrasonic sensor parameters are stored in the ULTRA_NUM array based on the timer and channel numbers.
 */
void HULTRA_vInitialize(Enum_ULTRA_SONIC_NUM Copy_u8Ultra_NUM,Enum_TIMER_NUM Copy_u8TimerNum, u8 Copy_u8ChannelNum);
/******************************************************************************************************/

/******************************************************************************************************/
/*                                      02- HULTRA_vSendTrigger                                       */
/*----------------------------------------------------------------------------------------------------*/
/**
 * @Description   Send a trigger signal to an ultrasonic sensor.
 * 
 * @return	void
 *
 * @note    This function sets the specified pin as an OUTPUT, raises it to HIGH for a short duration,
 *          then brings it back to LOW. It is typically used to initiate distance measurements in ultrasonic sensors.
 */
void HULTRA_vSendTrigger(const UltraSX_t *UltraS);
/******************************************************************************************************/

/******************************************************************************************************/
/*                                      03- HULTRA_vGetDistance                                       */
/*----------------------------------------------------------------------------------------------------*/
/**
 * @Description   Get the distance measurement from an ultrasonic sensor.
 * 
 * @return	void
 *
 * @note    This function calculates the distance based on the input from a specified timer channel.
 *          The calculated distance is stored in the variable pointed to by Copy_f64Distance.
 *          The formula used for the calculation assumes a speed of sound of 343 meters per second.
 *          The timer values are expected to represent the time taken for the ultrasonic signal to travel
 *          to an object and back, divided by 2 to get the one-way distance.
 */
void HULTRA_vGetDistance(Enum_ULTRA_SONIC_NUM Copy_u8Ultra_NUM,f64* Copy_f64Distance);

/******************************************************************************************************/

#endif /* HAL_ULTRASONIC_ULTRASONIC_INTERFACE_H_ */
