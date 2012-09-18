/** @file Platform.h
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 21/05/2012 - 29/05/2012
 *
 *  @addtogroup Global
 *  @addtogroup Memory
 *
 *  This file defines some constants to be used on different platform. This constants are Memory-specific.
 *
**/
#ifndef APROPLATFORM_H
#define APROPLATFORM_H

/** Complete version name of the @ref Memory Module. */
#define APRO_MEMORY_VERSION "0.1A"

#include "Base.h"

#if APRO_EXCEPTION == APRO_ON
#   include "Exception.h"
#endif

#endif
