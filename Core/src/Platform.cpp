////////////////////////////////////////////////////////////
/** @file Platform.cpp
 *  @ingroup Global
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 26/02/2014 - 27/02/2014
 *
 *  Implements Platform specific things.
 *
**/
////////////////////////////////////////////////////////////
#include "Platform.h"

#if 0

#if APRO_PLATFORM == APRO_WINDOWS

bool _path_is_okay(const char * _dir_name)
{
    return PathFileExists(_dir_name) == TRUE;
}

void build_entry(DIR* _dir_p)
{
    if(!_dir_p)
        return;

    struct dirent* e = &(_dir_p->_entry);

    const size_t strsz = strlen(_dir_p->_data.name);
    memcpy(e->d_name, _dir_p->_data.name, sizeof(char) * strsz);
    e->d_name[strsz] = '\0';
    e->d_ino = _dir_p->_cur_id;
}

DIR* opendir(const char * _dir_name)
{
    // Our version of opendir doesn't truly open the
    // directory handle, it just verify that path is okay
    // and allocate memory for the directory structure.

    if(!_dir_name)
        return nullptr;
    if(strlen(_dir_name) == 0)
        return nullptr;

    if(!_path_is_okay(_dir_name))
        return nullptr;

    DIR* _ret = (DIR*) malloc(sizeof(DIR));
    if(!_ret)
        return nullptr;

    // We create the path like
    // blabla/blablablabl/example/ + *
    // result is : blabla/blablablabl/example/*

    const int strsz = strlen(_dir_name);
    _ret->_first_entry_code = (char*) malloc(sizeof(char) * (strsz + 1 + 1));
    const char* _find_code = "*";

    memcpy(_ret->_first_entry_code, _dir_name, sizeof(char) * strsz);
    memcpy(_ret->_first_entry_code + strsz, _find_code, sizeof(char));
    _ret->_first_entry_code[strsz+1] = '\0';

    _ret->_cur_id = -1;
    _ret->_handle = -1;
    return _ret;
}

struct dirent* readdir  (DIR* _dir_p)
{
    if(!_dir_p)
        return -1;

    if(_dir_p->_cur_id == -1)
    {
        // We did not set an id so we use _findfirst
        _dir_p->_handle = _findfirst( _dir_p->_first_entry_code, &(_ret->_data) );
        if(_dir_p->_handle == -1)
        {
            return nullptr;
        }
        else
        {
            _dir_p->_cur_id = 0;
            build_entry(_dir_p);
            return &(_dir_p->_entry);
        }
    }
    else if(_dir_p->_cur_id >= 0)
    {
        // We have to go next entry.
        if(_findnext( _dir_p->_handle, &(_dir_p->_data) ) != 0)
        {
            // Can't find any other entries, return nullptr.
            _dir_p->_cur_id = -2; // when _cur_id is -2 (or < -1), you must call rewinddir to get again entries.
            return nullptr;
        }
        else
        {
            // We build the entry and return it.
            build_entry(_dir_p);
            _dir_p->_cur_id += 1;
            return &(_dir_p->_entry);
        }
    }
    else
    {
        return nullptr;
    }
};

int closedir(DIR* _dir_p)
{
    if(!_dir_p)
        return -1;

    // When closing the dir pointer, we must free also the internal pointer.
    int ret = _findclose(_dir_p->_handle);

    if(_dir_p->_first_entry_code)
        free(_dir_p->_first_entry_code);

    free(_dir_p);
    return ret;
}

void rewinddir(DIR* _dir_p)
{
    if(!_dir_p)
        return;

    // Setting _cur_id to -1 will let readdir function use findfirst function
    // to be back at the beginning of the directory.
    _dir_p->_cur_id = -1;
}

#endif

#endif // 0

