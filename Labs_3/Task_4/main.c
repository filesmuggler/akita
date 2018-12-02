/**
 * @author Krzysztof Stezala
 * @date 2018-12-02
 * @version 1.0
 * @brief Set diode with proper period task
 */
#include "aduc831.h"
#include "timers.h"
#include "bitop.h"

#include <stdio.h>
#include <math.h>


/**
 * Global variables
 */
int time_ms = 20;
int test_g_1 = 20;
int test_g_2 = 30;
float k = 1;
float result = 0;
 
/**
 * Timer 1 interrupt function
 */
void timer_1_function(void) interrupt 3
{
	/**
	 * Light up the diode at port P3, pin 6.
   */
	DiodeTOGGLE(P3,6);	
	test_g_1 = test_g_1 * (-1);	
	T1_set_time_ms(time_ms);
	
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
		PT1 = 1;
	
		/**
		 * Setting the proper mode for TMOD register 
		 */
		TMOD = T1_MODE_16B | T1_MODE_OPERATIONAL_TIMER;
		/**
		 * Setting the upper (TH1) and lower (TL1) register 
		 * values to make overflow after given number of impulses.
		 */
		T1_set_time_ms(time_ms);
	
		/**
		 * Setting the proper TCON register value.
		 */
		TR1 = 1;
		DiodeON(P3,6);
		DiodeON(P3,7);
		
		 
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
			if(TF1){	
				test_g_2 = test_g_2 * (-1);	
				TF1 = 0;
				T1_set_time_ms(time_ms);
			}
			DiodeTOGGLE(P3,7);
			if(k>=10)
			{
				k=1;
			}
			else
			{
				k = k + 0.1;
				result = k*(sqrt(k));
			}
		}
}
 