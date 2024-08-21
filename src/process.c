#include "process.h"

Defer _defer;
int16_t readylist; /* the queue ID of the 'reay' list */
int16_t preempt;

void
context_switch(uint32_t* old_stack, uint32_t* new_stack)
{

}

/*------------------------------------------------------------------------
* resched - Reschedule processor to highest priority eligible process.
* Assumes interrupts are disabled.
*------------------------------------------------------------------------
*/
void
resched(void)
{
	Process *ptold; /* Ptr to table entry for old process */
	Process *ptnew; /* Ptr to table entry for new process */

	/* If rescheduling is deferred, record attempt and return */
	if (_defer.attempts_count > 0) {
		_defer.attempt = 1;
		return;
	}

	/* Point to process table entry for the current (old) process */
	ptold = &process_table[process_current];
	if (ptold->state == PROC_CURR) { /* Process remains eligible */
		if (ptold->prio > firstkey(readylist))
			return;

		/* Old process will no longer remain current */
		ptold->state = PROC_READY;
		insert(process_current, readylist, ptold->prio);
	}

	/* Force context switch to highest priority ready process */
	process_current = dequeue(readylist);
	ptnew = &process_table[process_current];
	ptnew->state = PROC_CURR;
	preempt = QUANTUM; /* Reset time slice for process */

	context_switch(&ptold->stack, &ptnew->stack);
	/* Old process returns here when resumed */
	return;
}

/*------------------------------------------------------------------------
* resched_cntl - Control whether rescheduling is deferred or allowed.
* Assumes interrupts are disabled
* int32_t defer - Either DEFER_START or DEFER_STOP
*------------------------------------------------------------------------
*/
int16_t
resched_cntl(int32_t defer)
{
	switch (defer) {
		case DEFER_START: /* Handle a deferral request */
			if (_defer.attempts_count++ == 0)
				_defer.attempt = 0;
		return FUNOS_SW_OK;

		case DEFER_STOP: /* Handle end of deferral */
			if (_defer.attempts_count <= 0)
				return FUNOS_SW_DEFERRING_CTRL_ERR;

			if ( (--_defer.attempts_count == 0) && _defer.attempt )
				resched();
		return FUNOS_SW_OK;

		default:
			return FUNOS_SW_DEFERRING_CTRL_ERR;
	}
}

/*------------------------------------------------------------------------
* ready - Make a process eligible for CPU service.
* int32_t pID - ID of process to make ready
*------------------------------------------------------------------------
*/
int16_t
ready(int32_t pID)
{
	Process *process;
	if (HAS_BAD_PROC_ID(pID))
		return FUNOS_SW_BAD_PROC_ID;
	
	/* Set process state to indicate ready and add to ready list */
	process = &process_table[pID];
	process->state = PROC_READY;

	insert(pID, readylist, process->prio);
	resched();
	
	return FUNOS_SW_OK;
}

/*------------------------------------------------------------------------
* resume - Unsuspend a process, making it ready
* int32_t pID - ID of process to unsuspend 
*------------------------------------------------------------------------
*/
int16_t
resume(int32_t pID)
{
	uint32_t mask;			/* Saved interrupt mask */
	Process *process;			/* Ptr to process’ table entry */
	int16_t prio;			/* Priority to return */
	mask = disable();
	
	if (HAS_BAD_PROC_ID(pID)) {
		restore(mask);
		return FUNOS_SW_BAD_PROC_ID;
	}
	
	process = &process_table[pID];
	if (process->state != PROC_SUSP) {
		restore(mask);
		return FUNOS_SW_INCORRECT_PROC_STATE;
	}
	
	prio = process->prio; /* Record priority to return */
	ready(pID);
	restore(mask);
	
	return prio;
}

/*------------------------------------------------------------------------
* suspend - Suspend a process, placing it in hibernation
* int32_t pID - ID of process to suspend
*------------------------------------------------------------------------
*/
int16_t
suspend(int32_t pID)
{
	uint32_t mask; /* Saved interrupt mask */
	Process *process; /* Ptr to process’ table entry */
	int16_t prio; /* Priority to return */
	
	mask = disable();
	if (HAS_BAD_PROC_ID(pID) || (pID == PROC_NULL)) {
		restore(mask);
		return FUNOS_SW_BAD_PROC_ID;
	}

	/* Only suspend a process that is current or ready */
	process = &process_table[pID];
	if ((process->state != PROC_CURR) && (process->state != PROC_READY)) {
		restore(mask);
		return FUNOS_SW_INCORRECT_PROC_STATE;
	}
	
	if (process->state == PROC_READY) {
		getitem(pID); /* Remove a ready process from the ready list */
		
		process->state = PROC_SUSP;
	} else {
		process->state = PROC_SUSP; /* Mark the current process suspended and resched. */
		resched(); 
	}

	prio = process->prio;
	restore(mask);
	return prio;
}

/*------------------------------------------------------------------------
* kill - Kill a process and remove it from the system.
* int32_t pID - ID of process to kill
*------------------------------------------------------------------------
*/
int16_t
kill(int32_t pID)
{
	uint32_t mask; /* Saved interrupt mask */
	Process* process; /* Ptr to process’ table entry */
	int32_t i; /* Index into descriptors */
	mask = disable();
	if (HAS_BAD_PROC_ID(pID) || (pID == PROC_NULL) ||
		((process = &process_table[pID])->state) == PROC_FREE) {
		restore(mask);
		return FUNOS_SW_BAD_PROC_ID;
	}
	
	if (--process_count <= 1) { /* Last user process completes */
		xdone();
	}
	
	send(process->parent, pID);
	for (i = 0; i < 3; i++)
		close(process->dev_desc[i]);
	
	freestk(process->stack_base, process->stack_len);
	
	switch (process->state) {
		case PROC_CURR:
			process->state = PROC_FREE; /* Suicide */
			resched();
		case PROC_SLEEP:
		case PROC_RECTIM:
			unsleep(pID);
			process->state = PROC_FREE;
		break;
		case PROC_WAIT:
			sem_table[process->sem].scount++;
		/* Fall through */
		case PROC_READY:
			getitem(pID); /* Remove from queue */
		/* Fall through */
		default:
		process->state = PROC_FREE;
	}

	restore(mask);
	return FUNOS_SW_OK;
}

/*------------------------------------------------------------------------
* xdone - Print system completion message as last process exits
*------------------------------------------------------------------------*/
void
xdone(void)
{
	kprintf("\n\nAll user processes have completed.\n\n");
	halt(); /* Halt the processor */
}

/*------------------------------------------------------------------------
* userret - Called when a process returns from the top-level function
*------------------------------------------------------------------------
*/
void user_ret(void)
{
	kill(getpid()); /* Force process to exit */
}

/*------------------------------------------------------------------------
* newpid - Obtain a new (free) process ID
*------------------------------------------------------------------------
*/
uint32_t
new_pid(void)
{
	uint32_t i; /* Iterate through all processes*/
	static uint32_t nextpid = 1; /* Position in table to try or */

	/* one beyond end of table */
	/* Check all slots */
	for (i = 0; i < PROCESSES_MAX; i++) {
		nextpid %= PROCESSES_MAX; /* Wrap around to beginning */
		if (process_table[nextpid].state == PROC_FREE) {
			return nextpid++;
		} else {
			nextpid++;
		}
	}

	return FUNOS_SW_PROCESS_TABLE_IS_FULL;
}

/*------------------------------------------------------------------------
* getprio - Return the scheduling priority of a process
* int32_t pID - process ID
*------------------------------------------------------------------------*/
uint32_t
get_prio(int32_t pID)
{
	uint32_t mask; /* Saved interrupt mask */
	uint32_t prio; /* Priority to return */
	
	mask = disable();
	if (HAS_BAD_PROC_ID(pID)) {
		restore(mask);
		return FUNOS_SW_BAD_PROC_ID;
	}

	prio = process_table[pID].prio;
	restore(mask);
	
	return prio;
}

/*------------------------------------------------------------------------
* chprio - Change the scheduling priority of a process
* int32_t pID - ID of process to change 
* int16_t new_prio - New priority 
*------------------------------------------------------------------------*/
int16_t chprio(int32_t pID, int16_t new_prio)
{
	uint32_t mask; /* Saved interrupt mask */
	Process *process; /* Ptr to process’ table entry */
	int16_t old_prio; /* Priority to return */
	
	mask = disable();
	if (HAS_BAD_PROC_ID(pID)) {
		restore(mask);
		return FUNOS_SW_BAD_PROC_ID;
	}

	process = &process_table[pID];
	old_prio = process->prio;
	process->prio = new_prio;
	restore(mask);

	return old_prio;
}

/*------------------------------------------------------------------------
* getpid - Return the ID of the currently executing process
*------------------------------------------------------------------------
*/
int32_t
get_pid(void)
{
	return (process_current);
}

/*------------------------------------------------------------------------
* create - Create a process to start running a function on x86
* void *funcaddr - Address of the function
* uint32_t stack_size - Stack size in words 
* int16_t priority - Process priority > 0 
* char *proc_name - Name (for debugging) 
* uint32_t nargs - Number of args that follow 
*------------------------------------------------------------------------*/
int32_t
create(void *funcaddr, uint32_t stack_size, int16_t priority, char *proc_name, uint32_t nargs, ...)
{
	uint32_t savsp, *pushsp;
	uint32_t mask; /* Interrupt mask */
	uint32_t pID; /* Stores new process id */
	Process * process; /* Pointer to proc. table entry */
	int32_t i;
	uint32_t *arg_lst; /* Points to list of args */
	uint32_t *stack_addr; /* Stack address */

	mask = disable();
	if (stack_size < STACK_SIZE)
		stack_size = STACK_SIZE;

	stack_size = (uint32_t)roundmb(stack_size);
	stack_addr = (uint32_t*)getstk(stack_size);

	if (stack_addr == NULL)
		return FUNOS_SW_FAILED_TO_ALLOCATE_STACK;

	pID = new_pid();

	if ((priority < 1) || (pID == FUNOS_SW_PROCESS_TABLE_IS_FULL)) {
		
		restore(mask);
		return FUNOS_SW_FAILED_TO_CREATE_PROCESS;
	}

	process_count++;
	process = &process_table[pID];

	/* Initialize process table entry for new process */
	process->state		= PROC_SUSP; /* Initial state is suspended */
	process->prio		= priority;
	process->stack_base	= (char *)stack_addr;
	process->stack_len	= stack_size;
	process->name[PROC_NAME_LEN-1] = NULL;
	
	for (i = 0; i < PROC_NAME_LEN - 1; i++) {
		process->name[i] = proc_name[i];
		if (process->name[i] == NULL)
			break;
	}

	process->sem = -1;
	process->parent = (int32_t)get_pid();
	process->has_msg = FALSE;

	// Set up stdin, stdout, and stderr descriptors for the shell
	process->dev_desc[0] = DESCRIPTOR_CONSOLE;
	process->dev_desc[1] = DESCRIPTOR_CONSOLE;
	process->dev_desc[2] = DESCRIPTOR_CONSOLE;

	// Initialize stack as if the process was called
	*stack_addr = STACKMAGIC;
	savsp = (uint32_t)stack_addr;
	
	// Push arguments
	arg_lst = (uint32_t *)(&nargs + 1); // Start of args
	arg_lst += nargs - 1; // Last argument
	
	// Machine dependent; copy args onto created process’ stack.
	for ( ; nargs > 0; nargs--)	
		*--stack_addr = *arg_lst--; 
	
	*--stack_addr = (long)PROC_RETADDR; // Push on return address

	// The following entries on the stack must match what ctxsw
	// expects a saved process state to contain: ret address,
	// ebp, interrupt mask, flags, registers, and an old SP

	// Make the stack look like it’s half-way through a call to
	// ctxsw that "returns" to the new process
	*--stack_addr = (uint32_t)funcaddr;

	// This will be register ebp for process exit
	*--stack_addr = savsp;
	
	// Start of frame for ctxsw
	savsp = (uint32_t) stack_addr;

	// new process runs with interrupts enabled
	*--stack_addr = 0x00000200;

	// Basically, the following emulates an x86 "pushal" instruction
	*--stack_addr = 0; // %eax
	*--stack_addr = 0; // %ecx
	*--stack_addr = 0; // %edx
	*--stack_addr = 0; // %ebx
	*--stack_addr = 0; // %esp; value filled in below
	pushsp = stack_addr; // Remember this location
	*--stack_addr = savsp; // %ebp (while finishing ctxsw)
	*--stack_addr = 0; // %esi
	*--stack_addr = 0; // %edi

	*pushsp = (uint32_t) (process->stack = (char *)stack_addr);
	restore(mask);
	return pID;
}