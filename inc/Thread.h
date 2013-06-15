////////////////////////////////////////////////////////////
/** @file Thread.h
 *  @ingroup Thread
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 06/04/2013
 *
 *  Defines the Thread class.
 *
**/
////////////////////////////////////////////////////////////
#ifndef APRO_THREAD_H
#define APRO_THREAD_H

#include "Implementable.h"
#include "List.h"
#include "Variant.h"
#include "SString.h"
#include "EventEmitter.h"

namespace APro
{
    class Thread;

    ////////////////////////////////////////////////////////////
    /** @class ThreadImplementation
     *  @ingroup Thread
     *  @brief Defines the implementation of the Thread class.
     *  @details One implementation must be available to use Thread
     *  on any platform.
    **/
    ////////////////////////////////////////////////////////////
    class APRO_DLL ThreadImplementation : public Implementation
    {
        APRO_DECLARE_SHAREDPOINTER_CLASS_TYPEDEF(ThreadImplementation)

    public:

        ////////////////////////////////////////////////////////////
        /** Give the name of the class implemented.
         *  @see Implementation::getClassImplementation
        **/
        ////////////////////////////////////////////////////////////
        const String getClassImplementation() const;

    public:

        ////////////////////////////////////////////////////////////
        /** Default constructor.
        **/
        ////////////////////////////////////////////////////////////
        ThreadImplementation();

        ////////////////////////////////////////////////////////////
        /** Virtual destructor
        **/
        ////////////////////////////////////////////////////////////
        virtual ~ThreadImplementation();

    public:

        ////////////////////////////////////////////////////////////
        /** Initialize the Thread.
         *  @see Implementation::init
         *  @note This function create the thread using create_thread
         *  function and notify the parent Thread if creation is
         *  successfull.
         *  @return Is the thread created ?
        **/
        ////////////////////////////////////////////////////////////
        bool init();

        ////////////////////////////////////////////////////////////
        /** Deinitialize the Thread.
         *  @see Implementation::deinit
         *  @note This function wait for the thread to finish. If you
         *  must kill the thread without waiting for it, use terminate.
        **/
        ////////////////////////////////////////////////////////////
        void deinit();

        ////////////////////////////////////////////////////////////
        /** Exit thread and notify.
         *  @note This function is generally used by the parent Thread
         *  to exit the Thread::exec function.
         *  @warning Don't use it externally.
        **/
        ////////////////////////////////////////////////////////////
        void exit();

        ////////////////////////////////////////////////////////////
        /** Terminate the Thread.
         *  @note This function temrinate the thread without cleaning
         *  anything and without checking for the Thread to be
         *  finished.
         *  @warning This function is not safe and may results to
         *  memory leaks. More, it has undefined behavior that if the
         *  thread call exit in the terminate function, the Thread
         *  will send more events.
        **/
        ////////////////////////////////////////////////////////////
        void terminate();

    public:

        ////////////////////////////////////////////////////////////
        /** Create the thread and execute it.
         *  @note This function JUST create the thread object,
         *  depending on the implementation and on the platform.
         *  @param pdata : Data to call the thread function with.
        **/
        ////////////////////////////////////////////////////////////
        virtual bool create_thread(void* pdata) = 0;

    public:

        ////////////////////////////////////////////////////////////
        /** Wait for thread to be finished.
        **/
        ////////////////////////////////////////////////////////////
        virtual void join_thread() = 0;

        ////////////////////////////////////////////////////////////
        /** Exit the thread.
        **/
        ////////////////////////////////////////////////////////////
        virtual void exit_thread() = 0;

        ////////////////////////////////////////////////////////////
        /** Terminate the thread.
        **/
        ////////////////////////////////////////////////////////////
        virtual void terminate_thread() = 0;

    public:

        Thread* m_parent;///< Thread wich own this implementation
    };

    ////////////////////////////////////////////////////////////
    /** @class Thread
     *  @ingroup Thread
     *  @brief Defines a thread.
     *  @details There are two ways to create it :
     *  - Construct a Thread object and setting a callback.
     *  - Inherits from it and override the exec() function.
     *
     *  @note The thread use the ThreadImplementation to
     *  run. So, the ThreadImplementation first create the thread
     *  (in notifying the Thread), then it runs a static function
     *  wich call the Thread::exec method.
     *  - If the Thread have a callback, the exec function will call
     *  this one with userdata arguments.
     *  - If it doesn't have, it will call the normal exec function,
     *  wich you should have override.
    **/
    ////////////////////////////////////////////////////////////
    class APRO_DLL Thread : public Implementable<ThreadImplementation>,
                            public EventEmitter
    {
        APRO_DECLARE_SHAREDPOINTER_CLASS_TYPEDEF(Thread)

    public:

        typedef void (*pfunc) (void*);///< The type of function to callback.
        friend class ThreadImplementation;

    public:

        ////////////////////////////////////////////////////////////
        /** Construct a Thread from nothing.
         *  @note Ths function shouldn't be called.
        **/
        ////////////////////////////////////////////////////////////
        Thread();

        ////////////////////////////////////////////////////////////
        /** Construct a Thread with a name.
         *  @param name : Name of the thread.
        **/
        ////////////////////////////////////////////////////////////
        Thread(const String& name);

        ////////////////////////////////////////////////////////////
        /** Virtual destructor.
        **/
        ////////////////////////////////////////////////////////////
        virtual ~Thread();

        ////////////////////////////////////////////////////////////
        /** Returns the name of the Thread.
         *  @return Name of the Thread.
        **/
        ////////////////////////////////////////////////////////////
        String getName() const;

        ////////////////////////////////////////////////////////////
        /** Set the callback to call during the Running process.
         *  @param ptr : Callback pointer.
         *  @param userdata : Data to use as argument.
        **/
        ////////////////////////////////////////////////////////////
        void setCallback(pfunc ptr, void* userdata)
        {
            m_callback = ptr;
            m_userdata = userdata;
        }

        ////////////////////////////////////////////////////////////
        /** Remove the callback.
        **/
        ////////////////////////////////////////////////////////////
        void removeCallback();

    protected:

        String m_name;///< Name of the thread.
        bool   m_started;///< Thread is started ?
        pfunc  m_callback;///< Callback function.
        void*  m_userdata;///< Argument to the callback.

    public:



    public:

        ////////////////////////////////////////////////////////////
        /** Create and run the thread.
        **/
        ////////////////////////////////////////////////////////////
        void run();

        ////////////////////////////////////////////////////////////
        /** Wait for the thread to finish.
        **/
        ////////////////////////////////////////////////////////////
        void join();

        ////////////////////////////////////////////////////////////
        /** Terminate the thread.
         *  @note This function is not safe. It forces te thread to
         *  terminate without freeing any memory allocated, so it can
         *  causes memory leaks.
        **/
        ////////////////////////////////////////////////////////////
        void terminate();

        ////////////////////////////////////////////////////////////
        /** Destroy the thread. It deinitialize the implementation.
        **/
        ////////////////////////////////////////////////////////////
        void destroy();

        ////////////////////////////////////////////////////////////
        /** Tell if thread is running.
         *  @return Is the thread running ?
        **/
        ////////////////////////////////////////////////////////////
        bool isRunning() const;

        ////////////////////////////////////////////////////////////
        /** Creates event to send.
         *  @see EventEmitter::createEvent
        **/
        ////////////////////////////////////////////////////////////
        Event::ptr createEvent(const String& name) const;

    public:

        ////////////////////////////////////////////////////////////
        /** Execute the thread.
         *  @note It is equivalent to the thread entry point. If you
         *  override this function, you should use
         *  Implementable::implement->exit() to stop the thread, even
         *  at the end of the function. This is necessary to notify
         *  thread finishing.
         *  @warning This function is called by the Thread Implementation,
         *  so you should never call this yourself. Use run() to start
         *  the thread.
        **/
        ////////////////////////////////////////////////////////////
        virtual void exec();

    protected:

        ////////////////////////////////////////////////////////////
        /** Notify thread starting.
         *  @warning This is an internal method used by
         *  ThreadImplementation, so you should never call this yourself.
        **/
        ////////////////////////////////////////////////////////////
        void notify_thread_started();

        ////////////////////////////////////////////////////////////
        /** Notify thread finishing.
         *  @warning This is an internal method used by
         *  ThreadImplementation, so you should never call this yourself.
        **/
        ////////////////////////////////////////////////////////////
        void notify_thread_terminated();

    protected:

        ////////////////////////////////////////////////////////////
        /** Init implementation.
         *  @see Implementable::initImplementation
        **/
        ////////////////////////////////////////////////////////////
        void initImplementation();

        ////////////////////////////////////////////////////////////
        /** Document Events.
         *  @see EventEmitter::documentEvents
        **/
        ////////////////////////////////////////////////////////////
        void documentEvents();
    };
}

#endif // APRO_THREAD_H
