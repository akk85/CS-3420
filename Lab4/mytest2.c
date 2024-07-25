#include "3140_concur.h"
#include "led.h"
#include "lock.h"

lock_t l;

void p1(void) {
    l_lock(&l);
    red_on_frdm();
    delay(1000);
    red_off_frdm();
    l_unlock(&l);
}

void p2(void) {
    l_lock(&l);
    green_on_frdm();
    delay(1000);
    green_off_frdm();
    l_unlock(&l);
}

int main(void) {
    led_init();
    l_init(&l);

    if (process_create(p1, 30) < 0) {
        return -1;
    }
    if (process_create(p2, 30) < 0) {
        return -1;
    }

    process_start();
    while (1);
}

//Test case 4
//Simple test to test for the order in which the lock is released.
//Expected Observation:
//The red LED should turn on first and then off, indicating that process p1 has acquired and released the lock sucessfuly.
//Immediately after the red LED turns off, the green LED should turn on and then off, indicating that process p2 successfully
//acquired the lock right after process p1 released it.

