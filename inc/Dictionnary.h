/** @file Dictionnary.h
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 17/09/2012
 *
 *  @addtogroup Global
 *  @addtogroup Memory
 *
 *  This file defines the Dictionnary class.
 *
**/
#ifndef APRODICTIONNARY_H
#define APRODICTIONNARY_H

#include "Map.h"
#include "SString.h"
#include "Variant.h"

namespace APro
{
    typedef Map<String, Variant> Dictionnary;
}

#endif
