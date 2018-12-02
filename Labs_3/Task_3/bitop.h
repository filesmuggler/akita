#ifndef BITOP_H
#define BITOP_H

/* Bit operations on specific bytes */
#define BitSet(B, number) B|=0x01<<number
#define BitClear(B, number) B&=~(0x01<<number)
#define BitChange(B, number) B^=0x01<<number

/* Diode operations */
#define DiodeON(P, pin) P|=0x01<<pin
#define DiodeOFF(P, pin) P&=~(0x01<<pin)
#define DiodeTOGGLE(P, pin) P^=0x01<<pin


#endif