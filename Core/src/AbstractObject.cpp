////////////////////////////////////////////////////////////
/** @file AbstractObject.cpp
 *  @ingroup Memory
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 03/07/2013
 *
 *  Implements the AbstractObject class.
 *
**/
////////////////////////////////////////////////////////////
#include "AbstractObject.h"

namespace APro
{
    AbstractObject::AbstractObject(const String& name, AbstractObjectFactory* factory)
    {
        m_name = name;
        m_factory = factory;
    }

    AbstractObject::AbstractObject(const AbstractObject& other, AbstractObjectFactory* factory)
    {
        m_name = other.name;
        m_factory = factory ? factory : other.m_factory;
    }

    AbstractObject::~AbstractObject()
    {

    }

    const String& AbstractObject::getName() const
    {
        return m_name;
    }

    AbstractObjectFactory* AbstractObject::getFactory()
    {
        return m_factory;
    }

    const AbstractObjectFactory* AbstractObject::getFactory() const
    {
        return m_factory;
    }

    Dictionnary& AbstractObject::getProperties()
    {
        return m_properties;
    }

    const Dictionnary& AbstractObject::getProperties() const
    {
        return m_properties;
    }

    void AbstractObject::setProperty(const String& prop_name, Variant& prop_value)
    {
        m_properties.push(prop_name, prop_value);
    }

    bool AbstractObject::hasProperty(const String& prop_name) const
    {
        return m_properties.exists(prop_name);
    }

    size_t AbstractObject::getPropertiesNumber() const
    {
        return m_properties.size();
    }
}
