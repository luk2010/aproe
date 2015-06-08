/////////////////////////////////////////////////////////////
/** @file CheckSumCRC16.h
 *  @ingroup Utils
 *  @brief Defines the CheckSumCRC16 class.
 *
 *  @author Luk2010
 *  @date 08/03/2015
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
**/
////////////////////////////////////////////////////////////
#ifndef APRO_CHECKSUMCRC16_H
#define APRO_CHECKSUMCRC16_H

#include "Platform.h"
#include "CheckSum.h"

namespace APro
{
    ////////////////////////////////////////////////////////////
    /** @class CheckSumCRC16
     *  @ingroup Utils
     *  @brief A software based implementation of CRC16 checksum.
     *
     *  @note
     *  You can set the "Fast" property to true if you want the 
     *  fast software algorithm. 
     *
     *  @see
     *  http://c.snippets.org/snip_lister.php?fname=crc_16f.c
    **/
    ////////////////////////////////////////////////////////////
    class CheckSumCRC16
    : public CheckSum
    {
    private:
        
        /** @brief Internal CRC data. **/
        typedef union {
            uint32_t value;
            
            struct {
                uint8_t head;
                uint16_t remainder;
                uint8_t tail;
            } part;
        } CRC16Data;
        
    public:
        
        CheckSumCRC16();
        
        Prototype* clone() const;
        
        CheckSumType generate(const void* data, uint32_t lenght);
        
        CompareResult compare(const CheckSumType first, const CheckSumType second) const;
        
    private:
        
        /** @brief Initialize the CRC16 data. **/
        void _initCRC16Data(CRC16Data& crcdata);
        
        /** @brief Compute the slow CRC16 algorithm for one byte. **/
        void _processCRC16Data(CRC16Data& crcdata, uint8_t value);
        
        /** @brief Compute the fast software algorithm for a byte array. **/
        CheckSumType _computeFast(const void* data, uint32_t lenght);
        
    private:
        
        static const int32_t CRC16_INITVALUE;
        static const int32_t CRC16_POLYNOMIAL;
        static const uint32_t CRCTAB[1<<8];
    };
}

#endif
