/*******************************************************************************************************/
/* Author            : GP_FOTA_TEAM                                                                    */
/* Version           : V0.0.0                                                                          */
/* Data              : 10 Feb 2024                                                                      */
/* Description       : BootLoader_config.h --> Configuration                                            */
/*******************************************************************************************************/

#ifndef APP_BOOTLOADER_BOOTLOADER_CONFIG_H_
#define APP_BOOTLOADER_BOOTLOADER_CONFIG_H_

/*   Macros Base Address Of the APPs and flags  */
#define APP_1_BASE_ADD 		SECTOR_4_BASE_ADD
#define APP_2_BASE_ADD 		SECTOR_5_BASE_ADD

#define APP_1_2_FLAG_ADD	SECTOR_3_BASE_ADD

/*   Macros for the used communication  */
#define USART_COMM	1
#define CAN_COMM	2

#define BL_communication	USART_COMM

/*   Macros for the debugging  */
#define	BL_IMT_DEBUGGING		DISABLE


#endif /* APP_BOOTLOADER_BOOTLOADER_CONFIG_H_ */
