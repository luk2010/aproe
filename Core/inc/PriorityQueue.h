/////////////////////////////////////////////////////////////
/** @file PriorityQueue.h
 *  @ingroup Utils
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 01/03/2015
 *
 *  @brief
 *  Defines a Queue sorted by Priority.
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
#ifndef APRO_PRIORITYQUEUE_H
#define APRO_PRIORITYQUEUE_H

#include "Platform.h"
#include "List.h"

#include "BaseObject.h"
#include "Swappable.h"

namespace APro
{
    /////////////////////////////////////////////////////////////
    /** @class PriorityQueue
     *  @ingroup Utils
     *  @brief Represents a Queue with its elements sorted by 
     *  priority levels.
     *
     *  @note
     *  About the Implementation : The PriorityQueue is implemented
     *  using a simple List container. Adding and object to the queue
     *  is so very quick, but the cost of this operation depends
     *  on the number of Elements having a lesser priority than
     *  the added Element.
     *  If you don't care about the data size, you can use 
     *  QueuedPriorityQueue, which use multiple Queues for each
     *  PriorityLevel.
     *
     *  @note
     *  The PriorityLevel should not be superior or inferior to 
     *  PriorityLevelMax and PriorityLevelMin .
     *
     *  @see QueuedPriorityQueue
    **/
    /////////////////////////////////////////////////////////////
    template<typename ElementType>
    class PriorityQueue
        : public BaseObject<PriorityQueue<ElementType> >,
          public Swappable<PriorityQueue<ElementType> >
    {
    public:
        
        /////////////////////////////////////////////////////////////
        /** @brief Priority levels.
        **/
        /////////////////////////////////////////////////////////////
        enum PriorityLevel
        {
            PriorityLevelMin    = 0,
            PriorityLevelNormal = 50,
            PriorityLevelMax    = 100
        };
        
    private:
        
        struct ElementCell
        {
            uint32_t    priority;
            ElementType element;
        };
        
    public:
        
        /////////////////////////////////////////////////////////////
        /** @brief Constructs a PriorityQueue.
         *
         *  @param maxPriorityLevel : The Max Priority Level the pushed
         *  objects can reach. If an object is pushed with a higher
         *  priority, the Priority Level will be clamped to the Max one
         *  of this Queue.
         * 
         *  @param minPriorityLevel : The Min Priority Level the pushed
         *  objects can reach. If an object is pushed with a lesser
         *  priority, the Priority Level will be clamped to the Min one
         *  of this Queue.
        **/
        /////////////////////////////////////////////////////////////
        PriorityQueue(uint32_t maxPriorityLevel = PriorityLevelMax, uint32_t minPriorityLevel = PriorityLevelMin);
        
        /////////////////////////////////////////////////////////////
        /** @brief Copies given PriorityQueue.
        **/
        /////////////////////////////////////////////////////////////
        PriorityQueue(const PriorityQueue<ElementType>& rhs);
        
        /////////////////////////////////////////////////////////////
        /** @brief Moves given PriorityQueue.
         **/
        /////////////////////////////////////////////////////////////
        PriorityQueue(PriorityQueue<ElementType>&& rhs);
        
        /////////////////////////////////////////////////////////////
        /** @brief Destroys the PriorityQueue and all its objects.
         **/
        /////////////////////////////////////////////////////////////
        ~PriorityQueue();
        
    public:
        
        /////////////////////////////////////////////////////////////
        /** @brief Adds an element in the PriorityQueue, according
         *  to its given PriorityLevel.
        **/
        /////////////////////////////////////////////////////////////
        void push(const ElementType& object, uint32_t priority = PriorityLevelNormal);
        
        /////////////////////////////////////////////////////////////
        /** @brief Removes the last element in the PriorityQueue.
         *
         *  @note
         *  This object is not returned, and so is lost forever if you
         *  pop it before doing any copy (or move).
        **/
        /////////////////////////////////////////////////////////////
        void pop();
        
        /////////////////////////////////////////////////////////////
        /** @brief Destroys every Elements in the PriorityQueue.
        **/
        /////////////////////////////////////////////////////////////
        void clear();
        
        /////////////////////////////////////////////////////////////
        /** @brief Returns the size of the PriorityQueue.
        **/
        /////////////////////////////////////////////////////////////
        uint32_t size() const;
        
        /////////////////////////////////////////////////////////////
        /** @brief Returns true if the PriorityQueue is empty.
        **/
        /////////////////////////////////////////////////////////////
        bool isEmpty() const;
        
        /////////////////////////////////////////////////////////////
        /** @brief Returns the last Element contained in this 
         *  PriorityQueue.
        **/
        /////////////////////////////////////////////////////////////
        ElementType& get();
        
        /////////////////////////////////////////////////////////////
        /** @brief Returns the last Element contained in this
         *  PriorityQueue.
        **/
        /////////////////////////////////////////////////////////////
        const ElementType& get() const;
        
        /////////////////////////////////////////////////////////////
        /** @brief Returns the last element and destroys it.
         *
         *  @note
         *  As this method makes two copies (or moves) of the given 
         *  element, you may used PriorityQueue::get() and PriorityQueue::pop()
         *  separately in your program to avoid using this costly 
         *  function.
        **/
        /////////////////////////////////////////////////////////////
        ElementType popg();
        
    public:
        
        ////////////////////////////////////////////////////////////
        /** @brief Swap this object with another one from the same
         *  kind.
        **/
        ////////////////////////////////////////////////////////////
        void swap(PriorityQueue<ElementType>& obj);
        
    private:
        
        uint32_t          mMaxPriority;
        uint32_t          mMinPriority;
        List<ElementCell> mElements;
    };
    
    template<typename ElementType>
    PriorityQueue<ElementType>::PriorityQueue(uint32_t maxPriorityLevel, uint32_t minPriorityLevel)
    {
        using std::swap;
        
        mMaxPriority = maxPriorityLevel;
        mMinPriority = minPriorityLevel;
        
        if(mMinPriority > mMaxPriority) {
            swap(mMaxPriority, mMinPriority);
        }
    }
    
    template<typename ElementType>
    PriorityQueue<ElementType>::PriorityQueue(const PriorityQueue<ElementType>& rhs)
    {
        mMinPriority = rhs.mMinPriority;
        mMaxPriority = rhs.mMaxPriority;
        mElements    = rhs.mElements;
    }
    
    template<typename ElementType>
    PriorityQueue<ElementType>::PriorityQueue(PriorityQueue<ElementType>&& rhs)
        : mElements(std::move(rhs.mElements))
    {
        using std::swap;
        
        mMinPriority = 0;
        mMaxPriority = 0;
        
        swap(mMinPriority, rhs.mMinPriority);
        swap(mMaxPriority, rhs.mMaxPriority);
    }
    
    template<typename ElementType>
    PriorityQueue<ElementType>::~PriorityQueue()
    {
        mElements.clear();
    }
    
    template<typename ElementType>
    void PriorityQueue<ElementType>::push(const ElementType& object, uint32_t priority)
    {
        if(priority < mMinPriority)
            priority = mMinPriority;
        if(priority > mMaxPriority)
            priority = mMaxPriority;
        
        for(uint32_t i = 0; i < mElements.size(); ++i)
        {
            if(mElements[i].priority >= priority) {
                mElements.insert(mElements.begin() + i, {object, priority});
                return;
            }
        }
        
        mElements.append({object, priority});
    }
    
    template<typename ElementType>
    ElementType PriorityQueue<ElementType>::pop()
    {
        ElementType ret = *(mElements.last());
        mElements.erase(mElements.last());
        return ret;
    }
    
    template<typename ElementType>
    void PriorityQueue<ElementType>::clear()
    {
        mElements.clear();
    }
    
    template<typename ElementType>
    uint32_t PriorityQueue<ElementType>::size() const
    {
        mElements.size();
    }
    
    template<typename ElementType>
    bool PriorityQueue<ElementType>::isEmpty() const
    {
        mElements.isEmpty();
    }
    
    template<typename ElementType>
    ElementType& PriorityQueue<ElementType>::get()
    {
        return *(mElements.last());
    }
    
    template<typename ElementType>
    const ElementType& PriorityQueue<ElementType>::get() const
    {
        return *(mElements.last());
    }
    
    template<typename ElementType>
    ElementType& PriorityQueue<ElementType>::popg()
    {
        ElementType ret = get();
        pop();
        return ret;
    }
    
    template<typename ElementType>
    void PriorityQueue<ElementType>::swap(PriorityQueue<ElementType>& obj)
    {
        using std::swap;
        swap(mMinPriority, obj.mMinPriority);
        swap(mMaxPriority, obj.mMaxPriority);
        swap(mElements,    obj.mElements);
    }
}


#endif
