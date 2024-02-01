/*******************************************************************************************************/
/* Author            : GP_FOTA_TEAM                                                                    */
/* Version           : V0.0.0                                                                          */
/* Data              : 31 Jan 2024                                                                     */
/* Description       : MUSART_Interface.c --> implementations                                          */
/* Module  Features  :                                                                                 */
/*      01- MSUART_voidInit                                                                            */
/*      02- MUSART_voidEnable                                                                          */
/*      03- MUSART_voidDisable                                                                         */
/*      04- MSUART_u8SendData                                                                          */
/*      05- MUSART_u8ReadData                                                                          */
/*      06- MUSART_GetHandler                                                                          */
/*******************************************************************************************************/


/*******************************************************************************************************/
/*                                      Standard Types LIB                                             */
/*******************************************************************************************************/

#ifndef UART_INTERFACE_H
#define UART_INTERFACE_H

#define USART1				1
#define USART2				2
#define USART6				6

#define MSUART_NewLine	"\r\n"
#define	MSUART_Tab      '\t'

void MSUART_voidInit(void);

void MUSART_voidEnable(u8 copy_u8Index);
void MUSART_voidDisable(u8 copy_u8Index);

void MUSART_u8Send_Byte(u8 copy_u8Index ,u8 copy_u8Data);
void MUSART_u8Send_Data(u8 copy_u8Index , u8 *copy_u8Data);

void MUSART_u8Read_Byte(u8 copy_u8Index,u8 *copy_u8Data);



#endif //UART_INTERFACE_H_
