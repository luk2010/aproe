/*
    Posix Thread Implementation.
*/
#ifndef POSIXTHREAD_H
#define POSIXTHREAD_H

#include <Thread.h>
#include <pthread.h>
using namespace APro;

class PosixThread : public ThreadImplementation
{
public:

    PosixThread();
    ~PosixThread();

public:

    const String getImplementationName() const;

    Implementation::ptr clone() const;
    void destroy(Implementation* impl);

public:

    bool create_thread(void* pdata);
    void join_thread();
    void exit_thread();
    void terminate_thread();

    static void* startRoutine(void* userdata);

private:

    typedef struct data_thread
    {
        void* parent_thread;
        PosixThread* implementation;
    } data_thread_t;

    pthread_t thread_id;
    data_thread_t data;
};

#endif // POSIXTHREAD_H
