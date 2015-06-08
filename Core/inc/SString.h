////////////////////////////////////////////////////////////
/** @file String.h
 *  @ingroup Global
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 25/06/2012 - 05/06/2015
 *
 *  @brief
 *  Defines the String class.
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
#ifndef APROSTRING_H
#define APROSTRING_H

#include "Platform.h"
#include "Array.h"
#include "List.h"
#include "GenericHash.h"

namespace APro
{
    ////////////////////////////////////////////////////////////
    /** @class String
     *  @ingroup Global
     *  @brief Defines a string, with variable size.
     *  @details This is a
     *  non-threadsafe version, neither hared string version.
     *  It is only an ASCII string.
     *  @note String add automaticly a Null-character at the
     *  end of the string.
    **/
    ////////////////////////////////////////////////////////////
    class APRO_DLL String : public Swappable <String>
    {

    private:

        Array<char> mstr;///< The string

    public:

        ////////////////////////////////////////////////////////////
        /** Default constructor
        **/
        ////////////////////////////////////////////////////////////
        String();

        ////////////////////////////////////////////////////////////
        /** Explicit constructor for C-string.
         *  @param str : C-style string.
        **/
        ////////////////////////////////////////////////////////////
		String(const char* str);
        String(const char* str, size_t sz);

        ////////////////////////////////////////////////////////////
        /** Copy constructor
        **/
        ////////////////////////////////////////////////////////////
        String(const String& str);
        
        ////////////////////////////////////////////////////////////
        /** @brief Move Constructor.
        **/
        ////////////////////////////////////////////////////////////
        String(String&& rhs);
        
        ////////////////////////////////////////////////////////////
        /** @brief Swap this object with another one from the same
         *  kind.
         *  @see Swappable
        **/
        ////////////////////////////////////////////////////////////
        void swap (String& rhs);

        ~String();
        
	public:
        
        ////////////////////////////////////////////////////////////
        /** @{
         *  @brief Appends the given char, string or real to this 
         *  String.
         *  @see Array::append(), Array::reserve(), Array::push_back(),
         *  Array::prepend()
        **/
        ////////////////////////////////////////////////////////////
        void append(char c);
        void append(const char* c);
        void append(const String& c);
        void append(const Real& rhs);
        /** @} */

        ////////////////////////////////////////////////////////////
        /** @{
         *  @brief Prepends the given char, string or real to this 
         *  String.
         *  @see Array::append(), Array::reserve(), Array::push_front(),
         *  Array::prepend()
        **/
        ////////////////////////////////////////////////////////////
        void prepend(char c);
        void prepend(const char* c);
        void prepend(const String& c);
        void prepend(const Real& rhs);
        /** @} */

        ////////////////////////////////////////////////////////////
        /** @{
         *  @brief Insert the given char, string or real to this 
         *  String.
         *  @see Array::insert(), Array::reserve()
        **/
        ////////////////////////////////////////////////////////////
        void insert(size_t before, char c, size_t it = 1);
        void insert(size_t before, const char* c, size_t it = 1);
        void insert(size_t before, const String& c, size_t it = 1);
        void insert(size_t before, const Real& rhs, size_t it = 1);
        /** @} */
        
	public:

		////////////////////////////////////////////////////////////
        /** @brief Erases given indexes in the String. ( [first, last[ )
        **/
        ////////////////////////////////////////////////////////////
        void erase(size_t first, size_t last = 0);
        
        ////////////////////////////////////////////////////////////
        /** @brief Clears the String.
        **/
        ////////////////////////////////////////////////////////////
        void clear();

        size_t findFirst(char c, size_t from = 0) const;
        size_t findFirst(const String& str, size_t from = 0) const;

        size_t findLast(char c) const;
        size_t findLast(const String& str) const;

        /* Return the string[from, to). */
        String extract(size_t from, size_t to) const;

        List<String> explode(const String & str) const;
        List<String> explode(const char* str) const;
        List<String> explode(char c) const;

        int replaceEvery(char from, char to);
        void replace(const String& str, const String& to);

        bool match(char c) const;
        bool match(const String& str) const;

        bool isEmpty() const;
        size_t size() const;

        Array<char>& toArray();
        const Array<char>& toCstArray() const;

        const char* toCstChar() const;

        char& at(size_t index);
        const char& at(size_t index) const;

        char& operator[](size_t index);
        const char& operator[](size_t index) const;

        char& first();
        const char& first() const;

        char& last();
        const char& last() const;

        String& operator << (char c);
        String& operator << (const String & str);
        String& operator << (const char* str);
        String& operator << (Real nb);

        static String toString(unsigned int num);
        static String toString(int num);
        static String toString(double num);
        static String toString(Real r);
        static String toString(bool b);

        static int toInt(const String& str);
        static double toDouble(const String& str);
        Real toReal() const;
        int toInt() const;

        String & operator = (const String & other);
        String & operator = (const char* other);

        bool operator == (const String& other) const;
        bool operator != (const String& other) const;

        bool operator == (const char* other) const;
        bool operator != (const char* other) const;

        String operator + (const char* other) const;
        String operator + (const String& other) const;
        String operator + (const Real& nb) const;

        static String toUpper(const String& other);
        static String toLower(const String& other);

        static char toUpper(char c);
        static char toLower(char c);

        static String fromDouble(double d);
        static String FromInt(int i);

        ////////////////////////////////////////////////////////////
        /** @brief Performs a standard hash.
         *
         *  Same strings will return the same hash, but each strings
         *  has a unique hash.
        **/
        ////////////////////////////////////////////////////////////
        HashType hash() const;

        ////////////////////////////////////////////////////////////
        /** @brief Performs a standard hash.
         *
         *  Same strings will return the same hash, but each strings
         *  has a unique hash.
        **/
        ////////////////////////////////////////////////////////////
        static HashType Hash(const char* str);
        static int Hash(const String& str) { return String::Hash(str.toCstChar()); }
        static int Hash2(char* const& str) { return (int) String::Hash(str); }

        // return size of given string, without the null-terminated character.
        static int Size(const char* str);

        bool operator < (const String& other) const;
        
        ////////////////////////////////////////////////////////////
        /** @brief Interpret given string as an hexadecimal number
         *  and returns it.
        **/
        ////////////////////////////////////////////////////////////
        static u32 ToHex(const char* str);
        
        ////////////////////////////////////////////////////////////
        /** @brief Modify the String, interpreting it as a texted C-String,
         *  beginning and ending with '"', and having every \" or \'.
         * 
         *  This function so erase the ", convert the \" to ", \' to ', 
         *  etc.
        **/
        ////////////////////////////////////////////////////////////
        void interpretastext();
        
        static String Empty;///< @brief An empty string.
        
        ////////////////////////////////////////////////////////////
        /** @brief Build a string using the traditionnal vsprintf C
         *  function.
         *  @note The size of the String should not be more than
         *  2048.
        **/
        ////////////////////////////////////////////////////////////
        static String Build(const char* format, ...);

    protected:

        void assertFinal();
    };

    typedef Array<String> StringArray;
    typedef List<String>  StringList;
    
    APRO_DECLARE_GENERICHASH(char*, String::Hash2);
    APRO_DECLARE_GENERICHASH(String, String::Hash);
}

#endif
