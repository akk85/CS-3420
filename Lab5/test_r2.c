#include "led.h"
#include "3140_concur.h"
#include "realtime.h"

#define NRT_STACK 20

void pNRT1(void) {
    for (int i = 0; i < 5; i++) {
        green_on_frdm();
        delay(300);
        green_off_frdm();
        delay(300);
    }
}

void pNRT2(void) {
    for (int i = 0; i < 10; i++) {
        red_on_frdm();
        delay(300);
        red_off_frdm();
        delay(300);
    }
}

int main(void) {
    led_init();

    if (process_create(pNRT1, NRT_STACK) < 0) {
    	return -1;
    }
    if (process_create(pNRT2, NRT_STACK) < 0) {
    	return -1;
    }

    process_start();

    // Turn off all LEDs after process execution
    green_off_frdm();
    red_off_frdm();

    //infinite loop with red and green turning on simultaneosly after processes terminate.
	while(1) {
			red_on_frdm();
			green_on_frdm();
			delay(330);
			green_off_frdm();
			red_off_frdm();
			delay(330);
			process_deadline_miss--;
	}

    while (1); // Keep the main thread running
    return 0;
}


// test case for all Non-real-time processes, green and red LED's turn on simultaneoslly for 5 blinks, then green stops and then
//red blinks for more 5 blinks alone after which red and green LED start to blink once again together infinitely.

