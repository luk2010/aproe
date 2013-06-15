/*
    The XCB Window Implementation
*/
#ifndef XCBWINDOWIMP_H
#define XCBWINDOWIMP_H

#include <WindowImplementation.h>

#include <X11/Xlib.h>

#include <X11/Xlib-xcb.h>
#include <xcb/xcb.h>
#include <GL/glx.h>
#include <GL/gl.h>


namespace APro
{
    class XCBWindowImp : public WindowImplementation
    {
    public:

        const String getImplementationName() const;

    public:

        XCBWindowImp()
        {

        }

        ~XCBWindowImp()
        {

        }

        bool init(); // Create the window
        void deinit(); // Destroy the window

        Implementation::ptr clone() const;
        void destroy(Implementation*);

    public:

        void loop();

        void show();
        void hide();

        void move(int x, int y);
        void resize(size_t width, size_t height);

        void setTitle(const String& title) const;
        void showCursor(bool m_show) const;

        void context_bind();
        void context_unbind();

    private:

        Display*                 m_display;
        xcb_connection_t*        m_connection;
        xcb_intern_atom_reply_t* m_custom_reply;
        GLXDrawable              m_drawable;
        GLXWindow                m_glxwindow;
        GLXContext               m_context;
        xcb_window_t             m_window;
    };
}

#endif // XCBWINDOWIMP_H
