/////////////////////////////////////////////////////////////
/** @file PointerCollector.cpp
 *  @ingroup Memory
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 02/07/2013 - 17/06/2014
 *
 *  Implements the PointerCollector class.
 *
**/
/////////////////////////////////////////////////////////////
#include "PointerCollector.h"
#include "Console.h"

namespace APro
{
    APRO_IMPLEMENT_MANUALSINGLETON(PointerCollector)

    PointerCollector::PointerCollector(const String& collector_name)
        : name(collector_name)
    {
 //       pointers_utility.reserve(100);
    }

    PointerCollector::~PointerCollector()
    {

    }

    void PointerCollector::push(void* ptr)
    {
        APRO_THREADSAFE_AUTOLOCK

        if(!pointers_utility.keyExists(ptr))
            pointers_utility[ptr] = 1;
        else
            pointers_utility[ptr]++;
    }

    void PointerCollector::pop(void* ptr)
    {
        APRO_THREADSAFE_AUTOLOCK

        if(!pointers_utility.keyExists(ptr))
        {
            Console::Get() << "\n[PointerCollector] Collector \"" << name << "\" couldn't pop unexistant pointer \"" << (intptr_t) ptr << "\".";
        }
        else
            pointers_utility[ptr] = (pointers_utility[ptr] == 0) ? 0 : pointers_utility[ptr]--;
    }

    void PointerCollector::remove(void* ptr)
    {
        APRO_THREADSAFE_AUTOLOCK

        if(pointers_utility.keyExists(ptr))
        {
            pointers_utility.erase(ptr);
        }
    }

    bool PointerCollector::exists(void* ptr) const
    {
        APRO_THREADSAFE_AUTOLOCK
        return pointers_utility.keyExists(ptr);
    }

    size_t PointerCollector::getPointersCollected() const
    {
        APRO_THREADSAFE_AUTOLOCK
        return pointers_utility.size();
    }

    unsigned int PointerCollector::getPointerUtility(void* ptr) const
    {
        APRO_THREADSAFE_AUTOLOCK
        return pointers_utility.keyExists(ptr) ? 0 : pointers_utility[ptr];
    }

    const String& PointerCollector::getName() const
    {
        APRO_THREADSAFE_AUTOLOCK
        return name;
    }
}
