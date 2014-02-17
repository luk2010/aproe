////////////////////////////////////////////////////////////
/** @file NameCopyGenerator.cpp
 *  @ingroup Utils
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 15/02/2014
 *
 *  Implements the NameCopyGenerator utility class.
 *
**/
////////////////////////////////////////////////////////////
#include "NameCopyGenerator.h"

namespace APro
{
    String NameCopyGenerator::operator () (const String& name)
    {
        // We try to find a name as MyResource (1)
        //                          MyResource (2)
        //                          MyResource (3)
        //                          ...
        //                          MyResource (2147483647)

        int _cpy = 0;
        if(!isNameUsed(name))
            return name;

        _cpy++;
        String _cpyname;
        do
        {
            _cpyname = name;
            _cpyname.append(" (");
            _cpyname.append(String::fromInt(_cpy));
            _cpyname.append(")");

        } while (isNameUsed(name));

        return _cpyname;
    }
}
