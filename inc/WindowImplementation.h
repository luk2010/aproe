/** @file WindowImplementation.h
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 16/03/2013
 *
 *  @addtogroup Global
 *  @addtogroup System
 *
 *  This file defines the WindowImplementation class.
 *
**/
#ifndef APRO_WINDOWIMPLEMENTATION_H
#define APRO_WINDOWIMPLEMENTATION_H

#include "Platform.h"
#include "Implementation.h"

namespace APro
{
    class APRO_DLL WindowImplementation : public Implementation
    {
        APRO_DECLARE_SHAREDPOINTER_CLASS_TYPEDEF(WindowImplementation)

    public:

        const String getClassImplementation() const
        {
            return String("APro::Window");
        }

    public:

        WindowImplementation()
        {

        }

        virtual ~WindowImplementation()
        {

        }

        virtual void loop() = 0;

    public:

        virtual void show() = 0;
        virtual void hide() = 0;

        virtual void move(int x, int y) = 0;
        virtual void resize(size_t width, size_t height) = 0;

    public:

        virtual void setTitle(const String& title) const = 0;
        virtual void showCursor(bool m_show) const = 0;

    public:
        virtual void context_bind() = 0;
        virtual void context_unbind() = 0;

    public:

        void* parentWindow;
    };
}

#endif // APRO_WINDOWIMPLEMENTATION_H
