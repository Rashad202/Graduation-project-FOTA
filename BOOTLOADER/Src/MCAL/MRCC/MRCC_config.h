/*******************************************************************************************************/
/* Author            : GP_FOTA_TEAM                                                                    */
/* Version           : V0.0.0                                                                          */
/* Data              : 15 Dec 2023                                                                     */
/* Description       : MRCC_Config.h --> Configuration                                                 */
/*******************************************************************************************************/

/*******************************************************************************************************/
/*                                   guard of file will call on time in .c                             */
/*******************************************************************************************************/

#ifndef RCC_CONFIG_H
#define RCC_CONFIG_H

/*******************************************************************************************************/
/*
	- CLKSRC option :
			         1) HSI
			         2) HSE
			         3) PLL
*/
#define CLKSRC  HSI
/*******************************************************************************************************/
/*
   - HSE option :
                 1)_HSE_CRYSTAL
                 2)_HSE_RC
*/
#define HSE_SRC  HSE_CRYSTAL
/*******************************************************************************************************/
/*
   - PLL option :
	            1) _HSE_PLL
                2) _HSI_PLL
 */
#define PLL_SRC   HSI_PLL
/*******************************************************************************************************/

#endif // RCC_CONFIG_H
