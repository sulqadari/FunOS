#ifndef X_QUEUE_H
#define X_QUEUE_H

#include "x_process.h"

#define SEM_COUNT	8
#define NODE_TOTAL	(PROC_TOTAL + 4 + SEM_COUNT * 2)

#define NODE_EMPTY	(-1)
#define KEY_MAX		0x7FFFFFFF
#define KEY_MIN		0x80000000

typedef struct {
	i32 key;	// the key of the node
	i16 next;	// The next node on the list
	i16 prev;	// The previous node on the list
} Node;

extern Node queueTable[];

#define GET_HEAD(idx) \
	(idx)
#define GET_TAIL(idx) \
	(idx + 1)

#define GET_FIRST_NODE(idx) \
	(queueTable[GET_HEAD(idx)].next)

#define GET_LAST_NODE(idx) \
	(queueTable[GET_TAIL(idx)].prev)

#define IS_EMPTY_NODE(idx) \
	(GET_FIRST_NODE(idx) >= PROC_TOTAL)

#define NOT_EMPTY(idx) \
	(GET_FIRST_NODE(idx) < PROC_TOTAL)

#define GET_FIRST_KEY(idx) \
	(queueTable[GET_FIRST_NODE(idx)].key)

#define GET_LAST_KEY(idx) \
	(queueTable[GET_LAST_NODE(idx)].key)

#define IS_BAD_QID(idx) \
	((idx < 0) || (idx >= NODE_TOTAL))



#endif // !X_QUEUE_H