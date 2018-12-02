/**
 * @author Krzysztof Stezala
 * @date 2018-12-02
 * @version 2.0
 * @brief Timers settings
 */
#ifndef _TIMERS_H_
#define _TIMERS_H_

/* Timer 0 mode sets */												 // T1:  T0:
#define T0_MODE_13B 											0x00 // 0000 0000b
#define T0_MODE_16B 											0x01 // 0000 0001b
#define T0_MODE_8B_AUTORELOAD 						0x02 // 0000 0010b
#define T0_MODE_16B_CONTROL_BITS 					0x03 // 0000 0011b
#define T0_MODE_OPERATIONAL_TIMER					0x00 // 0000 0000b
#define T0_MODE_OPERATIONAL_COUNTER				0x04 // 0000 0100b
#define T0_MODE_GATE_OFF									0x00 // 
#define T0_MODE_GATE_ON										0x08 // 0000 1000b

/* Timer 1 mode sets */												 // T1:  T0: 
#define T1_MODE_13B 											0x00 // 0000 0000b
#define T1_MODE_16B 											0x10 // 0001 0000b
#define T1_MODE_8B_AUTORELOAD							0x20 // 0010 0000b
#define T1_MODE_16B_CONTROL_BITS					0x30 // 0011 0000b
#define T1_MODE_OPERATIONAL_TIMER					0x00 // 0000 0000b
#define T1_MODE_OPERATIONAL_COUNTER				0x40 // 0100 0000b
#define T1_MODE_GATE_OFF									0x00 // 
#define T1_MODE_GATE_ON										0x80 // 1000 0000b

#define F_OSC 											12000000.0 // oscillator frequency
#define Tx_tau(divider)\
(float)((float)divider/F_OSC)								 // okres zliczanych impulsów czasomierza
	
#define Tx_N(time_ms, divider)\
(unsigned int)((float)time_ms/Tx_tau(divider)/1000.0)	// wart poczatkowa licznika dla podanego czasu
	
#define T0_divider 												12
#define T0_resolution 										16
#define T0_register_initial_value(time_ms)\
((0x000001ul<<T0_resolution)-Tx_N(time_ms,T0_divider))

#define T1_divider 												12
#define T1_resolution 										16
#define T1_register_initial_value(time_ms)\
((0x000001ul<<T1_resolution)-Tx_N(time_ms,T1_divider))

#define T0_set_time_ms(time_ms)\
TL0 = T0_register_initial_value(time_ms);\
TH0 = T0_register_initial_value(time_ms)>>8;

#define T1_set_time_ms(time_ms)\
TL1 = T1_register_initial_value(time_ms);\
TH1 = T1_register_initial_value(time_ms)>>8;


#endif