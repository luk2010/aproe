/*
    Posix Thread Condition Implementation
*/
#include "PosixThreadCondition.h"
#include "PosixThreadMutex.h"
#include <sys/time.h>
using namespace APro;

PosixThreadCondition::PosixThreadCondition()
    : condition(PTHREAD_COND_INITIALIZER)
{

}

PosixThreadCondition::~PosixThreadCondition()
{

}

const String PosixThreadCondition::getImplementationName() const
{
    return String("Posix Condition Implementation");
}

bool PosixThreadCondition::init()
{
    return true;
}

void PosixThreadCondition::deinit()
{

}

Implementation::ptr PosixThreadCondition::clone() const
{
    Implementation::ptr new_condition = Implementation::ptr(AProNew3(PosixThreadCondition));
    new_condition.setDeletionMethod(DeletionMethod::Delete3);
    return new_condition;
}

void PosixThreadCondition::destroy(Implementation* impl)
{
    if(impl)
    {
        PosixThreadCondition* pimp = reinterpret_cast<PosixThreadCondition*>(impl);
        if(pimp)
            AProDelete3(pimp);
    }
}

void PosixThreadCondition::signal()
{
    pthread_cond_signal(&condition);
}

void PosixThreadCondition::signalAll()
{
    pthread_cond_broadcast(&condition);
}

void PosixThreadCondition::wait(ThreadMutexImplementation* muteximp)
{
    if(muteximp)
    {
        PosixThreadMutex* pmutex = reinterpret_cast<PosixThreadMutex*>(muteximp);
        pthread_cond_wait(&condition, pmutex->pthread_mutex());
    }
}

void PosixThreadCondition::waitTimeout(ThreadMutexImplementation* muteximp, int timeout)
{
    if(muteximp)
    {
        PosixThreadMutex* pmutex = reinterpret_cast<PosixThreadMutex*>(muteximp);

        timeval tv;
        gettimeofday(&tv, NULL);

        timespec ti;
        ti.tv_nsec = (tv.tv_usec + (timeout % 1000)) * 1000000;
        ti.tv_sec = tv.tv_sec + (timeout / 1000) + (ti.tv_nsec / 1000000000);
        ti.tv_nsec %= 1000000000;

        pthread_cond_timedwait(&condition, pmutex->pthread_mutex(), &ti);
    }
}


