////////////////////////////////////////////////////////////
/** @file Path.h
 *  @ingroup Utils
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 27/02/2014 - 06/05/2014
 *
 *  Defines the Path class.
 *
**/
////////////////////////////////////////////////////////////
#ifndef APRO_PATH_H
#define APRO_PATH_H

#include "Platform.h"
#include "SString.h"

namespace APro
{
    class Path : public String
    {
    public:

        static Path Invalid;

        Path();
        Path(const String& str);

        bool exists() const;
        String getLastElement() const;
    };
}

#endif // APRO_PATH_H
