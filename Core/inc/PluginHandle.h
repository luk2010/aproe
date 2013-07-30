/////////////////////////////////////////////////////////////
/** @file PluginHandle.h
 *  @ingroup Plugin
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 17/09/2012
 *
 *  Defines the PluginHandle class.
 *
**/
/////////////////////////////////////////////////////////////
#ifndef APROPLUGINHANDLE_H
#define APROPLUGINHANDLE_H

#include "Platform.h"
#include "SharedPointer.h"
#include "DynamicLibrary.h"

namespace APro
{
    
    typedef struct _PluginApiVersion
    {
        int major;
        int minor;
        int build;
        
    } PluginApiVersion;
    
    typedef struct PluginInfo
    {
        String           name;
        String           author;
        String           date;
        String           description;
        PluginApiVersion apiversion;
    } PluginInfo;

    class APRO_DLL PluginHandle
    {
        APRO_DECLARE_SHAREDPOINTER_CLASS_TYPEDEF(PluginHandle)

    protected:

        String                          name;
        PluginInfo*                     info;
        SharedPointer<DynamicLibrary>   dynLib;
        bool                            started;
        bool                            terminated;

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
        
        bool isStarted() const;
        bool isTerminated() const;

        PluginInfo* getPluginInfo() const;
        void refreshPluginInfo();

        SharedPointer<DynamicLibrary> toDynamicLibrary();
    };

}

#endif
