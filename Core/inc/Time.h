////////////////////////////////////////////////////////////
/** @file Time.h
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
#ifndef APRO_TIME_H
#define APRO_TIME_H

#include "Platform.h"

namespace APro
{
    ////////////////////////////////////////////////////////////
    /** @class Time
     *  @ingroup Utils
     *  @brief A Time basic class holding Hours to microseconds.
    **/
    ////////////////////////////////////////////////////////////
    class Time
    {
    protected:

        int m_hour;
        int m_min;
        int m_sec;
        int m_milli;
        int m_micro;

    public:

        /** @brief Flags describing each part. */
        enum TimePart
        {
            TP_NULL    = 0x00,
            TP_HOUR    = 0x01,
            TP_MINUTES = 0x02,
            TP_SECONDS = 0x04,
            TP_MILLI   = 0x08,
            TP_MICRO   = 0x10,
            TP_ALL     = 0xFF
        };

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Constructs the Time object.
        **/
        ////////////////////////////////////////////////////////////
        Time(int hour, int minutes, int seconds, int milliseconds = 0, int microseconds = 0);

        ////////////////////////////////////////////////////////////
        /** @brief Constructs the Time object from another one.
        **/
        ////////////////////////////////////////////////////////////
        Time(const Time& other);

        ////////////////////////////////////////////////////////////
        /** @brief Destructs the Time object.
        **/
        ////////////////////////////////////////////////////////////
        ~Time();

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Returns Hour holded in this object.
        **/
        ////////////////////////////////////////////////////////////
        int getHours() const;

        ////////////////////////////////////////////////////////////
        /** @brief Returns Minutes holded in this object.
        **/
        ////////////////////////////////////////////////////////////
        int getMinutes() const;

        ////////////////////////////////////////////////////////////
        /** @brief Returns Seconds holded in this object.
        **/
        ////////////////////////////////////////////////////////////
        int getSeconds() const;

        ////////////////////////////////////////////////////////////
        /** @brief Returns secs + minutes*60 + hours*3600 .
        **/
        ////////////////////////////////////////////////////////////
        int toSeconds() const;

        ////////////////////////////////////////////////////////////
        /** @brief Returns Milliseconds holded in this object.
        **/
        ////////////////////////////////////////////////////////////
        int getMilliseconds() const;

        ////////////////////////////////////////////////////////////
        /** @brief Returns Microseconds holded in this object.
        **/
        ////////////////////////////////////////////////////////////
        int getMicroseconds() const;

        ////////////////////////////////////////////////////////////
        /** @brief Returns Microseconds * 1000 + milliseconds.
        **/
        ////////////////////////////////////////////////////////////
        int getAfterSecondsPart() const;

        ////////////////////////////////////////////////////////////
        /** @brief Returns in seconds every parts of the Time object.
        **/
        ////////////////////////////////////////////////////////////
        float getTotal() const;

        ////////////////////////////////////////////////////////////
        /** @brief Set every parts from the total in seconds.
        **/
        ////////////////////////////////////////////////////////////
        void fromTotal(float total);

        static Time FromTotal(float total);

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Change given parts to given int.
        **/
        ////////////////////////////////////////////////////////////
        void changeParts(int parts, ...);

        ////////////////////////////////////////////////////////////
        /** @brief Prints given parts.
        **/
        ////////////////////////////////////////////////////////////
        String printParts(int parts = TP_ALL);

    public:

        Time& operator + (const Time& other);
        Time& operator - (const Time& other);
        Time& operator = (const Time& other);

    public:

        bool operator == (const Time& other) const;
        bool operator != (const Time& other) const;

    public:

        static Time& GetCurrentTime(int parts);
        static Time Invalid;
    };
}

#endif // APRO_TIME_H
