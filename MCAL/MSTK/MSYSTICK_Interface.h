/*******************************************************************************************************/
/* Author            : GP_FOTA_TEAM                                                                    */
/* Version           : V0.0.0                                                                          */
/* Data              : 15 Dec 2023                                                                     */
/* Description       : MSTK_Interface.c --> implementations                                           */
/* Module  Features  :                                                                                 */
/*      01- MSTK_voidInit                                                                              */
/*      02- MSTK_voidStart                                                                             */
/*      03- MSTK_voidINTStatus                                                                         */
/*      04- MSTK_u8ReadFlag                                                                            */
/*      05- MSTK_VidSetCallBack                                                                        */
/*******************************************************************************************************/
#ifndef SYSTICK_INTERFACE_H_
#define SYSTICK_INTERFACE_H_


/*                                      Function Prototypes                                            */


void MSTK_voidInit( void );

void MSTK_voidStart( u32 Copy_PreloadValue );

void MSTK_voidStopInterval(void) ;

u8 MSTK_u8ReadFlag( void );

void MSTK_voidSetIntervalSingle(u32 Ticks,void (*Copy_ptr)(void));

void	MSTK_voidSetIntervalPeriodic(u32 Ticks,void (*Copy_ptr)(void));

u32 MSTK_u32GetCurrentValue(void);

u32 MSTK_u32GetElapsedTime(void);

void _delay_us( u32 Copy_u32Time ) ;

void _delay_ms( u32 Copy_u32Time ) ;


#endif /* SYSTICK_INTERFACE_H_ */
