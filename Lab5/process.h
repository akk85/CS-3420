/*
 * process.h
 *
 * Nils Napp
 * Cornell University
 * All right reserved
 *
 * Jan 2024
 * Ithaca NY
 *
 * This file is part of the ECE3140/CS3420 offering for Spring 2024. If you are not part
 * of this class you should not have access to this file. Do not post, share, or otherwise
 * distribute this file. We will consider it an AI violation if you do.
 */

#ifndef PROCESS_H_
#define PROCESS_H_

#include "realtime.h"
#include <stdbool.h>

struct process_state{
	unsigned int *sp;   //stack pointer
	unsigned int *orig_sp;  //original stack pointer
	int n;    // stack size
	realtime_t arrival_time;  // Start time of the process
	realtime_t deadline;    // Deadline of the process
	int is_realtime;       // Is the process a real-time process?
	struct process_state * next; //next process in the queue

};

typedef struct process_state process_t;


#endif /* PROCESS_H_ */
