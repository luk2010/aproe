/////////////////////////////////////////////////////////////
/** @file QueuedPriorityQueue.h
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
#ifndef APRO_QUEUEDPRIORITYQUEUE_H
#define APRO_QUEUEDPRIORITYQUEUE_H

#include "Platform.h"
#include "Queue.h"

#include "BaseObject.h"
#include "Swappable.h"

namespace APro
{
    /////////////////////////////////////////////////////////////
    /** @class QueuedPriorityQueue
     *  @ingroup Utils
     *  @brief Represents a Queue with its elements sorted by
     *  priority levels.
     *
     *  @note
     *  About the Implementation : The QueuedPriorityQueue is implemented
     *  using multiples Queues. Each Queue define a PriorityLevel. 
     *  This allows to push Objects much more quickly than PriorityQueue, 
     *  but at the cost of data size.
     *
     *  @see PriorityQueue
     **/
    /////////////////////////////////////////////////////////////
    template<typename ElementType>
    class QueuedPriorityQueue
        : public BaseObject<QueuedPriorityQueue<ElementType> >,
          public Swappable<QueuedPriorityQueue<ElementType> >
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
        
    public:
        
        /////////////////////////////////////////////////////////////
        /** @brief Constructs a QueuedPriorityQueue.
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
        QueuedPriorityQueue(uint32_t maxPriorityLevel = PriorityLevelMax, uint32_t minPriorityLevel = PriorityLevelMin);
        
        /////////////////////////////////////////////////////////////
        /** @brief Copies given QueuedPriorityQueue.
         **/
        /////////////////////////////////////////////////////////////
        QueuedPriorityQueue(const QueuedPriorityQueue<ElementType>& rhs);
        
        /////////////////////////////////////////////////////////////
        /** @brief Moves given QueuedPriorityQueue.
         **/
        /////////////////////////////////////////////////////////////
        QueuedPriorityQueue(QueuedPriorityQueue<ElementType>&& rhs);
        
        /////////////////////////////////////////////////////////////
        /** @brief Destroys the QueuedPriorityQueue and all its elements.
        **/
        /////////////////////////////////////////////////////////////
        ~QueuedPriorityQueue();
        
    public:
        
        /////////////////////////////////////////////////////////////
        /** @brief Adds an element in the QueuedPriorityQueue, according
         *  to its given PriorityLevel.
        **/
        /////////////////////////////////////////////////////////////
        void push(const ElementType& element, uint32_t priority = PriorityLevelNormal);
        
        /////////////////////////////////////////////////////////////
        /** @brief Removes the last element in the QueuedPriorityQueue.
         *
         *  @note
         *  This object is not returned, and so is lost forever if you
         *  pop it before doing any copy (or move).
         **/
        /////////////////////////////////////////////////////////////
        void pop();
        
        /////////////////////////////////////////////////////////////
        /** @brief Destroys every Elements in the QueuedPriorityQueue.
        **/
        /////////////////////////////////////////////////////////////
        void clear();
        
        /////////////////////////////////////////////////////////////
        /** @brief Returns the size of the QueuedPriorityQueue.
         **/
        /////////////////////////////////////////////////////////////
        uint32_t size() const;
        
        /////////////////////////////////////////////////////////////
        /** @brief Returns true if the QueuedPriorityQueue is empty.
         **/
        /////////////////////////////////////////////////////////////
        bool isEmpty() const;
        
        /////////////////////////////////////////////////////////////
        /** @brief Returns the last Element contained in this
         *  QueuedPriorityQueue.
        **/
        /////////////////////////////////////////////////////////////
        ElementType& get();
        
        /////////////////////////////////////////////////////////////
        /** @brief Returns the last Element contained in this
         *  QueuedPriorityQueue.
        **/
        /////////////////////////////////////////////////////////////
        const ElementType& get() const;
        
    public:
        
        ////////////////////////////////////////////////////////////
        /** @brief Swap this object with another one from the same
         *  kind.
        **/
        ////////////////////////////////////////////////////////////
        void swap(QueuedPriorityQueue<ElementType>& obj);
        
    private:
        
        /////////////////////////////////////////////////////////////
        /** @brief Returns the Number of Queues. 
         *  Result is mMaxPriorityLevel - mMinPriorityLevel + 1.
        **/
        /////////////////////////////////////////////////////////////
        uint32_t getNumQueues() const;
        
        /////////////////////////////////////////////////////////////
        /** @brief Returns the highest non null Queue.
        **/
        /////////////////////////////////////////////////////////////
        Queue<ElementType>* findLastQueue();
        
    private:
        
        uint32_t              mMinPriorityLevel; ///< @brief Min PriorityLevel.
        uint32_t              mMaxPriorityLevel; ///< @brief Max PriorityLevel.
        uint32_t              mNumQueues;        ///< @brief Number of Queues.
        uint32_t              mHighestQueue;     ///< @brief Current Highest Queue Level.
        uint32_t              mSize;             ///< @brief We stores the size here for efficiency.
        Queue<ElementType>**  mQueues;           ///< @brief Priority Queues.
    };
    
    template<typename ElementType>
    QueuedPriorityQueue<ElementType>::QueuedPriorityQueue(uint32_t maxPriorityLevel, uint32_t minPriorityLevel)
    {
        mMinPriorityLevel = minPriorityLevel;
        mMaxPriorityLevel = maxPriorityLevel;
        mNumQueues        = getNumQueues();
        mHighestQueue     = 0;
        mSize             = 0;
        
        mQueues = AProNewA(mNumQueues, Queue<ElementType>*);
        for(unsigned int i = 0; i < mNumQueues; ++i) {
            mQueues[i] = nullptr;
        }
    }
    
    template<typename ElementType>
    QueuedPriorityQueue<ElementType>::QueuedPriorityQueue(const QueuedPriorityQueue<ElementType>& rhs)
    {
        mMinPriorityLevel = rhs.mMinPriorityLevel;
        mMaxPriorityLevel = rhs.mMaxPriorityLevel;
        mNumQueues        = rhs.mNumQueues;
        mHighestQueue     = rhs.mHighestQueue;
        mSize             = rhs.mSize;
        
        mQueues = AProNewA(mNumQueues, Queue<ElementType>*);
        for(unsigned int i = 0; i < mNumQueues; ++i) {
            if(rhs.mQueues[i] != nullptr) {
                mQueues[i] = AProNew(Queue<ElementType>, *(rhs.mQueues[i]));
            }
            else {
                mQueues[i] = nullptr;
            }
        }
    }
    
    template<typename ElementType>
    QueuedPriorityQueue<ElementType>::QueuedPriorityQueue(QueuedPriorityQueue<ElementType>&& rhs)
    {
        mMinPriorityLevel = 0;
        mMaxPriorityLevel = 0;
        mNumQueues        = 0;
        mHighestQueue     = 0;
        mQueues           = 0;
        mSize             = 0;
        
        using std::swap;
        swap(mMinPriorityLevel, rhs.mMinPriorityLevel);
        swap(mMaxPriorityLevel, rhs.mMaxPriorityLevel);
        swap(mNumQueues,        rhs.mNumQueues);
        swap(mHighestQueue,     rhs.mHighestQueue);
        swap(mQueues,           rhs.mNumQueues);
        swap(mSize,             rhs.mSize);
    }
    
    template<typename ElementType>
    QueuedPriorityQueue<ElementType>::~QueuedPriorityQueue()
    {
        if(mNumQueues > 0)
        {
            for(unsigned int i = 0; i < mNumQueues; ++i)
            {
                if(mQueues[i] != nullptr) {
                    AProDelete(mQueues[i]);
                }
            }
            
            AProDelete(mQueues);
        }
    }
    
    template<typename ElementType>
    void QueuedPriorityQueue<ElementType>::push(const ElementType& element, uint32_t priority)
    {
        if(priority > mMaxPriorityLevel)
            priority = mMaxPriorityLevel;
        if(priority < mMinPriorityLevel)
            priority = mMinPriorityLevel;
        
        priority = priority - mMinPriorityLevel;
        
        if(mQueues[priority] == nullptr) {
            mQueues[priority] = AProNew(Queue<ElementType>);
        }
        
        mQueues[priority].push(element);
        mSize = mSize + 1;
        
        if(priority > mHighestQueue)
            mHighestQueue = priority;
    }
    
    template<typename ElementType>
    void QueuedPriorityQueue<ElementType>::pop()
    {
        Queue<ElementType>* curQueue = findLastQueue();
        if(curQueue == nullptr)
            return;
        
        curQueue->pop();
        mSize = mSize - 1;
        
        if(curQueue->isEmpty()) {
            AProDelete(curQueue);
            mQueues[mHighestQueue] = nullptr;
            
            if(mHighestQueue > 0)
                mHighestQueue = mHighestQueue - 1;
        }
    }
    
    template<typename ElementType>
    void QueuedPriorityQueue<ElementType>::clear()
    {
        if(mNumQueues > 0)
        {
            for(unsigned int i = 0; i < mNumQueues; ++i)
            {
                if(mQueues[i] != nullptr) {
                    AProDelete(mQueues[i]);
                    mQueues[i] = nullptr;
                }
            }
        }
        
        mNumQueues    = 0;
        mHighestQueue = 0;
        mSize         = 0;
    }
    
    template<typename ElementType>
    uint32_t QueuedPriorityQueue<ElementType>::size() const
    {
        return mSize;
    }
    
    template<typename ElementType>
    bool QueuedPriorityQueue<ElementType>::isEmpty() const
    {
        return mSize == 0;
    }
    
    template<typename ElementType>
    ElementType& QueuedPriorityQueue<ElementType>::get()
    {
        Queue<ElementType>* curQueue = findLastQueue();
        aproassert1(curQueue != nullptr);
        
        return curQueue->get();
    }
    
    template<typename ElementType>
    const ElementType& QueuedPriorityQueue<ElementType>::get() const
    {
        return const_cast<QueuedPriorityQueue<ElementType>*>(this)->get();
    }
    
    template<typename ElementType>
    void QueuedPriorityQueue<ElementType>::swap(QueuedPriorityQueue<ElementType>& obj)
    {
        using std::swap;
        swap(mMinPriorityLevel, obj.mMinPriorityLevel);
        swap(mMaxPriorityLevel, obj.mMaxPriorityLevel);
        swap(mNumQueues,        obj.mNumQueues);
        swap(mHighestQueue,     obj.mHighestQueue);
        swap(mSize,             obj.mSize);
        swap(mQueues,           obj.mQueues);
    }
    
    template<typename ElementType>
    uint32_t QueuedPriorityQueue<ElementType>::getNumQueues() const
    {
        return (mMaxPriorityLevel - mMinPriorityLevel) + 1;
    }
    
    template<typename ElementType>
    Queue<ElementType>* QueuedPriorityQueue<ElementType>::findLastQueue()
    {
        Queue<ElementType>* curQueue = mQueues[mHighestQueue];
        
        if(curQueue == nullptr && mHighestQueue == 0)
            return nullptr;
        
        if(curQueue == nullptr) {
            // We look for a valid queue.
            while(curQueue == nullptr && mHighestQueue != 0)
            {
                mHighestQueue = mHighestQueue - 1;
                curQueue = mQueues[mHighestQueue];
            }
            
            if(curQueue == nullptr)
                return nullptr;
        }
        
        return curQueue;
    }
}


#endif // APRO_QUEUEDPRIORITYQUEUE_H
