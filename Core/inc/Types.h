////////////////////////////////////////////////////////////
/** @file Types.h
 *  @ingroup Utils
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 14/10/2013
 *
 *  Types namespace for Types helpers.
 *
**/
////////////////////////////////////////////////////////////
#ifndef APRO_TYPES_H
#define APRO_TYPES_H

#include "Platform.h"
#include <type_traits>

namespace APro
{
    namespace Types
    {
        ////////////////////////////////////////////////////////////
        /** @brief Tell if a Type has a destructor.
        **/
        ////////////////////////////////////////////////////////////
        template<typename T>
        APRO_DLL bool IsDestructible() { return std::is_destructible<T>::value; }

        ////////////////////////////////////////////////////////////
        /** @brief Tell if a Type has a constructor that correspond to
         *  given Args.
        **/
        ////////////////////////////////////////////////////////////
        template <typename T, typename... Args>
        APRO_DLL bool IsConstructible() { return std::is_constructible<T, Args>::value; }

        ////////////////////////////////////////////////////////////
        /** @brief Tell if a Type is constructible by copy.
        **/
        ////////////////////////////////////////////////////////////
        template <typename T>
        APRO_DLL bool IsCopyConstructible() { return std::is_copy_constructible<T>::value; }

        ////////////////////////////////////////////////////////////
        /** @brief Tell if a Type is a class.
        **/
        ////////////////////////////////////////////////////////////
        template <typename T>
        APRO_DLL bool IsClass() { return std::is_class<T>::value; }
    }
}

#endif // APRO_TYPES_H
