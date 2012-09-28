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

#if APRO_PLATFORM == APRO_WINDOWS

    SharedPointer<Window> findWindow(HWND hwnd)
    {
        for(size_t i = 0; i < Main::get().getWindowManager().getWindowNumber(); ++i)
        {
            SharedPointer<Window> w = Main::get().getWindowManager().getWindow(i);
            if(!w.isNull() && w->getParam(String("HANDLE")).to<HWND>() == hwnd)
                return w;
        }

        return SharedPointer<Window>();
    }

    LRESULT CALLBACK wndproc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        SharedPointer<Window> w = findWindow(hWnd);
        if(w.isNull())
        {
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
        }

        static Pair<size_t, size_t> opos;
        static Pair<size_t, size_t> osz;

        static RECT pos;
        if(uMsg == WM_EXITSIZEMOVE)
        {
            static Pair<size_t, size_t> newPos;
            static Pair<size_t, size_t> newSize;

            GetWindowRect(hWnd, &pos);

            newPos.setFirst(pos.left); newPos.setSecond(pos.top);
            newSize.setFirst(pos.right - pos.left); newSize.setSecond(pos.bottom - pos.top);

            opos = w->position();
            osz = w->size();

            w->setParam(String("Position"), Variant(newPos));
            w->setParam(String("Size"), Variant(newSize));

            if(newPos.first() != (int) opos.first() || newPos.second() != (int) opos.second())
            {
                w->sendEvent(w->createEvent(String("WindowMovedEvent")));
            }

            if(newSize.first() != (int) osz.first() || newSize.second() != (int) osz.second())
            {
                w->sendEvent(w->createEvent(String("WindowResizedEvent")));
            }

            return 0;
        }

        else if(uMsg == WM_SIZE)
        {
            if(wParam == SIZE_MAXIMIZED || wParam == SIZE_RESTORED)
            {
                static Pair<size_t, size_t> newPos;
                static Pair<size_t, size_t> newSize;

                GetWindowRect(hWnd, &pos);

                newPos.setFirst(pos.left); newPos.setSecond(pos.top);
                newSize.setFirst(pos.right - pos.left); newSize.setSecond(pos.bottom - pos.top);

                opos = w->position();
                osz = w->size();

                w->setParam(String("Position"), Variant(newPos));
                w->setParam(String("Size"), Variant(newSize));
                w->setParam(String("Status"), Variant(Window::Status::Showed));

                w->sendEvent(w->createEvent(String("WindowResizedEvent")));
            }
            else if(wParam == SIZE_MINIMIZED)
            {
                w->setParam(String("Status"), Variant(Window::Status::Hidden));
                w->sendEvent(w->createEvent(String("WindowMinimizedEvent")));
            }

            return 0;
        }

        else if (uMsg == WM_CLOSE)
        {
            w->sendEvent(w->createEvent(String("WindowClosingEvent")));
            w->destroy();
            return 0;
        }

        else
        {
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
        }
    }

#endif

    Window::Window()
        : ParametedObject()
    {
        setParam(String("Name"), Variant(String("NullWindow")), String("Name of the Window Object."));
        setParam(String("Title"), Variant(String("NullWindow")), String("Title of the Window."));

        setParam(String("Size"), Variant(Pair<size_t, size_t>(0, 0)), String("Size of the Window, Width by Height."));
        setParam(String("Position"), Variant(Pair<size_t, size_t>(0, 0)), String("Position of the Window, x and y."));

        setParam(String("Fullscreen"), Variant(false), String("Set if the Window is Fullscreen Mode or not. \
                                                              If you change this property, the window has to be reloaded to \
                                                              this property to take effect."));
        setParam(String("Status"), Variant(Status::Null), String("Status of the Window. If Null, the window hasn't been created yet."));

        keyboard = AProNew(1, Keyboard) ();
        context = nullptr;
    }

    Window::Window(const String& name, const String & title, const String & sz)
        : ParametedObject()
    {
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
        context = nullptr;
    }

    Window::Window(const Window& other)
        : ParametedObject(other)
    {
        String nnae = other.getParam(String("Name")).to<String>();
        nnae.append("_copy");
        setParam(String("Name"), Variant(nnae));
        setParam(String("Status"), Variant(Status::Null), String("Status of the Window. If Null, the window hasn't been created yet."));

        keyboard = other.keyboard;
        context = nullptr;
    }

    Window::~Window()
    {
        destroy();
    }

    bool Window::create()
    {
#if APRO_PLATFORM == APRO_WINDOWS

        DWORD dwExStyle = 0;
        DWORD dwStyle = 0;

        RECT windowsRect;
        windowsRect.left = (long) position().first();
        windowsRect.right = (long) windowsRect.left + size().first();
        windowsRect.top = (long) position().second();
        windowsRect.bottom = (long) windowsRect.top + size().second();

        bool mfullscreen = isFullScreen();

        WNDCLASS wc;
        HINSTANCE hInstance = GetModuleHandle(NULL);
        wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
        wc.lpfnWndProc = wndproc;
        wc.cbClsExtra = 0;
        wc.cbWndExtra = 0;
        wc.hInstance = hInstance;
        wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);
        wc.hbrBackground = 0;
        wc.lpszMenuName = 0;
        wc.lpszClassName = getParam(String("Name")).to<String>().toCstChar();

        if(!RegisterClass(&wc))
        {
            Console::get() << "\n[Window] Couldn't register class " << getParam(String("Name")).to<String>() << ".";
            return false;
        }

        if(mfullscreen)
        {
            DEVMODE dmScreenSettings;
            memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
            dmScreenSettings.dmSize = sizeof(dmScreenSettings);
            dmScreenSettings.dmPelsWidth = windowsRect.right - windowsRect.left;
            dmScreenSettings.dmPelsHeight = windowsRect.bottom - windowsRect.top;
            dmScreenSettings.dmBitsPerPel = 32;
            dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSHEIGHT | DM_PELSWIDTH;

            if(ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
            {
                setParam(String("Fullscreen"), Variant(false));
            }
        }

        mfullscreen = isFullScreen();

        if(mfullscreen)
        {
            dwExStyle = WS_EX_APPWINDOW | WS_EX_TOPMOST;
            dwStyle = 0;
        }
        else
        {
            dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE | WS_EX_CLIENTEDGE;
            dwStyle = WS_TILEDWINDOW;
        }

        AdjustWindowRectEx(&windowsRect, dwStyle, FALSE, dwExStyle);

        HWND hwnd = CreateWindowEx(dwExStyle,
                                   getParam(String("Name")).to<String>().toCstChar(),
                                   getParam(String("Title")).to<String>().toCstChar(),
                                   WS_CLIPSIBLINGS | WS_CLIPCHILDREN | dwStyle,
                                   0, 0,
                                   windowsRect.right - windowsRect.left,
                                   windowsRect.bottom - windowsRect.top,
                                   NULL,
                                   NULL,
                                   hInstance,
                                   NULL);

        if(mfullscreen)
        {
            SetWindowLong(hwnd, GWL_STYLE, WS_CHILD);
            SetWindowLong(hwnd, GWL_EXSTYLE, 0);
        }

        setParam(String("HANDLE"), Variant((HWND) hwnd));
        setParam(String("HINSTANCE"), Variant((HINSTANCE) hInstance));
        setParam(String("Status"), Variant(Status::Created));

        if(!hwnd)
        {
            destroy();
            Console::get() << "\n[Window] Couldn't create Window " << getParam(String("Name")).to<String>() << ".";
            return false;
        }

        return true;

#endif

        return false;
    }

    void Window::destroy()
    {
#if APRO_PLATFORM == APRO_WINDOWS

        if(status() == Status::Null)
            return;

        ChangeDisplaySettings(NULL, 0);

        detachContext();

        HWND hwnd = getParam(String("HANDLE")).to<HWND>();
        if(hwnd && !DestroyWindow(hwnd))
        {
            hwnd = NULL;
            setParam(String("HANDLE"), Variant(hwnd));
        }

        if(!UnregisterClass(getParam(String("Name")).to<String>().toCstChar(), getParam(String("HINSTANCE")).to<HINSTANCE>()))
        {
            setParam(String("HINSTANCE"), Variant((HINSTANCE) NULL));
        }

        setParam(String("Status"), Variant(Status::Null));

#endif
    }

    void Window::show()
    {
#if APRO_PLATFORM == APRO_WINDOWS

        HWND hwnd = getParam(String("HANDLE")).to<HWND>();

        if(hwnd)
        {
            ShowWindow(hwnd, SW_RESTORE);
            setParam(String("Status"), Variant(Status::Showed));
        }

#endif
    }

    void Window::hide()
    {
#if APRO_PLATFORM == APRO_WINDOWS

        HWND hwnd = getParam(String("HANDLE")).to<HWND>();

        if(hwnd)
        {
            ShowWindow(hwnd, SW_HIDE);
            setParam(String("Status"), Variant(Status::Hidden));
        }

#endif
    }

    void Window::move(int x, int y, bool relative)
    {
        if(/*status() == Status::Hidden ||*/ status() == Status::Null || isFullScreen()) return;

        if(relative)
        {
            Pair<size_t, size_t> p = position();
            x = p.first() + x;
            y = p.second() + y;
        }

#if APRO_PLATFORM == APRO_WINDOWS

        HWND hwnd = getParam(String("HANDLE")).to<HWND>();

        if(hwnd)
        {
            Pair<size_t, size_t> rect(size());
            MoveWindow(hwnd, x, y, rect.first(), rect.second(), TRUE);
        }
        else
        {
            Console::get() << "\n[Window] Can't move window " << name() << "  because of Null hwnd !";
            return;
        }

#endif
    }

    void Window::resize(size_t width, size_t height)
    {
        if(/*status() == Status::Hidden ||*/ status() == Status::Null)
        {
            Console::get() << "\n[Window] Resize with an hidden or null window has no effect.";
            return;
        }

#if APRO_PLATFORM == APRO_WINDOWS

        HWND hwnd = getParam(String("HANDLE")).to<HWND>();

        if(hwnd)
        {
            if(isFullScreen())
            {
                DEVMODE dmScreenSettings;
                memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
                dmScreenSettings.dmSize = sizeof(dmScreenSettings);
                dmScreenSettings.dmPelsWidth = width;
                dmScreenSettings.dmPelsHeight = height;
                dmScreenSettings.dmBitsPerPel = 32;
                dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSHEIGHT | DM_PELSWIDTH;

                if(ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
                {
                    Console::get() << "\n[Window] Couldn't change screen resolution.";
                    return;
                }
            }

            Pair<size_t, size_t> p(position());
            MoveWindow(hwnd, p.first(), p.second(), width, height, TRUE);
        }
        else
        {
            Console::get() << "\n[Window] Can't resize window " << name() << "  because of Null hwnd !";
            return;
        }

#endif
    }

    void Window::setTitle(const String& other)
    {
#if APRO_PLATFORM == APRO_WINDOWS

        HWND hwnd = getParam(String("HANDLE")).to<HWND>();

        if(hwnd)
        {
            SetWindowText(hwnd, other.toCstChar());
            setParam(String("Title"), Variant(other));
        }
        else
        {
            Console::get() << "\n[Window] Can't change title of window " << name() << "  because of Null hwnd !";
            return;
        }

#endif
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

#if APRO_PLATFORM == APRO_WINDOWS

        HWND hwnd = getParam(String("HANDLE")).to<HWND>();

        if(hwnd)
        {

            MSG msg;
            if(PeekMessage(&msg, hwnd, 0, 0, PM_REMOVE))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }

        }

#endif

        keyboard->loop();
    }

    bool Window::reset()
    {
        if(status() != Status::Null)
            destroy();

        return create();
    }

    void Window::showCursor(bool s) const
    {
#if APRO_PLATFORM == APRO_WINDOWS

        ShowCursor((BOOL) s);

#endif
    }

    SharedPointer<Event> Window::createEvent(const String& name) const
    {
        SharedPointer<Event> e = AProNew(1, Event) (name);
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

        context->initialize();
        context->addListener(addListener(String("WindowToContextListener")));
    }

    void Window::detachContext()
    {
        if(context)
        {
            context->removeListener(String("WindowToContextListener"));
            removeListener(String("WindowToContextListener"));

            context->release();
            context = nullptr;
        }
    }
}
