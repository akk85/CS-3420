/*************************************************************************
 * Lab 5 Test
 * 
 * pNRT: ^_______r r r r v
 * pRT1: ^g g g v
 *
 *   You should see the sequence of processes depicted above:
 *     - Non real-time process pNRT and real-time process pRT1 both start
 *       at time zero. pRT1 has priority, and blinks green 3 times (medium).
 *     - After pRT1 completes, pNRT begins and blinks red 4 times (fast).
 * 
 *   pRT1 should miss its deadline, check double blinks at end.
 *
 ************************************************************************/
 
#include "led.h"
#include "3140_concur.h"
#include "realtime.h"

/*--------------------------*/
/* Parameters for test case */
/*--------------------------*/


 
/* Stack space for processes */
#define NRT_STACK 20
#define RT_STACK  20
 


/*--------------------------------------*/
/* Time structs for real-time processes */
/*--------------------------------------*/

/* Constants used for 'work' and 'deadline's */
realtime_t t_1msec = {0, 1};


/* Process start time */
realtime_t t_pRT1 = {0, 0};


/*----------------------------------------------------
 *  Non real-time process
 *  Blinks red LED 4 times.
 *  Should be blocked by real-time process at first.
 *----------------------------------------------------*/
 
void pNRT(void) {
	int i;
	for (i=0; i<4;i++){
	red_on_frdm();
	delay(330);
	red_toggle_frdm();
	delay(330);
	}
}

/*-------------------
 * Real-time process
 *-------------------*/
void pRT1(void) {
	int i;
	for (i=0; i<3;i++){
	green_on_frdm();
	delay(660);
	green_toggle_frdm();
	delay(660);
	}
}


/*--------------------------------------------*/
/* Main function - start concurrent execution */
/*--------------------------------------------*/
int main(void) {	
	 
	led_init();

    /* Create processes */ 
    if (process_create(pNRT, NRT_STACK) < 0) {
    	return -1;
    }
    if (process_rt_create(pRT1, RT_STACK, &t_pRT1, &t_1msec) < 0) {
    	return -1;
    }
   
    /* Launch concurrent execution */
	process_start();

	green_off_frdm();
	red_off_frdm();

	while(process_deadline_miss>0) {
			red_on_frdm();
			green_on_frdm();
			delay(330);
			green_off_frdm();
			red_off_frdm();
			delay(330);
			process_deadline_miss--;
	}
	
	/* Hang out in infinite loop (so we can inspect variables if we want) */ 
	while (1);
	return 0;
}
