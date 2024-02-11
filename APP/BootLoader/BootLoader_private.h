/*******************************************************************************************************/
/* Author            : GP_FOTA_TEAM                                                                    */
/* Version           : V0.0.0                                                                          */
/* Data              : 10 Feb 2024                                                                     */
/* Description       : BootLoader_private.h --> implementations                                        */
/*******************************************************************************************************/
/*                                   guard of file will call on time in .c                             */
#ifndef APP_BOOTLOADER_BOOTLOADER_PRIVATE_H_
#define APP_BOOTLOADER_BOOTLOADER_PRIVATE_H_

/*   Macros Base Address Of the sectors   */
#define SECTOR_0_BASE_ADD 0x08000000
#define SECTOR_1_BASE_ADD 0x08004000
#define SECTOR_2_BASE_ADD 0x08008000
#define SECTOR_3_BASE_ADD 0x0800C000
#define SECTOR_4_BASE_ADD 0x08010000
#define SECTOR_5_BASE_ADD 0x08020000

/*   Macros Base Address Of the APPs   */
#define APP_1_BASE_ADD SECTOR_5_BASE_ADD
#define APP_2_BASE_ADD SECTOR_3_BASE_ADD

/*   Macros Base Address Of the APPs Version  */
#define APP_1_Version_ADD	*((volatile u32 *)(SECTOR_2_BASE_ADD))
#define APP_2_Version_ADD	*((volatile u32 *)(SECTOR_2_BASE_ADD + 0x0010))

#endif /* APP_BOOTLOADER_BOOTLOADER_PRIVATE_H_ */
