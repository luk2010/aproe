////////////////////////////////////////////////////////////
/** @file ThreadMutexLockGuard.h
 *  @ingroup Thread
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 06/04/2013 - 22/03/2014
 *
 *  Defines the MutexLockGuard class.
 *
**/
////////////////////////////////////////////////////////////
#ifndef APRO_MUTEXLOCKGUARD_H
#define APRO_MUTEXLOCKGUARD_H

#include "Platform.h"
#include "ThreadMutexI.h"

namespace APro
{
    ////////////////////////////////////////////////////////////
    /** @class ThreadMutexLockGuard
     *  @ingroup Thread
     *  @brief Helper class to prevent deadlock. Instanciate it
     *  at the beginning of your locked zone in brackets.
     *  Example :
     *  @code
     *  {
     *     ThreadMutexLockGuard lockguard_variable(myMutex);
     *
     *     // Do some weird things.
     *  }
     *  @endcode
    **/
    ////////////////////////////////////////////////////////////
    class APRO_DLL ThreadMutexLockGuard : public NonCopyable
    {
    public:

        ////////////////////////////////////////////////////////////
        /** @brief Constructs the lockguard.
         *
         *  The mutex is locked during the process.
         *  @param mutex : Mutex to guard.
        **/
        ////////////////////////////////////////////////////////////
        ThreadMutexLockGuard(IMutex* mutex);

        ////////////////////////////////////////////////////////////
        /** @brief Destructs the lockguard.
         *
         *  The mutex is unlocked during the process.
        **/
        ////////////////////////////////////////////////////////////
        ~ThreadMutexLockGuard();

    private:

        IMutex* m_mutex;///< Mutex
    };

/// @brief Create a variable to lock a given mutex.
///
/// The name of the lockguard will be __mutex_guard__ with the line number
/// appended.
#define THREADMUTEXAUTOLOCK_I        CONCAT( __mutex_guard__, __LINE__ )
#define THREADMUTEXAUTOLOCK( mutex ) ThreadMutexLockGuard THREADMUTEXAUTOLOCK_I (&mutex)
}

#endif // APRO_MUTEXLOCKGUARD_H
