#include "led.h"
#include "3140_concur.h"
#include "realtime.h"

#define RT_STACK 20

/* Start times and deadlines for the real-time processes */
realtime_t start_pRT1 = {0, 1};
realtime_t start_pRT2 = {0, 0}; // Starts 1milli second later
realtime_t deadline_pRT1 = {0, 3}; // 3 milliseconds to complete
realtime_t deadline_pRT2 = {0, 2}; // 2 milliseconds to complete

/* Real-time processes */
void pRT1(void) {
	int i;
    for (i = 0; i < 5; i++) {
        green_on_frdm();
        delay(500);
        green_off_frdm();
        delay(500);
    }
}

void pRT2(void) {
	int i;
    for (i = 0; i < 5; i++) {
        red_on_frdm();
        delay(500);
        red_off_frdm();
        delay(500);
    }
}


int main(void) {
    led_init();

    // Create real-time processes
    if (process_rt_create(pRT1, RT_STACK, &start_pRT1, &deadline_pRT1) < 0) {  //later priority
    	return -1;
    }
    if (process_rt_create(pRT2, RT_STACK, &start_pRT2, &deadline_pRT2) < 0) { //earliest priority
    	return -1;
    }

    // Start concurrent execution
    process_start();

    // Ensure all LEDs are turned off after execution
    red_off_frdm();
    green_off_frdm();


    while (1); // Keep the main thread running
    return 0;
}

//test case of two realtime processes wuth different start times

//process prt2 has an earlier deadline therefore will be executed first before prt1. pRT2 (red LED) will blink its LED first for
//five cycles, each consisting of turning on for 500ms and then off for 500ms. Once pRT2 completes or reaches its deadline,
//pRT1 (green LED) will execute similarly.






