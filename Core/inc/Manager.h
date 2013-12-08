/** @file Manager.h
 *  @ingroup Utils
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 20/09/2012
 *
 *  Defines the Manager class.
 *
**/
#ifndef APROMANAGERR_H
#define APROMANAGERR_H

#include "Platform.h"
#include "List.h"
#include "AutoPointer.h"

namespace APro
{
    ////////////////////////////////////////////////////////////
    /** @class Manager
     *  @ingroup Utils
     *  @brief Utility class to manage typed objects.
     *
     *  Simplifies the managing of objects by using uniquely the
     *  push/pop system.
     *  Objects are stored as AutoPointer.
     *
     *  @note This class is ThreadSafe.
     *  You can access to the objects list by using
     *  Manager<T>::objects. We advice you to use a reference variable
     *  constructed directly in the class :
     *  @code MyClass() : my_reference(Manager<T>::objects) {} @endcode
    **/
    ////////////////////////////////////////////////////////////
    template<typename T>
    class Manager : public ThreadSafe
    {
    public:

        ////////////////////////////////////////////////////////////
        /** @brief Constructor.
        **/
        ////////////////////////////////////////////////////////////
        Manager()
        {

        }

        ////////////////////////////////////////////////////////////
        /** @brief Destructor.
        **/
        ////////////////////////////////////////////////////////////
        ~Manager()
        {
            APRO_THREADSAFE_AUTOLOCK
            objects.clear();
        }

        ////////////////////////////////////////////////////////////
        /** @brief Push an object in the objects list.
        **/
        ////////////////////////////////////////////////////////////
        void push(const AutoPointer<T>& obj)
        {
            APRO_THREADSAFE_AUTOLOCK
            if(!obj.isNull() && objects.find(obj) == -1)
                objects.append(obj);
        }

        ////////////////////////////////////////////////////////////
        /** @brief Pop an object from the object list.
         *  @note The object isn't deleted.
        **/
        ////////////////////////////////////////////////////////////
        void pop(const AutoPointer<T>& obj)
        {
            APRO_THREADSAFE_AUTOLOCK
            int index = objects.find(obj);
            if(!obj.isNull() && index != -1)
                objects.erase(objects.begin() + index);
        }

        ////////////////////////////////////////////////////////////
        /** @brief Clear every objects.
        **/
        ////////////////////////////////////////////////////////////
        void clear()
        {
            APRO_THREADSAFE_AUTOLOCK
            objects.clear();
        }

    protected:

        List< AutoPointer<T> > objects;///< Object list.
    };
}

#endif
