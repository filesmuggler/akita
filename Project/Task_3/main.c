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

char buffer[25];
char uart_buffer[25];
int local_index;

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
bool is_read = TRUE;

void receiveMessage() interrupt 4
{
	/**
	* Receiving transmission
	*/
	char received = 0;
	if(RI==1){
		received = (char)SBUF;
		RI = 0;
		//SBUF = received;
		buffer[message_index] = received;
		message_index = message_index + 1;
	}
	if(TI==1){
		TI = 0;
	}
	
	if(received == 'E')
	{
		is_read = FALSE;
		message_index = 0;
		return;
	}
	else
	{
		is_read = TRUE;
	}
	/*
	if(message_index > 25)
	{
		message_index = 0;
	}*/
	
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
	
	message_index = 0;
	local_index = 0;
	
	
	while(1)
	{
		
		while(buffer[local_index]!='E' && !is_read)
		{
			if(buffer[local_index]=='S')
			{
				new_data = TRUE;
		
				mode_data = TRUE;
				freq_data = FALSE;
				duty_cycle_data = FALSE;
		
				local_index = local_index + 1;
				continue;
			}
			else if(buffer[local_index] == 'D')
			{
				mode_data = FALSE;
				duty_cycle_data = TRUE;
				freq_data = FALSE;		
		
				local_index = local_index + 1;
				continue;
			}
			else if(buffer[local_index] == 'F')
			{
				mode_data = FALSE;
				duty_cycle_data = FALSE;
				freq_data = TRUE;
				
				local_index = local_index + 1;
				continue;
			}
	
			/**
			* Incoming data analysis
			*/
			if(new_data)
			{
				if(mode_data)
				{
					operation_mode = buffer[local_index];
					if(operation_mode == 49)
					{
						two_channel = FALSE;
					}
					else
					{
						two_channel = TRUE;
					}
				}
			}
		
			if(duty_cycle_data)
			{
				if(!two_channel)
				{
					// for single channel
					duty_cycle_1_t[local_index - 3] = buffer[local_index];
				}	
				else
				{
					// for double channel
					if(local_index < 5)
					{
						duty_cycle_1_t[local_index - 3] = buffer[local_index];
					}
					else
					{
						duty_cycle_2_t[local_index - 5] = buffer[local_index];
					}
				}
			}
		
			if(freq_data)
			{	
				if(!two_channel)
				{
					// for single channel
					frequency_1_t[local_index - 6] = buffer[local_index];
				}
				else
				{
					// for double channel
					if(local_index < 16)
					{
						frequency_1_t[local_index - 8] = buffer[local_index];
					}
					else
					{
						frequency_2_t[local_index - 16] = buffer[local_index];
					}
				}
			}
			local_index = local_index + 1;
		}
		if(buffer[local_index]=='E')
		{
			is_read = TRUE;
			local_index = 0;
		}
		
		
	}
}