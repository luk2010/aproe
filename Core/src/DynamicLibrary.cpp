/////////////////////////////////////////////////////////////
/** @file DynamicLibrary.cpp
 *  @ingroup Core
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 18/09/2012 - 22/01/2015
 *
 *  @brief
 *  Implements the DynamicLibrary class.
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
#include "DynamicLibrary.h"
#include "Console.h"

namespace APro
{
    APRO_REGISTER_EVENT_NOCONTENT(DynamicLibraryLoadedEvent);
    APRO_REGISTER_EVENT_NOCONTENT(DynamicLibraryUnloadedEvent);

    DynamicLibrary::DynamicLibrary()
        : Resource()
    {
        loaded.set(false);
        handle = nullptr;

        documentEvent(DynamicLibraryLoadedEvent::Hash,   String("DynamicLibrary has been loaded."));
        documentEvent(DynamicLibraryUnloadedEvent::Hash, String("DynamicLibrary has been unloaded."));
    }

    DynamicLibrary::DynamicLibrary(const String& mfilename)
        : Resource(mfilename)
    {
        loaded.set(false);
        handle = nullptr;

        documentEvent(DynamicLibraryLoadedEvent::Hash,   String("DynamicLibrary has been loaded."));
        documentEvent(DynamicLibraryUnloadedEvent::Hash, String("DynamicLibrary has been unloaded."));
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
            Console::Get() << "\n[DynamicLibrary] Couldn't load DynLib " << getFilename() << " : " << DYNLIB_LASTERROR() << ".";
            loaded.set(false);
            return false;
        }
        else
        {
            sendEvent(createEvent(DynamicLibraryLoadedEvent::Hash));
            Console::Get() << "\n[DynamicLibrary] DynLib " << getFilename() << " loaded successfuly.";
            loaded.set(true);
            return true;
        }
    }

    bool DynamicLibrary::unload()
    {
        if(!isLoaded())
            return true;

        APRO_THREADSAFE_AUTOLOCK

        if(!DYNLIB_UNLOAD(handle))
        {
            Console::Get() << "\n[DynamicLibrary] Couldn't release DynLib " << getFilename() << " : " << DYNLIB_LASTERROR() << ".";
            loaded.set(false);
            return false;
        }
        else
        {
            sendEvent(createEvent(DynamicLibraryUnloadedEvent::Hash));
            Console::Get() << "\n[DynamicLibrary] DynLib " << getFilename() << " unloaded successfuly.";
            loaded.set(false);
            return true;
        }
    }

    bool DynamicLibrary::isLoaded() const
    {
        return loaded.get();
    }

    EventLocalPtr DynamicLibrary::createEvent(const HashType& e_type) const
    {
        if(e_type == DynamicLibraryLoadedEvent::Hash) {
            EventLocalPtr ret((Event*) AProNew(DynamicLibraryLoadedEvent));
            ret->m_emitter = this;
            return ret;
        }

        else if(e_type == DynamicLibraryUnloadedEvent::Hash) {
            EventLocalPtr ret((Event*) AProNew(DynamicLibraryUnloadedEvent));
            ret->m_emitter = this;
            return ret;
        }

        else {
            return EventEmitter::createEvent(e_type);
        }
    }
}
