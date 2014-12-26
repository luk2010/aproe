////////////////////////////////////////////////////////////
/** @file MathModule.cpp
 *  @ingroup Maths
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 16/10/2012 - 08/12/2013
 *
 *  Implements the MathModule class.
 *
**/
////////////////////////////////////////////////////////////
#include "MathModule.h"

namespace APro
{
    MathModule::MathModule()
        : functions(Manager<MathFunction>::objects), modules(Manager<MathModule>::objects)
    {

    }

    MathModule::MathModule(const String& n, const String& desc)
        : name(n), description(desc), functions(Manager<MathFunction>::objects), modules(Manager<MathModule>::objects)
    {

    }

    MathModule::MathModule(const String& n, const MathModule& other)
        : name(n), description(other.getDescription()), functions(Manager<MathFunction>::objects), modules(Manager<MathModule>::objects)
    {
        functions = other.functions;
        modules   = other.modules;
    }

    MathModule::~MathModule()
    {
        clear();
    }

    const String& MathModule::getName() const
    {
        return name;
    }

    const String& MathModule::getDescription() const
    {
        return description;
    }

    void MathModule::pushFunction(const MathFunctionPtr& obj)
    {
        Manager<MathFunction>::push(obj);
    }

    void MathModule::pushModule(const MathModulePtr& obj)
    {
        Manager<MathModule>::push(obj);
    }

    void MathModule::popFunction(const MathFunctionPtr& obj)
    {
        Manager<MathFunction>::pop(obj);
    }

    void MathModule::popModule(const MathModulePtr& obj)
    {
        Manager<MathModule>::pop(obj);
    }

    MathFunctionPtr& MathModule::findFunction(const String& fname)
    {
        if(fname.isEmpty())
            return MathFunctionPtr::Null;

        List<MathFunctionPtr>::const_iterator e = functions.end();
        for(List<MathFunctionPtr>::iterator it = functions.begin(); it != e; it++)
        {
            if((*it)->getName() == fname)
                return *it;
        }

        return MathFunctionPtr::Null;
    }

    const MathFunctionPtr& MathModule::findFunction(const String& fname) const
    {
        return const_cast<MathModule*>(this)->findFunction(fname);
    }

    MathModulePtr& MathModule::findModule(const String& mname)
    {
        if(mname.isEmpty())
            return MathModulePtr::Null;

        List<MathModulePtr>::const_iterator e = modules.end();
        for(List<MathModulePtr>::iterator it = modules.begin(); it != e; it++)
        {
            if((*it)->getName() == mname)
                return *it;
        }

        return MathModulePtr::Null;
    }

    const MathModulePtr& MathModule::findModule(const String& mname) const
    {
        return const_cast<MathModule*>(this)->findModule(mname);
    }

    List<MathFunctionPtr>& MathModule::getFunctions()
    {
        return functions;
    }

    List<MathModulePtr>& MathModule::getModules()
    {
        return modules;
    }

    void MathModule::clearFunction()
    {
        Manager<MathFunction>::clear();
    }

    void MathModule::clearModule()
    {
        Manager<MathModule>::clear();
    }

    void MathModule::clear()
    {
        clearFunction();
        clearModule();
    }
}
