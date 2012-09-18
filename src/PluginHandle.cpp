/** @file PluginHandle.cpp
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 17/09/2012
 *
 *  @addtogroup Global
 *  @addtogroup System
 *
 *  This file defines the PluginHandle class.
 *
**/
#include "PluginHandle.h"
#include "Console.h"

namespace APro
{
    typedef void (*DLL_START_PLUGIN)(void);
    typedef void (*DLL_END_PLUGIN)(void);
    typedef PluginInfo (*DLL_GET_PLUGININFO)(void);

    PluginHandle::PluginHandle()
        : name(""), dynLib(nullptr)
    {
        info.name = String("");
        info.author = String("");
        info.date = String("");
        info.description = String("");
    }

    PluginHandle::PluginHandle(const String& mname)
        : name(mname), dynLib(nullptr)
    {
        info.name = String("");
        info.author = String("");
        info.date = String("");
        info.description = String("");
    }

    PluginHandle::PluginHandle(const PluginHandle& other)
        : name(""), dynLib(nullptr)
    {
        info.name = String("");
        info.author = String("");
        info.date = String("");
        info.description = String("");
    }

    PluginHandle::PluginHandle(const String& mname, const SharedPointer<DynamicLibrary>& lib)
        : name(mname), dynLib(nullptr)
    {
        initialize(lib);
    }

    PluginHandle::~PluginHandle()
    {
        end();
    }

    void PluginHandle::initialize(const SharedPointer<DynamicLibrary>& lib)
    {
        if(!dynLib.isNull()) end();

        dynLib = lib;
        DLL_START_PLUGIN startPluginFunc = (DLL_START_PLUGIN) dynLib->getSymbol(String("StartPlugin"));
        if(!startPluginFunc)
        {
            Console::get() << "[Plugin] Couldn't find function StartPlugin in library " << dynLib->getName() << ".";
        }
        else
        {
            refreshPluginInfo();
            startPluginFunc();
        }
    }

    void PluginHandle::end()
    {
        if(!dynLib.isNull())
        {
            DLL_END_PLUGIN endPluginFunc = (DLL_END_PLUGIN) dynLib->getSymbol(String("EndPlugin"));
            if(!endPluginFunc)
            {
                Console::get() << "[Plugin] Couldn't find function EndPlugin in library " << dynLib->getName() << ".";
            }
            else
            {
                endPluginFunc();
            }

            dynLib->unload();
            refreshPluginInfo();
        }
    }

    const PluginInfo& PluginHandle::getPluginInfo() const
    {
        return info;
    }

    void PluginHandle::refreshPluginInfo()
    {
        if(dynLib.isNull())
        {
            info.name = String("");
            info.author = String("");
            info.date = String("");
            info.description = String("");
        }
        else
        {
            DLL_GET_PLUGININFO infofunc = (DLL_GET_PLUGININFO) dynLib->getSymbol(String("GetPluginInfo"));
            if(infofunc)
            {
                info = infofunc();
            }
            else
            {
                Console::get() << "[Plugin] Can't retrieve information of library " << dynLib->getName() << ".";
                info.name = String("");
                info.author = String("");
                info.date = String("");
                info.description = String("");
            }
        }
    }

    SharedPointer<DynamicLibrary> PluginHandle::toDynamicLibrary()
    {
        return dynLib;
    }

    void PluginHandle::setName(const String& n)
    {
        name = n;
    }

    const String& PluginHandle::getName() const
    {
        return name;
    }
}
