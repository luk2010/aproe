/** @file Window.h
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 03/09/2012
 *
 *  @addtogroup Global
 *  @addtogroup System
 *
 *  This file defines the Window class.
 *
**/
#ifndef APROWINDOW_H
#define APROWINDOW_H

#include "Resource.h"
#include "ParametedObject.h"
#include "SString.h"
#include "Pair.h"
#include "EventEmitter.h"
#include "Keyboard.h"

namespace APro
{
    class APRO_DLL Window : public ParametedObject,
                            public EventEmitter
    {
    public:

        class Status
        {
        public:
            enum _
            {
                Created,
                Showed,
                Hidden,
                HasToBeReset,
                Null
            };
        };

    public:

        Window();
        Window(const String& name, const String & title, const String & sz = String("1024x768"));
        Window(const Window& other);

        ~Window();

        bool create();

        void show();
        void hide();
        void move(int x, int y, bool relative = false);

        void destroy();

        void resize(size_t width, size_t height);
        void setTitle(const String& other);

        bool isFullScreen() const;
        void fullscreen(bool toggle);

        Status::_ status() const;

        String name() const;
        String title() const;

        Pair<size_t, size_t> size() const;
        Pair<size_t, size_t> position() const;

        void systemLoop();

        bool reset();

        void showCursor(bool s) const;

        SharedPointer<Event> createEvent(const String& name) const;

        SharedPointer<Keyboard> getKeyboard();

    private:

        SharedPointer<Keyboard> keyboard;
    };
}

#endif
