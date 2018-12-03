/**
 * @author Krzysztof Stezala
 * @date 2018-12-03
 * @version 1.0
 * @brief UART Timer 3
 */
 
 #include "aduc831.h"
 #include "timers.h"
 
 
/*
 * Example for 11.0592 MHz and 115200 bits/second
 */
 
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
 
void main(void)
{
		EA = 1;
		ES = 1;
	
		//UART configuration
		SM0 = 1;
		SM1 = 1;
		SM2 = 0;
		REN = 1;
		
		//Timer 3 setup
		T3CON = T3CON_115200_11;
		T3FD = T3FD_115200_11;
	
		while(1)
		{
		}
}