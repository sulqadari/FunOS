#ifndef FUNOS_STATUSES_H
#define FUNOS_STATUSES_H

typedef enum {
	gpSuccess		= 0x00,	/* Success. */
	gpErrCardTerm,
	gpErrCritical	= 0xFF	/* Critical error. */
} gpStatus;

#endif /* FUNOS_STATUSES_H */