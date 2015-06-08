/////////////////////////////////////////////////////////////
/** @file QuickMap.h
 *  @ingroup Utils
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 26/04/2015 - 05/06/2015
 *
 *  @brief
 *  Defines the QuickMap class.
 *
 *  @copyright
 *  Atlanti's Project Engine
 *  Copyright (C) 2012 - 2015  Atlanti's Corp
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
**/
/////////////////////////////////////////////////////////////
#ifndef APRO_QUICKMAP_H
#define APRO_QUICKMAP_H

#include "Platform.h"
#include "SString.h"
#include "GenericHash.h"

namespace APro
{
    /////////////////////////////////////////////////////////////
    /** @class QuickMap
     *  @ingroup Utils
     *  @brief Implements a Quick Access Map based on Hash. 
     *  @see http://cs.stanford.edu/people/eroberts/courses/cs106b/chapters/12-implementing-maps.pdf
     * 
     *  The KeyType must have a correct Hash function returned 
     *  by GenericHash<KeyType>::GetFunction(). The user can provide
     *  this function. 
     *  
     *  The loadFactor of this Map is very important, as it manages
     *  dynamicly the number of buckets getting the entries in the Map.
     *  You should find a correct loadFactor for your map when creating
     *  it (generally 4.0 or 5.0 is okay).
    **/
    /////////////////////////////////////////////////////////////
    template <typename KeyType, typename ValueType>
    class QuickMap
    {
    public:
        
        struct CellT
        {
            KeyType   key;
            ValueType value;
            CellT*    link;
        };
        
        typedef GenericHashFunction<KeyType> HashFunction;///< @brief Describe the Hash function.
        
    private:
        
        HashFunction mHashFunc;  ///< @brief The Hash Function used in this Map.
        int     mNumBuckets;     ///< @brief Allocated size of the Buckets array.
        int     mNumEntries;     ///< @brief Actual number of entries in the map.
        uint32_t mMaxLoadFactor; ///< @brief Maximum load factor for the Map.
        uint32_t mMinLoadFactor; ///< @brief Minimum load factor for the Map.
        CellT** mBuckets;        ///< @brief Dynamic Array of Buckets.
        
    public:
        
        /////////////////////////////////////////////////////////////
        /** @brief Create a QuickMap from a moved map.
         **/
        /////////////////////////////////////////////////////////////
        QuickMap(QuickMap&& movedMap);
        
        /////////////////////////////////////////////////////////////
        /** @brief Constructs the Map object.
         *
         *  @note
         *  The constructor allocates the array of buckets and initializes
         *  each bucket to the empty list.
         *
         *  @param reservedBuckets : Reserve an initial number of buckets, 
         *  independantly from max and min load factor. This can be used
         *  to reserve directly buckets for big sized map.
         *
         *  @param maxLoadFactor : This parameter is very important for
         *  the performance of the Map. For big maps, the higher the loadFactor
         *  is, the less efficience the map is. But decreasing the loadFactor
         *  increase the data size of the Map (number of buckets increase
         *  to decrease the number of entries by buckets).
         *
         *  @param minLoadFactor : The minimum load factor that can be reached
         *  by the Map when reorganizing itself. This is used in order to 
         *  prevent the Map from having big buckets array, and so minimize
         *  the data size, but it also can prevent the Map form correctly
         *  optimizing the buckets array.
         *
         *  @param hashFunc : The Hashing function used by this map to 
         *  hash the keys. This function should be the quickest possible.
         *  You may use the GenericHash::GetFunction() template to get
         *  this function, as users can provide their own hash function.
        **/
        /////////////////////////////////////////////////////////////
        QuickMap(int reservedBuckets = 10, Real maxLoadFactor = 5.0, Real minLoadFactor = 1.0, HashFunction hashFunc = GenericHash<KeyType>::GetFunction());
        
        /////////////////////////////////////////////////////////////
        /** @brief Destroys the Map.
        **/
        /////////////////////////////////////////////////////////////
        ~QuickMap();
        
    public:
        
        /////////////////////////////////////////////////////////////
        /** @brief Returns the Load Factor of the HashMap.
         *
         *  It corresponds to the average lenght of the chain which
         *  returns from the findCell function. 
         *
         *  For good performance, you want to make sure that the value of 
         *  loadFactor remains relatively small. On the other hand, choosing 
         *  a large value for nBuckets means that there are lots of empty 
         *  buckets in the hash table array, which wastes a certain amount 
         *  of space.
         *
         *  @return
         *  A number called Load Factor.
        **/
        /////////////////////////////////////////////////////////////
        Real loadFactor() const;
        
        /////////////////////////////////////////////////////////////
        /** @brief Returns the number of entries in this map.
        **/
        /////////////////////////////////////////////////////////////
        uint32_t size() const;
        
        /////////////////////////////////////////////////////////////
        /** @brief Returns true if the map does not contain any entry.
        **/
        /////////////////////////////////////////////////////////////
        bool isEmpty() const;
        
        /////////////////////////////////////////////////////////////
        /** @brief Clear the map (destroy every nodes).
         *
         *  @note
         *  The implementation destroy each bucket chain.
        **/
        /////////////////////////////////////////////////////////////
        void clear();
        
        /////////////////////////////////////////////////////////////
        /** @brief Removes a key in the Map.
         *
         *  @note
         *  The remove method cannot use the findCell method as it
         *  stands because it needs a pointer to the previous entry.
         *  Because that code is used only in this method, the loop
         *  through the cells in a chain is reimplemented here and
         *  therefore does not add any cost to the get/put operations.
        **/
        /////////////////////////////////////////////////////////////
        void remove(const KeyType& key);
        
    public:
        
        /////////////////////////////////////////////////////////////
        /** @brief Add an entry to the Map if the key does not already
         *  exists.
         *
         *  @param key : Key to look up. If the key already exists, the
         *  value will be overwritten with the given one. 
         *
         *  @param value : Value to add to the map for given key.
         *
         *  @note
         *  When adding a new entry in the map, if the loadFactor is 
         *  superior to the given one, the Map is recalculated in order
         *  to have a loadFactor of mMinLoadFactor (the complexity of the
         *  Map is so reduced to O(n * mMinLoadFactor)). This may take time,
         *  so you may reserve buckets before adding entries when adding 
         *  multiple entries in the map.
        **/
        /////////////////////////////////////////////////////////////
        void put(const KeyType& key, const ValueType& value);
        
        ValueType& operator [] (const KeyType& key);
        const ValueType& operator [] (const KeyType& key) const;
        
        /////////////////////////////////////////////////////////////
        /** @brief Returns the value for given key.
        **/
        /////////////////////////////////////////////////////////////
        ValueType& get(const KeyType& key);
        
        /////////////////////////////////////////////////////////////
        /** @brief Returns the value for given key.
        **/
        /////////////////////////////////////////////////////////////
        const ValueType& get(const KeyType& key) const;
        
        /////////////////////////////////////////////////////////////
        /** @brief Returns true if the Map contains the given key.
        **/
        /////////////////////////////////////////////////////////////
        bool contains(const KeyType& key) const;
        
    private:
        
        /////////////////////////////////////////////////////////////
        /** @brief Hash the given key value. 
         *
         *  This function takes the key and uses it to derive a hash code,
         *  which is a nonnegative integer. The Hash function is the one
         *  given by the user. 
         *  
         *  @return
         *  If no function is given, this function returns -1.
        **/
        /////////////////////////////////////////////////////////////
        int hash(const KeyType& key);
        
        /////////////////////////////////////////////////////////////
        /** @brief Finds a cell in the chain that matches key.
         *
         *  @return
         *  If a match is found, findCell returns a pointer to that cell.
         *  If not, findCell returns NULL.
        **/
        /////////////////////////////////////////////////////////////
        CellT* findCell(CellT* chain, const KeyType& key);
        
        /////////////////////////////////////////////////////////////
        /** @brief Deletes all of the cells in a bucket chain.
         *
         *  It operates recursively by freeing the rest of the chain
         *  and freeing the current cell.
        **/
        /////////////////////////////////////////////////////////////
        void deleteChain(CellT* chain);
        
        /////////////////////////////////////////////////////////////
        /** @brief Reorganize the Map in order to have a loadFactor
         *  of mMinLoadFactor.
        **/
        /////////////////////////////////////////////////////////////
        void reorganizeMap();
        
        /////////////////////////////////////////////////////////////
        /** @brief Add a chain to this Map. 
         *
         *  @note
         *  It adds every cell in the chain, recalculating the index
         *  using the hash function.
        **/
        /////////////////////////////////////////////////////////////
        void addBucket(CellT* chain);
        
        /////////////////////////////////////////////////////////////
        /** @brief Add a given cell to the map in the correct bucket.
        **/
        /////////////////////////////////////////////////////////////
        void addCell(CellT* cell);
        
    public:
    	
    	class const_iterator;
        
        /////////////////////////////////////////////////////////////
        /** @brief An Iterator class to go through the Map.
        **/
        /////////////////////////////////////////////////////////////
        class iterator
        {
        public:
            
            iterator(CellT** buckets, int numBucket, CellT* cur, HashFunction hash)
            {
                mBuckets = buckets;
                mCell = cur;
                mHash = hash;
            }
            
            iterator& operator++ ()
            {
                if(mCell->link != nullptr)
                    mCell = mCell->link;
                else
                {
                    if(mCell == nullptr)
                        return this;
                    
                    int index = mHash(mCell->key) % mNumBuckets;
                    index++;
                    
                    mCell = nullptr;
                    
                    if(index >= mNumBuckets)
                        return this;
                    
                    // Look for next valid bucket.
                    while (mBuckets[index] == nullptr && index < mNumBuckets)
                        index++;
                    
                    if(index >= mNumBuckets)
                        return this;
                    else
                        mCell = mBuckets[index];
                    
                    return this;
                }
            }
            
            iterator& next()
            {
                return operator++ ();
            }
            
            iterator& operator + (int i)
            {
                while(i > 0)
                    operator++ ();
                return this;
            }
            
            KeyType& key()
            {
                aproassert1(mCell != nullptr);
                return mCell->key;
            }
            
            ValueType& value()
            {
                aproassert1(mCell != nullptr);
                return mCell->value;
            }
            
            bool isValid()
            {
                return mCell != nullptr;
            }
            
            bool operator == (iterator& it) const { return mCell == it.mCell; }
            bool operator == (const_iterator& it) const;
            
            bool operator != (iterator& it) const { return mCell != it.mCell; }
            bool operator != (const_iterator& it) const;
            
        private:
            
            CellT** mBuckets;
            CellT*  mCell;
            HashFunction mHash;
            int mNumBuckets;
        };
        
        /////////////////////////////////////////////////////////////
        /** @brief A Constant Iterator class to go through the Map.
        **/
        /////////////////////////////////////////////////////////////
        class const_iterator
        {
        public:
            
            const_iterator(iterator& it)
            {
                mBuckets = it.mBuckets;
                mNumBuckets = it.mNumBuckets;
                mCell = it.mCell;
                mHash = it.mHash;
            }
            
            const_iterator(CellT** buckets, int numBucket, CellT* cur, HashFunction hash)
            {
                mBuckets = buckets;
                mNumBuckets = numBucket;
                mCell = cur;
                mHash = hash;
            }
            
            const_iterator& operator++ ()
            {
                if(mCell->link != nullptr)
                    mCell = mCell->link;
                else
                {
                    if(mCell == nullptr)
                        return this;
                    
                    int index = mHash(mCell->key) % mNumBuckets;
                    index++;
                    
                    mCell = nullptr;
                    
                    if(index >= mNumBuckets)
                        return this;
                    
                    // Look for next valid bucket.
                    while (mBuckets[index] == nullptr && index < mNumBuckets)
                        index++;
                    
                    if(index >= mNumBuckets)
                        return this;
                    else
                        mCell = mBuckets[index];
                    
                    return this;
                }
            }
            
            const_iterator& next()
            {
                return operator++ ();
            }
            
            const_iterator& operator + (int i)
            {
                while(i > 0)
                    operator++ ();
                return this;
            }
            
            const KeyType& key()
            {
                aproassert1(mCell != nullptr);
                return mCell->key;
            }
            
            const ValueType& value()
            {
                aproassert1(mCell != nullptr);
                return mCell->value;
            }
            
            bool isValid()
            {
                return mCell != nullptr;
            }
            
            bool operator == (iterator& it) const { return mCell == it.mCell; }
            bool operator == (const_iterator& it) const { return mCell == it.mCell; }
            
            bool operator != (iterator& it) const { return mCell != it.mCell; }
            bool operator != (const_iterator& it) const { return mCell != it.mCell; }
            
        private:
            
            CellT** mBuckets;
            CellT*  mCell;
            HashFunction mHash;
            int mNumBuckets;
        };
        
    public:
        
        iterator begin();
        const_iterator begin() const;
        const_iterator end() const;
    };
    
    template <typename KeyType, typename ValueType>
	QuickMap<KeyType, ValueType>::QuickMap(QuickMap<KeyType, ValueType>&& movedMap)
    {
        using std::swap;
        
        mBuckets       = nullptr;
        mNumEntries    = 0;
        mNumBuckets    = 0;
        mHashFunc      = nullptr;
        mMaxLoadFactor = 0;
        mMinLoadFactor = 0;
        
        swap(mBuckets,       movedMap.mBuckets);
        swap(mNumBuckets,    movedMap.mNumBuckets);
        swap(mNumEntries,    movedMap.mNumEntries);
        swap(mHashFunc,      movedMap.mHashFunc);
        swap(mMaxLoadFactor, movedMap.mMaxLoadFactor);
        swap(mMinLoadFactor, movedMap.mMinLoadFactor);
    }
    
    template <typename KeyType, typename ValueType>
    QuickMap<KeyType, ValueType>::QuickMap(int reservedBuckets, Real maxLoadFactor, Real minLoadFactor, QuickMap<KeyType, ValueType>::HashFunction hashFunc)
    {
        aproassert1(maxLoadFactor > 0);
        aproassert1(minLoadFactor > 0);
        aproassert1(minLoadFactor < maxLoadFactor);
        aproassert1(hashFunc != nullptr);
        aproassert1(reservedBuckets > 0);
        
        mMaxLoadFactor = maxLoadFactor;
        mMinLoadFactor = minLoadFactor;
        mNumBuckets    = reservedBuckets;
        mNumEntries    = 0;
        mHashFunc      = hashFunc;
        mBuckets       = nullptr;
        
        // Initialize the bucket array.
        mBuckets = AProNewA(CellT*, mNumBuckets);
        for(uint32_t i = 0; i < mNumBuckets; ++i) {
            mBuckets[i] = nullptr;
        }
    }
    
    template <typename KeyType, typename ValueType>
    QuickMap<KeyType, ValueType>::~QuickMap()
    {
        clear();
        AProDelete(mBuckets);
    }
    
    template <typename KeyType, typename ValueType>
    Real QuickMap<KeyType, ValueType>::loadFactor() const
    {
        return mNumEntries / mNumBuckets;
    }
    
    template <typename KeyType, typename ValueType>
    uint32_t QuickMap<KeyType, ValueType>::size() const
    {
        return mNumEntries;
    }
    
    template <typename KeyType, typename ValueType>
    bool QuickMap<KeyType, ValueType>::isEmpty() const
    {
        return mNumEntries == 0;
    }
    
    template <typename KeyType, typename ValueType>
    void QuickMap<KeyType, ValueType>::clear()
    {
        for(uint32_t i = 0; i < mNumBuckets; ++i)
        {
            deleteChain(mBuckets[i]);
        }
        
        mNumEntries = 0;
    }
    
    template <typename KeyType, typename ValueType>
    void QuickMap<KeyType, ValueType>::remove(const KeyType& key)
    {
        int index = mHashFunc(key);
        aproassert1(index > -1);
        index = index % mNumBuckets;
        
        CellT* prev = nullptr;
        CellT* cp   = mBuckets[index];
        
        while (cp != nullptr && cp->key != key)
        {
            prev = cp;
            cp = cp->link;
        }
        
        if(cp != nullptr)
        {
            if(prev == nullptr)
                mBuckets[index] = cp->link;
            else
                prev->link = cp->link;
            
            AProDelete(cp);
            mNumEntries--;
        }
    }
    
    template <typename KeyType, typename ValueType>
    void QuickMap<KeyType, ValueType>::put(const KeyType& key, const ValueType& value)
    {
        aproassert1(mMaxLoadFactor > 0);
        aproassert1(mHashFunc != nullptr);
        
        int hash = mHashFunc(key);
        aproassert1(hash > -1);
        
        int index = hash % mNumBuckets;
        CellT* cell = findCell(mBuckets[index], key);
        
        if(cell == nullptr)
        {
            // We must see if loadFactor is okay.
            mNumEntries++;
            if(loadFactor() > mMaxLoadFactor)
            {
                reorganizeMap();
            }
            
            // Creating a new cell.
            index = hash % mNumBuckets;
            cell = AProNew(CellT);
            cell->key = key;
            cell->link = mBuckets[index];
            mBuckets[index] = cell;
        }
        
        cell->value = value;
    }
    
    template <typename KeyType, typename ValueType>
    ValueType& QuickMap<KeyType, ValueType>::operator [] (const KeyType& key)
    {
        aproassert1(mMaxLoadFactor > 0);
        aproassert1(mHashFunc != nullptr);
        
        int hash = mHashFunc(key);
        aproassert1(hash > -1);
        
        int index = hash % mNumBuckets;
        CellT* cell = findCell(mBuckets[index], key);
        
        if(cell == nullptr)
        {
            // We must see if loadFactor is okay.
            mNumEntries++;
            if(loadFactor() > mMaxLoadFactor)
            {
                reorganizeMap();
            }
            
            // Creating a new cell.
            index = hash % mNumBuckets;
            cell = AProNew(CellT);
            cell->key = key;
            cell->link = mBuckets[index];
            mBuckets[index] = cell;
        }
        
        return cell->value;
    }
    
    template <typename KeyType, typename ValueType>
    const ValueType& QuickMap<KeyType, ValueType>::operator [] (const KeyType& key) const
    {
        aproassert1(mMaxLoadFactor > 0);
        aproassert1(mHashFunc != nullptr);
        
        int hash = mHashFunc(key);
        aproassert1(hash > -1);
        
        int index = hash % mNumBuckets;
        CellT* cell = findCell(mBuckets[index], key);
        aproassert1(cell != nullptr);
        return cell->value;
    }
    
    template <typename KeyType, typename ValueType>
    ValueType& QuickMap<KeyType, ValueType>::get(const KeyType& key)
    {
        CellT* cell = findCell(mBuckets[mHashFunc(key) % mNumBuckets], key);
        aproassert1(cell != nullptr);
        return cell->value;
    }
    
    template <typename KeyType, typename ValueType>
    const ValueType& QuickMap<KeyType, ValueType>::get(const KeyType& key) const
    {
        return (const_cast<QuickMap<KeyType, ValueType>*>(this))->get(key);
    }
    
    template <typename KeyType, typename ValueType>
    bool QuickMap<KeyType, ValueType>::contains(const KeyType& key) const
    {
        return (const_cast<QuickMap<KeyType, ValueType>*>(this))->findCell(mBuckets[mHashFunc(key) % mNumBuckets], key) != nullptr;
    }
    
    template <typename KeyType, typename ValueType>
    int QuickMap<KeyType, ValueType>::hash(const KeyType& key)
    {
        aproassert1(mHashFunc != 0);
        return mHashFunc(key);
    }
    
    template <typename KeyType, typename ValueType>
    typename QuickMap<KeyType, ValueType>::CellT* QuickMap<KeyType, ValueType>::findCell(CellT* chain, const KeyType& key)
    {
        for(CellT* cp = chain; cp != nullptr; cp = cp->link)
        {
            if(cp->key == key)
                return cp;
        }
        
        return nullptr;
    }
    
    template <typename KeyType, typename ValueType>
    void QuickMap<KeyType, ValueType>::deleteChain(CellT* chain)
    {
        if(chain != nullptr)
        {
            deleteChain(chain->link);
            AProDelete(chain);
        }
    }
    
    template <typename KeyType, typename ValueType>
    void QuickMap<KeyType, ValueType>::reorganizeMap()
    {
        // We temporize the current data.
        CellT** oldBuckets     = mBuckets;
        uint32_t oldNumBuckets = mNumBuckets;
        
        // We assume mNumEntries has been ++'d.
        mNumBuckets = mNumEntries / mMinLoadFactor;
        
        // Creating a new Buckets array.
        mBuckets = AProNewA(CellT*, mNumBuckets);
        for(uint32_t i = 0; i < mNumBuckets; ++i) {
            mBuckets[i] = nullptr;
        }
        
        // Putting every data in the new Bucket array.
        for(uint32_t i = 0; i < oldNumBuckets; ++i) {
            addBucket(oldBuckets[i]);
        }
        
        // Deleting old data.
        AProDelete(oldBuckets);
    }
    
    template <typename KeyType, typename ValueType>
    void QuickMap<KeyType, ValueType>::addBucket(CellT* chain)
    {
        // We add each cell by using the recursive method addCell().
        CellT* cur = chain;
        while(cur != nullptr) {
            addCell(cur);
            cur = cur->link;
        }
    }
    
    template <typename KeyType, typename ValueType>
    void QuickMap<KeyType, ValueType>::addCell(CellT* cell)
    {
        int index = mHashFunc(cell->key) % mNumBuckets;
        cell->link = mBuckets[index];
        mBuckets[index] = cell;
    }
    
    template <typename KeyType, typename ValueType>
    typename QuickMap<KeyType, ValueType>::iterator QuickMap<KeyType, ValueType>::begin()
    {
        iterator it(mBuckets, mNumBuckets, mBuckets[0], mHashFunc);
        while (!it.isValid()) it++;
        return it;
    }
    
    template <typename KeyType, typename ValueType>
    typename QuickMap<KeyType, ValueType>::const_iterator QuickMap<KeyType, ValueType>::begin() const
    {
        return const_iterator(const_cast<QuickMap<KeyType, ValueType>*>(this)->begin());
    }
    
    template <typename KeyType, typename ValueType>
    typename QuickMap<KeyType, ValueType>::const_iterator QuickMap<KeyType, ValueType>::end() const
    {
        return const_iterator(mBuckets, mNumBuckets, nullptr, mHashFunc);
    }
    
    template <typename KeyType, typename ValueType>
    bool QuickMap<KeyType, ValueType>::iterator::operator == (QuickMap<KeyType, ValueType>::const_iterator& cit) const
    {
    	return mCell == cit.mCell;
    }
    
    template <typename KeyType, typename ValueType>
    bool QuickMap<KeyType, ValueType>::iterator::operator != (QuickMap<KeyType, ValueType>::const_iterator& cit) const
    {
    	return mCell != cit.mCell;
    }
}

#endif
