/*******************************************************************************************************/
/* Author            : GP_FOTA_TEAM                                                                    */
/* Version           : V0.0.0                                                                          */
/* Data              : 3 Feb 2024                                                                      */
/* Description       : HexParser_private.h --> implementations                                         */
/*******************************************************************************************************/


/*******************************************************************************************************/
/*                                      Standard Types LIB                                             */
#include "../../Libraries/STD_TYPES.h"
#include "../../Libraries/BIT_MATH.h"
/*******************************************************************************************************/
/*                                      MCAL Components                                                */
#include "../../MCAL/MFMI/MFMI_interface.h"
/*******************************************************************************************************/
/*                                HexParser APP Components                                             */
#include "HexParser_private.h"
#include "HexParser_interface.h"
#include "HexParser_config.h"

/*  variables  ---------------------------------------------------------*/
u16 DataBuffer[100] ;

/* Global variables  END */
/*******************************************************************************************************/
/*                                      Functions Implementations                                      */
/*******************************************************************************************************/
/*******************************************************************************************************/
/*                                      00- HexParser_u8Ascii2Hex                                	   */
/*-----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Converts an ASCII character representing a hexadecimal digit to 		   */
/*    its corresponding hexadecimal value                   										   */
/* 2- Function Input       -> A_u8Ascii												                   */
/* 3- Function Return      -> u8                                                           		       */
/*******************************************************************************************************/
static u8 HexParser_u8Ascii2Hex(u8 A_u8Ascii)
{
	/* local variable that holds the returned value */
	u8 L_u8HexValue = 0;

	/* Check if this Ascii value is equivalent to number from 0 to 9 */
	if(A_u8Ascii >= '0' && A_u8Ascii <= '9')
	{
		L_u8HexValue = A_u8Ascii - '0' ;
	}
	/* Check if this Ascii value is char A to F */
	else if(A_u8Ascii >= 'A' && A_u8Ascii <='F')
	{
		/* 55 to transform A to 10, B to 11 and etc.. */
		L_u8HexValue = A_u8Ascii - 55 ; 
	}
	return L_u8HexValue;
}

/*******************************************************************************************************/
/*                                      01- HexParser_voidParseRecord                                	   */
/*-----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Parse the record.                                                		   */
/* Parameters (in): uint8* (Holds pointer to buffer record)											   */
/* Function Return      -> None																		   */	
/*******************************************************************************************************/
void HexParser_vParseRecord(u8*Copy_BufRecord)
{
	/* Check on record type */
	switch(Copy_BufRecord[8])
	{
	case '0' :

		/* Start parsing the record */
		HexParser_voidParseData(Copy_BufRecord);
		break;

	case '4':
		/*set high address part*/
		break;

	case '1':
		/* End of file - Do nothing */
		break;

	default:
		/* Do nothing - defensive programming */
		break;
	}
}

/*******************************************************************************************************/
/*                                      02- HexParser_voidParseData                                	   */
/*-----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Parse the hex file..                                                		   */
/* Parameters (in): uint8* (Holds pointer to buffer record)											   */
/* Function Return      -> None																		   */	
/*******************************************************************************************************/
void HexParser_voidParseData(u8 * A_pu8Data)
{
/* local variable to hold the character count high byte ,count low byte & count */
	u8 CC_high, CC_low, CC ;

	/* 4 digits for conversion */
	u8 digit0,digit1,digit2,digit3 ;

	/* To hold the address value */
	u32 address = 0;

	/*** Getting the character count ***/

		/* Get the high byte */
	CC_high = HexParser_u8Ascii2Hex(A_pu8Data[1]);
		/* Get the low byte */
	CC_low = HexParser_u8Ascii2Hex(A_pu8Data[2]);
		/* Get the character count */
	CC = (CC_high<<4)|CC_low ;

	/*** Extracting the address ***/
	digit0 = HexParser_u8Ascii2Hex(A_pu8Data[3]);
	digit1 = HexParser_u8Ascii2Hex(A_pu8Data[4]);
	digit2 = HexParser_u8Ascii2Hex(A_pu8Data[5]);
	digit3 = HexParser_u8Ascii2Hex(A_pu8Data[6]);


	/* Insert the low address into the least significant 4 bytes */
	address = (FLASH_BASE_ADDR) |
			  (digit0 << 12)    |
			  (digit1 << 8 )    |
			  (digit2 << 4 )    |
			  (digit3 << 0 );

	/*** Extracting the data ***/

	/* Writes 2 bytes per time */		  
	for(u8 i=0; i<(CC/2) ; i++)
	{
		/* Get the first byte */
		digit0 = HexParser_u8Ascii2Hex(A_pu8Data[(4*i)+9]);
		digit1 = HexParser_u8Ascii2Hex(A_pu8Data[(4*i)+10]);
		/* Get the second byte */
		digit2 = HexParser_u8Ascii2Hex(A_pu8Data[(4*i)+11]);
		digit3 = HexParser_u8Ascii2Hex(A_pu8Data[(4*i)+12]);


		/*
		 * Load the second byte then first byte using MSB first
		 * Example: FE BA should be loaded as BA FE
		 */
		DataBuffer[i] = (digit0 << 12) | (digit1 << 8 ) | (digit2 << 4 ) | (digit3 << 0 );

	}

	/* Write the data in the flash memory */
	MFMI_voidFlashWrite(address, DataBuffer, CC/2);
}

