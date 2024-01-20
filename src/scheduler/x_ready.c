#include "x_queue.h"

/**
 * Makes a process eligible for CPU service
*/
Status
sched_ready(i32 pID)
{
	Process* proc;

	if (IS_BAD_PID(pID))
		return ERR_BAD_PID;
	
	proc = &procTable[pID];
	proc->state = PR_READY;

	prio_insert(pID, readyListID, proc->priority);
	reschedule();

	return NO_ERROR;
}