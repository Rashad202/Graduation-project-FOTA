/*******************************************************************************************************/
/* Author            : Mohamed Samy Mohamed                                                            */
/* Version           : V0.0.0                                                                          */
/* Data              : 16 Dec 2023                                                                     */
/* Description       : LED_interface.h --> implementations                                             */
/* Module  Features  :                                                                                 */
/*      01- LED_Init                                                                    			   */
/*      02- LED_DeInit                                                                 				   */
/*      03- LED_On                                                                  				   */
/*      04- LED_Off                                                                      			   */
/*      05- Led_Toggle                                                                                 */
/*******************************************************************************************************/

#ifndef HAL_PUSHB_PUSHB_INTERFACE_H_
#define HAL_PUSHB_PUSHB_INTERFACE_H_

/*******************************************************************************************************/
/*                                      Standard Types LIB                                             */
/*******************************************************************************************************/
#include "../../Libraries/STD_TYPES.h"
//#include "LERROR_STATES.h"
#include "../../Libraries/BIT_MATH.h"

/*#####################################################################################################*/
/*#####################################################################################################*/

/*******************************************************************************************************/
/*                                      HAL Components                                                 */
/*******************************************************************************************************/
#include "../../MGPIO/MGPIO_interface.h"
#include "../../MRCC/MRCC_interface.h"
#include "PushB_private.h"
#include "PushB_Config.h"

/*******************************************************************************************************/
/*                                      Macros Of Status                                               */
/*******************************************************************************************************/

#define _BUTTON_NOT_PRESSED   	0U
#define _BUTTON_PRESSED   		1U


/*Function To initialize LED port and pin */
void PushB_Init	(const PushBX_t *PushB);


/*Function To Disable LED */
void PushB_DeInit	(const PushBX_t *PushB);


/*Function To turn LED on */
u8 	 PushB_Read		(const PushBX_t *PushB);



#endif /* HAL_LED_LED_H_ */
