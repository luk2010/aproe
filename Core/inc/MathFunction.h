/** @file MathFunction.h
 *  @ingroup Maths
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 16/10/2012 - 06/12/2013
 *
 *  Defines the MathFunction class.
 *
**/
#ifndef APROMATHFUNCTION_H
#define APROMATHFUNCTION_H

#include "Platform.h"
#include "Variant.h"
#include "List.h"
#include "SString.h"

namespace APro
{
    ////////////////////////////////////////////////////////////
    /** @class MathFunction
     *  @ingroup Maths
     *  @brief A function that can be called by the MathFunctionManager.
     *
     *  This function has form :
     *  return_value:arg1,arg2,arg3,...
     *
     *  where :
     *  - return_value is the type of the returning value. It must be
     *  at least 'void' if function doesn't return an object.
     *  - arg1 are the argues types user must pass to this function.
     *
     *  @note The minimal function is 'void:void'.
    **/
    ////////////////////////////////////////////////////////////
    class APRO_DLL MathFunction
    {
    public:

        typedef Variant (*function_def) (const List<Variant>&);

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Constructs the function.
        **/
        ////////////////////////////////////////////////////////////
        MathFunction();

        ////////////////////////////////////////////////////////////
        /** @brief Constructs the function with some argues.
        **/
        ////////////////////////////////////////////////////////////
        MathFunction(const String& name_, const String& args_, const String & descr_, function_def func_);

        ////////////////////////////////////////////////////////////
        /** @brief Constructs the function by copy.
        **/
        ////////////////////////////////////////////////////////////
        MathFunction(const MathFunction& other);

        ////////////////////////////////////////////////////////////
        /** @brief Destructs thhe function.
        **/
        ////////////////////////////////////////////////////////////
        ~MathFunction();

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Returns the name of the function.
        **/
        ////////////////////////////////////////////////////////////
        const String& getName() const;

        ////////////////////////////////////////////////////////////
        /** @brief Returns the argues of the function.
        **/
        ////////////////////////////////////////////////////////////
        const List<String>& getArgues() const;

        ////////////////////////////////////////////////////////////
        /** @brief Returns the 'return type' of the function.
        **/
        ////////////////////////////////////////////////////////////
        const String& getReturnType() const;

        ////////////////////////////////////////////////////////////
        /** @brief Returns the description of the function.
        **/
        ////////////////////////////////////////////////////////////
        const String& getDescription() const;

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Call the function explicitly with given args.
        **/
        ////////////////////////////////////////////////////////////
        Variant run(const List<Variant>& args);
        Variant operator () (const List<Variant>& args);

    protected:

        String name;
        String description;
        String returnType;
        List<String> argues;
        function_def theFunction;
    };

    typedef AutoPointer<MathFunction> MathFunctionPtr;
}

#endif
