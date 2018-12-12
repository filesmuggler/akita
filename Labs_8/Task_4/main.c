/**
 * @author Krzysztof Stezala
 * @date 2018-12-11
 * @version 1.0
 * @brief Triangular wave
 */
 
 #include "aduc831.h"
 #include "timers.h"
 #include "bitop.h"
 #include "definitions.h"
 
  /*
	* Global variables
	*/
sig_params_t wave_params; 			// to store parameters of the signal
float32_t sample_voltage=0.0; 	// sample voltage to be put on DAC
sample_t sample = {0};					// final  value for DAC registers is stored here

/**
 * voltage_calc() calculates the current state of the voltage of the signal
 */
float32_t voltage_calc(float t, float period, float rise, float timeon, float wave_amplitude, float offset)
{
	float32_t voltage;
	
	if(t<rise)	//if we are in 'rise part' of a period
	{
		voltage = ((wave_amplitude/rise)*t)+offset;
	}
	else if(t>=(rise+timeon))	//if we are in 'fall part' of a period
	{
		voltage = wave_amplitude-(wave_amplitude/(period-(rise+timeon)))*(t-rise-timeon)+offset;
	}
	
	return voltage;
}	

void timer_1_interrupt() interrupt 3
{
	T1_set_time(GENERATOR_SAMPLING_TIME);
	// adding a frection to 
	wave_params.t+=wave_params.delta_t;
	if(wave_params.t>=wave_params.period)
	{
		wave_params.t=wave_params.delta_t;
	}
	//Determine sample
	sample_voltage=voltage_calc(wave_params.t,wave_params.period,wave_params.rise_edge,wave_params.time_on,wave_params.amplitude,wave_params.offset);
	
	//Signal restrictions//sample_voltage=(sample_voltage>DA_Vref)? DA_Vref: sample_voltage; //The expression a ? b : c returns b if a is true, otherwise it returns c.//sample_voltage=(sample_voltage<0)? 0 : sample_voltage;
	//Keep the signal in bounds
	if(sample_voltage>DA_Vref)
	{
		sample_voltage = DA_Vref;
	}
	else
	{
		sample_voltage = sample_voltage;
	}	
	if(sample_voltage<0)
	{
		sample_voltage = 0;
	}
	else
	{
		sample_voltage = sample_voltage;
	}
	// Register conversion
	// takes the relative value for integer in the union
	sample.value=(unsigned int)(sample_voltage/DA_Vref*(float)DA_MAX_VALUE); 
	// from the same union takes the respective bytes for DAC registers
	DAC0H = sample.word.high_byte;
	DAC0L = sample.word.low_byte;
}

void main(void)
{
	// setting DACCON register for both DAC0 and DAC1
	DACCON = (DAC_MODE_12|DAC_RNG1_ON|DAC_RNG0_ON|DAC_CLR1_ON|DAC_CLR0_ON|DAC_SYNC_ON|DAC_POWER1_ON|DAC_POWER0_ON);
	
	ET1=1;	//allow T1 interrupts
	EA=1;		//allow interrupts
	
	//timer config
	TMOD = (T1_MODE_GATE_ON|T1_MODE_OPERATIONAL_TIMER|T1_MODE_16B); //16b timer
	
	//saw-tooth parameters
	wave_params.period = 5.0;
	wave_params.amplitude = 5;					// wave_amplitude
	wave_params.rise_edge = 2.5;				// czas narastania
	wave_params.time_on = 0.0;					
	wave_params.offset = 0.0;
	wave_params.t = 0.0;
	wave_params.delta_t = (((float32_t)GENERATOR_SAMPLING_TIME)/1000.0); // getting the accuracy of sawtooh wave; how big is step in y axis
	
	//start timer 1 
	TR1 = 1;
	while(1)
	{
	}

}
