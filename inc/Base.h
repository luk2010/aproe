/** @file Base.h
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 29/05/2012
 *
 *  @addtogroup Global
 *  @addtogroup Memory
 *
 *  This file defines some constants to be used on different platform. This constants are universal.
 *
**/
#ifndef APROBASE_H
#define APROBASE_H

/** Define the OFF state to another define. */
#define APRO_OFF 0

/** Define the ON state to another define. */
#define APRO_ON 1

/** Set if the C++0X should be used. */
#define APRO_USECPLUSPLUS0X APRO_OFF

/** Set if we must use Exception. */
#define APRO_EXCEPTION APRO_ON

/** Defines the Max Buffer Size in Exception. */
#if APRO_EXCEPTION == APRO_ON
#   define APRO_EXCEPTIONMAXBUFFERSIZE 4096
#endif

/** Defines if we use the Memory tracker. */
#define APRO_MEMORYTRACKER APRO_ON

/** Defines the Max Buffer Size in MemoryTracker. */
#if APRO_MEMORYTRACKER == APRO_ON
#   define APRO_MEMORYTRACKERMAXBUFFERSIZE 16384
#endif

/** Set if we can use the Standard Library. */
#define APRO_USESTDLIB APRO_OFF

/** Set ON if you want to use Strict Memory Allocator System (No error will be tolered). */
#define APRO_ALLOCATORSTRICT APRO_ON

/** Defines Debug or Release compilation. */
#if defined(DEBUG) || defined(_DEBUG_) || defined(__DEBUG__)
#   define APRO_DEBUG APRO_ON
#else
#   define APRO_DEBUG APRO_OFF
#endif

/** Set DLL config to export. */
#define APRO_BUILDDLLEXPORT __declspec(dllexport)

/** Set DLL config to import. */
#define APRO_BUILDDLLIMPORT __declspec(dllimport)

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

#endif
