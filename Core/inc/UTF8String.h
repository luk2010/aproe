////////////////////////////////////////////////////////////
/** @file UTF8String.h
 *  @ingroup Utils
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 04/11/2014 - 07/02/2015
 *
 *  @brief
 *  Defines the UTF8String class.
 *
 *  @copyright
 *  Atlanti's Project Engine
 *  Copyright (C) 2012 - 2015  Atlanti's Corp
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
#ifndef APROUTF8STRING_H 
#define APROUTF8STRING_H

#include "Platform.h"
#include "Array.h"

namespace APro
{
    ////////////////////////////////////////////////////////////
    /** @class UTF8CHar
     *  @ingroup Global
     *  @brief A helper class to categorize data about UTF-8 
     *  characters.
     *
     *  @note
     *  The UTF-8 CodePoint logic is explained here : http://fr.wikipedia.org/wiki/UTF-8
     *  All the implementation is based on CodePoints and Octets value
     *  given there.
    **/
    ////////////////////////////////////////////////////////////
    class APRO_DLL UTF8Char
    {
    public:
        
        ////////////////////////////////////////////////////////////
        /** @brief Type the Octet can have.
        **/
        ////////////////////////////////////////////////////////////
        enum Type {
            TBegin,      ///< @brief Octet is first in sequence. ( v = [00 - 7F] | [C2 - F4] )
            TContinued,  ///< @brief Octet is a continuing sequence. ( v = [80 - BF] )
            
            TInvalid     ///< @brief Octet value is Invalid.
        };
        
        ////////////////////////////////////////////////////////////
        /** @brief Type of the Octet in the sequence.
        **/
        ////////////////////////////////////////////////////////////
        enum SequenceType {
            STAscii, ///< @brief Octet is the only sequence octet. ( v = [00 - 7F] )
            STOctet1x, ///< @brief First octet of a sequence of 2. ( v = [C2 - DF] )
            STOctet1xx, ///< @brief First octet of a sequence of 3. ( v = [E0 - EF] )
            STOctet1xxx, ///< @brief First octet of a sequence of 4. ( v = [F0 - F4] )
            STOctetXNormal, ///< @brief Continuing octet (can be 2nd, third or fourth) normally encountered. ( v = [80 - BF] )
            STOctet2E0, ///< @brief Second octet of EO. ( v = [A0 - BF] )
            STOctet2ED, ///< @brief Second octet of ED. ( v = [80 - 9F] )
            STOctet2F0, ///< @brief Second octet of F0. ( v = [90 - BF] )
            STOctet2F4, ///< @brief Second octet of F4. ( v = [80 - 8F] )
            
            STInvalid, ///< @brief Octet type can be resolved or is invalid.
        
            OE1C0C1, ///< @brief Octet 1 is C0 or C1.
            OE2BAD   ///< @brief Octet 2 has invalid value depending on octet 1.
        };
        
        /// @brief A simple type to define what is the smallest value in an
        /// UTF8 string.
        typedef uint8_t Octet;
        
        static Type OctetType(Octet cp);
        static SequenceType Sequence(Octet cp, Octet prev = 0x00);
        
        static bool IsSequenceContinuing(SequenceType st);
        static int  GetOctetNumber(const Octet& first);
        
        typedef uint32_t CodePoint;///< A common CodePoint type who can handle every Unicode UTF-8 character.
        
        /// @brief Extract a code point from given sequence. This sequence can be 1, 2, 3 or 4 octet long.
        static CodePoint ExtractUTF8CodePoint(Octet o1, Octet o2 = 0x00, Octet o3 = 0x00, Octet o4 = 0x00);
        
        /// @brief Return the number of segment used to encode given CodePoint.
        static size_t GetCodePointSegmentSize(CodePoint cp);
        
        /// @brief Returns true if given CodePoint is a spacing character. (U+0020, U+0009, U+000D, U+000A)
        /// @note UTF8 CodePoin for spacing characters from http://www.w3.org/TR/REC-xml/#NT-S
        static bool IsSpace(const CodePoint& cp);
        
        /// @brief Convert given CodePoint to char, and returns the valid char used.
        static int toChar(char* ret , const CodePoint& cp);
        /// @brief Convert given hexadecimal string to CodePoint.
        static CodePoint fromStr(const char* str);
        
        static const CodePoint CPInvalid; ///< Defines an Invalid CodePoint.
        static const CodePoint CPNull;    ///< Defines the Null CodePoint.
        
        typedef struct BOM {
            char byte1;
            char byte2;
            char byte3;
        } BOM;
        static const BOM CPBOM;  ///< Defines the ByteOrderMask to identify UTF8.
    };
    
    ////////////////////////////////////////////////////////////
    /** @class String
     *  @ingroup Global
     *  @brief Defines an UTF8 encoded String.
     *
     *  The UTF8String class is constitued with a simple array of
     *  codepoints (cp) , designating the sentence cp by cp. 
     *  This method allows us to have fast managing of the sentence, 
     *  but the disadvantage here is that an UTF8 string take 4 times
     *  more memory than an ASCII string (as a cp is 4 char). 
     *
     *  @note Read/Write functions
     *  You can use the File IO functions to read/write to a file.
     *  We advice you to add a correct BOM at the beginning of every 
     *  UTF8 file.
    **/
    ////////////////////////////////////////////////////////////
    class APRO_DLL UTF8String
    {
    private:
        
        Array<UTF8Char::CodePoint> mdata;///< The string data.
        
    public:
        
        UTF8String ();
        UTF8String (const UTF8String& str);
        UTF8String (UTF8String&& str);


	public:
        
        size_t size() const { return mdata.size() - 1; }
        bool isEmpty() const { return size() == 0; }
        
        typedef Array<UTF8Char::CodePoint>::iterator iterator;
        typedef Array<UTF8Char::CodePoint>::const_iterator const_iterator;
        
        iterator begin() { return mdata.begin(); }
        const_iterator begin() const { mdata.begin(); }
        
        iterator end() { return mdata.end(); }
        const_iterator end() const { return mdata.end(); }
        
        iterator last() { return mdata.last(); }
        const_iterator last() const { return mdata.last(); }
        
    public:
        
        void append (const UTF8String& str);
        void push_back (const UTF8String& str) { append(str); }
        UTF8String& operator << (const UTF8String& str) { append(str); return *this; }
        
        void append (const UTF8Char::CodePoint& cp);
        void push_back (const UTF8Char::CodePoint& cp) { append(cp); }
        
        void prepend (const UTF8String& str);
        void push_front (const UTF8String& str) { prepend(str); }
        
        void clear();
        void erase(iterator beg, const_iterator e = nullptr);
        
        void insert(const UTF8Char::CodePoint& cp, const_iterator);
        
    public:
        
        static UTF8String fromAscii (const char* str);
        static UTF8String fromUtf8Data(const UTF8Char::Octet* data);
    };
}

#endif
