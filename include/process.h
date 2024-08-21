#ifndef FUNOS_PROCESS_H
#define FUNOS_PROCESS_H

#include "common.h"

/* Maximum number of processes in the system */
#ifndef PROCESSES_MAX
	#define PROCESSES_MAX 8
#endif

/* Process state constants */
#define PROC_FREE		0 /* Process table entry is unused */
#define PROC_CURR		1 /* Process is currently running */
#define PROC_READY		2 /* Process is on ready queue */
#define PROC_RECV		3 /* Process waiting for message */
#define PROC_SLEEP		4 /* Process is sleeping */
#define PROC_SUSP		5 /* Process is suspended */
#define PROC_WAIT		6 /* Process is on semaphore queue */
#define PROC_RECTIM		7 /* Process is receiving with timeout */

/* Miscellaneous process definitions */
#define PROC_NAME_LEN	16 /* Length of process "name" */

#define PROC_NULL		0 /* ID of the null process */

/* Process initialization constants */
#define STACK_SIZE		1024	/* Initial process stack size */
#define PROC_PRIORITY	20		/* Initial process priority */

#define PROC_RETADDR	user_ret	/* Address to which process returns */

/* Inline code to check process ID (assumes interrupts are disabled) */
#define HAS_BAD_PROC_ID(pID)	\
(((int32_t)(pID) < 0) || ((int32_t)(pID) >= PROCESSES_MAX) || (process_table[(pID)].state == PROC_FREE))

/* Number of device descriptors a process can have open */
#define DESCRIPTORS_TOTAL 5 /* must be odd to make procent 4N bytes */
#define DESCRIPTOR_CONSOLE	(0)

/* Marker for the top of a process stack (used to help detect overflow) */
#define STACKMAGIC 0x0A0AAAA9

/* Definition of the process table (multiple of 32 bits) */
typedef struct Process_t {			/* Entry in the process table */
	uint16_t	state;				/* Process state: PROC_CURR, etc. */
	int16_t		prio;				/* Process priority */
	char*		stack;				/* Saved stack pointer */
	char*		stack_base;			/* Base of run time stack */
	uint32_t	stack_len;			/* Stack length in bytes */
	char		name[PROC_NAME_LEN];/* Process name */
	int32_t		sem;				/* Semaphore on which process waits */
	int32_t		parent;				/* ID of the creating process */
	uint32_t	msg;				/* Message sent to this process */
	int8_t		has_msg;			/* Nonzero if msg is valid */
	int16_t		dev_desc[DESCRIPTORS_TOTAL]; /* Device descriptors for process */
} Process;

typedef struct Defer_t {
	int8_t attempt;
	int32_t attempts_count;
} Defer;

#define DEFER_START	1
#define DEFER_STOP	2

extern Process process_table[];
extern int32_t process_count;	/* Currently active processes */
extern int32_t process_current; /* Currently executing process */

void context_switch(uint32_t* old_stack, uint32_t* new_stack);
void resched(void);
int16_t resched_cntl(int32_t defer);
int16_t ready(int32_t pID);
int16_t resume(int32_t pID);
#endif /* FUNOS_PROCESS_H */