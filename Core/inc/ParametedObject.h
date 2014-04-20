/////////////////////////////////////////////////////////////
/** @file ParametedObject.h
 *  @ingroup Utils
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 01/09/2012 - 20/04/2014
 *
 *  Defines the ParametedObject class.
 *
**/
/////////////////////////////////////////////////////////////
#ifndef APROPARAMETEDOBJECT_H
#define APROPARAMETEDOBJECT_H

#include "Platform.h"
#include "Map.h"
#include "Variant.h"
#include "SString.h"
#include "NonCopyable.h"
#include "Printable.h"

namespace APro
{
    /////////////////////////////////////////////////////////////
    /** @class ParametedObject
     *  @ingroup Utils
     *  @brief An object with custom parameters.
     *
     *  Use this object to create a parameted object. You can store
     *  custom parameters that can be used by other objects and can
     *  be added at run-time.
     *
     *  @warning You should not use too much this object as
     *  dynamic casting and map access are expensive operations.
     *
     *  @note Parameters are constructed when setted and destroyed
     *  in the destructors. You do not have to free them.
    **/
    /////////////////////////////////////////////////////////////
    class APRO_DLL ParametedObject : public NonCopyable,
                                     public Printable
    {
    public:

        /////////////////////////////////////////////////////////////
        /** @brief An entry in the parameters map.
        **/
        /////////////////////////////////////////////////////////////
        typedef struct Descriptor
        {
            Variant data;       ///< Stores the data.
            String  description;///< Description of the data.
        } Descriptor;

        typedef Map<String, Descriptor> ParametersMap;
        ParametersMap parameters; ///< Stored parameters.

    public:

        /////////////////////////////////////////////////////////////
        /** @brief Constructs an empty parameted object.
        **/
        /////////////////////////////////////////////////////////////
        ParametedObject();

        /////////////////////////////////////////////////////////////
        /** @brief Destructs the Parameted object.
        **/
        /////////////////////////////////////////////////////////////
        ~ParametedObject();

    public:

        /////////////////////////////////////////////////////////////
        /** @brief Set a new parameter.
         *  @param param : Name of the param to set.
         *  @param data : Data to set.
         *  @param description : Description of the data to set. If this
         *  field is empty, current description is not overwritten.
        **/
        /////////////////////////////////////////////////////////////
        void setParam(const String & param, const Variant& data, const String & description = String());

        /////////////////////////////////////////////////////////////
        /** @brief Returns parameter form given name.
        **/
        /////////////////////////////////////////////////////////////
        Variant& getParam(const String & name);

        /////////////////////////////////////////////////////////////
        /** @brief Returns parameter form given name.
        **/
        /////////////////////////////////////////////////////////////
        const Variant& getParam(const String & name) const;

    public:

        /////////////////////////////////////////////////////////////
        /** @brief Print information about this object in the console.
        **/
        /////////////////////////////////////////////////////////////
        virtual void print(Console& console) const;
    };
}

#endif
