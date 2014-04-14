#include "mythread.h"

//  static int start = 1;
int next_tid = 1;
myqueue *runnable_q = NULL, *sleeping_q = NULL, cur_mythread;



void add_runnable(struct mythread *, myqueue *);


struct mythread *mythread_init(void)
{
    start = 0;
    runnable_q = (myqueue *) malloc(myqueue);
    runnable_q -> n = 0;
    sleeping_q = (myqueue *) malloc(myqueue);
    sleeping_q -> n = 0;
    running_q = (myqueue *) malloc(myqueue);
    running_q -> n = 0;
    
    struct mythread *t = (tcb *) malloc(sizeof(mythread));
    
    t -> state = EMBRYO;
    t -> tid = next_tid++;
    t -> context = (ucontext_t *) malloc(sizeof(ucontext_t);
    t -> context -> uc_stack.ss_sp = () malloc(sizeof(STACKSIZE));
    t -> context -> uc_stack.ss_size = STACKSIZE;
    t -> retval = NULL;
    
    if(getcontext(t -> context) == 0)
        return NULL;
    
    return t;
}

int mythread_create(int *mythread_id, const mythread_attr_t *attr, void (*start_routine) (void *), void *arg)
{
    mythread *t = mythread_init();
    if(t == NULL)
    {
        printf("\nCannot create new thread");
        return -1;
    }
    
    if(mythread_attr_t == NULL)
        my_thread_attr_t.joinable = 1;          // Joinable by default
        
    add_runnable_q(t, runnable_q);              // Add thread to RUNNABLE QUEUE
    t -> state = RUNNABLE;
    
    if(makecontext(t -> context, (void *) wrapper_function, 2, start_routine, arg) == -1)
    {
        printf("\nCannot switch to newly created thread");
        t -> state = KILLED;
    }
    
    cur_mythread -> status = RUNNABLE;
    add_runnable_q(cur_mythread, runnable_q);
    cur_mythread = t;
    swapcontext(runnable_q -> front -> mytcb -> context, cur_mythread -> mytcb -> context);
}


void add_runnable(struct mythread *thread, myqueue *queue)
{
    mythread_mutex_lock(& queue -> lock);
    
    queue = (myqueue *) malloc(sizeof(myqueue));
    
    if(queue -> num == 0)           //  Queue is empty
        queue -> front = queue -> rear = thread;
    else
        queue -> rear = thread;
    
    mythread_mutex_unlock(& queue -> lock);
}















