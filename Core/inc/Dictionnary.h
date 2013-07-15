/////////////////////////////////////////////////////////////
/** @file Dictionnary.h
 *  @ingroup Utils
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 17/09/2012
 *
 *  Defines the Dictionnary class.
 *
**/
/////////////////////////////////////////////////////////////
#ifndef APRODICTIONNARY_H
#define APRODICTIONNARY_H

#include "Map.h"
#include "SString.h"
#include "Variant.h"
#include "Printable.h"

namespace APro
{
    /////////////////////////////////////////////////////////////
    /** @class Dictionnary
     *  @ingroup Utils
     *  @brief Describes a variant map based on string keys.
    **/
    /////////////////////////////////////////////////////////////
    class Dictionnary : public Map<String, Variant>,
                        public Printable
    {
    public:

        virtual ~Dictionnary() {}
        virtual void print(Console& console);
    };
}

#endif
