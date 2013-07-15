/** @file Keys.h
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
#ifndef APRO_KEYS_H
#define APRO_KEYS_H

#include "Platform.h"

namespace APro
{
    enum KEY
    {
        KEY_CANCEL          = 0x03,//Touche Ctrl+Break
        KEY_UNKNOW          = 0x07,
        KEY_ERASE           = 0x08,//Effacer
        KEY_TAB             = 0x09,//Tab
        KEY_CLEAR           = 0x0C,//Clear
        KEY_ENTER           = 0x0D,//Entrée
        KEY_SHIFT           = 0x10,//Shift
        KEY_CTRL            = 0x11,//Control
        KEY_ALT             = 0x12,//Alt
        KEY_PAUSE           = 0x13,//Pause
        KEY_CAPSLOCK        = 0x14,//Caps lock (verrouillage des majuscules)
        KEY_KANA            = 0x15,//Mode Kana ?
        KEY_HANGUEL         = 0x15,//Mode Hanguel ?
        KEY_HANGUL          = 0x15,//Mode Hangul ?
        KEY_JUNJA           = 0x17,//Mode Junja ?
        KEY_FINAL           = 0x18,//Mode Final ?
        KEY_HANJA           = 0x19,//Mode Hanja ?
        KEY_KENJI           = 0x19,//Mode Kenji ?
        KEY_ESC             = 0x1B,//Echap
        KEY_CONVERT         = 0x1C,//Mode Convertit ?
        KEY_NOCONVERT       = 0x1D,//Mode non convertit ?
        KEY_IME_ACCEPT      = 0x1E,//Unknown
        KEY_MODECHANGE      = 0x1F,//Unknown
        KEY_SPACE           = 0x20,//Espace
        KEY_PAGEUP          = 0x21,//Page Up
        KEY_PAGEDWN         = 0x22,//Page Down
        KEY_FIN             = 0x23,//Fin
        KEY_DEBUT           = 0x24,
        KEY_LEFT            = 0x25,//Gauche
        KEY_UP              = 0x26,//Haut
        KEY_RIGHT           = 0x27,//Droite
        KEY_DOWN            = 0x28,//Bas
        KEY_SELECT          = 0x29,
        KEY_PRINT           = 0x2A,
        KEY_EXECUT          = 0x2B,
        KEY_SCREENPRINT     = 0x2C,
        KEY_INSER           = 0x2D,
        KEY_DEL             = 0x2E,
        KEY_HELP            = 0x2F,
        KEY_0               = 0x30,
        KEY_1               = 0x31,
        KEY_2               = 0x32,
        KEY_3               = 0x33,
        KEY_4               = 0x34,
        KEY_5               = 0x35,
        KEY_6               = 0x36,
        KEY_7               = 0x37,
        KEY_8               = 0x38,
        KEY_9               = 0x39,
        KEY_A               = 0x41,
        KEY_B               = 0x42,
        KEY_C               = 0x43,
        KEY_D               = 0x44,
        KEY_E               = 0x45,
        KEY_F               = 0x46,
        KEY_G               = 0x47,
        KEY_H               = 0x48,
        KEY_I               = 0x49,
        KEY_J               = 0x4A,
        KEY_K               = 0x4B,
        KEY_L               = 0x4C,
        KEY_M               = 0x4D,
        KEY_N               = 0x4E,
        KEY_O               = 0x4F,
        KEY_P               = 0x50,
        KEY_Q               = 0x51,
        KEY_R               = 0x52,
        KEY_S               = 0x53,
        KEY_T               = 0x54,
        KEY_U               = 0x55,
        KEY_V               = 0x56,
        KEY_W               = 0x57,
        KEY_X               = 0x58,
        KEY_Y               = 0x59,
        KEY_Z               = 0x5A,
        KEY_LEFTWIN         = 0x5B,
        KEY_RIGHTWIN        = 0x5C,
        KEY_APPS            = 0x5D,
        KEY_SLEEP           = 0x5F,
        KEY_NUMPAD_0        = 0x60,
        KEY_NUMPAD_1        = 0x61,
        KEY_NUMPAD_2        = 0x62,
        KEY_NUMPAD_3        = 0x63,
        KEY_NUMPAD_4        = 0x64,
        KEY_NUMPAD_5        = 0x65,
        KEY_NUMPAD_6        = 0x66,
        KEY_NUMPAD_7        = 0x67,
        KEY_NUMPAD_8        = 0x68,
        KEY_NUMPAD_9        = 0x69,
        KEY_NUMPAD_MULT     = 0x6A,
        KEY_NUMPAD_ADD      = 0x6B,
        KEY_NUMPAD_SEP      = 0x6C,
        KEY_NUMPAD_SUB      = 0x6D,
        KEY_NUMPAD_DECI     = 0x6E,
        KEY_NUMPAD_DIV      = 0x6F,
        KEY_F1              = 0x70,
        KEY_F2              = 0x71,
        KEY_F3              = 0x72,
        KEY_F4              = 0x73,
		KEY_F5              = 0x74,
		KEY_F6              = 0x75,
		KEY_F7              = 0x76,
		KEY_F8              = 0x77,
		KEY_F9              = 0x78,
		KEY_F10             = 0x79,
		KEY_F11             = 0x7A,
		KEY_F12             = 0x7B,
		KEY_F13             = 0x7C,
		KEY_F14             = 0x7D,
		KEY_F15             = 0x7E,
		KEY_F16             = 0x7F,
		KEY_F17             = 0x80,
		KEY_F18             = 0x81,
		KEY_F19             = 0x82,
		KEY_F20             = 0x83,
		KEY_F21             = 0x84,
		KEY_F22             = 0x85,
		KEY_F23             = 0x86,
		KEY_F24             = 0x87,
        KEY_VERRNUM         = 0x90,
        KEY_SCROLLLOCK      = 0x91,
        KEY_LEFTSHIFT       = 0xA0,
        KEY_RIGHTSHIFT      = 0xA1,
        KEY_LEFTCTRL        = 0xA2,
        KEY_RIGHTCTRL       = 0xA3,
        KEY_LEFTMENU        = 0xA4,
        KEY_RIGHTMENU       = 0xA5,
        KEY_PLUS            = 0xBB,
        KEY_VIRGULE         = 0xBC,
        KEY_MINUS           = 0xBD,
        KEY_ATTN            = 0xF6,
        KEY_CRSEL           = 0xF7,
        KEY_EXSEL           = 0xF8,
        KEY_EREOF           = 0xF9,
        KEY_PLAY            = 0xFA,
        KEY_ZOOM            = 0xFB,
        KEY_PA1             = 0xFD,
        KEY_OEM_CLEAR       = 0xFE,


		KEY_COUNT           = 0xFF
    };

    APRO_DLL const char* keyToString(KEY k);
    typedef char key_t;
}

#endif // APRO_KEYS_H
