/**
 * @author Krzysztof Stezala
 * @date 2018-11-30
 * @version 1.0
 * @brief Timer 0 task
 */
 
#include "aduc831.h"
#include "timers.h"

/**
 * Global variables
 */
int g_1 = 15;
int g_2 = 20;
int num_impulses = 15;
char th0_initial_value;
char tl0_initial_value;

 
/**
 * Timer 0 interrupt function
 */
void timer_0_function(void) interrupt 1
{
	/**
	 * Change of global variable to opposite.
   */
	g_2 = g_2 * (-1);
}
 
/**
 * Main function
 */
void main(void)
{
		/**
		 * Setting the upper (TH0) and lower (TL0) register 
		 * values to make overflow after given number of impulses.
		 */
		th0_initial_value = 0xFF;
		tl0_initial_value = 0xFF - num_impulses;
	
		TH0 = th0_initial_value;
		TL0 = tl0_initial_value;
	
		/**
		 * Setting the proper mode for TMOD register 
		 */
		TMOD = T0_MODE_16B | T0_MODE_OPERATIONAL_COUNTER;
	
		/**
		 * Setting the proper TCON register value.
		 */
		TR0 = 1;
		
		/**
		 * Enabling all interrupts.
		 */
		EA = 1;
		
		/**
		 * Enabling interrupt at Timer 0.
		 */
		ET0 = 1;
		
		/**
		 * Setting interrupt's priority.
		 */
		 PT0 = 1;
		 
		/**
		 * Main loop
		 */
		while(1)
		{
			/**
			 * If Timer 0 overflow occurs
			 * the flag TF0 is changed to 1
			 * which has to be manually cleared
			 * by the user for making the recurrent
			 * overflow possible.
			 * TH0 and TL0 has to be reset to initial values.
		   */
			if(TF0)
			{
				g_1 = g_1 * (-1);
				TF0 = 0;
				TH0 = th0_initial_value;
				TL0 = tl0_initial_value;
			}
		}
}
 