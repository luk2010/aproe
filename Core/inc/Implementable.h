/////////////////////////////////////////////////////////////
/** @file Implementable.h
 *  @ingroup Implementations
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 20/03/2013
 *
 *  Defines the Implementable class.
 *
**/
/////////////////////////////////////////////////////////////
#ifndef APRO_IMPLEMENTABLE_H
#define APRO_IMPLEMENTABLE_H

#include "Main.h"
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
     *
     *  The implementation can do any of his destruction in his
     *  destructor as it will be called in ::destroyImplementation
     *  before to be deallocated by the same heap it was allocated.
     *  @see Prototype::operator delete().
    **/
    /////////////////////////////////////////////////////////////
    template <typename T>
    class Implementable
    {
    public:

//      typedef typename T::ptr typeptr;
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
            /* DEPRECATED
            ImplementationStore& impStore = Main::get().getImplementationStore();
            Implementation::ptr impptr = impStore.find(Variant(m_class));
            implement = 0;

            if(impptr.isNull())
            {
                Console::get() << "\n[Implementable]{createImplementation} No implementation provided ! Please add correct plugin.";
            }
            else
            {
                Implementation::ptr p2 = impptr->clone();
                implement = spCast<T, Implementation>(p2);

                if(!implement.isNull())
                {
                    initImplementation();
                    if(Main::get().hasOption(Main::GlobalOption::Debugging_Implementation))
                        Console::get() << "\n[Implementable]{createImplementation} " << implement->getClassImplementation() << " using " << implement->getImplementationName() << ".";
                }
                else
                {
                    Console::get() << "\n[Implementable]{createImplementation} Can't clone implementation " << impptr->getImplementationName() << ".";
                    implement = NULL;
                }
            }
             */

            typeptr implementation = Main::get().getImplementations().create(String(className<T>()));
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
            /*
            ImplementationStore& impStore = Main::get().getImplementationStore();
            Implementation::ptr impptr = impStore.find(Variant(m_class));

            if(impptr.isNull())
            {
                Console::get() << "\n[Implementable]{createImplementation} No implementation provided to destroy this one ! Please do not remove plugins before destroying all implementations.";
            }
            else
            {
                if(!implement.isNull())
                {
                    impptr->destroy(implement.getPtr());
                    implement._force_set(nullptr);
                }
            }
             */

            if(implement)
            {
                ::operator delete((Prototype*) proto);// This call the AProDelete function.
                implement = nullptr;
            }
        }

//      virtual void initImplementation() = 0;

        ////////////////////////////////////////////////////////////
        /** @brief Return the implementation and if none exists, try
         *  try to create one.
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
