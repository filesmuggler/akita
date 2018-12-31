/**
 * @author Krzysztof Stezala
 * @date 2018-12-11
 * @version 2.0
 * @brief Interface 
 */
 
 #include "aduc831.h"
 #include "timers.h"
 #include "bitop.h"
 #include "definitions.h"
 
  /*
	* Global variables
	*/
sig_params_t wave_params; //to store parameters
float32_t sample_voltage=0.0;
sample_t sample = {0};

float32_t voltage_calc(float t, float period, float rise, float timeon, float ampli, float offset, bool rectangle)
{
	
	float32_t voltage;
	
	if(t<rise)	//if we are in 'rise part' of a period
	{
		voltage = ((ampli/rise)*t)+offset;
	}
	else if((t>=rise) && (t < (rise+timeon)))	//if we are in 'on part' of a period
	{
		voltage = ampli + offset;
	}
	
	else if(t>=(rise+timeon))	//if we are in 'fall part' of a period
	{
		if(rectangle==1) voltage = 0+offset;
		else 	voltage = ampli-(ampli/(period-(rise+timeon)))*(t-rise-timeon)+offset;
	}
	
	return voltage;
}	

void timer1_handler() interrupt 3
{
	//set T1
	T1_set_time(GENERATOR_SAMPLING_TIME);
	//Change time of signal
	wave_params.t+=wave_params.delta_t;
	if(wave_params.t>=wave_params.period)wave_params.t=wave_params.delta_t;
	//Determine sample
	sample_voltage=voltage_calc(wave_params.t,wave_params.period,wave_params.rise_edge,wave_params.time_on,wave_params.amplitude,wave_params.offset,wave_params.rectangle);
	//Signal restrictions
	sample_voltage=(sample_voltage>DA_Vref)? DA_Vref: sample_voltage;
	sample_voltage=(sample_voltage<0)? 0 : sample_voltage;
	//Register conversion
	sample.value=(unsigned int)(sample_voltage/DA_Vref*(float)DA_MAX_VALUE);
	//Set converter
	DAC0H = sample.word.high_byte;
	DAC0L = sample.word.low_byte;
}
void main(){

	//DAC config
	DACCON=(DAC_MODE_12|DAC_RNG1_ON|DAC_RNG0_ON|DAC_CLR1_ON|DAC_CLR0_ON|DAC_SYNC_ON|DAC_POWER1_ON|DAC_POWER0_ON);
	
	ET1=1;	//allow T1 interrupts
	EA=1;		//allow interrupts
	
	//timer config
	TMOD = (T1_MODE_GATE_ON|T1_MODE_OPERATIONAL_TIMER|T1_MODE_16B); //16b timer //16b timer
	
	//saw-tooth params
	wave_params.period = 6.0;
	wave_params.amplitude = 3.5;
	wave_params.rise_edge = 2.0;
	wave_params.time_on = 4.0;
	wave_params.offset = 2.0;
	wave_params.rectangle = 0;
	wave_params.t = 0.0;
	wave_params.delta_t = (((float32_t)GENERATOR_SAMPLING_TIME)/1000.0);

	TR1 = 1;
	while(1)
	{
	}
}
