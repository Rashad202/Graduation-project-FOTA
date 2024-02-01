/*******************************************************************************************************/
/* Author            : GP_FOTA_TEAM                                                                    */
/* Version           : V0.0.0                                                                          */
/* Data              : 31 Jan 2024                                                                     */
/* Description       : MUSART_Program.c --> implementations                                            */
/*******************************************************************************************************/
/* Module  Features  :                                                                                 */
/*      01- MSUART_voidInit                                                                            */
/*      02- MUSART_voidEnable                                                                          */
/*      03- MUSART_voidDisable                                                                         */
/*      04- MSUART_u8SendData                                                                          */
/*      05- MUSART_u8ReadData                                                                          */
/*      06- MUSART_GetHandler                                                                          */
/*******************************************************************************************************/

/*#####################################################################################################*/
/*#####################################################################################################*/

/*******************************************************************************************************/
/*                                      Standard Types LIB                                             */
/*******************************************************************************************************/

#include "../../Libraries/STD_TYPES.h"
#include "../../Libraries/BIT_MATH.h"

// Global Pointer to Function to Hold USART ISR Address
void (*USART_USART1Function)(void) = NULL;
void (*USART_USART2Function)(void) = NULL;
void (*USART_USART6Function)(void) = NULL;
/*#####################################################################################################*/
/*#####################################################################################################*/

/*******************************************************************************************************/
/*                                      MCAL Components                                                */
/*******************************************************************************************************/
#include "MUSART_Interface.h"
#include "MUSART_Private.h"
#include "MUSART_Config.h"

/*#####################################################################################################*/
/*#####################################################################################################*/

/*******************************************************************************************************/
/*                                      Functions Implementations                                      */
/*******************************************************************************************************/

/*#####################################################################################################*/
/*#####################################################################################################*/

/*******************************************************************************************************/
/*                                      01- MSUART_voidInit                                            */
/*-----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Enable Peripheral Clock                                                  */
/* 2- Function Input       -> Copy_uBusName ,   Copy_u8PerNum                                          */
/*   - BusName_t      : The Bus Of The Prepheral ( AHB1 , AHB2 , APB1 , APB2 ) Every One               */
/*                      Detect Which REG To Choice Pripheral From It                                   */ 
/*   - Copy_u8PerName :  The Order Of Prepheral On The Selected Reg                                    */                      
/* 3- Function Return      -> No Thing                                                                 */
/*******************************************************************************************************/


void MSUART_voidInit(void)
{

	/***********	UART_1		***********/
#if (UART1_USED == U_ENABLE)
	/**< Configure UART baud rate  */
	USART1_REG->BRR = UART1_BUAD_RATE;
	/**< Configure UART stop bits */
	USART1_REG->CR2 |= (UART1_STOP_BITS << 12);
	/**< Configure UART send break character */
	USART1_REG->CR1.SBK = UART1_SEND_BREAK;
	/**< Configure UART RX enable/Disable */
	USART1_REG->CR1.RE = UART1_RECEIVER;
	/**< Configure UART1 TX enable/Disable */
	USART1_REG->CR1.TE = UART1_TRANSMITTER;
	/**< Configure UART1 RX Interrupt enable/Disable */
	USART1_REG->CR1.RXNEIE = UART1_RX_INT;
	/*< Configure UART1 Transmission complete interrupt enable/disable/*/
	USART1_REG->CR1.TCIE = UART1_T_COMP_INT;
	/**< Enable/Disable UART1 parity mode */
	USART1_REG->CR1.PCE = UART1_PARITY_ENABLE;
	/**< Configure UART1 parity mode */
	USART1_REG->CR1.PS = UART1_PARITY_MODE;
	/**< Configure UART1 word length (data bits) */
	USART1_REG->CR1.M = UART1_WORD_LEN;
	/**< Configure UART1 Over-sampling mode */
	USART1_REG->CR1.OVER8	= UART1_OVER_SAMPLING;
#endif

	/***********	UART_2		***********/
#if (UART2_USED == U_ENABLE)
	/**< Configure UART baud rate  */
	USART2_REG->BRR = UART2_BUAD_RATE;
	/**< Configure UART stop bits */
	USART2_REG->CR2 |= (UART2_STOP_BITS << 12);
	/**< Configure UART send break character */
	USART2_REG->CR1.SBK = UART2_SEND_BREAK;
	/**< Configure UART RX enable/Disable */
	USART2_REG->CR1.RE = UART2_RECEIVER;
	/**< Configure UART1 TX enable/Disable */
	USART2_REG->CR1.TE = UART2_TRANSMITTER;
	/**< Configure UART1 RX Interrupt enable/Disable */
	USART2_REG->CR1.RXNEIE = UART2_RX_INT;
	/*< Configure UART1 Transmission complete interrupt enable/disable/*/
	USART2_REG->CR1.TCIE = UART2_T_COMP_INT;
	/**< Enable/Disable UART1 parity mode */
	USART2_REG->CR1.PCE = UART2_PARITY_ENABLE;
	/**< Configure UART1 parity mode */
	USART2_REG->CR1.PS = UART2_PARITY_MODE;
	/**< Configure UART1 word length (data bits) */
	USART2_REG->CR1.M = UART2_WORD_LEN;
	/**< Configure UART1 Over-sampling mode */
	USART2_REG->CR1.OVER8	= UART2_OVER_SAMPLING;
#endif

	/***********	UART_6		***********/
#if (UART6_USED == U_ENABLE)
	/**< Configure UART baud rate  */
	USART6_REG->BRR = UART6_BUAD_RATE;
	/**< Configure UART stop bits */
	USART6_REG->CR2 |= (UART6_STOP_BITS << 12);
	/**< Configure UART send break character */
	USART6_REG->CR1.SBK = UART6_SEND_BREAK;
	/**< Configure UART RX enable/Disable */
	USART6_REG->CR1.RE = UART6_RECEIVER;
	/**< Configure UART1 TX enable/Disable */
	USART6_REG->CR1.TE = UART6_TRANSMITTER;
	/**< Configure UART1 RX Interrupt enable/Disable */
	USART6_REG->CR1.RXNEIE = UART6_RX_INT;
	/*< Configure UART1 Transmission complete interrupt enable/disable/*/
	USART6_REG->CR1.TCIE = UART6_T_COMP_INT;
	/**< Enable/Disable UART1 parity mode */
	USART6_REG->CR1.PCE = UART6_PARITY_ENABLE;
	/**< Configure UART1 parity mode */
	USART6_REG->CR1.PS = UART6_PARITY_MODE;
	/**< Configure UART1 word length (data bits) */
	USART6_REG->CR1.M = UART6_WORD_LEN;
	/**< Configure UART1 Over-sampling mode */
	USART6_REG->CR1.OVER8	= UART6_OVER_SAMPLING;
#endif
}

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

void MUSART_voidEnable(u8 copy_u8Index){
	switch(copy_u8Index){
	case 1: USART1_REG -> CR1.UE = 1; break;
	case 2: USART2_REG -> CR1.UE = 1; break;
	case 6: USART6_REG -> CR1.UE = 1; break;
	}
}

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

void MUSART_voidDisable(u8 copy_u8Index){
	switch (copy_u8Index)
	{
	case 1: USART1_REG -> CR1.UE = 0; break;
	case 2: USART2_REG -> CR1.UE = 0; break;
	case 6: USART6_REG -> CR1.UE = 0; break;
	}
}

/*******************************************************************************************************/
/*                                      04- MUSART_u8Send_Byte                                         */
/*-----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Enable Peripheral Clock                                                  */
/* 2- Function Input       -> copy_u8Index :USART(1,2,6)   -copy_u8Data : copy of data 	    	       */
/* 3- Function Return      -> No Thing                                                                 */
/*******************************************************************************************************/

void MUSART_u8Send_Byte(u8 copy_u8Index ,u8 copy_u8Data){
	UART_REG uhandler = MUSART_GetHandler(copy_u8Index);
	while(0==GET_BIT(uhandler->SR, 7));// wait until transmission complete into the shift register
	uhandler ->DR = copy_u8Data;
	while(0==GET_BIT(uhandler->SR, 6));// wait until transmission of a frame containing data is complete
}

/*******************************************************************************************************/
/*                                      04- MUSART_u8Send_Data                                         */
/*-----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Enable Peripheral Clock                                                  */
/* 2- Function Input       -> copy_u8Index :USART(1,2,6)   -copy_u8Data : copy of data 	    	       */
/* 3- Function Return      -> No Thing                                                                 */
/*******************************************************************************************************/

void MUSART_u8Send_Data(u8 copy_u8Index , u8 *copy_u8Data){
	u8 Local_u8Index =0;
	while('\0'!=copy_u8Data[Local_u8Index])
	{
		MUSART_u8Send_Byte(copy_u8Index,copy_u8Data[Local_u8Index]);
		Local_u8Index++;
	}
}

/*******************************************************************************************************/
/*                                      05- MUSART_u8ReadData                                          */
/*-----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Enable Peripheral Clock                                                  */
/* 2- Function Input       -> Copy_uBusName ,   Copy_u8PerNum                                          */
/*   - BusName_t      : The Bus Of The Prepheral ( AHB1 , AHB2 , APB1 , APB2 ) Every One               */
/*                      Detect Which REG To Choice Pripheral From It                                   */ 
/*   - Copy_u8PerName :  The Order Of Prepheral On The Selected Reg                                    */                      
/* 3- Function Return      -> No Thing                                                                 */
/*******************************************************************************************************/


void MUSART_u8Read_Byte(u8 copy_u8Index,u8 *copy_u8Data){
	UART_REG uhandler = MUSART_GetHandler(copy_u8Index);
	//while(0==GET_BIT(uhandler->SR, 5));
	*copy_u8Data= uhandler->DR;
}

/*******************************************************************************************************/
/*                                      06- MUSART_GetHandler                                          */
/*-----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Enable Peripheral Clock                                                  */
/* 2- Function Input       -> Copy_uBusName ,   Copy_u8PerNum                                          */
/*   - BusName_t      : The Bus Of The Prepheral ( AHB1 , AHB2 , APB1 , APB2 ) Every One               */
/*                      Detect Which REG To Choice Pripheral From It                                   */ 
/*   - Copy_u8PerName :  The Order Of Prepheral On The Selected Reg                                    */                      
/* 3- Function Return      -> No Thing                                                                 */
/*******************************************************************************************************/


UART_REG MUSART_GetHandler(u8 copy_u8Index){
	UART_REG L_handle= (UART_REG) USART1_BASE_ADRESS;
	switch (copy_u8Index)
	{
	case 1: L_handle =  (UART_REG) USART1_BASE_ADRESS; break;
	case 2: L_handle =  (UART_REG) USART2_BASE_ADRESS; break;
	case 6: L_handle =  (UART_REG) USART6_BASE_ADRESS; break;
	}
	return L_handle;
}


/*******************************************************************************************************/
/*                                      07- USART1_voidSetCallBack                                     */
/*-----------------------------------------------------------------------------------------------------*/

void USART1_voidSetCallBack( void (*ptr) (void) )
{
	USART_USART1Function = ptr;
}

/*******************************************************************************************************/
/*                                      08- USART2_voidSetCallBack                                     */
/*-----------------------------------------------------------------------------------------------------*/
void USART2_voidSetCallBack( void (*ptr) (void) )
{
	USART_USART2Function = ptr;
}
/*******************************************************************************************************/
/*                                      09- USART2_voidSetCallBack                                     */
/*-----------------------------------------------------------------------------------------------------*/
void USART6_voidSetCallBack( void (*ptr) (void) )
{
	USART_USART6Function = ptr;
}

/*******************************************************************************************************/
/** ISR of USART1 **/
void USART1_IRQHandler(void)
{
	USART1_REG->SR = 0 ;	//reset flags
	USART_USART1Function();
}

/** ISR of USART2 **/
void USART2_IRQHandler(void)
{
	USART2_REG->SR = 0 ;
	USART_USART2Function();
}

/** ISR of USART6 **/
void USART6_IRQHandler(void)
{
	USART6_REG->SR = 0 ;
	USART_USART6Function();
}
