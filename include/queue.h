#ifndef FUNOS_QUEUE_H
#define FUNOS_QUEUE_H

#include "common.h"

#ifndef QUEUE_ENTRIES_MAX
#	define QUEUE_ENTRIES_MAX (PROCESSES_MAX + 4 + SEMAPHORES_MAX + SEMAPHORES_MAX)
#endif /* QUEUE_ENTRIES_MAX */

#define QUEUE_EMPTY		0xFFFFFFFF
#define QUEUE_KEY_MAX	0x7FFFFFFF
#define QUEUE_KEY_MIM	0x80000000

typedef struct Queue_entry_t {
	int32_t key;
	int16_t next;
	int16_t prev;
} Queue_entry;

extern Queue_entry queue_table[];

#define QUEUE_HEAD(qID)	(qID)
#define QUEUE_TAIL(qID) ((qID) + 1)
#define FIRST_ID(qID)	(queue_table[QUEUE_HEAD(qID)].next)
#define LAST_ID(qID)	(queue_table[QUEUE_TAIL(qID)].prev)
#define IS_EMPTY(qID)	(FIRST_ID(qID) >= PROCESSES_MAX)
#define NOT_EMPTY(qID)	(FIRST_ID(qID) < PROCESSES_MAX)
#define FIRST_KEY(qID)	(queue_table[FIRST_ID(qID)].key)
#define LAST_KEY(qID)	(queue_table[LAST_ID(qID)].key)

/* Inline to check queue id assumes interrupts are disabled */
#define HAS_BAD_QUEUE_ID(qID)	\
	(((int32_t)(qID) < 0) || (int32_t)(qID) >= QUEUE_ENTRIES_MAX - 1)

int32_t get_first(int16_t qID);
int32_t get_last(int16_t qID);
int32_t get_item(int32_t pID);
int32_t enqueue(int32_t pID, int16_t qID);
int32_t dequeue(int16_t qID);
int32_t insert(int32_t pID, int16_t qID, int32_t pKey);
int16_t new_queue(void);

#endif /* FUNOS_QUEUE_H */