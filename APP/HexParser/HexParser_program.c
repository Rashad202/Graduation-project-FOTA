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
u32 FLASH_BASE_ADDR=0X00000000;
u16 DataBuffer[100] ;

/*******************************************************************************************************/
/*                                      Functions Implementations                                      */



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
		u8 digit0,digit1,digit2,digit3 ;
		digit0 = HexParser_u8Ascii2Hex(Copy_BufRecord[9]);
		digit1 = HexParser_u8Ascii2Hex(Copy_BufRecord[10]);
		digit2 = HexParser_u8Ascii2Hex(Copy_BufRecord[11]);
		digit3 = HexParser_u8Ascii2Hex(Copy_BufRecord[12]);

		FLASH_BASE_ADDR |=(digit0<<28)|(digit1<<24)|(digit2<<20)|(digit3<<16);
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
	address = address & 0xFFFF0000;
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
		DataBuffer[i] = (digit2 << 12) | (digit3 << 8 ) | (digit0 << 4 ) | (digit1 << 0 );// 2-3-0-1 insted of 3-2-1-0

	}

	/* Write the data in the flash memory */
	MFMI_voidFlashWrite(address, DataBuffer, CC/2);
}

/*******************************************************************************************************/
u8 HexParser_CheckSumOfData (u8 * Copy_u8BufData)
{


	/* local variable */
	u8 CharCount_H_Byte = 0, CharCount_L_Byte = 0 ,CharCount = 0;

	u8 No_ofRecord_Digits_without_CS_digits = 0;

	u8 Sum_of_Digits_without_CS_digits = 0;

	int CheckSum = 0;

	u8 Check_No_Error;

	/*** Getting the character count ***/

	/* Get the high byte */
	CharCount_H_Byte = HexParser_u8Ascii2Hex(Copy_u8BufData[1]);

	/* Get the low byte */
	CharCount_L_Byte = HexParser_u8Ascii2Hex(Copy_u8BufData[2]);

	/* Get the character count */
	CharCount = (CharCount_H_Byte << 4) | CharCount_L_Byte;


    /*
    CharCount_digits = 2 digit
     Address_digits  = 4 digit
     Type_digit      = 2 digit
     so we add 8 to sum of data digits
    */

    /* Calculate number of digits */
	No_ofRecord_Digits_without_CS_digits = (CharCount * 2) + 8;
	/*
	  Start from 1 to neglect the ':'
	  Increment by 1 bytes "2 digit"
	*/

	for (int i = 1 ;i < No_ofRecord_Digits_without_CS_digits; i+=2)
	{
		/* Accumulate the sum byte by byte */
	Sum_of_Digits_without_CS_digits += ( HexParser_u8Ascii2Hex(Copy_u8BufData[i]) << 4) | HexParser_u8Ascii2Hex((Copy_u8BufData[i+1]));

	}

	/*
	  Checksum is the 2s-complement of the sum of the number of bytes, plus the address plus the data
	  Add up the number of bytes, the address and all the data and discard any carry to give 8-bit total
	  Then invert each digit to give 1s-complement by XOR with 0xFF then add 1 to get the 2s-complement
	 */

	Sum_of_Digits_without_CS_digits = (((Sum_of_Digits_without_CS_digits ^ 0xFF)) + 1);


	/*
	        Get the checkSum byte from Record
	*/
	int CheckSum_HByte = HexParser_u8Ascii2Hex(Copy_u8BufData[No_ofRecord_Digits_without_CS_digits+1]);
	int CheckSum_LByte = HexParser_u8Ascii2Hex(Copy_u8BufData[No_ofRecord_Digits_without_CS_digits+2]);
	CheckSum = ( CheckSum_HByte << 4) | CheckSum_LByte ;

	/* Compare between Calculated checksum and checksum in record*/
    if ((CheckSum & 0xFF) == (Sum_of_Digits_without_CS_digits& 0xFF))
	{
		Check_No_Error = No_ERROR;
	}
	else
	{
		Check_No_Error = ERROR;
	}
	return Check_No_Error;

}
