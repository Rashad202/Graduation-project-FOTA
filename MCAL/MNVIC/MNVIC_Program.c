/*******************************************************************************************************/
/*******************************************************************************************************/
/* Author            : GP_FOTA_TEAM                                                                    */
/* Version           : V0.0.0                                                                          */
/* Data              : 17 Dec 2023                                                                     */
/* Description       : NVIC_Program.c --> implementations                                              */
/*******************************************************************************************************/

/*******************************************************************************************************/
/*                                      Standard Types LIB                                             */
/*******************************************************************************************************/
#include "../Libraries/STD_TYPES.h"
#include "../Libraries/BIT_MATH.h"

/*******************************************************************************************************/
/*                                      MCAL Components                                                */
/*******************************************************************************************************/

#include "MNVIC_private.h"
#include "MNVIC_interface.h"
#include "MNVIC_config.h"




/*******************************************************************************************************/
/*                                      Functions Implementations                                      */
/*******************************************************************************************************/
static u8 Global_u8IPR;
/*******************************************************************************************************/
/*
* Function: Set The enable for any prefiral
* Range :	Copy_u8PeripheralID -> 84 "Refer to data sheet" */

void MNVIC_voidEnableInterrupt(u8 Copy_u8PeripheralID){
	NVIC_REG->ISER[Copy_u8PeripheralID / Reg_div] = (1U << Copy_u8PeripheralID % Reg_div);
}

/*******************************************************************************************************/
/*
* Function: Set The enable for any prefiral
* Range :	Copy_u8PeripheralID -> 84 "Refer to data sheet" */
void MNVIC_voidDisableInterrupt(u8 Copy_u8PeripheralID){
	NVIC_REG->ICER[Copy_u8PeripheralID / Reg_div] = (1U << Copy_u8PeripheralID % Reg_div);
	
}

/*******************************************************************************************************/
void MNVIC_voidEnableInterruptPending(u8 Copy_u8PeripheralID){
	NVIC_REG->ISPR[Copy_u8PeripheralID / Reg_div] = (1U << Copy_u8PeripheralID % Reg_div);
	
}

/*******************************************************************************************************/
void MNVIC_voidDisableInterruptPinding(u8 Copy_u8PeripheralID){
	NVIC_REG->ICPR[Copy_u8PeripheralID / Reg_div] = (1U << Copy_u8PeripheralID % Reg_div);
	
}

/*******************************************************************************************************/
void MNVICE_u8IsInterruptActive(u8 Copy_u8PeripheralID,u8 *copy_u8Read){
	*copy_u8Read= GET_BIT(NVIC_REG->IABR[Copy_u8PeripheralID / Reg_div], Copy_u8PeripheralID);

}

/*******************************************************************************************************/
void MNVIC_voidInitInterruptGroup(NVIC_GroupMode_t copy_GropMode){
		 //Read  SCB_AIRCR First reset the regester first
	Global_u8IPR = copy_GropMode;
	SCB_AIRCR = (VECTKEY | (copy_GropMode << 8));
}

/*******************************************************************************************************/ 
void MNVIC_voidSetInterruptPriority(u8 Copy_u8PeripheralID, u8 copy_u8IntGroup, u8 copy_u8IntSubGroup){

	switch(Global_u8IPR){
		case NVIC_GroupMode_g16s0 :
									NVIC_REG->IPR[Copy_u8PeripheralID] = (copy_u8IntGroup << 4);
									break;
		case NVIC_GroupMode_g8s2  :
									NVIC_REG->IPR[Copy_u8PeripheralID] = (copy_u8IntGroup << 5) | (copy_u8IntSubGroup << 4);
									break;
		case NVIC_GroupMode_g4s4  :
									NVIC_REG->IPR[Copy_u8PeripheralID] = (copy_u8IntGroup << 6) | (copy_u8IntSubGroup << 4);
									break;
		case NVIC_GroupMode_g2s8  :
									NVIC_REG->IPR[Copy_u8PeripheralID] = (copy_u8IntGroup << 7) | (copy_u8IntSubGroup << 4);
									break;
		case NVIC_GroupMode_g0s16 :
									NVIC_REG->IPR[Copy_u8PeripheralID] = (copy_u8IntSubGroup << 4);
									break;
	}
}

/*******************************************************************************************************/
void MNVIC_voidGenerateSoftwareInterrupt(u8 Copy_u8PeripheralID){
	NVIC_REG->STIR = (Copy_u8PeripheralID << 4);
}
