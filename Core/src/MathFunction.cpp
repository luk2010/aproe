////////////////////////////////////////////////////////////
/** @file MathFunction.cpp
 *  @ingroup Maths
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 16/10/2012 - 06/12/2013
 *
 *  Implements the MathFunction class.
 *
**/
////////////////////////////////////////////////////////////
#include "MathFunction.h"

namespace APro
{
    MathFunction::MathFunction()
    {

    }

    MathFunction::MathFunction(const String& name_, const String& args_, const String & descr_, function_def func_)
        : name(name_), description(descr_), theFunction(func_)
    {
        if(args_ == String("void:void") || args_.isEmpty())
        {
            returnType = "void";
        }
        else
        {
            returnType = args_.extract(0, args_.findFirst(':'));
            argues = args_.extract(args_.findFirst(':') + 1, args_.size()).explode(',');
        }
    }

    MathFunction::MathFunction(const MathFunction& other)
        : name(other.name), description(other.description),
        returnType(other.returnType), argues(other.argues),
        theFunction(other.theFunction)
    {

    }

    MathFunction::~MathFunction()
    {

    }

    const String& MathFunction::getName() const
    {
        return name;
    }

    const List<String>& MathFunction::getArgues() const
    {
        return argues;
    }

    const String& MathFunction::getReturnType() const
    {
        return returnType;
    }

    const String& MathFunction::getDescription() const
    {
        return description;
    }

    Variant MathFunction::operator () (const List<Variant>& args)
    {
        return run(args);
    }

    Variant MathFunction::run(const List<Variant>& args)
    {
        return theFunction(args);
    }
}
