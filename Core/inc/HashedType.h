////////////////////////////////////////////////////////////
/** @file HashedType.h
 *  @ingroup Utils
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 22/12/2013 - 23/12/2013
 *
 *  Defines the HashedType class.
 *
**/
////////////////////////////////////////////////////////////
#ifndef APRO_HASHEDTYPE_H
#define APRO_HASHEDTYPE_H

#include "Platform.h"

namespace APro
{
    ////////////////////////////////////////////////////////////
    /** @class HashedType
     *  @ingroup Core
     *  @brief A general type containing a Hash identifier.
     *
     *  You can add a hash identifier to your class, subclassing
     *  this one and using the Macros APRO_DECLARE_HASHEDTYPE in the
     *  header of your class, and APRO_IMPLEMENT_HASHEDTYPE in the
     *  source file of your class.
     *
     *  ### Subclassing types already Hashed
     *
     *  If you subclass types that already have Hash, you shouldn't
     *  re-use the two macros in most commons cases. In some
     *  exceptionnal cases, you can use these macros to specialize
     *  and independantalize your type, so there will be no link
     *  with the parent class.
    **/
    ////////////////////////////////////////////////////////////
    class HashedType
    {
    public:

        HashedType() {}
        virtual ~HashedType() {}

        ////////////////////////////////////////////////////////////
        /** @brief Retuurn the Hash of this class. This correspond
         *  exactly to the static member Hash of this class.
        **/
        ////////////////////////////////////////////////////////////
        virtual HashType getHash() const = 0;
    };

/// @def APRO_DECLARE_HASHEDTYPE
/// @ingroup Utils
/// @brief Declare a HashedType.
#define APRO_DECLARE_HASHEDTYPE \
public: \
HashType getHash() const; \
static HashType Hash

/// @def APRO_IMPLEMENT_HASHEDTYPE(type)
/// @ingroup Utils
/// @brief Implements a HashedType.
#define APRO_IMPLEMENT_HASHEDTYPE(type) \
HashType type::getHash() const { return type::Hash; } \
HashType type::Hash = String::Hash( TOTEXT(type) )

}

#endif // APRO_HASHEDTYPE_H
