////////////////////////////////////////////////////////////
/** @file ThreadMutexI.h
 *  @ingroup Thread
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 22/03/2014
 *
 *  Defines the MutexI class.
 *
**/
////////////////////////////////////////////////////////////
#ifndef APRO_THREADMUTEXI_H
#define APRO_THREADMUTEXI_H

#include "Platform.h"
#include "NonCopyable.h"

namespace APro
{
    /** A mutex interface.
        @ingroup Thread
     */
    class IMutex : public NonCopyable
    {
    public:

        IMutex() {}
        virtual ~IMutex() {}

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Returns locked state of the mutex.
        **/
        ////////////////////////////////////////////////////////////
        virtual bool isLocked() const = 0;

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Lock the mutex.
         *
         *  This operation waits as the mutex can't be locked.
        **/
        ////////////////////////////////////////////////////////////
        virtual void lock() = 0;

        ////////////////////////////////////////////////////////////
        /** @brief Try to lock the mutex.
         *  @return Mutex is lockable ?
        **/
        ////////////////////////////////////////////////////////////
        virtual bool tryLock() = 0;

        ////////////////////////////////////////////////////////////
        /** @brief Unlock the mutex.
        **/
        ////////////////////////////////////////////////////////////
        virtual void unlock() = 0;
    };


    ////////////////////////////////////////////////////////////
    /** @class ThreadMutexI
     *  @ingroup Thread
     *  @brief Defines a mutex (MUTual EXclusion) object to avoid
     *  simultaeous access to memory.
     *
     *  These mutexs are internal (-I suffix). It means that their
     *  primary use is for Engine classes. These utexs doesn't send
     *  any event, are not managed by the ThreadManager and so can
     *  be created by anyone who wants quick mutexs without event
     *  system behind.
     *
     *  The need of these types of mutexs is simple : it allows events
     *  to have their own mutexs, without involving a paradoxal system
     *  where mutex send event wich create mutex wich send events...
     *
     *  @note This is the events used by ThreadSafe. You cannot listen
     *  to the mutexs involved in ThreadSafe as they aren't events
     *  emitters.
     *
     *  @note On Compilations where option '--no-thread' is setted,
     *  every functions are stubs.
     *
     *  @see http://en.wikipedia.org/wiki/Mutual_exclusion for more
     *  on mutexs.
    **/
    ////////////////////////////////////////////////////////////
    class ThreadMutexI : public IMutex
    {
    public:

        ////////////////////////////////////////////////////////////
        /** @brief Constructs an empty mutex.
        **/
        ////////////////////////////////////////////////////////////
        ThreadMutexI();

        ////////////////////////////////////////////////////////////
        /** @brief Destructs the mutex.
        **/
        ////////////////////////////////////////////////////////////
        ~ThreadMutexI();

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Returns locked state of the mutex.
        **/
        ////////////////////////////////////////////////////////////
        bool isLocked() const;

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Lock the mutex.
         *
         *  This operation waits as the mutex can't be locked.
        **/
        ////////////////////////////////////////////////////////////
        void lock();

        ////////////////////////////////////////////////////////////
        /** @brief Try to lock the mutex.
         *  @return Mutex is lockable ?
        **/
        ////////////////////////////////////////////////////////////
        bool tryLock();

        ////////////////////////////////////////////////////////////
        /** @brief Unlock the mutex.
        **/
        ////////////////////////////////////////////////////////////
        void unlock();

    protected:

        typedef void* apro_mutex_t;

        apro_mutex_t m_mutex; ///< Pthread data.
        bool         m_locked;///< Tell if mutex is curently locked.
    };
}

#endif // APRO_THREADMUTEXI_H
