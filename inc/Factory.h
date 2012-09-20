/** @file Factory.h
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 19/09/2012
 *
 *  @addtogroup Global
 *  @addtogroup System
 *
 *  This file defines the Factory class.
 *
**/
#ifndef APROFACTORY_H
#define APROFACTORY_H

#include "Platform.h"
#include "SharedPointer.h"
#include "List.h"
#include "Manager.h"

namespace APro
{
    template <typename T>
    class Factory
    {
    public:

        typedef typename List<SharedPointer<T> >::Iterator SharedPtrTypeListIterator;

    public:
        Factory()
        {

        }

        Factory(const String& n)
            : name(n)
        {

        }

        virtual ~Factory()
        {
            Objects.clear();
        }

        virtual SharedPointer<T> create() = 0;
        virtual void destroy(const SharedPointer<T>& obj) = 0;

        void clear()
        {
            for(SharedPtrTypeListIterator i(Objects.begin()); !i.isEnd(); i++)
            {
                destroy(i.get());
            }

            Objects.clear();
        }

        String getName() const
        {
            return name;
        }

        void setName(const String& n)
        {
            name = n;
        }

    protected:

        void registerObject(const SharedPointer<T>& object)
        {
            if(Objects.find(object) == -1)
                Objects.append(object);
        }

        void unregisterObject(const SharedPointer<T>& object)
        {
            int index = Objects.find(object);
            if(index != -1)
                Objects.erase(index);
        }

    private:

        String name;
        List<SharedPointer<T> > Objects;
    };

    template<typename T>
    class FactoryManager : public Manager<T>
    {
    public:

        typedef typename List<SharedPointer<T> >::Iterator SharedPtrTypeListIterator;

    public:
        SharedPointer<T> find(const String& name)
        {
            for(SharedPtrTypeListIterator i(Manager<T>::objects.begin()); !i.isEnd(); i++)
            {
                if(i.get()->getName() == name)
                    return i.get();
            }

            return SharedPointer<T>();
        }

        void clear()
        {
            for(SharedPtrTypeListIterator i(Manager<T>::objects.begin()); !i.isEnd(); i++)
            {
                i.get()->clear();
            }

            Manager<T>::clear();
        }

        String availableFactories() const
        {
            String ret;

            ret << "[FactoryManager<" << typeid(T).name() << ">] Available Factories : ";

            if(Manager<T>::objects.isEmpty())
            {
                ret << "\n  + None You should add some factories :) !";
            }
            else
            {
                for(SharedPtrTypeListIterator i(Manager<T>::objects.begin()); !i.isEnd(); i++)
                {
                    ret << "\n  + " << i.get()->getName();
                }
            }

            return ret;
        }
    };
}

#endif
