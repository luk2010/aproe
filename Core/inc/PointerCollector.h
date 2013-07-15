////////////////////////////////////////////////////////////
/** @file PointerCollector.h
 *  @ingroup Memory
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 02/07/2013
 *
 *  Defines the PointerCollector class.
 *
**/
////////////////////////////////////////////////////////////
#ifndef APRO_POINTER_COLLECTOR_H
#define APRO_POINTER_COLLECTOR_H

#include "Platform.h"
#include "SString.h"
#include "Map.h"
#include "ThreadSafe.h"

namespace APro
{
    ////////////////////////////////////////////////////////////
    /** @class PointerCollector
     *  @ingroup Memory
     *  @brief Collects pointers and tell how many use they have.
     *  @details This class can is used by SharedPointers to push
     *  and pop shared adresses.
     *  You can create your own to collect custom pointers.
     *
     *  @warning
     *  The PointerCollector NEVER deletes the pointers it has.
    **/
    ////////////////////////////////////////////////////////////
    class APRO_DLL PointerCollector : public ThreadSafe
    {
    private:

        String name;///< Name of the collector.
        Map<void*, unsigned int> pointers_utility;///< Map of pointers with their utility.

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
        ~PointerCollector();


        ////////////////////////////////////////////////////////////
        /** @brief Push a pointer use, or a new pointer if it doesn't
         *  already exists.
         *
         *  @param ptr : Pointer to push.
        **/
        ////////////////////////////////////////////////////////////
        void push(void* ptr);

        ////////////////////////////////////////////////////////////
        /** @brief Pop a pointer use, or send an error if no pointer
         *  were registered.
         *
         *  @param ptr : Pointer to pop.
        **/
        ////////////////////////////////////////////////////////////
        void pop(void* ptr);

        ////////////////////////////////////////////////////////////
        /** @brief remove given pointer to the entries.
         *  @note Used by SharedPointer when it deletes the pointer
         *  because of last entry.
        **/
        ////////////////////////////////////////////////////////////
        void remove(void* ptr);

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Tell if given pointer adress is registered.
        **/
        ////////////////////////////////////////////////////////////
        bool exists(void* ptr) const;

        ////////////////////////////////////////////////////////////
        /** @brief Return the number of registered pointers.
        **/
        ////////////////////////////////////////////////////////////
        size_t getPointersCollected() const;

        ////////////////////////////////////////////////////////////
        /** @brief Return the uses of a given pointer.
        **/
        ////////////////////////////////////////////////////////////
        unsigned int getPointerUtility(void* ptr) const;

        ////////////////////////////////////////////////////////////
        /** @brief Return the name of this collector.
        **/
        ////////////////////////////////////////////////////////////
        const String& getName() const;
    };
}

#endif // APRO_POINTER_COLLECTOR_H