/** @file Window.cpp
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 04/09/2012
 *
 *  @addtogroup Global
 *  @addtogroup System
 *
 *  This file defines the Window class.
 *
**/
#include "Window.h"
#include "WindowManager.h"
#include "Main.h"

namespace APro
{
    Window::Window()
        : Implementable(String("APro::Window"))
    {
        context = 0;
    }

    Window::Window(const String& name, const String & title, const String & sz)
        : ParametedObject(), Implementable(String("APro::Window"))
    {
        createImplementation();

        setParam(String("Name"), Variant(name), String("Name of the Window Object."));
        setParam(String("Title"), Variant(title), String("Title of the Window."));

        List<String> sizess = sz.explode('x');
        Pair<size_t, size_t> sizes(String::toInt(sizess.at(0)), String::toInt(sizess.at(1)));
        setParam(String("Size"), Variant(sizes), String("Size of the Window, Width by Height."));
        setParam(String("Position"), Variant(Pair<size_t, size_t>(0, 0)), String("Position of the Window, x and y."));

        setParam(String("Fullscreen"), Variant(false), String("Set if the Window is Fullscreen Mode or not. \
                                                              If you change this property, the window has to be reloaded to \
                                                              this property to take effect."));
        setParam(String("Status"), Variant(Status::Null), String("Status of the Window. If Null, the window hasn't been created yet."));

        keyboard = AProNew(1, Keyboard) ();
        context = 0;
        documentEvents();
    }

    Window::Window(const Window& other)
        : ParametedObject(other), EventEmitter(), Implementable(String("APro::Window"))
    {
        createImplementation();
        String nnae = other.getParam(String("Name")).to<String>();
        nnae.append("_copy");
        setParam(String("Name"), Variant(nnae));
        setParam(String("Status"), Variant(Status::Null), String("Status of the Window. If Null, the window hasn't been created yet."));

        keyboard = other.keyboard;
        context = 0;
        documentEvents();
    }

    Window::~Window()
    {
        destroy();
    }

    bool Window::create()
    {
        if(!Implementable::implement.isNull())
        {
            if(Implementable::implement->init())
            {
                setParam(String("Status"), Variant(Window::Status::Created));
                sendEvent(createEvent(String("WindowCreatedEvent")));
                return true;
            }
        }
        return false;
    }

    void Window::destroy()
    {
        if(!Implementable::implement.isNull() && status() != Status::Null)
        {
            Implementable::implement->deinit();
            setParam(String("Status"), Variant(Window::Status::Null));
            sendEvent(createEvent(String("WindowDestroyedEvent")));
        }
    }

    void Window::show()
    {
        if(!Implementable::implement.isNull())
        {
            Implementable::implement->show();
            setParam(String("Status"), Variant(Window::Status::Showed));
            sendEvent(createEvent(String("WindowShowedEvent")));
        }
    }

    void Window::hide()
    {
        if(!Implementable::implement.isNull())
        {
            Implementable::implement->hide();
            setParam(String("Status"), Variant(Window::Status::Hidden));
            sendEvent(createEvent(String("WindowHideEvent")));
        }
    }

    void Window::move(int x, int y, bool relative)
    {
        if( /* status() == Status::Hidden || */ status() == Status::Null || isFullScreen()) return;

        if(relative)
        {
            Pair<size_t, size_t> p = position();
            x = p.first() + x;
            y = p.second() + y;
        }

        if(!Implementable::implement.isNull())
        {
            Implementable::implement->move(x, y);
        }
    }

    void Window::resize(size_t width, size_t height)
    {
        if( /* status() == Status::Hidden || */ status() == Status::Null)
        {
            Console::get() << "\n[Window] Resize with an hidden or null window has no effect.";
            return;
        }

        if(!Implementable::implement.isNull())
        {
            Implementable::implement->resize(width, height);
        }
    }

    void Window::setTitle(const String& other)
    {
        if(!Implementable::implement.isNull())
        {
            Implementable::implement->setTitle(other);
        }
    }

    bool Window::isFullScreen() const
    {
        return getParam(String("Fullscreen")).to<bool>();
    }

    void Window::fullscreen(bool toggle)
    {
        bool f = isFullScreen();

        if(f != toggle)
        {
            Status::_ s = status();

            if(s != Status::Null)
            {
                setParam(String("Status"), Variant(Status::HasToBeReset));
            }

            setParam(String("Fullscreen"), Variant(toggle));
        }
    }

    Window::Status::_ Window::status() const
    {
        return getParam(String("Status")).to<Status::_>();
    }

    String Window::name() const
    {
        return getParam(String("Name")).to<String>();
    }

    String Window::title() const
    {
        return getParam(String("Title")).to<String>();
    }

    Pair<size_t, size_t> Window::size() const
    {
        return getParam(String("Size")).to<Pair<size_t, size_t> >();
    }

    Pair<size_t, size_t> Window::position() const
    {
        return getParam(String("Position")).to<Pair<size_t, size_t> >();
    }

    void Window::systemLoop()
    {
        if(status() == Status::Null)
            return;

        if(!Implementable::implement.isNull())
        {
            Implementable::implement->loop();
        }

        //keyboard->loop();
    }

    bool Window::isValid()
    {
        systemLoop();
        return status() != Status::Null;
    }

    bool Window::reset()
    {
        if(status() != Status::Null)
            destroy();

        return create();
    }

    void Window::showCursor(bool s) const
    {
        if(!Implementable::implement.isNull())
        {
            Implementable::implement->showCursor(s);
        }
    }

    Event::ptr Window::createEvent(const String& name) const
    {
        Event::ptr e = EventEmitter::createEvent(name);
        e->setParam(String("Emitter"), Variant(this), String("Emitter of this event."));

        if(name == "WindowMovedEvent")
        {
            e->setParam(String("Position"), Variant(position()), String("New Position of the window."));
        }
        else if(name == "WindowResizedEvent")
        {
            e->setParam(String("Size"), Variant(size()), String("New Size of the window."));
        }

        return e;
    }

    SharedPointer<Keyboard> Window::getKeyboard()
    {
        return keyboard;
    }

    void Window::attachContext(Context* c)
    {
        if(context)
        {
            detachContext();
        }

        context = c;
        context->addListener(addListener(String("WindowToContextListener")));
    }

    void Window::detachContext()
    {
        if(context)
        {
            context->removeListener(String("WindowToContextListener"));
            removeListener(String("WindowToContextListener"));

            context = nullptr;
        }
    }

    void Window::initImplementation()
    {
        Implementable::implement->parentWindow = this;
    }

    void Window::context_bind()
    {
        if(!Implementable::implement.isNull())
        {
            Implementable::implement->context_bind();
        }
    }

    void Window::context_unbind()
    {
        if(!Implementable::implement.isNull())
        {
            Implementable::implement->context_unbind();
        }
    }

    void Window::documentEvents()
    {
        String event;
        String description;

        event = "WindowCreatedEvent";
        description = "Window is created. There are no garantee that the window has been showed or drawned. This event is sended after \"create\" has been called.";
        documentEvent(event, description);

        event = "WindowDestroyedEvent";
        description = "Window is destroyed. This event is sended after \"destroy\" has been called.";
        documentEvent(event, description);

        event = "WindowMovedEvent";
        description = "Window has been moved. Event field \"Position\" contains the new position of the window.";
        documentEvent(event, description);

        event = "WindowSizedEvent";
        description = "Window has been resized. Event field \"Size\" contains the new size of the window.";
        documentEvent(event, description);

        event = "WindowClosingEvent";
        description = "Window is closing.";
        documentEvent(event, description);

        event = "WindowShowedEvent";
        description = "Window is showed. There is no garantee that the function \"show\" is a success.";
        documentEvent(event, description);

        event = "WindowHideEvent";
        description = "Window is hidden. There is no garantee that the function \"hide\" is a success.";
        documentEvent(event, description);
    }
}
