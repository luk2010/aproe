/** @file WindowManager.cpp
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
#include "WindowManager.h"
#include "ThreadMutex.h"
#include "ThreadMutexLockGuard.h"

namespace APro
{
    APRO_IMPLEMENT_MANUALSINGLETON(WindowManager)

    WindowManager::WindowManager()
        : ThreadSafe(), windows(Manager<Window>::objects)
    {

    }

    WindowManager::~WindowManager()
    {

    }

    SharedPointer<Window> WindowManager::getWindow(const String & name) const
    {
        for(List<SharedPointer<Window> >::Iterator i(windows.begin()); !i.isEnd(); i++)
        {
            if(i.get()->name() == name)
            {
                return i.get();
            }
        }

        return SharedPointer<Window>();
    }

    SharedPointer<Window> WindowManager::getWindow(size_t index) const
    {
        return windows.at(index);
    }

    size_t WindowManager::getWindowNumber() const
    {
        return windows.size();
    }

    SharedPointer<Window> WindowManager::create(const String& name, const String& title, const String& size, bool fullscreen)
    {
        APRO_THREADSAFE_AUTOLOCK

        SharedPointer<Window> ret = getWindow(name);
        if(ret.isNull())
        {
            ret = AProNew(Window, name, title, size);
            ret->fullscreen(fullscreen);
            if(fullscreen)
            {
                ret->reset();
            }
            else
            {
                bool created = ret->create();
                if(!created)
                {
                    Console::get() << "\n[WindowManager] Couldn't create Window " << name << " !";
                    return Window::ptr();
                }

            }

            Manager<Window>::push(ret);
            Console::get() << "\n[WindowManager] Created Window with name : " << name << ", title : " << title << " and size : " << size << ".";
        }

        return ret;
    }

    void WindowManager::destroy(const String& name)
    {
        APRO_THREADSAFE_AUTOLOCK
        SharedPointer<Window> d = getWindow(name);
        if(!d.isNull())
        {
            d->destroy();
        }
    }

    void WindowManager::destroy(const SharedPointer<Window>& window)
    {
        APRO_THREADSAFE_AUTOLOCK
        SharedPointer<Window> d = getWindow(window->name());
        if(!d.isNull())
        {
            d->destroy();
        }
    }

    void WindowManager::clear()
    {
        APRO_THREADSAFE_AUTOLOCK
        while(!windows.isEmpty())
        {
            destroy(windows.at(0));
            windows.erase(0);
        }
    }

    void WindowManager::loop()
    {
        APRO_THREADSAFE_AUTOLOCK
        for(List<SharedPointer<Window> >::Iterator i(windows.begin()); !i.isEnd(); i++)
        {
            if(!(i.get().isNull()))
                i.get()->systemLoop();
        }
    }
}
