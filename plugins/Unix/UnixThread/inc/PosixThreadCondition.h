/*
    Posix Thread Condition Implementation
*/
#ifndef POSIXTHREADCONDITION_H
#define POSIXTHREADCONDITION_H

#include <ThreadCondition.h>
#include <pthread.h>
using namespace APro;

class PosixThreadCondition : public ThreadConditionImplementation
{
public:

    PosixThreadCondition();
    ~PosixThreadCondition();

public:

    const String getImplementationName() const;
    bool init();
    void deinit();
    Implementation::ptr clone() const;
    void destroy(Implementation* impl);

public:

    void signal();
    void signalAll();
    void wait(ThreadMutexImplementation* muteximp);
    void waitTimeout(ThreadMutexImplementation* muteximp, int timeout);

private:

    pthread_cond_t condition;
};

#endif // POSIXTHREADCONDITION_H
