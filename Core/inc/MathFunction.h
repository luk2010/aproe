/** @file MathFunction.h
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
#ifndef APROMATHFUNCTION_H
#define APROMATHFUNCTION_H

#include "Platform.h"
#include "SharedPointer.h"
#include "Variant.h"
#include "List.h"
#include "SString.h"

namespace APro
{
    class APRO_DLL MathFunction
    {

        APRO_DECLARE_SHAREDPOINTER_CLASS_TYPEDEF(MathFunction)

    public:

        typedef Variant (*function_def) (const List<Variant>&);

    public:
        MathFunction();
        MathFunction(const String& name_, const String& args_, const String & descr_, function_def func_);
        MathFunction(const MathFunction& other);

        ~MathFunction();

    public:

        String getName() const;
        List<String> getArgues() const;
        String getReturnType() const;
        String getDescription() const;

        Variant operator () (const List<Variant>& args);
        Variant run(const List<Variant>& args);
        //Variant call(size_t nbParametre, ...);

    protected:

        String name;
        String description;
        String returnType;
        List<String> argues;
        function_def theFunction;
    };
}

#endif
