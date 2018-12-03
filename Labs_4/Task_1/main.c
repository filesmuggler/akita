/**
 * @author Krzysztof Stezala
 * @date 2018-12-02
 * @version 1.0
 * @brief UART
 */
#include "aduc831.h"
#include "timers.h"

void UART_function() interrupt 4
{
	char received = 0;
	if(RI==1){
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
	
	
	SM0 = 0;
	SM1 = 1;
	SM2 = 0;
	REN = 1;
	
	TMOD = T1_MODE_8B_AUTORELOAD;
	
	TH1 = T1_19200_12;
	
	TR1 = 1;
	
	while(1)
	{
	}
}