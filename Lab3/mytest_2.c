#include "3140_concur.h"
#include <stdlib.h>
#include "led.h"

//TEST to demonstrate dynamic process creation and scheduling

void p1(void) {
	//Toggle the Green LED
    for (int i = 0; i < 10; i++) {
        delay(1000);  // 1-second delay
        green_toggle_frdm();
    }
}

void p2(void) {
    // toggle the red LED and create new processes
    for (int i = 0; i < 5; i++) {
        delay(700);  // Shorter delay
        red_toggle_frdm();

        // Dynamically create another process during execution
        if (i == 2) {  // Example condition to create new processes
            process_create(p1, 100);
        }
    }
}

int main(void) {
    led_init();
    set15MHz();

    // Create the initial process
    if (process_create(p2, 100) < 0) {
        return -1;  // Return -1 if process creation fails
    }

    process_start();  // Start the concurrent processes

    // The system should run `initial_process` which in turn creates `dynamic_process`.
    // Red LED should toggle faster initially, then both red and green should toggle,
    // demonstrating dynamic process creation and scheduling.

    return 0;
}
