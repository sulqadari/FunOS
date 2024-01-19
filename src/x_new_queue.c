#include "x_queue.h"

/**
 * Allocates a pair of adjacent positions in the
 * queueTable array to use as head and tail nodes.
 * Because a queue can be used either as FIFO or priority
 * queue, only one allocation function is needed.
*/
i16
new_queue(void)
{
	static i16 nextQID = PROC_TOTAL;
	i16 qID;

	qID = nextQID;
	if (qID > NODE_TOTAL)
		return ERR_QTABLE_OVERFLOW;
	
	nextQID += 2;

	/* Initialize head and tail nodes to
	 * form an empty queue. */
	queueTable[GET_HEAD(qID)].next = GET_TAIL(qID);
	queueTable[GET_HEAD(qID)].prev = NODE_EMPTY;
	queueTable[GET_HEAD(qID)].key = KEY_MAX;

	queueTable[GET_TAIL(qID)].next = NODE_EMPTY;
	queueTable[GET_TAIL(qID)].prev = GET_HEAD(qID);
	queueTable[GET_TAIL(qID)].key = KEY_MIN;

}