/** @file Image.cpp
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 27/09/2012
 *
 *  @addtogroup Global
 *  @addtogroup Resource
 *
 *  This file defines the Image class.
 *
**/
#include "Image.h"
#include "Main.h"
#include "ResourceManager.h"

namespace APro
{
    Image::Image()
        : Resource()
    {
        type = "Image";
    }

    Image::Image(const String& name_, const String& filename_)
        : Resource(name_, filename_)
    {
        type = "Image";
    }

    Image::Image(const String& name_, const String& filename_, const Data& mdata, const OriginData& modata)
        : Resource(name_, filename_), data(mdata), odata(modata)
    {
        type = "Image";

        if(data.width + data.height != 0 && data.colors.size() == 0)
        {
            fill(Color((unsigned char) 255, 255, 255, 255));
        }
    }

    size_t Image::width() const
    {
        return data.width;
    }

    size_t Image::height() const
    {
        return data.height;
    }

    Array<Color>& Image::colors()
    {
        return data.colors;
    }

    const Array<Color>& Image::colors() const
    {
        return data.colors;
    }

    unsigned char* Image::rawColors()
    {
        if(data.colors.size() > 0)
            return data.colors[0];
        else
            return nullptr;
    }

    const unsigned char* Image::rawColors() const
    {
        if(data.colors.size() > 0)
            return data.colors[0];
        else
            return nullptr;
    }

    void Image::set(size_t x, size_t y, const Color& c)
    {
        if(x + y * data.width < data.colors.size())
        {
            data.colors[x + y * data.width] = c;
        }
    }

    void Image::fill(const Color& c)
    {
        for(size_t i = 0; i < data.colors.size(); ++i)
        {
            data.colors[i] = c;
        }
    }

    Color& Image::get(size_t x, size_t y)
    {
        return data.colors[x + y * data.width];
    }

    const Color& Image::get(size_t x, size_t y) const
    {
        return data.colors[x + y * data.width];
    }

    void Image::resize(size_t width, size_t height)
    {
        if(width != data.width || height != data.height)
        {
            Data newdata;

            newdata.width = width;
            newdata.height = height;
            newdata.colors.reserve(width * height);

            Vector2F step(static_cast<float>(data.width) / width, static_cast<float>(data.height) / height);

            for(size_t i = 0; i < width; ++i)
            {
                for(size_t j = 0; j < height; ++j)
                {
                    Color& c = get(static_cast<int>(i * step.x), static_cast<int>(j * step.y));
                    newdata.colors.append(c);
                }
            }

            data = newdata;
        }
    }

    SharedPointer<Image> Image::subRect(const Rectangle<size_t>& rect) const
    {
        SharedPointer<Image> img = AProNew(Image, getName() + "_sub_" + String::toString((unsigned int) rect.left()) + "_" +
                                                                       String::toString((unsigned int) rect.top()) + "_" +
                                                                       String::toString((unsigned int) rect.right()) + "_" +
                                                                       String::toString((unsigned int) rect.bottom()),

                                                  getFilename() + "_sub_" + String::toString((unsigned int) rect.left()) + "_" +
                                                                           String::toString((unsigned int) rect.top()) + "_" +
                                                                           String::toString((unsigned int) rect.right()) + "_" +
                                                                           String::toString((unsigned int) rect.bottom()));

        Data mdata;
        mdata.width = rect.width();
        mdata.height = rect.height();
        mdata.colors.reserve(rect.surface());

        img->data = mdata;

        Rectangle<size_t> mrect(0, 0, width(), height());
        if(mrect.intersects(rect) == Intersection::In)
        {
            for(size_t i = 0; i < mdata.width; ++i)
            {
                for(size_t j = 0; j < mdata.height; ++j)
                {
                    img->data.colors.append(get(i + rect.left(), j + rect.top()));
                }
            }
        }
        else
        {
            img->fill(Color((unsigned char) 0, 0, 0, 255));
        }

        Main::get().getResourceManager().Manager<Resource>::push(img);
        return img;
    }

    void Image::flip()
    {
        for(size_t j = 0; j < height() / 2; ++j)
        {
           std::swap_ranges(&data.colors[j * width()], &data.colors[(j + 1) * width() - 1],
                             &data.colors[(height() - j - 1) * width()]);
        }
    }

    void Image::flipWidth(size_t h)
    {
        if(h < height())
        {
            for(size_t c = h * width(); c <= (h + 1) * width() - 1; c++)
            {

            }
        }
    }

    void Image::mirror()
    {
        for(size_t i = 0; i < width() / 2; ++i)
        {
            for(size_t j = 0; j < height(); ++j)
            {
                std::swap_ranges(&data.colors[i + j * data.width],
                                 &data.colors[i + j * data.width + 1],
                                 &data.colors[data.width - i - 1 + j * data.width]);
            }
        }
    }

    void Image::destroy()
    {
        data.colors.clear();
        data.width = 0;
        data.height = 0;

        odata.type.clear();
        odata.loader.clear();
        odata.advicedWriter.clear();
        odata.bpp = 0;
        odata.width = 0;
        odata.height = 0;
    }
}
