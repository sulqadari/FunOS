#include "x_queue.h"

/**
 * The last function which is called before the process
 * passes processor over to another process.
*/
static void
context_switch(i8* currStack, i8* newStack)
{

}

/**
 * Reschedules processor o highest priority eligible process.
*/
void
reschedule(void)
{
	Process* curr;
	Process* new;

	/* If rescheduling is deferred, record this
	 * attempt to reschedule and return. */
	if (defer.attemptCount > 0) {
		defer.isDeffered = 1;
		return;
	}

	curr = &procTable[currPID];
	if (curr->state == PR_CURR) {
		
		/* If the priority of the current process is higher than the one
		 * waiting on the READY list, then just return. */
		if (curr->priority > GET_FIRST_KEY(readyListID))
			return;
		
		/* Otherwise, put him into the READY list. */
		curr->state = PR_READY;
		prio_insert(currPID, readyListID, curr->priority);
	}

	currPID = fifo_dequeue(readyListID);
	new = &procTable[currPID];
	new->state = PR_CURR;
	preemption = QUANTUM;

	context_switch(&curr->sp, &new->sp);

	/* Old process returns here when resumed. */
}

/**
 * Rescheduling deferral handler.
 * Everytime a deferral is requested, the code increments
 * Defer:attemptCount. Later, when f function ends its deferral
 * period, that field is decremented.
*/
Status
sched_defer(i32 cmd)
{
	switch (cmd) {
		case DEFER_START:
			if (defer.attemptCount++ == 0)
				defer.isDeffered = 0;
		break;
		case DEFER_STOP:
			if (defer.attemptCount <= 0)
				return ERR_DEFER_OUT_OF_RANGE;
			
			if ((--defer.attemptCount == 0) && defer.isDeffered)
				reschedule();
		break;
		default: return ERR_DEFER_UNKNOWN_OPTION;
	}

	return NO_ERROR;
}