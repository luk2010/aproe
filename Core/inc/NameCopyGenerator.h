////////////////////////////////////////////////////////////
/** @file NameCopyGenerator.h
 *  @ingroup Utils
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 15/02/2014
 *
 *  Defines the NameCopyGenerator utility class.
 *
**/
////////////////////////////////////////////////////////////
#ifndef APRO_NAMECOPYGENERATOR_h
#define APRO_NAMECOPYGENERATOR_h

#include "Platform.h"

namespace APro
{
    ////////////////////////////////////////////////////////////
    /** @class NameCopyGenerator
     *  @ingroup Utils
     *  @brief A class function to generate copy name for already
     *  used name.
     *
     *  Subclass this class and overwrite the function isNameUsed()
     *  as you want to create names that are not used.
    **/
    ////////////////////////////////////////////////////////////
    class NameCopyGenerator
    {
    public:

        /////////////////////////////////////////////////////////////
        /** @brief Constructs the NCG.
        **/
        /////////////////////////////////////////////////////////////
        NameCopyGenerator() { }

        /////////////////////////////////////////////////////////////
        /** @brief Use this operator to generate a non-used name.
        **/
        /////////////////////////////////////////////////////////////
        String operator () (const String& name);

        /////////////////////////////////////////////////////////////
        /** @brief Overwrite this function when creating a specific
         *  name generator.
        **/
        /////////////////////////////////////////////////////////////
        virtual bool isNameUsed(const String& name) const { return false; };
    };
}

#endif // APRO_NAMECOPYGENERATOR_h
