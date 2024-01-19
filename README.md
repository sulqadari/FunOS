# Hierarchy


 ___________________________________
|           Applications            | 8
|___________________________________|
|           File System             | 7
|___________________________________|
|            Networking             | 6
|___________________________________|
|           IO Routines             | 5
|___________________________________|
|     Real-Time Clock Management    | 4
|___________________________________|
|       Process Coordination        | 3
|___________________________________|
| 		Process Management			| 2
|___________________________________|
| 		  Memory Manager 			| 1
|___________________________________|
|            Hardware               | 0
|___________________________________|

The multi-level structure describes only the internal implementation and does't
restrict the services the system provides. That is, the Application layer can call
any function from the underlying levels.

The main services that an OS supplies are as follows:
	- concurrent execution (5-6);
	- facilities for process synchronization (7);
	- IPC (8, 11);
	- Dynamic memory allocation (9);
	- Management of address spaces and virtual memory (10);
	- High-level interface for IO devices (13-15);
	- Network and internet communication (16-17);
	- A file system and file access facilities (19-21);

Concurent execution is at the heart of an OS and affects each piece of OS code.
Thus, this journey begins by this mobule.
The systems thtat support multitasking can be divided into two broad categories:

	"timesharing" - equal priority to all computations. The latter can start and
					terminate at any time.

	"real-time"   - due to performance constraints, this kind of OSs doesn't
					treat all computations equally.

Xinu permits processes to share an address space, i.e. Xinu processes follow
a "thread" model, thus there is one process with multiple tasks declared at
compile time which share a join address space.


					4. List and queue manipulation functions
These functions represent a unified approach - a single data structure and a
single set of nodes used by all levels of the OS to maintain lists of processes.
There is a six types of lists of processes:
	 - waiting
	 - sleeping
	 -

A process manager handles objects called "processes".It moves a process from one list
to another very frequently doing it by means of storing its ID in the list. All that
lists are stored in one structure with the following attributes:
	- all lists are doubly linked.
	- nodes store a PID and KEY, even though the latter isn't used in FIFO lists.
	- lists have HEAD and TAIL nodes.
	- non-FIFO (e.g. priority) lists are ordered in descending order; note that
	  HEAD_KEY > MAX_KEY, and TAIL_KEY < MIN_KEY.

        HEAD                                                    TAIL
	 _____________     _____________     _____________     _____________ 
	|  |   |   |x-|-->|  |   |   |x-|-->|  |   |   |x-|-->|  |   |   |  |
	|X |PID|KEY|  |   |  | 4 | 25|  |   |  | 2 | 14|  |   |  |PID|KEY| X|
	|_ |___|___|__|<--|-x|___|___|__|<--|-x|___|___|__|<--|-x|___|___|__|


					4.3 A compact list data structure
To optimize the memory usage in linked lists, Xunu features two approaches:

	Relative pointers - instead of using pointer, each element in the lists
						is represented by 8-bit integer identifier, i.e. the
						array index can be used instead of pointer.
	
	Implicit data structure - omitting the PID field from all nodes. The relative
							  address of the a node is the same as the ID of the
							  process being stored.

Queue table - the array containing all types of queues. The indices from 0 through
NPROC - 1 each correspond to one process, and the ones beyond that ranges designate
heads and tails of the lists. The maximum number of lists are each known at compile
time and a process can only appear on one list at a given time.

