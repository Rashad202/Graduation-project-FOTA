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

#ifndef HAL_LED_LED_H_
#define HAL_LED_LED_H_

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
#include "LED_private.h"
#include "LED_Config.h"


/*Function To initialize LED port and pin */
void LED_Init	(const LedX_t *LED);


/*Function To Disable LED */
void LED_DeInit	(const LedX_t *LED);


/*Function To turn LED on */
void LED_On		(const LedX_t *LED);


/*Function To turn LED off */
void LED_Off	(const LedX_t *LED);

/*Function To toggle LED  */
void Led_Toggle	(const LedX_t *LED);


#endif /* HAL_LED_LED_H_ */
