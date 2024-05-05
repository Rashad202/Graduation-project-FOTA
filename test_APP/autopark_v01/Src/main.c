/* USER CODE BEGIN Header */
/*******************************************************************************
 * @file           : main.c
 * @author         : Mohamed_Samy@GP_FOTA_TEAM
 * @brief          : Auto Parking APP
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
#include "MCAL/MTIMER/MTIMER_interface.h"

#include "HAL/LED/LED_interface.h"
#include "HAL/Ultrasonic/Ultrasonic_interface.h"
#include "HAL/MotorDriver/MotorDriver_interface.h"
#include "HAL/Servo_motor/Servo_motor_interface.h"
/* USER CODE END Includes */

/* externs ------------------------------------------------------------------*/
/* USER CODE BEGIN externs */
extern const LedX_t 		Led_0,Led_1,Led_2,Led_3;//embedded blue  ,1,2,3 red
extern const UltraSX_t  	UltraS_t_F,UltraS_t_B;				//Ultrasonics trigger 1..6
extern const MotorX_t		Motor_1;				//DC Motors  1,2
/* USER CODE END externs */

/* Global variables  ---------------------------------------------------------*/
u8  R_data=0; 	   		//USART date
u8  R_data_Flag=0;   	//USART date flag
u8  currunt_motion=STOP;//motion flag

f64 Distance_F =0; //distance from ultraS_1 (front)
f64 Distance_B =0; //distance from ultraS_2	(back)
f64 Distance_Rf=0; //distance from ultraS_3	(right front)
f64 Distance_Rb=0; //distance from ultraS_4	(right back)
f64 Distance_Lf=0; //distance from ultraS_5	(left front)
f64 Distance_Lb=0; //distance from ultraS_6	(left back)
/* Global variables  END */

/*functions deceleration -----------------------------------------------------*/
void RECIVE_INT(void);
void WWDT_voidMakeSoftWareReset(void);
/* functions deceleration  END */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int main(void)
{
	/*System Clock is 16MHz from HSI*/
	MRCC_voidInitSystemClk();
	MSTK_voidInit();
	//--------LEDs--------//
	MRCC_voidEnablePeripheralClock(AHB1,GPIOC_PORT );
	LED_Init(&Led_0);
	LED_Off (&Led_0);
	MRCC_voidEnablePeripheralClock(AHB1,GPIOA_PORT );
	LED_Init(&Led_1);
	LED_Off (&Led_1);
	LED_Init(&Led_2);
	LED_Off (&Led_2);
	LED_Init(&Led_3);
	LED_Off (&Led_3);
	//--------USART--------//
	MRCC_voidEnablePeripheralClock(AHB1,GPIOA_PORT);
	MRCC_voidEnablePeripheralClock(APB2,PERIPHERAL_EN_USART1);
	MGPIO_voidSetPinMode (GPIOA_PORT, PIN_9,  MODE_ALTF);
	MGPIO_voidSetPinMode (GPIOA_PORT, PIN_10, MODE_ALTF);
	MGPIO_voidSetPinAltFn(GPIOA_PORT, PIN_9,  ALTFN_7);
	MGPIO_voidSetPinAltFn(GPIOA_PORT, PIN_10, ALTFN_7);
	MUSART_voidInit();
	MUSART_voidEnable(USART1);
	USART1_voidSetCallBack(RECIVE_INT);
	//--------ULTRASONIC echo & its Timer--------// F  B
	// the front one	(A1)
	MRCC_voidEnablePeripheralClock(AHB1_BUS, PERIPHERAL_EN_GPIOB);
	MRCC_voidEnablePeripheralClock(APB1_BUS, PERIPHERAL_EN_TIM2);
	MTIMER_vStartTime(TIMER2);
	MNVIC_voidEnableInterrupt(MNVIC_TIM2);
	HULTRA_vInitialize(ULTRA_SONIC2, TIMER2, CH2);
	// the back one		(A15)
	MRCC_voidEnablePeripheralClock(AHB1_BUS, PERIPHERAL_EN_GPIOA);
	MRCC_voidEnablePeripheralClock(APB1_BUS, PERIPHERAL_EN_TIM2);
	MTIMER_vStartTime(TIMER2);
	MNVIC_voidEnableInterrupt(MNVIC_TIM2);
	HULTRA_vInitialize(ULTRA_SONIC1, TIMER2, CH1);
	//--------Motor Driver--------// 	//B6
	HAL_MOTOR_Init(&Motor_1);
	HAL_MOTOR_STOP(&Motor_1);
	//--------Servo motor --------// 	//A6
	MRCC_voidEnablePeripheralClock(AHB1_BUS, PERIPHERAL_EN_GPIOA);
	MRCC_voidEnablePeripheralClock(APB1_BUS, PERIPHERAL_EN_TIM3);
	HSERVO_vServoInit(TIMER3,CH1);
	HSERVO_vServoDeg(90);
	//--------------------------------------*/
	//--------------------------------------*/


	//------------TEST AREA-----------------*/
	LED_On(&Led_1);
	LED_On(&Led_2);
	_delay_s(10);
	LED_Off(&Led_1);
	LED_Off(&Led_2);
	//--------------------------------------*/


	//--------Enable Interrupts-------------//
	MNVIC_voidEnableInterrupt(MNVIC_USART1);		//UART
	//--------------------------------------*/
	LED_On(&Led_3);		//Indicate stop condition at start
	while(1){
		//---------------//
		Led_Toggle(&Led_0);
		//---------------//

		//get ULTRA_SONIC_X distances_X
		HULTRA_vSendTrigger(&UltraS_t_F);
		HULTRA_vGetDistance(ULTRA_SONIC2, &Distance_F);
		HULTRA_vSendTrigger(&UltraS_t_B);
		HULTRA_vGetDistance(ULTRA_SONIC1, &Distance_B);

		//---------------------------------------------------------------------------------------
		//-------------------------------------	 FORWARD APP  -----------------------------------

		if('W'==R_data_Flag && Distance_F>20){
			HAL_MOTOR_MOVE(&Motor_1, FORWARD, 80);
			HSERVO_vServoDeg(90);
			LED_On(&Led_1);
			LED_Off(&Led_2);
			LED_Off(&Led_3);
			//MUSART_u8Send_Data(USART1,"FORWARD ");//--
			R_data_Flag='0';
			currunt_motion=FORWARD;
		}
		else if(currunt_motion==FORWARD && Distance_F<=20){
			HAL_MOTOR_MOVE(&Motor_1, STOP, 0);
			HSERVO_vServoDeg(90);
			LED_Off(&Led_1);
			LED_Off(&Led_2);
			LED_On(&Led_3);
			// buzzer alarm
			//MUSART_u8Send_Data(USART1,"STOP ");//--
			R_data_Flag='0';
			currunt_motion=STOP;
		}
		else{
			//
		}

		//---------------------------------------------------------------------------------------
		//-------------------------------------	 BACKWARD APP  ----------------------------------

		if('S'==R_data_Flag && Distance_B>20){
			HAL_MOTOR_MOVE(&Motor_1, BACKWARD, 80);
			HSERVO_vServoDeg(90);
			LED_Off(&Led_1);
			LED_On(&Led_2);
			LED_Off(&Led_3);
			//MUSART_u8Send_Data(USART1,"BACKWARD ");//--
			R_data_Flag='0';
			currunt_motion=BACKWARD;
		}
		else if(currunt_motion==BACKWARD && Distance_B<=20){
			HAL_MOTOR_MOVE(&Motor_1, STOP, 0);
			HSERVO_vServoDeg(90);
			LED_Off(&Led_1);
			LED_Off(&Led_2);
			LED_On(&Led_3);
			// buzzer alarm
			//MUSART_u8Send_Data(USART1,"STOP ");//--
			R_data_Flag='0';
			currunt_motion=STOP;

		}
		else{
			//
		}
		//---------------------------------------------------------------------------------------
		//-------------------------------------	 AUTOPARK APP  ----------------------------------

		//HSERVO_vServoDeg(i);//---








	}
}

/* USER CODE END 0 */
/* Functions ---------------------------------------------------------*/

void RECIVE_INT(void)
{
	MUSART_u8INT_Receive_Byte(USART1,&R_data);
	// software rest to the bootloader
	if('1'==R_data){
		LED_Off(&Led_0);
		MNVIC_voidDisableInterrupt(MNVIC_USART1);
		MUSART_voidDisable(USART1);
		//reset soft//
		WWDT_voidMakeSoftWareReset();
	}
	// Forward parking
	else if('W'==R_data){
		R_data_Flag='W';
	}
	// Backward parking
	else if('S'==R_data){
		R_data_Flag='S';
	}
	// Auto parking
	else if('A'==R_data){
		R_data_Flag='A';
	}
	//
	else{
		//MUSART_u8Send_Data(USART1,"ERROR ");//-----
	}
	//MUSART_u8Send_Data(USART1,"recived int \n ");//-----
	MUSART_u8Send_Data(USART1,MUSART_NewLine);
}


#define WWDT_CR            *((volatile u32 *)(0x40002C00))
void WWDT_voidMakeSoftWareReset(void)
{
	MRCC_voidEnablePeripheralClock(APB1,PERIPHERAL_EN_WWDG);
	WWDT_CR=0xBF;
	while(1);
}



/*______________________________________________
________________________________________________
______________________ ... _____________________
______________________| W |_____________________
_______________________...______________________
________________________________________________
________________ -	   ... 	   - _______________
_______________| A |__| S |__| D |______________
________________ -	   ...	   - _______________
________________________________________________
________________________________________________*/
