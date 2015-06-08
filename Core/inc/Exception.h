////////////////////////////////////////////////////////////
/** @file Exception.h
 *  @ingroup Core
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 21/05/2012 - 05/06/2015
 *
 *  Defines the basics Exceptions used in the engine.
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
#ifndef APROEXCEPTION_H
#define APROEXCEPTION_H

#include "Base.h"

#if APRO_EXCEPTION == APRO_ON

#include <exception>

namespace APro
{
    ////////////////////////////////////////////////////////////
    /** @class Exception
     *  @ingroup Core
     *  @brief Defines an interface for every Exception in the 
     *  Engine.
     *
     *  An Exception is described by the following protocole : 
     *  - The what() function return the throwing function with
     *  complementary data (depending on the Exception).
     *  - An Exception object should always provide file, function
     *  and line from the throwing point, but it is not guaranteed.
     *  In the case of an Exception subclass may not fill those
     *  values, they may not be provided.
     *  - Other functions are specific to an Exception object.
    **/
    ////////////////////////////////////////////////////////////
    class Exception : public std::exception
    {
    private:
        std::string m_what;
	public:
		typedef struct {
			std::string file;
			std::string func;
			long 		line;
		} ThrowInfo;
		
		ThrowInfo m_info;

    public:
        Exception() throw() 
        {
        	m_info.file = "Unknown";
        	m_info.func = "Unknown";
        	m_info.line = 0;
        }
        
        Exception(long l, const char* fi, const char* fu) 
        {
        	m_info.file = std::string(fi);
        	m_info.func = std::string(fu);
        	m_info.line = l;
        }
        
        Exception(const Exception& other) throw() 
			: m_info(other.m_info)
        {  
        	
        }
        
        Exception& operator = (const Exception& rhs) throw() 
        { 
        	m_info.file = rhs.m_info.file;
        	m_info.func = rhs.m_info.func;
			m_info.line = rhs.m_info.line;
        	
        	return *this; 
		}
		
        virtual ~Exception() throw() {}

        long getLine() const throw() { return m_info.line; }
        const char* getFile() const throw() { return m_info.file.c_str(); }
        const char* getFunction() const throw() { return m_info.func.c_str(); }

        ////////////////////////////////////////////////////////////
        /** @brief Return the description of this exception.
        **/
        ////////////////////////////////////////////////////////////
        virtual const char* what() const throw() = 0;

    };

    /** @def APRO_MAKE_EXCEPTION(class)
     *
     *  Make the exception constructor for a given class. Use it to create your
     *  own exceptions.
    **/
    #define APRO_MAKE_EXCEPTION(class) public: class(long l, const char* fi, const char* fu) : Exception(l,fi,fu) { }

    /** Throw a simple exception. */
    #define aprothrow(Except) throw Except (__LINE__, __FILE__, __FUNCTION__)

    /** Throw a Custom exception. Use this function to easily throw an exception with a message. */
    #define aprothrow_ce(msg) throw CustomException(msg, __LINE__, __FILE__, __FUNCTION__)
}

#else

#define aprothrow
#define aprothrow_ce
#define APRO_MAKE_EXCEPTION

namespace APro
{
    class Exception
    {
    public:
        Exception() {}
        ~Exception() {}
    };
}

#endif

namespace APro
{
    ////////////////////////////////////////////////////////////
    /** @class FatalException
     *  @ingroup Core
     *  @brief A Fatal Error exception.
     *
     *  It can be launched if a very rare error is encountered,
     *  without needing some special description.
    **/
    ////////////////////////////////////////////////////////////
    class FatalException : public Exception
    {
        APRO_MAKE_EXCEPTION(FatalException)

        const char* what() const throw() { return "A fatal error has been thrown. See the program's provider for more support."; }
    };

    ////////////////////////////////////////////////////////////
    /** @class CustomException
     *  @ingroup Core
     *  @brief A Custom Error exception.
     *
     *  Can be used to launch an error without creating a new class
     *  if we just want to draw a message.
    **/
    ////////////////////////////////////////////////////////////
    class CustomException : public Exception
    {
    public:

        CustomException(const char* msg, long l, const char* fi, const char* fu);

        const char* what() const throw() { return buffer; }

    private:

        char buffer[512];
    };
}

#endif
