/**
 * @author Krzysztof Stezala
 * @date 2018-12-09
 * @version 1.0
 * @brief DAC operation analysis
 */
 
 #include "aduc831.h"
 #include "timers.h"
 #include "bitop.h"
 #include "definitions.h"
  
 /*
	* Global variables
	*/
sample_t sample0={0};								//first sample voltage (assigned to DAC0)
sample_t sample1={0};								//second sample voltage (assigned to DAC1)
float sample_voltage=DA_Vref;

float given_scaler;

void main(void)
{
	// setting DACCON register for both DAC0 and DAC1
	DACCON = (DAC_MODE_12|DAC_RNG1_ON|DAC_RNG0_ON|DAC_CLR1_ON|DAC_CLR0_ON|DAC_SYNC_ON|DAC_POWER1_ON|DAC_POWER0_ON);
	//given_scaler sets the DAC0 to half of the reference voltage
	given_scaler = 0.5;
	sample0.value=(unsigned int)(sample_voltage/DA_Vref*given_scaler*(float)DA_MAX_VALUE);
	//given_scaler sets the DAC0 to 3/4 of the reference voltage
	given_scaler = 0.75;
	sample1.value=(unsigned int)(sample_voltage/DA_Vref*given_scaler*(float)DA_MAX_VALUE);
	
	DAC0H=sample0.word.high_byte;
	DAC0L=sample0.word.low_byte;
	
	DAC1H=sample1.word.high_byte;
	DAC1L=sample1.word.low_byte;
	
	while(1)
	{
	}
}