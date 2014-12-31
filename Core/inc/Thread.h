////////////////////////////////////////////////////////////
/** @file Thread.h
 *  @ingroup Thread
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 06/04/2013 - 02/05/2014
 *
 *  Defines the Thread class.
 *
**/
////////////////////////////////////////////////////////////
#ifndef APRO_THREAD_H
#define APRO_THREAD_H

#include "Platform.h"
#include "List.h"
#include "SString.h"
#include "EventEmitter.h"
#include "ThreadMutexI.h"
#include "Time.h"

namespace APro
{
    ////////////////////////////////////////////////////////////
    /** @class Thread
     *  @ingroup Thread
     *  @brief Defines a thread.
     *
     *  A Thread is a task containing instructions. They aims to
     *  be executed in parallel, but as there aren't enough processor
     *  unit to do that, they will be executed using a task sheduler,
     *  wich is Operating System dependent.
     *
     *  The Engine always have a main thread. You cannot exec this
     *  thread or cannot stop or cancel it.
     *
     *  There are two ways to create it :
     *  - Construct a Thread object and setting a callback function
     *  that will be called during the exec function.
     *  - Inherits from it and override the exec() function.
     *
     *  @note This class creates 3 mutexes without asking for
     *  ThreadManager. As no id are provided for these mutexes, you
     *  should never use them as normal mutexes.
     *  Users mutexes should always be created thanks to ThreadManager.
     *
     *  Thread is started using the Thread::start() function. The
     *  Thread::run() function is called by the main thread routine,
     *  so don't call it yourself or it will cause undefined behaviours.
    **/
    ////////////////////////////////////////////////////////////
    class APRO_DLL Thread : public NonCopyable,
                            public EventEmitter
    {

    protected:

        /** @brief A mutex with a boolean. */
        struct MutexBool
        {
            ThreadMutexI mutex;///< Mutex for the boolean.
            bool         value;///< Value of the boolean.
        };

        typedef void (*pfunc) (void*);///< The type of function to callback.
        typedef void* apro_thread_t;  ///< Standard type for threads.

        String        m_name;      ///< Name of the thread.
        apro_thread_t m_thread;    ///< Pointer Handle to the thread.

        MutexBool     m_started;   ///< Thread is started ?
        MutexBool     m_finished  ;///< Thread is finished ?
        MutexBool     m_terminated;///< Thread terminated ?

        pfunc         m_callback;  ///< User Callback function.
        void*         m_userdata;  ///< Argument to the callback.

    private:

        ////////////////////////////////////////////////////////////
        /** @brief Function passed to pthread.
         *
         *  It always have this thread as data. If a user callback is
         *  setted, it will be called after the exec function.
         *
         *  As this function is the main function of the thread, it
         *  return NULL by default.
         *
         *  This function primarly call Thread::run(). Then ::run()
         *  call first Thread::exec() then the callback, if there is
         *  one. Then it returns and the _thread_func returns also.
        **/
        ////////////////////////////////////////////////////////////
        static void* _thread_func(void* _caller);


    public:

        ////////////////////////////////////////////////////////////
        /** @brief Construct a Thread.
         *
         *  @note This function shouldn't be called.
        **/
        ////////////////////////////////////////////////////////////
        Thread();

        ////////////////////////////////////////////////////////////
        /** @brief Constructs a Thread with a name.
         *  @param name : Name of the thread.
        **/
        ////////////////////////////////////////////////////////////
        Thread(const String& name);

        ////////////////////////////////////////////////////////////
        /** @brief Destructs the Thread.
         *
         *  @note If Thread is still running when object must be destroyed,
         *  Thread::terminate() is called and undefined behaviour might
         *  take place.
        **/
        ////////////////////////////////////////////////////////////
        virtual ~Thread();

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Returns the name of the Thread.
        **/
        ////////////////////////////////////////////////////////////
        const String& getName() const;

        ////////////////////////////////////////////////////////////
        /** @brief Set the callback to call during the Running process.
         *
         *  @param ptr : Callback pointer.
         *  @param userdata : Data to use as argument. Management of data
         *  is let to you. Invalidating given adress may have undefined
         *  behaviours.
        **/
        ////////////////////////////////////////////////////////////
        void setCallback(pfunc ptr, void* userdata);

        ////////////////////////////////////////////////////////////
        /** @brief Reset callback to null.
         *
         *  @note This doesn't deallocate user data passed in
         *  Thread::setCallback.
        **/
        ////////////////////////////////////////////////////////////
        void resetCallback();

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Starts the Thread.
         *  @note Also creates it and call main routine. A call to
         *  Thread::start() don't send a ThreadSartedEvent. This is
         *  Thread::run() that send start and finish event, and that
         *  modify the m_started and m_finished value.
        **/
        ////////////////////////////////////////////////////////////
        void start();

        ////////////////////////////////////////////////////////////
        /** @brief Runs this Thread procedure.
         *
         *  The running process is made of 5 steps :
         *  - Send event ThreadStartedEvent.
         *  - Calling the Thread::exec() function.
         *  - Calling the callback function if it exists.
         *  - Send event ThreadFinishedEvent.
         *  - Return.
         *
         *  @warning Don't call this function ! It will be done by
         *  Thread::start().
        **/
        ////////////////////////////////////////////////////////////
        void run();

        ////////////////////////////////////////////////////////////
        /** @brief Wait for this thread to finish.
        **/
        ////////////////////////////////////////////////////////////
        void join();

        ////////////////////////////////////////////////////////////
        /** @brief Wait for this thread to finish.
         *  @param timeout : Maximum time to wait for the joined thread.
        **/
        ////////////////////////////////////////////////////////////
        void join(const Time& timeout);

        ////////////////////////////////////////////////////////////
        /** @brief Terminates the thread.
         *
         *  @note This function is not safe. It forces the thread to
         *  terminate without freeing any memory allocated, so it can
         *  causes memory leaks and undefined behaviours.
        **/
        ////////////////////////////////////////////////////////////
        void terminate();

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Tell if thread is running.
         *
         *  Thread is running if the Thread::run() function has been
         *  called and not finished.
        **/
        ////////////////////////////////////////////////////////////
        bool isRunning() const;

        ////////////////////////////////////////////////////////////
        /** @brief Tell if thread is finished.
         *
         *  Thread is finished if it has been either finished normally
         *  or terminated.
        **/
        ////////////////////////////////////////////////////////////
        bool isFinished() const;

        ////////////////////////////////////////////////////////////
        /** @brief Tell if thread is terminated.
         *
         *  Thread is teminated if Thread::terminate() has been called.
        **/
        ////////////////////////////////////////////////////////////
        bool isTerminated() const;

    protected:

        ////////////////////////////////////////////////////////////
        /** @brief Main procedure of this thread.
         *
         *  You can overload it to do here whatever you want. You can
         *  use 'return' instruction as a thread exit point, as it will
         *  return to Thread::run() function.
        **/
        ////////////////////////////////////////////////////////////
        virtual void exec();

    public:

        /////////////////////////////////////////////////////////////
        /** @brief Create an event recognized by his hash type.
         *  @see EventEmitter::createEvent
        **/
        /////////////////////////////////////////////////////////////
        EventLocalPtr createEvent(const HashType& e_type) const;
    };

    /** @brief Thread is started. Send at the beginning of the 'run' function. */
    APRO_DECLARE_EVENT_NOCONTENT(ThreadStartedEvent);

    /** @brief Thread is finished. Send at the end of the 'run' function. */
    APRO_DECLARE_EVENT_NOCONTENT(ThreadFinishedEvent);

    /** @brief Thread has been terminated suddenly. */
    APRO_DECLARE_EVENT_NOCONTENT(ThreadTerminatedEvent);

    typedef AutoPointer<Thread> ThreadPtr;
}

#endif // APRO_THREAD_H
