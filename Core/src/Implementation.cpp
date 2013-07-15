/** @file Implementation.cpp
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 16/03/2013
 *
 *  @addtogroup Global
 *  @addtogroup System
 *
 *  This file defines the Implementation class.
 *
**/
#include "Implementation.h"
#include "Console.h"

namespace APro
{
    Implementation::Implementation()
    {

    }

    Implementation::~Implementation()
    {

    }

    // --------------------------------
    // ImplementationStore
    // --------------------------------

    ImplementationStore::ImplementationStore()
    {

    }

    ImplementationStore::~ImplementationStore()
    {

    }

    Implementation::ptr ImplementationStore::findImplementationByName(const String & impname) const
    {
        if(impname.isEmpty()) return Implementation::ptr();

        Store::ConstIteratorType itend = Store::objects.end();
        for(Store::ConstIteratorType it = Store::objects.begin(); it != itend; it++)
        {
            if(it.get()->getImplementationName() == impname)
                return it.get();
        }

        return Implementation::ptr();
    }

    bool ImplementationStore::isKeyEgal(const Variant& var, ConstIteratorType it) const
    {
        if(!var.isCastable<String>())
            return false;

        String varS = var.to<String>();
        Store::ConstIteratorType itend = Store::objects.end();
        if(it != itend)
        {
            if(!it.get().isNull())
            {
                if(it.get()->getClassImplementation() == varS)
                {
                    return true;
                }
            }
        }

        return false;
    }

    bool ImplementationStore::isKeyEgal(const Implementation::ptr& object, Store::ConstIteratorType it) const
    {
        if(object.isNull())
            return false;

        Store::ConstIteratorType itend = Store::objects.end();
        if(it != itend)
        {
            if(!it.get().isNull())
            {
                if(it.get()->getClassImplementation() == object->getClassImplementation())
                {
                    return true;
                }
            }
        }

        return false;
    }

    void ImplementationStore::drawInfos() const
    {
        Store::ConstIteratorType itend = Store::objects.end();

        Console::get() << "\n[ImplementationStore] Getting implementations infos"
                       << "\n---------------------------------------------------";

        if(Store::objects.isEmpty())
        {
            Console::get() << "\n+ No Implementations found ! Please add some.";
        }
        else
        {
            for(Store::ConstIteratorType it = Store::objects.begin(); it != itend; it++)
            {
                Implementation::ptr imp = it.get();
                Console::get() << "\n+ Class : " << imp->getClassImplementation() << " | Name : " << imp->getImplementationName() << ".";
            }
        }

        Console::get() << "\n---------------------------------------------------";
    }
}
