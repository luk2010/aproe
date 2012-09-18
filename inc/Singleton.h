/** @file Singleton.h
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 25/06/2012
 *
 *  @addtogroup Global
 *  @addtogroup Utils
 *
 *  This file defines the Singleton interface.
 *
**/
#ifndef APROSINGLETON_H
#define APROSINGLETON_H

#include "Memory.h"
#include "Platform.h"
#include "Allocator.h"

namespace APro
{
    template <typename T>
    class Singleton
    {
    protected:

        Singleton() { /* */ }
        ~Singleton() { /* */ }

    private:

        Singleton(Singleton&) { /* */ }
        Singleton(const Singleton&) { /* */ }
        void operator = (Singleton&) { /* */ }

    };

    #define APRO_DECLARE_SINGLETON(class) \
    public: \
    static class& get();

    #define APRO_IMPLEMENT_SINGLETON(class) \
    class& class::get()\
    { static class singleton; return singleton;  }
}

#endif
