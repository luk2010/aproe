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
    typedef void* (*DLL_GET_PLUGININFO)(void);

    PluginHandle::PluginHandle()
        : name(""), info(nullptr), dynLib(nullptr)
    {

    }

    PluginHandle::PluginHandle(const String& mname)
        : name(mname), info(nullptr), dynLib(nullptr)
    {

    }

    PluginHandle::PluginHandle(const PluginHandle& /* other */)
        : name(""), info(nullptr), dynLib(nullptr)
    {

    }

    PluginHandle::PluginHandle(const String& mname, const SharedPointer<DynamicLibrary>& lib)
        : name(mname), info(nullptr), dynLib(nullptr)
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
            Console::get() << "\n[PluginHandle] Couldn't find function StartPlugin in library " << dynLib->getName() << ".";
        }
        else
        {
            Console::get() << "\n[PluginHandle] Starting plugin " << name << "...";
            startPluginFunc();
            refreshPluginInfo();
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
                Console::get() << "\n[PluginHandle] Stopping plugin " << name << "...";
                endPluginFunc();
            }

            dynLib->unload();
            refreshPluginInfo();
        }
    }

    PluginInfo* PluginHandle::getPluginInfo() const
    {
        return info;
    }

    void PluginHandle::refreshPluginInfo()
    {
        if(dynLib.isNull() || !dynLib->isLoaded())
        {
            info = nullptr;
        }
        else
        {
            DLL_GET_PLUGININFO infofunc = (DLL_GET_PLUGININFO) dynLib->getSymbol(String("GetPluginInfo"));
            if(infofunc)
            {
                info = (PluginInfo*) infofunc();
            }
            else
            {
                Console::get() << "[Plugin] Can't retrieve information of library " << dynLib->getName() << ".";
                info = nullptr;
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
