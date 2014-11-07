/////////////////////////////////////////////////////////////
/** @file FileStream.cpp
 *  @ingroup Utils
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 03/02/2013 - 07/04/2014
 *
 *  Implements the FileStream class.
 *
**/
/////////////////////////////////////////////////////////////
#include "FileStream.h"

namespace APro
{
    FileStream::FileStream()
        : m_file(nullptr)
    {

    }

    FileStream::FileStream(FileStream& f_stream)
        : m_file(nullptr)
    {
        if(!f_stream.m_file.isNull() && f_stream.m_file->isOpened())
            m_file = f_stream.m_file;
    }

    FileStream::FileStream(File& f)
        : m_file(nullptr)
    {
        if(f.isOpened())
            m_file = std::move(FilePtr(&f, nullptr, true, nullptr));
    }

    FileStream::~FileStream()
    {
        // We do nothing as file object musn't be closed.
    }

    bool FileStream::set(File& f)
    {
        if(f.isOpened())
        {
            m_file = std::move(FilePtr(&f, nullptr, true, nullptr));
            return true;
        }

        return false;
    }

    bool FileStream::set(FileStream& other)
    {
        if(!other.m_file.isNull() && other.m_file->isOpened())
        {
            m_file = other.m_file;
            return true;
        }

        return false;
    }

    const FilePtr& FileStream::toFilePtr() const
    {
        return m_file;
    }

    FilePtr& FileStream::toFilePtr()
    {
        return m_file;
    }

    bool FileStream::readChar(char& to)
    {
        if(m_file.isNull() || !m_file->isOpened())
        {
            return false;
        }
        else
        {
            return m_file->read(&to, sizeof(char));
        }
    }

    bool FileStream::readWord(String& str)
    {
        char c;
        if(m_file.isNull() || !m_file->isOpened())
            return false;

        if(skipBlanck(c) < 0)
            return false;

        while(isalpha((int) c))
        {
            str.append(c);
            if(!readChar(c))
                break;
        }

        return true;
    }

    bool FileStream::readUntill(String& str, ByteArray clist)
    {
        char c;
        if(m_file.isNull() || !m_file->isOpened())
            return false;

        if(!readChar(c))
            return false;

        while(!clist.contains((Byte) c))
        {
            str.append(c);
            if(!readChar(c))
                break;
        }

        return true;
    }

    bool FileStream::readReal(Real& r)
    {
        char c;
        if(m_file.isNull() || !m_file->isOpened())
            return false;

        ByteArray authorized_characters;
        authorized_characters << (Byte) '+' << (Byte) '-' << (Byte) '.' << (Byte) 'e' << (Byte) 'E';

        String real;
        if(skipBlanck(c) < 0)
            return false;

        while(isdigit(c) || authorized_characters.contains(c))
        {
            real.append(c);
            if(!readChar(c))
                break;
        }

        r = real.toReal();
        return true;
    }

    bool FileStream::readInt(int& i)
    {
        char c;
        if(m_file.isNull() || !m_file->isOpened())
            return false;

        String real;
        if(skipBlanck(c) < 0)
            return false;

        while(isdigit(c))
        {
            real.append(c);
            if(!readChar(c))
                break;
        }

        i = real.toInt();
        return true;
    }
    
    bool FileStream::readUTF8Char(UTF8Char::CodePoint& ret)
    {
        if(m_file.isNull())
            return false;
        if(!m_file->hasUTF8BOM()) {
            aprodebug("Reading UTF8 from file '") << m_file->getFileName() << "' wich does not have correct UTF8 mode.\n";
            return false;
        }
        
        // Preparing octets
        UTF8Char::Octet octets [4] = { 0x00, 0x00, 0x00, 0x00 };
        
        // Read Octet 1
        if(!m_file->read((Byte*)&octets[0], 1)) {
            aprodebug("Can't read UTF8 Octet1 from file '") << m_file->getFileName() << "'.\n";
            return false;
        }
        
        // Checking Octet
        if(!UTF8Char::OctetType(octets[0]) != UTF8Char::TBegin) {
            aprodebug("Invalid UTF8 Octet1 from file '") << m_file->getFileName() << "'.\n";
            return false;
        }
        
        int numoctet = UTF8Char::GetOctetNumber(octets[0]);
        
        // Read Octet 2
        if(numoctet > 1)
        {
            if(!m_file->read((Byte*)&octets[1], 1)) {
                aprodebug("Can't read UTF8 Octet2 from file '") << m_file->getFileName() << "'.\n";
                return false;
            }
        }
        
        // Read Octet 3
        if(numoctet > 2)
        {
            if(!m_file->read((Byte*)&octets[2], 1)) {
                aprodebug("Can't read UTF8 Octet3 from file '") << m_file->getFileName() << "'.\n";
                return false;
            }
        }
        
        // Read Octet 4
        if(numoctet > 3)
        {
            if(!m_file->read((Byte*)&octets[3], 1)) {
                aprodebug("Can't read UTF8 Octet4 from file '") << m_file->getFileName() << "'.\n";
                return false;
            }
        }
        
        // Compute the codepoint
        ret = UTF8Char::ExtractUTF8CodePoint(octets[0], octets[1], octets[2], octets[3]);
        return true;
    }
    
    bool FileStream::readUTF8Word(UTF8String& str, size_t maxsz)
    {
        if(m_file.isNull())
            return false;
        if(!m_file->hasUTF8BOM()) {
            aprodebug("Reading UTF8 from file '") << m_file->getFileName() << "' wich does not have correct UTF8 mode.\n";
            return false;
        }
        
        if(!str.isEmpty()) {
            aprodebug("Reading UTF8 Word to string wich is not empty.");
            return false;
        }
        
        UTF8Char::CodePoint cp = UTF8CHar::CPNull;
        
        if(!readUTF8Char(cp)) {
            return false;
        }
        
        while (cp != UTF8Char::CPNull &&
               !UTF8Char::IsSpace(cp))
        {
            str.append(cp);
            readUTF8Char(cp);
        }
        
        return true;
    }

    int FileStream::skipBlanck(char& c)
    {
        if(m_file.isNull() || !m_file->isOpened())
            return -1;

        int ret = 0;
        if(!readChar(c))
            return -1;
        while(isblank(c))
        {
            if(!readChar(c))
                return ret;
            ret++;
        }
        return ret;
    }

    bool FileStream::write(const String& str)
    {
        if(m_file.isNull() || !m_file->isOpened())
            return false;

        return m_file->write(str.toCstChar(), str.size());
    }

    bool FileStream::write(const Real& str)
    {
        if(m_file.isNull() || !m_file->isOpened())
            return false;

        return write(String::toString(str));
    }

    bool FileStream::write(const int& str)
    {
        if(m_file.isNull() || !m_file->isOpened())
            return false;

        return write(String::toString(str));
    }
    
    bool FileStream::write(const UTF8Char::CodePoint& cp)
    {
        if(m_file.isNull() || !m_file->isOpened())
            return false;
        
        // Prepare the char.
        char cptoc [4] = { 0, 0, 0, 0 };
        int vcu = UTF8Char::toChar (&cptoc[0], cp);
        if (vcu < 1)
            return false;
        
        // Write the current used char.
        return m_file->write ((const char*) cptoc, vcu);
    }
    
    bool FileStream::write(const UTF8String& str)
    {
        if(m_file.isNull() || !m_file->isOpened())
            return false;
        
        for(UTF8String::const_iterator it = str.begin(); it != str.end(); it++) {
            if(!write(*it))
                return false;
        }
        
        return true;
    }

    bool FileStream::isEOS() const
    {
        if(m_file.isNull())
            return false;
        return m_file->isEOF();
    }

    size_t FileStream::tell() const
    {
        if(m_file.isNull())
            return 0;
        return m_file->tell();
    }

    void FileStream::seek(size_t pos, CursorPosition cp)
    {
        if(m_file.isNull())
            return;
        m_file->seek(File::C_BEGIN + (int) cp, (Offset) pos);
    }

}
