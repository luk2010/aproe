////////////////////////////////////////////////////////////
/** @file PointerCollector.h
 *  @ingroup Memory
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 02/07/2013 - 26/12/2014
 *
 *  @brief
 *  Defines the PointerCollector class.
 *
 *  @copyright
 *  Atlanti's Project Engine
 *  Copyright (C) 2012 - 2014  Atlanti's Corp
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
////////////////////////////////////////////////////////////
#ifndef APRO_POINTER_COLLECTOR_H
#define APRO_POINTER_COLLECTOR_H

#include "Platform.h"
#include "Singleton.h"
#include "SString.h"
#include "Map.h"
#include "ThreadSafe.h"

namespace APro
{
    ////////////////////////////////////////////////////////////
    /** @class PointerCollector
     *  @ingroup Memory
     *  @brief Collects pointers and tell how many use they have.
     *  
     *  This class is used by SharedPointers to push and pop shared 
     *  adresses.
     *  You can create your own to collect custom pointers.
     *
     *  @warning
     *  The PointerCollector NEVER deletes the pointers it has.
    **/
    ////////////////////////////////////////////////////////////
    class APRO_DLL PointerCollector : public ThreadSafe
    {
    public:
        APRO_DECLARE_MANUALSINGLETON(PointerCollector)

    private:

        String name;                              ///< @brief Name of the collector.
        Map<void*, unsigned int> pointers_utility;///< @brief Map of pointers with their utility.

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Constructor.
         *
         *  @param collector_name : Name of the collector to create.
        **/
        ////////////////////////////////////////////////////////////
        PointerCollector(const String& collector_name);

        ////////////////////////////////////////////////////////////
        /** @brief Destructor.
        **/
        ////////////////////////////////////////////////////////////
        virtual ~PointerCollector();


        ////////////////////////////////////////////////////////////
        /** @brief Push a pointer use, or a new pointer if it doesn't
         *  already exists.
         *
         *  @param ptr : Pointer to push.
        **/
        ////////////////////////////////////////////////////////////
        virtual void push(void* ptr);

        ////////////////////////////////////////////////////////////
        /** @brief Pop a pointer use, or send an error if no pointer
         *  were registered.
         *
         *  @param ptr : Pointer to pop.
        **/
        ////////////////////////////////////////////////////////////
        virtual void pop(void* ptr);

        ////////////////////////////////////////////////////////////
        /** @brief remove given pointer to the entries.
         *  @note Used by SharedPointer when it deletes the pointer
         *  because of last entry.
        **/
        ////////////////////////////////////////////////////////////
        virtual void remove(void* ptr);

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Tell if given pointer adress is registered.
        **/
        ////////////////////////////////////////////////////////////
        virtual bool exists(void* ptr) const;
        
        ////////////////////////////////////////////////////////////
        /** @brief Returns true if the given pointer is still present
         *  in the pointer database.
         *  @see exists
        **/
        ////////////////////////////////////////////////////////////
        bool isValid(void* pointer) const { return exists(pointer); }

        ////////////////////////////////////////////////////////////
        /** @brief Return the number of registered pointers.
        **/
        ////////////////////////////////////////////////////////////
        virtual size_t getPointersCollected() const;

        ////////////////////////////////////////////////////////////
        /** @brief Return the uses of a given pointer.
        **/
        ////////////////////////////////////////////////////////////
        virtual unsigned int getPointerUtility(void* ptr) const;

        ////////////////////////////////////////////////////////////
        /** @brief Return the name of this collector.
        **/
        ////////////////////////////////////////////////////////////
        virtual const String& getName() const;
    };
}

#endif // APRO_POINTER_COLLECTOR_H
