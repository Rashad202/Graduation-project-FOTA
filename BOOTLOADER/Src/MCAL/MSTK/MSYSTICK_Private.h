/*******************************************************************************************************/
/* Author            : GP_FOTA_TEAM                                                                    */
/* Version           : V0.0.0                                                                          */
/* Data              : 15 Dec 2023                                                                     */
/* Description       : MSTK_Privite.h --> implementations                                             */
/* Features          : Register Definitions                                                            */
/*******************************************************************************************************/
#ifndef SYSTICK_REG_H_
#define SYSTICK_REG_H_

/*******************************************************************************************************/
/*                                    Macros Base Address Of SYSTICK Registers                         */
 
#define    STK_BASE_ADRESS        0xE000E010

typedef struct{

	volatile u32 CTRL ;
	volatile u32 LOAD ;
	volatile u32 VAL  ;
	volatile u32 CALIB;

}SYSTICK;

#define MSTK ((volatile SYSTICK*)STK_BASE_ADRESS)

#endif /* SYSTICK_REG_H_ */
