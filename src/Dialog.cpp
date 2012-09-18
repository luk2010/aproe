/** @file MessageBox.cpp
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 17/09/2012
 *
 *  @addtogroup Global
 *  @addtogroup System
 *
 *  This file defines the MessageBox class.
 *
**/
#include "Dialog.h"

namespace APro
{
    void Dialog::information(const String& title, const String & msg)
    {
#if APRO_PLATFORM == APRO_WINDOWS

        MessageBox(0, msg.toCstChar(), title.toCstChar(), MB_OK | MB_ICONINFORMATION);

#endif
    }

    void Dialog::warning(const String& title, const String & msg)
    {
#if APRO_PLATFORM == APRO_WINDOWS

        MessageBox(0, msg.toCstChar(), title.toCstChar(), MB_OK | MB_ICONWARNING);

#endif
    }

    Dialog::Answer::_ Dialog::ask(const String& title, const String & msg)
    {
#if APRO_PLATFORM == APRO_WINDOWS

        int id = MessageBox(0, msg.toCstChar(), title.toCstChar(), MB_YESNO | MB_ICONINFORMATION);

        switch(id)
        {
        case IDYES:
            return Answer::Yes;

        case IDNO:
          default:
            return Answer::No;
        }

#endif
    }

    Dialog::Answer::_ Dialog::askError(const String& title, const String & msg)
    {
#if APRO_PLATFORM == APRO_WINDOWS

        int id = MessageBox(0, msg.toCstChar(), title.toCstChar(), MB_YESNO | MB_ICONWARNING);

        switch(id)
        {
        case IDYES:
            return Answer::Yes;

        case IDNO:
          default:
            return Answer::No;
        }

#endif
    }
}
