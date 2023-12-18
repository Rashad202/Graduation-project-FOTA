#ifndef STD_TYPES_H
#define STD_TYPES_H

//unsigned typedef
typedef unsigned char 				u8  ;           // 1 Byte
typedef unsigned short int  		u16 ;   	 	// 2 Byte 
typedef unsigned long int  			u32 ;     		// 4 Byte
typedef unsigned long long int		u64 ;			// 8 Byte

//signed typedef
typedef signed char 				s8  ;           // 1 Byte
typedef signed short int  			s16 ;      		// 2 Byte
typedef signed long int  			s32 ;       	// 4 Byte
typedef signed long long int		s64 ;			// 8 Byte

//float typedef
typedef float  						f32 ;           // 4 Byte
typedef double  					f64 ;           // 8 Byte

//Null pointer
#define NULL  		(void*)0

//Error status
#define OK         		1
#define NOT_OK     		0


#endif
