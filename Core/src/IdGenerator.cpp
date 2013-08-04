/////////////////////////////////////////////////////////////
/** @file IdGenerator.cpp
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
#include <IdGenerator.h>

namespace APro
{
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
        m_cur_id = m_base;
    }
    
    void IdGenerator::setBase(unsigned long base)
    {
        m_base = base;
        if(m_cur_id < m_base)
            reset();
    }
    
    void IdGenerator::setIncrementation(unsigned long increment)
    {
        m_incrementation = increment;
    }
    
    void IdGenerator::setMaximumId(unsigned long max)
    {
        m_max = max;
    }
    
    unsigned long IdGenerator::pick()
    {
        unsigned long ret = m_cur_id;
        if(ret + 1 > m_max)
        {
            APRO_THROW("MaxRangeReached", "Max range for id reached !", "IdGenerator");
        }
        
        m_cur_id += 1;
        return ret;
    }
    
    bool IdGenerator::canPick() const
    {
        return m_cur_id >= m_max;
    }
}