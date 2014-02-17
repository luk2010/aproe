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
    static class& Get();

    #define APRO_IMPLEMENT_SINGLETON(class) \
    class& class::Get()\
    { static class singleton; return singleton;  }

    /// @brief Macro to define Main constructed classes.
    /// Harmonize the current functions in the SuperClass initialized
    /// in the Main Singleton.
    #define APRO_DECLARE_MANUALSINGLETON(class) public: \
        static class * __curent_##class ; \
        static bool IsCreated() { return __current_##class != nullptr; } \
        static class & Get() { return *__current_##class ; } \
        static class * GetPtr() { return __current_##class ; }

    #define APRO_IMPLEMENT_MANUALSINGLETON(class) \
        class * class##::__current_##class = nullptr;
}

#endif
