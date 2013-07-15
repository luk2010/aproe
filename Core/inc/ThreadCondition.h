////////////////////////////////////////////////////////////
/** @file ThreadCondition.h
 *  @ingroup Thread
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 06/04/2013
 *
 *  Defines the Condition class and his implementation.
 *
**/
////////////////////////////////////////////////////////////
#ifndef APRO_THREADCONDITION_H
#define APRO_THREADCONDITION_H

#include "Implementable.h"
#include "Implementation.h"
#include "ThreadMutex.h"

namespace APro
{
    ////////////////////////////////////////////////////////////
    /** @class ThreadConditionImplementation
     *  @ingroup Thread
     *  @brief Defines the implementation interface of
     *  ThreadCondition.
    **/
    ////////////////////////////////////////////////////////////
    class APRO_DLL ThreadConditionImplementation : public Implementation
    {
        APRO_DECLARE_SHAREDPOINTER_CLASS_TYPEDEF(ThreadConditionImplementation)

    public:

        ////////////////////////////////////////////////////////////
        /** Give the name of the class implemented.
         *  @see Implementation::getClassImplementation
        **/
        ////////////////////////////////////////////////////////////
        const String getClassImplementation() const
        {
            return String("APro::ThreadCondition");
        }

    public:

        ////////////////////////////////////////////////////////////
        /** Default constructor.
        **/
        ////////////////////////////////////////////////////////////
        ThreadConditionImplementation()
        {

        }

        ////////////////////////////////////////////////////////////
        /** Virtual destructor.
        **/
        ////////////////////////////////////////////////////////////
        virtual ~ThreadConditionImplementation()
        {

        }

    public:

        ////////////////////////////////////////////////////////////
        /** Create condition object.
         *  @see Implementation::init
         *  @return Is object created ?
        **/
        ////////////////////////////////////////////////////////////
        virtual bool init() = 0;

        ////////////////////////////////////////////////////////////
        /** Destroy condition object.
         *  @see Implementation::deinit
        **/
        ////////////////////////////////////////////////////////////
        virtual void deinit() = 0;

    public:

        ////////////////////////////////////////////////////////////
        /** Unblock one thread blocked with this condition.
        **/
        ////////////////////////////////////////////////////////////
        virtual void signal() = 0;

        ////////////////////////////////////////////////////////////
        /** Unblock every thread blocked with this condition.
        **/
        ////////////////////////////////////////////////////////////
        virtual void signalAll() = 0;

        ////////////////////////////////////////////////////////////
        /** Block the calling thread while the condition isn't signaled
         *  by another thread.
         *  @param muteximp : The mutex to wait for.
        **/
        ////////////////////////////////////////////////////////////
        virtual void wait(ThreadMutexImplementation* muteximp) = 0;

        ////////////////////////////////////////////////////////////
        /** Block the calling thread while the condition isn't signaled
         *  by another thread. If timeout is depassed, condition is
         *  unblocked automaticly.
         *  @param muteximp : Mutex to wait for.
         *  @param timeout : Time not to depass.
        **/
        ////////////////////////////////////////////////////////////
        virtual void waitTimeout(ThreadMutexImplementation* muteximp, int timeout) = 0;
    };

    ////////////////////////////////////////////////////////////
    /** @class ThreadCondition
     *  @ingroup Thread
     *  @brief A Condition block the thread while another thread
     *  signals that the condition can be unblocked.
     *  @details It is associated to a mutex, and can be used
     *  to wait for mutex to be to be unlocked.
    **/
    ////////////////////////////////////////////////////////////
    class APRO_DLL ThreadCondition : public Implementable<ThreadConditionImplementation>
    {
        APRO_DECLARE_SHAREDPOINTER_CLASS_TYPEDEF(ThreadCondition)

    public:

        ////////////////////////////////////////////////////////////
        /** Default constructor.
        **/
        ////////////////////////////////////////////////////////////
        ThreadCondition();

        ////////////////////////////////////////////////////////////
        /** Contructor with Id.
         *  @note The id is given by the Thread Manager.
         *  @param id : Id of the condition.
        **/
        ////////////////////////////////////////////////////////////
        ThreadCondition(Id id);

        ////////////////////////////////////////////////////////////
        /** Destructor.
        **/
        ////////////////////////////////////////////////////////////
        ~ThreadCondition();

    public:

        ////////////////////////////////////////////////////////////
        /** Unblock one thread blocked with this condition.
        **/
        ////////////////////////////////////////////////////////////
        void signal();

        ////////////////////////////////////////////////////////////
        /** Unblock every thread blocked with this condition.
        **/
        ////////////////////////////////////////////////////////////
        void signalAll();

        ////////////////////////////////////////////////////////////
        /** Block the calling thread while the condition isn't signaled
         *  by another thread.
         *  @note If timeout is negativ, this function call the non-time
         *  wait.
         *  @param mid : Id of the Mutex.
         *  @param timeout : Time before cancel of condition.
        **/
        ////////////////////////////////////////////////////////////
        void wait(Id mid, int timeout = -1);

        ////////////////////////////////////////////////////////////
        /** Block the calling thread while the condition isn't signaled
         *  by another thread.
         *  @note If timeout is negativ, this function call the non-time
         *  wait.
         *  @param mutex : Mutex to associate.
         *  @param timeout : Time before cancel of condition.
        **/
        ////////////////////////////////////////////////////////////
        void wait(ThreadMutex::ptr mutex, int timeout = -1);

    public:

        ////////////////////////////////////////////////////////////
        /** Give the id of this condition.
         *  @note This has nothing to do with pthread's ID or anything
         *  else.
         *  @return The ID.
        **/
        ////////////////////////////////////////////////////////////
        Id getId() const;

        ////////////////////////////////////////////////////////////
        /** Init implementation.
         *  @see Implementable::initImplementation
        **/
        ////////////////////////////////////////////////////////////
        void initImplementation();

    protected:

        Id m_id;///< ID of the condition
    };
}

#endif // APRO_THREADCONDITION_H
