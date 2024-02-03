/*******************************************************************************************************/
/* Author            : GP_FOTA_TEAM                                                                    */
/* Version           : V0.0.0                                                                          */
/* Data              : 3 Feb 2024                                                                      */
/* Description       : FMI_program.c --> implementations                                             */
/*******************************************************************************************************/


/*******************************************************************************************************/
/*                                      Standard Types LIB                                             */
#include "../../Libraries/STD_TYPES.h"
#include "../../Libraries/BIT_MATH.h"

/*******************************************************************************************************/
/*                                      MCAL Components                                                */
#include "FMI_private.h"
#include "FMI_config.h"
#include "FMI_interface.h"

/*******************************************************************************************************/
/*                                      Functions Implementations                                      */
/*******************************************************************************************************/

void FMI_voidEraseAppArea(void)
{
	/* 1- Wait if Flash is Busy (BSY) */
	while (GET_BIT(FMI->SR, 16) == 1) {}
	/* 2- Unlock Flash Register using KEYR */
	if (GET_BIT(FMI->CR, 31) == 1)
	{
	    FMI->KEYR = FMI_KEY1;
	    FMI->KEYR = FMI_KEY2;
	}
	/* 3- Select Mass Erase operation */
	SET_BIT(FMI->CR, 2);
	/* 4- Start erase operation */
	SET_BIT(FMI->CR, 16);
	/* 5- Wait for Busy Flag */
	while (GET_BIT(FMI->SR, 16) == 1) {}
	/* 6- Clear EOP flag */
	SET_BIT(FMI->SR, 0);
	/* 7- De-select Mass Erase Operation */
	CLR_BIT(FMI->CR, 2);
}

/*******************************************************************************************************/
void FMI_voidSectorErase(u8 A_u8SectorNo)
{
	/* 1- Wait if Flash is Busy (BSY) */
	while(GET_BIT(FMI->SR, 16) == 1){}
	/* 2- Unlock Flash Register using KEYR */
	if(GET_BIT(FMI->CR, 31) == 1)
	{
		FMI->KEYR = FMI_KEY1 ;
		FMI->KEYR = FMI_KEY2 ;
	}

	/* 3- select Sector Number to erase */
	FMI->CR &=~((u32)(0b1111<<3));
	FMI->CR |= (A_u8SectorNo <<3);

	/* 4- Select Erase operation */
	SET_BIT(FMI->CR, 1);
	/* 5- Start erase operation  */
	SET_BIT(FMI->CR, 16);
	/* 6- wait for Busy Flag    */
	while(GET_BIT(FMI->SR, 16) == 1){}
	/* 7- Clear EOP flag   */
	SET_BIT(FMI->SR, 0);

	/* 8- DeSelect Erase Operation (reverse of step 4) */
	CLR_BIT(FMI->CR, 1);
}

/*******************************************************************************************************/
void FMI_voidFlashWrite(u32 A_u32Address, u16* A_pu16Data, u16  A_u16Length)
{
	/* 1- Wait if Flash is Busy (BSY) */
	while(GET_BIT(FMI->SR, 16) == 1){}
	/* 2- Unlock Flash Register using KEYR */
	if(GET_BIT(FMI->CR, 31) == 1)
	{
		FMI->KEYR = FMI_KEY1 ;
		FMI->KEYR = FMI_KEY2 ;
	}

	/* 3- select element size (PSIZE)  */
	FMI->CR &=~((u32)(0b11<<8)) ;
	FMI->CR |= (Program_size<<8);

	/* 4- Activate Programming Mode (PG bit) */
	SET_BIT(FMI->CR, 0);

	/* 5- Write Data Array on Flash address */
	for(u16 i=0; i<A_u16Length; i++)
	{
		*((volatile u16*)A_u32Address) = A_pu16Data[i];
		A_u32Address += 2 ;//2 locations if u used 16 mode

		/* 6- wait for Busy Flag    */
		while(GET_BIT(FMI->SR, 16) == 1){}
		/* 7- Clear EOP flag   */
		SET_BIT(FMI->SR, 0);
	}
	/* 8- deactivate programming mode */
	CLR_BIT(FMI->CR, 0);
}


