/**
 * @author Krzysztof Stezala
 * @date 2018-12-02
 * @version 1.0
 * @brief Timer 1 task
 */
#include "aduc831.h"
#include "timers.h"

/**
 * Global variables
 */
int g_1 = 10;
int g_2 = 25;
char num_impulses = 20;
char th1_initial_value;
char tl1_initial_value;

 
/**
 * Timer 1 interrupt function
 */
void timer_1_function(void) interrupt 3
{
	/**
	 * Change of global variable to opposite.
   */
	g_2 = g_2 * (-1);	
	th1_initial_value = 0xFF;
	tl1_initial_value = 0xFF - num_impulses + 1;	
	TH1 = th1_initial_value;
	TL1 = tl1_initial_value;
	
	
	
}
 
/**
 * Main function
 */
void main(void)
{
		/**
		 * Enabling all interrupts.
		 */
		EA = 1;
		
		/**
		 * Enabling interrupt at Timer 1.
		 */
		ET1 = 1;
		
		/**
		 * Setting interrupt's priority.
		 */
		 //PT1 = 1;
	
		/**
		 * Setting the proper mode for TMOD register 
		 */
		TMOD = T1_MODE_16B | T1_MODE_OPERATIONAL_TIMER;
		/**
		 * Setting the upper (TH1) and lower (TL1) register 
		 * values to make overflow after given number of impulses.
		 */
		th1_initial_value = 0xFF;
		tl1_initial_value = 0xFF - num_impulses + 1;
		TH1 = th1_initial_value;
		TL1 = tl1_initial_value;
	
		
	
		/**
		 * Setting the proper TCON register value.
		 */
		TR1 = 1;
		
		
		 
		/**
		 * Main loop
		 */
		while(1)
		{
			/**
			 * If Timer 1 overflow occurs
			 * the flag TF1 is changed to 1
			 * which has to be manually cleared
			 * by the user for making the recurrent
			 * overflow possible.
			 * TH1 and TL1 has to be reset to initial values.
		   */
			if(TF1)
			{
				g_1 = g_1 * (-1);				
				TF1 = 0;
				
				th1_initial_value = 0xFF;
				tl1_initial_value = 0xFF - num_impulses + 1;
				TH1 = th1_initial_value;
				TL1 = tl1_initial_value;
				
			}
		}
}
 