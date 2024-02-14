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
volatile u8 UpdateAPP=0;

volatile u8 u8RecBuffer[100] = {0}   ;
volatile u8 u8RecCounter     =  0    ;
volatile u8 TimeOutFlag      =  0    ;
volatile u8 u8BLWriteReq     =  1    ;
u8 CS=No_ERROR;

/* Global variables  END */
/*functions deceleration ---------------------------------------------------------*/

void Func_CallBack(void);
void Disables (void);
/* functions deceleration  END */
/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

int main(void)
{
	/*Initialize System Clock to be 16MHz from HSI*/
	MRCC_voidInitSystemClk();
	/*Initialize the USART*/
	MRCC_voidEnablePeripheralClock(AHB1,GPIOA_PORT);
	MRCC_voidEnablePeripheralClock(APB2,PERIPHERAL_EN_USART1);
	MGPIO_voidSetPinMode (GPIOA_PORT, PIN_9,  MODE_ALTF);
	MGPIO_voidSetPinMode (GPIOA_PORT, PIN_10, MODE_ALTF);
	MGPIO_voidSetPinAltFn(GPIOA_PORT, PIN_9,  ALTFN_7);
	MGPIO_voidSetPinAltFn(GPIOA_PORT, PIN_10, ALTFN_7);
	MUSART_voidInit();
	MUSART_voidEnable(USART1);
	MSTK_voidInit();
	//USART6_voidSetCallBack(RECIVE_INT);
	//MNVIC_voidEnableInterrupt(MNVIC_USART6);
	/*Initialize the LEDS*/
	LED_Init(&Led_1);
	LED_Init(&Led_3);

	/*begin */
	LED_On(&Led_1);
//
	if ( UpDate_Flag == No_APP )
	{
		// determined which App active
		CurrantAPP=0;
		// determined which App will boot
		UpdateAPP =1;

	}
	//  app1 is active
	else if ( UpDate_Flag == APP_1_MID )
	{
		// determined which App active
		CurrantAPP=1;
		// determined which App will boot
		UpdateAPP =2;
	}
	else if (UpDate_Flag == APP_2_MID )
	{
		// determined which App active
		CurrantAPP=2;
		// determined which App will boot
		UpdateAPP =1;
	}
//
	MUSART_u8Send_Data(USART1,(u8*)"FOTA (v 1.0.0) ");
	MUSART_u8Send_Data(USART1,MUSART_NewLine);

	u8 LOC_u8RecStatus = NoReceive;
	MSTK_voidSetIntervalSingle((u32)15000000,Func_CallBack);//to back to the APP if an error happen

	while( TimeOutFlag == 0 )
	{
		LOC_u8RecStatus =MUSART_u8Receive_Byte(USART1,& u8RecBuffer[u8RecCounter]);
		if( LOC_u8RecStatus == Receive )
		{
			/*Stop timer Application code in processing*/
			MSTK_voidStopInterval();
			/*Indicate The end of the Record*/
			if( u8RecBuffer[u8RecCounter] == '\n' ){
				if( u8BLWriteReq == 1 ){
					/*Erase The Application Area*/
					if(UpdateAPP==1){
						MFMI_voidSectorErase(SECTOR_4);
					}
					else if(UpdateAPP==2){
						//MUSART_u8Send_Data(USART1,(u8 *)"sector 5 errase");
						MFMI_voidSectorErase(SECTOR_5);
					}
					/*Set WriteReq Flag = 0 */
					u8BLWriteReq = 0 ;
				}

				CS=HexParser_CheckSumOfData( u8RecBuffer );
				if(CS==No_ERROR){
					/*Parse The record and wite it to flash*/
					HexParser_vParseRecord ( u8RecBuffer );
					/*send ok to the tool to send the next record*/
					MUSART_u8Send_Data(USART1,(u8 *)"ok");
				}
				else{
					LED_On(&Led_2);
					MUSART_u8Send_Data(USART1,(u8 *)"Not ok");

					// for depug we will ask the getway to send it again
					//MFMI_voidSectorErase(SECTOR_5);
					MSTK_voidSetIntervalSingle( 1000000 , Func_CallBack);
				}

				u8RecCounter = 0 ;
			}
			else{ u8RecCounter++ ; }
			/*End of hex file */
			if( u8RecBuffer[8] == '1' ){
				/*wait 1 sec then jump to application code*/
				CurrantAPP=UpdateAPP;
				MSTK_voidSetIntervalSingle( 1000000 , Func_CallBack );
				LED_On(&Led_3); //indicate to successful flashing
			}
		}
	}
	if(TimeOutFlag == 1){
		Jumper();
	}
}

/* USER CODE END 0 */
/* Functions ---------------------------------------------------------*/
void Func_CallBack(void){
	TimeOutFlag = 1 ;
	switch(CurrantAPP)
	{
	case 0:
		MUSART_u8Send_Data(USART1,(u8 *)" ---NO APPs--- ");
		MUSART_u8Send_Data(USART1,MUSART_NewLine);
		TimeOutFlag = 0;
		MSTK_voidReSetInterval((u32)15000000);
		break;

	case 1:
		MUSART_u8Send_Data(USART1,(u8 *)" ---APP1_S4--- ");
		MUSART_u8Send_Data(USART1,MUSART_NewLine);

		MFMI_voidSectorErase(3);
		MFMI_voidFlashWrite(APP_FLAG_ADD,&APP_1,1);
		MSTK_voidStopInterval();
		break;

	case 2:
		MUSART_u8Send_Data(USART1,(u8 *)" ---APP2_S5--- ");
		MUSART_u8Send_Data(USART1,MUSART_NewLine);

		MFMI_voidSectorErase(3);
		MFMI_voidFlashWrite(APP_FLAG_ADD,&APP_2,1);
		MSTK_voidStopInterval();
		break;
	}
}

void Jumper(void){
	switch(CurrantAPP)
	{
	case 0:
				/*	NO APPs	*/
		break;

	case 1:
		//MSTK_u8ReadFlag();
		Disables();
		BL_voidJumpToAPP_1();
		break;

	case 2:
		//MSTK_u8ReadFlag();
		Disables();
		BL_voidJumpToAPP_2();
		break;
	}
}

void Disables (void){
	/*	turn off BootLoader led*/
	LED_Off(&Led_1);
	MNVIC_voidDisableInterrupt(MNVIC_USART1);
	MUSART_voidDisable(USART1);

	MRCC_voidDisablePeripheralClock(AHB1,GPIOA_PORT);
	MRCC_voidDisablePeripheralClock(APB2,PERIPHERAL_EN_USART1);

	//MEXTI_voidDisableEXTI(9);
	//MEXTI_voidDisableEXTI(10);
	//__disable_irq();
	//MSTK_voidStopInterval();
	//MSTK_u8ReadFlag();
}




