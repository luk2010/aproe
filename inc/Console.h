/** @file Console.h
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 25/06/2012
 *
 *  @addtogroup Global
 *  @addtogroup Utils
 *
 *  This file defines the Console Utility class.
 *
**/
#ifndef APROCONSOLE_H
#define APROCONSOLE_H

#include "Platform.h"
#include "Singleton.h"
#include "SString.h"

namespace APro
{
    class APRO_DLL Console : public Singleton<Console>
    {

        APRO_DECLARE_SINGLETON(Console)

    public:

        class Color
        {
        public :

            enum _
            {
#if APRO_PLATFORM == APRO_WINDOWS

                Black = 0,
                Blue = 1,
                Green = 2,
                Cyan = 3,
                Red = 4,
                Magenta = 5,
                Yellow = 6,
                White = 7

#else


                Black = 30,
                Red = 31,
                Green = 32,
                Yellow = 33,
                Blue = 34,
                Magenta = 35,
                Cyan = 36,
                White = 37

#endif
           };
        };

        struct ConsoleOptions
        {
            Color::_ foreground;
            Color::_ background;
            bool bold;
            bool blink;
        };

    protected:

        Console();
        ~Console();

    private:

#if APRO_PLATFORM == APRO_WINDOWS

        HANDLE console;

#endif

    public:

        Console& dump(const char* filename);
        Console& dump(const String& filename);

        Console& put(const String & str);

        Console& info(const String& class_, const String& func_, int line_, const String& msg);
        #define inform(m, c) info(c, APro::String(__FUNCTION__), __LINE__, m)

        Console& backgroundColor(Color::_ color);
        Console& foregroundColor(Color::_ color);
        Console& bold(bool bold_);
        Console& blink(bool blink_);
        Console& params(Color::_ foreground, Color::_ background, bool bold, bool blink);

        Console& reset();
        Console& clearScreen();

        Console& hide();
        Console& show();

        Console& operator << (const String& str);
        Console& operator << (const char* str);
        Console& operator << (char c);
        Console& operator << (int i);

    private:
        void write(const String& str, Color::_ foreground, Color::_ background, bool bold, bool blink);

    protected:

        ConsoleOptions currentState;
        String dumpedLog;
    };
}

#endif
