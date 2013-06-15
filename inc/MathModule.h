/** @file MathModule.h
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 16/10/2012
 *
 *  @addtogroup Global
 *  @addtogroup Maths
 *
 *  This file defines the MathModule class.
 *
**/
#ifndef APROMATHMODULE_H
#define APROMATHMODULE_H

#include "Platform.h"
#include "SharedPointer.h"
#include "MathFunction.h"
#include "Manager.h"

namespace APro
{
    class APRO_DLL MathModule : public Manager<MathFunction>,
                        public Manager<MathModule>
    {
        APRO_DECLARE_SHAREDPOINTER_CLASS_TYPEDEF(MathModule)

    public:
        MathModule();
        MathModule(const String& n, const String& desc);
        MathModule(const String& n, const MathModule& other);

        ~MathModule();

    public:

        String getName() const;
        String getDescription() const;

        void pushFunction(const MathFunction::ptr& obj);
        void pushModule(const MathModule::ptr& obj);

        void popFunction(const MathFunction::ptr& obj);
        void popModule(const MathModule::ptr& obj);

        MathFunction::ptr findFunction(const String& obj);
        MathModule::ptr   findModule(const String& obj);

        List<MathFunction::ptr>& getFunctions();
        List<MathModule::ptr>& getModules();

        void clearFunction();
        void clearModule();
        void clears();

    protected:

        String name;
        String description;
        List<MathFunction::ptr>& functions;
        List<MathModule::ptr>& modules;
    };
}

#endif
