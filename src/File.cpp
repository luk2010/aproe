/** @file File.h
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 30/08/2012
 *
 *  @addtogroup Global
 *  @addtogroup Resource
 *
 *  This file defines the File resource.
 *
**/
#include "File.h"

namespace APro
{
    File::File() : Resource(), data(), currentIndex(0), openMode(OpenMode::ReadWrite)
    {
        type = "File";
    }

    File::File(const String& name_, const String& filename_, OpenMode::_ om)
        : Resource(name_, filename_), data(), currentIndex(0), openMode(om)
    {
        type = "File";
    }

    File::File(const String& name_, const String& filename_, const String& data_, OpenMode::_ om)
        : Resource(name_, filename_), data(data_), currentIndex(0), openMode(om)
    {
        type = "File";
    }

    File::~File()
    {

    }

    void File::destroy()
    {

    }

    void File::put(char c)
    {
        if(openMode != OpenMode::ReadOnly)
        {
            data.insert(currentIndex, c);
            pushIndex();
        }
    }

    void File::put(const char* m)
    {
        put(String(m));
    }

    void File::put(const String& str)
    {
        data.insert(currentIndex, str);
        if(!isEOF()) currentIndex += str.size();
    }

    void File::pop(size_t nbr, Position::_ from)
    {
        seek(0, from);
        data.erase(currentIndex, currentIndex + nbr - 1);
    }

    char File::get()
    {
        char ret = data.at(currentIndex);
        pushIndex();

        return ret;
    }

    String File::getLine()
    {
        return get(String("\n"));
    }

    String File::get(const String& separator)
    {
        if(isEOF())
            return String();

        String ret;
        String sep;
        while(sep != separator && !isEOF())
        {
            char ap = data.at(currentIndex);
            sep = data.extract(currentIndex + 1, currentIndex + 1 + separator.size());
            ret.append(ap);
            pushIndex();
        }

        return ret;
    }

    void File::seek(int to, Position::_ from)
    {
        if(to == 0 && from == Position::Current)
            return;

        if(to >= (int) size()) to = (int) size() - 1;

        switch (from)
        {
        case Position::Begin:
            currentIndex = 0 + to;
        case Position::End:
            currentIndex = data.size() + to;
        case Position::Current:
        default:
            currentIndex = currentIndex + to;
        }
    }

    size_t File::size() const
    {
        return data.size() + 1;
    }

    void File::clear()
    {
        data.clear();
    }

    const Array<char>& File::getData() const
    {
        return data.toCstArray();
    }

    const String& File::toString() const
    {
        return data;
    }

    bool File::isEOF() const
    {
        return data.toCstArray().at(currentIndex) == '\0';
    }

    void File::pushIndex()
    {
        if(!isEOF()) currentIndex++;
    }

    File& File::operator >> (String& str)
    {
        str = get(String(" "));
        return *this;
    }

    File& File::operator >> (char& c)
    {
        c = get();
        return *this;
    }

    File& File::operator >> (int& i)
    {
        const char* d = data.toCstChar();
        i = *((int*) d[currentIndex]);

        if(currentIndex + sizeof(int) < data.size())
            currentIndex += sizeof(int);
        else
            currentIndex = data.size();
        return *this;
    }

    File& File::operator >> (double& d)
    {
        const char* e = data.toCstChar();
        d = *((double*) e[currentIndex]);

        if(currentIndex + sizeof(double) < data.size())
            currentIndex += sizeof(double);
        else
            currentIndex = data.size();
        return *this;
    }
}
