#ifndef X_PROCESS_H
#define X_PROCESS_H

#include "x_common.h"

#define PROC_TOTAL	8

typedef enum {
	PS_FREE,
} ProcState;

#define IS_BAD_PID(pid) \
	((pid < 0) || (pid >= PROC_TOTAL) || \
	 (procTable[pid].state == PS_FREE))

typedef struct {
	u16 state;
	i16 priority;
} Process;

extern Process procTable[];

#endif // !X_PROCESS_H