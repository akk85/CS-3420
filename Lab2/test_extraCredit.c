#include "led.h"

void main(void) {
    int i; // Counter for loops

    grb32_t led_val; // Structure to hold RGB values
    int up_flag = 0; // Flag to implement pulsing behavior

    set15MHz(); // Set system clock to 15 MHz, assuming this function sets up the clock
    led_init(); // Initialize the LEDs
    delay(1); // Make sure the LEDs are reset

    // Initialize RGB values to represent Carnellian color
    led_val.red = 179;
    led_val.green = 27;
    led_val.blue = 27;

    while (1) {
        // Check if the red value has reached extremes and switch directions
        if (led_val.red >= 179) {
            up_flag = 0; // Start dimming
        } else if (led_val.red <= 18) {
            up_flag = 1; // Start brightening
        }

        // Increase or decrease the LED values
        if (up_flag) {
            led_val.red += 6;
            led_val.green += 1;
            led_val.blue += 1;
        } else {
            led_val.red -= 6;
            led_val.green -= 1;
            led_val.blue -= 1;
        }

        // Write new values to LED0
        set_led0(led_val);
        delay(50); // Adjust delay to control pulsing speed
    }
}
