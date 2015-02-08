////////////////////////////////////////////////////////////
/** @file Resource.h
 *  @ingroup Core
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 25/08/2012 - 23/12/2013
 *
 *  Defines the Resource class.
 *
**/
////////////////////////////////////////////////////////////
#ifndef APRORESOURCE_H
#define APRORESOURCE_H

#include "Platform.h"
#include "NonCopyable.h"
#include "AutoPointer.h"
#include "ThreadSafe.h"
#include "SString.h"
#include "HashedType.h"

namespace APro
{
    ////////////////////////////////////////////////////////////
    /** @class Resource
     *  @brief A simple Resource handler.
     *
     *  ### What is a resource ?
     *
     *  A resource is an object attached to a physical file. So
     *  basically you can load it, and write it to another file
     *  if loaders and writers are present.
     *
     *  A resource can be any type of object : a mesh, a texture,
     *  an image, etc. The ResourceManager unload every unloaded
     *  resources at his destruction, at the end of the program.
     *
     *  Custom resources should destroy every thing in their
     *  destructors as every destructors are called during the
     *  destruction process.
     *
     *  #### Load/Unload a Resource
     *
     *  @see ResourceManager
     *
     *  ### Identifying a Resource
     *
     *  As a resource is a HashedType, every Resource class
     *  has a unique Hash that identify it.
     *  @note Big Resource class should have a unique hash, but
     *  subclass should not. For example, if you make a JPeGImage
     *  class, user will want the Hash of the Image class, and not
     *  to include your files, he wil have to be able to compare
     *  your hash to Image::Hash. So think before you set a unique
     *  hash to your Resource class !
     *
     *  ### Manipulating Resource
     *
     *  The ResourceManager will give you a ResourceEntry pointer,
     *  wich is more usable thanks to the name of the entry. This
     *  entry is like a handle to this class, and you should always
     *  pass through this handler to manipulate your resource.
     *
     *  @note Resource is already ThreadSafe. If you override the
     *  Resource class, you can still use APRO_THREADSAFE_AUTOLOCK to lock
     *  automatic mutex.
     *
    **/
    ////////////////////////////////////////////////////////////
    class APRO_DLL Resource : virtual public ThreadSafe,
                              public HashedType,
                              public NonCopyable
    {

        APRO_DECLARE_HASHEDTYPE;

    protected:

        String m_filename;

    public:

        ////////////////////////////////////////////////////////////
        /** @brief Constructs the Resource object.
        **/
        ////////////////////////////////////////////////////////////
        Resource();

        ////////////////////////////////////////////////////////////
        /** @brief Constructs the Resource object giving the filename.
        **/
        ////////////////////////////////////////////////////////////
        Resource(const String& filename);

        ////////////////////////////////////////////////////////////
        /** @brief Destructs the Resource object.
        **/
        ////////////////////////////////////////////////////////////
        virtual ~Resource();


    public:

        ////////////////////////////////////////////////////////////
        /** @brief Returns the filename this Resource was loaded from.
        **/
        ////////////////////////////////////////////////////////////
        const String& getFilename() const;
    };

    typedef AutoPointer<Resource> ResourcePtr;
}

#endif
