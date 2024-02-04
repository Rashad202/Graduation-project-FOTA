/*******************************************************************************************************/
/* Author            : GP_FOTA_TEAM                                                                    */
/* Version           : V0.0.0                                                                          */
/* Data              : 31 Jan 2024                                                                     */
/* Description       : MUSART_Interface.c --> implementations                                          */
/* Module  Features  :                                                                                 */
/*      01- MSUSART_voidInit                                                                            */
/*      02- MUSART_voidEnable                                                                          */
/*      03- MUSART_voidDisable                                                                         */
/*      04- MSUSART_u8SendData                                                                          */
/*      05- MUSART_u8ReadData                                                                          */
/*      06- MUSART_GetHandler                                                                          */
/*******************************************************************************************************/


/*******************************************************************************************************/
/*                                      Standard Types LIB                                             */
/*******************************************************************************************************/

#ifndef USART_INTERFACE_H
#define USART_INTERFACE_H

#define USART1				1
#define USART2				2
#define USART6				6

#define MUSART_NewLine	"\r\n"
#define	MUSART_Tab      '\t'


/*******************************************************************************************************/
/*                                      01- MSUSART_voidInit                                            */
/*-----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Enable Peripheral Clock                                                  */
/* 2- Function Input       -> Copy_uBusName ,   Copy_u8PerNum                                          */
/*   - BusName_t      : The Bus Of The Prepheral ( AHB1 , AHB2 , APB1 , APB2 ) Every One               */
/*                      Detect Which REG To Choice Pripheral From It                                   */
/*   - Copy_u8PerName :  The Order Of Prepheral On The Selected Reg                                    */
/* 3- Function Return      -> No Thing                                                                 */
/*******************************************************************************************************/
void MSUSART_voidInit(void);

/*******************************************************************************************************/
/*                                      02- MUSART_voidEnable                                          */
/*-----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Enable Peripheral Clock                                                  */
/* 2- Function Input       -> Copy_uBusName ,   Copy_u8PerNum                                          */
/*   - BusName_t      : The Bus Of The Prepheral ( AHB1 , AHB2 , APB1 , APB2 ) Every One               */
/*                      Detect Which REG To Choice Pripheral From It                                   */
/*   - Copy_u8PerName :  The Order Of Prepheral On The Selected Reg                                    */
/* 3- Function Return      -> No Thing                                                                 */
/*******************************************************************************************************/
void MUSART_voidEnable(u8 copy_u8Index);

/*******************************************************************************************************/
/*                                      03- MUSART_voidDisable                                         */
/*-----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Enable Peripheral Clock                                                  */
/* 2- Function Input       -> Copy_uBusName ,   Copy_u8PerNum                                          */
/*   - BusName_t      : The Bus Of The Prepheral ( AHB1 , AHB2 , APB1 , APB2 ) Every One               */
/*                      Detect Which REG To Choice Pripheral From It                                   */
/*   - Copy_u8PerName :  The Order Of Prepheral On The Selected Reg                                    */
/* 3- Function Return      -> No Thing                                                                 */
/*******************************************************************************************************/
void MUSART_voidDisable(u8 copy_u8Index);

/*******************************************************************************************************/
/*                                      04- MUSART_u8Send_Byte                                         */
/*-----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Enable Peripheral Clock                                                  */
/* 2- Function Input       -> copy_u8Index :USART(1,2,6)   -copy_u8Data : copy of data 	    	       */
/* 3- Function Return      -> No Thing                                                                 */
/*******************************************************************************************************/
void MUSART_u8Send_Byte(u8 copy_u8Index ,u8 copy_u8Data);

/*******************************************************************************************************/
/*                                      05- MUSART_u8Send_Data                                        */
/*-----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Enable Peripheral Clock                                                  */
/* 2- Function Input       -> copy_u8Index :USART(1,2,6)   -copy_u16Data : copy of data 	    	   */
/* 3- Function Return      -> No Thing                                                                 */
/*******************************************************************************************************/
void MUSART_u8Send_Data(u8 copy_u8Index , u8 *copy_u8Data);

/*******************************************************************************************************/
/*                                      06- MUSART_u8ReadData                                          */
/*-----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Enable Peripheral Clock                                                  */
/* 2- Function Input       -> Copy_uBusName ,   Copy_u8PerNum                                          */
/*   - BusName_t      : The Bus Of The Prepheral ( AHB1 , AHB2 , APB1 , APB2 ) Every One               */
/*                      Detect Which REG To Choice Pripheral From It                                   */
/*   - Copy_u8PerName :  The Order Of Prepheral On The Selected Reg                                    */
/* 3- Function Return      -> No Thing                                                                 */
/*******************************************************************************************************/
void MUSART_u8Read_Byte(u8 copy_u8Index,u8 *copy_u8Data);
/*******************************************************************************************************/
/*                                      07- USART1_voidSetCallBack                                     */
/*-----------------------------------------------------------------------------------------------------*/
void USART1_voidSetCallBack( void (*ptr) (void) );

/*******************************************************************************************************/
/*                                      08- USART2_voidSetCallBack                                     */
/*-----------------------------------------------------------------------------------------------------*/
void USART2_voidSetCallBack( void (*ptr) (void) );
/*******************************************************************************************************/
/*                                      09- USART2_voidSetCallBack                                     */
/*-----------------------------------------------------------------------------------------------------*/
void USART6_voidSetCallBack( void (*ptr) (void) );



#endif //USART_INTERFACE_H_
