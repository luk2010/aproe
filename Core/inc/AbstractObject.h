////////////////////////////////////////////////////////////
/** @file AbstractObject.h
 *  @ingroup Core
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 03/07/2013 - 11/12/2014
 *
 *  @brief 
 *  Defines the AbstractObject class.
 *
 *  @copyright
 *  Atlanti's Project Engine
 *  Copyright (C) 2012 - 2014  Atlanti's Corp
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
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
    class AbstractObject;
    typedef AutoPointer<AbstractObject> AbstractObjectPtr;///< An AutoPointer to AbstractObject.

    ////////////////////////////////////////////////////////////
    /** @class AbstractObject
     *  @ingroup Core
     *  @brief An object that can be stored by the Rendering
     *  Engine.
     *
     *  @details AbstractObject represents any objects capable of
     *  entering the rendering process, as Lights, Cameras, Meshes,
     *  etc...
     *  It use the prototype design pattern, and a global fatory
     *  is given in the Main object to handle any type of
     *  Object construction.
     *
     *  As it follows the Factory Design Pattern, you must provide
     *  clone() function to your customized object.
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

        typedef AbstractObjectPtr ptr;

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
        /** @brief Destruct the abstract object.
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
            return m_properties[prop_name].cast<PropertyType>();
        }

        ////////////////////////////////////////////////////////////
        /** @brief Return given property to given type.
         *  @param prop_name : Name of property.
        **/
        ////////////////////////////////////////////////////////////
        template<typename PropertyType> const PropertyType& getProperty(const String& prop_name) const
        {
            return m_properties[prop_name].cast<PropertyType>();
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
    };

    /// A Factory instanciated by the Main object.
    class AbstractObjectFactory : public Factory<AbstractObject>
    {
        APRO_DECLARE_MANUALSINGLETON(AbstractObjectFactory)
    };
}

#endif // APRO_ABSTRACTOBJECT_H
