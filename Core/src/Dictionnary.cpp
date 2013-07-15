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
    void Dictionnary::print(Console& console)
    {
        console << "Dictionnary \n[";

        for(size_t i = 0; i < size(); ++i)
        {
            const Dictionnary::Pair& pair = getPair(i);
            console << "\n \"" << pair.first() << "\"";
        }

        console << "\n]";
    }
}
