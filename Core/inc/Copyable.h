/////////////////////////////////////////////////////////////
/** @file Copyable.h
 *  @ingroup Utils
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 25/05/2013
 *
 *  Defines an interface for copyable objects.
 *
**/
/////////////////////////////////////////////////////////////
#ifndef APRO_COPYABLE_H
#define APRO_COPYABLE_H

#include "Platform.h"

namespace APro
{
    /////////////////////////////////////////////////////////////
    /** @class Copyable
     *  @ingroup utils
     *  @brief Describes a Copyable class.
     *  @details Inherits from this class if you want yours to
     *  be correctly copyable. You will have to implements the pure
     *  functions.
    **/
    /////////////////////////////////////////////////////////////
    template <typename ClassType>
    class Copyable
    {
    public:

        /////////////////////////////////////////////////////////////
        /** @brief Destructor
        **/
        /////////////////////////////////////////////////////////////
        virtual ~Copyable()
        {

        }

        /////////////////////////////////////////////////////////////
        /** @brief Copy this object from another object of same kind.
         *  @param other : Object to copy.
        **/
        /////////////////////////////////////////////////////////////
        virtual void copyFrom(const ClassType& other) = 0;

        /////////////////////////////////////////////////////////////
        /** @brief Copy this object in a given one.
         *  @param other : Object to copy to.
        **/
        /////////////////////////////////////////////////////////////
        void copyTo(ClassType& other)
        {
            other.copyFrom(*this);
        }

        /////////////////////////////////////////////////////////////
        /** @brief Assignment operator.
        **/
        /////////////////////////////////////////////////////////////
        ClassType& operator = (const ClassType& other)
        {
            copyFrom(other);
            return *this;
        }

        /////////////////////////////////////////////////////////////
        /** @brief Egality operator.
        **/
        /////////////////////////////////////////////////////////////
        virtual bool operator == (const ClassType& other) const = 0;

        /////////////////////////////////////////////////////////////
        /** @brief Inegality operator.
        **/
        /////////////////////////////////////////////////////////////
        bool operator != (const ClassType& other) const
        {
            return !(*this == other);
        }
    };
}

#endif // APRO_COPYABLE_H
