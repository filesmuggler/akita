/**
 * @author Krzysztof Stezala
 * @date 2018-12-09
 * @version 1.0
 * @brief Useful definitions
 */
 
#ifndef _DEFINITIONS_H_
#define _DEFINITIONS_H_

/**
 * DAC definitions
 */
#define DAC_MODE_8 (0x0001<<7)
#define DAC_MODE_12 0x0000
#define DAC_RNG1_ON (0x0001<<6)
#define DAC_RNG1_OFF 0x0000
#define DAC_RNG0_ON (0x0001<<5)
#define DAC_RNG0_OFF 0x0000
#define DAC_CLR1_ON (0x0001<<4)
#define DAC_CLR1_OFF 0x0000
#define DAC_CLR0_ON (0x0001<<3)
#define DAC_CLR0_OFF 0x0000
#define DAC_SYNC_ON (0x0001<<2)
#define DAC_SYNC_OFF 0x0000
#define DAC_POWER1_ON (0x0001<<1)
#define DAC_POWER1_OFF 0x0000
#define DAC_POWER0_ON (0x0001<<0)
#define DAC_POWER0_OFF 0x0000


//Generator definitions
#define GENERATOR_SAMPLING_TIME 100

//DAC definitions
#define DA_Vref 5.0
#define DA_RESOLUTION 12
#define DA_MAX_VALUE ((0x01ul<<DA_RESOLUTION)-1)

typedef union{
	unsigned int value;
	struct{
		unsigned char high_byte;
		unsigned char low_byte;
	}word;
}sample_t;

typedef struct{
	double period;
	double ampl;
	double rise_edge;
	double offset;
	double t;
	double delta_t;
}sig_params_t;




#endif