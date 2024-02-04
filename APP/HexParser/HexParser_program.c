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
	u8 L_u8HexValue = 0;

	if(A_u8Ascii >= '0' && A_u8Ascii <= '9')
	{
		L_u8HexValue = A_u8Ascii - '0' ;
	}
	else if(A_u8Ascii >= 'A' && A_u8Ascii <='F')
	{
		L_u8HexValue = A_u8Ascii - 55 ; // 55='A'-10
	}
	return L_u8HexValue;
}

/*******************************************************************************************************/
void HexParser_voidParseData(u8 * A_pu8Data)
{
	/* charachter Count variables */
	u8 CC_high, CC_low, CC ;

	/* 4 digits for conversion */
	u8 digit0,digit1,digit2,digit3 ;

	/* Address variable */
	u32 address = 0;

	/* 1- convert charachter count */
	CC_high = HexParser_u8Ascii2Hex(A_pu8Data[1]);
	CC_low = HexParser_u8Ascii2Hex(A_pu8Data[2]);
	CC = (CC_high<<4)|CC_low ;

	/* 2- convert Address */
	digit0 = HexParser_u8Ascii2Hex(A_pu8Data[3]);
	digit1 = HexParser_u8Ascii2Hex(A_pu8Data[4]);
	digit2 = HexParser_u8Ascii2Hex(A_pu8Data[5]);
	digit3 = HexParser_u8Ascii2Hex(A_pu8Data[6]);

	address = (FLASH_BASE_ADDR)|(digit0 << 12)|(digit1 << 8)|(digit2 << 4)|(digit3 << 0);

	for(u8 i=0; i<(CC/2) ; i++)
	{
		digit0 = HexParser_u8Ascii2Hex(A_pu8Data[(4*i)+9]);
		digit1 = HexParser_u8Ascii2Hex(A_pu8Data[(4*i)+10]);
		digit2 = HexParser_u8Ascii2Hex(A_pu8Data[(4*i)+11]);
		digit3 = HexParser_u8Ascii2Hex(A_pu8Data[(4*i)+12]);

		DataBuffer[i] = (digit0 << 12)|(digit1 << 8 )|(digit2 << 4)|(digit3 << 0);
	}

	MFMI_voidFlashWrite(address, DataBuffer, CC/2);
}

