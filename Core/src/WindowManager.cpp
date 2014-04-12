////////////////////////////////////////////////////////////
/** @file WindowManager.cpp
 *  @ingroup Core
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 06/09/2012 - 12/04/2014
 *
 *  Implements the WindowManager class.
 *
**/
////////////////////////////////////////////////////////////
#include "WindowManager.h"

namespace APro
{
    APRO_IMPLEMENT_MANUALSINGLETON(WindowManager)

    WindowManager::WindowManager()
        : windows(Manager<Window, Array<WindowPtr> >::objects)
    {
        idgen.setBase(1);
        idgen.setIncrementation(1);
        idgen.setMaximumId(1024);
        idgen.reset();
        windows.append(WindowPtr(nullptr));
    }

    WindowManager::~WindowManager()
    {

    }

    WindowId WindowManager::create(const String& title, const size_t& width, const size_t& height, bool fullscreen)
    {
        if(!title.isEmpty() &&
           width > 0 && height > 0)
        {
            if(!Window::HasCorrectImplementation())
            {
                aprodebug("No valid implementation found to create Window object (title='") << title << "').";
                return 0;
            }

            APRO_THREADSAFE_AUTOLOCK

            // Look for free Id
            WindowId id = findNulllId();
            if(id == 0)
            {
                if(idgen.canPick())
                    id = idgen.pick();
            }

            if(id != 0)
            {
                Window* new_win = AProNew(Window, id, title, width, height, fullscreen);

                if(new_win)
                {
                    if(isIdValid(id))
                        windows.at(id).set(new_win);
                    else
                        windows.append(new_win);

                    windows.at(id).setOwning(true);
                    return id;
                }
                else
                {
                    aprodebug("Can't allocate Window object (title='") << title << "').";
                    idgen.unpick();
                    return 0;
                }
            }
            else
            {
                aprodebug("Can't create new Window object (title='") << title << "') because max Window number has been reached.";
                return 0;
            }
        }

        return 0;
    }

    bool WindowManager::destroy(WindowPtr& window)
    {
        aproassert(!window.isNull());

        if(!isWindowRegistered(window))
        {
            aprodebug("Can't destroy unregistered Window (title='") << window->getTitle() << "').";
            return false;
        }

        if(window.getPointerUses() > 1)
            aprodebug("Window (title='") << window->getTitle() << "') is being destroyed but other AutoPointer holds it. They will be invalidate.";

        // This call the destructor for sure.
        // We do not erase the entry from the array as we want to re-use
        // the Id.
        window.nullize();
        return true;
    }

    bool WindowManager::destroy(const WindowId& windowId)
    {
        aproassert(isIdValid(windowId));

        APRO_THREADSAFE_AUTOLOCK

        WindowPtr& windowptr = windows.at(windowId);

        if(window.getPointerUses() > 1)
            aprodebug("Window (title='") << window->getTitle() << "') is being destroyed but other AutoPointer holds it. They will be invalidate.";

        // This call the destructor for sure.
        // We do not erase the entry from the array as we want to re-use
        // the Id.
        windowptr.nullize();
        return true;
    }

    WindowPtr& WindowManager::getWindow(const WidowId& windowid)
    {
        APRO_THREADSAFE_AUTOLOCK
        if(isIdValid(windowid))
            return windows.at(windowid);
        else
            return WindowPtr(nullptr);
    }

    const WindowPtr& WindowManager::getWindow(const WidowId& windowid) const
    {
        APRO_THREADSAFE_AUTOLOCK
        if(isIdValid(windowid))
            return windows.at(windowid);
        else
            return WindowPtr(nullptr);
    }

    size_t WindowManager::countActiveWindows() const
    {
        APRO_THREADSAFE_AUTOLOCK
        int cnt = 0;

        WindowArray::const_iterator& e = windows.end();
        for(WindowArray::const_iterator it = windows.begin() + 1; it != e; it++)
            if(!(*it).isNull())
                cnt++;

        return cnt;
    }

    void WindowManager::clear()
    {
        APRO_THREADSAFE_AUTOLOCK

        windows.clear();
        windows.append(WindowPtr(nullptr));
        idgen.reset();
    }

    void WindowManager::updateWindows()
    {
        APRO_THREADSAFE_AUTOLOCK

        WindowArray::const_iterator e = windows.end();
        for(WindowArray::iterator it = windows.begin() + 1; it != e; it++)
        {
            if(!(*it).isNull())
                (*it)->update();
        }
    }

    bool WindowManager::isIdValid(const WindowId& windowid) const
    {
        APRO_THREADSAFE_AUTOLOCK
        return windowid > 0 &&
               windowid < windows.size();
    }

    bool WindowManager::isWindowRegistered(const WindowPtr& ptr) const
    {
        APRO_THREADSAFE_AUTOLOCK
        return windows.find(ptr) > 0;
    }

    WindowId WindowManager::findNullId() const
    {
        APRO_THREADSAFE_AUTOLOCK

        WindowArray::const_iterator e = windows.end();
        for(WindowArray::const_iterator it = windows.begin() + 1; it != e; it++)
        {
            if((*it).isNull())
                return windows.toIndex(it);
        }

        return 0;
    }

}
