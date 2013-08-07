/** @file EventEmitter.cpp
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 11/09/2012
 *
 *  @addtogroup Global
 *  @addtogroup System
 *
 *  This file defines the EventEmitter class.
 *
**/
#include "EventEmitter.h"
#include "Console.h"
#include "StringStream.h"

namespace APro
{
    EventEmitter::EventEmitter()
    {
        
    }
    
    EventEmitter::EventEmitter(const EventEmitter& emitter)
    {
        listeners = emitter.listeners;
        events    = emitter.events;
    }
    
    
}
