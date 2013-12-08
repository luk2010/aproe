/////////////////////////////////////////////////////////////
/** @file IdGenerator.h
 *  @ingroup Utils
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 03/07/2013
 *
 *  Defines the IdGenerator class.
 *
 **/
/////////////////////////////////////////////////////////////
#ifndef APRO_IDGENERATOR_H
#define APRO_IDGENERATOR_H

#include "Platform.h"
#include "ThreadSafe.h"

namespace APro
{
    /////////////////////////////////////////////////////////////
    /** @class IdGenerator
     *  @ingroup Utils
     *  @brief Generate an id in given incrementation from setted
     *  base.
     *
     *  By default, the base is 0 and the incrementation is 1 but
     *  you can set it to anything you want.
     *
     *  You should reset the id generator after setting the base
     *  of the generator, but you don't have to do it if you only
     *  change the incrementation tick.
     *
     *  @note You can set a maximum id returned by this generator.
     *  When this is used, you should use the IdGenerator::canPick
     *  function to know if new ids are available.
     *
     *  @note If Max is 0, infinite limit.
     *
     *  This class is thread-safe.
    **/
    /////////////////////////////////////////////////////////////
    class APRO_DLL IdGenerator : public ThreadSafe
    {

        APRO_DECLARE_MANUALSINGLETON(IdGenerator)

    private:

        unsigned long m_cur_id;///< Current id that will be given to next call.

        unsigned long m_incrementation;///< Current incrementation tick.
        unsigned long m_base;///< Base of the generator.
        unsigned long m_max;///< Possible maximum id available.

    public:

        /////////////////////////////////////////////////////////////
        /** @brief Constructor.
        **/
        /////////////////////////////////////////////////////////////
        IdGenerator();

        /////////////////////////////////////////////////////////////
        /** @brief Destructor.
        **/
        /////////////////////////////////////////////////////////////
        ~IdGenerator();

    public:

        /////////////////////////////////////////////////////////////
        /** @brief Reset the incrementation of this generator.
        **/
        /////////////////////////////////////////////////////////////
        void reset();

        /////////////////////////////////////////////////////////////
        /** @brief Set the base to given.
        **/
        /////////////////////////////////////////////////////////////
        void setBase(unsigned long base);

        /////////////////////////////////////////////////////////////
        /** @brief Set to given incrementation tick.
        **/
        /////////////////////////////////////////////////////////////
        void setIncrementation(unsigned long increment);

        /////////////////////////////////////////////////////////////
        /** @brief Set new maximum id limit.
        **/
        /////////////////////////////////////////////////////////////
        void setMaximumId(unsigned long max);

        /////////////////////////////////////////////////////////////
        /** @brief Return the next id available.
         *
         *  @throw MaxRangeReached if maximum id is reached.
        **/
        /////////////////////////////////////////////////////////////
        unsigned long pick();

        /////////////////////////////////////////////////////////////
        /** @brief Tell if next id will be valid.
         **/
        /////////////////////////////////////////////////////////////
        bool canPick() const;
    };

    typedef unsigned long Id; ///< A generic id type.
}

#endif // APRO_IDGENERATOR_H
