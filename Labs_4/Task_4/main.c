/**
 * @author Krzysztof Stezala
 * @date 2018-12-03
 * @version 1.0
 * @brief UART Timer 3
 */
 
 #include "aduc831.h"
 #include "timers.h"
 #include "bitop.h"
 
 /*
	* Global variables
	*/
char my_buffer[3];
int counter = 0;
int led_number = 0;
 
/*
 * Example for 11.0592 MHz and 115200 bits/second
 */
 
void UART_function() interrupt 4
{
	char received = 0;
	if(RI == 1){
		// getting char from user
		received = (char)SBUF;
		// putting the char into array
		my_buffer[counter]=received;
		// incrementing the counter
		counter++;
		// if counter == 3 check contents
		if(counter==3)
		{
			if(my_buffer[0]=='L')
			{
				if(my_buffer[1]=='1' || my_buffer[1]=='2' || my_buffer[1]=='3')
				{
					led_number = my_buffer[1] - '0';
				}
				if(my_buffer[2]=='S')
				{
					DiodeON(P3, led_number);
					counter = 0;
				}
				else if(my_buffer[2]=='R')
				{
					DiodeOFF(P3, led_number);
					counter = 0;
				}
			}
		}
		// 			if contents are a command do them
		// 					clear the array, reset counter
		// else keep going
	  received = (char)SBUF;
		RI = 0;
		SBUF = received;
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