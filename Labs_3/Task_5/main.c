/**
 * @author Krzysztof Stezala
 * @date 2018-12-12
 * @version 1.0
 * @brief Counting pulses
 */
 
 #include "aduc831.h"
 #include "timers.h"
 #include "bitop.h"
 #include "definitions.h"
 
/*
* Global variables
*/
int z=0;
int number_of_pulses=0;
int obs_time=2;
int sampling_time = 75;
uint16_t result;

void timer1_interrupt() interrupt 3
{
	if(z<result)
	{
		z++;
	}
	else
	{
		TR0=0;
		TR1=0;
		number_of_pulses=(int)(TL0+TH0);
		TL0=0x00;
		TH0=0x00;
		z=0;
		T1_set_time(sampling_time);
		TR1=1;
		TR0=1;
	}
}

void main(void)
{ 
    ET1=1;
    ET0=1;
    EA=1;  
    result =(int)(obs_time*1000/sampling_time);
    T1_set_time(sampling_time);
		TMOD=T1_MODE_GATE_ON|T1_MODE_OPERATIONAL_TIMER|T1_MODE_16B|T0_MODE_GATE_OFF|T0_MODE_OPERATIONAL_COUNTER|T0_MODE_16B;
    TH1=0;
    TL1=0;
    TR1=1; //Start timer 1
    TR0=1;
	while(1)
	{

	}
}
