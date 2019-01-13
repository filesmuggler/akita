#include "aduc831.h"
#include "pwm_macro.h"


float period;
int duty;

void main(void)
{
	CFG831 = 0x0000;
	//Mode 1
	PWMCON=PWM_MODE1;								//1 PWM with maximum period - maxPeriod16
	period=2.0;											//period of PWM (ms)
	duty=50;												//duty cycle of PWM (%)
	
	if(period>maxPeriod16)
		period=maxPeriod16;
	if(duty>maxDuty)
		duty=maxDuty;
	
	PWM_M1_PERIOD(period);
	PWM_M1_DUTY(per2time(duty));
	
	while(1){
	}
	
	
	
}