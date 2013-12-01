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
#include "ThreadMutex.h"

namespace APro
{
    ////////////////////////////////////////////////////////////
    /** @class ThreadSafe
     *  @brief Enables a safe mutex lock and unlock for classes.
     *
     *  Inherits from this class enables yours to have a
     *  ready-to-use mutex to protect data overwritting from threads.
     *  You can use the easy functions safelock and safeunlock to
     *  lock/unlock the mutex.
     *
     *  @note The mutex is created in the safelock function if it
     *  wasn't done in the constructor.
    **/
    ////////////////////////////////////////////////////////////
    class ThreadSafe
    {
    public:
        ////////////////////////////////////////////////////////////
        /** @brief Default constructor.
        **/
        ////////////////////////////////////////////////////////////
        ThreadSafe();

        ////////////////////////////////////////////////////////////
        /** @brief Destructor.
        **/
        ////////////////////////////////////////////////////////////
        ~ThreadSafe();

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Lock safely the mutex.
         *
         *  The mutex is locked and created if it isn't yet.
         *
         *  @throw CustomException if mutex cannot be created.
        **/
        ////////////////////////////////////////////////////////////
        void safelock();

        ////////////////////////////////////////////////////////////
        /** @brief Unlock safely the mutex.
         *
         *  The mutex is unlocked and created if it isn't yet.
        **/
        ////////////////////////////////////////////////////////////
        void safeunlock();

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Return the internal mutex.
         *
         *  The pointer returned musn't be deleted.
        **/
        ////////////////////////////////////////////////////////////
        ThreadMutex* getMutex();

        ////////////////////////////////////////////////////////////
        /** @brief Return the internal mutex.
         *
         *  The pointer returned musn't be deleted.
        **/
        ////////////////////////////////////////////////////////////
        const ThreadMutex* getMutex() const;

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Tell if the mutex has been created.
        **/
        ////////////////////////////////////////////////////////////
        bool isMutexCreated() const;

        ////////////////////////////////////////////////////////////
        /** @brief Tell if the mutex is currently in creation.
        **/
        ////////////////////////////////////////////////////////////
        bool isMutexCreating() const;

    private:

        ////////////////////////////////////////////////////////////
        /** @brief Creates the mutex.
         *  @internal
        **/
        ////////////////////////////////////////////////////////////
        void createmutex();

    private:

        ThreadMutexPtr mutexptr;///< Pointer to the mutex.
        bool mutexcreated;      ///< Tell if mutex is created.
        bool mutexcreating;     ///< Tell if mutex is creating.
    };

    #define APRO_THREADSAFE_AUTOLOCK ThreadSafe::safelock(); THREADMUTEXAUTOLOCK(ThreadSafe::getMutex());
}

#endif // APRO_THREADSAFE_H
