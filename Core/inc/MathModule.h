////////////////////////////////////////////////////////////
/** @file MathModule.h
 *  @ingroup Maths
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 16/10/2012 - 08/13/2013
 *
 *  Defines the MathModule class.
 *
**/
////////////////////////////////////////////////////////////
#ifndef APROMATHMODULE_H
#define APROMATHMODULE_H

#include "Platform.h"
#include "Manager.h"
#include "MathFunction.h"
#include "AutoPointer.h"

namespace APro
{
    class   MathModule;
    typedef AutoPointer<MathModule> MathModulePtr;

    ////////////////////////////////////////////////////////////
    /** @class MathModule
     *  @ingroup Maths
     *  @brief Regroups sub-modules and functions.
     *  @note Modules and sub-modules are the same class, they
     *  both represents a groupig node.
     *  @note This class is thread-safe.
    **/
    ////////////////////////////////////////////////////////////
    class APRO_DLL MathModule : public Manager<MathFunction>,
                                public Manager<MathModule>
    {
    public:

        ////////////////////////////////////////////////////////////
        /** @brief Constructs the module.
        **/
        ////////////////////////////////////////////////////////////
        MathModule();

        ////////////////////////////////////////////////////////////
        /** @brief Constructs the module giving his name and his
         *  description.
        **/
        ////////////////////////////////////////////////////////////
        MathModule(const String& n, const String& desc);

        ////////////////////////////////////////////////////////////
        /** @brief Constructs the module specifying his name, and another
         *  module to copy.
         *
         *  Datas in the copied module will be copied too. As we works
         *  with AutoPointer, theere won't be any deallocation problems.
        **/
        ////////////////////////////////////////////////////////////
        MathModule(const String& n, const MathModule& other);

        ////////////////////////////////////////////////////////////
        /** @brief Destructs the module.
        **/
        ////////////////////////////////////////////////////////////
        ~MathModule();

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Returns the name of this module.
        **/
        ////////////////////////////////////////////////////////////
        const String& getName() const;

        ////////////////////////////////////////////////////////////
        /** @brief Returns the description of this module.
        **/
        ////////////////////////////////////////////////////////////
        const String& getDescription() const;

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Add a function to this module.
        **/
        ////////////////////////////////////////////////////////////
        void pushFunction(const MathFunctionPtr& obj);

        ////////////////////////////////////////////////////////////
        /** @brief Add a sub-module to this module.
        **/
        ////////////////////////////////////////////////////////////
        void pushModule(const MathModulePtr& obj);

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Remove a function from this module.
        **/
        ////////////////////////////////////////////////////////////
        void popFunction(const MathFunctionPtr& obj);

        ////////////////////////////////////////////////////////////
        /** @brief Remove a sub-module from this module.
        **/
        ////////////////////////////////////////////////////////////
        void popModule(const MathModulePtr& obj);

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Find a function in this module with given name.
        **/
        ////////////////////////////////////////////////////////////
        MathFunctionPtr& findFunction(const String& fname);

        ////////////////////////////////////////////////////////////
        /** @brief Find a function in this module with given name.
        **/
        ////////////////////////////////////////////////////////////
        const MathFunctionPtr& findFunction(const String& obj) const;

        ////////////////////////////////////////////////////////////
        /** @brief Find a sub-module with given name.
        **/
        ////////////////////////////////////////////////////////////
        MathModulePtr& findModule(const String& mname);

        ////////////////////////////////////////////////////////////
        /** @brief Find a sub-module with given name.
        **/
        ////////////////////////////////////////////////////////////
        const MathModulePtr& findModule(const String& mname) const;

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Returns every functions in this module.
         *  @note Use this reference with care, cause modifying the
         *  returned value will modify this object.
        **/
        ////////////////////////////////////////////////////////////
        List<MathFunctionPtr>& getFunctions();

        ////////////////////////////////////////////////////////////
        /** @brief Returns every modules in this module.
         *  @note Use this reference with care, cause modifying the
         *  returned value will modify this object.
        **/
        ////////////////////////////////////////////////////////////
        List<MathModulePtr>& getModules();

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Removes every functions in this module.
        **/
        ////////////////////////////////////////////////////////////
        void clearFunction();

        ////////////////////////////////////////////////////////////
        /** @brief Removes every modules in this module.
        **/
        ////////////////////////////////////////////////////////////
        void clearModule();

        ////////////////////////////////////////////////////////////
        /** @brief Removes every functions and modules in this module.
        **/
        ////////////////////////////////////////////////////////////
        void clear();

    protected:

        String name;
        String description;
        List<MathFunctionPtr>& functions;
        List<MathModulePtr>& modules;
    };
}

#endif
