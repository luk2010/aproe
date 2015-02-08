/////////////////////////////////////////////////////////////
/** @file Base.h
 *  @ingroup Utils
 *  @brief Defines the BaseObject class.
 *
 *  @author Luk2010
 *  @date 30/11/2014 - 03/02/2015
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
 **/
////////////////////////////////////////////////////////////
#ifndef APRO_BASEOBJECT_H
#define APRO_BASEOBJECT_H

#include "Platform.h"
#include "Memory.h"

namespace APro
{
    ////////////////////////////////////////////////////////////
    /** @enum AllocatorPool
     *  @ingroup Memory
     *  @brief A class-enum for Pools number.
    **/
    ////////////////////////////////////////////////////////////
    enum class AllocatorPool {
        Default = 0 ///< @brief The default Pool. Every Base Object
        ///< set the Pool to this one if you don't set one
        ///< in your subclass.
    };
    
    ////////////////////////////////////////////////////////////
    /** @class Allocator
     *  @ingroup Memory
     *  @brief A helper class to allocate Base Objects into correct
     *  Memory Pools. 
     *
     *  This class is used by Base Object to allocate memory space
     *  for their class.
     *  The Pool Number is defined by the class to distribute 
     *  resources and memory allocations through the Engine.
    **/
    ////////////////////////////////////////////////////////////
    template<AllocatorPool PoolNum>
    class APRO_DLL Allocator
    {
    public:
        
        ////////////////////////////////////////////////////////////
        /** @brief Return the Current Allocator for given Pool.
        **/
        ////////////////////////////////////////////////////////////
        static Allocator& Get() {
            static Allocator a;
            return a;
        }
        
        ////////////////////////////////////////////////////////////
        /** @brief Creates a new number of Objects. 
         *
         *  Those objects are created using the correct AProNew 
         *  function (if you create more than 1 object at the same
         *  time, it will create an array using AProNewA and so the
         *  returned pointer will habe to be freed in one time.)
         *
         *  @note
         *  If you have set a maximum size for the pool, the returned
         *  pointer can be null if this limit is reached. 
         *
         *  @param num : Number of objects to create. 
         *  
         *  @see ::New(), ::Delete()
        **/
        ////////////////////////////////////////////////////////////
        template<typename T>
        T* New (size_t num) {
            if(num > 1) {
                if (m_cursize + sizeof(T)*num < m_maxsize || m_maxsize == 0) {
                    m_cursize += sizeof(T)*num;
                    return AProNewA(T, num);
                }
                return nullptr;
            }
            else {
                if (m_cursize + sizeof(T) < m_maxsize || m_maxsize == 0) {
                    m_cursize += sizeof(T);
                    return AProNew(T);
                }
                return nullptr;
            }
        }
        
        ////////////////////////////////////////////////////////////
        /** @brief Creates a new number of Objects and give the correct
         *  constructor arguments.
         *
         *  Those objects are created using the correct AProNew
         *  function (if you create more than 1 object at the same
         *  time, it will create an array using AProNewA and so the
         *  returned pointer will habe to be freed in one time.)
         *
         *  Thanks to C++11 variadic template arguments, we can pass
         *  correct argues to the constructor (with std::forward() ).
         *  This method enable us using the correct placement new function
         *  with our own AProNew method.
         *
         *  @note
         *  If you have set a maximum size for the pool, the returned
         *  pointer can be null if this limit is reached.
         *
         *  @param num : Number of objects to create.
         *  @param args : Argues to the constructor.
         *
         *  @see ::New(), ::Delete()
         **/
        ////////////////////////////////////////////////////////////
        template<typename T, typename ...Args>
        T* New (size_t num, Args&&... args) {
            if(num >= 2) {
                if (m_cursize + sizeof(T) * num < m_maxsize || m_maxsize == 0) {
                    m_cursize += sizeof(T) * num;
                    return AProNewA (T, num, std::forward<Args>(args)...);
                }
                
                return nullptr;
            }
            else {
                if (m_cursize + sizeof(T) < m_maxsize || m_maxsize == 0) {
                    m_cursize += sizeof(T);
                    return AProNew (T, std::forward<Args>(args)...);
                }
                
                return nullptr;
            }
        }
        
        ////////////////////////////////////////////////////////////
        /** @brief Delete an object in the Pool. 
        **/
        ////////////////////////////////////////////////////////////
        template<typename T>
        void Delete(T* obj) {
            if (obj) {
                size_t sz = Memory::GetBlockSize(obj);
                if(sz > 0) {
                    AProDelete(obj);
                    m_cursize -= sz;
                }
            }
        }
        
    private:
        ////////////////////////////////////////////////////////////
        /** @brief Construct a basic Allocator object.
        **/
        ////////////////////////////////////////////////////////////
        Allocator() : m_maxsize(0), m_cursize(0) { }
        
    public:
        
        ////////////////////////////////////////////////////////////
        /** @brief Sets the maximum size of this pool allocator, in
         *  bytes. 
         *  
         *  @note
         *  In case you do not set a limit, then allocate some objects, 
         *  then set a limit which is inferior to current size, you 
         *  will not be able to allocate new objects untill the correct
         *  size is reached, and the overflow flag will be true.
        **/
        ////////////////////////////////////////////////////////////
        void setMaxSize(long sz) { m_maxsize = sz; }
        
        ////////////////////////////////////////////////////////////
        /** @brief Returns the pool used by this Allocator.
        **/
        ////////////////////////////////////////////////////////////
        AllocatorPool getPool() const { return PoolNum; }
        
        ////////////////////////////////////////////////////////////
        /** @brief Returns the maximum size this Allocator can 
         *  allocate.
        **/
        ////////////////////////////////////////////////////////////
        uint64_t getMaximumSize() const { return m_maxsize; }
        
        ////////////////////////////////////////////////////////////
        /** @brief Returns the current size this allocator is 
         *  allocating.
        **/
        ////////////////////////////////////////////////////////////
        uint64_t getCurrentSize() const { return m_cursize; }
        
        ////////////////////////////////////////////////////////////
        /** @brief Returns true if an Overflow is happening.
         *  @see ::setMaxSize().
        **/
        ////////////////////////////////////////////////////////////
        bool isOverflowed() const { return m_cursize > m_maxsize; }
        
    private:
        uint64_t m_maxsize;
        uint64_t m_cursize;
    };
    
    ////////////////////////////////////////////////////////////
    /** @class BaseObject
     *  @ingroup Core
     *  @brief A Basic Object registered in the Engine.
     *
     *  A Basic Object has certain functionnality, like having 
     *  the Class::New() and Class::Delete() system. 
     *  You also can stores them in different Memory Pools.
    **/
    ////////////////////////////////////////////////////////////
    template <typename T, AllocatorPool PoolNum = AllocatorPool::Default>
    class APRO_DLL BaseObject : public BaseObjectTrait
    {
	public:
		
		typedef Allocator<PoolNum> PooledAllocator;
		
    public:
        
        ////////////////////////////////////////////////////////////
        /** @brief Allocates a new object with default constructor.
        **/
        ////////////////////////////////////////////////////////////
        static T* New() {
            return Allocator<PoolNum>::Get().New<T>(1);
        }
        
        ////////////////////////////////////////////////////////////
        /** @brief Allocates a new object using given argues.
        **/
        ////////////////////////////////////////////////////////////
        template <typename ...Args>
        static T* New(Args&&... args) {
            return Allocator<PoolNum>::Get().New<T>(1, std::forward<Args>(args)...);
        }
        
        ////////////////////////////////////////////////////////////
        /** @brief Allocates new objects using given argues.
         **/
        ////////////////////////////////////////////////////////////
        static T* NewA(size_t num) {
            return Allocator<PoolNum>::Get().New<T>(num);
        }
        
        ////////////////////////////////////////////////////////////
        /** @brief Allocates new objects using given argues.
         **/
        ////////////////////////////////////////////////////////////
        template <typename ...Args>
        static T* New(size_t num, Args&&... args) {
            return Allocator<PoolNum>::Get().New<T>(num, std::forward<Args>(args)...);
        }
        
        ////////////////////////////////////////////////////////////
        /** @brief Delete given object.
         **/
        ////////////////////////////////////////////////////////////
        static void Delete(T* obj) {
            Allocator<PoolNum>::Get().Delete(obj);
        }
        
    public:
        
        ////////////////////////////////////////////////////////////
        /** @brief Returns current AllocatorPool.
         **/
        ////////////////////////////////////////////////////////////
        const AllocatorPool getAllocatorPool () const { return PoolNum; }
    };
}

#endif
