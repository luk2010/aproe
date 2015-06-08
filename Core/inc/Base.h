/** @file Base.h
 *  @ingroup Global
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 29/05/2012 - 05/06/2015
 *
 *  Defines some constants to be used on different platform. 
 *  This constants are universal.
 *
 *  @copyright
 *  Atlanti's Project Engine
 *  Copyright (C) 2012 - 2015  Atlanti's Corp
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
**/
#ifndef APROBASE_H
#define APROBASE_H

#define CONCAT_I(a, b) a ## b
#define CONCAT(a, b) CONCAT_I(a, b)

/** @def TOTEXT(a)
 *  Transform something into text.
**/
#define TOTEXT(a) #a

/** Define the OFF state to another define. */
#define APRO_OFF 0

/** Define the ON state to another define. */
#define APRO_ON 1

/** Defines Debug or Release compilation. */
#if _HAVE_DEBUG_MODE_
#   define APRO_DEBUG APRO_ON
#else
#   define APRO_DEBUG APRO_OFF
#endif

#if APRO_DEBUG == APRO_ON
#   if _HAVE_EXCEPTIONS_
        /** Set if we must use Exception. */
#       define APRO_EXCEPTION APRO_ON
        /** Defines the Max Buffer Size in Exception. */
#       define APRO_EXCEPTIONMAXBUFFERSIZE 4096
#   endif

#   if _HAVE_MEMORYTRACKER_
        /** Defines if we use the Memory tracker. */
#       define APRO_MEMORYTRACKER APRO_ON
#   endif
#endif

/** Defines the Max Buffer Size in MemoryTracker. */
#if APRO_MEMORYTRACKER == APRO_ON
#   define APRO_MEMORYTRACKERMAXBUFFERSIZE 16384
#endif

#include "System.h"

/** Defines either DLL is export or import. */
#ifdef __builddll__
#   define APRO_DLL APRO_BUILDDLLEXPORT
#else
#   define APRO_DLL APRO_BUILDDLLIMPORT
#endif

#if defined _USE_DOUBLEREAL_
#   define REAL_TYPE double
#else
#   define REAL_TYPE float
#endif

#if defined _USE_DOUBLEANGLE_
#   define ANGLE_TYPE double
#else
#   define ANGLE_TYPE float
#endif

namespace APro
{
    typedef uint8_t             u8;
    typedef uint16_t            u16;
    typedef uint32_t            u32;
    typedef uint64_t            u64;

    typedef u8                  Byte;       ///< Represents a byte (8 bits).
    typedef u64                 Offset;     ///< Represents an adress offset.

    typedef REAL_TYPE           unit_t;     ///< Represents the system unit measure.
    typedef unit_t              Real;       ///< Represents a number in the system unit measure.

    typedef ANGLE_TYPE          angle_t;    ///< Represents an angle in the system unit measure.
    typedef angle_t             Radian;     ///< Represents a Radian angle measure.
    typedef angle_t             Degree;     ///< Represents a Degree angle measure.

    typedef unsigned int        HashType;   ///< A standard hash type.
    typedef signed   long       Id;         ///< A generic id type.


// ---------------------------------------------------
// Compile-time assertions
// ---------------------------------------------------
// Here we assert that every type has a correct size. This
// is necessary for different processor architecture, as
// x86 or x64.

    CCASSERT(sizeof(char) == 1)                 // char = 1 Byte  (8 bits)
    CCASSERT(sizeof(Byte) == 1)                 // BYTE = 1 Byte  (8 bits)
    CCASSERT(sizeof(u8)   == 1)                 // u8   = 1 Byte  (8 bits)
    CCASSERT(sizeof(u16)  == 2)                 // u16  = 2 Bytes (16 bits)
    CCASSERT(sizeof(u32)  == 4)                 // u32  = 4 Bytes (32 bits)
    CCASSERT(sizeof(u64)  == 8)                 // u64  = 8 Bytes (64 bits)

#ifdef _USE_DOUBLEREAL_
    CCASSERT(sizeof(unit_t) == sizeof(double))  // unit_t = 8 Bytes (64 bits)
#else
    CCASSERT(sizeof(unit_t) == sizeof(float))   // unit_t = 4 Bytes (32 bits)
#endif // _USE_DOUBLEREAL_

#ifdef _USE_DOUBLEANGLE_
    CCASSERT(sizeof(angle_t) == sizeof(double)) // angle_t = 8 Bytes (64 bits)
#else
    CCASSERT(sizeof(angle_t) == sizeof(float))  // angle_t = 4 Bytes (32 bits)
#endif // _USE_DOUBLEANGLE_

// ---------------------------------------------------

    union FloatIntReinterpret
    {
        float f;
        u32   i;
    };

    /// Returns the bit pattern of the given float as a u32.
    u32 ReinterpretAsU32(float& f)
    {
        FloatIntReinterpret fi;
        fi.f = f;
        return fi.i;
    }

    /// Converts the bit pattern specified by the given integer to a floating point (this is a binary conversion, not numeral!).
    float ReinterpretAsFloat(u32& i)
    {
        FloatIntReinterpret fi;
        fi.i = i;
        return fi.f;
    }

    union DoubleIntReinterpret
    {
        double d;
        u64    i;
    };

    /// Returns the bit pattern of the given double as a u64.
    u64 ReinterpretAsU64(double& d)
    {
        DoubleIntReinterpret di;
        di.d = d;
        return di.i;
    }

    /// Converts the bit pattern specified by the given integer to a double (this is a binary conversion, not numeral!).
    double ReinterpretAsDouble(u64& i)
    {
        DoubleIntReinterpret di;
        di.i = i;
        return di.d;
    }

    ////////////////////////////////////////////////////////////
    /** @brief Return the name of a given class.
    **/
    ////////////////////////////////////////////////////////////
    template<typename T>
    const char* className()
    {
        static const char* _name = TOTEXT(T);
        return _name;
    }

    /////////////////////////////////////////////////////////////
    /** @brief Tell if one comparable object is less than another
     *  one.
     *
     *  Use this function as a standard comparator. It is the same
     *  implementation as std::less but we provide it for
     *  simple use.
     *
     *  @return true if a is less than b.
    **/
    /////////////////////////////////////////////////////////////
    template <class T> struct is_less {
        bool operator() (const T& x, const T& y) const { return x < y; }
    };

    /////////////////////////////////////////////////////////////
    /** @brief Block given calling Thread while a given boolean is
     *  different from given boolean value.
    **/
    /////////////////////////////////////////////////////////////
    void __wait_boolean__(bool* b, bool result) { while (*b != result); }

    enum Intersection
    {
        INTIN,
        INTOUT,
        INTBETWEEN
    };
    
    /////////////////////////////////////////////////////////////
    /** @brief A generic enum descriving Compareason results.
    **/
    /////////////////////////////////////////////////////////////
    enum class CompareResult
    {
    	Inferior,
    	Equal,
    	Superior
    };
    
    template <typename T>
    using Invoke = typename T::type;
    
    template <typename Condition>
    using EnableIf = Invoke<std::enable_if<Condition::value> >;
}

////////////////////////////////////////////////////////////
/** @def aprodebug(a)
 *
 *  Print a message using the console, giving function and
 *  line.
 *  @note Console must be included.
 *
 *  @def aproassert(condition, message)
 *
 *  Make an assertion from a condition, and print it if
 *  false, or throw an exception if setted.
**/
////////////////////////////////////////////////////////////

#if APRO_DEBUG == APRO_ON
#   define aprodebug(a) Console::Get() << "\n" << __FUNCTION__ << " (" << __LINE__ << ") : " << a
#else
#   define aprodebug(a) EmptyConsole::Get()
#endif

#if APRO_DEBUG == APRO_ON
#   if defined(_HAVE_EXCEPT_ON_ASSERT_) && defined(_HAVE_EXCEPTIONS_)
#       include "Assert.h"
#       define aproassert(condition, message) __assert_with_except(condition, message, TOTEXT(condition))
#   else
#       define aproassert(condition, message) \
if(!(condition) ) \
{ \
    Console::get() << "\nAssertion failed ! [\"" << #condition << "\"](\"" << __FUNCTION__ << "\") " << aprodebug(message); \
}
#   endif
#else
#   define aproassert(a,b)
#endif

#define aproassert1(a) aproassert(a, "")

#endif // APRO_BASE_H

