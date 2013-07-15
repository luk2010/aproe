////////////////////////////////////////////////////////////
/** @file Console.cpp
 *  @ingroup Utils
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 27/06/2012
 *
 *  Implements the Console Utility class.
 *
**/
////////////////////////////////////////////////////////////
#define _WIN32_WINNT 0x0500
#include "Console.h"
#include <stdio.h>
#include "ThreadMutex.h"
#include "ThreadMutexLockGuard.h"

namespace APro
{

    APRO_IMPLEMENT_SINGLETON(Console)

    Console::Console()
        : ThreadSafe()
    {
        currentState.background = Color::Black;
        currentState.foreground = Color::White;
        currentState.blink = false;
        currentState.bold = false;
    }

    Console::~Console()
    {

    }

    Console& Console::dump(const char* filename)
    {
        if(filename)
        {
            APRO_THREADSAFE_AUTOLOCK

            FILE* file = nullptr;

            file = fopen(filename, "w+");
            if(file)
            {
                fprintf(file, "Console Log");
                fprintf(file, "\n-----------\n\n");
                fprintf(file, "%s", dumpedLog.toCstChar());
                fclose(file);
            }
        }

        return *this;
    }

    Console& Console::dump(const String& filename)
    {
        if(!filename.isEmpty())
        {
            dump(filename.toCstChar());
        }

        return *this;
    }

    Console& Console::put(const String& str)
    {
        Console::write(str, currentState.foreground, currentState.background, currentState.bold, currentState.blink);
        return *this;
    }

    Console& Console::backgroundColor(Console::Color::_ color)
    {
        currentState.background = color;
        return *this;
    }

    Console& Console::foregroundColor(Console::Color::_ color)
    {
        currentState.foreground = color;
        return *this;
    }

    Console& Console::blink(bool blink_)
    {
        currentState.blink = blink_;
        return *this;
    }

    Console& Console::bold(bool bold_)
    {
        currentState.bold = bold_;
        return *this;
    }

    Console& Console::params(Color::_ foreground, Color::_ background, bool bold_, bool blink_)
    {
        backgroundColor(background);
        foregroundColor(foreground);
        bold(bold_);
        blink(blink_);
        return *this;
    }

    Console& Console::reset()
    {
        currentState.background = Color::Black;
        currentState.foreground = Color::White;
        currentState.blink = false;
        currentState.bold = false;

        put(String(""));

        return *this;
    }

    Console& Console::clearScreen()
    {
#if APRO_PLATFORM == APRO_WINDOWS

        system("cls");

#else

        printf("\033[H\033[2J");

#endif

        return *this;
    }

    Console& Console::operator<<(const String& str)
    {
        return put(str);
    }

    Console& Console::operator<<(const char* str)
    {
        return put(String(str));
    }

    Console& Console::operator<<(char c)
    {
        String t; t.append(c);
        return put(t);
    }

    Console& Console::operator<<(int i)
    {
        char buffer[33];
        sprintf(buffer, "%d", i);
        return put(String(buffer));
    }

    Console& Console::operator<<(unsigned long li)
    {
        char buffer[33];
        sprintf(buffer, "%lu", li);
        return put(String(buffer));
    }

#if APRO_PLATFORM == APRO_WINDOWS

    void Console::write(const String& str, Color::_ foreground, Color::_ background, bool bold, bool blink)
    {
        APRO_THREADSAFE_AUTOLOCK

        int b = (int) background;
        int colour = ((int) foreground) + (b * 16);

        console = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(console, colour);

        printf(str.toCstChar());

        dumpedLog.append(str);
    }

#else

    #define makeC(param) printf("\033[%sm",param)
    #define makeI(param) printf("\033[%dm",param)

    void Console::write(const String& str, Color::_ foreground, Color::_ background, bool bold, bool blink)
    {
        APRO_THREADSAFE_AUTOLOCK

        makeC("0");

        int f = (int) foreground;
        int b = ((int) background) + 10;

        if(bold)
            makeC("1");

        if(blink)
            makeC("5");

        makeI(f);
        makeI(b);

        printf("%s", str.toCstChar());

        dumpedLog.append(str);
    }

    #undef makeC
    #undef makeI

#endif

    Console& Console::hide()
    {
#if APRO_PLATFORM == APRO_WINDOWS

        HWND hc = GetConsoleWindow();
        ShowWindow(hc, SW_HIDE);

#else

        put(String("\nHiding this window isn't supported yet !"));

#endif

        return *this;
    }

    Console& Console::show()
    {
#if APRO_PLATFORM == APRO_WINDOWS

        HWND hc = GetConsoleWindow();
        ShowWindow(hc, SW_SHOW);

#else

        put(String("\nShowing this window isn't supported yet !"));

#endif

        return *this;
    }

    Console& Console::info(const String& class_, const String& func_, int line_, const String& msg)
    {
        String result;
        result << "\n[" << class_ << "]" << "{" << func_ << "}" << "(" << String::toString(line_) << ") " << msg;
        put(result);
        return *this;
    }
}
