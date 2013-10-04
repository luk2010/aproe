/** @file Base.h
 *  @ingroup Global
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 29/05/2012
 *
 *  Defines some constants to be used on different platform. This constants are universal.
 *
**/
#ifndef APROBASE_H
#define APROBASE_H

/** @def TOTEXT(a)
 *  Transform something into text.
**/
#define TOTEXT(a) #a

/** Define the OFF state to another define. */
#define APRO_OFF 0

/** Define the ON state to another define. */
#define APRO_ON 1

/** Set if the C++0X should be used. */
#define APRO_USECPLUSPLUS0X APRO_ON

/** Set if we can use the Standard Library. */
#define APRO_USESTDLIB APRO_OFF

/** Set ON if you want to use Strict Memory Allocator System (No error will be tolered). */
#define APRO_ALLOCATORSTRICT APRO_ON

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

/** Set DLL config to export. */
#define APRO_BUILDDLLEXPORT /* __declspec(dllexport)*/

/** Set DLL config to import. */
#define APRO_BUILDDLLIMPORT /* __declspec(dllimport)*/

/** Defines either DLL is export or import. */
#if defined(BUILD_DLL) || defined(DLL) || defined(__DLL__)
#   define APRO_DLL APRO_BUILDDLLEXPORT
#else
#   define APRO_DLL APRO_BUILDDLLIMPORT
#endif

#if APRO_USECPLUSPLUS0X == APRO_OFF
#   define nullptr NULL
#endif

#include "System.h"

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

typedef char                Byte;       ///< Represents a byte (8 bits).
typedef long int            Offset;     ///< Represents an adress offset.
// typedef unsigned long int   Id; // Defined in IdGenerator.h

typedef REAL_TYPE           unit_t;     ///< Represents the system unit measure.
typedef unit_t              Real;       ///< Represents a number in the system unit measure.

typedef ANGLE_TYPE           angle_t;    ///< Represents an angle in the system unit measure.
typedef angle_t             Radian;     ///< Represents a Radian angle measure.
typedef angle_t             Degree;     ///< Represents a Degree angle measure.

typedef uint8_t             u8;
typedef uint16_t            u16;
typedef uint32_t            u32;
typedef uint64_t            u64;

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
#   define aprodebug(a) Console::get() << "\n" << __FUNCTION__ << " (" << __LINE__ << ") : " << a
#else
#   define aprodebug(a)
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

////////////////////////////////////////////////////////////
/** @brief Return the name of a given class.
**/
////////////////////////////////////////////////////////////
template<typename T>
const char* className()
{
    return TOTEXT(T);
}

#endif
