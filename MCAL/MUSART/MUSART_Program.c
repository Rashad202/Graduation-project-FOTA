/*******************************************************************************************************/
/* Author            : GP_FOTA_TEAM                                                                    */
/* Version           : V0.0.0                                                                          */
/* Data              : 31 Jan 2024                                                                     */
/* Description       : MUSART_Program.c --> implementations                                            */
/*******************************************************************************************************/
/* Module  Features  :                                                                                 */
/*      01- MSUSART_voidInit                                                                           */
/*      02- MUSART_voidEnable                                                                          */
/*      03- MUSART_voidDisable                                                                         */
/*      04- MSUSART_u8SendData                                                                         */
/*      05- MUSART_u8ReadData                                                                          */
/*      06- MUSART_SetUSART                                                                            */
/*******************************************************************************************************/

/*******************************************************************************************************/
/*                                      Standard Types LIB                                             */
#include "../../Libraries/STD_TYPES.h"
#include "../../Libraries/BIT_MATH.h"
/*******************************************************************************************************/
// Global Pointer to Function to Hold USART ISR Address
void (*USART_USART1Function)(void) = NULL;
void (*USART_USART2Function)(void) = NULL;
void (*USART_USART6Function)(void) = NULL;

/*******************************************************************************************************/
/*                                      MCAL Components                                                */
#include "../MUSART/MUSART_Interface.h"
#include "../MUSART/MUSART_Private.h"
#include "../MUSART/MUSART_config.h"

/*******************************************************************************************************/
/*                                      Functions Implementations                                      */
/*******************************************************************************************************/


/*******************************************************************************************************/
void MUSART_voidInit(void)
{

	/***********	USART_1		***********/
#if (USART1_USED == U_ENABLE)
	/**< Configure USART baud rate  */
	USART1_REG->BRR = USART1_BUAD_RATE;
	/**< Configure USART stop bits */
	USART1_REG->CR2 |= (USART1_STOP_BITS << 12);
	/**< Configure USART send break character */
	USART1_REG->CR1.SBK = USART1_SEND_BREAK;
	/**< Configure USART RX enable/Disable */
	USART1_REG->CR1.RE = USART1_RECEIVER;
	/**< Configure USART1 TX enable/Disable */
	USART1_REG->CR1.TE = USART1_TRANSMITTER;
	/**< Configure USART1 RX Interrupt enable/Disable */
	USART1_REG->CR1.RXNEIE = USART1_RX_INT;
	/*< Configure USART1 Transmission complete interrupt enable/disable/*/
	USART1_REG->CR1.TCIE = USART1_T_COMP_INT;
	/**< Enable/Disable USART1 parity mode */
	USART1_REG->CR1.PCE = USART1_PARITY_ENABLE;
	/**< Configure USART1 parity mode */
	USART1_REG->CR1.PS = USART1_PARITY_MODE;
	/**< Configure USART1 word length (data bits) */
	USART1_REG->CR1.M = USART1_WORD_LEN;
	/**< Configure USART1 Over-sampling mode */
	USART1_REG->CR1.OVER8	= USART1_OVER_SAMPLING;
#endif

	/***********	USART_2		***********/
#if (USART2_USED == U_ENABLE)
	/**< Configure USART baud rate  */
	USART2_REG->BRR = USART2_BUAD_RATE;
	/**< Configure USART stop bits */
	USART2_REG->CR2 |= (USART2_STOP_BITS << 12);
	/**< Configure USART send break character */
	USART2_REG->CR1.SBK = USART2_SEND_BREAK;
	/**< Configure USART RX enable/Disable */
	USART2_REG->CR1.RE = USART2_RECEIVER;
	/**< Configure USART1 TX enable/Disable */
	USART2_REG->CR1.TE = USART2_TRANSMITTER;
	/**< Configure USART1 RX Interrupt enable/Disable */
	USART2_REG->CR1.RXNEIE = USART2_RX_INT;
	/*< Configure USART1 Transmission complete interrupt enable/disable/*/
	USART2_REG->CR1.TCIE = USART2_T_COMP_INT;
	/**< Enable/Disable USART1 parity mode */
	USART2_REG->CR1.PCE = USART2_PARITY_ENABLE;
	/**< Configure USART1 parity mode */
	USART2_REG->CR1.PS = USART2_PARITY_MODE;
	/**< Configure USART1 word length (data bits) */
	USART2_REG->CR1.M = USART2_WORD_LEN;
	/**< Configure USART1 Over-sampling mode */
	USART2_REG->CR1.OVER8	= USART2_OVER_SAMPLING;
#endif

	/***********	USART_6		***********/
#if (USART6_USED == U_ENABLE)
	/**< Configure USART baud rate  */
	USART6_REG->BRR = USART6_BUAD_RATE;
	/**< Configure USART stop bits */
	USART6_REG->CR2 |= (USART6_STOP_BITS << 12);
	/**< Configure USART send break character */
	USART6_REG->CR1.SBK = USART6_SEND_BREAK;
	/**< Configure USART RX enable/Disable */
	USART6_REG->CR1.RE = USART6_RECEIVER;
	/**< Configure USART1 TX enable/Disable */
	USART6_REG->CR1.TE = USART6_TRANSMITTER;
	/**< Configure USART1 RX Interrupt enable/Disable */
	USART6_REG->CR1.RXNEIE = USART6_RX_INT;
	/*< Configure USART1 Transmission complete interrupt enable/disable/*/
	USART6_REG->CR1.TCIE = USART6_T_COMP_INT;
	/**< Enable/Disable USART1 parity mode */
	USART6_REG->CR1.PCE = USART6_PARITY_ENABLE;
	/**< Configure USART1 parity mode */
	USART6_REG->CR1.PS = USART6_PARITY_MODE;
	/**< Configure USART1 word length (data bits) */
	USART6_REG->CR1.M = USART6_WORD_LEN;
	/**< Configure USART1 Over-sampling mode */
	USART6_REG->CR1.OVER8	= USART6_OVER_SAMPLING;
#endif
}

/*******************************************************************************************************/

void MUSART_voidEnable(u8 copy_u8Index){
	switch(copy_u8Index){
	case 1: USART1_REG -> CR1.UE = 1; break;
	case 2: USART2_REG -> CR1.UE = 1; break;
	case 6: USART6_REG -> CR1.UE = 1; break;
	}
}

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
void MUSART_u8Send_Byte(u8 copy_u8Index ,u8 copy_u8Data){
	USART_REG _USART_ = MUSART_SetUSART(copy_u8Index);
	while(0==GET_BIT(_USART_->SR, 7));// wait until transmission complete into the shift register
	_USART_->DR = copy_u8Data;
	while(0==GET_BIT(_USART_->SR, 6));// wait until transmission of a frame containing data is complete
}

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
u8 MUSART_u8Receive_Byte(u8 copy_u8Index,u8 *copy_u8Data){
	USART_REG _USART_ = MUSART_SetUSART(copy_u8Index);
	u8 Statue = Receive;
	if( GET_BIT( _USART_->SR ,5) == 1 )
	{
		*copy_u8Data= _USART_->DR;
	}
	else
	{
		Statue = NoReceive ;
	}
		return Statue ;
}

/*******************************************************************************************************/
USART_REG MUSART_SetUSART(u8 copy_u8Index){
	USART_REG L_handle= (USART_REG) USART1_BASE_ADRESS;
	switch (copy_u8Index)
	{
	case 1: L_handle =  (USART_REG) USART1_BASE_ADRESS; break;
	case 2: L_handle =  (USART_REG) USART2_BASE_ADRESS; break;
	case 6: L_handle =  (USART_REG) USART6_BASE_ADRESS; break;
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
