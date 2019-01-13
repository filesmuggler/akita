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
		buffer[message_index] = received;
		message_index = message_index + 1;
	}
	if(TI==1){
		TI = 0;
	}
	if(received == 'E')
	{
		message_index = 0;
		return;
	}
	if(message_index > 25)
	{
		message_index = 0;
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
	
	message_index = 0;
	
	while(1)
	{
	}
}