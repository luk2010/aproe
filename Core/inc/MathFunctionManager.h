/** @file MathFunctionManager.h
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 10/10/2012
 *
 *  @addtogroup Global
 *  @addtogroup Maths
 *
 *  This file defines the MathFunctionManager class.
 *
**/
#ifndef APROMATHFUNCTIONMANAGER_H
#define APROMATHFUNCTIONMANAGER_H

#include "Manager.h"
#include "MathModule.h"

namespace APro
{
    class APRO_DLL MathFunctionManager : public Manager<MathModule>
    {
    public:
        MathFunctionManager();

        ~MathFunctionManager();

    private:
        MathFunctionManager(const MathFunctionManager&) { }

    public:

        MathFunction::ptr find(const String& completeName);
        MathModule::ptr module(const String& moduleName);

        bool hasModule(const String& moduleName);
        bool hasFunction(const String& functionName);
    };
}

#endif
