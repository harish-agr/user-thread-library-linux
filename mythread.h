
#define mythreads_MAX 10
#define STACKSIZE 8192
#define unsigned int uint



enum mythread_state {EMBRYO, SLEEPING, RUNNABLE, RUNNING};



struct mythread {
    enum mythread_state state;  //  Thread state
    volatile int tid;           //  Thread ID
    int killed;                 //  If non-zero, have been killed
    char name[16];              //  Thread name (debugging)
    void *retval;               //  Return value to be passes to join() routine
    ucontext_t *context;        //  Context of the current thread
};



struct mythread_attr {
    int joinable;               //  Joinable if its 1
};
typedef mythread_attr mythread_attr_t;



struct mythread_queue_node {
    mythread *mytcb;
    struct mythread_queue_node *mythread_queue_next;
}mynode;



struct mythread_queue {
    int num;                    //  # of elements in queue
    struct mythread_mutex lock;
    mynode *front, *rear;
}myqueue;



struct mythread_mutex {
    int locked;                 //  Unlocked if its 1
    char name[16];              //  Thread holding the lock (debugging)
};
typedef struct mythread_mutex mythread_mutex_t;



struct mythread_mutexattr {
    int pshared;                //  Not really used
};
typedef mythread_mutexattr my_tread_mutexattr_t;



//  USER LEVEL THREAD FUNCTIONS

int                 mythread_create(int *mythread_id, const mythread_attr_t *attr, void (*start_routine) (void *), void *arg);
void                mythread_exit(void *retval);
int                 mythread_yield(void);
int                 mythread_join(int mythread_id, void **retval);
struct mythread*    mythread_init(void);



// USER LEVEL THREAD MUTEX FUNCTIONS

int     mythread_mutex_init(mythread_mutex_t *mutex, const my_tread_mutexattr_t *attr);
int     mythread_mutex_destroy(mythread_mutex_t *mutex);
int     mythread_mutex_lock(mythread_mutex_t *mutex);