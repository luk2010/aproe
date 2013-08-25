/** @file Implementable.h
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 20/03/2013
 *
 *  @addtogroup Global
 *  @addtogroup System
 *
 *  This file defines the Implementable class.
 *
**/
#ifndef APRO_IMPLEMENTABLE_H
#define APRO_IMPLEMENTABLE_H

#include "Main.h"
#include "Implementation.h"

namespace APro
{
    template <typename T>
    class Implementable
    {
    public:

//      typedef typename T::ptr typeptr;
        typedef typename T* typeptr;

    protected:

        typeptr implement;
        String m_class;

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
            
            typeptr implementation = Main::get().getImplementations().create(String(m_class));
            if(implementation)
            {
                implement = implementation;
            }
        }

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

    public:

        Implementable()
        {

        }

        Implementable(const String& mclss)
            : m_class(mclss)
        {

        }

        virtual ~Implementable()
        {
            destroyImplementation();
        }

        T* getImplementationPtr()
        {
            return implement.getPtr();
        }

    };
}

#endif // APRO_IMPLEMENTABLE_H
