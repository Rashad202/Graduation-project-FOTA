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


#define SECTOR_0	0
#define SECTOR_1	1
#define SECTOR_2	2
#define SECTOR_3	3
#define SECTOR_4	4
#define SECTOR_5	5
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
