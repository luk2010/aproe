/*
    DevIL Image Loader / Writer for Atlanti's Project Engine.

    Luk2010 2012 - 2013
*/

#include <Image.h>
#include <Console.h>
#include <SharedPointer.h>

#include "Writer.h"

#include "IL/il.h"
#include "IL/ilu.h"

DevILWriter::DevILWriter()
    : ResourceWriter()
{
    DevILLoader::initializeDevIL();

    setParam(String("Name"), Variant(String("DevILWriter")));
    setParam(String("Description"), Variant(String("Write an image using DevIL Library.")));
}

DevILWriter::DevILWriter(const DevILWriter& other)
    : ResourceWriter(other)
{
    DevILLoader::initializeDevIL();

    setParam(String("Name"), Variant(String("DevILWriter")));
    setParam(String("Description"), Variant(String("Write an image using DevIL Library.")));
}

DevILWriter::~DevILWriter()
{

}

void DevILWriter::write(const SharedPointer<Resource>& resource, const String& filename) const
{
    if(resource.isNull() || filename.isEmpty() || resource->getType() != "Image")
        return;

    const SharedPointer<Image>& img = spCstCast<Image, Resource>(resource);

    ILuint handle;

    handle = ilGenImage();
    ilBindImage(handle);

    ILbyte* data = (ILbyte*) img->rawColors();

    ilTexImage(img->width(), img->height(), 1, 4, IL_RGBA, IL_UNSIGNED_BYTE, data);
    iluFlipImage();

    ilSaveImage(filename.toCstChar());

    Console::get() << "\n[DevIL Image Loader] Resource " << resource->getName() << " correctly wrote in file " << filename << ".";
    ilDeleteImage(handle);
}
