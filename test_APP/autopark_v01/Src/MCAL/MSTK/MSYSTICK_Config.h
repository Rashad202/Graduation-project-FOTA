/*******************************************************************************************************/
/* Author            : GP_FOTA_TEAM                                                                    */
/* Version           : V0.0.0                                                                          */
/* Data              : 15 Dec 2023                                                                     */
/* Description       : MSTK_Config.c --> Configuration                                                */
/*******************************************************************************************************/



/*******************************************************************************************************/
/*                                   guard of file will call on time in .c                             */
/*******************************************************************************************************/

#ifndef MSTK_CONFIG_H_
#define MSTK_CONFIG_H_

#define PROCCESOR_CLK_AHB          1
#define PROCCESOR_CLK_AHB_DIV8     2

#define CLK_SOURCE_CONFIG          PROCCESOR_CLK_AHB_DIV8

#define CLKSOURCE                  2
#define COUNTFLAG                  16

#define MSTK_SINGLE_INTERVAL		1
#define	MSTK_PERIOD_INTERVAL		0

#endif /* MSTK_CONFIG_H_ */
