/** @file Keys.cpp
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 21/03/2013
 *
 *  @addtogroup Global
 *  @addtogroup System
 *
 *  This file defines the Keys used in the Engine.
 *
**/
#include "Keys.h"

namespace APro
{
    const char* keyToString(KEY k)
    {
        switch(k)
        {
        case KEY_0:
            return "key 0";
        case KEY_1:
            return "key 1";
        case KEY_2:
            return "key 2";
        case KEY_3:
            return "key 3";
        case KEY_4:
            return "key 4";
        case KEY_5:
            return "key 5";
        case KEY_6:
            return "key 6";
        case KEY_7:
            return "key 7";
        case KEY_8:
            return "key 8";
        case KEY_9:
            return "key 9";
        case KEY_A:
            return "key A";
        case KEY_B:
            return "key B";
        case KEY_C:
            return "key C";
        case KEY_D:
            return "key D";
        case KEY_E:
            return "key E";
        case KEY_F:
            return "key F";
        case KEY_G:
            return "key G";
        case KEY_H:
            return "key H";
        case KEY_I:
            return "key I";
        case KEY_J:
            return "key J";
        case KEY_K:
            return "key K";
        case KEY_L:
            return "key L";
        case KEY_M:
            return "key M";
        case KEY_N:
            return "key N";
        case KEY_O:
            return "key O";
        case KEY_P:
            return "key P";
        case KEY_Q:
            return "key Q";
        case KEY_R:
            return "key R";
        case KEY_S:
            return "key S";
        case KEY_T:
            return "key T";
        case KEY_U:
            return "key U";
        case KEY_V:
            return "key V";
        case KEY_W:
            return "key W";
        case KEY_X:
            return "key X";
        case KEY_Y:
            return "key Y";
        case KEY_Z:
            return "key Z";
        case KEY_ALT:
            return "key ALT";
        case KEY_APPS:
            return "key APPS";
        case KEY_ATTN:
            return "key ATTN";
        case KEY_CANCEL:
            return "key CANCEL";
        case KEY_CAPSLOCK:
            return "key CAPSLOCK";
        case KEY_CLEAR:
            return "key CLEAR";
        case KEY_CONVERT:
            return "key CONVERT";
        case KEY_COUNT:
            return "key COUNT";
        case KEY_CRSEL:
            return "key CRSEL";
        case KEY_CTRL:
            return "key CTRL";
        case KEY_DEBUT:
            return "key DEBUT";
        case KEY_DEL:
            return "key DEL";
        case KEY_DOWN:
            return "key DOWN";
        case KEY_ENTER:
            return "key ENTER";
        case KEY_ERASE:
            return "key ERASE";
        case KEY_EREOF:
            return "key EREOF";
        case KEY_ESC:
            return "key ESC";
        case KEY_EXECUT:
            return "key EXECUT";
        case KEY_EXSEL:
            return "key EXSEL";
        case KEY_F1:
            return "key F1";
        case KEY_F10:
            return "key F10";
        case KEY_F11:
            return "key F11";
        case KEY_F12:
            return "key F12";
        case KEY_F13:
            return "key F13";
        case KEY_F14:
            return "key F14";
        case KEY_F15:
            return "key F15";
        case KEY_F16:
            return "key F16";
        case KEY_F17:
            return "key F17";
        case KEY_F18:
            return "key F18";
        case KEY_F19:
            return "key F19";
        case KEY_F2:
            return "key F2";
        case KEY_F20:
            return "key F20";
        case KEY_F21:
            return "key F21";
        case KEY_F22:
            return "key F22";
        case KEY_F24:
            return "key F24";
        case KEY_F3:
            return "key F3";
        case KEY_F4:
            return "key F4";
        case KEY_F5:
            return "key F5";
        case KEY_F6:
            return "key F6";
        case KEY_F7:
            return "key F7";
        case KEY_F8:
            return "key F8";
        case KEY_F9:
            return "key F9";
        case KEY_FIN:
            return "key FIN";
        case KEY_FINAL:
            return "key FINAL";
        case KEY_HANGUEL:
            return "key HANGUEL";
        case KEY_HANJA:
            return "key HANJA";
        case KEY_HELP:
            return "key HELP";
        case KEY_INSER:
            return "key INSER";
        case KEY_JUNJA:
            return "key JUNJA";
        case KEY_LEFT:
            return "key LEFT";
        case KEY_LEFTCTRL:
            return "key LEFTCTRL";
        case KEY_LEFTMENU:
            return "key LEFTMENU";
        case KEY_LEFTSHIFT:
            return "key LEFTSHIFT";
        case KEY_LEFTWIN:
            return "key LEFTWIN";
        case KEY_MINUS:
            return "key MINUS";
        case KEY_MODECHANGE:
            return "key MODECHANGE";
        case KEY_NOCONVERT:
            return "key NOCONVERT";
        case KEY_NUMPAD_0:
            return "numpad 0";
        case KEY_NUMPAD_1:
            return "numpad 1";
        case KEY_NUMPAD_2:
            return "numpad 2";
        case KEY_NUMPAD_3:
            return "numpad 3";
        case KEY_NUMPAD_4:
            return "numpad 4";
        case KEY_NUMPAD_5:
            return "numpad 5";
        case KEY_NUMPAD_6:
            return "numpad 6";
        case KEY_NUMPAD_7:
            return "numpad 7";
        case KEY_NUMPAD_8:
            return "numpad 8";
        case KEY_NUMPAD_9:
            return "numpad 9";
        case KEY_NUMPAD_ADD:
            return "numpad ADD";
        case KEY_NUMPAD_DECI:
            return "numpad DECI";
        case KEY_NUMPAD_DIV:
            return "numpad DIV";
        case KEY_NUMPAD_MULT:
            return "numpad MULT";
        case KEY_NUMPAD_SEP:
            return "numpad SEP";
        case KEY_NUMPAD_SUB:
            return "numpad SUB";
        case KEY_PAGEDWN:
            return "key PAGEDWN";
        case KEY_PAGEUP:
            return "key PAGEUP";
        case KEY_PAUSE:
            return "key PAUSE";
        case KEY_PLAY:
            return "key PLAY";
        case KEY_PLUS:
            return "key PLUS";
        case KEY_PRINT:
            return "key PRINT";
        case KEY_RIGHT:
            return "key RIGHT";
        case KEY_RIGHTCTRL:
            return "key RIGHTCTRL";
        case KEY_RIGHTMENU:
            return "key RIGHTMENU";
        case KEY_RIGHTSHIFT:
            return "key RIGHTSHIFT";
        case KEY_RIGHTWIN:
            return "key RIGHTWIN";
        case KEY_SCREENPRINT:
            return "key SCREENPRINT";
        case KEY_SCROLLLOCK:
            return "key SCROLLLOCK";
        case KEY_SELECT:
            return "key SELECT";
        case KEY_SHIFT:
            return "key SHIFT";
        case KEY_SLEEP:
            return "key SLEEP";
        case KEY_SPACE:
            return "key SPACE";
        case KEY_TAB:
            return "key TAB";
        case KEY_UP:
            return "key UP";
        case KEY_VERRNUM:
            return "key VERRNUM";
        case KEY_VIRGULE:
            return "key VIRGULE";
        case KEY_ZOOM:
            return "key ZOOM";
        case KEY_UNKNOW:
        case KEY_PA1:
        case KEY_OEM_CLEAR:
        case KEY_IME_ACCEPT:
        default:
            return "unknown key";
        }
    }
}
