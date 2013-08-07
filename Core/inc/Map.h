/** @file Map.h
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 24/08/2012
 *
 *  @addtogroup Global
 *  @addtogroup Memory
 *
 *  This file defines the Map class.
 *
**/
#ifndef APROMAP_H
#define APROMAP_H

#include "Platform.h"
#include "List.h"
#include "Console.h"

namespace APro
{
    template <typename T1, typename T2>
    class Map
    {
    public:

        class Pair
        {
        private:
            T1* obj;
            T2* obj2;

        public:

            Pair()
            {
                obj = AProNew(1, T1) ();
                obj2 = AProNew(1, T2) ();
            }

            Pair(const T1& first, const T2& second)
            {
                obj = AProNew(1, T1) (first);
                obj2 = AProNew(1, T2) (second);
            }

            Pair(const Pair& other)
            {
                obj = AProNew(1, T1) (other.first());
                obj2 = AProNew(1, T2) (other.second());
            }

            ~Pair()
            {
                if(obj != nullptr)
                    AProDelete(obj);
                if(obj2 != nullptr)
                    AProDelete(obj2);
            }

            T1& first()
            {
                return *obj;
            }

            const T1& first() const
            {
                return *obj;
            }

            T2& second()
            {
                return *obj2;
            }

            const T2& second() const
            {
                return *obj2;
            }

            void setFirst(const T1& obj_)
            {
                if(obj != nullptr)
                    AProDelete(obj);

                obj = AProNew(1, T1) (obj_);
            }

            void setSecond(const T2& obj_)
            {
                if(obj2 != nullptr)
                    AProDelete(obj2);

                obj2 = AProNew(1, T2) (obj_);
            }

            bool operator == (const Pair& other)
            {
                return obj == other.obj &&
                        obj2 == other.obj2;
            }

            bool operator != (const Pair& other)
            {
                return !(*this == other);
            }
        };

    private:

        List<Pair*> pairs;

    public:

        Map()
        {

        }

        Map(const Map<T1, T2>& other)
        {
            for(unsigned int i = 0; i < other.size(); i++)
            {
                const Map<T1, T2>::Pair& pair = other.getPair(i);
                push(pair.first(), pair.second());
            }
        }
        
        Map<T1, T2> & operator = (const Map<T1, T2>& other)
        {
            clear();
            for(unsigned int i = 0; i < other.size(); i++)
            {
                const Map<T1, T2>::Pair& pair = other.getPair(i);
                push(pair.first(), pair.second());
            }
        }

        ~Map()
        {
            clear();
        }

        void push(const T1& key, const T2& value)
        {
            pairs.push_back(AProNew(1, Pair) (key, value));
        }

        void pop(const T1& key)
        {
            int index = getIndex(key);
            if(index < 0)
                return;

            Pair* toDelete = pairs.at(index);
            pairs.erase(index);

            AProDelete(toDelete);
        }

        size_t size() const
        {
            return pairs.size();
        }

        size_t physicalSize() const
        {
            return  pairs.getPhysicalSize() +
                    sizeof(T1) * size() +
                    sizeof(T2) * size() +
                    sizeof(Pair) * size();
        }

        T2& operator [] (const T1& key)
        {
            int index = getIndex(key);
            if(index < 0)
            {
                push(key, T2());
                return getPair(getIndex(key)).second();
            }
            else
            {
                return getPair(index).second();
            }
        }
        const T2& operator [] (const T1& key) const
        {
            return getPair(getIndex(key)).second();
        }

        Pair& getPair(size_t index)
        {
            return * (pairs.at(index));
        }

        const Pair& getPair(size_t index) const
        {
            return * (pairs.at(index));
        }

        int getIndex(const T1& key) const
        {
            for(unsigned int i = 0; i < size(); i++)
            {
                if(getPair(i).first() == key)
                    return i;
            }
            return -1;
        }

        void clear()
        {
            while(!pairs.size() == 0)
            {
                Pair* toDelete = pairs.at(0);
                pairs.erase(0);
                AProDelete(toDelete);
            }
        }

        List<Pair*>& toList()
        {
            return pairs;
        }

        const List<Pair*>& toList() const
        {
            return pairs;
        }

        bool exists(const T1& key) const
        {
            return getIndex(key) > -1;
        }
    };
}

#endif
