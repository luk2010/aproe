/*
    The XCB Window Implementation
*/
#include <Window.h>
#include <Console.h>
#include <Variant.h>
#include "XCBWindowImp.h"

namespace APro
{
    const String XCBWindowImp::getImplementationName() const
    {
        return String("XCB Window Implementation");
    }

    bool XCBWindowImp::init()
    {
        XInitThreads();

        /* Connexion avec X */
        Display             *dpy = NULL;
        dpy = XOpenDisplay(NULL);
        xcb_connection_t    *connection = NULL;
        xcb_screen_t        *screen = NULL;

        if(!dpy)
        {
            Console::get() << "\n[XCBWindow] Can't open X display !";
            return false;
        }

        /* Cast to XCBConnection */
        connection = XGetXCBConnection(dpy);
        if(!connection)
        {
            Console::get() << "\n[XCBWindow] Can't cast X display to XCB connection !";
            XCloseDisplay(dpy);
            return false;
        }

        /* Event queue ownership */
        XSetEventQueueOwner(dpy, XCBOwnsEventQueue);

        int visualID = 0;

        /* Getting screen */
        int default_screen = DefaultScreen(dpy);
        xcb_screen_iterator_t screen_iter = xcb_setup_roots_iterator(xcb_get_setup(connection));
        for(int screen_num = default_screen; screen_iter.rem && screen_num > 0; --screen_num, xcb_screen_next(&screen_iter));
        screen = screen_iter.data;

        /* Query framebuffer configuration */
        GLXFBConfig *fb_configs = 0;
        int num_fb_configs = 0;
        fb_configs = glXGetFBConfigs(dpy, default_screen, &num_fb_configs);
        if(!fb_configs || num_fb_configs == 0)
        {
            Console::get() << "\n[XCBWindow] Can't find Framebuffer configs !";
            XCloseDisplay(dpy);
            return false;
        }

        /* Select first framebuffer config and query visualID */
        GLXFBConfig fb_config = fb_configs[0];
        glXGetFBConfigAttrib(dpy, fb_config, GLX_VISUAL_ID , &visualID);

        /* Create OpenGL context */
        GLXContext context;
        context = glXCreateNewContext(dpy, fb_config, GLX_RGBA_TYPE, 0, True);
        if(!context)
        {
            Console::get() << "\n[XCBWindow] Can't create GLX context !";
            XCloseDisplay(dpy);
            return false;
        }

        /* Create XID's for colormap and window */
        xcb_colormap_t colormap = xcb_generate_id(connection);
        xcb_window_t window = xcb_generate_id(connection);

        /* Create colormap */
        xcb_create_colormap(
            connection,
            XCB_COLORMAP_ALLOC_NONE,
            colormap,
            screen->root,
            visualID
            );

        /* Create window */
        uint32_t eventmask = XCB_EVENT_MASK_EXPOSURE | XCB_EVENT_MASK_BUTTON_PRESS | XCB_EVENT_MASK_BUTTON_RELEASE;
        uint32_t valuelist[] = { eventmask, colormap, 0 };
        uint32_t valuemask = XCB_CW_EVENT_MASK | XCB_CW_COLORMAP;

        APro::Window* win = reinterpret_cast<APro::Window*>(parentWindow);
        size_t width = win->size().first();
        size_t height = win->size().second();

        size_t x = win->position().first();
        size_t y = win->position().second();

        xcb_create_window(
            connection,
            XCB_COPY_FROM_PARENT,
            window,
            screen->root,
            x, y,
            width, height,
            0,
            XCB_WINDOW_CLASS_INPUT_OUTPUT,
            visualID,
            valuemask,
            valuelist
            );

        /* Get WM_PROTOCOLS cookie */
        xcb_intern_atom_cookie_t cookie = xcb_intern_atom      (connection, 1, 12, "WM_PROTOCOLS");
        xcb_intern_atom_reply_t* reply  = xcb_intern_atom_reply(connection, cookie, 0);

        /* Get WM_DELETE_WINDOW cookie */
        xcb_intern_atom_cookie_t cookie2 = xcb_intern_atom      (connection, 0, 16, "WM_DELETE_WINDOW");
        xcb_intern_atom_reply_t* reply2  = xcb_intern_atom_reply(connection, cookie2, 0);

        xcb_change_property(connection, XCB_PROP_MODE_REPLACE, window, (*reply).atom, 4, 32, 1, &(*reply2).atom);
        m_custom_reply = reply2;

        /* Create GLX Window */
        GLXWindow glxwindow =
            glXCreateWindow(
                dpy,
                fb_config,
                window,
                0
                );

        if(!window)
        {
            xcb_destroy_window(connection, window);
            glXDestroyContext(dpy, context);
            XCloseDisplay(dpy);

            Console::get() << "\n[XCBWindow] Can't create GLX window !";
            return false;
        }

        m_display = dpy;
        m_connection = connection;
        m_drawable = glxwindow;
        m_glxwindow = glxwindow;
        m_context = context;
        m_window = window;

        setTitle(win->title());
        //((Window*) WindowImplementation::parentWindow)->show();
        return true;
    }

    void XCBWindowImp::deinit()
    {
        glXDestroyWindow(m_display, m_glxwindow);
        xcb_destroy_window(m_connection, m_window);
        glXDestroyContext(m_display, m_context);
        XCloseDisplay(m_display);
    }

    Implementation::ptr XCBWindowImp::clone() const
    {
        Implementation::ptr ret = Implementation::ptr(AProNew3(XCBWindowImp));
        ret.setDeletionMethod(DeletionMethod::Delete3);
        return ret;
    }

    void XCBWindowImp::destroy(Implementation* imp)
    {
        if(imp)
        {
            XCBWindowImp* impc = reinterpret_cast<XCBWindowImp*>(imp);
            if(impc)
            {
                AProDelete3(impc);
            }
        }
    }

    void XCBWindowImp::loop()
    {
        xcb_generic_event_t *event = xcb_poll_for_event (m_connection);
        Window* win = (Window*) WindowImplementation::parentWindow;

        if(!event) return;
        switch((*event).response_type & ~0x80)
        {
        case XCB_EXPOSE:
            break;

        case XCB_CLIENT_MESSAGE:
            if((*(xcb_client_message_event_t*)event).data.data32[0] == (*m_custom_reply).atom)
            {
                win->sendEvent(win->createEvent(String("WindowClosingEvent")));
                win->destroy();
            }
            break;
        }
    }

    void XCBWindowImp::show()
    {
        xcb_map_window(m_connection, m_window);
        xcb_flush(m_connection);
    }

    void XCBWindowImp::hide()
    {
        xcb_unmap_window(m_connection, m_window);
        xcb_flush(m_connection);
    }

    void XCBWindowImp::move(int x, int y)
    {
        uint32_t values[] = { (uint32_t) x, (uint32_t) y };
        xcb_configure_window(m_connection, m_window, XCB_CONFIG_WINDOW_X | XCB_CONFIG_WINDOW_Y, values);
        xcb_flush(m_connection);
    }

    void XCBWindowImp::resize(size_t width, size_t height)
    {
        uint32_t values[] = { (uint32_t) width, (uint32_t) height };
        xcb_configure_window(m_connection, m_window, XCB_CONFIG_WINDOW_WIDTH | XCB_CONFIG_WINDOW_HEIGHT, values);
        xcb_flush(m_connection);
    }

    void XCBWindowImp::setTitle(const String& title) const
    {
        xcb_change_property(m_connection,
                            XCB_PROP_MODE_REPLACE,
                            m_window,
                            XCB_ATOM_WM_NAME,
                            XCB_ATOM_STRING, 8,
                            title.size(), title.toCstChar());

        xcb_flush(m_connection);

    }

    void XCBWindowImp::showCursor(bool m_show) const
    {

    }

    void XCBWindowImp::context_bind()
    {
        glXMakeContextCurrent(m_display, m_drawable, m_drawable, m_context);
    }

    void XCBWindowImp::context_unbind()
    {
        glXMakeCurrent(m_display, None, None);
    }
}
