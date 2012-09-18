/** @file DynamicLibrary.cpp
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 18/09/2012
 *
 *  @addtogroup Global
 *  @addtogroup System
 *
 *  This file defines the DynamicLibrary class.
 *
**/
#include "DynamicLibrary.h"
#include "Console.h"

namespace APro
{
    DynamicLibrary::DynamicLibrary()
        : Resource(), loaded(false), handle(nullptr)
    {
        type = String("DynamicLibrary");
    }

    DynamicLibrary::DynamicLibrary(const String& mname, const String& mfilename)
        : Resource(mname, mfilename), loaded(false), handle(nullptr)
    {
        type = String("DynamicLibrary");
        load();
    }

    DynamicLibrary::~DynamicLibrary()
    {

    }

    void DynamicLibrary::destroy()
    {
        unload();
    }

    void* DynamicLibrary::getSymbol(const String& sym) const
    {
        if(loaded)
        {
            return (void*) DYNLIB_GETSYM(handle, sym.toCstChar());
        }

        return nullptr;
    }

    void DynamicLibrary::load()
    {
        if(!loaded)
        {
            handle = DYNLIB_LOAD(getFilename().toCstChar());
            if(!handle)
            {
                Console::get() << "\n[DynamicLibrary] Couldn't load DynLib " << getFilename() << ".";
                loaded = false;
            }
            else
            {
                Console::get() << "\n[DynamicLibrary] DynLib " << getFilename() << " loaded successfuly.";
                loaded = true;
            }
        }
    }

    void DynamicLibrary::unload()
    {
        if(loaded && handle)
        {
            if(! DYNLIB_UNLOAD(handle))
            {
                Console::get() << "\n[DynamicLibrary] Couldn't release DynLib " << getFilename() << ".";
            }
            else
            {
                Console::get() << "\n[DynamicLibrary] DynLib " << getFilename() << " unloaded successfuly.";
                loaded = false;
            }
        }
    }

    bool DynamicLibrary::isLoaded() const
    {
        return loaded;
    }
}
