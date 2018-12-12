/**
 * @author Krzysztof Stezala
 * @date 2018-12-03
 * @version 5.0
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
	
#define T_divider 												12
#define T_resolution 										  16
#define T_register_initial_value(time_ms)\
((0x000001ul<<T_resolution)-Tx_N(time_ms,T_divider))

/**
 * Timer 1 settings for uart
 */
#define T1_9600_12 0xF9
#define T1_19200_11 0xFD 
#define T1_9600_11 0xFD
#define T1_2400_11 0xF4

/**
 * Timer 2 settings for uart
 */
#define T2_19200_12_H 0xFF
#define T2_19200_12_L 0xEC
#define T2_9600_12_H 0xFF
#define T2_9600_12_L 0xD7
#define T2_2400_12_H 0xFF
#define T2_2400_12_L 0x5C
#define T2_1200_12_H 0xFE
#define T2_1200_12_L 0xB8
#define T2_19200_11_H 0xEE
#define T2_19200_11_L 0xEH
#define T2_9600_11_H 0xFF
#define T2_9600_11_L 0xDC
#define T2_2400_11_H 0xFF
#define T2_2400_11_L 0x70
#define T2_1200_11_H 0xFF
#define T2_1200_11_L 0xE0

/**
 * Timer 3 settings for uart
 */
#define T3CON_230400_11 0x80
#define T3FD_230400_11 0x20
#define T3CON_115200_11 0x81
#define T3FD_115200_11 0x20
#define T3CON_57600_11 0x82
#define T3FD_57600_11 0x20
#define T3CON_38400_11 0x83
#define T3FD_38400_11 0x08
#define T3CON_19200_11 0x84
#define T3FD_19200_11 0x08
#define T3CON_9600_11 0x85
#define T3FD_9600_11 0x08


#endif