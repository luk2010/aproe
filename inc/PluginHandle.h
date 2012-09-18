/** @file PluginHandle.h
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 17/09/2012
 *
 *  @addtogroup Global
 *  @addtogroup Plugin
 *
 *  This file defines the PluginHandle class.
 *
**/
#ifndef APROPLUGINHANDLE_H
#define APROPLUGINHANDLE_H

#include "Platform.h"
#include "SharedPointer.h"
#include "DynamicLibrary.h"

namespace APro
{
    typedef struct PluginInfo
    {
        String name;
        String author;
        String date;
        String description;
    } PluginInfo;

    class APRO_DLL PluginHandle
    {
    protected:

        String name;
        PluginInfo info;
        SharedPointer<DynamicLibrary> dynLib;

    public:

        PluginHandle();
        PluginHandle(const String& mname);
        PluginHandle(const PluginHandle& other);
        PluginHandle(const String& mname, const SharedPointer<DynamicLibrary>& lib);

        ~PluginHandle();

        void setName(const String& n);
        const String& getName() const;

        void initialize(const SharedPointer<DynamicLibrary>& lib);
        void end();

        const PluginInfo& getPluginInfo() const;
        void refreshPluginInfo();

        SharedPointer<DynamicLibrary> toDynamicLibrary();
    };

}

#endif
