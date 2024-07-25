#include "3140_concur.h"
#include "lock.h"

/**
 * Initialises the lock structure
 *
 * @param l pointer to lock to be initialised
 */
void l_init(lock_t* l){

	l->locked = 0;
	l->blocked_queue.head = NULL;
}


/**
 * Grab the lock or block the process until lock is available
 *
 * @param l pointer to lock to be grabbed
 */
void l_lock(lock_t* l){
	NVIC_DisableIRQ(PIT_IRQn);
	// check if some other process holds the lock and block
	if (l->locked == 1){
		current_process_p->blocked = 1;
		enqueue(current_process_p, &l->blocked_queue);
		process_blocked();
		l_lock(l);
	}else {
			l->locked = 1;
	}

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
	process_t * pro;
	if (!is_empty(&l->blocked_queue)){
		pro = dequeue(&l->blocked_queue);
		pro->blocked = 0;
		enqueue(pro, &process_queue);
	}

	NVIC_EnableIRQ(PIT_IRQn);
}
