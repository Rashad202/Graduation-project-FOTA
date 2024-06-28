/* USER CODE BEGIN Header */
/*******************************************************************************
 * @file           : main.c
 * @author         : Samy&Rashad&Huda@GP_FOTA_TEAM
 * @Data           : 17 Feb 2024	-	8 May 2024
 * @brief          : GETWAY_V0
 *******************************************************************************/
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "Libraries/STD_TYPES.h"
#include "Libraries/BIT_MATH.h"

#include "MCAL/MRCC/MRCC_interface.h"
#include "MCAL/MGPIO/MGPIO_interface.h"
#include "MCAL/MSTK/MSYSTICK_Interface.h"
#include "MCAL/MNVIC/MNVIC_Interface.h"
#include "MCAL/MEXTI/MEXTI_interface.h"
#include "MCAL/MUSART/MUSART_Interface.h"

#include "HAL/LED/LED_interface.h"

/* USER CODE END Includes */
/*******************************************************************************************************/
/*                                      MCAL Components                                                */
#define No_ERROR	 1
#define ERROR		 0

#define ENABLE		 1
#define DISABLE		 0

#define USART_COMM	 1
#define CAN_COMM	 2
#define GW_communication	USART_COMM

#define GW_DEBUGGING 		DISBLE
#define GW_IMT_DEBUGGING 	ENABLE
/* externs ------------------------------------------------------------------*/
/* USER CODE BEGIN externs */
extern const LedX_t Led_3;

//for test
extern const LedX_t Led_1;
extern const LedX_t Led_2;

/* USER CODE END externs */
/* Global variables  ---------------------------------------------------------*/

volatile u8 u8RecBuffer_6[45]  = {NULL};
volatile u8 u8RecCounter_6     =  0    ;
volatile u8 u8FirstLineReq     =  1    ;
volatile u8 USART=0;

volatile u8 u8RecBuffer_1    =  0    ;
volatile u8 u8RecBuffer_2    =  0    ;
/* Global variables  END */
/*functions deceleration ---------------------------------------------------------*/

void Reset_Flags(void);
/* functions deceleration  END */
/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

int main(void)
{
	/*Initialize System Clock to be 16MHz from HSI*/
	MRCC_voidInitSystemClk();
	MSTK_voidInit();
	_delay_ms(1500);
	/*Initialize  USARTs GPIO clock*/
	MRCC_voidEnablePeripheralClock(AHB1,GPIOA_PORT);
	MRCC_voidEnablePeripheralClock(AHB1,GPIOC_PORT);
	/*USART 1 initializing*/								//for Node_1
	MRCC_voidEnablePeripheralClock(APB2,PERIPHERAL_EN_USART1);
	MGPIO_voidSetPinMode (GPIOA_PORT, PIN_9,  MODE_ALTF);
	MGPIO_voidSetPinMode (GPIOA_PORT, PIN_10, MODE_ALTF);
	MGPIO_voidSetPinAltFn(GPIOA_PORT, PIN_9,  ALTFN_7);
	MGPIO_voidSetPinAltFn(GPIOA_PORT, PIN_10, ALTFN_7);
	/*USART 2 initializing*/								//for Node_2
	MRCC_voidEnablePeripheralClock(APB1,PERIPHERAL_EN_UART2);
	MGPIO_voidSetPinMode (GPIOA_PORT, PIN_2,  MODE_ALTF);
	MGPIO_voidSetPinMode (GPIOA_PORT, PIN_3,  MODE_ALTF);
	MGPIO_voidSetPinAltFn(GPIOA_PORT, PIN_2,  ALTFN_7);
	MGPIO_voidSetPinAltFn(GPIOA_PORT, PIN_3,  ALTFN_7);
	/*USART 6 initializing*/								//for ESP32
	MRCC_voidEnablePeripheralClock(APB2,PERIPHERAL_EN_USART6);
	MGPIO_voidSetPinMode (GPIOA_PORT, PIN_11,  MODE_ALTF);
	MGPIO_voidSetPinMode (GPIOA_PORT, PIN_12,  MODE_ALTF);
	MGPIO_voidSetPinAltFn(GPIOA_PORT, PIN_11,  ALTFN_8);
	MGPIO_voidSetPinAltFn(GPIOA_PORT, PIN_12,  ALTFN_8);
	/*USARTs initialize and enable*/
	MUSART_voidInit();
	MUSART_voidEnable(USART1);
	MUSART_voidEnable(USART2);
	MUSART_voidEnable(USART6);
	/*SysTick initialize*/
	MSTK_voidInit();
	/*Initialize the LEDS*/
	LED_Init(&Led_3);
	LED_Init(&Led_1);
	LED_Init(&Led_2);

	/* begin ---------------------------------------------------------*/
	LED_Off(&Led_3);
	/*Defending on the used communication protocol*/
#if (GW_communication == USART_COMM)

#if	(GW_DEBUGGING == ENABLE)
	MUSART_u8Send_Data(USART6,(u8*)"---GETEWAY_READY---");		//---
	MUSART_u8Send_Data(USART6,MUSART_NewLine);				 	//---
#endif
	/*USARTs receive statuses*/
	u8 LOC_u8RecStatus_1 = NoReceive;	//from Node_1
	u8 LOC_u8RecStatus_2 = NoReceive;	//from Node_2
	u8 LOC_u8RecStatus_6 = NoReceive;	//from ESP32

	while(1)
	{
		LOC_u8RecStatus_1 =MUSART_u8Receive_Byte(USART1,& u8RecBuffer_1); 					    //from Node_1
		LOC_u8RecStatus_2 =MUSART_u8Receive_Byte(USART2,& u8RecBuffer_2); 					    //from Node_2
		LOC_u8RecStatus_6 =MUSART_u8Receive_Byte(USART6,& u8RecBuffer_6[u8RecCounter_6]); 	    //from ESP32
		//---------------------------------------------------------------------------------------
		//-------------------------------------	 ESP32	-----------------------------------------
		if( LOC_u8RecStatus_6 == Receive )
		{
			/*Collecting data in the buffer*/
			if( u8RecBuffer_6[u8RecCounter_6] == '\n' ){
				/*indicate the target node and send the restart order to the app*/
				if( u8FirstLineReq == 1 ){

					/*--------UPDATE  NODE 1 or 2--------*/
					if (u8RecBuffer_6[0]=='1') {
#if	(GW_DEBUGGING == ENABLE)
						MUSART_u8Send_Data(USART6,(u8 *)"Start USART 1");	 //---
#endif
						USART=USART1;
						u8FirstLineReq   = 0 ;
						LED_On(&Led_1);
					}
					else if (u8RecBuffer_6[0]=='2') {
#if	(GW_DEBUGGING == ENABLE)
						MUSART_u8Send_Data(USART6,(u8 *)"Start USART 2");	 //---
#endif
						USART=USART2;
						u8FirstLineReq   = 0 ;
					}

					/*--------applications on NODE_1	(FORWARD,BACKWORD,AUTOPARK)--------*/
					else if(u8RecBuffer_6[0]=='W'){
						USART=USART1;
						u8FirstLineReq   = 0 ;
					}
					else if(u8RecBuffer_6[0]=='S'){
						USART=USART1;
						u8FirstLineReq   = 0 ;
					}
					else if(u8RecBuffer_6[0]=='A'){
						USART=USART1;
						u8FirstLineReq   = 0 ;
					}
					else if(u8RecBuffer_6[0]=='O'){
						USART=USART1;
						u8FirstLineReq   = 0 ;
					}

					/*--------applications on NODE_2	(CONDITIONER)--------*/
					else if(u8RecBuffer_6[0]=='5'){
						USART=USART2;
						u8FirstLineReq   = 0 ;
					}
					else if(u8RecBuffer_6[0]=='6'){
						USART=USART2;
						u8FirstLineReq   = 0 ;
					}
					else{ /*for future fetcher*/ }
				}
				u8RecBuffer_6[u8RecCounter_6+1]='\0';	// for not sending anything from the older data in the buffer
				/*send to the target*/
				if(USART==USART1 || USART==USART2){
					MUSART_u8Send_Data(USART,u8RecBuffer_6);
					LED_On(&Led_2);

					Led_Toggle(&Led_3);	//led to visualizes the send process
					/*Set buffer counter to 0 */
					u8RecCounter_6   = 0 ;

					/*rest usart after ordering the app*/
					if((u8FirstLineReq  == 0) && (u8RecBuffer_6[0]=='W' || u8RecBuffer_6[0]=='A' || u8RecBuffer_6[0]=='S' || u8RecBuffer_6[0]=='O' || u8RecBuffer_6[0]=='6' || u8RecBuffer_6[0]=='5')){
						u8FirstLineReq  = 1;
						USART=0;
						//Reset_Flags();
					}

				}


			}
			else{ u8RecCounter_6++ ; }
		}
		//---------------------------------------------------------------------------------------
		//-------------------------------------	 Node 1	-----------------------------------------
		if( LOC_u8RecStatus_1 == Receive )
		{
			/*Receive the ACK from the BOOTLOADER*/
			if(u8RecBuffer_1=='B'){			//node1 in the BOOTLOADER
				MUSART_u8Send_Byte(USART6,'B');
			}
			else if(u8RecBuffer_1=='K'){	//record correct
#if	(GW_IMT_DEBUGGING == ENABLE)
				MUSART_u8Send_Data(USART6,(u8 *)"ok");
#else
				MUSART_u8Send_Byte(USART6,'K');
#endif
			}
			else if (u8RecBuffer_1=='N' ) {	//error in the record
				MUSART_u8Send_Byte(USART6,'N');
			}
			else if (u8RecBuffer_1=='D') {	//End of hex file
				MUSART_u8Send_Byte(USART6,'D');
				Reset_Flags();				//restart & send something to show on the tablet
			}
			else if(u8RecBuffer_1=='F'){
				//Bootloader received wrong 3 times ACK for ESP to re download the file or ask the server to fix the problem
				MUSART_u8Send_Byte(USART6,'F');
				Reset_Flags();
			}
			else{
#if	(GW_DEBUGGING == ENABLE)
				MUSART_u8Send_Data(USART6,&u8RecBuffer_1);		//---
				MUSART_u8Send_Data(USART6," --- ERRORR1\n");	//---
#endif
			}
			Led_Toggle(&Led_3);	//led to visualizes the send process
		}
		//---------------------------------------------------------------------------------------
		//-------------------------------------	 Node 2	-----------------------------------------
		if( LOC_u8RecStatus_2 == Receive )
		{
			/*Receive the ACK from the BOOTLOADER*/
			if(u8RecBuffer_2=='B'){			//node2 in the BOOTLOADER
				MUSART_u8Send_Byte(USART6,'B');
			}
			else if(u8RecBuffer_2=='K'){	//record correct
#if	(GW_IMT_DEBUGGING == ENABLE)
				MUSART_u8Send_Data(USART6,(u8 *)"ok");
#else
				MUSART_u8Send_Byte(USART6,'K');
#endif
			}
			else if (u8RecBuffer_2=='N' ) {	//error in the record
				MUSART_u8Send_Byte(USART6,'N');
			}
			else if (u8RecBuffer_2=='D') {	//End of hex file
				MUSART_u8Send_Byte(USART6,'D');
				Reset_Flags();				//restart send something to show on the LCD
			}
			else if(u8RecBuffer_2=='F'){
				//Bootloader received wrong 3 times ACK for ESP to re download the file or ask the server to fix the problem
				MUSART_u8Send_Byte(USART6,'F');
				Reset_Flags();
			}
			else{
#if	(GW_DEBUGGING == ENABLE)
				MUSART_u8Send_Data(USART6,&u8RecBuffer_2);		//---
				MUSART_u8Send_Data(USART6," --- ERRORR2\n");	//---
#endif
			}
			Led_Toggle(&Led_3);	//led to visualizes the send process
		}
	}
#endif

#if (GW_communication == CAN_COMM)
	/*for CAN communication*/
#endif
}


/* USER CODE END 0 */
/* Functions ---------------------------------------------------------*/

void Reset_Flags(void)
{
	u8FirstLineReq = 1;
	USART=0;
	LED_Off(&Led_3);
}


/* GIDE for the characters send from the GETWAY -------------------------*/
/*
	'B'	---	ACK to inform the ESP that the node BOOTLOADER respond					  'BOOTLOADER'
	'K'	---	ACK to inform the ESP that the node BOOTLOADER received the record correct'OK'
	'N'	---	ACK to inform the ESP that the node BOOTLOADER received the record wrong  'NO'
	'D'	---	ACK to inform the ESP that the node BOOTLOADER received the last record   'DONE'
	'F'	---	ACK to inform the ESP that the node BOOTLOADER received failed 3 times	  'FAILED'


	'W'	---	ACK to inform the NODE to start FORWARD     application	  'FORWARD'
	'S'	---	ACK to inform the NODE to start BACKWORD    application   'BACKWORD'
	'A'	---	ACK to inform the NODE to start AUTOPARK    application   'AUTOPARK'
	'C'	---	ACK to inform the NODE to start CONDITIONER application	  'CONDITIONER'
 */

