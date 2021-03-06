////////////////////////////////////////////////////////////
/** @file ThreadMutex.h
 *  @ingroup Thread
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 06/04/2013 - 30/12/2014
 *
 *  @brief
 *  Defines the Mutex class.
 *
 *  @copyright
 *  Atlanti's Project Engine
 *  Copyright (C) 2012 - 2014  Atlanti's Corp
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
**/
////////////////////////////////////////////////////////////
#ifndef APRO_MUTEX_H
#define APRO_MUTEX_H

#include "Platform.h"
#include "NonCopyable.h"
#include "EventEmitter.h"
#include "ThreadMutexI.h"

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
     *  If mutex is created without id (id == 0), this seems the mutex
     *  is internal. Event Sending is so disabled to prevent multiple
     *  events creation.
     *
     *  @note ThreadMutex are identified with an unique id,
     *  given by the ThreadManager.
     *  @note Mutex should always be created thanks to the
     *  ThreadManager using createMutex(). If you need mutexs without
     *  event handling, you should use ThreadMutexI instead.
     *
     *  @note On Compilations where option '--no-thread' is setted,
     *  every functions are stubs.
     *
     *  @see http://en.wikipedia.org/wiki/Mutual_exclusion for more
     *  on mutexs.
    **/
    ////////////////////////////////////////////////////////////
    class APRO_DLL ThreadMutex : public IMutex,
                                 public EventEmitter
    {

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
        EventLocalPtr createEvent(const HashType& e_type) const;

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
