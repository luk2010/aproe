////////////////////////////////////////////////////////////
/** @file ThreadCondition.h
 *  @ingroup Thread
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 06/04/2013 - 01/12/2013
 *
 *  Defines the Condition class.
 *
**/
////////////////////////////////////////////////////////////
#ifndef APRO_THREADCONDITION_H
#define APRO_THREADCONDITION_H

#include "Platform.h"
#include "NonCopyable.h"
#include "ThreadMutex.h"
#include "Time.h"

namespace APro
{
    ////////////////////////////////////////////////////////////
    /** @class ThreadCondition
     *  @ingroup Thread
     *  @brief A Condition block the thread while another thread
     *  signals this condition.
     *
     *  When a thread must wait for a condition, he can be idling
     *  while the other thread that have the 'lock' unlock this
     *  condition by signaling it and unblock the waiting thread.
     *
     *  @note Waiting a condition always make thread idling.
    **/
    ////////////////////////////////////////////////////////////
    class APRO_DLL ThreadCondition : public NonCopyable
    {

    public:

        typedef enum _WaitError
        {
            WE_OK,       ///< Returned by wait() when condition is signaled without error.
            WE_TIMEOUT,  ///< Returned by wait() when condition is cancelled due to time out.
            WE_EINVALUE  ///< Returned by wait() when condition is cancelled due to an error with one of the argues given.
        } WaitError;

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Constructs an empty condition.
        **/
        ////////////////////////////////////////////////////////////
        ThreadCondition();

        ////////////////////////////////////////////////////////////
        /** @brief Constructs a condition with given id.
         *  @note The id is given by the Thread Manager.
         *  @param id : Id of the condition.
        **/
        ////////////////////////////////////////////////////////////
        ThreadCondition(Id id);

        ////////////////////////////////////////////////////////////
        /** @brief Destructs the condition.
        **/
        ////////////////////////////////////////////////////////////
        ~ThreadCondition();

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Unblock one thread blocked with this condition.
         *
         *  @note If more than one thread is blocked on a condition
         *  variable, then unblocking them will be done in the
         *  sheduling order. First blocked will be first unblocked.
        **/
        ////////////////////////////////////////////////////////////
        void signal();

        ////////////////////////////////////////////////////////////
        /** @brief Unblock every thread blocked with this condition.
         *
         *  @note If more than one thread is blocked on a condition
         *  variable, then unblocking them will be done in the
         *  sheduling order. First blocked will be first unblocked.
        **/
        ////////////////////////////////////////////////////////////
        void signalAll();

        ////////////////////////////////////////////////////////////
        /** @brief Block the calling thread while the condition isn't
         *  signaled by another thread.
         *
         *  @note If timeout is invalid, no time-out is applied.
         *
         *  @param mid : Id of the Mutex.
         *  @param timeout : Time before cancel of condition.
         *
         *  @return WE_OK if everything is okay, else an error code.
        **/
        ////////////////////////////////////////////////////////////
        WaitError wait(Id mid, const Time& timeout = Time::Invalid);

        ////////////////////////////////////////////////////////////
        /** @brief Block the calling thread while the condition isn't
         *  signaled by another thread.
         *
         *  @note If timeout is invalid, no time-out is applied.
         *
         *  @param mutex : Mutex to associate.
         *  @param timeout : Time before cancel of condition.
         *
         *  @return WE_OK if everything is okay, else an error code.
        **/
        ////////////////////////////////////////////////////////////
        WaitError wait(ThreadMutexPtr& mutex, const Time& timeout = Time::Invalid);

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Give the id of this condition.
        **/
        ////////////////////////////////////////////////////////////
        Id getId() const { return m_id; }

    protected:

        typedef void* apro_condition_t;

        apro_condition_t condition; ///< Pointer to the condition data holded by pthread.
        Id m_id;                    ///< ID of this condition object.
    };

    typedef AutoPointer<ThreadCondition> ThreadConditionPtr;
}

#endif // APRO_THREADCONDITION_H
