/*
    Posix Thread Implementation.
*/
#include <Console.h>

#include"PosixThread.h"

PosixThread::PosixThread()
{

}

PosixThread::~PosixThread()
{

}

const String PosixThread::getImplementationName() const
{
    return String("Posix Thread Implementation");
}

Implementation::ptr PosixThread::clone() const
{
    Implementation::ptr new_pthread = Implementation::ptr(AProNew3(PosixThread));
    new_pthread.setDeletionMethod(DeletionMethod::Delete3);
    return new_pthread;
}

void PosixThread::destroy(Implementation* impl)
{
    if(impl)
    {
        PosixThread* pimp = reinterpret_cast<PosixThread*>(impl);
        if(pimp)
            AProDelete3(pimp);
    }
}

bool PosixThread::create_thread(void* pdata)
{
    data.implementation = this;
    data.parent_thread = pdata;

    int ret = pthread_create(&thread_id, NULL, startRoutine, &data);
    if(ret)
    {
        Console::get() << "\n[PosixThread]{create_thread} Can't create thread !";
        return false;
    }

    return true;
}

void* PosixThread::startRoutine(void* userdata)
{
    /* Thread Entry Point */

    if(userdata)
    {
        data_thread_t* data = static_cast<data_thread_t*>(userdata);

        Thread* thread = static_cast<Thread*>(data->parent_thread);
        thread->exec();

        /* Si on atteint ce point c'est que la fonction n'a pas appele exit(). */
        data->implementation->exit();
    }

    return NULL;
}

void PosixThread::join_thread()
{
    pthread_join(thread_id, NULL);
}

void PosixThread::exit_thread()
{
    pthread_exit(0);
}

void PosixThread::terminate_thread()
{
    pthread_cancel(thread_id);
}


