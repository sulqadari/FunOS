#include "x_queue.h"
#include "x_process.h"

Node queueTable[NODE_TOTAL];

/**
 * Insert a process at the tail of a queue.
*/
i32
fifo_enqueue(i32 pID, i16 qID)
{
	i16 tail, prev;

	if (IS_BAD_QID(qID))
		return ERR_BAD_QID;

	if (IS_BAD_PID(pID))
		return ERR_BAD_PID;
	
	tail = GET_TAIL(qID);
	prev = queueTable[tail].prev;

	/* Make the new node pointing to the 'ex-last node'
	 * and the tail. */
	queueTable[pID].next = tail;
	queueTable[pID].prev = prev;

	/* Make the ex-last node point to the 'new last' node. */
	queueTable[prev].next = pID;

	/* Make the tail point to the 'new last' node. */
	queueTable[tail].prev = pID;

	return pID;
}

/**
 * Remove the first process on a list.
 * @return i32 a pID of the process being removed.
*/
i32
fifo_dequeue(i16 qID)
{
	i32 pID;

	if (IS_BAD_QID(qID))
		return ERR_BAD_QID;
	
	if (IS_EMPTY_NODE(qID))
		return NODE_EMPTY;
	
	pID = GET_FIRST_NODE(qID);
	queueTable[pID].prev = NODE_EMPTY;
	queueTable[pID].next = NODE_EMPTY;
	return pID;
}

