/** @file Exception.cpp
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 21/05/2012 - 26/05/2012
 *
 *  @addtogroup Global
 *  @addtogroup Memory
 *
 *  This file implements the basics Exceptions used in the engine.
 *
**/
#include "Exception.h"

#if APRO_EXCEPTION == APRO_ON

#include <sstream>

namespace APro
{
    Exception::Exception(const char* _type, const char* msg, const char* _class, const char* _func, int _line)
        : type(_type), message(msg), class_(_class), func_(_func), line(_line)
    {

    }

    Exception::Exception(const Exception& e)
        : type(e.type), message(e.message), class_(e.class_), func_(e.func_), line(e.line)
    {

    }

    Exception::~Exception()
    {

    }

    const std::string & Exception::getType() const
    {
        return type;
    }

    const std::string & Exception::getMessage() const
    {
        return message;
    }

    const std::string & Exception::getClass() const
    {
        return class_;
    }

    const std::string & Exception::getFunction() const
    {
        return func_;
    }

    int Exception::getLine() const
    {
        return line;
    }

    std::string Exception::getFullDescription() const
    {
        if(!isNull())
        {
            std::stringstream stream;
            stream << "[" << type << "] : " << message << " Thrown at line " << line << " in function " << func_ << " from class " << class_ << ".";

            return stream.str().c_str();
        }

        else
        {
            return "";
        }
    }

    bool Exception::isNull() const
    {
        return type.empty() || message.empty() || class_.empty() || func_.empty();
    }
}

#endif
