/*******************************************************************************************************/
/* Author            : GP_FOTA_TEAM                                                                    */
/* Version           : V0.0.0                                                                          */
/* Data              : 21 Dec 2023                                                                     */
/* Description       : MEXTI_Interface.c --> implementations                                           */
/* Module  Features  :                                                                                 */
/*      01- MEXTI_voidEnableEXTI                                                                       */
/*      02- MEXTI_voidDisableEXTI                                                                      */
/*      03- MEXIT_voidSoftwareInterrput                                                                */
/*      04- MEXTI_voidSetSignalLatch                                                                   */
/*      05- EXTI_voidSetCallBack                                                                       */
/*******************************************************************************************************/
#ifndef EXTI_INTERFACE_H
#define EXTI_INTERFACE_H

#define EXTI0     0
#define EXTI1     1
/*******************************************************************************************************/
#define   RISING_EDGE     0
#define   FALLING_EDGE    1
#define   ON_CHANGE       2
/*******************************************************************************************************/
typedef enum{
	EXTI_PORTA = 0,
	EXTI_PORTB,
	EXTI_PORTC,
	EXTI_PORTD,
	EXTI_PORTE,
	RESERVED1,
	RESERVED2,
	EXTI_PORTH,
}EXTI_Ports_t;
/*******************************************************************************************************/
/*****  The Line ******/
#define LINE_0			0
#define LINE_1			1
#define LINE_2			2
#define LINE_3			3
#define LINE_4			4
#define LINE_5			5
#define LINE_6			6
#define LINE_7			7
#define LINE_8			8
#define LINE_9			9
#define LINE_10			10
#define LINE_11			11
#define LINE_12			12
#define LINE_13			13
#define LINE_14			14
#define LINE_15			15
/*******************************************************************************************************/
/***********	Function To Choice The Sense Mode At The Line	***********/

void MEXTI_voidSetSignalLatch(u8 Copy_Exti_Line ,u8 Copy_EXTI_Sense_Mode )  ;

/*******************************************************************************************************/
/***********		  Function To Enable The Line				***********/

void MEXTI_voidEnableEXTI(u8 Copy_u8Line) ;

/*******************************************************************************************************/
/***********	Function To Disable The Line					***********/

void MEXTI_voidDisableEXTI(u8 Copy_u8Line);

/*******************************************************************************************************/
/***********	Function Make SoftWare Interrput				***********/

void MEXTI_voidSoftwareInterrput(u8 Copy_u8Line);

/*******************************************************************************************************/
/***********	Function Take A Pointer To Function				***********/

void MEXTI0_voidSetCallBack( void (*ptr) (void));
void MEXTI1_voidSetCallBack( void (*ptr) (void));
void MEXTI2_voidSetCallBack( void (*ptr) (void));
void MEXTI3_voidSetCallBack( void (*ptr) (void));
void MEXTI4_voidSetCallBack( void (*ptr) (void));

/*******************************************************************************************************/
void MEXTI_voidSetEXTIConfiguration(u8 Copy_u8ExtiLine , EXTI_Ports_t Copy_enumGpioPortNum );
#endif  //EXTI_INTERFACE_H
