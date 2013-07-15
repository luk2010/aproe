/////////////////////////////////////////////////////////////
/** @file Printable.h
 *  @ingroup Utils
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 25/05/2013
 *
 *  Defines an interface for printable objects.
 *
**/
/////////////////////////////////////////////////////////////
#ifndef APRO_PRINTABLE_H
#define APRO_PRINTABLE_H

#include "Platform.h"
#include "Console.h"

namespace APro
{
    /////////////////////////////////////////////////////////////
    /** @class Printable
     *  @ingroup utils
     *  @brief Interface for printable in console objects.
    **/
    /////////////////////////////////////////////////////////////
    class Printable
    {
    public:

        /////////////////////////////////////////////////////////////
        /** @brief Destructor
        **/
        /////////////////////////////////////////////////////////////
        virtual ~Printable()
        {

        }

        /////////////////////////////////////////////////////////////
        /** @brief Print information about this object in the console.
        **/
        /////////////////////////////////////////////////////////////
        virtual void print(Console& console) const = 0;
    };

    /////////////////////////////////////////////////////////////
    /** @brief Operator to help print functions.
    **/
    /////////////////////////////////////////////////////////////
    Console& operator << (Console& console, const Printable& printable)
    {
        printable.print(console);
        return console;
    }
}

#endif // APRO_PRINTABLE_H
