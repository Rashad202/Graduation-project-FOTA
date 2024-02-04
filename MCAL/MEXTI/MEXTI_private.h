/*******************************************************************************************************/
/* Author            : GP_FOTA_TEAM                                                                    */
/* Version           : V0.0.0                                                                          */
/* Data              : 21 Dec 2023                                                                     */
/* Description       : MEXTI_Privite.h --> implementations                                             */
/* Features          : Register Definitions                                                            */
/*******************************************************************************************************/
#ifndef EXIT_PRIVATE_H
#define EXIT_PRIVATE_H

/*******************************************************************************************************/
/*                                    Macros Base Address Of NVIC Registers                            */
#define Base_Address_EXTI			       0x40013C00
#define Base_Address_SYSCFG                0x40013800

/*******************************************************************************************************/
#define   EXTI_CONFG_MASK1                0xFFFFFFF0UL
#define   EXTI_CONFG_MASK2                0xFFFFFF0FUL
#define   EXTI_CONFG_MASK3                0xFFFFF0FFUL
#define   EXTI_CONFG_MASK4                0xFFFF0FFFUL

/*******************************************************************************************************/
typedef struct
{
	/*  	Must be arranged like register map		*/

	volatile  u32   IMR		;				// From Here Choice The Line
	volatile  u32   EMR		;				// FOR Event Mask
	volatile  u32   RTSR	;				// For Enable or Disable Raising Trigger For Line
	volatile  u32   FTSR	;				// For Enable or Disable Falling Trigger For Line
	volatile  u32   SWIER   ;				// For The SoftWare Interrput Event
	volatile  u32   PR		;				// For The Pending
}EXTI_t;																					// The New Data Type Of That Struct
/*******************************************************************************************************/
typedef struct{
	u32 MEMRMP ;
	u32 PMC ;
	u32 EXTICR1 ;
	u32 EXTICR2 ;
	u32 EXTICR3 ;
	u32 EXTICR4 ;
	u32 CMPCR ;
}SYSCFG_memoryMap_t;
/*******************************************************************************************************/
/*                                   Struct Macros Base Address Of NVIC                                */
/* Pointer Point To EXTI_t ( The Struct ) Casting Pointer To Struct Point To The Frist base  Address   */
/* Without Dereferance (It is A Pointer )                                                              */
#define EXTI_Ptr     		(( volatile  EXTI_t * ) Base_Address_EXTI )			
#define SYSCFG              (( volatile SYSCFG_memoryMap_t*) Base_Address_SYSCFG)
/*******************************************************************************************************/
/******	  Sense_Mode	 ******/
#define Rising_Edage				0
#define Falling_Edage			    1
#define On_Change					2									// Any Change Happen


#endif //EXIT_PRIVATE_H
