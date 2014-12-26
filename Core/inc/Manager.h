////////////////////////////////////////////////////////////
/** @file Manager.h
 *  @ingroup Utils
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 20/09/2012 - 11/04/2014
 *
 *  Defines the Manager class.
 *
**/
////////////////////////////////////////////////////////////
#ifndef APROMANAGERR_H
#define APROMANAGERR_H

#include "Platform.h"
#include "AutoPointer.h"
#include "List.h"

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
     *
     *  @note <b>A note on how objects are stored :</b> Objects
     *  are stored into AutoPointer, but they are not pushed into
     *  a PointerCollector. Objects are so destroyed only by the
     *  Manager. This rule ony apply to objects loaded by brute
     *  pointer. if you push objects in already made AutoPointer, you
     *  will not have this feature.
     *
     *  Objects Pointers are stored in a List by default, but you
     *  can choose to store them in an Array. An Array is more efficient
     *  than a list as there are only push/pop access by default, but
     *  destructors are less guarenteed to be called in Array than in
     *  List.
    **/
    ////////////////////////////////////////////////////////////
    template<typename T, typename Container = List<AutoPointer<T> > >
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

        void push(T* object)
        {
            if(object)
                push(AutoPointer<T>(object));
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
                objects.erase(objects.begin() + (size_t) index);
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

        Container objects;///< Object list.
    };
}

#endif
