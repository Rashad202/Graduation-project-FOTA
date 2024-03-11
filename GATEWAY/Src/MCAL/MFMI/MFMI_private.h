/*******************************************************************************************************/
/* Author            : GP_FOTA_TEAM                                                                    */
/* Version           : V0.0.0                                                                          */
/* Data              : 3 Feb 2024                                                                      */
/* Description       : MFMI_private.h --> implementations                                               */
/*******************************************************************************************************/
/*                                   guard of file will call on time in .c                             */
#ifndef MFMI_private_H_
#define MFMI_private_H_

/*   Macros Base Address Of FMI Registers   */
#define MFMI_BASE_ADDRESS	0x40023C00

/*   Macros of Keys   */
#define FMI_KEY1	0x45670123
#define FMI_KEY2    0xCDEF89AB
/*******************************************************************************************************/
/*   Register Definitions   */
typedef struct
{
	volatile u32 ACR;
	volatile u32 KEYR;
	volatile u32 OPTKEYR;
	volatile u32 SR;
	volatile u32 CR;
	volatile u32 OPTCR;
}FMI_t;

#define FMI   ((volatile FMI_t*)(MFMI_BASE_ADDRESS))

#endif /* MFMI_private_H_ */
