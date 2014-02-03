/////////////////////////////////////////////////////////////
/** @file Factory.h
 *  @ingroup Utils
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 19/05/2013
 *
 *  Defines the Factory class and Design Pattern.
 *
**/
/////////////////////////////////////////////////////////////
#ifndef APROFACTORY_H
#define APROFACTORY_H

#include "Platform.h"
#include "Map.h"
#include "Printable.h"

namespace APro
{
    /////////////////////////////////////////////////////////////
    /** @class Factory
     *  @ingroup Utils
     *  @brief A factory class that implements the Factory Design
     *  Pattern.
     *
     *  A factory is an object that can create other objects
     *  by cloning them from a prototype stored in the factory.
     *  The prototype is user-created from the application or from
     *  a plugin if the factory is accessible from every point of
     *  the Engine.
     *
     *  The Factory Design Pattern shows that you  must subclass
     *  Prototype to make your own kind of object. After, only a
     *  typedef of the templated factory is suffisant. Every class that
     *  inherits your prototype can so be created by the factory.
     *
     *  @note The Factory Design Pattern is even more usefull if it is
     *  more efficient to copy this object than to initialise it.
     *  @note A Factory is always thread-safe.
     *  @note We advice you to use standard function className() to
     *  set a new key registering a prototype, so everybody will
     *  guess which name you use.
     *
     *  @warning The prototype has to be destroyed by the creator.
    **/
    /////////////////////////////////////////////////////////////
    template <typename PrototypeBase>
    class Factory : public Printable,
                    public ThreadSafe
    {
    protected:
        Map<String, PrototypeBase*> prototypes;///< Prototypes the factory can clone.

    public:
        /////////////////////////////////////////////////////////////
        /** @brief Destructor.
        **/
        /////////////////////////////////////////////////////////////
        ~Factory() {}

        /////////////////////////////////////////////////////////////
        /** @brief Create an object.
         *  @param key : Key where the object is stored.
         *  @return A copy of this object.
        **/
        /////////////////////////////////////////////////////////////
        PrototypeBase* create(const String& key) const { APRO_THREADSAFE_AUTOLOCK return prototypes.exists(key) ? prototypes[key]->clone() : nullptr; }

        /////////////////////////////////////////////////////////////
        /** @brief Register a prototype to this factory.
         *  @param key : Key to store the prototype.
         *  @param proto : Prototype to store.
        **/
        /////////////////////////////////////////////////////////////
        void register_prototype(const String& key, PrototypeBase* proto) { APRO_THREADSAFE_AUTOLOCK if(proto) { prototypes[key] = proto; proto->fact = this; } }

        ////////////////////////////////////////////////////////////
        /** @brief Tell if a prototype is registered.
        **/
        ////////////////////////////////////////////////////////////
        bool hasPrototype(const String& key) { APRO_THREADSAFE_AUTOLOCK return prototypes.exists(key); }

        /////////////////////////////////////////////////////////////
        /** @see Printable::print
        **/
        /////////////////////////////////////////////////////////////
        void print(Console& console) const
        {
            APRO_THREADSAFE_AUTOLOCK
            console << "Factory { Prototypes = \"" << className<PrototypeBase>() << "\", Prototypes Number = " << prototypes.size() << " }";
        }
    };

    /////////////////////////////////////////////////////////////
    /** @class Prototype
     *  @ingroup Utils
     *  @brief Object that can be cloned.
     *  @details Every object that can be created by a factory
     *  must inherits this class, and implement the clone and destroy
     *  methods.
    **/
    /////////////////////////////////////////////////////////////
    class Prototype
    {
    public:
        /////////////////////////////////////////////////////////////
        /** @brief Destructor.
        **/
        /////////////////////////////////////////////////////////////
        virtual ~Prototype() {}

        /////////////////////////////////////////////////////////////
        /** @brief Clone this object.
         *  @note This function should be used only by a factory.
         *
         *  @return A new instance of this object.
        **/
        /////////////////////////////////////////////////////////////
        virtual Prototype* clone() const = 0;
    };
}

#endif
