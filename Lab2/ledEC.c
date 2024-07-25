#include <MKL46Z4.h>
#include "led.h"

volatile uint8_t redIntensity = 0;
volatile uint8_t greenIntensity = 0;
volatile uint8_t blueIntensity = 0;


void PIT_init(void);
void set_led0(grb32_t rgb_val);

void PIT_IRQHandler(void) {
    static uint8_t counter = 0;

    // Clear the PIT interrupt flag
    PIT->CHANNEL[0].TFLG = PIT_TFLG_TIF_MASK;

    if(counter < redIntensity) {
        red_on();
    } else {
        red_off();
    }

    if(counter < greenIntensity) {
        green_on();
    } else {
        green_off();
    }

    if(counter < blueIntensity) {
        blue_on();
    } else {
        blue_off();
    }

    counter = (counter + 1) % 256; // Increment and wrap the counter
}

void PIT_init(void) {
    SIM->SCGC6 |= SIM_SCGC6_PIT_MASK;
    PIT->MCR = 0x00;
    PIT->CHANNEL[0].LDVAL = SystemCoreClock / 10000 - 1;
    PIT->CHANNEL[0].TCTRL = PIT_TCTRL_TEN_MASK | PIT_TCTRL_TIE_MASK;
    NVIC_EnableIRQ(PIT_IRQn);
}

void set_led0(grb32_t rgb_val) {
    redIntensity = rgb_val.red;
    greenIntensity = rgb_val.green;
    blueIntensity = rgb_val.blue;
}

int main(void) {
    led_init();
    PIT_init();

    grb32_t color;

    while(1) {
        // Cycle through colors
        for(uint8_t i = 0; i < 255; i++) {
            color.red = i;
            color.green = 255 - i;
            color.blue = i / 2;
            set_led0(color);
            for (volatile int j = 0; j < 10000; j++); // Delay
        }
    }
}
