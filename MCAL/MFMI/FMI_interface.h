/*******************************************************************************************************/
/* Author            : GP_FOTA_TEAM                                                                    */
/* Version           : V0.0.0                                                                          */
/* Data              : 3 Feb 2024                                                                      */
/* Description       : FMI_interface.h --> implementations                                             */
/* Module  Features  :                                                                                 */
/*      01- FMI_voidEraseAppArea                                                                       */
/*      02- FMI_voidSectorErase                                                              		   */
/*      03- FMI_voidFlashWrite                                                                  	   */
/*******************************************************************************************************/

/*******************************************************************************************************/
/*                                   guard of file will call on time in .c                             */
#ifndef FMI_interface_H_
#define FMI_interface_H_

/*******************************************************************************************************/
/*                                      Macros Of Sectors                                              */
#define Flash_Sector_0	0b0000
#define Flash_Sector_1	0b0001
#define Flash_Sector_2	0b0010
#define Flash_Sector_3	0b0011
#define Flash_Sector_4	0b0100
#define Flash_Sector_5	0b0101

/*******************************************************************************************************/
/*                                      Function Prototypes                                            */
/*******************************************************************************************************/
void FMI_voidEraseAppArea(void);
void FMI_voidSectorErase(u8 A_u8SectorNo);
void FMI_voidFlashWrite(u32 A_u32Address, u16* A_pu16Data, u16  A_u16Length);

/*******************************************************************************************************/
#endif /* FMI_interface_H_ */
