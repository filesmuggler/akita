#include "aduc831.h"
#include "timers.h"

void UART_function() interrupt 4
{
	char received = 0;
	if(RI == 1){
	  received = (char)SBUF;
		RI = 0;
		SBUF = received + 1;
	}
	if(TI==1){
		TI = 0;
	}
	return;
}

void main()
{
	ES = 1; 
	EA = 1;
	
	//UART configuration
	SM0 = 1;
	SM1 = 1;
	SM2 = 0;
	REN = 1;
	
	//Timer1 setup
	TMOD = T1_MODE_8B_AUTORELOAD;

	//set to 9600 at 11.0592MHz
	TH1 = T1_9600_11;
	
	TR1 = 0x01;
	
	//Timer 2 setup
	RCLK = 1;
	TCLK = 0;
	
	//set to 2400 at 11.0592MHz
	RCAP2H = T2_2400_11_H;
	RCAP2L = T2_2400_11_L;
	
	TR2 = 1;
	
	while(1)
	{
	}
}