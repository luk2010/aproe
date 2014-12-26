////////////////////////////////////////////////////////////
/** @file Time.cpp
 *  @ingroup Utils
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 25/04/2014 - 02/05/2014
 *
 *  Defines the Time class.
 *
**/
////////////////////////////////////////////////////////////
#include "Time.h"
#include <cstdarg>
#include <ctime>

namespace APro
{
    Time::Time(int hour, int minutes, int seconds, int milliseconds, int microseconds)
    {
        m_hour  = hour;
        m_min   = minutes;
        m_sec   = seconds;
        m_milli = milliseconds;
        m_micro = microseconds;
    }

    Time::Time(const Time& other)
    {
        m_hour  = other.m_hour;
        m_min   = other.m_min;
        m_sec   = other.m_sec;
        m_milli = other.m_milli;
        m_micro = other.m_micro;
    }

    Time::~Time()
    {

    }

    int Time::getHours() const
    {
        return m_hour;
    }

    int Time::getMinutes() const
    {
        return m_min;
    }

    int Time::getSeconds() const
    {
        return m_sec;
    }

    int Time::toSeconds() const
    {
        return m_sec + m_min * 60 + m_hour * 3600;
    }

    int Time::getMilliseconds() const
    {
        return m_milli;
    }

    int Time::getMicroseconds() const
    {
        return m_micro;
    }

    int Time::getAfterSecondsPart() const
    {
        return m_milli + m_micro * 1000;
    }

    void Time::changeParts(int parts, ...)
    {
        va_list arguments;
        va_start(arguments, parts);

        if(parts & TP_HOUR)    m_hour  = va_arg(arguments, int);
        if(parts & TP_MINUTES) m_min   = va_arg(arguments, int);
        if(parts & TP_SECONDS) m_sec   = va_arg(arguments, int);
        if(parts & TP_MILLI)   m_milli = va_arg(arguments, int);
        if(parts & TP_MICRO)   m_micro = va_arg(arguments, int);

        va_end(arguments);
    }

    String Time::printParts(int parts)
    {
        String result("");
        result << "Time( | ";

        if(parts & TP_HOUR)    result << "H='" << String::toString(m_hour)   << "' | ";
        if(parts & TP_MINUTES) result << "M='" << String::toString(m_min)    << "' | ";
        if(parts & TP_SECONDS) result << "S='" << String::toString(m_sec)    << "' | ";
        if(parts & TP_MILLI)   result << "m='" << String::toString(m_milli)  << "' | ";
        if(parts & TP_MICRO)   result << "u='" << String::toString(m_micro)  << "' | ";

        result << ")";
        return String;
    }

    float Time::getTotal() const
    {
        return m_hour * 3600 + m_min * 60 + m_sec + m_milli / 1000 + m_micro / 1000000;
    }

    void Time::fromTotal(float total)
    {
        if(total < 0)
            *this = Time::Invalid;

        m_hour = (int) total / 3600;
        total -= m_hour * 3600;

        m_min = (int) total / 60;
        total -= m_min * 60;

        m_sec = (int) total;
        total -= m_sec;

        total *= 1000;
        m_milli = (int) total;
        total -= m_milli;
        total *= 1000;
        m_micro = (int) total;
    }

    Time& Time::operator + (const Time& other)
    {
        fromTotal(getTotal() + other.getTotal());
        return *this;
    }

    Time& Time::operator - (const Time& other)
    {
        fromTotal(getTotal() - other.getTotal());
        return *this;
    }

    Time& Time::operator = (const Time& other)
    {
        m_hour  = other.m_hour;
        m_min   = other.m_min;
        m_sec   = other.m_sec;
        m_milli = other.m_milli;
        m_micro = other.m_micro;
    }

    bool Time::operator == (const Time& other) const
    {
        return m_hour  == other.m_hour  &&
               m_min   == other.m_min   &&
               m_sec   == other.m_sec   &&
               m_milli == other.m_milli &&
               m_micro == other.m_micro;
    }

    bool Time::operator != (const Time& other) const
    {
        return !(*this == other);
    }

    Time& Time::GetCurrentTime(int parts)
    {
        // We get current time by calling the standard time methods.
        clock_t clocks = clock();
        return Time::FromTotal( ((float)clocks) / CLOCKS_PER_SEC );
    }

    Time Time::FromTotal(float total)
    {
        Time ret(Time::Invalid);
        ret.fromTotal(total);
        return ret;
    }

    Time Time::Invalid = Time(-1,-1,-1,-1,,-1);
}
