/** @file Image.h
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 23/09/2012
 *
 *  @addtogroup Global
 *  @addtogroup Resource
 *
 *  This file defines the Image class.
 *
**/
#ifndef APROIMAGE_H
#define APROIMAGE_H

#include "Resource.h"
#include "Color.h"
#include "SString.h"
#include "Rectangle.h"
#include "SharedPointer.h"

namespace APro
{
    class APRO_DLL Image : public Resource
    {
    public:

        typedef struct Data
        {
            Array<Color> colors;
            size_t width;
            size_t height;

            Data() : colors(), width(0), height(0) { }

        } Data;

        typedef struct OriginData
        {
            String type;
            String loader;
            String advicedWriter;
            int bpp;
            size_t width;
            size_t height;

            OriginData() : type(""), loader(""), advicedWriter(""), bpp(0), width(0), height(0) { }

        } OriginData;

    public:

        Image();
        Image(const String& name_, const String& filename_);
        Image(const String& name_, const String& filename_, const Data& mdata, const OriginData& modata);

        size_t width() const;
        size_t height() const;

        Array<Color>& colors();
        const Array<Color>& colors() const;

        unsigned char* rawColors();
        const unsigned char* rawColors()const;

        void set(size_t x, size_t y, const Color& c);
        void fill(const Color& c);

        Color& get(size_t x, size_t y);
        const Color& get(size_t x, size_t y) const;

        void resize(size_t width, size_t height);

        SharedPointer<Image> subRect(const Rectangle<size_t>& rect) const;
        void flip();
        void mirror();

        void destroy();

    protected:

        void flipWidth(size_t h);

    private:

        Data data;
        OriginData odata;
    };
}

#endif
