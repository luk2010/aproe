/*
    DevIL Image Loader / Writer for Atlanti's Project Engine.

    Luk2010 2012 - 2013
*/

#include <Console.h>
#include <Image.h>

#include "Loader.h"

#include "IL/il.h"
#include "IL/ilu.h"

bool DevILLoader::is_devil_initialized = false;

DevILLoader::DevILLoader()
    : ResourceLoader()
{
    setParam(String("Name"), Variant(String("DevILLoader")));
    setParam(String("Description"), Variant(String("Loads an image using DevIL library.")));
    setParam(String("IsManual"), Variant(true));

    initializeDevIL();
}

DevILLoader::DevILLoader(const DevILLoader& loader)
    : ResourceLoader(loader)
{
    setParam(String("Name"), Variant(String("DevILLoader")));
    setParam(String("Description"), Variant(String("Loads an image using DevIL library.")));
    setParam(String("IsManual"), Variant(true));

    initializeDevIL();
}

DevILLoader::~DevILLoader()
{

}

void DevILLoader::initializeDevIL()
{
    if(!is_devil_initialized)
    {
        ilInit();
        iluInit();

        ilEnable(IL_FILE_OVERWRITE);

        ilEnable(IL_ORIGIN_SET);
        ilSetInteger(IL_ORIGIN_MODE, IL_ORIGIN_UPPER_LEFT);

        is_devil_initialized = true;
    }
}

SharedPointer<Resource> DevILLoader::loadResource(const String& filename)
{
    ILuint handle;

    ilGenImages(1, &handle);
    ilBindImage(handle);

    ILboolean loaded = ilLoadImage(filename.toCstChar());
    if(!loaded)
    {
        ILenum error = ilGetError();
        if(error != IL_NO_ERROR)
        {
            Console::get() << "\n[DevIL Image Loader] Can't load image " << filename << " ! Error : " << iluErrorString(error);
            return SharedPointer<Resource>();
        }
    }

    Image::Data data;
    data.width = ilGetInteger(IL_IMAGE_WIDTH);
    data.height = ilGetInteger(IL_IMAGE_HEIGHT);

    Color* dc = AProNew(data.width * data.height, Color);
    ILuint * d = (ILuint*) dc;

    ilCopyPixels(0, 0, 0, data.width, data.height, 1, IL_RGBA, IL_UNSIGNED_BYTE, d);

    data.colors.set(dc, data.width * data.height);

    AProDelete(dc);
    ilDeleteImage(handle);

    Image::OriginData odata;
    odata.type = "DevIL Image";
    odata.loader = "DevILLoader";
    odata.advicedWriter = "DevILWriter";
    odata.bpp = ilGetInteger(IL_IMAGE_BYTES_PER_PIXEL);
    odata.width = data.width;
    odata.height = data.height;

    return SharedPointer<Resource>(AProNew(1, Image) (String(""), filename, data, odata));
}

