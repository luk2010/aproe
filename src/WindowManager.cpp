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

namespace APro
{
    WindowManager::WindowManager()
        : windows(Manager<Window>::objects)
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
        SharedPointer<Window> ret = getWindow(name);
        if(ret.isNull())
        {
            ret = AProNew(1, Window) (name, title, size);
            ret->fullscreen(fullscreen);
            if(fullscreen)
            {
                ret->reset();
            }
            else if(!ret->create())
            {
                Console::get() << "\n[WindowManager] Couldn't create Window " << name << " !";
                return SharedPointer<Window>();
            }

            windows.append(ret);
            Console::get() << "\n[WindowManager] Created Window with name : " << name << ", title : " << title << " and size : " << size << ".";
        }

        return ret;
    }

    void WindowManager::destroy(const String& name)
    {
        SharedPointer<Window> d = getWindow(name);
        if(!d.isNull())
        {
            d->destroy();
        }
    }

    void WindowManager::destroy(const SharedPointer<Window>& window)
    {
        SharedPointer<Window> d = getWindow(window->name());
        if(!d.isNull())
        {
            d->destroy();
        }
    }

    void WindowManager::clear()
    {
        while(!windows.isEmpty())
        {
            destroy(windows.at(0));
            windows.erase(0);
        }
    }

    void WindowManager::loop()
    {
        for(List<SharedPointer<Window> >::Iterator i(windows.begin()); !i.isEnd(); i++)
        {
            if(!(i.get().isNull()))
                i.get()->systemLoop();
        }
    }
}
