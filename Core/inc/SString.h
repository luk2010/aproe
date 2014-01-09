//////  //////////////////////////////////////////////////////
/** @file String.h
 *  @ingroup Global
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 25/06/2012
 *
 *  Defines the String class.
 *
**/
////////////////////////////////////////////////////////////
#ifndef APROSTRING_H
#define APROSTRING_H

#include "Platform.h"
#include "Array.h"

namespace APro
{
    class Number;

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
    class APRO_DLL String
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
        explicit String(const char* str);

        ////////////////////////////////////////////////////////////
        /** Copy constructor
        **/
        ////////////////////////////////////////////////////////////
        String(const String& str);

        ////////////////////////////////////////////////////////////
        /** Constructor from a Number.
        **/
        ////////////////////////////////////////////////////////////
        String(const Number& nb);

        ~String();

        void append(char c);
        void append(const char* c);
        void append(const String& c);
        void append(const Number& nb);

        void prepend(char c);
        void prepend(const char* c);
        void prepend(const String& c);
        void prepend(const Number& nb);

        void insert(size_t before, char c, size_t it = 1);
        void insert(size_t before, const char* c, size_t it = 1);
        void insert(size_t before, const String& c, size_t it = 1);

        void erase(size_t first, size_t last = 0);

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

        void clear();

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
        String& operator << (const Number& nb);

        static String toString(unsigned int num);
        static String toString(int num);
        static String toString(double num);

        static int toInt(const String& str);
        static double toDouble(const String& str);

        String & operator = (const String & other);
        String & operator = (const char* other);

        bool operator == (const String& other) const;
        bool operator != (const String& other) const;

        bool operator == (const char* other) const;
        bool operator != (const char* other) const;

        String operator + (const char* other) const;
        String operator + (const String& other) const;
        String operator + (const Number& nb) const;

        static String toUpper(const String& other);
        static String toLower(const String& other);

        static char toUpper(char c);
        static char toLower(char c);

        static String fromDouble(double d);

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

    protected:

        void assertFinal();
    };

    typedef Array<String> StringArray;
    typedef List<String>  StringList;
}

#endif
