/** @file MessageBox.h
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 11/09/2012
 *
 *  @addtogroup Global
 *  @addtogroup System
 *
 *  This file defines the MessageBox class.
 *
**/
#ifndef APROMESSAGEBOX_H
#define APROMESSAGEBOX_H

#include "Platform.h"
#include "SString.h"

namespace APro
{
    class APRO_DLL Dialog
    {
    public:

        class Answer
        {
        public :
            enum _
            {
                Yes     = 0x0001,
                No      = 0x0010,
                OK      = 0x0100,
                Cancel  = 0x1000
            };
        };

        static void information(const String& title, const String & msg);
        static void warning(const String& title, const String & msg);
        static Answer::_ ask(const String& title, const String & msg);
        static Answer::_ askError(const String& title, const String & msg);
    };
}

#endif
