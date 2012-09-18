/** @file Exception.h
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 21/05/2012 - 24/05/2012
 *
 *  @addtogroup Global
 *  @addtogroup Memory
 *
 *  This file defines the basics Exceptions used in the engine.
 *
**/
#ifndef APROEXCEPTION_H
#define APROEXCEPTION_H

#include "Platform.h"

#if APRO_EXCEPTION == APRO_ON

#include <string>

namespace APro
{
    /** @class Exception
     *
     *  @addtogroup Global
     *  @addtogroup Exception
     *
     *  @version 0.1A
     *
     *  This class can be used to describe a simple Exception. It can be thrown using the macro APRO_THROW or using
     *  the throw function.
     *  You must initialize each component with the throw function, whereas you just have to set Type, Message and Class
     *  with the APRO_THROW macro.
     *
     *  @addtogroup Global
     *  @addtogroup Memory
     *
     *  @note
     *  This class isn't std-free, it use std::string.
     *
     *  @remarks
     *  Exceptions doesn't have any real "type" : these are just the "name" of the Exception. You are indeed able to throw
     *  any kind of exception. More, you can't throw data in subclasing the Exception class.
     *
     *  @remarks
     *  You can modify the getFullDescription function in subclassing this class.
     *
    **/
    class APRO_DLL Exception
    {
    public:

        /** Public constructor.
         *
         *  @param _type : Type of the Exception.
         *  @param msg : Description of the Exception.
         *  @param _class : Classe of the source.
         *  @param _func : Function of the source.
         *  @param _line : Line in the file.
         *
         *  @note
         *  most of the times, _func and _line are PreProcessor-processed.
        **/
        Exception(const char* _type, const char* msg, const char* _class, const char* _func, int _line);
        Exception(const Exception & e);
        virtual ~Exception();

        /** Return the type of the Exception. */
        const std::string & getType() const;
        /** Return the description of the Exception. */
        const std::string & getMessage() const;
        /** Return the class from where the exception was thrown. */
        const std::string & getClass() const;
        /** Return the function from where the exception was thrown. */
        const std::string & getFunction() const;
        /** Return the line in the file where the excpetion was thrown. */
        int getLine() const;

        /** Tell if some field is empty. */
        bool isNull() const;

        /** Return the Complete description of the Exception. */
        virtual std::string getFullDescription() const;

    protected:

        std::string type;
        std::string message;
        std::string class_;
        std::string func_;
        int         line;
    };

    /** Throw a simple exception. */
    #define APRO_THROW(type, msg, class) throw APro::Exception(type, msg, class, __FUNCTION__, __LINE__)

    /** Assert a simple condition. */
    #define APRO_ASSERT(condition, message, class)  \
    if(!condition)                                  \
    {                                               \
        APRO_THROW("Assertion", message, class);    \
    }
}

#else

#define APRO_THROW
#define APRO_ASSERT(a, b, c)

#endif

#endif
