#ifndef BIT_MATH_H
#define BIT_MATH_H

//one Bit operation
#define SET_BIT(REG,BIT_POSITION)     	REG |= (1<<BIT_POSITION)
#define CLR_BIT(REG,BIT_POSITION)   	REG &=~(1<<BIT_POSITION)
#define TOG_BIT(REG,BIT_POSITION)  		REG ^= (1<<BIT_POSITION)
#define GET_BIT(REG,BIT_POSITION)     	(REG & (1<<BIT_POSITION))>>BIT_POSITION
#define SET_VAL(Var,Bit_No,Val)		    (Var |= (Val<<Bit_No))
//Register operation (with mask)
#define MSK_BITS(REG,MSK)				(REG) |=  (MSK)
#define Clr_BITS(REG,MSK)				(REG) &= ~(MSK)
#define Toggle_BITS(REG,MSK)			(REG) ^=  (MSK)
//full Register operation (0s|1s)
#define Set_REG(REG)					(REG) =  (0xFFFFFFFF)
#define Clr_REG(REG)					(REG) =  (0x00000000)
#define Toggle_REG(REG)					(REG) ^= (0xFFFFFFFF)


#endif
