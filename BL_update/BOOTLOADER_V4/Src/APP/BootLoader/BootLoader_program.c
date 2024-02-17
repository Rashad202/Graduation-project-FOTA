/*******************************************************************************************************/
/* Author            : GP_FOTA_TEAM                                                                    */
/* Version           : V0.0.0                                                                          */
/* Data              : 10 Feb 2024                                                                     */
/* Description       : HexParser_private.h --> implementations                                         */
/*******************************************************************************************************/

/*******************************************************************************************************/
/*                                      Standard Types LIB                                             */
#include "../../Libraries/STD_TYPES.h"
#include "../../Libraries/BIT_MATH.h"
/*******************************************************************************************************/
/*                                      APP Components                                                 */
#include "BootLoader_private.h"
#include "BootLoader_config.h"
#include "BootLoader_interface.h"

#include "../HexParser/HexParser_interface.h"
/*******************************************************************************************************/
/*                                      MCAL Components                                                */
#include "../../MCAL/MFMI/MFMI_interface.h"
/*******************************************************************************************************/
/*                                      Variables                           	                       */

/*******************************************************************************************************/
/*                                      Functions Implementations                                      */
void BL_voidJumpToAPP_1(void){
	/*	stack pointer	*/
	*((volatile u32 *)0xE000ED08)=APP_1_BASE_ADD;
	/*	Reset Handler function	*/
	u32 main_APP_1= *((volatile u32*)(APP_1_BASE_ADD+4));
	void (*A1_resetHandler_Address)(void) = (void *)main_APP_1;
	A1_resetHandler_Address();
}

void BL_voidJumpToAPP_2(void){
	/*	stack pointer	*/
	*((volatile u32 *)0xE000ED08)=APP_2_BASE_ADD;
	u32 main_APP_2= *((volatile u32*)(APP_2_BASE_ADD+4));
	/*	Reset Handler function	*/
	void (*A2_resetHandler_Address)(void) = (void *)main_APP_2;
	A2_resetHandler_Address();
}
