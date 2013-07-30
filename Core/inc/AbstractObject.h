////////////////////////////////////////////////////////////
/** @file AbstractObject.h
 *  @ingroup Core
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 03/07/2013
 *
 *  Defines the AbstractObject class.
 *
**/
////////////////////////////////////////////////////////////
#ifndef APRO_ABSTRACTOBJECT_H
#define APRO_ABSTRACTOBJECT_H

#include "Platform.h"
#include "SString.h"
#include "Dictionnary.h"
#include "Factory.h"
#include "AutoPointer.h"

namespace APro
{
    class APRO_DLL AbstractObjectFactory;

    ////////////////////////////////////////////////////////////
    /** @class AbstractObject
     *  @ingroup Core
     *  @brief An object that can be stored by the Rendering
     *  Engine.
     *  @details AbstractObject represents any objects capable of
     *  entering the rendering process, as Lights, Cameras, Meshes,
     *  etc...
     *  It use the prototype design pattern, and a global fatory
     *  is given in the Main object to handle any type of
     *  Object construction.
     *
     *  As it follows the Factory Design Pattern, you must provide
     *  clone() function to your customized object, but you also
     *  must provide a standard destroy() method.
     *
     *  @note Properties must be copied by subclass, they better
     *  know what type of property are stored :) .
    **/
    ////////////////////////////////////////////////////////////
    class APRO_DLL AbstractObject : public Prototype
    {
    protected:

        String                  m_name;      ///< Name of the object.
        AbstractObjectFactory*  m_factory;   ///< Factory that created this object.
        Dictionnary             m_properties;///< Properties of this object.

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Constructor.
         *  @param name : Name of the object.
         *  @param factory : Factory that crerated this object.
        **/
        ////////////////////////////////////////////////////////////
        AbstractObject(const String& name, AbstractObjectFactory* factory = nullptr);

        ////////////////////////////////////////////////////////////
        /** @brief Constructor by copy.
         *  @param other : Object to copy.
         *  @param factory : Factory who copied the object.
         *  @note If none factory is given, the other one is given.
        **/
        ////////////////////////////////////////////////////////////
        AbstractObject(const AbstractObject& other, AbstractObjectFactory* factory = nullptr);

        ////////////////////////////////////////////////////////////
        /** @brief Destructor.
         *  @note It must do nothing because there is a destroy function
         *  that can better do that.
        **/
        ////////////////////////////////////////////////////////////
        virtual ~AbstractObject();

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Return the name of this object.
        **/
        ////////////////////////////////////////////////////////////
        const String& getName() const;

        ////////////////////////////////////////////////////////////
        /** @brief Return the Factory associated with this object.
        **/
        ////////////////////////////////////////////////////////////
        AbstractObjectFactory* getFactory();

        ////////////////////////////////////////////////////////////
        /** @brief Return the Factory associated with this object.
        **/
        ////////////////////////////////////////////////////////////
        const AbstractObjectFactory* getFactory() const;

        ////////////////////////////////////////////////////////////
        /** @brief Return every properties in this object.
        **/
        ////////////////////////////////////////////////////////////
        Dictionnary& getProperties();

        ////////////////////////////////////////////////////////////
        /** @brief Returns every properties in this object.
        **/
        ////////////////////////////////////////////////////////////
        const Dictionnary& getProperties() const;

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Set given property to given value.
         *  @param prop_name : Name of property.
         *  @param prop_value : Value of the property.
         *  @note You can define custom properties with this function.
        **/
        ////////////////////////////////////////////////////////////
        void setProperty(const String& prop_name, Variant& prop_value);

        ////////////////////////////////////////////////////////////
        /** @brief Return given property to given type.
         *  @param prop_name : Name of property.
        **/
        ////////////////////////////////////////////////////////////
        template<typename PropertyType> PropertyType& getProperty(const String& prop_name)
        {
            return m_properties[prop_name].to<PropertyType>();
        }

        ////////////////////////////////////////////////////////////
        /** @brief Return given property to given type.
         *  @param prop_name : Name of property.
        **/
        ////////////////////////////////////////////////////////////
        template<typename PropertyType> const PropertyType& getProperty(const String& prop_name) const
        {
            return m_properties[prop_name].to<PropertyType>();
        }

        ////////////////////////////////////////////////////////////
        /** @brief Tell if given property exists in this object.
         *  @param prop_name : Property to check.
        **/
        ////////////////////////////////////////////////////////////
        bool hasProperty(const String& prop_name) const;

        ////////////////////////////////////////////////////////////
        /** @brief Return the number of properties.
        **/
        ////////////////////////////////////////////////////////////
        size_t getPropertiesNumber() const;

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Destroy this object, and every custom data.
        **/
        ////////////////////////////////////////////////////////////
        virtual void destroy() = 0;
    };

    ////////////////////////////////////////////////////////////
    /** @class AbstractObjectFactory
     *  @ingroup Core
     *  @brief A factory instanciated by the Main object.
     *  @details Use it to register custom objects, or to create
     *  objects.
    **/
    ////////////////////////////////////////////////////////////
    class AbstractObjectFactory : public Factory<AbstractObject> {};

    ////////////////////////////////////////////////////////////
    /** @class AbstractObjectAutoPointer
     *  @ingroup Core
     *  @brief Specialized version of AutoPointer.
    **/
    ////////////////////////////////////////////////////////////
    class APRO_DLL AbstractObjectAutoPointer : public AutoPointer<AbstractObject>
    {
    public:
        
        APRO_COPY_AUTOPOINTER_CONSTRUCT(AbstractObjectAutoPointer, AbstractObject)
        
        virtual ~AbstractObjectAutoPointer() { ungrab_pointer(); }
        
    protected:

        virtual void destroy_pointer()
        {
            if(pointer)
                pointer->destroy();

            AutoPointer<AbstractObject>::deallocate_pointer();
        }
    };
}

#endif // APRO_ABSTRACTOBJECT_H
