/** @file MathFunction.cpp
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 16/10/2012
 *
 *  @addtogroup Global
 *  @addtogroup Maths
 *
 *  This file defines the MathFunction class.
 *
**/
#include "MathFunction.h"
#include <cstdarg>

namespace APro
{
    MathFunction::MathFunction()
    {

    }

    MathFunction::MathFunction(const String& name_, const String& args_, const String & descr_, function_def func_)
        : name(name_), description(descr_), theFunction(func_)
    {
        List<String> mlist = args_.explode(':');

        returnType = mlist.size() <= 1 ? String("void") : mlist.at(0);

        String returnt = args_.extract(0, args_.findFirst(':'));
        String argues__ = (returnt.size() != args_.size()) ?
                                args_.extract(args_.findFirst(':') + 1, args_.size())
                                : args_;

        /*mlist = argues__.explode(',');
        if(mlist.size() > 0)
            argues.push_back(mlist);*/
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

    String MathFunction::getName() const
    {
        return name;
    }

    List<String> MathFunction::getArgues() const
    {
        return argues;
    }

    String MathFunction::getReturnType() const
    {
        return returnType;
    }

    String MathFunction::getDescription() const
    {
        return description;
    }

    Variant MathFunction::operator () (const List<Variant>& args)
    {
        return theFunction(args);
    }

    Variant MathFunction::run(const List<Variant>& args)
    {
        return theFunction(args);
    }
/*
    Variant MathFunction::call(size_t nbParametre, ...)
    {
        List<Variant> args;

        va_list ap;
        va_start(ap, nbParametre);

        for(size_t i = 0; i < nbParametre; ++i)
        {
            args << Variant(va_arg(ap, Variant));
        }

        va_end(ap);

        return theFunction(args);
    }
    */
}
