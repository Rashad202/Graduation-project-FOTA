/*******************************************************************************************************/
/* Author            : GP_FOTA_TEAM                                                                    */
/* Version           : V0.0.0                                                                          */
/* Data              : 10 Feb 2024                                                                     */
/* Description       : BootLoader_interface.h --> implementations                                      */
/* Module  Features  :                                                                                 */
/*      01- HexParser_voidParseData                                                                    */
/*******************************************************************************************************/

/*******************************************************************************************************/
/*                                   guard of file will call on time in .c                             */
#ifndef APP_BOOTLOADER_BOOTLOADER_INTERFACE_H_
#define APP_BOOTLOADER_BOOTLOADER_INTERFACE_H_

/*******************************************************************************************************/
/*                                      MCAL Components                                                */
#include "BootLoader_config.h"

#define APP_FLAG_ADD	 APP_1_2_FLAG_ADD
#define UpDate_Flag	     *((volatile u32 *)(APP_FLAG_ADD))

#define No_APP 		0xFFFFFFFF
#define APP_1_ID	0xAAAA
#define APP_2_ID	0xBBBB

#define APP_1_MID	0xFFFFAAAA
#define APP_2_MID	0xFFFFBBBB

/*******************************************************************************************************/
/*                                      Function Prototypes                                            */
/*******************************************************************************************************/
/*******************************************************************************************************/
/*                                      00- BL_voidJumpToAPP_1                                	       */
/*-----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> jump from the bootloader to application one (to its base address)			*/
/* 2- Function Input       -> none											               			   */
/* 3- Function Return      -> none                                                           		   */
/*******************************************************************************************************/
void BL_voidJumpToAPP_1(void);
/*******************************************************************************************************/
/*                                      01- BL_voidJumpToAPP_2                                	       */
/*-----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> jump from the bootloader to application two (to its base address)		   */
/* 2- Function Input       -> none													                   */
/* 3- Function Return      -> none                                                           		   */
/*******************************************************************************************************/
void BL_voidJumpToAPP_2(void);


#endif /* APP_BOOTLOADER_BOOTLOADER_INTERFACE_H_ */
