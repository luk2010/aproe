/** @file Singleton.h
 *  @ingroup Utils
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 25/06/2012
 *
 *  Defines the Singleton interface.
 *
**/
#ifndef APROSINGLETON_H
#define APROSINGLETON_H

#include "Platform.h"
#include "NonCopyable.h"

namespace APro
{
    ////////////////////////////////////////////////////////////
    /** @class Singleton
     *  @ingroup Utils
    **/
    ////////////////////////////////////////////////////////////
    template <typename T>
    class Singleton : public NonCopyable
    {
    protected:

        Singleton() { /* */ }
        ~Singleton() { /* */ }

    };

    #define APRO_DECLARE_SINGLETON(class) \
    public: \
    static class& get();

    #define APRO_IMPLEMENT_SINGLETON(class) \
    class& class::get()\
    { static class singleton; return singleton;  }
}

#endif
