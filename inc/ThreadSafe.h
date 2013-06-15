////////////////////////////////////////////////////////////
/** @file ThreadSafe.h
 *  @ingroup Thread
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 25/04/2013
 *
 *  Defines the ThreadSafe class.
 *
**/
////////////////////////////////////////////////////////////
#ifndef APRO_THREADSAFE_H
#define APRO_THREADSAFE_H

#include "Platform.h"
#include "SharedPointer.h"
//#include "ThreadMutex.h"

namespace APro
{
    class ThreadMutex;
    typedef SharedPointer<ThreadMutex> ThreadMutexPtr;

    ////////////////////////////////////////////////////////////
    /** @class ThreadSafe
     *  @brief Enables a safe mutex lock and unlock for classes.
     *  @details Inherits from this class enables yours to have a
     *  ready-to-use mutex to protect data overwritting from threads.
     *  You can use the easy functions safelock and safeunlock to
     *  lock/unlock the mutex.
     *  @note The mutex is created only when the ThreadManager is created
     *  AND when one of the functions safelock / safeunlock is called.
    **/
    ////////////////////////////////////////////////////////////
    class ThreadSafe
    {
    public:
        ////////////////////////////////////////////////////////////
        /** Default constructor.
        **/
        ////////////////////////////////////////////////////////////
        ThreadSafe();

        ////////////////////////////////////////////////////////////
        /** Destructor.
        **/
        ////////////////////////////////////////////////////////////
        ~ThreadSafe();

    public:

        ////////////////////////////////////////////////////////////
        /** Lock safely the mutex.
         *  @note Performs creation test before it is created. Create it if
         *  not yet.
        **/
        ////////////////////////////////////////////////////////////
        void safelock();

        ////////////////////////////////////////////////////////////
        /** Unlock safely the mutex.
         *  @note Performs creation test before it is created. Create it if
         *  not yet.
        **/
        ////////////////////////////////////////////////////////////
        void safeunlock();

    public:

        ////////////////////////////////////////////////////////////
        /** Return the internal mutex.
         *  @return Pointer to the mutex.
        **/
        ////////////////////////////////////////////////////////////
        ThreadMutex* getMutex();

        ////////////////////////////////////////////////////////////
        /** Return the internal mutex.
         *  @return Pointer to the mutex.
        **/
        ////////////////////////////////////////////////////////////
        const ThreadMutex* getMutex() const;

    public:

        ////////////////////////////////////////////////////////////
        /** Tell if the mutex has been created.
        **/
        ////////////////////////////////////////////////////////////
        bool isMutexCreated() const;

        ////////////////////////////////////////////////////////////
        /** Tell if the mutex is currently in creation.
        **/
        ////////////////////////////////////////////////////////////
        bool isMutexCreating() const;

    private:

        ////////////////////////////////////////////////////////////
        /** Creates the mutex.
         *  @internal
        **/
        ////////////////////////////////////////////////////////////
        void createmutex();

    private:

        ThreadMutex* mutexptr;///< Safe-pointer to the mutex.
        bool mutexcreated;///< Tell if mutex is created.
        bool mutexcreating;///< Tell if mutex is creating.
    };

    #define APRO_THREADSAFE_AUTOLOCK ThreadSafe::safelock(); THREADMUTEXAUTOLOCK(ThreadSafe::getMutex());
}

#endif // APRO_THREADSAFE_H
