////////////////////////////////////////////////////////////
/** @file Implementation.h
 *  @ingroup Implementations
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 16/03/2013
 *
 *  Defines the Implementation class and system.
 *
**/
////////////////////////////////////////////////////////////
#ifndef APRO_IMPLEMENTATION_H
#define APRO_IMPLEMENTATION_H

#include "Platform.h"

#include "SString.h"
#include "SharedPointer.h"
#include "Store.h"
#include "Variant.h"

namespace APro
{
    /* THIS IS OLD VERSION OF THE IMPLENTATION SYSTEM
     NEW VERSION USES PROTOTYPE AND FACTORY SYSTEM
     
        Use this class to create an implementation for another class.
        Only one implementation can be set by user for one class.

        @note This system allow powerfull dll loading of os-specific
        implementations. Plugins can also give better implementations, or use
        other system like Qt or others.

        @warning Class that use this implementation MUST use init function at first use
        and deinit function and destruction of them.

    **
    class APRO_DLL Implementation
    {
        APRO_DECLARE_SHAREDPOINTER_CLASS_TYPEDEF(Implementation)

    public:

        virtual const String getImplementationName() const = 0;
        virtual const String getClassImplementation() const = 0;

        virtual bool init() = 0;
        virtual void deinit() = 0;

        virtual Implementation::ptr clone() const = 0;
        virtual void destroy(Implementation* impl) = 0;

    public:

        Implementation();
        virtual ~Implementation();
    };

    class APRO_DLL ImplementationStore : public Store<Implementation>
    {
    public:

        ImplementationStore();
        virtual ~ImplementationStore();

    public:

        Implementation::ptr findImplementationByName(const String & impname) const;
        void drawInfos() const;

    protected:

        bool isKeyEgal(const Variant& var, ConstIteratorType it) const;
        bool isKeyEgal(const Implementation::ptr& object, Store::ConstIteratorType it) const;
    };
    */
    
    ////////////////////////////////////////////////////////////
    /** @defgroup Implementations Implementation System
     *  @brief An Implementation subsystem.
     *
     *  The Implementation subsystem is a system that can be used
     *  to create implementations for some parts of the Engine.
     *  
     *  This is the Implementable class part to manage his own 
     *  implementation, because there is no initialization or 
     *  destroying made here.
     *
     *  Any class can use this implementation system. You just have 
     *  to register your implementation to the implementation global
     *  factory like : 
     *  @code Main::get().getImplementations().register_prototype
                          ("MyImpClass", my_imp);
     *  @endcode
     *
    **/
    ////////////////////////////////////////////////////////////
    
    ////////////////////////////////////////////////////////////
    /** @class Implementation
     *  @ingroup Implementations
     *  @brief The base class for any implementation.
    **/
    ////////////////////////////////////////////////////////////
    class APRO_DLL Implementation : public Prototype 
    {
    public:
        
        Implementation() { }
        ~Implementation() { }
        
    };
    
    typedef Factory<Implementation> ImplementationFactory;///< A factory that can creates any implementation easily.
    
}

#endif // APRO_IMPLEMENTATION_H
