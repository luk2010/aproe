/** @file Store.h
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 16/03/2013
 *
 *  @addtogroup Global
 *  @addtogroup System
 *
 *  This file defines the Store class.
 *
**/
#ifndef APRO_STORE_H
#define APRO_STORE_H

#include "Platform.h"
#include "List.h"
#include "Variant.h"

namespace APro
{
    /**
        A store is a class that can 'store' objects. You must provide an identification system
        to your objects to be correctly stored. You can choose to give them a name, or an id, or anything else.

        @note This system is provided for efficiency, and for unique objects. You can't store 2 objects with same
        identificator. Use factory instead.
    **/
    template <typename T>
    class Store
    {
    public:

        typedef typename T::ptr typeptr;

    protected:

        List<typeptr> objects;
        typedef typename List<typeptr>::Iterator IteratorType;
        typedef typename List<typeptr>::ConstIterator ConstIteratorType;

    public:

        Store()
        {

        }

        virtual ~Store()
        {

        }

    protected:

        bool isStorable(const typeptr & object) const
        {
            if(object.isNull()) return false;

            ConstIteratorType ite = objects.end();
            for(ConstIteratorType i(objects.begin()); i != ite; i++)
            {
                if(isKeyEgal(object, i))
                    return false;
            }

            return true;
        }

        IteratorType findKey(const Variant & key)
        {
            ConstIteratorType itend = objects.end();
            for(IteratorType i(objects.begin()); i != itend; i++)
            {
                if(isKeyEgal(key, i))
                    return i;
            }

            return objects.end();
        }

        IteratorType findObject(const typeptr& object)
        {
            if(object.isNull()) return objects.end();

            ConstIteratorType ite = objects.end();
            for(IteratorType i(objects.begin()); i != ite; i++)
            {
                if(isKeyEgal(object, i))
                    return i;
            }

            return objects.end();
        }

        virtual bool isKeyEgal(const Variant& var, ConstIteratorType it) const = 0;
        virtual bool isKeyEgal(const typeptr& object, ConstIteratorType it) const = 0;

    public:

        bool store(const typeptr& object)
        {
            if(isStorable(object))
            {
                objects.append(object);
                return true;
            }

            return false;
        }

        typeptr unstore(const Variant& objectQual)
        {
            IteratorType it = findKey(objectQual);
            ConstIteratorType ite = objects.end();
            if(it != ite)
            {
                typeptr o = it.get();
                objects.erase(it);

                return o;
            }

            return typeptr();
        }

        typeptr find(const Variant& objectQual)
        {
            return findKey(objectQual).get();
        }

        void clear()
        {
            objects.clear();
        }
    };
}

#endif // APRO_STORE_H
