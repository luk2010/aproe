////////////////////////////////////////////////////////////
/** @file MathFunctionManager.h
 *  @ingroup Maths
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 10/10/2012 - 03/12/2013
 *
 *  Defines the MathFunctionManager class.
 *
**/
////////////////////////////////////////////////////////////
#ifndef APROMATHFUNCTIONMANAGER_H
#define APROMATHFUNCTIONMANAGER_H

#include "Platform.h"
#include "Manager.h"
#include "MathModule.h"

namespace APro
{
    ////////////////////////////////////////////////////////////
    /** @class MathFunctionManager
     *  @ingroup Maths
     *  @brief Manages every MathModule objects.
     *
     *  The MathModuleManager gives you access to every Math added
     *  function of the engine.
     *
     *  Math added function are grouped in namespaces. Each namespace
     *  can have sub-namespace, and functions.
     *  A Math namespace is called a Module (MathModule). A function
     *  in a MathModule is called a MathFunction.
     *
     *  You can access a namespace with MathModuleManager::module()
     *  and access a function with MathModuleManager::find(). The name
     *  of a function is relative to the current namespace.
     *  If function is in namespace Std (for exemple 'Cos' that is the
     *  Cosinus function), name will be 'Std.Cos'. It is the same
     *  way for namespace.
     *
     *  @note Std.Cos and Std.Sin are pre-builded.
    **/
    ////////////////////////////////////////////////////////////
    class APRO_DLL MathFunctionManager : public Manager<MathModule>
    {
        APRO_DECLARE_MANUALSINGLETON(MathFunctionManager)

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Constructs the manager.
        **/
        ////////////////////////////////////////////////////////////
        MathFunctionManager();

        ////////////////////////////////////////////////////////////
        /** @brief Destructs the manager.
        **/
        ////////////////////////////////////////////////////////////
        ~MathFunctionManager();

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Find a given MathFunction from his path.
        **/
        ////////////////////////////////////////////////////////////
        MathFunctionPtr find(const String& completeName);

        ////////////////////////////////////////////////////////////
        /** @brief Find a given MathModule in this Manager.
         *  @note It doesn't find for sub-module.
        **/
        ////////////////////////////////////////////////////////////
        MathModulePtr module(const String& moduleName);

        ////////////////////////////////////////////////////////////
        /** @brief Return true if given module is registered.
        **/
        ////////////////////////////////////////////////////////////
        bool hasModule(const String& moduleName);

        ////////////////////////////////////////////////////////////
        /** @brief Return true if given function is registered.
         *  @note Functions from sub-module are also found.
        **/
        ////////////////////////////////////////////////////////////
        bool hasFunction(const String& functionName);
    };
}

#endif
