/*
    Posix Thread Mutex Implementation
*/
#include "PosixThreadMutex.h"
using namespace APro;

PosixThreadMutex::PosixThreadMutex()
    : mutex(PTHREAD_MUTEX_INITIALIZER)
{

}

PosixThreadMutex::~PosixThreadMutex()
{

}

const String PosixThreadMutex::getImplementationName() const
{
    return String("Posix Mutex Implementation");
}

bool PosixThreadMutex::init()
{
    return true;
}

void PosixThreadMutex::deinit()
{

}

Implementation::ptr PosixThreadMutex::clone() const
{
    Implementation::ptr new_mutex = Implementation::ptr(AProNew3(PosixThreadMutex));
    new_mutex.setDeletionMethod(DeletionMethod::Delete3);
    return new_mutex;
}

void PosixThreadMutex::destroy(Implementation* impl)
{
    if(impl)
    {
        PosixThreadMutex* pimp = reinterpret_cast<PosixThreadMutex*>(impl);
        if(pimp)
            AProDelete3(pimp);
    }
}

void PosixThreadMutex::lock()
{
    pthread_mutex_lock(&mutex);
}

bool PosixThreadMutex::tryLock()
{
    return (pthread_mutex_trylock(&mutex) == 0);
}

void PosixThreadMutex::unlock()
{
    pthread_mutex_unlock(&mutex);
}

pthread_mutex_t* PosixThreadMutex::pthread_mutex()
{
    return &mutex;
}
