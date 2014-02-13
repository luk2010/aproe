/////////////////////////////////////////////////////////////
/** @file DynamicLibrary.cpp
 *  @ingroup Core
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 18/09/2012 - 06/02/2014
 *
 *  Implements the DynamicLibrary class.
 *
**/
/////////////////////////////////////////////////////////////
#include "DynamicLibrary.h"
#include "Console.h"

namespace APro
{
    DynamicLibrary::DynamicLibrary()
        : Resource()
    {
        loaded.set(false);
        handle = nullptr;
    }

    DynamicLibrary::DynamicLibrary(const String& mfilename)
        : Resource(mfilename)
    {
        loaded.set(false);
        handle = nullptr;
        load();
    }

    DynamicLibrary::~DynamicLibrary()
    {
        unload();
    }

    void* DynamicLibrary::getSymbol(const char* sym)
    {
        if(isLoaded())
        {
            return (void*) DYNLIB_GETSYM(handle, sym);
        }

        return nullptr;
    }

    bool DynamicLibrary::load()
    {
        if(isLoaded())
            return true;

        APRO_THREADSAFE_AUTOLOCK

        handle = DYNLIB_LOAD(getFilename().toCstChar());
        if(!handle)
        {
            Console::get() << "\n[DynamicLibrary] Couldn't load DynLib " << getFilename() << " : " << DYNLIB_LASTERROR() << ".";
            loaded.set(false);
            return false;
        }
        else
        {
            sendEvent(createEvent(DynamicLibraryLoadedEvent::Hash));
            Console::get() << "\n[DynamicLibrary] DynLib " << getFilename() << " loaded successfuly.";
            loaded.set(true);
            return true;
        }
    }

    bool DynamicLibrary::unload()
    {
        if(!isLoaded())
            return true;

        APRO_THREADSAFE_AUTOLOCK

        sendEvent(createEvent(DynamicLibraryUnloadedEvent::Hash));
        if(!DYNLIB_UNLOAD(handle))
        {
            Console::get() << "\n[DynamicLibrary] Couldn't release DynLib " << getFilename() << " : " << DYNLIB_LASTERROR() << ".";
            loaded.set(false);
            return false;
        }
        else
        {
            Console::get() << "\n[DynamicLibrary] DynLib " << getFilename() << " unloaded successfuly.";
            loaded.set(false);
            return true;
        }
    }

    bool DynamicLibrary::isLoaded() const
    {
        return loaded.get();
    }

    EventPtr DynamicLibrary::createEvent(const HashType& e_type) const
    {
        switch (e_type)
        {
        case DynamicLibraryLoadedEvent::Hash:
            EventPtr ret = (Event*) AProNew(DynamicLibraryLoadedEvent);
            ret->m_emitter = this;
            return ret;

        case DynamicLibraryUnloadedEvent::Hash:
            EventPtr ret = (Event*) AProNew(DynamicLibraryUnloadedEvent);
            ret->m_emitter = this;
            return ret;

        default:
            return EventEmitter::createEvent(e_type);
        }
    }
}
