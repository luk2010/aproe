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
#ifndef APROFILE_H
#define APROFILE_H

#include "Platform.h"
#include "Resource.h"
#include "Array.h"
#include "SString.h"

namespace APro
{
    class APRO_DLL File : public Resource
    {
    public:

        class Position
        {
        public:
            enum _
            {
                Begin,
                End,
                Current
            };
        };

        class OpenMode
        {
        public:
            enum _
            {
                ReadOnly,
                WriteOnly,
                ReadWrite
            };
        };

    public:

        File();
        File(const String& name_, const String& filename_, OpenMode::_ om);
        File(const String& name_, const String& filename_, const String& data_, OpenMode::_ om);

        ~File();

        void put(char c);
        void put(const char* m);
        void put(const String& str);

        void pop(size_t nbr = 1, Position::_ from = Position::Current);

        char get();
        String getLine();
        String get(const String& separator);

        void seek(int to, Position::_ from);

        size_t size() const;
        void clear();

        const Array<char>& getData() const;
        const String& toString() const;

        bool isEOF() const;

        File& operator >> (String& str);
        File& operator >> (char& c);
        File& operator >> (int& i);
        File& operator >> (double& d);

        void destroy();

    private:

        void pushIndex();

    private:

        String data;
        int currentIndex;
        OpenMode::_ openMode;
    };
}

#endif
