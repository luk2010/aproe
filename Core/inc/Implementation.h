////////////////////////////////////////////////////////////
/** @file Implementation.h
 *  @ingroup Implementations
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 16/03/2013 - 22/02/2014
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
     *  @code ImplementationFactory::Get().register_prototype
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
        virtual ~Implementation() { }

    };

    /// @brief A factory that can creates any implementation easily.
    /// @ingroup Implementations.
    class ImplementationFactory : public Factory<Implementation>
    {
        APRO_DECLARE_MANUALSINGLETON(ImplementationFactory)
    };

}

#endif // APRO_IMPLEMENTATION_H
