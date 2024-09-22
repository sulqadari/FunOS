#ifndef FUNOS_STATUSES_H
#define FUNOS_STATUSES_H

typedef enum {
	gpSuccess		= 0x00,	/* <! Success. */
	gpErrCardTerm,			/* <! The card is at Terminated LCS. */
	gpErrClsRevert,			/* <! Atttempt to revert CLCS. */
	gpErrCritical	= 0xFF	/* <! Critical error. */
} gpStatus;

#endif /* FUNOS_STATUSES_H */