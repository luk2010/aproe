/** @file ParametedObject.cpp
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 01/09/2012
 *
 *  @addtogroup Global
 *
 *  This file defines the ParametedObject class.
 *
**/
#include "ParametedObject.h"

namespace APro
{
    ParametedObject::ParametedObject()
    {

    }

    ParametedObject::ParametedObject(const ParametedObject& other)
        : parameters(other.parameters)
    {

    }

    ParametedObject::~ParametedObject()
    {
        parameters.clear();
    }

    void ParametedObject::setParam(const String & param, const Variant & data, const String & description)
    {
        parameters[param].data = data;

        if(!description.isEmpty())
            parameters[param].description = description;
    }

    Variant& ParametedObject::getParam(const String & name)
    {
        return parameters[name].data;
    }

    const Variant& ParametedObject::getParam(const String & name) const
    {
        return parameters[name].data;
    }

    String ParametedObject::listParameters() const
    {
        String result;

        result << "ParametedObject \n{";

        for(size_t i = 0; i < parameters.size(); i++)
        {
            const Map<String, Descriptor>::Pair& pair = parameters.getPair(i);
            result << "\n  + " << pair.first() << " : " << pair.second().description;
        }

        result << "\n}";

        return result;
    }
}
