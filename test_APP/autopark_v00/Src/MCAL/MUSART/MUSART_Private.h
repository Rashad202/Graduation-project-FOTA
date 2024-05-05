/*******************************************************************************************************/
/* Author            : GP_FOTA_TEAM                                                                    */
/* Version           : V0.0.0                                                                          */
/* Data              : 31 Jan 2024                                                                     */
/* Description       : MUSART_Privite.h --> implementations                                            */
/* Features          : Register Definitions                                                            */
/*******************************************************************************************************/



/*******************************************************************************************************/
/*                                   guard of file will call on time in .c                             */
/*******************************************************************************************************/

#ifndef MSART_PRIVATE_H
#define MSART_PRIVATE_H

/*******************************************************************************************************/
/*                                    Macros Base Address Of USARTX Registers                           */
#define USART1_BASE_ADRESS     0x40011000UL
#define USART2_BASE_ADRESS     0x40004400UL
#define USART6_BASE_ADRESS     0x40011400UL

/*******************************************************************************************************/
typedef struct{
    u32 SBK       :1;
    u32 RWU       :1;
    u32 RE        :1;
    u32 TE        :1;
    u32 IDLEIE    :1;
    u32 RXNEIE    :1;
    u32 TCIE      :1;
    u32 TXEIE     :1;
    u32 PEIE      :1;
    u32 PS        :1;
    u32 PCE       :1;
    u32 WAKE      :1;
    u32 M         :1;
    u32 UE        :1;
    u32 RESERVED  :1;
    u32 OVER8     :1;
    u32 RESERVED2 :16;
}USART_CR1;

/*******************************************************************************************************/
typedef struct{
    u32 SR;
    u32 DR;
    u32 BRR;
    USART_CR1 CR1;
    u32 CR2;
    u32 CR3;
    u32 GTPR;
}USART_t;

/*******************************************************************************************************/
/*                                   Struct Macros Base Address Of USARTx                              */

typedef    volatile USART_t* USART_REG ;

#define     USART1_REG    ((volatile USART_t*)(USART1_BASE_ADRESS))
#define     USART2_REG    ((volatile USART_t*)(USART2_BASE_ADRESS))
#define     USART6_REG    ((volatile USART_t*)(USART6_BASE_ADRESS))



/*******************************************************************************************************/
/*                                       MUSART_SetUSART                                          */
/*-----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Enable Peripheral Clock                                                  */
/* 2- Function Input       -> Copy_uBusName ,   Copy_u8PerNum                                          */
/*   - BusName_t      : The Bus Of The Prepheral ( AHB1 , AHB2 , APB1 , APB2 ) Every One               */
/*                      Detect Which REG To Choice Pripheral From It                                   */
/*   - Copy_u8PerName :  The Order Of Prepheral On The Selected Reg                                    */
/* 3- Function Return      -> No Thing                                                                 */
/*******************************************************************************************************/
static USART_REG MUSART_SetUSART(u8 copy_u8Index);


#endif // USART_PRIVATE_H
