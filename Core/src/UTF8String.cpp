////////////////////////////////////////////////////////////
/** @file UTF8String.cpp
 *  @ingroup Global
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 04/11/2014 - 07/11/2014
 *
 *  Implements the UTF8String class.
 *
 **/
////////////////////////////////////////////////////////////

#include "UTF8String.h"
#include "Maths.h"

namespace APro
{
    const UTF8Char::CodePoint UTF8Char::CPInvalid = 0xFFFFFFFF;
    const UTF8Char::CodePoint UTF8Char::CPNull    = 0x00000000;
    const UTF8Char::BOM       UTF8Char::CPBOM     = { 0xEF, 0xBB, 0xBF };
    
    
    UTF8Char::Type UTF8Char::OctetType (UTF8Char::Octet cp)
    {
        if( (cp >= 0x00 && cp <= 0x7F) ||
            (cp >= 0xC2 && cp <= 0xF4) )
            return UTF8Char::TBegin;
        else if ( cp >= 0x80 && cp <= 0xBF )
            return UTF8Char::TContinued;
        else
            return UTF8Char::TInvalid;
    }
    
    UTF8Char::SequenceType UTF8CHar::Sequence (UTF8Char::Octet cp, UTF8Char::Octet prev)
    {
        if(cp >= 0x00 && cp <= 0x7F)
            return UTF8Char::STAscii;
        
        // First multibyte sequence
        else if(cp >= 0xC2 && cp <= 0xDF)
            return UTF8Char::STOctet1x;
        else if(cp >= 0xE0 && cp <= 0xEF)
            return UTF8Char::STOctet1xx;
        else if(cp >= 0xF0 && cp <= 0xF4)
            return UTF8Char::STOctet1xxx;
        
        // Other multibyte bytes (exceptions, must be treated
        // before other bytes.)
        else if(cp >= 0x80 && cp <= 0xBF)
        {
            else if(prev == 0xE0)
                if(cp >= 0xA0 && cp <= 0xBF)
                    return UTF8Char::STOctet2E0;
                else
                    return UTF8Char::OE2BAD;
            
            else if(prev == 0xED)
                if(cp >= 0x80 && cp <= 0x9F)
                    return UTF8Char::STOctet2ED;
                else
                    return UTF8Char::OE2BAD;
            
            else if(prev == 0xF0)
                if(cp >= 0x90 && cp <= 0xBF)
                    return UTF8Char::STOctet2F0;
                else
                    return UTF8Char::OE2BAD;
            
            else if(prev == 0xF4)
                if(cp >= 0x80 && cp <= 0x8F)
                    return UTF8Char::STOctet2F4;
                else
                    return UTF8Char::OE2BAD;
            
            else
                return UTF8Char::STOctetXNormal;
        }
        
        // Invalid handling
        else if(cp == 0xC0 || cp == 0xC1)
            return UTF8Char::OE1C0C1;
        
        else
            return UTF8Char::STInvalid;
    }
    
    UTF8Char::CodePoint UTF8Char::ExtractUTF8CodePoint(UTF8Char::Octet o1,
                                                       UTF8Char::Octet o2,
                                                       UTF8Char::Octet o3,
                                                       UTF8Char::Octet o4)
    {
        CodePoint result = UTF8Char::CPInvalid;
        
        if(Sequence(o1) == UTF8Char::STAscii)
            result = o1;
        
        else if( Sequence(o1) == UTF8Char::STOctet1x &&
                 IsSequenceContinuing ( Sequence(o2, o1) ) )
        {
            result  = ((CodePoint) (o1 & 0b00011111)) << 6;
            result |= ((CodePoint) (o2 & 0b00111111));
        }
        
        else if ( Sequence (o1) == UTF8Char::STOctet1xx &&
                  IsSequenceContinuing ( Sequence(o2, o1) ) &&
                  IsSequenceContinuing ( Sequence(o3, o2) ) )
        {
            result  = ((CodePoint) (o1 & 0b00001111)) << 12;
            result |= ((CodePoint) (o2 & 0b00111111)) << 6;
            result |= ((CodePoint) (o3 & 0b00111111));
        }
        
        else if ( Sequence (o1) == UTF8Char::STOctet1xx &&
                 IsSequenceContinuing ( Sequence(o2, o1) ) &&
                 IsSequenceContinuing ( Sequence(o3, o2) ) &&
                 IsSequenceContinuing ( Sequence(o4, o3) ) )
        {
            result  = ((CodePoint) (o1 & 0b00000111)) << 18;
            result |= ((CodePoint) (o2 & 0b00111111)) << 12;
            result |= ((CodePoint) (o3 & 0b00111111)) << 6;
            result |= ((CodePoint) (o4 & 0b00111111));
        }
        
        return result;
    }
    
    size_t UTF8Char::GetCodePointSegmentSize(CodePoint cp)
    {
        unsigned long int nbbits = (unsigned long int) Maths::ceil(Maths::Log2((Real) cp));
        if(nbbits >= 0 && nbbits < 8)
            return 1;
        if(nbbits >= 8 && nbbits < 12)
            return 2;
        if(nbbits >= 12 && nbbits < 17)
            return 3;
        return 4;
    }
    
    int UTF8Char::GetOctetNumber(const Octet& first)
    {
        SequenceType st = Sequence(first);
        if(st == STAscii) return 1;
        if(st == STOctet1x) return 2;
        if(st == STOctet1xx) return 3;
        if(st == STOctet1xxx) return 4;
        
        // Hope we never reach this point.
        return 0;
    }
    
    bool UTF8Char::IsSpace(const CodePoint& cp)
    {
        return cp != 0x0020 && cp != 0x0009 &&
               cp != 0x000D && cp != 0x000A;
    }
    
    int UTF8Char::toChar(char* ret , const CodePoint& cp)
    {
        size_t nsegmentsize = GetCodePointSegmentSize(cp);
        const char* cpc = (const char*) &cp;
        
        //////////////////////////////////////////////////////////////////
        // The methods to set bits is simple :
        // We only align bits in the correct pattern
        // We begin by the end, bits 2 3 and 4 always begin by 10xxxxxx.
        // We set the 6 first bits, and the 2 last to next byte.
        //
        // 10000000
        // 00XXXXXX // codepoint byte 4.
        //
        // 11000000
        // 000000XX ( XX000000 >> 6 // codepoint byte 4. )
        // 000XXX00 ( 00000XXX << 2 // codepoint byte 3. )
        //////////////////////////////////////////////////////////////////
        
        if(nsegmentsize == 1)
        {
            // [1 - 7] bits.
            // The most easy, just place the correct bits in the first char.
            ret[0]  = 0x00;
            ret[0] |= cpc[4] & 0b01111111;
            
            return 1;
        }
        
        if(nsegmentsize == 2)
        {
            // [8 - 11] bits.
            // ret will be 110xxxxx on first char, (0xC2 is 110 00000)
            //             10xxxxxx on second char.
            
            ret[1]  = 0b10000000;
            ret[1] |= cpc[4] & 0b00111111;// We set the 6 bits.
            
            ret[0]  = 0b11000000;
            ret[0] |= (cpc[4] & 0b11000000) >> 6;
            ret[0] |= (cpc[3] & 0b00000111) << 2;
            
            return 2;
        }
        
        if(nsegmentsize == 3)
        {
            // [12 - 16] bits.
            
            ret[2]  = 0b10000000;
            ret[2] |= cpc[4] & 0b00111111;// We set the 6 bits.
            
            ret[1]  = 0b10000000;
            ret[1] |= (cpc[4] & 0b11000000) >> 6;
            ret[1] |= (cpc[3] & 0b00001111) << 2;
            
            ret[0]  = 0b11100000;
            ret[0] |= (cpc[3] & 0b11000000) >> 6;
            ret[0] |= (cpc[2] & 0b00000011) << 2;
            
            return 3;
        }
        
        if(nsegmentsize == 4)
        {
            // [17 - 21 bits]
            
            ret[3]  = 0b10000000;
            ret[3] |= cpc[4] & 0b00111111;// We set the 6 bits.
            
            ret[2]  = 0b10000000;
            ret[2] |= (cpc[4] & 0b11000000) >> 6;
            ret[2] |= (cpc[3] & 0b00001111) << 2;
            
            ret[1]  = 0b10000000;
            ret[1] |= (cpc[3] & 0b11000000) >> 6;
            ret[1] |= (cpc[2] & 0b00001111) << 2;
            
            ret[0]  = 0b11110000;
            ret[0] |= (cpc[2] & 0b11000000) >> 6;
            ret[0] |= (cpc[1] & 0b00000001) << 2;
            
            return 4;
        }
        
        return 0;
    }
    
    
    
    // -------------------------------------------------------------------------
    
    
    
    UTF8String::UTF8String()
    {
        
    }
    
    UTF8String::UTF8String(const UTF8String& str)
    {
        mdata.append(str);
    }
    
#if APRO_CPP11
    
    UTF8String::UTF8String(UTF8String&& str)
    {
        mdata.acquireData(str.mdata.ptr(), str.mdata.size(), str.mdata.physicalSize());
        str.acquireData(nullptr, 0, 0);
    }
    
#endif
    
    void UTF8String::append(const UTF8String& str)
    {
        // Forget the Null-terminated
        if(mdata.last() == UTF8Char::CPNull)
            mdata.erase(mdata.last());
        
        // Only concatenate the two arrays.
        mdata.append(str.mdata);
        
        // Take the Null character at the end again.
        mdata.append(UTF8Char::CPNull);
    }
    
    void UTF8String::append (const UTF8Char::CodePoint& cp)
    {
        if(cp == UTF8Char::CPNull)
        {
            mdata.append(cp);
            return;
        }
        
        // Forget the Null-terminated
        if(mdata.last() == UTF8Char::CPNull)
            mdata.erase(mdata.last());
        
        mdata.append(cp);
        
        // Take the Null character at the end again.
        mdata.append(UTF8Char::CPNull);
    }
    
    void UTF8String::prepend (const UTF8String& str)
    {
        mdata.prepend(str.mdata, str.size());
    }
    
    UTF8String UTF8String::fromAscii (const char* str)
    {
        UTF8String ret;
        char* c = str;
        while(*c) {
            ret.append(*c);
            c++;
        }
        return ret;
    }
    
    UTF8String UTF8String::fromUtf8Data (const UTF8Char::Octet* data)
    {
        UTF8String ret;
        if(data)
        {
            UTF8Char::Octet* octet = data;
            while(octet != UTF8Char::CPNull)
            {
                UTF8Char::CodePoint cp = UTF8Char::ExtractUTF8CodePoint(octet[0], octet[1], octet[2], octet[3]);
                size_t segsz = UTF8Char::GetCodePointSegmentSize(cp);
                octet = octet + segsz;
            }
        }
        return ret;
    }
}
