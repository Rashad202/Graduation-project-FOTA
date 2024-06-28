/*******************************************************************************************************/
/* Author            : GP_FOTA_TEAM                                                                    */
/* Version           : V0.0.0                                                                          */
/* Data              : 3 Feb 2024                                                                      */
/* Description       : TIMER_program.c --> implementations                                             */
/*******************************************************************************************************/


/*******************************************************************************************************/
/*                                      Standard Types LIB                                             */
#include "../../Libraries/STD_TYPES.h"
#include "../../Libraries/BIT_MATH.h"

/*******************************************************************************************************/
/*                                      MCAL Components                                                */
#include "MTIMER_config.h"
#include "MTIMER_interface.h"
#include "MTIMER_private.h"

#include"../MGPIO/MGPIO_interface.h"
/*******************************************************************************************************/
/*                                      Functions Implementations                                      */
/*******************************************************************************************************/
//Global Pointer to be used for TIMER IRQ Call Back Functions
static void (*GLOBAL_Ptr[8])(void)={NULL};

/*******************************************************************************************************/
/*                                		 LOC_TIMER_ICU Function                                    */
/*-----------------------------------------------------------------------------------------------------*/
static void LOC_TIMER_ICU(Enum_TIMER_NUM Copy_u8TimerNum, Enum_TIMER_CHs Copy_u8ChannelNum);
/*******************************************************************************************************/

//Global Array to Store each CH Captured Pulse width value
u32 Time[29]={0};

/*******************************************************************************************************/
/*                                      GET_TIMER Function                                         */
/*-----------------------------------------------------------------------------------------------------*/

static TIM2_5_MemMap_t* GET_TIMER(u32 Copy_u8TimerNum) {
	// Array containing the offsets of TIMER registers for different TIMers.
	u32 Timer_Offset[8] = TIMERS_OFFSET;

	// Calculate the base address of the specified TIMER using its offset.
	TIM2_5_MemMap_t* TIMx = (TIM2_5_MemMap_t*)((u32)TIM2 + Timer_Offset[Copy_u8TimerNum - 1]);

	// Return the pointer to the memory-mapped structure of the specified TIMER.
	return TIMx;
}
/*******************************************************************************************************/

/*******************************************************************************************************/
/*                                      01- MTIMER_vStartTime                                          */
/*-----------------------------------------------------------------------------------------------------*/
void MTIMER_vStartTime(Enum_TIMER_NUM Copy_u8TimerNum) {
	// Get the base address of the specified timer
	TIM2_5_MemMap_t* TIMx = GET_TIMER(Copy_u8TimerNum);

	// Reset Control Register 1 Value
	TIMx->CR1 = 0;

	// Set the prescaler value to achieve a 1ms time base
	TIMx->PSC = SYS_CLOCK * 1000 - 1;

	// Set the auto-reload value to MAX Value
	TIMx->ARR = 0xFFFFFFFF;

	// Set the Counter Enable bit to start the timer
	SET_BIT(TIMx->CR1, CEN);

	// Ensure Starting CNT from 0 as of some problems with TIMER2 and TIMER 5 if "ARR >0x0020000"
	TIMx->CNT = 0xFFFFFFFF;
}
/*******************************************************************************************************/

/*******************************************************************************************************/
/*                       				 02- MTIMER_vContTimer                                         */
/*-----------------------------------------------------------------------------------------------------*/
void MTIMER_vCntTimer(Enum_TIMER_NUM Copy_u8TimerNum, Enum_Timer_Cont Copy_u8TimerCont) {
	// Get the base address of the specified timer
	TIM2_5_MemMap_t* TIMx = GET_TIMER(Copy_u8TimerNum);

	// Check the desired action for the TIMER
	switch (Copy_u8TimerCont) {
	case StopTimer:
		// Clear the Counter Enable bit to stop the timer
		CLR_BIT(TIMx->CR1, CEN);
		break;
	case ContinueTimer:
		// Set the Counter Enable bit to continue or start the timer
		SET_BIT(TIMx->CR1, CEN);
		break;
	}
}
/*******************************************************************************************************/

/*******************************************************************************************************/
/*                                      03- MTIMER_vDelayms                                  		   */
/*-----------------------------------------------------------------------------------------------------*/
void MTIMER_vDelayms(Enum_TIMER_NUM	Copy_u8TimerNum,u32 Copy_u32Delayms){
	// Get the base address of the specified timer
	TIM2_5_MemMap_t* TIMx = GET_TIMER(Copy_u8TimerNum);

	// Reset Control Register 1 Value
	TIMx->CR1 = 0;

	// Set the prescaler value to achieve a 1ms time base
	TIMx->PSC = SYS_CLOCK * 1000 - 1;

	// Set the auto-reload value to MAX Value
	TIMx->ARR = Copy_u32Delayms;

	// Set the Counter Enable bit to start the timer
	SET_BIT(TIMx->CR1, CEN);

	// Ensure Starting CNT from 0 as of some problems with TIMER2 and TIMER 5 if "ARR >0x0020000"
	TIMx->CNT = 0xFFFFFFFF;
	// Wait for Update flag to be zero
	while (!GET_BIT(TIMx->SR, 0));
	// Clear the update interrupt flag of TIMx
	CLR_BIT(TIMx->SR,0);
	// Wait for the Timer to reach zero (polling)
	while ( !GET_BIT(TIMx->SR, 0) );
	// Clear the update interrupt flag of TIM1
	CLR_BIT(TIMx->SR,0);
	// Clear Enable bit to disable the timer
	CLR_BIT(TIMx->CR1, CEN);

}


/*******************************************************************************************************/

/*******************************************************************************************************/
/*                                      04- MTIMER_vPeriodicMS                                         */
/*-----------------------------------------------------------------------------------------------------*/
void MTIMER_vPeriodicMS(Enum_TIMER_NUM Copy_u8TimerNum, u32 Copy_u32Delay) {
	// Get the base address of the specified timer
	TIM2_5_MemMap_t* TIMx = GET_TIMER(Copy_u8TimerNum);

	// Reset Control Register 1 Value
	TIMx->CR1 = 0;

	// Set the prescaler value to achieve a 1ms time base
	TIMx->PSC = SYS_CLOCK * 1000 - 1;

	// Set the auto-reload value to achieve the desired delay
	TIMx->ARR = Copy_u32Delay - 1;

	// Set the Update Interrupt Enable bit to enable the interrupt
	SET_BIT(TIMx->DIER, UIE);

	// Set the Counter Enable bit to start the timer
	SET_BIT(TIMx->CR1, CEN);

	// Ensure Starting CNT from 0 as of some problems with TIMER2 and TIMER 5 if "ARR >0x0020000"
	TIMx->CNT = 0xFFFFFFFF;
}
/*******************************************************************************************************/

/*******************************************************************************************************/
/*                                      05- MTIMER_vPWM                                       		   */
/*-----------------------------------------------------------------------------------------------------*/
void MTIMER_vPWM(Enum_TIMER_NUM Copy_u8TimerNum,Enum_TIMER_CHs Copy_u8Channel,u16 Copy_u16TotalTime_uSec,u16 Copy_u16PositiveDutyCycle_uSec){

	// Configure GPIO pins and alternative functions based on the selected timer and channel
	/*-----------------------------------------------------------------------------------------------------*/
	MGPIO_voidSetPinMode(
			TIMER_PORT_MAP[Copy_u8TimerNum-1][Copy_u8Channel-1],
			TIMER_PIN_MAP[Copy_u8TimerNum-1][Copy_u8Channel-1] ,
			MODE_ALTF
	);
	MGPIO_voidSetPinAltFn(
			TIMER_PORT_MAP[Copy_u8TimerNum-1][Copy_u8Channel-1],
			TIMER_PIN_MAP[Copy_u8TimerNum-1][Copy_u8Channel-1] ,
			TIMER_AF[Copy_u8TimerNum-1]
	);
	/*-----------------------------------------------------------------------------------------------------*/


	// Get the base address of the specified timer
	TIM2_5_MemMap_t* TIMx = GET_TIMER(Copy_u8TimerNum);
	SET_BIT( TIMx->CR1 , ARPE );    // Enable auto-reload preload
	CLR_BIT( TIMx->CR1 , DIR); 		// UP COUNT
	CLR_BIT( TIMx->CR1 , CMS0); 	// 00: Edge-aligned mode. The counter counts up
	CLR_BIT( TIMx->CR1 , CMS1);     // 	   or down depending on the direction bit(DIR)

	//01: CCx channel is configured as output  "PWM"
	CLR_BIT( TIMx->CCMR[Copy_u8Channel / 3] , ( CCxS0+(((Copy_u8Channel-1)%2)*8)) );
	CLR_BIT( TIMx->CCMR[Copy_u8Channel / 3] , ( CCxS1+(((Copy_u8Channel-1)%2)*8)) );

	// set prescaler
	/* TIME Calculation of Total Period:
	 * Total_Period = (PSC / (SYS_CLOCK * 10^6)) * ARR
	 */
	TIMx->PSC = SYS_CLOCK*10-1;
	TIMx->ARR = ( Copy_u16TotalTime_uSec*100 )/1000; // Timer auto-reload to max <<Periodic time>>
	TIMx->CCR[Copy_u8Channel-1] = ( Copy_u16PositiveDutyCycle_uSec*100 )/1000; // << DUTY CYCLE >>
	SET_BIT( TIMx->CCMR[Copy_u8Channel / 3] , ( OCxPE+(((Copy_u8Channel-1)%2)*8)) );  //1: Preload register on TIMx_CCRx enabled

	CLR_BIT( TIMx->CCMR[Copy_u8Channel / 3] , ( OCxM0+(((Copy_u8Channel-1)%2)*8)) );// PWM Mode1 (high then low)
	SET_BIT( TIMx->CCMR[Copy_u8Channel / 3] , ( OCxM1+(((Copy_u8Channel-1)%2)*8)) );
	SET_BIT( TIMx->CCMR[Copy_u8Channel / 3] , ( OCxM2+(((Copy_u8Channel-1)%2)*8)) );

	CLR_BIT( TIMx->CCER ,( CCxP + (Copy_u8Channel-1)*4) ); //Polarity 0: active high
	//SET_BIT(TIMx->EGR,0); //UG: Update generation - 1: Reinitialize counter&update registers
	SET_BIT( TIMx->CCER ,( CCxE + (Copy_u8Channel-1)*4) ); //Bit 0 CC1E: Capture/Compare 1 output enable
	SET_BIT( TIMx->RESERVED2 , 15 );// MOE 1: OC and OCN outputs are enabled

	SET_BIT( TIMx->CR1 , CEN );// Enable timer
	TIMx->CNT = 0xFFFFFFFF;
}
/*******************************************************************************************************/


/*******************************************************************************************************/
/*                                      06- MTIMER_vICU                                       		   */
/*-----------------------------------------------------------------------------------------------------*/
void MTIMER_vICU(Enum_TIMER_NUM Copy_u8TimerNum,Enum_TIMER_CHs Copy_u8Channel){

	// Configure GPIO pins and alternative functions based on the selected timer and channel
	/*-----------------------------------------------------------------------------------------------------*/

	MGPIO_voidSetPinMode(
			TIMER_PORT_MAP[Copy_u8TimerNum-1][Copy_u8Channel-1],
			TIMER_PIN_MAP[Copy_u8TimerNum-1][Copy_u8Channel-1] ,
			MODE_ALTF
	);
	MGPIO_voidSetPinAltFn(
			TIMER_PORT_MAP[Copy_u8TimerNum-1][Copy_u8Channel-1],
			TIMER_PIN_MAP[Copy_u8TimerNum-1][Copy_u8Channel-1] ,
			TIMER_AF[Copy_u8TimerNum-1]
	);
	/*-----------------------------------------------------------------------------------------------------*/


	// Get the base address of the specified timer
	TIM2_5_MemMap_t* TIMx = GET_TIMER(Copy_u8TimerNum);
	SET_BIT( TIMx->CR1 , ARPE );    // Enable auto-reload preload
	CLR_BIT( TIMx->CR1 , DIR ); 	// UP COUNT
	CLR_BIT( TIMx->CR1 , CMS0 ); 	// 00: Edge-aligned mode. The counter counts up
	CLR_BIT( TIMx->CR1 , CMS1 );    // 		or down depending on the direction bit(DIR)

	//01: CCx channel is configured as ICU
	SET_BIT( TIMx->CCMR[Copy_u8Channel / 3] , ( CCxS0 + ( ((Copy_u8Channel-1)%2)*8)) );
	CLR_BIT( TIMx->CCMR[Copy_u8Channel / 3] , ( CCxS1 + ( ((Copy_u8Channel-1)%2)*8)) );

	//FILTERING
	SET_BIT(TIMx->CCMR[Copy_u8Channel / 3],( ICxF0 + ( ((Copy_u8Channel-1)%2)*8)));
	SET_BIT(TIMx->CCMR[Copy_u8Channel / 3],( ICxF1 + ( ((Copy_u8Channel-1)%2)*8)));
	CLR_BIT(TIMx->CCMR[Copy_u8Channel / 3],( ICxF2 + ( ((Copy_u8Channel-1)%2)*8)));
	CLR_BIT(TIMx->CCMR[Copy_u8Channel / 3],( ICxF3 + ( ((Copy_u8Channel-1)%2)*8)));

	// set prescaler
	TIMx -> PSC = (SYS_CLOCK * 100)-1;
	TIMx -> ARR = 0xFFFFFFFF;

	//SET_BIT(TIMx->EGR,0); //UG: Update generation - 1: Reinitialize counter&update registers
	SET_BIT( TIMx->CCER  , ( CCxE + (Copy_u8Channel-1)*4) ); //Bit 0 CC1E: Capture/Compare 1 output enable
	CLR_BIT( TIMx->CCER  , ( CCxP + (Copy_u8Channel-1)*4) );
	SET_BIT( TIMx->DIER  , Copy_u8Channel );

	SET_BIT( TIMx->CR1   , CEN );// Enable timer
	TIMx-> CNT = 0xFFFFFFFF;

}
/*******************************************************************************************************/

/*******************************************************************************************************/
static void LOC_TIMER_ICU(Enum_TIMER_NUM Copy_u8TimerNum,Enum_TIMER_CHs Copy_u8ChannelNum) {
	static u8  captureState [29] = {0};
	static u32 captureValue1[29] = {0};
	static u32 captureValue2[29] = {0};
	TIM2_5_MemMap_t* TIMx = GET_TIMER(Copy_u8TimerNum+1);
	if (captureState[(4*Copy_u8TimerNum+Copy_u8ChannelNum)] == 0) {
		// Capture the time on the rising edge
		captureValue1[(4*Copy_u8TimerNum+Copy_u8ChannelNum)] = TIMx->CCR[Copy_u8ChannelNum];

		// Enable falling edge capture
		SET_BIT(TIMx->CCER, (CCxP + Copy_u8ChannelNum*4) );

		// Move to the next state
		captureState[(4*Copy_u8TimerNum+Copy_u8ChannelNum)] = 1;
	} else {
		// Capture the time on the falling edge
		captureValue2[(4*Copy_u8TimerNum+Copy_u8ChannelNum)] = TIMx->CCR[Copy_u8ChannelNum];

		// Enable rising edge capture
		CLR_BIT(TIMx->CCER, (CCxP + Copy_u8ChannelNum*4) );

		// Calculate the time difference
		Time[(4*Copy_u8TimerNum+Copy_u8ChannelNum)] = captureValue2[(4*Copy_u8TimerNum+Copy_u8ChannelNum)] - captureValue1[(4*Copy_u8TimerNum+Copy_u8ChannelNum)];

		// Reset state value
		captureState[(4*Copy_u8TimerNum+Copy_u8ChannelNum)] = 0;
	}
}
/*******************************************************************************************************/

/*******************************************************************************************************/
/*                                      07- MTIMER_GET_ICU                                       	   */
/*-----------------------------------------------------------------------------------------------------*/
u32 MTIMER_GET_ICU(Enum_TIMER_NUM Copy_u8TimerNum, Enum_TIMER_CHs Copy_u8Channel) {
	return Time[(4 * (Copy_u8TimerNum - 1) + (Copy_u8Channel - 1))];//return Time[(4 * (Copy_u8TimerNum - 1) + Copy_u8Channel)];
}
/*******************************************************************************************************/

/*******************************************************************************************************/
/*                                      08- MTIMER_CallBack                                       	   */
/*-----------------------------------------------------------------------------------------------------*/
void MTIMER_CallBack(Enum_TIMER_NUM Copy_u8TimerNum, void (*ptr)(void)) {
	// Set the callback function pointer in the GLOBAL_Ptr array
	GLOBAL_Ptr[Copy_u8TimerNum - 1] = ptr;
}
/*******************************************************************************************************/


/*******************************************************************************************************/
/*
 * @note    This function is called when either TIM1 or TIM10 triggers an interrupt.
 */
void TIM1_UP_TIM10_IRQHandler(void) {
	// Check if the update interrupt flag of TIM1 is set
	if (GET_BIT(TIM1->SR, 0)) {

		// Check if a callback function is registered for TIM1
		if (GLOBAL_Ptr[0] != NULL) {
			// Call the callback function for TIM1
			GLOBAL_Ptr[0]();
		}

		// Clear the update interrupt flag of TIM1
		CLR_BIT(TIM1->SR, 0);
	}
	else {
		// Check if the capture/compare interrupt flag for CH1 of TIM10 is set
		if (GET_BIT(TIM10->SR, 1)) {

			// Call the LOC_TIMER_ICU function for handling CH1 interrupt of TIM10
			LOC_TIMER_ICU(TIMER10 - 1, CH1 - 1);

			// Clear the capture/compare interrupt flag for CH1 of TIM10
			CLR_BIT(TIM10->SR, CH1);
		}
		// Check if the update interrupt flag of TIM10 is set
		if (GET_BIT(TIM10->SR, 0)) {

			// Check if a callback function is registered for TIM10 (at index 6 in GLOBAL_Ptr array)
			if (GLOBAL_Ptr[6] != NULL) {

				// Call the callback function for TIM10
				GLOBAL_Ptr[6]();

				// Clear the update interrupt flag of TIM10
				CLR_BIT(TIM10->SR, 0);
			}
			else {
				// Clear the update interrupt flag of TIM10 without calling a callback function
				CLR_BIT(TIM10->SR, 0);
			}
		}
	}
}
/*******************************************************************************************************/


/*******************************************************************************************************/
/*
 * @note    This function is called when either TIM1 triggers a trigger/completion or TIM11 triggers an interrupt.
 */
void TIM1_TRG_COM_TIM11_IRQHandler(void) {

	// Check if the trigger interrupt or COM interrupt flag of TIM1 is set
	if (GET_BIT(TIM1->SR, 5) || GET_BIT(TIM1->SR, 6)) {
		// Handle TIMER1 trigger or COM interrupt
		// Add the necessary code or call a function for TIMER1 trigger or COM handling
	}
	else {
		// Check if the capture/compare interrupt flag for CH1 of TIM11 is set
		if (GET_BIT(TIM11->SR, 1)) {

			// Call the LOC_TIMER_ICU function for handling CH1 interrupt of TIM11
			LOC_TIMER_ICU(TIMER11 - 1, CH1 - 1);

			// Clear the capture/compare interrupt flag for CH1 of TIM11
			CLR_BIT(TIM11->SR, CH1);
		}
		// Check if the update interrupt flag of TIM11 is set
		if (GET_BIT(TIM11->SR, 0)) {

			// Check if a callback function is registered for TIM11 (at index 7 in GLOBAL_Ptr array)
			if (GLOBAL_Ptr[7] != NULL) {

				// Call the callback function for TIM11
				GLOBAL_Ptr[7]();

				// Clear the update interrupt flag of TIM11
				CLR_BIT(TIM11->SR, 0);
			}
			else {
				// Clear the update interrupt flag of TIM11 without calling a callback function
				CLR_BIT(TIM11->SR, 0);
			}
		}
	}
}
/*******************************************************************************************************/

/*******************************************************************************************************/
/*
 * @note    This function is called when either TIM1 triggers a break interrupt or TIM9 triggers an interrupt.
 */
void TIM1_BRK_TIM9_IRQHandler(void) {
	// Check if the break interrupt flag of TIM1 is set
	if (GET_BIT(TIM1->SR, 7)) {
		// Handle TIMER1 break interrupt
		// Add the necessary code or call a function for TIMER1 break handling
	}
	else {

		// Check if the capture/compare interrupt flag for CH1 of TIM9 is set
		if (GET_BIT(TIM9->SR, 1)) {

			// Call the LOC_TIMER_ICU function for handling CH1 interrupt of TIM9
			LOC_TIMER_ICU(TIMER9 - 1, CH1 - 1);

			// Clear the capture/compare interrupt flag for CH1 of TIM9
			CLR_BIT(TIM9->SR, CH1);
		}
		else if (GET_BIT(TIM9->SR, 2)) {
			// Call the LOC_TIMER_ICU function for handling CH2 interrupt of TIM9
			LOC_TIMER_ICU(TIMER9 - 1, CH2 - 1);

			// Clear the capture/compare interrupt flag for CH2 of TIM9
			CLR_BIT(TIM9->SR, CH2);
		}
		// Check if the update interrupt flag of TIM9 is set
		if (GET_BIT(TIM9->SR, 0)) {

			// Check if a callback function is registered for TIM9 (at index 5 in GLOBAL_Ptr array)
			if (GLOBAL_Ptr[5] != NULL) {

				// Call the callback function for TIM9
				GLOBAL_Ptr[5]();

				// Clear the update interrupt flag of TIM9
				CLR_BIT(TIM9->SR, 0);
			}
			else {
				// Clear the update interrupt flag of TIM9 without calling a callback function
				CLR_BIT(TIM9->SR, 0);
			}
		}
	}
}
/*******************************************************************************************************/

/*******************************************************************************************************/
/*
 * @note    This function is called when any of the capture/compare channels (CH1-CH4)
 * 				 of TIM1 triggers an interrupt.
 */
void TIM1_CC_IRQHandler(void) {
	// Check if the capture/compare interrupt flag for CH1 of TIM1 is set
	if (GET_BIT(TIM1->SR, 1)) {

		// Call the LOC_TIMER_ICU function for handling CH1 interrupt of TIM1
		LOC_TIMER_ICU(TIMER1 - 1, CH1 - 1);

		// Clear the capture/compare interrupt flag for CH1 of TIM1
		CLR_BIT(TIM1->SR, CH1);
	}
	else if (GET_BIT(TIM1->SR, 2)) {

		// Call the LOC_LOC_TIMER_ICU function for handling CH2 interrupt of TIM1
		LOC_TIMER_ICU(TIMER1 - 1, CH2 - 1);

		// Clear the capture/compare interrupt flag for CH2 of TIM1
		CLR_BIT(TIM1->SR, CH2);
	}
	else if (GET_BIT(TIM1->SR, 3)) {

		// Call the LOC_TIMER_ICU function for handling CH3 interrupt of TIM1
		LOC_TIMER_ICU(TIMER1 - 1, CH3 - 1);

		// Clear the capture/compare interrupt flag for CH3 of TIM1
		CLR_BIT(TIM1->SR, CH3);
	}
	else {
		// Call the LOC_TIMER_ICU function for handling CH4 interrupt of TIM1
		LOC_TIMER_ICU(TIMER1 - 1, CH4 - 1);

		// Clear the capture/compare interrupt flag for CH4 of TIM1
		CLR_BIT(TIM1->SR, CH4);
	}
}
/*******************************************************************************************************/

/*******************************************************************************************************/
/*
 * @note    This function is called when any of the capture/compare channels (CH1-CH4) or
 * 				the update interrupt of TIM2 triggers an interrupt.
 */
void TIM2_IRQHandler(void) {
	// Check if the capture/compare interrupt flag for CH1 of TIM2 is set
	if (GET_BIT(TIM2->SR, 1)) {
		// Call the LOC_TIMER_ICU function for handling CH1 interrupt of TIM2
		LOC_TIMER_ICU(TIMER2 - 1, CH1 - 1);

		// Clear the capture/compare interrupt flag for CH1 of TIM2
		CLR_BIT(TIM2->SR, CH1);
	}
	else if (GET_BIT(TIM2->SR, 2)) {
		// Call the LOC_TIMER_ICU function for handling CH2 interrupt of TIM2
		LOC_TIMER_ICU(TIMER2 - 1, CH2 - 1);

		// Clear the capture/compare interrupt flag for CH2 of TIM2
		CLR_BIT(TIM2->SR, CH2);
	}
	else if (GET_BIT(TIM2->SR, 3)) {
		// Call the LOC_TIMER_ICU function for handling CH3 interrupt of TIM2
		LOC_TIMER_ICU(TIMER2 - 1, CH3 - 1);

		// Clear the capture/compare interrupt flag for CH3 of TIM2
		CLR_BIT(TIM2->SR, CH3);
	}
	else if (GET_BIT(TIM2->SR, 4)) {
		// Call the LOC_TIMER_ICU function for handling CH4 interrupt of TIM2
		LOC_TIMER_ICU(TIMER2 - 1, CH4 - 1);

		// Clear the capture/compare interrupt flag for CH4 of TIM2
		CLR_BIT(TIM2->SR, CH4);
	}

	// Check if the update interrupt flag of TIM2 is set
	if (GET_BIT(TIM2->SR, 0)) {
		// Check if a callback function is registered for TIM2 (at index 2 in GLOBAL_Ptr array)
		if (GLOBAL_Ptr[1] != NULL) {

			// Call the callback function for TIM2
			GLOBAL_Ptr[1]();

			// Clear the update interrupt flag of TIM2
			CLR_BIT(TIM2->SR, 0);
		}
		else {
			// Clear the update interrupt flag of TIM2 without calling a callback function
			CLR_BIT(TIM2->SR, 0);
		}
	}
}
/*******************************************************************************************************/


/*******************************************************************************************************/
/*
 * @note    This function is called when any of the capture/compare channels (CH1-CH4) or
 * 			 the update interrupt of TIM3 triggers an interrupt.
 */
void TIM3_IRQHandler(void) {
	// Check if the capture/compare interrupt flag for CH1 of TIM3 is set
	if (GET_BIT(TIM3->SR, 1)) {
		// Call the LOC_TIMER_ICU function for handling CH1 interrupt of TIM3
		LOC_TIMER_ICU(TIMER3 - 1, CH1 - 1);

		// Clear the capture/compare interrupt flag for CH1 of TIM3
		CLR_BIT(TIM3->SR, CH1);
	}
	else if (GET_BIT(TIM3->SR, 2)) {
		// Call the LOC_TIMER_ICU function for handling CH2 interrupt of TIM3
		LOC_TIMER_ICU(TIMER3 - 1, CH2 - 1);

		// Clear the capture/compare interrupt flag for CH2 of TIM3
		CLR_BIT(TIM3->SR, CH2);
	}
	else if (GET_BIT(TIM3->SR, 3)) {
		// Call the LOC_TIMER_ICU function for handling CH3 interrupt of TIM3
		LOC_TIMER_ICU(TIMER3 - 1, CH3 - 1);

		// Clear the capture/compare interrupt flag for CH3 of TIM3
		CLR_BIT(TIM3->SR, CH3);
	}
	else if (GET_BIT(TIM3->SR, 4)) {
		// Call the LOC_TIMER_ICU function for handling CH4 interrupt of TIM3
		LOC_TIMER_ICU(TIMER3 - 1, CH4 - 1);

		// Clear the capture/compare interrupt flag for CH4 of TIM3
		CLR_BIT(TIM3->SR, CH4);
	}

	// Check if the update interrupt flag of TIM3 is set
	if (GET_BIT(TIM3->SR, 0)) {
		// Check if a callback function is registered for TIM3 (at index 3 in GLOBAL_Ptr array)
		if (GLOBAL_Ptr[2] != NULL) {

			// Call the callback function for TIM3
			GLOBAL_Ptr[2]();

			// Clear the update interrupt flag of TIM3
			CLR_BIT(TIM3->SR, 0);
		}
		else {
			// Clear the update interrupt flag of TIM3 without calling a callback function
			CLR_BIT(TIM3->SR, 0);
		}
	}
}
/*******************************************************************************************************/

/*******************************************************************************************************/
/*
 * @note    This function is called when any of the capture/compare channels (CH1-CH4) or
 * 			 the update interrupt of TIM4 triggers an interrupt.
 */
void TIM4_IRQHandler(void) {
	// Check if the capture/compare interrupt flag for CH1 of TIM4 is set
	if (GET_BIT(TIM4->SR, 1)) {

		// Call the LOC_TIMER_ICU function for handling CH1 interrupt of TIM4
		LOC_TIMER_ICU(TIMER4 - 1, CH1 - 1);

		// Clear the capture/compare interrupt flag for CH1 of TIM4
		CLR_BIT(TIM4->SR, CH1);
	}
	else if (GET_BIT(TIM4->SR, 2)) {
		// Call the LOC_TIMER_ICU function for handling CH2 interrupt of TIM4
		LOC_TIMER_ICU(TIMER4 - 1, CH2 - 1);

		// Clear the capture/compare interrupt flag for CH2 of TIM4
		CLR_BIT(TIM4->SR, CH2);
	}
	else if (GET_BIT(TIM4->SR, 3)) {
		// Call the LOC_TIMER_ICU function for handling CH3 interrupt of TIM4
		LOC_TIMER_ICU(TIMER4 - 1, CH3 - 1);

		// Clear the capture/compare interrupt flag for CH3 of TIM4
		CLR_BIT(TIM4->SR, CH3);
	}
	else if (GET_BIT(TIM4->SR, 4)) {
		// Call the LOC_TIMER_ICU function for handling CH4 interrupt of TIM4
		LOC_TIMER_ICU(TIMER4 - 1, CH4 - 1);

		// Clear the capture/compare interrupt flag for CH4 of TIM4
		CLR_BIT(TIM4->SR, CH4);
	}

	// Check if the update interrupt flag of TIM4 is set
	if (GET_BIT(TIM4->SR, 0)) {
		// Check if a callback function is registered for TIM4 (at index 4 in GLOBAL_Ptr array)
		if (GLOBAL_Ptr[3] != NULL) {

			// Call the callback function for TIM4
			GLOBAL_Ptr[3]();

			// Clear the update interrupt flag of TIM4
			CLR_BIT(TIM4->SR, 0);
		}
		else {
			// Clear the update interrupt flag of TIM4 without calling a callback function
			CLR_BIT(TIM4->SR, 0);
		}
	}
}
/*******************************************************************************************************/

/*******************************************************************************************************/
/*
 * @note    This function is called when any of the capture/compare channels (CH1-CH4) or
 *  			the update interrupt of TIM5 triggers an interrupt.
 */
void TIM5_IRQHandler(void) {
	// Check if the capture/compare interrupt flag for CH1 of TIM5 is set
	if (GET_BIT(TIM5->SR, 1)) {
		// Call the LOC_TIMER_ICU function for handling CH1 interrupt of TIM5
		LOC_TIMER_ICU(TIMER5 - 1, CH1 - 1);

		// Clear the capture/compare interrupt flag for CH1 of TIM5
		CLR_BIT(TIM5->SR, CH1);
	}
	else if (GET_BIT(TIM5->SR, 2)) {
		// Call the LOC_TIMER_ICU function for handling CH2 interrupt of TIM5
		LOC_TIMER_ICU(TIMER5 - 1, CH2 - 1);

		// Clear the capture/compare interrupt flag for CH2 of TIM5
		CLR_BIT(TIM5->SR, CH2);
	}
	else if (GET_BIT(TIM5->SR, 3)) {
		// Call the LOC_TIMER_ICU function for handling CH3 interrupt of TIM5
		LOC_TIMER_ICU(TIMER5 - 1, CH3 - 1);

		// Clear the capture/compare interrupt flag for CH3 of TIM5
		CLR_BIT(TIM5->SR, CH3);
	}
	else if (GET_BIT(TIM5->SR, 4)) {
		// Call the LOC_TIMER_ICU function for handling CH4 interrupt of TIM5
		LOC_TIMER_ICU(TIMER5 - 1, CH4 - 1);

		// Clear the capture/compare interrupt flag for CH4 of TIM5
		CLR_BIT(TIM5->SR, CH4);
	}

	// Check if the update interrupt flag of TIM5 is set
	if (GET_BIT(TIM5->SR, 0)) {
		// Check if a callback function is registered for TIM5 (at index 5 in GLOBAL_Ptr array)
		if (GLOBAL_Ptr[4] != NULL) {

			// Call the callback function for TIM5
			GLOBAL_Ptr[4]();

			// Clear the update interrupt flag of TIM5
			CLR_BIT(TIM5->SR, 0);
		}
		else {
			// Clear the update interrupt flag of TIM5 without calling a callback function
			CLR_BIT(TIM5->SR, 0);
		}
	}
}
/*******************************************************************************************************/

