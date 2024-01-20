#include "x_queue.h"

/**
 * Inserts a process into priority queue, which can
 * be, for example the "ready list" of processes.
*/
Status
prio_insert(i32 pID, i16 qID, i32 key)
{
	i16 curr, prev;

	if (IS_BAD_QID(qID))
		return ERR_BAD_QID;

	if (IS_BAD_PID(pID))
		return ERR_BAD_PID;
	
	curr = GET_FIRST_NODE(qID);
	while (queueTable[curr].key >= key)
		curr = queueTable[curr].next;
	
	prev = queueTable[curr].prev;

	/* Initialize the new node. */
	queueTable[pID].next = curr;
	queueTable[pID].prev = prev;
	queueTable[pID].key = key;

	/* Make the surrounding nodes point to the new one. */
	queueTable[prev].next = pID;
	queueTable[curr].prev = pID;

	return NO_ERROR;
}