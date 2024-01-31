/*******************************************************************************************************/
/* Author            : GP_FOTA_TEAM                                                                    */
/* Version           : V0.0.0                                                                          */
/* Data              : 15 Dec 2023                                                                     */
/* Description       : MGPIO_Interface.h --> implementations                                           */
/* Module  Features  :                                                                                 */
/*      01- MGPIO_voidSetPinMode                                                                       */
/*      02- MGPIO_voidSetPinOutPutType                                                                 */
/*      03- MGPIO_voidSetPinOutSpeed                                                                   */
/*      04- MGPIO_voidSetPullType                                                                      */
/*      05- MGPIO_u8ReadData                                                                           */
/*      06- MGPIO_voidWriteData                                                                        */
/*      07- MGPIO_voidToggleData                                                                        */
/*      08- MGPIO_voidPinLock                                                                          */
/*      09- MGPIO_voidDirectSetReset                                                                   */
/*      10- MGPIO_voidSetPinAltFn                                                                      */
/*******************************************************************************************************/

/*******************************************************************************************************/	
/*	* What i sell To Customer                                                                          */
/*		*  The Archictect Give The API	                                                               */
/*						- The Name Of Function                                                         */
/*						- What is The Input                                                            */
/*						- What Is The Output                                                           */
/*						- Macro                                                                        */
/*******************************************************************************************************/


/*                                   guard of file will call on time in .c                             */

#ifndef GPIO_INTERFACE_H
#define GPIO_INTERFACE_H


/*                                      Standard Types LIB                                             */

#include "../../Libraries/STD_TYPES.h"
#include "../../Libraries/BIT_MATH.h"



/*                                      MCAL Components                                                */

#include "MGPIO_private.h"
#include "MGPIO_config.h"

/*                                      Macros Of Port                                                 */

#define GPIOA_PORT   		   0U
#define GPIOB_PORT   		   1U
#define GPIOC_PORT   		   2U
#define GPIOD_PORT   		   3U
#define GPIOE_PORT   		   4U
#define GPIOH_PORT   		   5U

/*                                      Macros Of Pins                                                 */
#define PIN_0        		   0U
#define PIN_1        		   1U
#define PIN_2        		   2U
#define PIN_3        		   3U
#define PIN_4        		   4U
#define PIN_5        		   5U
#define PIN_6        		   6U
#define PIN_7        		   7U
#define PIN_8        		   8U
#define PIN_9        		   9U
#define PIN_10       		   10U
#define PIN_11       		   11U
#define PIN_12       		   12U
#define PIN_13       		   13U
#define PIN_14       		   14U
#define PIN_15       		   15U

/*                                      Macros Of Mode                                                 */
#define MODE_INPUT      	 (0b00)
#define MODE_OUTPUT     	 (0b01)
#define MODE_ALTF       	 (0b10)
#define MODE_ANALOG     	 (0b11)

/*                                      Macros Of Type                                                 */
#define OUTPUT_TYPE_PUSH_PULL    0U
#define OUTPUT_TYPE_OPEN_DRAIN   1U

/*                                      Macros Of Speed                                                 */
#define OUTPUT_SPEED_LOW       (0b00)
#define OUTPUT_SPEED_MEDUIM    (0b01)
#define OUTPUT_SPEED_HIGH      (0b10)
#define OUTPUT_SPEED_VERY_HIGH (0b11)

/*                                      Macros Of PULL                                                 */
#define PULL_OFF              (0b00)
#define PULL_UP               (0b01)
#define PULL_DOWN             (0b10)
/*                                      Macros Write Data                                              */


#define HIGH                     	1U
#define LOW	                 	0U

/*                                      Macros ALTF                                                    */
#define ALTFN_0           0b0000
#define ALTFN_1           0b0001
#define ALTFN_2           0b0010
#define ALTFN_3           0b0011
#define ALTFN_4           0b0100
#define ALTFN_5           0b0101
#define ALTFN_6           0b0110
#define ALTFN_7           0b0111
#define ALTFN_8           0b1000
#define ALTFN_9           0b1001
#define ALTFN_10          0b1010
#define ALTFN_11          0b1011
#define ALTFN_12          0b1100
#define ALTFN_13          0b1101
#define ALTFN_14          0b1110
#define ALTFN_15          0b1111


/*                                      Function Prototypes                                            */
/*******************************************************************************************************/
/*                                      01- MGPIO_voidSetPinMode                                       */
/*-----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Function Set The Mode Of Pin Mode Take 2Bits                             */
/*                                                                                                     */
/*      1- MODE_INPUT                                                                                  */
/*      2- MODE_OUTPUT                                                                                 */
/*      3- MODE_ALTF                                                                                   */
/*      4- MODE_ANALOG                                                                                 */
/* 2- Function Input       -> Copy_u8PortName ,   Copy_u8PinNum ,   Copy_u8Mod                         */                   
/* 3- Function Return      -> No Thing                                                                 */
/*******************************************************************************************************/

void MGPIO_voidSetPinMode(u8 Copy_u8PortName ,u8 Copy_u8PinNum ,u8 Copy_u8Mode  );

/*******************************************************************************************************/
/*                                      02- MGPIO_voidSetPinOutPutType                                 */
/*-----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Set The Type Of OutPut (OpenDrain = 0 , PushPull = 1)                    */
/*                                                                                                     */
/*       - OUTPUT_TYPE_PUSH_PULL                                                                       */
/*       - OUTPUT_TYPE_OPEN_DRAIN	                                                                   */
/* 2- Function Input       -> Copy_u8PortName ,   Copy_u8PinNum ,   Copy_u8OutPutType                  */                   
/* 3- Function Return      -> No Thing                                                                 */
/*******************************************************************************************************/

void MGPIO_voidSetPinOutPutType(u8 Copy_u8PortName ,u8 Copy_u8PinNum ,u8 Copy_u8OutPutType  );

/*******************************************************************************************************/
/*                                      03- MGPIO_voidSetPinOutSpeed                                   */
/*-----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Set The Speed (LOW , Meduim , High ,VeryHaigh):                          */
/*                             - OUTPUT_SPEED_LOW                                                      */
/*                             - OUTPUT_SPEED_MEDUIM                                                   */
/*                             - OUTPUT_SPEED_HIGH                                                     */    
/*                             - OUTPUT_SPEED_VERY_HIGH	                                               */
/* 2- Function Input       -> Copy_u8PortName ,   Copy_u8PinNum ,   Copy_u8OutSpeed                    */                   
/* 3- Function Return      -> No Thing                                                                 */
/*******************************************************************************************************/

void MGPIO_voidSetPinOutSpeed(u8 Copy_u8PortName ,u32 Copy_u8PinNum ,u32 Copy_u8OutSpeed );

/*******************************************************************************************************/
/*                                      04- MGPIO_voidSetPullType                                      */
/*-----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Set The PULL Resistor Connection State                                   */
/*                              - PULL_OFF                                                             */
/*                              - PULL_UP                                                              */
/*                              - PULL_DOWN                                                            */    
/* 2- Function Input       -> Copy_u8PortName ,   Copy_u8PinNum ,   Copy_u8PullType                    */                   
/* 3- Function Return      -> No Thing                                                                 */
/*******************************************************************************************************/

void MGPIO_voidSetPullType(u8 Copy_u8PortName ,u32 Copy_u8PinNum ,u32 Copy_u8PullType );

/*******************************************************************************************************/
/*                                      05- MGPIO_u8ReadData                                           */
/*-----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Read Data From IDR                                                       */  
/* 2- Function Input       -> Copy_u8PortName ,   Copy_u8PinNum                                        */                   
/* 3- Function Return      -> LOC_u8ReturnValue                                                        */
/*******************************************************************************************************/

u8 MGPIO_u8ReadData(u8 Copy_u8PORT ,u8 Copy_u8PIN);


/*******************************************************************************************************/
/*                                      06- MGPIO_voidWriteData                                        */
/*-----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Write Data At ODR	Value :                                                */
/*                               - HIGH                                                                */
/*                               - LOW	                                                               */
/* 2- Function Input       -> Copy_u8PortName ,   Copy_u8PinNum ,   Copy_u8State                       */                   
/* 3- Function Return      -> No Thing                                                                 */
/*******************************************************************************************************/

void MGPIO_voidWriteData(u8 Copy_u8PortName ,u8 Copy_u8PinNum ,u8 Copy_u8State);


void MGPIO_voidToggleData(u8 Copy_u8PortName ,u8 Copy_u8PinNum);

/*******************************************************************************************************/
/*                                      07- MGPIO_voidPinLock                                          */
/*-----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> to Lock pin :                                                            */
/*                               1)Set Pin                                                             */
/*                               2)Set Pin 16                                                          */
/*                               3)Wait bit 16 =high                                                   */
/* 2- Function Input       -> Copy_u8PortName ,   Copy_u8PinNum                                        */                   
/* 3- Function Return      -> No Thing                                                                 */
/*******************************************************************************************************/

void MGPIO_voidPinLock(u8 Copy_u8PortNum ,u8 Copy_u8PinNum );

/*******************************************************************************************************/
/*                                      08- MGPIO_voidDirectSetReset                                   */
/*-----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> to Set pin Direction :                                                   */
/*                               1)Set Pin                                                             */
/*                               2)ReSet Pin                                                           */
/* 2- Function Input       -> Copy_u8PortName ,   Copy_u8PinNum  ,Copy_u8State                         */                   
/* 3- Function Return      -> No Thing                                                                 */
/*******************************************************************************************************/
void MGPIO_vDirectSetReset(u8 Copy_u8PortName , u8 Copy_u8PinNum, u8 Copy_u8State);

/*******************************************************************************************************/
/*                                      09- MGPIO_voidSetPinAltFn                                      */
/*-----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> to Set pin Altarnate :                                                   */
/* 2- Function Input       -> Copy_u8PortName ,   Copy_u8PinNum  ,Copy_u8ALF                           */                   
/* 3- Function Return      -> No Thing                                                                 */
/*******************************************************************************************************/

void MGPIO_voidSetPinAltFn( u8 Copy_u8PortNum ,u8 Copy_u8PinNum, u8 Copy_u8ALF );




#endif //GPIO_INTERFACE_H

