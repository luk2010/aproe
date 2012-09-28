/** @file String.h
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 25/06/2012
 *
 *  @addtogroup Global
 *  @addtogroup Memory
 *
 *  This file defines the String class.
 *
**/
#ifndef APROSTRING_H
#define APROSTRING_H

#include "Platform.h"
#include "Array.h"
#include "List.h"

namespace APro
{
    class APRO_DLL String
    {

    private:

        Array<char> mstr;

    public:

        String();
        explicit String(const char* str);
        String(const String& str);

        ~String();

        void append(char c);
        void append(const char* c);
        void append(const String& c);

        void prepend(char c);
        void prepend(const char* c);
        void prepend(const String& c);

        void insert(size_t before, char c, size_t it = 1);
        void insert(size_t before, const char* c, size_t it = 1);
        void insert(size_t before, const String& c, size_t it = 1);

        void erase(size_t first, size_t last = 0);

        size_t findFirst(char c, size_t from = 0) const;
        size_t findFirst(const String& str, size_t from = 0) const;

        size_t findLast(char c) const;
        size_t findLast(const String& str) const;

        String extract(size_t from, size_t to) const;

        List<String> explode(const String & str) const;
        List<String> explode(const char* str) const;
        List<String> explode(char c) const;

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

        static String toString(unsigned int num);
        static String toString(int num);
        static String toString(double num);

        static int toInt(const String& str);

        String & operator = (const String & other);
        String & operator = (const char* other);

        bool operator == (const String& other) const;
        bool operator != (const String& other) const;

        bool operator == (const char* other) const;
        bool operator != (const char* other) const;

        String operator + (const char* other) const;
        String operator + (const String& other) const;

    protected:

        void assertFinal();
    };
}

#endif
