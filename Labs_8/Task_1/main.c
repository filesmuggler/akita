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
sample_t sample0={0};
sample_t sample1={0};
float sample_voltage=DA_Vref;

void main(void)
{
	DACCON = (DAC_MODE_12|DAC_RNG1_ON|DAC_RNG0_ON|DAC_CLR1_ON|DAC_CLR0_ON|DAC_SYNC_ON|DAC_POWER1_ON|DAC_POWER0_ON);
	sample0.value=(unsigned int)(sample_voltage/DA_Vref*(float)DA_MAX_VALUE);
	sample1.value=(unsigned int)(sample_voltage/DA_Vref/2.0*(float)DA_MAX_VALUE);
	
	DAC0H=sample0.word.high_byte;
	DAC0L=sample0.word.low_byte;
	
	DAC1H=sample1.word.high_byte;
	DAC1L=sample1.word.low_byte;
	
	while(1)
	{
	}
}
	