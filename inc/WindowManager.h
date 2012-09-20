/** @file WindowManager.h
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 06/09/2012
 *
 *  @addtogroup Global
 *  @addtogroup System
 *
 *  This file defines the WindowManager class.
 *
**/
#ifndef APROWINDOWMANAGER_H
#define APROWINDOWMANAGER_H

#include "Window.h"
#include "Singleton.h"
#include "SharedPointer.h"
#include "List.h"

namespace APro
{
    class APRO_DLL WindowManager : public Manager<Window>
    {
    public:

        WindowManager();

        ~WindowManager();

    public:

        SharedPointer<Window> getWindow(const String & name) const;
        SharedPointer<Window> getWindow(size_t index) const;
        size_t                getWindowNumber() const;

        SharedPointer<Window> create(const String& name, const String& title, const String& size, bool fullscreen);

        void destroy(const String& name);
        void destroy(const SharedPointer<Window>& window);

        void clear();

        void loop();

    private:

        List<SharedPointer<Window> >& windows;
    };
}

#endif
