/*
 * BitMath.h
 *
 * Created: 7/8/2022 11:35:51 PM
 *  Author: mahdy
 */ 


#ifndef BITMATH_H_
#define BITMATH_H_


#define  SetBit(Reg, Bit)          (Reg |= (1 << Bit) )
#define  ClrBit(Reg, Bit)          (Reg &= ~(1 << Bit))
#define  TogBit(Reg, Bit)          (Reg ^= (1 << Bit) )
#define  GetBit(Reg, Bit)          (1 & (Reg >> Bit) )



#endif /* BITMATH_H_ */