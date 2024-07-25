#include "3140_concur.h"
#include "lock.h"

/**
 * Initialises the lock structure
 *
 * @param l pointer to lock to be initialised
 */
void l_init(lock_t* l){

	l->locked = 0;
}


/**
 * Grab the lock or block the process until lock is available
 *
 * @param l pointer to lock to be grabbed
 */
void l_lock(lock_t* l){
	NVIC_DisableIRQ(PIT_IRQn);
	while (l->locked == 1){
		NVIC_EnableIRQ(PIT_IRQn);
		while (l->locked == 1){
		}
		NVIC_DisableIRQ(PIT_IRQn);
	}
	l->locked = 1;		// current process grabs lock
	NVIC_EnableIRQ(PIT_IRQn);

}

/**
 * Release the lock along with the first process that may be waiting on
 * the lock. This ensures fairness wrt lock acquisition.
 *
 * @param l pointer to lock to be unlocked
 */
void l_unlock(lock_t* l){
	NVIC_DisableIRQ(PIT_IRQn);

	l->locked = 0;

	NVIC_EnableIRQ(PIT_IRQn);
}
