#include "process.h"
#include "3140_concur.h"
#include <stdlib.h>
#define ten_milli_seconds 0x0000000A  //100Hz

/* Creates a new process that starts at function f with intial stack size of n
 * Return -1 if creation failed and 0 on success
 * Allocate Memory for process_t structure using malloc
 * Initialized by calling function process_stack_init
 */
unsigned int * stack;
int process_create (void (*f)(void), int n){
	//n = 256;
	NVIC_DisableIRQ(PIT_IRQn);

	stack = process_stack_init(f, n); //inititalize the stack

	if (stack == NULL){
		return -1;
	}

	//create memory for process block.
	process_t * new_process = (process_t *)malloc(sizeof(process_t));


	if (new_process == NULL){
		return -1;
	}

	//Initialize the fields for process
	new_process->sp = stack;

	new_process->size = n;

	new_process->osp = stack;

	NVIC_EnableIRQ(PIT_IRQn);
	//Add the new process to the queue
	enqueue(new_process, &process_queue);


	return 0;

}


void process_start(void){

	//Enable the clock
    SIM->SCGC6 |= SIM_SCGC6_PIT_MASK;

    // Enable PIT and allow it to run in debug mode
    PIT->MCR = 0;

    // Configure PIT to generate an interrupt every 0.01 second
    PIT->CHANNEL[0].LDVAL =  149999;//149999;

//    // Disable timer and interrupt
//    PIT->CHANNEL[0].TCTRL = PIT_TCTRL_TEN_MASK;
//
    // Enable timer and interrupt
    PIT->CHANNEL[0].TCTRL = PIT_TCTRL_TEN_MASK | PIT_TCTRL_TIE_MASK;


    NVIC_EnableIRQ(PIT_IRQn);

    //starts the concurrency
    process_begin();

}



/* Make sure we handle event of when a program terminates, next process should be selected
 * by calling process_select
 */
unsigned int * process_select(unsigned int * cursp){
	NVIC_DisableIRQ(PIT_IRQn);
	if (cursp != NULL){
		current_process_p->sp = cursp;// Update the stack pointer for the current process

		if (is_empty(&process_queue)!=1) {
			enqueue(current_process_p, &process_queue); //add process to queue
			current_process_p = dequeue(&process_queue);
			NVIC_EnableIRQ(PIT_IRQn);
			return current_process_p->sp;
		}
		else {
			NVIC_EnableIRQ(PIT_IRQn);
			return current_process_p->sp;
		}

	}
	else if(cursp==NULL && current_process_p!=NULL) {

			// Free the stack and Program Control Block of the terminated process
//			NVIC_DisableIRQ(PIT_IRQn);
			process_stack_free(current_process_p->osp, current_process_p->size);

			free(current_process_p);

			if (is_empty(&process_queue)!=1) {
				current_process_p = dequeue(&process_queue);
				NVIC_EnableIRQ(PIT_IRQn);
				return current_process_p->sp;
			}
			else {
				NVIC_EnableIRQ(PIT_IRQn);
				return NULL;
			}

	}
	else if(cursp==NULL && current_process_p==NULL) {

				if (is_empty(&process_queue)!=1) {
	//				enqueue(current_process_p, &process_queue); //add process to queue
					current_process_p = dequeue(&process_queue);
					NVIC_EnableIRQ(PIT_IRQn);
					return current_process_p->sp;
				}
				else {
					NVIC_EnableIRQ(PIT_IRQn);
					return NULL;
				}


		}



	current_process_p->next = NULL;


	NVIC_EnableIRQ(PIT_IRQn);
	return current_process_p->sp;


}

//
//unsigned int * process_select(unsigned int * cursp) {
//    NVIC_DisableIRQ(PIT_IRQn);
//
//    // Clean up if the current process has finished
//    if (cursp == NULL && current_process_p != NULL) {
//        process_stack_free(current_process_p->osp, current_process_p->size);
//        free(current_process_p);
//        current_process_p = NULL;
//
//    } else if (cursp != NULL) {
//        current_process_p->sp = cursp;
//        enqueue(current_process_p, &process_queue);
//    }
//
//    if (!is_empty(&process_queue)) {
//        current_process_p = dequeue(&process_queue);
//    }
//
//    NVIC_EnableIRQ(PIT_IRQn);
//    return current_process_p ? current_process_p->sp : NULL;
//}
//
