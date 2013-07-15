/** @file MathModule.cpp
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
        modules = other.modules;
    }

    MathModule::~MathModule()
    {
        clears();
    }

    String MathModule::getName() const
    {
        return name;
    }

    String MathModule::getDescription() const
    {
        return description;
    }

    void MathModule::pushFunction(const MathFunction::ptr& obj)
    {
        Manager<MathFunction>::push(obj);
    }

    void MathModule::pushModule(const MathModule::ptr& obj)
    {
        Manager<MathModule>::push(obj);
    }

    void MathModule::popFunction(const MathFunction::ptr& obj)
    {
        Manager<MathFunction>::pop(obj);
    }

    void MathModule::popModule(const MathModule::ptr& obj)
    {
        Manager<MathModule>::pop(obj);
    }

    MathFunction::ptr MathModule::findFunction(const String& obj)
    {
        if(obj.isEmpty())
            return MathFunction::ptr();

        for(unsigned int i = 0; i < functions.size(); i++)
        {
            if(functions.at(i)->getName() == obj)
                return functions.at(i);
        }

        return MathFunction::ptr();
    }

    MathModule::ptr MathModule::findModule(const String& obj)
    {
        if(obj.isEmpty())
            return MathModule::ptr();

        for(unsigned int i = 0; i < modules.size(); i++)
        {
            if(modules.at(i)->getName() == obj)
                return modules.at(i);
        }

        return MathModule::ptr();
    }

    List<MathFunction::ptr>& MathModule::getFunctions()
    {
        return functions;
    }

    List<MathModule::ptr>& MathModule::getModules()
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

    void MathModule::clears()
    {
        clearFunction();
        clearModule();
    }
}
