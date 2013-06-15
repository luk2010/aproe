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
#include "SharedPointer.h"

namespace APro
{
    ////////////////////////////////////////////////////////////
    /** @class Manager
     *  @ingroup Utils
     *  @brief Utility class to manage typed objects.
     *  @details SubClass can manage a type of object with the
     *  push and pop command.
     *  @note Manager class isn't Thread-safe so the subclass
     *  should implement it.
     *  @note The subclass must clear the objets itself.
    **/
    ////////////////////////////////////////////////////////////
    template<typename T>
    class Manager
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
        virtual ~Manager()
        {
            // Manager must explicitly clear there objects
            //objects.clear();
        }

        ////////////////////////////////////////////////////////////
        /** @brief Push an object in the objects list.
         *  @details If the adress of the object is already pushed,
         *  the object isn't pushed.
         *
         *  @param obj : Object Pointer to push.
        **/
        ////////////////////////////////////////////////////////////
        virtual void push(const SharedPointer<T>& obj)
        {
            if(!obj.isNull() && objects.find(obj) == -1)
                objects.append(obj);
        }

        ////////////////////////////////////////////////////////////
        /** @brief Pop an object from the object list.
         *  @note The object isn't deleted.
         *
         *  @param obj : Object to erase from the list.
        **/
        ////////////////////////////////////////////////////////////
        virtual void pop(const SharedPointer<T>& obj)
        {
            int index = objects.find(obj);
            if(!obj.isNull() && index != -1)
                objects.erase(index);
        }

        ////////////////////////////////////////////////////////////
        /** @brief Clear every objects.
         *  @details This can be re-implemented by subclasses to
         *  possibly clear each object with special methods or things.
        **/
        ////////////////////////////////////////////////////////////
        virtual void clear()
        {
            objects.clear();
        }

    protected:

        List<SharedPointer<T> > objects;///< Object list.
    };
}

#endif
