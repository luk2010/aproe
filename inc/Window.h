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
#include "Context.h"
#include "WindowImplementation.h"
#include "Implementable.h"

namespace APro
{
    class APRO_DLL Window : public ParametedObject,
                            public EventEmitter,
                            public Implementable<WindowImplementation>
    {

        APRO_DECLARE_SHAREDPOINTER_CLASS_TYPEDEF(Window)
        
        public: friend class Context;

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
        bool isValid();// Performs system loop, to be used in a while

        bool reset();

        void showCursor(bool s) const;

        Event::ptr createEvent(const String& name) const;

        Keyboard::ptr getKeyboard();
        Context::ptr  getContext();

        void attachContext(Context* c);
        void detachContext();

    protected:

        void context_bind();
        void context_unbind();

    protected:

        void initImplementation();
        void documentEvents();

    private:

        Keyboard::ptr keyboard;
        Context*      context;
    };
}

#endif
