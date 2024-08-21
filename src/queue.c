#include "queue.h"
#include "process.h"

/* Table of process queues */
Queue_entry queue_table[QUEUE_ENTRIES_MAX];

/*------------------------------------------------------------------------
* getfirst - Remove a process from the front of a queue
* int16_t qID -  ID of queue from which to remove a process
*------------------------------------------------------------------------ */
int32_t
get_first(int16_t qID)
{
	int32_t head;
	if (IS_EMPTY(qID)) {
		return FUNOS_SW_QUEUE_IS_EMPTY;
	}

	head = QUEUE_HEAD(qID);
	return getitem(queue_table[head].next);
}
/*------------------------------------------------------------------------
* getlast - Remove a process from end of queue
* int16_t qID -  ID of queue from which to remove a process
*------------------------------------------------------------------------ */
int32_t
get_last(int16_t qID)
{
	int32_t tail;
	if (IS_EMPTY(qID)) {
		return FUNOS_SW_QUEUE_IS_EMPTY;
	}

	tail = QUEUE_TAIL(qID);
	return get_item(queue_table[tail].prev);
}

/*------------------------------------------------------------------------
* getitem - Remove a process from an arbitrary point in a queue
* int32_t pID - ID of process to remove
*------------------------------------------------------------------------*/
int32_t
get_item(int32_t pID)
{
	int32_t prev, next;
	next = queue_table[pID].next; /* Following node in list */
	prev = queue_table[pID].prev; /* Previous node in list */
	queue_table[prev].next = next;
	queue_table[next].prev = prev;

	return pID;
}


/*------------------------------------------------------------------------
* enqueue - Insert a process at the tail of a queue
* pid32 pID - ID of process to insert
* ID of queue to use
*------------------------------------------------------------------------
*/
int32_t
enqueue(int32_t pID, int16_t qID)
{
	int16_t tail, prev; /* Tail & previous node indexes */
	if (HAS_BAD_QUEUE_ID(qID) || HAS_BAD_PROC_ID(pID)) {
		return FUNOS_SW_BAD_PROC_ID;
	}

	tail = QUEUE_TAIL(qID);
	prev = queue_table[tail].prev;
	queue_table[pID].next  = tail; /* Insert just before tail node */
	queue_table[pID].prev  = prev;
	queue_table[prev].next = pID;
	queue_table[tail].prev = pID;

	return pID;
}

/*------------------------------------------------------------------------
* dequeue - Remove and return the first process on a list
* int16_t qID - ID queue to use
*------------------------------------------------------------------------
*/
int32_t
dequeue(int16_t qID)
{
	int32_t pID; /* ID of process removed */

	if (HAS_BAD_QUEUE_ID(qID))
		return FUNOS_SW_BAD_QUEUE_ID;
	
	if (IS_EMPTY(qID))
		return FUNOS_SW_QUEUE_IS_EMPTY;

	pID = get_first(qID);
	queue_table[pID].prev = QUEUE_EMPTY;
	queue_table[pID].next = QUEUE_EMPTY;

	return pID;
}

/*------------------------------------------------------------------------
* insert - Insert a process into a queue in descending key order
* int32_t pID - ID of process to insert 
* int16_t qID - ID of queue to use 
* int32_t pKey - Key for the inserted process 
*------------------------------------------------------------------------
*/
int32_t
insert(int32_t pID, int16_t qID, int32_t pKey)
{
	int16_t curr; /* Runs through items in a queue*/
	int16_t prev; /* Holds previous node index */
	if (HAS_BAD_QUEUE_ID(qID) || HAS_BAD_PROC_ID(pID)) {
		return FUNOS_SW_BAD_PROC_ID;
	}

	curr = FIRST_ID(qID);
	while (queue_table[curr].key >= pKey) {
		curr = queue_table[curr].next;
	}

	/* Insert process between curr node and previous node */
	prev = queue_table[curr].prev; /* Get index of previous node */
	queue_table[pID].next  = curr;
	queue_table[pID].prev  = prev;
	queue_table[pID].key   = pKey;
	queue_table[prev].next = pID;
	queue_table[curr].prev = pID;

	return FUNOS_SW_OK;
}

/*------------------------------------------------------------------------
* newqueue - Allocate and initialize a queue in the global queue table
*------------------------------------------------------------------------
*/
int16_t
new_queue(void)
{
	static int16_t next_qID = PROCESSES_MAX; /* Next list in queue_table to use */
	int16_t qID; /* ID of allocated queue */
	qID = next_qID;
	
	if (qID > QUEUE_ENTRIES_MAX) { /* Check for table overflow */
		return FUNOS_SW_QUEUE_TABLE_IS_FULL;
	}

	next_qID += 2; /* Increment index for next call*/
	/* Initialize head and tail nodes to form an empty queue */
	queue_table[QUEUE_HEAD(qID)].next = QUEUE_TAIL(qID);
	queue_table[QUEUE_HEAD(qID)].prev = QUEUE_EMPTY;
	queue_table[QUEUE_HEAD(qID)].key  = QUEUE_KEY_MAX;
	queue_table[QUEUE_TAIL(qID)].next = QUEUE_EMPTY;
	queue_table[QUEUE_TAIL(qID)].prev = QUEUE_HEAD(qID);
	queue_table[QUEUE_TAIL(qID)].key  = QUEUE_KEY_MIM;
	return qID;
}