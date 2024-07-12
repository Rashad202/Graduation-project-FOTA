/*******************************************************************************************************/
/* Author            : Mohamed Samy Mohamed                                                            */
/* Version           : V0.0.0                                                                          */
/* Data              : 16 Dec 2023                                                                     */
/* Description       : BUZZER_Program.c --> implementations                                               */
/* Module  Features  :                                                                                 */
/*      01- BUZZER_Init                                                                    			   */
/*      02- BUZZER_DeInit                                                                 				   */
/*      03- BUZZER_On                                                                  				   */
/*      04- BUZZER_Off                                                                      			   */
/*      05- BUZZER_Toggle                                                                                 */
/*******************************************************************************************************/


/*******************************************************************************************************/
/*                                      HAL Components                                                 */
/*******************************************************************************************************/
#include "BUZZER_interface.h"

/*#####################################################################################################*/
/*#####################################################################################################*/

/*******************************************************************************************************/
/*                                      Functions Implementations                                      */
/*******************************************************************************************************/

/*#####################################################################################################*/
/*#####################################################################################################*/


/*******************************************************************************************************/
/*                                      01- BUZZER_Init                               			           */
/*-----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Function Set The Mode Of Pin Output Take BUZZER structure                   */
/*                                                                                                     */
/* 2- Function Input       -> BUZZERX_t *BUZZER 									                           */
/* 3- Function Return      -> No Thing                                                                 */
/*******************************************************************************************************/
void BUZZER_Init(const BUZZERX_t *BUZZER){

	MGPIO_voidSetPinMode(BUZZER->BUZZER_port,BUZZER->BUZZER_Pin,MODE_OUTPUT);

}


/*******************************************************************************************************/
/*                                      02- BUZZER_DeInit                               			       */
/*-----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Function turn the BUZZER of #####(need to lock this pin also)######         */
/*                                                                                                     */
/* 2- Function Input       -> BUZZERX_t *BUZZER 									                           */
/* 3- Function Return      -> No Thing                                                                 */
/*******************************************************************************************************/
void BUZZER_DeInit(const BUZZERX_t *BUZZER){

	BUZZER_Off(BUZZER);

}


/*******************************************************************************************************/
/*                                      03- BUZZER_On                               			     	   */
/*-----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Function turn on the BUZZER       									  	   */
/*                                                                                                     */
/* 2- Function Input       -> BUZZERX_t *BUZZER 									                           */
/* 3- Function Return      -> No Thing                                                                 */
/*******************************************************************************************************/
void BUZZER_On(const BUZZERX_t *BUZZER){

	MGPIO_voidWriteData(BUZZER->BUZZER_port,BUZZER->BUZZER_Pin,HIGH);

}


/*******************************************************************************************************/
/*                                      04- BUZZER_Off                               			     	   */
/*-----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Function turn off the BUZZER       									  	   */
/*                                                                                                     */
/* 2- Function Input       -> BUZZERX_t *BUZZER 									                           */
/* 3- Function Return      -> No Thing                                                                 */
/*******************************************************************************************************/
void BUZZER_Off(const BUZZERX_t *BUZZER){

	MGPIO_voidWriteData(BUZZER->BUZZER_port,BUZZER->BUZZER_Pin,LOW);

}


/*******************************************************************************************************/
/*                                      05- BUZZER_Toggle                               			       */
/*-----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Function toggle the BUZZER condition      								   */
/*                                                                                                     */
/* 2- Function Input       -> BUZZERX_t *BUZZER 									                           */
/* 3- Function Return      -> No Thing                                                                 */
/*******************************************************************************************************/
void BUZZER_Toggle	(const BUZZERX_t *BUZZER){

	MGPIO_voidToggBUZZERata(BUZZER->BUZZER_port,BUZZER->BUZZER_Pin);

}

void BUZZER_vibrat_2s	(const BUZZERX_t *BUZZER){

	for(u8 i=0;i<10;i++){
		BUZZER_Toggle(&BUZZER);
		_delay_ms(200);
	}
	BUZZER_Off(&BUZZER);

}
/*#####################################################################################################*/
/*                                              END OF FUNCTIONS                                       */
/*#####################################################################################################*/
