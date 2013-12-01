////////////////////////////////////////////////////////////
/** @file ThreadMutex.h
 *  @ingroup Thread
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 06/04/2013 - 01/12/2013
 *
 *  Defines the Mutex class and his implementation.
 *
**/
////////////////////////////////////////////////////////////
#ifndef APRO_MUTEX_H
#define APRO_MUTEX_H

#include "Platform.h"
#include "NonCopyable.h"
#include "EventEmitter.h"

namespace APro
{
    class ThreadCondition;

    ////////////////////////////////////////////////////////////
    /** @class ThreadMutex
     *  @ingroup Thread
     *  @brief Defines a mutex (MUTual EXclusion) object to avoid
     *  simultaeous access to memory.
     *
     *  Mutexs are also event emitters, wich can send some events :
     *  - MutexLockedEvent
     *  - MutexUnlockedEvent
     *
     *  @note ThreadMutex are identified with an unique id,
     *  given by the ThreadManager.
     *  @note Mutex should always be created thanks to the
     *  ThreadManager using createMutex(). In rare excepted cases,
     *  you can create internal mutexs usgin the default constructor,
     *  as done in Atomic and Thread. This method simplify the creation
     *  of mutexs at the beginning of the program, where we are not sure
     *  that ThreadManager has been created.
     *
     *  @note On Compilations where option '--no-thread' is setted,
     *  every functions are stubs.
     *
     *  @see http://en.wikipedia.org/wiki/Mutual_exclusion for more
     *  on mutexs.
    **/
    ////////////////////////////////////////////////////////////
    class APRO_DLL ThreadMutex : public NonCopyable,
                                 public EventEmitter
    {
        APRO_DECLARE_SHAREDPOINTER_CLASS_TYPEDEF(ThreadMutex)

    public:

        friend class ThreadCondition;

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Constructs an empty mutex.
        **/
        ////////////////////////////////////////////////////////////
        ThreadMutex();

        ////////////////////////////////////////////////////////////
        /** @brief Constructs a mutex with an Id.
         *  @note The Id is provided by the ThreadManager and ensure
         *  the Mutex is unique.
        **/
        ////////////////////////////////////////////////////////////
        ThreadMutex(Id id);

        ////////////////////////////////////////////////////////////
        /** @brief Destructs the mutex.
        **/
        ////////////////////////////////////////////////////////////
        ~ThreadMutex();

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Returns the Id of this mutex.
         *  @return Id of the mutex.
        **/
        ////////////////////////////////////////////////////////////
        Id getId() const { return m_id; }

        ////////////////////////////////////////////////////////////
        /** @brief Returns locked state of the mutex.
         *  @return Is the mutex locked ?
        **/
        ////////////////////////////////////////////////////////////
        bool isLocked() const { return m_locked; }

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

    public:

        /////////////////////////////////////////////////////////////
        /** @brief Create an event recognized by his hash type.
         *  @see EventEmitter::createEvent
        **/
        /////////////////////////////////////////////////////////////
        EventPtr createEvent(const HashType& e_type) const;

    protected:

        typedef void* apro_mutex_t;

        Id   m_id;            ///< Unique ID given by ThreadManager.
        apro_mutex_t m_mutex; ///< Pthread data.
        bool m_locked;        ///< Tell if mutex is curently locked.
    };

    typedef AutoPointer<ThreadMutex> ThreadMutexPtr;

    /** @brief Event send when Mutex is locked. */
    APRO_DECLARE_EVENT_NOCONTENT(MutexLockedEvent);

    /** @brief Event send when Mutex is unlocked. */
    APRO_DECLARE_EVENT_NOCONTENT(MutexUnlockedEvent);

}

#endif // APRO_MUTEX_H
