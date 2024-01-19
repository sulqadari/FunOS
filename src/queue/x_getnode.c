#include "x_queue.h"

/**
 * Removes a process from an arbitrary point in a queue.
*/
static i32
get_item(i32 pID)
{
	i32 prev, next;

	next = queueTable[pID].next;
	prev = queueTable[pID].prev;

	queueTable[prev].next = next;
	queueTable[next].prev = prev;

	return (pID);
}

/**
 * Removes a process from the front of a queue
*/
i32
get_first_node(i16 qID)
{
	i32 head;

	if (IS_EMPTY_NODE(qID))
		return NODE_EMPTY;
	
	head = GET_HEAD(qID);
	return get_item(queueTable[head].next);
}

/**
 * Removes a process from the end of a queue
*/
i32
get_last_node(i16 qID)
{
	i32 tail;

	if (IS_EMPTY_NODE(qID))
		return NODE_EMPTY;
	
	tail = GET_TAIL(qID);
	return get_item(queueTable[tail].prev);
}