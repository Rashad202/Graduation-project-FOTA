/*******************************************************************************************************/
/* Author            : GP_FOTA_TEAM                                                                    */
/* Version           : V0.0.0                                                                          */
/* Data              : 3 Feb 2024                                                                      */
/* Description       : HexParser_interface.h --> implementations                                       */
/* Module  Features  :                                                                                 */
/*      01- HexParser_voidParseData                                                                       */
/*******************************************************************************************************/

/*******************************************************************************************************/
/*                                   guard of file will call on time in .c                             */
#ifndef APP_HEXPARSER_INTERFACE_H_
#define APP_HEXPARSER_INTERFACE_H_

/*******************************************************************************************************/
/*                                      Function Prototypes                                            */
/*******************************************************************************************************/
/*******************************************************************************************************/
/*                                      00- HexParser_voidParseData                                	   */
/*-----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Parses the input data and converts it into a buffer of hexadecimal values*/
/* 2- Function Input       -> A_pu8Data												                   */
/* 3- Function Return      -> NO                                                           		       */
/*******************************************************************************************************/
void HexParser_voidParseData(u8 * A_pu8Data);

/*******************************************************************************************************/
/*                                      01- HexParser_voidParseRecord                                	   */
/*-----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Parse the record.                                                		   */
/* Parameters (in): uint8* (Holds pointer to buffer record)											   */
/* Function Return      -> None																		   */	
/*******************************************************************************************************/
void HexParser_vParseRecord(u8*Copy_BufRecord);

#endif /* APP_HEXPARSER_INTERFACE_H_ */
