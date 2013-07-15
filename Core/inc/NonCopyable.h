////////////////////////////////////////////////////////////
/** @file NonCopyable.h
 *  @ingroup Utils
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 17/05/2013
 *
 *  Defines the NonCopyable class.
 *
**/
////////////////////////////////////////////////////////////
#ifndef APRO_NONCOPYABLE_CLASS_H
#define APRO_NONCOPYABLE_CLASS_H

#include "Platform.h"

namespace APro
{
    ////////////////////////////////////////////////////////////
    /** @class NonCopyable
     *  @ingroup Utils
     *  @brief Let subclass be non copyable.
    **/
    ////////////////////////////////////////////////////////////
    class NonCopyable
    {
    protected:

        NonCopyable() {}
        ~NonCopyable() {}

    private:

        NonCopyable(const NonCopyable& );
        NonCopyable& operator = (const NonCopyable&);
    };
}

#endif // APRO_NONCOPYABLE_CLASS_H
