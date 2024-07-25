#include <MKL46Z4.h>
#include "led.h"

/* ----------------------------------------------------------------------
 Note the different characters around the library names.
 Use <> characters to include system libraries
 Use "" characters to include your own libraries from the sources folder 
 ------------------------------------------------------------------------*/

// Function to initialize the PIT
void PIT_init(void) {
    // Enable clock to PIT module
    SIM->SCGC6 |= SIM_SCGC6_PIT_MASK;

    // Enable PIT module and allow it to run in debug mode
    PIT->MCR = 0x00;

    // Set load value for PIT[0] to achieve 1-second interval
    PIT->CHANNEL[0].LDVAL = 15000000 - 1; // 15MHz clock for 1 second

    // Enable timer and interrupt
    PIT->CHANNEL[0].TCTRL |= PIT_TCTRL_TEN_MASK;
}

// Function to check if the PIT timer has expired and if so, clears the flag
int PIT_has_expired(void) {
    if (PIT->CHANNEL[0].TFLG & PIT_TFLG_TIF_MASK) {
        // Clear the timer interrupt flag
        PIT->CHANNEL[0].TFLG = PIT_TFLG_TIF_MASK;
        return 1;
    }
    return 0;
}
/*
     Main program: entry point
*/
int main (void)
{
    // Initialize the red LED
    led_init();

    // Initialize the PIT
    PIT_init();

    while(1) {
        // Poll the PIT to see if it has expired
        if (PIT_has_expired()) {
            // Toggle the red LED when the timer expires
            red_toggle();
        }
    }
}
