/////////////////////////////////////////////////////////////
/** @file EventUniter.cpp
 *  @ingroup Event
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 02/12/2013 - 19/01/2015
 *
 *  @brief
 *  Implements the EventUniter object.
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
/////////////////////////////////////////////////////////////
#include "EventUniter.h"
#include "ThreadManager.h"

namespace APro
{
    APRO_IMPLEMENT_MANUALSINGLETON(EventUniter)

    EventUniter::EventUniter(const String& n)
        : Thread(n)
    {

    }

    EventUniter::~EventUniter()
    {
        terminate();
        
		while(commands.size() > 0) {
			if(commands.get().eventptr) {
				AProDelete (commands.get().eventptr);
			}
			commands.pop();
		}
    }

    void EventUniter::push(SendCommand& command)
    {
        APRO_THREADSAFE_AUTOLOCK
        commands.push(command);
        
        if(isidling) 
		{
			isidling = false;
			idlecondition.signal();
		}
    }

    void EventUniter::exec()
    {
        // Infinite loop to send events to listeners.
        // This loop can and should be terminated by the
        // destructor of this class.
        while(1)
        {
            SendCommand command;
            {
            	APRO_THREADSAFE_AUTOLOCK
            	
				if(commands.isEmpty())
				{
					// If queue is empty, we wait for push() function to signal us
					// that it is not anymore.
					isidling = true;
					idlecondition.wait(&getMutex());
				}
                
                command = commands.get();
                commands.pop();
            }

            if(command.eventptr == nullptr || ! command.eventptr->isValid())
            {
                aprodebug("Incorrect event given.");
                continue;
            }

            if(command.eventptr->mustStop())
            {
                aprodebug("Event has stop flag setted.");
                AProDelete(command.eventptr);
                continue;
            }

            if(!command.listeners.isEmpty())
            {
                for(uint32_t i = 0; i < command.listeners.size(); ++i) {
					EventListenerPtr& listener = command.listeners.at(i);
					listener->receive( (EventRef) *(command.eventptr));
					if(command.eventptr->mustStop()) {
						break;
					}
                }
                
                AProDelete(command.eventptr);
            }
        }
    }


}
