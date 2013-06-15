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
#include <unistd.h>

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

        return Answer::No;
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

        return Answer::No;
    }

    List<String> Dialog::chooseFile(const String& title, const String& filters, const String& defaultFilename, bool multiSelection)
    {
#if APRO_PLATFORM == APRO_WINDOWS

        // GetOpenFileName seems to change the current working directory so store it.
        char curWD[250];
        getcwd(curWD, 250);

        OPENFILENAME ofn;
        char buffer[260];
        if(!defaultFilename.isEmpty())
        {
            memcpy(buffer, defaultFilename.toCstChar(), sizeof(char) * (defaultFilename.size() + 1));
        }
        else
        {
            buffer[0] = '\0';
        }

        char filtersbuff[filters.size() + 1];
        memcpy(filtersbuff, filters.toCstChar(), sizeof(char) * (filters.size() + 1));

        ZeroMemory(&ofn, sizeof(ofn));
        ofn.lStructSize = sizeof(ofn);
        ofn.hwndOwner = NULL;
        ofn.lpstrFile = buffer;
        ofn.nMaxFile = sizeof(buffer);
        ofn.lpstrFile = filtersbuff;
        ofn.nFilterIndex = 1;
        ofn.lpstrFileTitle = NULL;
        ofn.nMaxFileTitle = 0;
        ofn.lpstrInitialDir = NULL;
        ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

        List<String> strList;
        if(GetOpenFileName(&ofn) == TRUE)
        {
            strList << String(ofn.lpstrFile);
        }

        // Restore working directory after GetOpenFileName
        chdir(curWD);

        return strList;

#endif

        return List<String>();
    }
}
