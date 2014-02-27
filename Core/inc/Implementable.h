/////////////////////////////////////////////////////////////
/** @file Implementable.h
 *  @ingroup Implementations
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 20/03/2013 - 22/02/2014
 *
 *  Defines the Implementable class.
 *
**/
/////////////////////////////////////////////////////////////
#ifndef APRO_IMPLEMENTABLE_H
#define APRO_IMPLEMENTABLE_H

#include "Platform.h"
#include "Implementation.h"

namespace APro
{
    /////////////////////////////////////////////////////////////
    /** @class Implementable
     *  @ingroup Implementations
     *  @brief A structure that describe a class containing an
     *  implementation.
     *
     *  An implementable object is an object that can have an
     *  implementation, loaded from the Implementation Factory.
     *
     *  The implementation doesn't have to be inited or destroyed,
     *  this is in charge of the implementable object to call
     *  correct functions, as it is his object.
    **/
    /////////////////////////////////////////////////////////////
    template <typename T>
    class Implementable
    {
    public:

        typedef typename T* typeptr;///< Pointer to the implementation.

    protected:

        typeptr implement;///< Pointer to the implementation.

        ////////////////////////////////////////////////////////////
        /** @brief Create the implementation from the factory.
         *
         *  The implementation is created using the Factory Design
         *  Pattern, so a base object copies itself in a newly
         *  allocated one.
         *
         *  The implementation is gotten by looking for the class name
         *  in the Implementation Factory, so the Implementation's
         *  provider must register his implementation using the
         *  className() function to be sure the same result will be
         *  given.
         *
         *  On error, a debug string is written.
        **/
        ////////////////////////////////////////////////////////////
        void createImplementation()
        {
            typeptr implementation = ImplementationFactory::Get().create(String(className<T>()));
            if(implementation)
            {
                implement = implementation;
            }
            else
            {
                aprodebug("Can't create implementation !");
            }
        }

        ////////////////////////////////////////////////////////////
        /** @brief Destroys the implementation if previously created.
        **/
        ////////////////////////////////////////////////////////////
        void destroyImplementation()
        {
            if(implement)
            {
                AProDelete(implement);
            }
        }

        ////////////////////////////////////////////////////////////
        /** @brief Return the implementation and if none exists, try
         *  to create one.
         *
         *  @note You should always use this function to get the
         *  implementation from the superclass.
        **/
        ////////////////////////////////////////////////////////////
        T* imp()
        {
            if(!implement)
                createImplementation();
            return implement;
        }

        ////////////////////////////////////////////////////////////
        /** @brief Return a pointer to the implementation.
         *
         *  @note You should always use this function to get the
         *  implementation from the superclass.
        **/
        ////////////////////////////////////////////////////////////
        const T* imp() const
        {
            return implement;
        }

    public:

        Implementable()
        {

        }

        virtual ~Implementable()
        {
            destroyImplementation();
        }

        T* getImplementationPtr()
        {
            return implement;
        }

        const T* getImplementationPtr() const
        {
            return implement;
        }

    };
}

#endif // APRO_IMPLEMENTABLE_H
