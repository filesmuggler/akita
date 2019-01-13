/**
 * @author Krzysztof Stezala
 * @date 2019-01-12
 * @version 1.0
 * @brief UART communication with third-party app
 */
 
 
 /**
  * UART set into Mode 1 (8-bit, Variable Baud Rate)
	*
	*
	*/
#include "aduc831.h"
#include "timers.h"
#include "definitions.h"

char message_index;

int frequency_1;
char frequency_1_t[8];
int duty_cycle_1;																				// after processing
char duty_cycle_1_t[2];																	// before processing


int frequency_2;
char frequency_2_t[8];
int duty_cycle_2;
char duty_cycle_2_t[2];

int operation_mode;

bool new_data = FALSE;
bool mode_data = FALSE;
bool duty_cycle_data = FALSE;
bool freq_data = FALSE;
bool two_channel = FALSE;

void receiveMessage() interrupt 4
{
	/**
	* Receiving transmission
	*/
	char received = 0;
	if(RI==1){
		received = (char)SBUF;
		RI = 0;
		SBUF = received;
	}
	if(TI==1){
		TI = 0;
	}
	
	/**
	* Checking for flags from incoming transmission
	*/
	if(received=='S')
	{
		new_data = TRUE;
		
		mode_data = TRUE;
		freq_data = FALSE;
		duty_cycle_data = FALSE;
		
		message_index = message_index + 1;
		return;
	}
	else if(received == 'D')
	{
		mode_data = FALSE;
		duty_cycle_data = TRUE;
		freq_data = FALSE;		
		
		message_index = message_index + 1;
		return;
	}
	else if(received == 'F')
	{
		mode_data = FALSE;
		duty_cycle_data = FALSE;
		freq_data = TRUE;
		
		message_index = message_index + 1;
		return;
	}
	else if(received == 'E')
	{
		new_data = FALSE;
		
		mode_data = FALSE;
		freq_data = FALSE;
		duty_cycle_data = FALSE;
		two_channel = FALSE;
		
		message_index = 0;
		return;
	}
	
	/**
	* Incoming data analysis
	*/
	if(new_data)
	{
		if(mode_data)
		{
			operation_mode = received;
			if(operation_mode!=49){
				two_channel = TRUE;
			}
		}
		
		if(duty_cycle_data)
		{
			if(!two_channel)
			{
				// for single channel
				duty_cycle_1_t[message_index - 3] = received;
			}
			else
			{
				// for double channel
				if(message_index < 5)
				{
					duty_cycle_1_t[message_index - 3] = received;
				}
				else
				{
					duty_cycle_2_t[message_index - 5] = received;
				}
			}
		}
		
		if(freq_data)
		{
			if(!two_channel)
			{
				// for single channel
				frequency_1_t[message_index - 6] = received;
			}
			else
			{
				// for double channel
				if(message_index < 16)
				{
					frequency_1_t[message_index - 8] = received;
				}
				else
				{
					frequency_2_t[message_index - 16] = received;
				}
			}
		}
		message_index = message_index + 1;
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
	
	TH1 = T1_9600_11;
	
	TR1 = 1;
	
	while(1)
	{
	}
}