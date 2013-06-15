////////////////////////////////////////////////////////////
/** @file ThreadMutex.h
 *  @ingroup Thread
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 06/04/2013
 *
 *  Defines the Mutex class and his implementation.
 *
**/
////////////////////////////////////////////////////////////
#ifndef APRO_MUTEX_H
#define APRO_MUTEX_H

#include "Implementation.h"
#include "Implementable.h"

namespace APro
{
    ////////////////////////////////////////////////////////////
    /** @class ThreadMutexImplementation
     *  @ingroup Thread
     *  @brief Defines the implementation of class ThreadMutex.
    **/
    ////////////////////////////////////////////////////////////
    class APRO_DLL ThreadMutexImplementation : public Implementation
    {
        APRO_DECLARE_SHAREDPOINTER_CLASS_TYPEDEF(ThreadMutexImplementation)

    public:

        ////////////////////////////////////////////////////////////
        /** Give the name of the class implemented.
         *  @see Implementation::getClassImplementation
        **/
        ////////////////////////////////////////////////////////////
        const String getClassImplementation() const
        {
            return String("APro::ThreadMutex");
        }

    public:

        ////////////////////////////////////////////////////////////
        /** Default constructor.
        **/
        ////////////////////////////////////////////////////////////
        ThreadMutexImplementation()
        {

        }

        ////////////////////////////////////////////////////////////
        /** Virtual destructor.
        **/
        ////////////////////////////////////////////////////////////
        virtual ~ThreadMutexImplementation()
        {

        }

    public:

        ////////////////////////////////////////////////////////////
        /** Creates the mutex object.
         *  @see Implementation::init
         *  @return Mutex created ?
        **/
        ////////////////////////////////////////////////////////////
        virtual bool init() = 0;

        ////////////////////////////////////////////////////////////
        /** Destroy mutex object.
         *  @see Implementation::init
        **/
        ////////////////////////////////////////////////////////////
        virtual void deinit() = 0;

    public:

        ////////////////////////////////////////////////////////////
        /** Lock mutex.
        **/
        ////////////////////////////////////////////////////////////
        virtual void lock() = 0;

        ////////////////////////////////////////////////////////////
        /** Tell if mutex is lockable.
         *  @return lockable ?
        **/
        ////////////////////////////////////////////////////////////
        virtual bool tryLock() = 0;

        ////////////////////////////////////////////////////////////
        /** Unlock mutex.
        **/
        ////////////////////////////////////////////////////////////
        virtual void unlock() = 0;
    };

    ////////////////////////////////////////////////////////////
    /** @class ThreadMutex
     *  @ingroup Thread
     *  @brief Defines a mutex (MUTual EXclusion) object to avoid
     *  simultaeous access to memory.
     *  @note ThreadMutex are identified with an unique id,
     *  given by the ThreadManager. It has nothig to do with possible
     *  ID in Thread Implementation.
    **/
    ////////////////////////////////////////////////////////////
    class APRO_DLL ThreadMutex : public Implementable<ThreadMutexImplementation>
    {
        APRO_DECLARE_SHAREDPOINTER_CLASS_TYPEDEF(ThreadMutex)

    public:

        ////////////////////////////////////////////////////////////
        /** Default constructor.
         *  @note You should never use this one. It is provided
         *  to use function as AProNew or AProNew3.
        **/
        ////////////////////////////////////////////////////////////
        ThreadMutex();

        ////////////////////////////////////////////////////////////
        /** Constructor with Id.
         *  @note The Id is provided by the ThreadManager and ensure
         *  the Mutex is unique.
        **/
        ////////////////////////////////////////////////////////////
        ThreadMutex(Id id);

        ////////////////////////////////////////////////////////////
        /** Destructor.
        **/
        ////////////////////////////////////////////////////////////
        ~ThreadMutex();

    public:

        ////////////////////////////////////////////////////////////
        /** Returns the Id of this mutex.
         *  @return Id of the mutex.
        **/
        ////////////////////////////////////////////////////////////
        Id getId() const;

        ////////////////////////////////////////////////////////////
        /** Returns locked state of the mutex.
         *  @return Is the mutex locked ?
        **/
        ////////////////////////////////////////////////////////////
        bool isLocked() const;

    public:

        ////////////////////////////////////////////////////////////
        /** Lock the mutex.
        **/
        ////////////////////////////////////////////////////////////
        void lock();

        ////////////////////////////////////////////////////////////
        /** Try to lock the mutex.
         *  @return Mutex is lockable ?
        **/
        ////////////////////////////////////////////////////////////
        bool tryLock();

        ////////////////////////////////////////////////////////////
        /** Unlock the mutex.
        **/
        ////////////////////////////////////////////////////////////
        void unlock();

        ////////////////////////////////////////////////////////////
        /** Init implementation.
         *  @see Implementable::initImplementation
        **/
        ////////////////////////////////////////////////////////////
        void initImplementation();

    protected:

        Id   m_id;    ///< Unique ID given by ThreadManager.
        bool m_locked;///< Tell if mutex is curently locked.
    };
}

#endif // APRO_MUTEX_H
