/*******************************************************************************************************/
/* Author            : GP_FOTA_TEAM                                                                    */
/* Version           : V0.0.0                                                                          */
/* Data              : 3 Feb 2024                                                                      */
/* Description       : MFMI_interface.h --> implementations                                             */
/* Module  Features  :                                                                                 */
/*      01- FMI_voidEraseAppArea                                                                       */
/*      02- FMI_voidSectorErase                                                              		   */
/*      03- FMI_voidFlashWrite                                                                  	   */
/*******************************************************************************************************/

/*******************************************************************************************************/
/*                                   guard of file will call on time in .c                             */
#ifndef MFMI_interface_H_
#define MFMI_interface_H_

/*******************************************************************************************************/
/*                                      Macros Of Sectors                                              */

#define SECTOR_0	0
#define SECTOR_1	1
#define SECTOR_2	2
#define SECTOR_3	3
#define SECTOR_4	4
#define SECTOR_5	5

#define SECTOR_0_BASE_ADD 	0x08000000
#define SECTOR_1_BASE_ADD 	0x08004000
#define SECTOR_2_BASE_ADD 	0x08008000
#define SECTOR_3_BASE_ADD 	0x0800C000
#define SECTOR_4_BASE_ADD 	0x08010000
#define SECTOR_5_BASE_ADD 	0x08020000

/*******************************************************************************************************/
/*                                      Function Prototypes                                            */
/*******************************************************************************************************/
void MFMI_voidEraseAppArea(void);
void MFMI_voidSectorErase (u8 A_u8SectorNo);
void MFMI_voidFlashWrite  (u32 A_u32Address, u16* A_pu16Data, u16  A_u16Length);

/*******************************************************************************************************/
#endif /* MFMI_interface_H_ */
