/** @file ParametedObject.h
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
#ifndef APROPARAMETEDOBJECT_H
#define APROPARAMETEDOBJECT_H

#include "Platform.h"
#include "Map.h"
#include "Variant.h"
#include "SString.h"

namespace APro
{
    class APRO_DLL ParametedObject
    {
    public:

        typedef struct Descriptor
        {
            Variant data;
            String description;
        } Descriptor;

    public:

        ParametedObject();
        ParametedObject(const ParametedObject& other);

        ~ParametedObject();

    public:

        void setParam(const String & param, const Variant& data, const String & description = String());

        Variant& getParam(const String & name);
        const Variant& getParam(const String & name) const;

        String listParameters() const;

    private:

        Map<String, Descriptor> parameters;
    };
}

#endif
