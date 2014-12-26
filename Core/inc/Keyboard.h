/** @file Keyboard.h
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
#ifndef APROKEYBOARD_H
#define APROKEYBOARD_H

#include "Keys.h"
#include "EventEmitter.h"
#include "Implementable.h"

namespace APro
{
/*
    class APRO_DLL Keyboard : public EventEmitter
    {

    public:

        class KeyBoardListenerInfo
        {
        public:

            typedef struct KeyInfo
            {
                bool repeat;
                float timelapse;
                float lastTime;

                KeyInfo() : repeat(false), timelapse(0.0f), lastTime(0.0f)
                {

                }

            } KeyInfo;

        public:

            KeyBoardListenerInfo()
            {

            }

            ~KeyBoardListenerInfo()
            {

            }

            Map<KEY, KeyInfo> keyInfos;
        };

    public:

        Keyboard();
        ~Keyboard();

    public:

        SharedPointer<Event> createEvent(const String& name) const;
        SharedPointer<EventListener> createListener(const String& name) const;

    public:
        void loop();

        void registerKey(KEY key);
        void clearRegisteredKeys();

    private:

        typedef struct KeyOption
        {
            bool pressed;

            KeyOption() : pressed(false)
            {

            }

        } KeyOption;

        typedef struct TempInfo
        {
            KEY keyToSend;
            key_t keys[256];
        } TempInfo;

    private:

        List<KEY> keyToCheck;
        Map<KEY, KeyOption> keyOptions;
        TempInfo temp;

    private:

        bool isPressed(KEY key);
        bool isRealPressed(KEY key);
    };


    class APRO_DLL KeyBoard : public EventEmitter,
                              public Implementable<KeyBoardImplementation>
    {

        APRO_DECLARE_SHAREDPOINTER_CLASS_TYPEDEF(KeyBoard)

    public:

        Event::ptr createEvent(const String& name) const;

    public:

        KeyBoard();
        ~KeyBoard();

    public:

        void loop();

    public:

        bool isKeyPressed(key_t key);
        bool isKeyReleased(key_t key);



    };
*/
}

#endif
