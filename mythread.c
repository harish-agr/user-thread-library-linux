#include "mythread.h"

//  static int start = 1;
int next_tid = 1, start = 1;
myqueue *runnable_q = NULL, *sleeping_q = NULL, finished_q = NULL;
mythread *cur_mythread;



void add_runnable(struct mythread *, myqueue *);


void *wrapper_function(void *function (void *), void *arg)
{
    void *ret = function(arg);
    mythread_exit(ret);
    
    return 0;
}


struct mythread *mythread_init(void)
{
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
    mynode *t_mynode = (mynode *) malloc(sizeof(mynode));
    
    if(start)
    {
        runnable_q -> front = runnable_q -> front = (myqueue *) malloc(myqueue);
        runnable_q -> num = 0;
        sleeping_q -> front = sleeping_q -> front = (myqueue *) malloc(myqueue);
        sleeping_q -> num = 0;
        finished_q -> front = finished_q -> front = (myqueue *) malloc(myqueue);
        finished_q -> num = 0;
        start = 0;
    }
    
    mythread *t = mythread_init();
    if(t == NULL)
    {
        printf("\nCannot create new thread");
        return -1;
    }
    
    if(mythread_attr_t == NULL)
        t -> attr -> joinable = 1;          // Joinable by default
        
    add_runnable_q(t, runnable_q);              // Add thread to RUNNABLE QUEUE
    t -> state = RUNNABLE;
    
    if(makecontext(t -> context, (void *) wrapper_function, 2, start_routine, arg) == -1)
    {
        printf("\nCannot switch to newly created thread");
        t -> state = KILLED;
        return -1;
    }
    t_mynode -> mytcb = t;
    t_mynode -> mythread_queue_next = NULL;
    mythread_id = t -> tid;
    
    cur_mythread -> status = RUNNABLE;
    add_runnable_q(cur_mythread, runnable_q);
    cur_mythread = t;
    t -> status = RUNNING;
    swapcontext(runnable_q -> front -> mytcb -> context, cur_mythread -> mytcb -> context);
    
    return 0;
}


void add_runnable(struct mythread *thread, myqueue *queue)
{
    mythread_mutex_lock(& queue -> lock);
    
    queue = (myqueue *) malloc(sizeof(myqueue));
    
    if(queue -> num == 0)           //  Queue is empty
    {
        queue -> front -> mythread_queue_next = NULL;
        queue -> front = thread;
        queue -> num++;
        queue -> front = queue -> rear;
    }
        
    else
        queue -> rear -> mytcb = thread;
        
    queue -> num++;
    mythread_mutex_unlock(& queue -> lock);
}


void mythread_exit(void *retval)
{
    cur_mythread -> retval = retval;
    cur_mythread -> status = KILLED;
    add_runnable(cur_mythread, finished_q);
    next_tid--;
    
    cur_mythread = get_thread(runnable_q);
    cur_mythread -> status = RUNNING;
    
    swapcontext(finished_q -> tail -> context, cur_mythread -> context);
}


int mythread_yield()
{
    if(context_switch() == -1)
    {
        printf("\nCannot yield");
        return -1;
    }
    
    return 0;
}


int context_switch()
{
    if(runnable_q -> num == 0)
    {
        printf("No threads available to yield");
        return -1;
    }
    
    add_runnable(cur_mythread, runnable_q);
    cur_mythread -> state = RUNNABLE;
    cur_mythread = get_thread(runnable_q);
    cur_mythread -> state = RUNNING;
    
    swappcontext(runnable_q -> rear -> mytcb -> context, cur_mythread -> context);
    
    return 0;
}


mythread *get_thread(myqueue *queue)
{
    mythread *temp = queue -> front;
    queue -> front = queue -> front -> mythread_queue_next;
    queue -> num--;
    
    return temp;
}


int mythread_join(int mythread_id, void **retval)
{
    mynode *temp;
    
    while(! (temp = inFinishedQueue(mythread_id)))
        mythread_yield();
        
    if(retval != NULL)
        *retval = temp -> mytcb -> retval;
    finished_q -> num--;
    remove_node(temp);
    
    return 0;
}


void remove_node(myqueue *node)
{
    free(node -> tcb -> context -> uc_stack.ss);
    free(node -> tcb -> context);
    free(node);
}


















