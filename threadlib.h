#ifndef __THREAD_LIB__
#define __THREAD_LIB__

/**
 * create a thread. 
 * @ip -- stating address of the thread (function pointer)
 * returns 0 on success -1 if failed
 */
int create_thread(void (*ip)(void));

/**
 * yeild the cpu (give a chance for another to run)
 */
void yield(void);

/**
 * The main function runs in the kernel created thread. 
 * This will create all the other threads and once other 
 * threads are created this function will be called and 
 * after that main thread should not be called at all. 
 * You should be able to use the same switch function 
 * that your would use to switch from one thread to another. 
 */
void stop_main(void);

/**
 * a thread wants to die
 */
void delete_thread(void);
/**
*@sp -- pass the stack pointer to starting thread
*This is the assembly function for the stop_main function
**/
void start_thread(void* sp);
/**
*@tem -- passing tcb_t to start the thread
*This takes tcb_t pointer as an argument and switch to that thread from the current thread
*And this is assembly function in the delete_thread function
**/
void delete_start(void* tem);


#endif
