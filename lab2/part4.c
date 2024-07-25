#include <MKL46Z4.h>
#include "led.h"

volatile int greenLedState = 0;

void PIT_init(void) {
    // Enable clock to PIT module
    SIM->SCGC6 |= SIM_SCGC6_PIT_MASK;
    // Enable PIT and allow it to run in debug mode
    PIT->MCR = 0x00;
    // Configure PIT to generate an interrupt every 1 second
    PIT->CHANNEL[0].LDVAL = 15000000 - 1;
    // Enable timer and interrupt
    PIT->CHANNEL[0].TCTRL = PIT_TCTRL_TEN_MASK | PIT_TCTRL_TIE_MASK;

}

void PIT_IRQHandler(void) {
    // Clear the PIT interrupt flag
    PIT->CHANNEL[0].TFLG = PIT_TFLG_TIF_MASK;

    if (greenLedState == 0) {
        green_on();
        greenLedState = 1;
        // Reset LDVAL for a shorter period (~0.1 second)
        PIT->CHANNEL[0].LDVAL = 1500000 - 1;
    } else {
        green_off();
        greenLedState = 0;
        // Reset LDVAL back to 1 second for the next cycle
        PIT->CHANNEL[0].LDVAL = 15000000 - 1;
    }
}

int main(void) {
    led_init();
    PIT_init();
    // Enable PIT interrupt in the NVIC
    NVIC_EnableIRQ(PIT_IRQn);
    while (1) {
        red_toggle();
        // Delay for roughly 1 second
        for (volatile int i = 0; i < 1000000; i++);
    }
}

