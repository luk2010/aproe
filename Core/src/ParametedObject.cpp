/////////////////////////////////////////////////////////////
/** @file ParametedObject.h
 *  @ingroup Utils
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 01/09/2012 - 20/04/2014
 *
 *  Implements the ParametedObject class.
 *
**/
/////////////////////////////////////////////////////////////
#include "ParametedObject.h"

namespace APro
{
    ParametedObject::ParametedObject()
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

    void ParametedObject::print(Console& console) const
    {
        console << "ParametedObject \n{";

        ParametersMap::const_iterator e = parameters.end();
        for(ParametersMap::iterator it = parameters.begin(); it != e; it++)
            console << "\n  + " << it.key() << " : " << it.value().description;

        console << "\n}";
    }
}
