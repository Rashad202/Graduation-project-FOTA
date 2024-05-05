/*******************************************************************************************************/
/* Author            : GP_FOTA_TEAM                                                                    */
/* Version           : V0.0.0                                                                          */
/* Data              : 13 Apr 2024                                                                     */
/* Description       : HULTRA_SONIC_Prog.c --> implementations                                         */
/*******************************************************************************************************/

#include "../../MCAL/MRCC/MRCC_interface.h"   // MRCC: Reset and Clock Control driver
#include "../../MCAL/MGPIO/MGPIO_interface.h" // MGPIO: General Purpose Input/Output driver
#include "../../MCAL/MTIMER/MTIMER_interface.h" // MTIMER: Timer driver
#include "../../MCAL/MSTK/MSYSTICK_Interface.h" // MSTK: SysTick timer driver
#include "Ultrasonic_config.h" // Configuration header for the Ultrasonic Sensor
#include "Ultrasonic_interface.h"    // Interface header for the Ultrasonic Sensor


// Definition of a structure to hold Ultrasonic Sensor information
typedef struct {
	Enum_TIMER_NUM TIMER;
	Enum_TIMER_CHs CHANNELS;
} LOC_ULTRA_NUM;

// Array to store information for multiple Ultrasonic Sensors
LOC_ULTRA_NUM ULTRA_STRUCT[TOT_ULTRA_SONIC_NUM];


void HULTRA_vInitialize(Enum_ULTRA_SONIC_NUM Copy_u8Ultra_NUM, Enum_TIMER_NUM Copy_u8TimerNum, u8 Copy_u8ChannelNum)
{
    // Initialize the Input Capture Unit (ICU) of the specified timer and channel
    MTIMER_vICU(Copy_u8TimerNum, Copy_u8ChannelNum);

    // Store the timer number and channel number in the ultrasonic sensor structure
    ULTRA_STRUCT[Copy_u8Ultra_NUM].TIMER = Copy_u8TimerNum;
    ULTRA_STRUCT[Copy_u8Ultra_NUM].CHANNELS = Copy_u8ChannelNum;
}


void HULTRA_vSendTrigger(const UltraSX_t *UltraS_t) {
	// Set the ultrasonic sensor trigger pin as OUTPUT
	MGPIO_voidSetPinMode(UltraS_t->UltraS_Trigger_port, UltraS_t->UltraS_Trigger_Pin, MODE_OUTPUT);

	// Raise the ultrasonic sensor trigger pin to HIGH for a short duration
	MGPIO_vDirectSetReset(UltraS_t->UltraS_Trigger_port, UltraS_t->UltraS_Trigger_Pin, HIGH);
	_delay_us(10);  // Wait for "Trigger_Pulse_Width" milliseconds

	// Bring the ultrasonic sensor trigger pin back to LOW
	MGPIO_vDirectSetReset(UltraS_t->UltraS_Trigger_port, UltraS_t->UltraS_Trigger_Pin, LOW);
	//_delay_us(250);//
}


void HULTRA_vGetDistance(Enum_ULTRA_SONIC_NUM Copy_u8Ultra_NUM,f64* Copy_f64Distance) {
	// Calculate distance based on timer values and assume speed of sound is 343 meters per second
	*Copy_f64Distance = ((f64)MTIMER_GET_ICU(ULTRA_STRUCT[Copy_u8Ultra_NUM].TIMER, ULTRA_STRUCT[Copy_u8Ultra_NUM].CHANNELS) / 2) * 3.43;
	_delay_ms(50);
}

