/*
    Posix Thread Mutex Implementation
*/
#ifndef POSIXTHREADMUTEX_H
#define POSIXTHREADMUTEX_H

#include <ThreadMutex.h>
#include <pthread.h>
using namespace APro;

class PosixThreadMutex : public ThreadMutexImplementation
{
public:

    PosixThreadMutex();
    ~PosixThreadMutex();

public:

    const String getImplementationName() const;
    bool init();
    void deinit();
    Implementation::ptr clone() const;
    void destroy(Implementation* impl);

public:

    void lock();
    bool tryLock();
    void unlock();

    pthread_mutex_t* pthread_mutex();

private:

    pthread_mutex_t mutex;
};

#endif // POSIXTHREADMUTEX_H
