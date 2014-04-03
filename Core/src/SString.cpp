/** @file String.cpp
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 25/06/2012 - 03/04/2014
 *
 *  @addtogroup Global
 *  @addtogroup Memory
 *
 *  This file defines the String class.
 *
**/
#include "ThreadMutex.h"
#include "SString.h"

namespace APro
{
    String::String()
    {
        mstr.append('\0');
    }

    String::String(const char* str)
        : mstr(str, strlen(str) + 1)
    {
        assertFinal();
    }

    String::String(const String& str)
        : mstr(str.toCstChar(), str.size() + 1)
    {
        assertFinal();
    }

    String::String(const Number& nb)
    {
        mstr.append('\0');
        append(nb);
    }

    String::~String()
    {
        mstr.clear();
    }

    void String::append(char c)
    {


        mstr.insert(mstr.lastIndex(), c);

        assertFinal();
    }

    void String::append(const char* c)
    {


        size_t sz = strlen(c);
        if(sz > 0)
        {
            for(unsigned int i = 0; i < sz; i++)
                mstr.insert(mstr.lastIndex(), c[i]);
        }
        assertFinal();
    }

    void String::append(const String & c)
    {


        if(c.size() > 0)
        {
            for(unsigned int i = 0; i < c.size(); i++)
                append(c.at(i));
        }
        assertFinal();
    }

    void String::append(const Number& nb)
    {


        append(String::fromDouble(nb.toReal()));
    }

    void String::prepend(char c)
    {


        mstr.prepend(c);
        assertFinal();
    }

    void String::prepend(const String& c)
    {


        for(int i = ((int) c.size()) - 1; i >= 0; i--)
            prepend(c.at(i));
        assertFinal();
    }

    void String::prepend(const char* c)
    {


        size_t sz = strlen(c);
        if(sz > 0)
        {
            for(int i = ((int) sz) - 1; i >= 0; i--)
                prepend(c[i]);
        }
        assertFinal();
    }

    void String::prepend(const Number& nb)
    {


        prepend(String::fromDouble(nb.toReal()));
    }

    void String::insert(size_t before, char c, size_t it)
    {


        mstr.insert(before, c, it);
        assertFinal();
    }

    void String::insert(size_t before, const char* c, size_t it)
    {


        size_t sz = strlen(c);
        if(sz > 0)
        {
            for(unsigned int j = 1; j <= it; j++)
            {
                unsigned int k = before;
                for(unsigned int i = 0; i < sz; i++)
                {
                    insert(k, c[i]);
                    k++;
                }
            }
        }

        assertFinal();
    }

    void String::insert(size_t before, const String& c, size_t it)
    {


        for(unsigned int j = 0; j < it; j++)
        {
            unsigned int k = before;
            for(unsigned int i = 0; i < c.size(); i++)
            {
                insert(k, c.at(i));
                k++;
            }
        }

        assertFinal();
    }

    void String::erase(size_t first, size_t last)
    {


        if(last >= size()) last = size() - 1;

        mstr.erase(first, last);
        assertFinal();
    }

    size_t String::findFirst(char c, size_t from) const
    {


        for(unsigned int i = from; i < size(); i++)
            if(mstr.at(i) == c) return i;

        return size();
    }

    size_t String::findFirst(const String & str, size_t from) const
    {


        for(unsigned int i = from; i < size() && size() - i < str.size(); i++)
        {
            if(mstr.at(i) == str.at(0))
            {
                for(unsigned int j = 1; j < str.size(); j++)
                {
                    if(j == str.size() - 1 && mstr.at(j) == str.at(j))
                        return i;
                }
            }
        }

        return size();
    }

    size_t String::findLast(char c) const
    {


        for(int i = size() - 1; i >= 0; i--)
            if(mstr.at(i) == c) return i;

        return size();
    }

    size_t String::findLast(const String & str) const
    {


        for(int i = size() - str.size(); i >= 0; i--)
        {
            if(mstr.at(i) == str.at(0))
            {
                for(unsigned int j = 1; j < str.size(); j++)
                {
                    if(j == str.size() - 1 && mstr.at(j) == str.at(j))
                        return i;
                }
            }
        }

        return size();
    }

    String String::extract(size_t from, size_t to) const
    {


        String result;

        if(from > to) Allocator<size_t>::swap(&from, &to, 1);
        if(to > size()) to = size();
        if(from >= size()) return result;

        for(size_t i = from; i < to; i++)
            result.append(at(i));

        return result;
    }

    bool String::match(char c) const
    {

        return findFirst(c) != size();
    }

    bool String::match(const String& str) const
    {

        return findFirst(str) != size();
    }

    bool String::isEmpty() const
    {

        return size() == 0;
    }

    size_t String::size() const
    {

        return mstr.size() - 1;
    }

    Array<char>& String::toArray()
    {

        return mstr;
    }

    const Array<char>& String::toCstArray() const
    {

        return mstr;
    }

    const char* String::toCstChar() const
    {

        return &(mstr[0]);
    }

    void String::clear()
    {

        mstr.clear();
        mstr.append('\0');
    }

    char& String::at(size_t index)
    {

        return mstr.at(index);
    }

    const char& String::at(size_t index) const
    {

        return mstr.at(index);
    }

    char& String::operator[](size_t index)
    {

        return mstr.at(index);
    }

    const char& String::operator[](size_t index) const
    {

        return mstr.at(index);
    }

    char& String::first()
    {

        return mstr.at(0);
    }

    const char& String::first() const
    {

        return mstr.at(0);
    }

    char& String::last()
    {

        return mstr.at(size());
    }

    const char& String::last() const
    {

        return mstr.at(size());
    }

    String& String::operator<<(char c)
    {

        append(c);
        return *this;
    }

    String& String::operator<<(const char* str)
    {

        append(str);
        return *this;
    }

    String& String::operator<<(const String& str)
    {

        append(str);
        return *this;
    }

    String& String::operator<<(const Number& nb)
    {

        append(String::fromDouble(nb.toReal()));
        return *this;
    }

    void String::assertFinal()
    {

        if(mstr.at(size()) != '\0')
            mstr.append('\0');
    }

    String String::toString(unsigned int num)
    {
        char buffer[30];
        sprintf(buffer, "%d", num);
        return String(buffer);
    }

    String String::toString(int num)
    {
        char buffer[30];
        sprintf(buffer, "%d", num);
        return String(buffer);
    }

    String String::toString(double num)
    {
        char buffer[30];
        sprintf(buffer, "%f", num);
        return String(buffer);
    }

    String String::toString(Real r)
    {
        char buffer[30];
        sprintf(buffer, "%f", r);
        return String(buffer);
    }

    Real String::toReal() const
    {
#ifdef _USE_DOUBLEREAL_
        return strtod(toCstChar(), nullptr);
#else
        return strtof(toCstChar(), nullptr);
#endif // _USE_DOUBLEREAL_
    }

    int String::toInt() const
    {
        return String::toInt(*this);
    }

    bool String::operator==(const String & other) const
    {

        return hash() == other.hash();
    }

    bool String::operator!=(const String & other) const
    {

        return !(*this == other);
    }

    bool String::operator == (const char* other) const
    {

        return *this == String(other);
    }

    bool String::operator != (const char* other) const
    {

        return !(*this == other);
    }

    int String::replaceEvery(char from, char to)
    {

        int nb = 0;
        for(unsigned int i = 0; i < size(); ++i)
        {
            if(at(i) == from)
            {
                at(i) = to;
                ++nb;
            }
        }

        return nb;
    }

    void String::replace(const String& str, const String& to)
    {

        if(str == to) return;

        int pos = findFirst(str);
        while(pos > -1)
        {
            erase(pos, pos + str.size() - 1);
            insert(pos, to);
            pos = findFirst(str);
        }
    }

    String& String::operator = (const String & other)
    {

        mstr = other.mstr;
        assertFinal();

        return *this;
    }

    String& String::operator = (const char* other)
    {

        return *this = String(other);
    }

    List<String> String::explode(char c) const
    {

        String str(*this);
        List<String> ret;

        size_t old = 0;
        size_t index = str.findFirst(c);
        while(index < str.size())
        {
            ret.append(str.extract(old, index));
            old = index + 1;
            index = str.findFirst(c, old);
        }

        ret.append(str.extract(old, index + 1));
        return ret;
    }

    List<String> String::explode(const String& str) const
    {

        String strc(*this);
        List<String> ret;

        size_t old = 0;
        size_t index = strc.findFirst(str);

        while(index < strc.size())
        {
            ret.append(strc.extract(old, index));
            old = index + 1;
            index = strc.findFirst(str, old);
        }

        ret.append(strc.extract(old, index + 1));
        return ret;
    }

    List<String> String::explode(const char* str) const
    {

        return explode(String(str));
    }

    int String::toInt(const String& str)
    {
        int x;
        sscanf(str.toCstChar(), "%i", &x);
        return x;
    }

    String String::operator+(const String& other) const
    {

        String ret(*this);
        ret.append(other);
        return ret;
    }

    String String::operator+(const char* other) const
    {

        String ret(*this);
        ret.append(other);
        return ret;
    }

    String String::operator+(const Number& nb) const
    {

        String ret(*this);
        ret << nb;
        return ret;
    }

    String String::toUpper(const String& other)
    {
        String result;

        for(unsigned int i = 0; i < other.size(); ++i)
            result.append(toUpper(other.at(i)));

        return result;
    }

    String String::toLower(const String& other)
    {
        String result;

        for(unsigned int i = 0; i < other.size(); ++i)
            result.append(toLower(other.at(i)));

        return result;
    }

    char String::toUpper(char c)
    {
        if(c <= 122 && c >= 97)
            c -= 32;
        return c;
    }

    char String::toLower(char c)
    {
        if(c >= 65 && c <= 90)
            c += 32;
        return c;
    }

    double String::toDouble(const String& str)
    {
        if(str.isEmpty()) return 0;
        return atof(str.toCstChar());
    }

    String String::fromDouble(double d)
    {
        char buffer[100];
        String ret;

        sprintf(buffer, "%.9lf", d);
        ret.append(buffer);

        return ret;
    }

    HashType String::hash() const
    {
        // From : http://stackoverflow.com/questions/8094790/how-to-get-hash-code-of-a-string-in-c
        HashType h = 0;
        for(size_t i = 0; i < size(); ++i)
        {
            h = 65599 * h + at(i);
        }

        return h ^ (h << 16);
    }

    HashType String::Hash(const char* str)
    {
        // From : http://stackoverflow.com/questions/8094790/how-to-get-hash-code-of-a-string-in-c
        // Modified to fit in this context.
        HashType h = 0;
        for(char* i = str; i != nullptr && (*i) != '\0'; i++)
        {
            h = 65599 * h + (*i);
        }

        return h ^ (h << 16);
    }

    int String::Size(const char* str)
    {
        return strlen(str);
    }
}
