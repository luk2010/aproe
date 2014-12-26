/////////////////////////////////////////////////////////////
/** @file Dictionnary.cpp
 *  @ingroup Utils
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 17/09/2012
 *
 *  Implements the Dictionnary class.
 *
**/
/////////////////////////////////////////////////////////////
#include "Dictionnary.h"

namespace APro
{
    void Dictionnary::print(Console& console) const
    {
        console << "Dictionnary \n[";

        const_iterator e = end();
        for(const_iterator it = begin(); it != e; it++)
            console << "\n \"" << it.key() << "\"";

        console << "\n]";
    }
}
