/** @file Keyboard.cpp
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 11/09/2012
 *
 *  @addtogroup Global
 *  @addtogroup System
 *
 *  This file defines the Keyboard class.
 *
**/
#include "Keyboard.h"
#include "Pair.h"

#include <time.h>

namespace APro
{
    Keyboard::Keyboard()
    {
        for(int i = 0; i < 256; i++)
            keyOptions[(KEY) i];
    }

    Keyboard::~Keyboard()
    {

    }

    SharedPointer<Event> Keyboard::createEvent(const String& name) const
    {
        SharedPointer<Event> e = EventEmitter::createEvent(name);
        e->setParam(String("Emitter"), Variant(this), String("Emitter of this event."));

        if(name == "KeyPressedEvent")
        {
            e->setParam(String("Key"), Variant(temp.keyToSend), String("Key Pressed."));
        }
        else if(name == "KeyReleasedEvent")
        {
            e->setParam(String("Key"), Variant(temp.keyToSend), String("Key Released."));
        }

        return e;
    }

    SharedPointer<EventListener> Keyboard::createListener(const String& name) const
    {
        SharedPointer<EventListener> listener(EventEmitter::createListener(name));
        listener->setParam(String("KeyInfos"), Variant(KeyBoardListenerInfo()), String("Infos for each key. Get them with member keyInfos."));
        return listener;
    }

    void Keyboard::loop()
    {
#if APRO_PLATFORM == APRO_WINDOWS
        if(!GetKeyboardState(temp.keys))
            return;
#endif

        if(keyToCheck.isEmpty())
        {
            for(size_t i = 0; i < keyOptions.size(); ++i)
            {
                Map<KEY, KeyOption>::Pair& pair = keyOptions.getPair(i);

                temp.keyToSend = pair.first();

                if(pair.second().pressed)
                {
                    if(isRealPressed(pair.first()))
                    {
                        for(List<SharedPointer<EventListener> >::Iterator i(listeners.begin()); !i.isEnd(); i++)
                        {
                            KeyBoardListenerInfo& info = i.get()->getParam(String("KeyInfos")).to<KeyBoardListenerInfo>();
                            if(info.keyInfos.exists(pair.first()))
                            {
                                Map<KEY, KeyBoardListenerInfo::KeyInfo>::Pair & keyInfo = info.keyInfos.getPair(info.keyInfos.getIndex(pair.first()));
                                if(keyInfo.second().repeat)
                                {
                                    float currentTime = clock() / CLOCKS_PER_SEC * 1000;
                                    if(currentTime - keyInfo.second().lastTime >= keyInfo.second().timelapse)
                                    {
                                        keyInfo.second().lastTime = currentTime;
                                        sendManualEvent(createEvent(String("KeyPressedEvent")), i.get());
                                    }
                                }
                            }
                        }
                    }
                    else
                    {
                        pair.second().pressed = false;
                        sendEvent(createEvent(String("KeyReleasedEvent")));
                    }
                }
                else
                {
                    if(isRealPressed(pair.first()))
                    {
                        pair.second().pressed = true;
                        sendEvent(createEvent(String("KeyPressedEvent")));
                    }
                    else
                    {

                    }
                }
            }
        }
        else
        {
            for(size_t i = 0; i < keyToCheck.size(); ++i)
            {
                Map<KEY, KeyOption>::Pair& pair = keyOptions.getPair(keyToCheck.at(i));

                temp.keyToSend = pair.first();

                if(pair.second().pressed)
                {
                    if(isRealPressed(pair.first()))
                    {
                        for(List<SharedPointer<EventListener> >::Iterator i(listeners.begin()); !i.isEnd(); i++)
                        {
                            KeyBoardListenerInfo& info = i.get()->getParam(String("KeyInfos")).to<KeyBoardListenerInfo>();
                            if(info.keyInfos.exists(pair.first()))
                            {
                                Map<KEY, KeyBoardListenerInfo::KeyInfo>::Pair & keyInfo = info.keyInfos.getPair(info.keyInfos.getIndex(pair.first()));
                                if(keyInfo.second().repeat)
                                {
                                    float currentTime = clock() / CLOCKS_PER_SEC * 1000;
                                    if(currentTime - keyInfo.second().lastTime >= keyInfo.second().timelapse)
                                    {
                                        keyInfo.second().lastTime = currentTime;
                                        sendManualEvent(createEvent(String("KeyPressedEvent")), i.get());
                                    }
                                }
                            }
                        }
                    }
                    else
                    {
                        pair.second().pressed = false;
                        sendEvent(createEvent(String("KeyReleasedEvent")));
                    }
                }
                else
                {
                    if(isRealPressed(pair.first()))
                    {
                        pair.second().pressed = true;
                        sendEvent(createEvent(String("KeyPressedEvent")));
                    }
                    else
                    {

                    }
                }
            }
        }
    }

    bool Keyboard::isPressed(KEY key)
    {
#if APRO_PLATFORM == APRO_WINDOWS
        return keyOptions[key].pressed;
#endif

        return false;
    }

    bool Keyboard::isRealPressed(KEY key)
    {
        return temp.keys[(int) key] >> ((sizeof(Byte)*8)-1);
    }

    void Keyboard::registerKey(KEY key)
    {
        if(keyToCheck.find(key) == -1)
            keyToCheck.append(key);
    }

    void Keyboard::clearRegisteredKeys()
    {
        keyToCheck.clear();
    }


}
