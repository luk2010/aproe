////////////////////////////////////////////////////////////
/** @file Exception.h
 *  @ingroup Core
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 21/05/2012 - 30/08/2013
 *
 *  Defines the basics Exceptions used in the engine.
 *
**/
////////////////////////////////////////////////////////////
#ifndef APROEXCEPTION_H
#define APROEXCEPTION_H

#include "Platform.h"

#if APRO_EXCEPTION == APRO_ON

#include <exception>

namespace APro
{
    ////////////////////////////////////////////////////////////
    /** @class Exception
     *  @ingroup Core
     *  @brief A standard Exception class with line, file and
     *  function management.
     *
     *  Overwrite this class to create your own exceptions, as in
     *  the FatalException example. The Exception stores always
     *  the line of the error, thhe file and the function where
     *  it has been thrown.
    **/
    ////////////////////////////////////////////////////////////
    class Exception : public std::exception
    {
    private:
        long        line;///< Line where the exception has been thrown.
        const char* file;///< File where the exception has been thrown.
        const char* func;///< Function where the exception has been thrown.

    public:
        Exception(long l, const char* fi, const char* fu) : line(l), file(fi), func(fu) {}
        virtual ~Exception() throw() {}

        long getLine() const throw() { return line; }
        const char* getFile() const throw() { return file; }
        const char* getFunction() const throw() { return func; }

        ////////////////////////////////////////////////////////////
        /** @brief Return the description of this exception.
        **/
        ////////////////////////////////////////////////////////////
        virtual const char* what() const throw() { return "Unkown."; }

    };

    /** @def APRO_MAKE_EXCEPTION(class)
     *
     *  Make the exception constructor for a given class. Use it to create your
     *  own exceptions.
    **/
    #define APRO_MAKE_EXCEPTION(class) public: class(long l, const char* fi, const char* fu) : Exception(l,fi,fu) { }

    /** Throw a simple exception. */
    #define aprothrow(Except) throw Except (__LINE__, __FILE__, __FUNCTION__)

    /** Throw a Custom exception. */
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
