/////////////////////////////////////////////////////////////
/** @file IdGenerator.cpp
 *  @ingroup Utils
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 03/07/2013 - 03/04/2014
 *
 *  Defines the IdGenerator class.
 *
 **/
/////////////////////////////////////////////////////////////
#include <IdGenerator.h>

namespace APro
{
    APRO_IMPLEMENT_MANUALSINGLETON(IdGenerator)

    IdGenerator::IdGenerator()
    {
        m_cur_id         = 0;
        m_incrementation = 1;
        m_base           = 0;
        m_max            = 0;
    }

    IdGenerator::~IdGenerator()
    {

    }

    void IdGenerator::reset()
    {
        APRO_THREADSAFE_AUTOLOCK
        m_cur_id = m_base;
    }

    void IdGenerator::setBase(unsigned long base)
    {
        APRO_THREADSAFE_AUTOLOCK
        m_base = base;
        if(m_cur_id < m_base)
            reset();
    }

    void IdGenerator::setIncrementation(unsigned long increment)
    {
        APRO_THREADSAFE_AUTOLOCK
        m_incrementation = increment;
    }

    void IdGenerator::setMaximumId(unsigned long max)
    {
        APRO_THREADSAFE_AUTOLOCK
        m_max = max;
    }

    unsigned long IdGenerator::pick()
    {
        APRO_THREADSAFE_AUTOLOCK
        unsigned long ret = m_cur_id;
        if(ret + m_incrementation > m_max)
        {
            APRO_THROW("MaxRangeReached", "Max range for id reached !", "IdGenerator");
        }

        m_cur_id += m_incrementation;
        return ret;
    }

    void IdGenerator::unpick()
    {
        APRO_THREADSAFE_AUTOLOCK
        m_cur_id -= m_incrementation;
    }

    bool IdGenerator::canPick() const
    {
        APRO_THREADSAFE_AUTOLOCK
        return m_cur_id >= m_max;
    }
}
