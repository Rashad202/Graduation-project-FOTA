/*******************************************************************************************************/
/* Author            : Mohamed Samy Mohamed                                                            */
/* Version           : V0.0.0                                                                          */
/* Data              : 16 Dec 2023                                                                     */
/* Description       : BUZZER_interface.h --> implementations                                             */
/* Module  Features  :                                                                                 */
/*      01- BUZZER_Init                                                                    			   */
/*      02- BUZZER_DeInit                                                                 				   */
/*      03- BUZZER_On                                                                  				   */
/*      04- BUZZER_Off                                                                      			   */
/*      05- BUZZER_Toggle                                                                                 */
/*******************************************************************************************************/

#ifndef HAL_BUZZER_BUZZER_H_
#define HAL_BUZZER_BUZZER_H_

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
#include "../../MCAL/MGPIO/MGPIO_interface.h"
#include "../../MCAL/MRCC/MRCC_interface.h"
#include "BUZZER_Config.h"
#include "BUZZER_private.h"


/*Function To initialize BUZZER port and pin */
void BUZZER_Init	(const BUZZERX_t *BUZZER);


/*Function To Disable BUZZER */
void BUZZER_DeInit	(const BUZZERX_t *BUZZER);


/*Function To turn BUZZER on */
void BUZZER_On		(const BUZZERX_t *BUZZER);


/*Function To turn BUZZER off */
void BUZZER_Off	(const BUZZERX_t *BUZZER);

/*Function To toggle BUZZER  */
void BUZZER_Toggle	(const BUZZERX_t *BUZZER);


#endif /* HAL_BUZZER_BUZZER_H_ */
