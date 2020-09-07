# cmpt300
## Assignment 1:-

Made a List structure comprising of Nodes (Struct) such that it has pointer to it's first, current and last node. It also stores size and pointer to list itself.\
Various functions can be applied on list structure as mentioned in List.h file.

## Assignment 2:-

* Using the List Structure made in assigment 1 and sockets, communication is built between server and client.
* Using pthreads and mutex locks 4 different threads are made to let server and client chat concurrently while on different PCs.
* Different functions running concurrently :-
  * sendClient/sendServer - send data (String) to the partner.
  * recieveClient/recieveServer- receive data from the partner.
  * printClient/PrintServer- print data recieved on the screen.
  * keywordClient/keywordServer- let user to type data to send to the partner server/client.
  
## Assignment 3:-

This assignment imitates the cpu scheduling, how the processes arrives and assigned to different priority queues and their execution accordingly.
* Using List Structure 5 different priority queues are represented.
  * L0, L1, L2 - Processes in the priority queue L0 has maximum priority and L2 has least priority.
  * Lsend & Lrecieve- Processes in these priority queues are waiting for send and receive operations respectively.
*  Process is represent by struct comprising of process PID, priority queue number, data (char array) and it states.
* State can be either blocked, ready, running.
* Semaphores are used for lock implementation.
* Through terminal various operation can be performed by user.
   * Create new process by giving it's priority.
   * Fork the current running process.
   * Kill the current running process.
   * Exit the current running process.
   * Finish the time quantum of current running process.
   * Initailize the semaphore of given id.
   * P the semaphore of given id.
   * V the semaphore of given id.
   * print details of process with given PID.
   * print details of all the processes.
   * make current running process to send message to another process.
   * make current running process to recieve messages waiting.
   * Make current running process to reply to another process.
   * terminate simulation by killing the init process.

## Assignemnt 4

This assignment imitates how the ls command work in unix system with all the options similar to built-in.\
Output is displayed in same format as built-in.
