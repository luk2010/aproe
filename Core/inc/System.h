/** @file System.h
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 21/05/2012
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

/** Set Platform to WindowsCE. */
#define APRO_WINDOWSCE 2

/** Set Platform to Linux. */
#define APRO_LINUX 3

/** Set Platform to OS X. */
#define APRO_OSX 4

//----------------------------------------------//
//                   Windows                    //
//----------------------------------------------//

#if defined(_WIN32) || defined(_WIN64) || defined(WIN32) || defined(WIN64)
#   define APRO_PLATFORM APRO_WINDOWS
#   define __WIN
#   define WIN
#   include <windows.h>
#   include <Windowsx.h>
#   define FSTAT _stat
#endif

//----------------------------------------------//
//                 Windows CE                   //
//----------------------------------------------//

#if defined(_WIN32_WCE)
#   define APRO_PLATFORM APRO_WINDOWSCE
#   include <windows.h>
#   define FSTAT _stat
#endif

//----------------------------------------------//
//                    OS X                      //
//----------------------------------------------//

#if defined(_APPLE_) || defined(MACOSX)
#   if !defined(MACOSX)
#       define MACOSX
#   endif
#
#   define APRO_PLATFORM APRO_OSX
#   define FSTAT stat
#endif

//----------------------------------------------//
//                   Linux                      //
//----------------------------------------------//

#ifndef APRO_PLATFORM
#   define APRO_PLATFORM APRO_LINUX
//#   include <X11/Xlib.h>
#   define FSTAT stat
#endif

#endif
