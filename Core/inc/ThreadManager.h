////////////////////////////////////////////////////////////
/** @file ThreadManager.h
 *  @ingroup Thread
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 06/04/2013
 *
 *  Defines the ThreadManager class.
 *
**/
////////////////////////////////////////////////////////////
#ifndef APRO_THREADMANAGER_H
#define APRO_THREADMANAGER_H

#include "Platform.h"
#include "Array.h"
#include "Singleton.h"

#include "ThreadMutex.h"
#include "ThreadCondition.h"
#include "Thread.h"

namespace APro
{
    ////////////////////////////////////////////////////////////
    /** @class ThreadManager
     *  @ingroup Thread
     *  @brief Manages every Thread, Condition and Mutex active
     *  in the engine.
     *
     *  It helps other class to get Condition or Mutex or even
     *  Threads easily.
     *
     *  @note You must create condition, mutex and thread
     *  by calling ThreadManager::create*(Thread, Condition or
     *  Mutex).
     *
     *  @note Ids are generated using the default IdGenerator given
     *  by the Main object.
     *
     *  @note Mutexs can also be used as internals one, if you don't
     *  need event support you can create them as normal objects.
    **/
    ////////////////////////////////////////////////////////////
    class APRO_DLL ThreadManager : public ThreadSafe
    {

        APRO_DECLARE_MANUALSINGLETON(ThreadManager)

    private:

        typedef Array<ThreadPtr> ThreadArray;
        ThreadArray threads;///< Threads created.

        typedef Array<ThreadMutexPtr> MutexArray;
        MutexArray mutexs;///< Mutexs created.

        typedef Array<ThreadConditionPtr> ConditionArray;
        ConditionArray conditions;///< Conditions created;

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Constructs the manager.
        **/
        ////////////////////////////////////////////////////////////
        ThreadManager();

        ////////////////////////////////////////////////////////////
        /** @brief Destructs the manager.
         *
         *  On destruction, every created threads are destroyed and so
         *  terminated.
        **/
        ////////////////////////////////////////////////////////////
        ~ThreadManager();

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Returns a new thread with given name.
        **/
        ////////////////////////////////////////////////////////////
        ThreadPtr createThread(const String& name);

        ////////////////////////////////////////////////////////////
        /** @brief Returns the thread that have given name if exists,
         *  or null.
        **/
        ////////////////////////////////////////////////////////////
        ThreadPtr getThread(const String& name);

        ////////////////////////////////////////////////////////////
        /** @brief Returns the thread that have given name if exists,
         *  or null.
        **/
        ////////////////////////////////////////////////////////////
        const ThreadPtr& getThread(const String& name) const;

        ////////////////////////////////////////////////////////////
        /** @brief Destroys given thread.
         *
         *  Waits 30 seconds the thread to finish, then terminate it
         *  if thread is not finished.
         *  AutoPointer ensure thread objet is correctly destroyed.
        **/
        ////////////////////////////////////////////////////////////
        void destroyThread(const String& name);

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Returns a new mutex.
        **/
        ////////////////////////////////////////////////////////////
        ThreadMutexPtr createMutex();

        ////////////////////////////////////////////////////////////
        /** @brief Returns mutex defined by given id.
        **/
        ////////////////////////////////////////////////////////////
        ThreadMutexPtr getMutex(Id id);

        ////////////////////////////////////////////////////////////
        /** @brief Returns mutex defined by given id.
        **/
        ////////////////////////////////////////////////////////////
        const ThreadMutexPtr& getMutex(Id id) const;

        ////////////////////////////////////////////////////////////
        /** @brief Destroys given mutex.
        **/
        ////////////////////////////////////////////////////////////
        void destroyMutex(Id id);

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Returns a new condition.
        **/
        ////////////////////////////////////////////////////////////
        ThreadConditionPtr createCondition();

        ////////////////////////////////////////////////////////////
        /** @brief Returns condition defined by given id.
        **/
        ////////////////////////////////////////////////////////////
        ThreadConditionPtr getCondition(Id id);

        ////////////////////////////////////////////////////////////
        /** @brief Returns condition defined by given id.
        **/
        ////////////////////////////////////////////////////////////
        const ThreadConditionPtr& getCondition(Id id) const;

        ////////////////////////////////////////////////////////////
        /** @brief Destroys given condition.
        **/
        ////////////////////////////////////////////////////////////
        void destroyCondition(Id id);

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Stop every running threads.
         *
         *  It waits 30 seconds for each thread to be finished and if
         *  they are not, it terminates them.
        **/
        ///////////////////////////////////////////////////////////
        void stopThreads();

        ////////////////////////////////////////////////////////////
        /** @brief Stop every running threads and destroy every threads,
         *  mutexs and conditions.
        **/
        ///////////////////////////////////////////////////////////
        void clear();

    };
}

#endif // APRO_THREADMANAGER_H
