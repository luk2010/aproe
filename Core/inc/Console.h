////////////////////////////////////////////////////////////
/** @file Console.h
 *  @ingroup Utils
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 25/06/2012 - 17/12/2014
 *
 *  @brief
 *  Defines the Console Utility class.
 *
 *  @copyright
 *  Atlanti's Project Engine
 *  Copyright (C) 2012 - 2014  Atlanti's Corp
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
**/
////////////////////////////////////////////////////////////
#ifndef APROCONSOLE_H
#define APROCONSOLE_H

#include "Platform.h"
#include "Singleton.h"
#include "SString.h"
#include "ThreadSafe.h"

namespace APro
{
    ////////////////////////////////////////////////////////////
    /** @class Console
     *  @ingroup Utils
     *  @brief Describes a simple access output system.
     *  @details The console class can be either a standard console
     *  or a created console window, depending on the system it is used.
     *
     *  You can create your own input implementation for your
     *  classes using the << operator.
    **/
    ////////////////////////////////////////////////////////////
    class APRO_DLL Console : public Singleton<Console>,
                             public ThreadSafe
    {

        APRO_DECLARE_SINGLETON(Console)

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Defines the Colors used by the console.
         *  @details The value of these colors are OS-dependant.
        **/
        ////////////////////////////////////////////////////////////
        enum class Color
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

        ////////////////////////////////////////////////////////////
        /** @brief The options used by the console class.
        **/
        ////////////////////////////////////////////////////////////
        struct ConsoleOptions
        {
            Color foreground;   ///< @brief Foreground color of the text.
            Color background;   ///< @brief Background color of the text.
            bool bold;          ///< @brief Text is bold ?
            bool blink;         ///< @brief Text is blinking ?
        };

    protected:

        ////////////////////////////////////////////////////////////
        /** @brief Constructor.
        **/
        ////////////////////////////////////////////////////////////
        Console();

        ////////////////////////////////////////////////////////////
        /** @brief Destructor.
        **/
        ////////////////////////////////////////////////////////////
        ~Console();

    private:

#if APRO_PLATFORM == APRO_WINDOWS

        HANDLE console;///< @brief Handle to the console. In other systems, std::cout is used.

#endif

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Write all the text already written on the console
         *  in a file.
         *
         *  As every text is automaticly recorded in a String,
         *  you can use this function at anytime.
         *
         *  @param filename : File to write. Path is relative.
         *  @return The console.
        **/
        ////////////////////////////////////////////////////////////
        Console& dump(const char* filename);

        ////////////////////////////////////////////////////////////
        /** @brief Write all the text already written on the console
         *  in a file.
         *  @details As every text is automaticly recorded in a String,
         *  you can use this function at anytime.
         *
         *  @param filename : File to write. Path is relative.
         *  @return The console.
        **/
        ////////////////////////////////////////////////////////////
        Console& dump(const String& filename);

        ////////////////////////////////////////////////////////////
        /** @brief Write a string in the console.
         *  @details The string is recorded and added.
         *
         *  @param str : String to write.
         *  @return The Console.
        **/
        ////////////////////////////////////////////////////////////
        Console& put(const String & str);

        ////////////////////////////////////////////////////////////
        /** @brief Write in the console some information that are
         *  correctly typed.
         *  @details The format is "[class_]{func_}(line_) msg". You can
         *  use this function in your program to have an homogene
         *  writing in the console.
         *
         *  @param class_ : Class sending the message.
         *  @param func_ : Function sending the message.
         *  @param line_ : Line where this instruction is called.
         *  @param msg : Message to write.
         *  @return The Console.
        **/
        ////////////////////////////////////////////////////////////
        Console& info(const String& class_, const String& func_, int line_, const String& msg);
        #define inform(m, c) info(c, APro::String(__FUNCTION__), __LINE__, m)

        ////////////////////////////////////////////////////////////
        /** @brief Change the current background color of the text.
         *
         *  @param color : New background color.
         *  @return The console.
        **/
        ////////////////////////////////////////////////////////////
        Console& backgroundColor(Color color);

        ////////////////////////////////////////////////////////////
        /** @brief Change the current foreground color of the text.
         *
         *  @param color : New foreground color.
         *  @return The console.
        **/
        ////////////////////////////////////////////////////////////
        Console& foregroundColor(Color color);

        ////////////////////////////////////////////////////////////
        /** @brief Change the current bold state of the text.
         *
         *  @param bold_ : New state.
         *  @return The console.
        **/
        ////////////////////////////////////////////////////////////
        Console& bold(bool bold_);

        ////////////////////////////////////////////////////////////
        /** @brief Change the current blink state of the text.
         *
         *  @param blink_ : New state.
         *  @return The console.
        **/
        ////////////////////////////////////////////////////////////
        Console& blink(bool blink_);

        ////////////////////////////////////////////////////////////
        /** @brief Change every text's params.
         *
         *  @param foreground : Foreground color.
         *  @param background : Background color.
         *  @param bold : New bold state.
         *  @param blink : blinnk state.
         *  @return The console.
        **/
        ////////////////////////////////////////////////////////////
        Console& params(Color foreground, Color background, bool bold, bool blink);

        ////////////////////////////////////////////////////////////
        /** @brief Reset every text's params.
         *  @note The text recorded isn't cleared.
         *
         *  @return The console.
        **/
        ////////////////////////////////////////////////////////////
        Console& reset();

        ////////////////////////////////////////////////////////////
        /** @brief Clear the screen.
         *  @return The console.
        **/
        ////////////////////////////////////////////////////////////
        Console& clearScreen();

        ////////////////////////////////////////////////////////////
        /** @brief If possible, hide the console window.
         *  @return The console.
        **/
        ////////////////////////////////////////////////////////////
        Console& hide();

        ////////////////////////////////////////////////////////////
        /** @brief If possible, show the console window.
         *  @return The console.
        **/
        ////////////////////////////////////////////////////////////
        Console& show();

        ////////////////////////////////////////////////////////////
        /** @name Operators
         *  Helpers to write basics things to the Console.
         *
         *  @{
        **/
        ////////////////////////////////////////////////////////////
        Console& operator << (const String& str);
        Console& operator << (const char* str);
        Console& operator << (char c);
        Console& operator << (int i);
        Console& operator << (unsigned long li);
        ////////////////////////////////////////////////////////////
        /** @}
        **/
        ////////////////////////////////////////////////////////////

    private:
        ////////////////////////////////////////////////////////////
        /** @brief Write things in the console.
         *  @internal
         *
         *  @param str: String to write.
         *  @param foreground : text's foreground color.
         *  @param background : text's backgrouund color.
         *  @param bold : Bold state.
         *  @param blink : Blink state.
         *  @return The console.
        **/
        ////////////////////////////////////////////////////////////
        void write(const String& str, Color foreground, Color background, bool bold, bool blink);

    protected:

        ConsoleOptions currentState;///< Current console state.
        String dumpedLog;///< Black box of the console. Record everything written.
    };

    ////////////////////////////////////////////////////////////
    /** @class EmptyConsole
     *  @ingroup Utils
     *  @brief Faked Console System.
     *
     *  Use this class Singleton to provide macro-specific debug
     *  operations.
     *
     *  In macro aprodebug, it is used in Released mode.
    **/
    ////////////////////////////////////////////////////////////
    class APRO_DLL EmptyConsole : public Singleton<EmptyConsole>
    {
        APRO_DECLARE_SINGLETON(EmptyConsole)

    public:

        template <typename T>
        EmptyConsole& operator << (const T& _a_thing) { return *this; }
    };
}

#endif
