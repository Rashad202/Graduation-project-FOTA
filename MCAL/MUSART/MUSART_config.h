/*******************************************************************************************************/
/* Author            : GP_FOTA_TEAM                                                                    */
/* Version           : V0.0.0                                                                          */
/* Data              : 31 Jan 2024                                                                     */
/* Description       : MGPIO_Config.c --> Configuration                                                */
/*******************************************************************************************************/



/*******************************************************************************************************/
/*                                   guard of file will call on time in .c                             */
/*******************************************************************************************************/
#ifndef  MUSART_CONFIG_H_
#define  MUSART_CONFIG_H_

/*******************************************************************************************************/
#define U_ENABLE                  1
#define U_DISABLE                 0

#define U_EVEN_PARITY             0
#define U_ODD_PARITY              1

#define U_DATA_8                  0
#define U_DATA_9                  1

#define U_OVER_SAMPLING_16        0
#define U_OVER_SAMPLING_8         1

#define STOP_1                   0b00
#define STOP_05                  0b01
#define STOP_2                   0b10

/*******************************************************************************************************/
typedef enum{
    B_1200   = 0x3415,
    B_2400   = 0x1A0B,
    B_9600   = 0x683,
    B_19200  = 0x341,
    B_38400  = 0x1A1,
    B_57600  = 0x116,
    B_115200 = 0x8B
}u_BaudRate_t;

/*******************************************************************************************************/
/*****     USART 1 configurations        ******/
//if you want to use USART 1 Make this enable otherwise its config values will be discarded
#define USART1_USED             U_ENABLE
#define USART1_SEND_BREAK       U_DISABLE
#define USART1_RECEIVER         U_ENABLE
#define USART1_TRANSMITTER      U_ENABLE
#define USART1_T_COMP_INT       U_DISABLE
#define USART1_RX_INT           U_DISABLE
#define USART1_PARITY_ENABLE    U_DISABLE
#define USART1_PARITY_MODE      U_EVEN_PARITY
#define USART1_WORD_LEN         U_DATA_8
#define USART1_BUAD_RATE        B_9600;
#define USART1_OVER_SAMPLING    U_OVER_SAMPLING_16
#define USART1_STOP_BITS        STOP_1


/*******************************************************************************************************/
/*****     USART 2 configurations        ******/
//if you want to use USART 2 Make this enable otherwise its config values will be discarded
#define USART2_USED             U_DISABLE
#define USART2_SEND_BREAK       U_DISABLE
#define USART2_RECEIVER         U_ENABLE
#define USART2_TRANSMITTER      U_ENABLE
#define USART2_T_COMP_INT       U_DISABLE
#define USART2_RX_INT           U_ENABLE
#define USART2_PARITY_ENABLE    U_DISABLE
#define USART2_PARITY_MODE      U_EVEN_PARITY
#define USART2_WORD_LEN         U_DATA_8
#define USART2_BUAD_RATE        B_9600;
#define USART2_OVER_SAMPLING    U_OVER_SAMPLING_16
#define USART2_STOP_BITS        STOP_1


/*******************************************************************************************************/
/*****     USART 6 configurations        ******/
//if you want to use USART 6 Make this enable otherwise its config values will be discarded
#define USART6_USED             U_DISABLE
#define USART6_SEND_BREAK       U_DISABLE
#define USART6_RECEIVER         U_ENABLE
#define USART6_TRANSMITTER      U_ENABLE
#define USART6_T_COMP_INT       U_DISABLE
#define USART6_RX_INT           U_DISABLE
#define USART6_PARITY_ENABLE    U_DISABLE
#define USART6_PARITY_MODE      U_EVEN_PARITY
#define USART6_WORD_LEN         U_DATA_8
#define USART6_BUAD_RATE        B_9600;
#define USART6_OVER_SAMPLING    U_OVER_SAMPLING_16
#define USART6_STOP_BITS        STOP_1




#endif
