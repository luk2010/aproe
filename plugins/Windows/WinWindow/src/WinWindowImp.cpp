#include "WinWindowImp.h"

#include <Map.h>
#include <Window.h>

using namespace APro;

Map<HWND, WinWindowImp*> impMap;

LRESULT CALLBACK wndproc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    WinWindowImp* w = impMap[hwnd];
    if(!w || !(w->parentWindow))
    {
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }

    Window* win = (Window*) w->parentWindow;

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

        opos = win->position();
        osz = win->size();

        win->setParam(String("Position"), Variant(newPos));
        win->setParam(String("Size"), Variant(newSize));

        if(newPos.first() != (int) opos.first() || newPos.second() != (int) opos.second())
        {
            win->sendEvent(win->createEvent(String("WindowMovedEvent")));
        }

        if(newSize.first() != (int) osz.first() || newSize.second() != (int) osz.second())
        {
            win->sendEvent(win->createEvent(String("WindowResizedEvent")));
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

            opos = win>position();
            osz = win->size();

            win->setParam(String("Position"), Variant(newPos));
            win->setParam(String("Size"), Variant(newSize));
            win->setParam(String("Status"), Variant(Window::Status::Showed));

            win->sendEvent(win->createEvent(String("WindowResizedEvent")));
        }
        else if(wParam == SIZE_MINIMIZED)
        {
            win->setParam(String("Status"), Variant(Window::Status::Hidden));
            win->sendEvent(w->createEvent(String("WindowMinimizedEvent")));
        }

        return 0;
    }

    else if (uMsg == WM_CLOSE)
    {
        win->sendEvent(win->createEvent(String("WindowClosingEvent")));
        win->destroy();
        return 0;
    }

    else
    {
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
}

WinWindowImp::WinWindowImp()
{
    handle = NULL;
    mInstance = NULL;
}

WinWindowImp::~WinWindowImp()
{
    handle = NULL;
    mInstance = NULL;
}

const String WinWindowImp::getImplementationName() const
{
    return String("WinAPI Window");
}

bool WinWindowImp::init()
{
    if(!parentWindow) return false;

    Console& console = Main::get().getConsole();

    DWORD dwExStyle = 0;
    DWORD dwStyle = 0;

    Window* win = (Window*) parentWindow;

    RECT windowsRect;
    windowsRect.left = (long) win->position().first();
    windowsRect.right = (long) windowsRect.left + size().first();
    windowsRect.top = (long) win->position().second();
    windowsRect.bottom = (long) windowsRect.top + size().second();

    bool mfullscreen = win->isFullScreen();

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
    wc.lpszClassName = win->getParam(String("Name")).to<String>().toCstChar();

    if(!RegisterClass(&wc))
    {
        console << "\n[WinWindowImp] Couldn't register class " << win->getParam(String("Name")).to<String>() << ".";
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
            win->setParam(String("Fullscreen"), Variant(false));
        }
    }

    mfullscreen = win->isFullScreen();

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
                                win->getParam(String("Name")).to<String>().toCstChar(),
                                win->getParam(String("Title")).to<String>().toCstChar(),
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

    handle = hwnd;
    mInstance = hInstance;
    impMap.push(handle, this);

    if(!hwnd)
    {
        win->destroy();
        console << "\n[WinWindowImp] Couldn't create Window " << win->getParam(String("Name")).to<String>() << ".";
        return false;
    }

    return true;
}

void WinWindowImp::deinit()
{
    if(!parentWindow) return false;
    Window* win = (Window*) WindowImplementation::parentWindow;
    Console& console = Main::get().getConsole();

    if(win->status() == Window::Status::Null)
        return;

    ChangeDisplaySettings(NULL, 0);

    win->detachContext();

    if(handle && !DestroyWindow(handle))
    {
        handle = NULL;
    }

    if(!UnregisterClass(win->getParam(String("Name")).to<String>().toCstChar(), mInstance))
    {
        mInstance = NULL;
    }
}

Implementation::ptr clone() const
{
    return spCast<Implementation>(WinWindowImp::ptr(AProNew(1, WinWindowImp)));
}

void WinWindowImp::loop()
{
    if(handle)
    {
        MSG msg;
        if(PeekMessage(&msg, handle, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
}

void WinWindowImp::show()
{
    if(handle)
    {
        ShowWindow(handle, SW_RESTORE);
    }
}

void WinWindowImp::hide()
{
    if(handle)
    {
        ShowWindow(handle, SW_HIDE);
    }
}

void WinWindowImp::move(int x, int y)
{
    if(handle)
    {
        Pair<size_t, size_t> rect(((Window*) WindowImplementation::parentWindow)->size());
        MoveWindow(handle, x, y, rect.first(), rect.second(), TRUE);
    }
}

void WinWindowImp::resize(size_t width, size_t height)
{
    if(handle)
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
                Main::get().getConsole() << "\n[WinWindowImp] Couldn't change screen resolution.";
                return;
            }
            else
            {
                MoveWindow(handle, 0, 0, width, height, TRUE);
                return;
            }
        }

        Pair<size_t, size_t> p(((Window*) WindowImplementation::parentWindow)->position());
        MoveWindow(handle, p.first(), p.second(), width, height, TRUE);
    }
}

void WinWindowImp::setTitle(const String& title)
{
    if(handle)
    {
        SetWindowText(handle, other.toCstChar());
        ((Window*) WindowImplementation::parentWindow)->setParam(String("Title"), Variant(other));
    }
}

void WinWindowImp::showCursor(bool m_show)
{
    ShowCursor((BOOL) m_show);
}

