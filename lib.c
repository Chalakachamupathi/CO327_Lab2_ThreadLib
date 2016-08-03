#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "threadlib.h"

#define DEBUG
/* uncomment when you are done! */

#ifdef DEBUG
 #define PRINT   printf
#else 
 #define PRINT(...)
#endif

/* information about threads */
struct tcb { 
  void *sp;  /* Address of stack pointer. 
	      * Keep this as first element would ease switch.S 
	      * You can do something else as well. 
	      */  
  /* you will need others stuff */ 
  /**
  *save the memory address for the free function
  **/      
  void* initMemAddress;

  struct tcb *forword;
  struct tcb *backword;     
};

typedef struct tcb tcb_t;
typedef struct tcb *TCB;


TCB head = NULL;

/**
 * assembly code for switching 
 * @sp -- new stack to switch 
 * return sp of the old thread
 * 
 * Switching 
*/
void machine_switch(tcb_t *newthread /* addr. of new TCB */, 
		    tcb_t *oldthread /* addr. of old TCB */);

void switch_threads(tcb_t *newthread /* addr. of new TCB */, 
		    tcb_t *oldthread /* addr. of old TCB */);


		    

/** Data structures and functions to support thread control box */ 

void create_node(long int * stack, long int* memAdd){
     TCB tem = malloc(sizeof(tcb_t));
     tem -> sp = stack;
     tem -> initMemAddress = memAdd;
     tem -> backword = tem;
     tem -> forword = tem;
     head = tem;
}

void addNode(long int * stack, long int* memAdd){
    if (head == NULL){
      	create_node(stack, memAdd);
      	return;
    }

    TCB tem = malloc(sizeof(tcb_t));
    tcb_t* forwordtcb = head->forword;
    head->forword = tem;
    tem -> sp = stack;
    tem ->initMemAddress = memAdd;
    tem -> backword = head;
    tem -> forword = forwordtcb;
    forwordtcb -> backword = tem;
    return;
}

/** end of data structures */



void switch_threads(tcb_t *newthread /* addr. of new TCB */, tcb_t *oldthread /* addr. of old TCB */) {

  /* This is basically a front end to the low-level assembly code to switch. */

  machine_switch(newthread , oldthread );
 
	//assert(!printf("Implement %s",__func__));

}


/*********************************************************
 *                 Thread creation etc 
 *********************************************************/

/* Notes: make sure to have sufficient space for the stack
 * also it needs to be aligned 
 */

#define STACK_SIZE (sizeof(void *) * 400)
#define FRAME_REGS 48 // is this correct for x86_64?

#include <stdlib.h>
#include <assert.h>

/*
 * allocate some space for thread stack.
 * malloc does not give size aligned memory 
 * this is some hack to fix that.
 * You can use the code as is. 
 */
void * malloc_stack(void); 

void * malloc_stack() 
{
   void *ptr = malloc(STACK_SIZE + 16);
   if (!ptr) return NULL;
   return ptr;
}

int create_thread(void (*ip)(void)) {
	
	long int  *stack; 
  long int  *initMemAddress; 
  
	initMemAddress = malloc_stack();
	if(!initMemAddress) return -1; /* no memory? */

  /**
   * Stack layout: last slot should contain the return address and I should have some space 
   * for callee saved registers. Also, note that stack grows downwards. So need to start from the top. 
   * Should be able to use this code without modification Basic idea: C calling convention tells us the top 
   * most element in the stack should be return ip. So we create a stack with the address of the function 
   * we want to run at this slot. 
   */
   //aligned at 16
   stack = (void *)(((long int)initMemAddress & (-1 << 4)) + 0x10);
   /**
   *Moving stack pointer to higer position and saving the sapce for Fram registres
   *And set ip to thet
   **/
   stack = stack + STACK_SIZE - sizeof(void *) *FRAME_REGS;
   (*stack) = (long int)ip;
   //save the space for 15 register that we are going to push
	 stack = stack - 15;

   addNode(stack, initMemAddress);
	return 0;
}

void yield(){
  /* thread wants to give up the CPUjust call the scheduler to pick the next thread. */
    head = head->backword;
    switch_threads(head,(head->forword));
}


void delete_thread(void){

  /* When a user-level thread calls this you should not 
   * let it run any more but let others run
   * make sure to exit when all user-level threads are dead */ 

  if (head != head -> forword){

      tcb_t* tem = head;
      tcb_t* save1 = head -> forword;

      head = head -> backword;

      save1 -> backword = head;
      head -> forword = save1;

      free(tem -> initMemAddress);
      free(tem);
      delete_start(head);
  }else{
      free(head -> initMemAddress);
      free(head);
      exit(0);
  }
  
	   
  assert(!printf("Implement %s",__func__));
}


void stop_main(void)
{ 
  /* Main function was not created by our thread management system. 
   * So we have no record of it. So hijack it. 
   * Do not put it into our ready queue, switch to something else.*/
	start_thread((head -> sp)+(sizeof(void *) *15));
	
  assert(!printf("Implement %s ",__func__));

}


