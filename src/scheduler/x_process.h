#ifndef X_PROCESS_H
#define X_PROCESS_H

#include "x_common.h"


typedef enum {
	PR_FREE,	/* Unsed */
	PR_CURR,	/* Current */
	PR_READY,	/* On 'ready' queue */
	PR_RECV,	/* Waiting for message */
	PR_SLEEP,	/* Is sleeping */
	PR_SUSP,	/* Is suspended */
	PR_WAIT,	/* On semaphore queue */
	PR_RECTIM,	/* Receiving with timeout */
} ProcState;

#define PROC_TOTAL			8
#define PROC_NAME_LEN		16
#define PROC_NULL			0
#define PROC_STACK_SIZE		512
#define PROC_STACK_MAGIC	0x0A0AAAA9
#define PROC_DFLT_PRIO		20
#define PROC_RETURN_ADDR	userret
#define PROC_DESCTR_TOTAL	4

#define IS_BAD_PID(pid) \
	((pid < 0) || (pid >= PROC_TOTAL) || \
	 (procTable[pid].state == PR_FREE))

#define QUANTUM 1000

typedef struct {
	u16 state;
	i16 priority;
	i8* sp;			/* Stack pointer */
	i8* stkBase;	/* Stack base */
	u32	stkLen;
	i8* name[PROC_NAME_LEN];
	i32 semID;
	i32 parent;		/* ID of the creating process */
	u32 message;
	u8  hasMsg;
	i16 desc[PROC_DESCTR_TOTAL];

} Process;

extern Process procTable[];
extern i32 procsCount;		/* Number of active processes */
extern i32 currPID;			/* Current process */


typedef struct {
	i32 attemptCount;
	i32 isDeffered;
#define DEFER_START 1
#define DEFER_STOP 0
} Defer;

extern i32 readyListID;
extern Defer defer;
extern i32 preemption;

void reschedule(void);
Status sched_defer(i32 cmd);
Status sched_ready(i32 pID);

#endif // !X_PROCESS_H