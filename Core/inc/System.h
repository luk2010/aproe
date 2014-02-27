/** @file System.h
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 21/05/2012 - 27/02/2014
 *
 *  @addtogroup Global
 *  @addtogroup Memory
 *
 *  This file defines the basics system-specific constants.
 *
**/
#ifndef APROSYSTEM_H
#define APROSYSTEM_H

//----------------------------------------------//
//            Microsoft Visual Studio           //
//----------------------------------------------//

#if defined(_MSC_VER) && (_MSC_VER < 1300)
#  error "Microsoft Visual studio 7 ou + seulement est supporte !"
#endif

//----------------------------------------------//
//                  Endianness                  //
//----------------------------------------------//

#ifndef __LITTLE_ENDIAN__
	#ifndef __BIG_ENDIAN__
		#define __LITTLE_ENDIAN__
	#endif
#endif

/** Set the Endianness to Little Endian. */
#define APRO_LITTLEENDIAN 0

/** Set the Endianness to Big Endian. */
#define APRO_BIGENDIAN 1

/** Defines the actual endianness of the current architecture. */
#ifdef __LITTLE_ENDIAN__
#   define APRO_ENDIANNESS APRO_LITTLEENDIAN
#else
#   define APRO_ENDIANNESS APRO_BIGENDIAN
#endif

class Endianness
{
public:
    enum t
    {
        Little = 0,
        Big = 1
    };

    static t endianness()
    {
        return (t) APRO_ENDIANNESS;
    }
};

//----------------------------------------------//
//                Architecture                  //
//----------------------------------------------//

/** Set the Architecture to 32bit. */
#define APRO_32 0

/** Set the Architecture to 64bit. */
#define APRO_64 1

/** Defines the actual architecture of the processor. */
#if defined(__x86_64__) || defined(_M_X64) || defined(__powerpc64__) || defined(__alpha__) || defined(__ia64__) || defined(__s390__) || defined(__s390x__)
#   define APRO_ARCHITECTURE APRO_64
#else
#   define APRO_ARCHITECTURE APRO_32
#endif

//----------------------------------------------//
//              Platforms defines               //
//----------------------------------------------//

/** Set Platform to Windows. */
#define APRO_WINDOWS 1

/** Set Platform to Linux. */
#define APRO_LINUX 2

/** Set Platform to OS X. */
#define APRO_OSX 3

// Inclusion des fichiers d'entetes globaux
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <dirent.h>

//----------------------------------------------//
//                   Windows                    //
//----------------------------------------------//

#ifdef __windows__
#   define APRO_PLATFORM APRO_WINDOWS

#   include <windows.h>
#   include <windowsx.h>
#   include <Shlwapi.h>
#   include <userenv.h>

#   define FSTAT _stat
#   define APRO_BUILDDLLEXPORT __declspec(dllexport)
#   define APRO_BUILDDLLIMPORT __declspec(dllimport)
#endif

//----------------------------------------------//
//                    OS X                      //
//----------------------------------------------//

#ifdef __macosx__
#   define APRO_PLATFORM APRO_OSX
#   define FSTAT stat
#endif

//----------------------------------------------//
//                   Linux                      //
//----------------------------------------------//

#ifdef __linux__
#   define APRO_PLATFORM APRO_LINUX
#   define FSTAT stat
#endif // __linux__

#ifndef __windows__
#   include <unistd.h>
#   define APRO_BUILDDLLEXPORT
#   define APRO_BUILDDLLIMPORT
#endif // __windows__

#endif
