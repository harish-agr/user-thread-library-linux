


enum thread_state {SLEEPING, RUNNABLE, RUNNING};

struct thread {
    uint sz;                    //  Size of thread memory (bytes)
    enum thread_state state;    //  Thread state
    volatile int tid;           //  Thread ID
    int killed;                 //  If non-zero, have been killed
    char name[16];              //  Thread name (debugging)
};

