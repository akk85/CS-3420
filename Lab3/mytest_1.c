#include "3140_concur.h"
#include "led.h"

void p1 (void)
{
	int i;
	for (i=0; i < 10; i++) {
		delay(500);
    	red_toggle_frdm();
	}
}

int main(void) {
    led_init();
    set15MHz();
    set15MHz();

    if (process_create(p1,32) < 0) { // only one call to process_create()
        return -1;
    }

    process_start();

    // Should observe the red LED toggling 10 times at a one-second interval


    return 0;
}
