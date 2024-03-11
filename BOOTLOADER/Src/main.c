/* USER CODE BEGIN Header */
/*******************************************************************************
 * @file           : main.c
 * @author         : Samy&Rashad@GP_FOTA_TEAM
 * @Data           : 14 Feb 2024
 * @brief          : Bootloader_V3
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
#include "MCAL/MFMI/MFMI_interface.h"

#include "HAL/LED/LED_interface.h"

#include "APP/HexParser/HexParser_interface.h"
#include "APP/BootLoader/BootLoader_interface.h"

/* USER CODE END Includes */
/*******************************************************************************************************/
/*                                      MCAL Components                                                */
/* externs ------------------------------------------------------------------*/
/* USER CODE BEGIN externs */
extern const LedX_t Led_1,Led_2,Led_3;

/* USER CODE END externs */
/* Global variables  ---------------------------------------------------------*/
volatile u16 APP_1=APP_1_ID;
volatile u16 APP_2=APP_2_ID;

volatile u8 CurrantAPP=0;
volatile u8 UpdateAPP =0;

volatile u8 u8RecBuffer[100] = {0}   ;
volatile u8 u8RecCounter     =  0    ;
volatile u8 TimeOutFlag      =  0    ;
volatile u8 u8BLWriteReq     =  1    ;
u8 CS=No_ERROR;
u8 Error_counter=0; //same line receive error counter

/* Global variables  END */
/*functions deceleration ---------------------------------------------------------*/

void Func_CallBack(void);
void Jumper	  (void);
void Disables (void);
/* functions deceleration  END */
/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

int main(void)
{
	/*Initialize System Clock to be 16MHz from HSI*/
	MRCC_voidInitSystemClk();
	/*Initialize  USART GPIO clock*/
	MRCC_voidEnablePeripheralClock(AHB1,GPIOA_PORT);
	/*Initialize the USART*/
	MRCC_voidEnablePeripheralClock(APB2,PERIPHERAL_EN_USART1);
	MGPIO_voidSetPinMode (GPIOA_PORT, PIN_9,  MODE_ALTF);
	MGPIO_voidSetPinMode (GPIOA_PORT, PIN_10, MODE_ALTF);
	MGPIO_voidSetPinAltFn(GPIOA_PORT, PIN_9,  ALTFN_7);
	MGPIO_voidSetPinAltFn(GPIOA_PORT, PIN_10, ALTFN_7);
	/*USART initialize and enable*/
	MUSART_voidInit();
	MUSART_voidEnable(USART1);
	/*SysTick initialize*/
	MSTK_voidInit();
	/*Initialize the LEDS*/
	LED_Init(&Led_1);
	//LED_Init(&Led_3);

	/* begin ---------------------------------------------------------*/
	LED_On(&Led_1);
	/*check on the currant App (in sector 4 and 5 )*/
	if ( UpDate_Flag == No_APP )
	{
		CurrantAPP=0;// determined which App active
		UpdateAPP =1;// determined which App will boot
	}
	else if ( UpDate_Flag == APP_1_MID )
	{
		CurrantAPP=1;// determined which App active
		UpdateAPP =2;// determined which App will boot
	}
	else if (UpDate_Flag == APP_2_MID )
	{
		CurrantAPP=2;// determined which App active
		UpdateAPP =1;// determined which App will boot
	}


	/*Defending on the used communication protocol*/
#if (BL_communication == USART_COMM)
	/*send ACK to the gateway that BOOTLOADER is active now*/
	MUSART_u8Send_Byte(USART1,(u8*)'B');
	/*7.5 sec wait then call the callback function*/
	MSTK_voidSetIntervalSingle((u32)15000000,Func_CallBack);
	/*USART receive statuses*/
	u8 LOC_u8RecStatus = NoReceive;

	while( TimeOutFlag == 0 )
	{
		LOC_u8RecStatus =MUSART_u8Receive_Byte(USART1,& u8RecBuffer[u8RecCounter]);	 //from the gateway
		//---------------------------------------------------------------------------------------
		//---------------------------------	 Gateway receive	---------------------------------
		if( LOC_u8RecStatus == Receive )
		{
			/*Stop timer Application code in processing*/
			MSTK_voidStopInterval();
			/*Collecting data in the buffer*/
			if( u8RecBuffer[u8RecCounter] == '\n' ){	//Indicate The end of the Record
				if( u8BLWriteReq == 1 ){
					if(u8RecBuffer[0] == '1' || u8RecBuffer[0] == '2'){
						MUSART_u8Send_Byte(USART1,(u8*)'B');
						u8RecCounter = 0 ;
						continue;
					}
					/*Erase The Application Area*/
					if(UpdateAPP==1){
						MFMI_voidSectorErase(SECTOR_4);
					}
					else if(UpdateAPP==2){
						MFMI_voidSectorErase(SECTOR_5);
					}
					/*Set WriteReq Flag = 0 */
					u8BLWriteReq = 0 ;
				}
				/*Collecting check sum and send ACK to the gateway*/
				CS=HexParser_CheckSumOfData( u8RecBuffer );
				if(CS==No_ERROR){
					/*Parse The record and write it to flash*/
					HexParser_vParseRecord ( u8RecBuffer );
					/*send ok to the tool to send the next record*/
#if	(BL_IMT_DEBUGGING == ENABLE)
					MUSART_u8Send_Data(USART1,(u8 *)"ok");
#else
					MUSART_u8Send_Byte(USART1,(u8 *)'K');
#endif
					Error_counter=0;
				}
				else{
					// send ACK to the gateway to send it again if the error happened 3 times it fail and back to the app
					Error_counter++;
					if(1==Error_counter || 2==Error_counter){
						MUSART_u8Send_Byte(USART1,(u8 *)'N');
					}
					else if(3==Error_counter){
						MUSART_u8Send_Byte(USART1,(u8 *)'F');
						Error_counter=0;
						Func_CallBack();
					}
				}
				u8RecCounter = 0 ;
			}
			else{ u8RecCounter++ ; }
			/*End of hex file */
			if( u8RecBuffer[8] == '1' ){
				//indicate to successful flashing
				//LED_On(&Led_3);
				MUSART_u8Send_Byte(USART1,(u8 *)'D');
				/*update the flag and jump  */
				CurrantAPP=UpdateAPP;
				Func_CallBack();
			}
		}
	}
#endif

#if (BL_communication == CAN_COMM)
	/*for CAN communication*/
#endif

	if(TimeOutFlag == 1){
		Jumper();
	}
}

/* USER CODE END 0 */
/* Functions ---------------------------------------------------------*/
void Func_CallBack(void){
	TimeOutFlag = 1 ;
	/*update the flag sector and be ready to jump */
	switch(CurrantAPP)
	{
	case 0:
		/*---NO APPs--- */
		TimeOutFlag = 0;
		MSTK_voidReSetInterval((u32)15000000);
		break;

	case 1:
		/*----APP1_S4--- */
		MFMI_voidSectorErase(SECTOR_3);
		MFMI_voidFlashWrite(APP_FLAG_ADD,&APP_1,1);
		MSTK_voidStopInterval();
		break;

	case 2:
		/*----APP2_S5--- */
		MFMI_voidSectorErase(SECTOR_3);
		MFMI_voidFlashWrite(APP_FLAG_ADD,&APP_2,1);
		MSTK_voidStopInterval();
		break;
	}
}

void Jumper(void){
	switch(CurrantAPP)
	{
	case 0:
		/*---NO APPs--- */
		break;

	case 1:
		/*----APP1_S4--- */
		Disables();
		BL_voidJumpToAPP_1();
		break;

	case 2:
		/*----APP1_S5--- */
		Disables();
		BL_voidJumpToAPP_2();
		break;
	}
}

void Disables (void){
	/*turn off BootLoader LEDs */
	LED_Off(&Led_1);
	//LED_Off(&Led_3);
	/*disable peripherals */
	MUSART_voidDisable(USART1);
	MRCC_voidDisablePeripheralClock(AHB1,GPIOA_PORT);
	MRCC_voidDisablePeripheralClock(APB2,PERIPHERAL_EN_USART1);
}


/* GIDE for the characters send from the BOOTLOADER -------------------------*/
/*
	'B'	---		ACK to inform the gateway this node is in the BOOTLOADER now
	'K'	---		ACK to inform the gateway this it received the record correct
	'N'	---		ACK to inform the gateway this it received the record wrong
	'D'	---		ACK to inform the gateway this it received the last record
	'F'	---		ACK to inform the gateway this it received failed 3 times
 */


