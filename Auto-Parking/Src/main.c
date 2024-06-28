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
extern const LedX_t 		Led_0;//,Led_1,Led_2,Led_3,Leds_F,Leds_B;//embedded blue  ,1,2,3 red
extern const UltraSX_t  	UltraS_t_F_B;			//Ultrasonics trigger 1&2..6
extern const MotorX_t		Motor_1,Motor_2;		//DC Motors  1,2
/* USER CODE END externs */

/* Global variables  ---------------------------------------------------------*/
u8  R_data=0; 	   			//USART date
u8  R_data_Flag=0;   		//USART date flag
u8  currunt_turn=NO_TURN;   //servo motion flag
u8  currunt_motion=STOP;	//dc motion flag
u8  SPEED=80;				//dc motors speed 0-100

f64 Distance_F =0; //distance from ultraS_1 (front)			  -
f64 Distance_B =0; //distance from ultraS_2	(back)			  _
f64 Distance_Rf=0; //distance from ultraS_3	(right front)	.	|
f64 Distance_Rb=0; //distance from ultraS_4	(right back)	.	|
f64 Distance_Lf=0; //distance from ultraS_5	(left front)	|	.
f64 Distance_Lb=0; //distance from ultraS_6	(left back)		|	.
/* Global variables  END */

/*functions deceleration -----------------------------------------------------*/
void HAL_Rear_Drive(u8 DIRCTION);
void HAL_Rear_Drive_Collision(u8 DIRCTION, u8 speed );
void RECIVE_INT(void);
void WWDT_voidMakeSoftWareReset(void);
/* functions deceleration  END */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int main(void)
{
	u8 Parking_Available=0;
	/*System Clock is 16MHz from HSI*/
	MRCC_voidInitSystemClk();
	MSTK_voidInit();
	_delay_ms(500);
	//--------LEDs --------//
	MRCC_voidEnablePeripheralClock(AHB1,GPIOC_PORT );
	LED_Init(&Led_0);
	LED_Off(&Led_0);
	//LED_Off (&Led_0);
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
	// the front one	(B3)
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
	// the front right	(A3)
	MRCC_voidEnablePeripheralClock(AHB1_BUS, PERIPHERAL_EN_GPIOA);
	MRCC_voidEnablePeripheralClock(APB1_BUS, PERIPHERAL_EN_TIM2);
	MTIMER_vStartTime(TIMER2);
	MNVIC_voidEnableInterrupt(MNVIC_TIM2);
	HULTRA_vInitialize(ULTRA_SONIC3, TIMER2, CH4);
	// the front back	A2
	MRCC_voidEnablePeripheralClock(AHB1_BUS, PERIPHERAL_EN_GPIOA);
	MRCC_voidEnablePeripheralClock(APB1_BUS, PERIPHERAL_EN_TIM2);
	MTIMER_vStartTime(TIMER2);
	MNVIC_voidEnableInterrupt(MNVIC_TIM2);
	HULTRA_vInitialize(ULTRA_SONIC4, TIMER2, CH3);





	//--------Motor Driver--------// 	PWM pin:	B6	B7
	HAL_MOTOR_Init(&Motor_1);
	HAL_MOTOR_STOP(&Motor_1);
	HAL_MOTOR_Init(&Motor_2);
	HAL_MOTOR_STOP(&Motor_2);
	//--------Servo motor --------// 	A6
	MRCC_voidEnablePeripheralClock(AHB1_BUS, PERIPHERAL_EN_GPIOA);
	MRCC_voidEnablePeripheralClock(APB1_BUS, PERIPHERAL_EN_TIM3);
	HSERVO_vServoInit(TIMER3,CH1);
	HSERVO_vServoDeg(NO_TURN);
	//--------------------------------------*/
	//--------------------------------------*/



	//--------------------TEST AREA-------------------------*/
	//LED_Off (&Led_0);
	//------------------------------------------------------*/



	//--------Enable Interrupts-------------//
	MNVIC_voidEnableInterrupt(MNVIC_USART1);		//UART
	//--------------------------------------*/

	while(1){
		//---------------//
		Led_Toggle(&Led_0);//Indicate the App is not stuck in something
		//---------------//

		//get ULTRA_SONIC_X distances_X
		HULTRA_vSendTrigger(&UltraS_t_F_B);				//send trigeer for both 1,2,3,4

		HULTRA_vGetDistance(ULTRA_SONIC2, &Distance_F);
		HULTRA_vGetDistance(ULTRA_SONIC1, &Distance_B);
		HULTRA_vGetDistance(ULTRA_SONIC3, &Distance_Rf);
		HULTRA_vGetDistance(ULTRA_SONIC4, &Distance_Rb);

		//---------------------------------------------------------------------------------------
		//-------------------------------------	 FORWARD APP  -----------------------------------

		if ((('W'==R_data_Flag)||(currunt_motion==FORWARD)) && (Distance_F<=20)) {
			HAL_Rear_Drive(STOP);
			HSERVO_vServoDeg(NO_TURN);
			//MUSART_u8Send_Data(USART1,"STOP ");//--
			R_data_Flag='0';
			currunt_motion=STOP;
			currunt_turn=NO_TURN;
			//MNVIC_voidEnableInterrupt(MNVIC_USART1);
		}
		else if(('W'==R_data_Flag) && (Distance_F>20)){
			//MNVIC_voidDisableInterrupt(MNVIC_USART1);
			HAL_Rear_Drive(FORWARD);
			HSERVO_vServoDeg(NO_TURN);
			//MUSART_u8Send_Data(USART1,"FORWARD ");//--
			R_data_Flag='0';
			currunt_motion=FORWARD;
			currunt_turn=NO_TURN;
		}
		else{
			//Forbidden//
		}

		//---------------------------------------------------------------------------------------
		//-------------------------------------	 BACKWARD APP  ----------------------------------
		//make it to stop after a delay and with the ultra sonic to be logiacly
		if ((('S'==R_data_Flag)||(currunt_motion==BACKWARD)) && ((Distance_B<=20)||(Distance_Rf>=20))) {
			HAL_Rear_Drive(STOP);
			HSERVO_vServoDeg(NO_TURN);
			//MUSART_u8Send_Data(USART1,"STOP ");//--
			R_data_Flag='0';
			currunt_motion=STOP;
			currunt_turn=NO_TURN;
			//MNVIC_voidEnableInterrupt(MNVIC_USART1);
		}
		else if(('S'==R_data_Flag) && (Distance_B>20)){
			//MNVIC_voidDisableInterrupt(MNVIC_USART1);
			HAL_Rear_Drive(BACKWARD);
			HSERVO_vServoDeg(NO_TURN);
			//MUSART_u8Send_Data(USART1,"FORWARD ");//--
			R_data_Flag='0';
			currunt_motion=BACKWARD;
			currunt_turn=NO_TURN;
		}
		else{
			//Forbidden//
		}

		//---------------------------------------------------------------------------------------
		//-------------------------------------	 AUTOPARK APP  ----------------------------------
		if('A'==R_data_Flag ){
			if((Distance_F <= 20)){
				HAL_Rear_Drive(STOP);

			}
			// first block
			if((Distance_Rb <= 20) && (Distance_Rf <= 20) && (Parking_Available == 0))
			{
				HAL_Rear_Drive(FORWARD);

			}
			//finding position
			else if((Distance_Rf > 20) && (Distance_Rb > 20) && (Parking_Available == 0))
			{
				/*	HAL_Rear_Drive(STOP);
				_delay_ms(250);*/
				HAL_Rear_Drive(FORWARD);
				Parking_Available = 1;

			}

			if((Distance_Rb <= 25) && (Distance_Rf <= 25) && (Parking_Available == 1))
			{
				HAL_Rear_Drive(STOP);
				_delay_ms(50);
				HAL_Rear_Drive(BACKWARD);
				_delay_ms(200);
				HAL_Rear_Drive(STOP);
				_delay_ms(100);
				HSERVO_vServoDeg(110);
				_delay_ms(200);
				HAL_Rear_Drive(BACKWARD);
				_delay_ms(1500);


				HAL_Rear_Drive(STOP);
				_delay_ms(100);
				HSERVO_vServoDeg(LEFT);
				_delay_ms(100);
				HAL_Rear_Drive(BACKWARD);


				HULTRA_vSendTrigger(&UltraS_t_F_B);				//send trigeer for both 1,2,3,4

				HULTRA_vGetDistance(ULTRA_SONIC4, &Distance_Rb);
				_delay_ms(20);
				HULTRA_vGetDistance(ULTRA_SONIC1, &Distance_B);

				while(Distance_Rb > 25 || Distance_B > 20)
				{
					HAL_Rear_Drive(BACKWARD);
					_delay_ms(10);
					HULTRA_vSendTrigger(&UltraS_t_F_B);				//send trigeer for both 1,2,3,4

					HULTRA_vGetDistance(ULTRA_SONIC4, &Distance_Rb);
					_delay_ms(10);
					HULTRA_vGetDistance(ULTRA_SONIC1, &Distance_B);
				}



				HAL_Rear_Drive(STOP);
				_delay_ms(20);
				//HSERVO_vServoDeg(RIGHT);
				//_delay_ms(50);
				HAL_Rear_Drive(FORWARD);
				//_delay_ms(1500);
				HULTRA_vSendTrigger(&UltraS_t_F_B);				//send trigeer for both 1,2,3,4

				HULTRA_vGetDistance(ULTRA_SONIC4, &Distance_Rb);
				_delay_ms(10);
				HULTRA_vGetDistance(ULTRA_SONIC3, &Distance_Rf);
				_delay_ms(10);
				HULTRA_vGetDistance(ULTRA_SONIC2, &Distance_F);

				while ((Distance_Rb > 20 || Distance_Rf > 20) || Distance_F >18)
				{
					_delay_ms(20);
					HSERVO_vServoDeg(RIGHT);
					_delay_ms(20);
					HAL_Rear_Drive(FORWARD);
					HULTRA_vSendTrigger(&UltraS_t_F_B);				//send trigeer for both 1,2,3,4
					if((1.2 >= (Distance_Rb/Distance_Rf)) && (0.8<=(Distance_Rb/Distance_Rf)))
					{
						HAL_Rear_Drive(STOP);
						break;
					}
					HULTRA_vGetDistance(ULTRA_SONIC4, &Distance_Rb);
					_delay_ms(10);
					HULTRA_vGetDistance(ULTRA_SONIC3, &Distance_Rf);
					_delay_ms(10);
					HULTRA_vGetDistance(ULTRA_SONIC2, &Distance_F);
				}

				HAL_Rear_Drive(STOP);
				_delay_ms(20);
				HSERVO_vServoDeg(NO_TURN);

				//_delay_ms(700);
				Parking_Available =2;
			}
		}

		//---------------------------------------------------------------------------------------
		//-----------------------------	 collision avoidance APP  -------------------------------

		if('O'==R_data_Flag ){

			HULTRA_vGetDistance(ULTRA_SONIC2, &Distance_F);

			if(Distance_F<=70 && Distance_F>=50)
			{
				HAL_Rear_Drive_Collision(FORWARD,95);
			}
			else if(Distance_F<50 && Distance_F>=35)
			{
				HAL_Rear_Drive_Collision(FORWARD,85);
			}
			else if(Distance_F<35 && Distance_F>=22)
			{
				HAL_Rear_Drive_Collision(FORWARD,70);
			}
			else if(Distance_F<22)
			{
				HAL_Rear_Drive_Collision(STOP,0);
				R_data_Flag='0';
			}
		}


	}
}
/* USER CODE END 0 */
/* Functions ---------------------------------------------------------*/

void HAL_Rear_Drive(u8 DIRCTION)
{
	HAL_MOTOR_MOVE(&Motor_1, DIRCTION, SPEED);
	HAL_MOTOR_MOVE(&Motor_2, DIRCTION, SPEED);

}
void HAL_Rear_Drive_Collision(u8 DIRCTION, u8 speed )
{
	HAL_MOTOR_MOVE(&Motor_1, DIRCTION, speed);
	HAL_MOTOR_MOVE(&Motor_2, DIRCTION, speed);

}

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
	else if('O'==R_data){
		R_data_Flag='O';
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
