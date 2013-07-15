////////////////////////////////////////////////////////////
/** @file TypeInfo.h
 *  @ingroup Rendering
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 15/06/2013
 *
 *  Defines the TypeInfo class.
 *
**/
////////////////////////////////////////////////////////////
#ifndef APRO_TYPEINFO_H
#define APRO_TYPEINFO_H

#include "Platform.h"
#include "SString.h"
#include <typeinfo>

/* USELESS
namespace APro
{
    template <typename Class>
    class TypeInfo
    {
    private:
        TypeInfo() {}
        ~TypeInfo() {}

    public:

        static String getClassName()
        {
            type_info ti = typeid<Class>;
            ti
        }
    };
}
*/

#endif // APRO_TYPEINFO_H
