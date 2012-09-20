/** @file Manager.h
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 20/09/2012
 *
 *  @addtogroup Global
 *  @addtogroup System
 *
 *  This file defines the Manager class.
 *
**/
#ifndef APROMANAGERR_H
#define APROMANAGERR_H

#include "Platform.h"
#include "List.h"
#include "SharedPointer.h"

namespace APro
{
    template<typename T>
    class Manager
    {
    public:

        Manager()
        {

        }

        virtual ~Manager()
        {
            objects.clear();
        }

        virtual void push(const SharedPointer<T>& obj)
        {
            if(!obj.isNull() && objects.find(obj) == -1)
                objects.append(obj);
        }

        virtual void pop(const SharedPointer<T>& obj)
        {
            int index = objects.find(obj);
            if(!obj.isNull() && index != -1)
                objects.erase(index);
        }

        virtual void clear()
        {
            objects.clear();
        }

    protected:

        List<SharedPointer<T> > objects;
    };
}

#endif
