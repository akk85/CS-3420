#include "3140_concur.h"
#include "led.h"
#include "lock.h"

lock_t l;

void p1(void) {
    for (int i = 0; i < 100; i++) {
        l_lock(&l);
        red_on_frdm();
        delay(150);
        red_off_frdm();
        l_unlock(&l);
        delay(150);
    }
}

int main(void) {
    led_init();
    l_init(&l);

    for (int i = 0; i < 5; i++) {
        if (process_create(p1, 30) < 0) {
            return -1;
        }
    }

    process_start();
	while(1);
	return 0;
}


//Test Case 3:
//This test case aims to stress the lock mechanism by rapidly
//acquiring and releasing the lock in a tight loop, simulating a high contention scenario.

//Expected Observation:
//The red LED should flicker rapidly without staying on for too long,
//indicating that the lock is being successfully acquired and released
//by different processes in quick succession. This shows that there is no deadlock happening showing that
//our lock can handle high contention.














