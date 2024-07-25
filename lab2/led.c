//PART 1 Control the red, green, and blue LEDs of LED 0

#include <MKL46Z4.h>
#include "led.h"

const int RED_LED_PIN = 16; // PTE16 for Red LED
const int GREEN_LED_PIN = 6; // PTD6 for Green LED
const int BLUE_LED_PIN = 2; // PTE2 for Blue LED

const int LED_SERIES_PIN = 3; //  pin number for LED1

// Function prototypes for assembly functions
extern void set_led(grb32_t rgb_val);


void led_init(void) {
    // Enable the clock
    SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;

    // Initialize Red LED on PORTE
    PORTE->PCR[RED_LED_PIN] = PORT_PCR_MUX(0b001); // Set up as GPIO
    PTE->PDDR |= (1 << RED_LED_PIN); // Make it output
    PTE->PSOR |= (1 << RED_LED_PIN); // Turn off LED

    // Initialize Blue LED on PORTE
    PORTE->PCR[BLUE_LED_PIN] = PORT_PCR_MUX(0b001); // Set up as GPIO
    PTE->PDDR |= (1 << BLUE_LED_PIN); // Make it output
    PTE->PSOR |= (1 << BLUE_LED_PIN); // Turn off LED

    // Initialize Green LED on PORTE
    PORTE->PCR[GREEN_LED_PIN] = PORT_PCR_MUX(0b001); // Set up as GPIO
    PTE->PDDR |= (1 << GREEN_LED_PIN); // Make it output
    PTE->PSOR |= (1 << GREEN_LED_PIN); // Turn off LED

    // Initialize LED_SERIES on PORTE
    PORTE->PCR[LED_SERIES_PIN] = PORT_PCR_MUX(0b001); //Set up as GPIO
    PTE->PDDR |= (1 << LED_SERIES_PIN); // Make it output
    PTE->PSOR |= (1 << LED_SERIES_PIN); // Turn off LED

    //Turn off all LED's

    all_leds_off();

}
//PSOR Port Set Output Register
//PCOR Port Clear Output Register
//PTOR Port Toggle Output Register
void red_on(void) {
    PTE->PCOR = (1 << RED_LED_PIN); // Clear the pin (LED on is active low)
}

void red_off(void) {
    PTE->PSOR = (1 << RED_LED_PIN); // Set the pin
}

void red_toggle(void) {
    PTE->PTOR = (1 << RED_LED_PIN); // Toggle the pin
}


void green_on(void) {
    PTE->PCOR = (1 << GREEN_LED_PIN); // Clear the pin (LED on is active low)
}

void green_off(void) {
    PTE->PSOR = (1 << GREEN_LED_PIN); // Set the pin
}

void green_toggle(void) {
    PTE->PTOR = (1 << GREEN_LED_PIN); // Toggle the pin
}


void blue_on(void) {
    PTE->PCOR = (1 << BLUE_LED_PIN); // Clear the pin (LED on is active low)
}

void blue_off(void) {
    PTE->PSOR = (1 << BLUE_LED_PIN); // Set the pin
}

void blue_toggle(void) {
    PTE->PTOR = (1 << BLUE_LED_PIN); // Toggle the pin
}

void all_leds_off(void) {
    // Turn off the LED's
    PTE->PSOR = (1 << RED_LED_PIN) | (1 << GREEN_LED_PIN) | (1 << BLUE_LED_PIN);

}

//Part 2 functions for controlling serial LEDs


void led_off(void) {
    grb32_t off = {0, 0, 0, 0}; // All LEDs off
    set_led(off); // Turns a single LED off
}


void leds_off(uint32_t num_led) {
    grb32_t off = {0, 0, 0, 0};
    for (uint32_t i = 0; i < num_led; i++) {
        set_led(off); // Turns each LED off in the chain
    }
}

void set_leds(grb32_t *rgb_vals, uint32_t num_led) {
    for (uint32_t i = 0; i < num_led; i++) {
        set_led(rgb_vals[i]); // Sets each LED's color in the chain
    }

}


