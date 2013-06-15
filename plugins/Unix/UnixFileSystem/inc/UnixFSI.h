/* Unix FileSystem Implementation */

#ifndef UNIX_FSI_H
#define UNIX_FSI_H

#include <Main.h>
#include <FileSystemImplementation.h>

#include <limits.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/sendfile.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

namespace APro
{
    class UnixFSI : public FileSystemImplementation
    {
    public:

        const String getImplementationName() const
        {
            return String("Unix FileSystem Implementation");
        }

    public:

        UnixFSI()
        {

        }

        ~UnixFSI()
        {

        }

    public:

        bool init()
        {
            return true;
        }

        void deinit()
        {

        }

        Implementation::ptr clone() const
        {
            return Implementation::ptr(AProNew(1, UnixFSI) ());
        }

        void destroy(Implementation* imp)
        {
            if(imp)
            {
                UnixFSI* impc = reinterpret_cast<UnixFSI*>(imp);
                if(impc)
                {
                    AProDelete(impc);
                }
            }
        }

    public:

        String generateRelative(const String& from, const String& path) const
        {
            String basepath = generateAbsolute(String(), from);
            String target = generateAbsolute(String(), path);

            if(target.isEmpty() || basepath.isEmpty())
            {
                return String();
            }

            List<String> basepath_list = basepath.explode(pathSeparator());
            List<String>::Iterator it = basepath_list.it(basepath_list.size()-1);
            basepath_list.erase(it);

            List<String> target_list = target.explode(pathSeparator());
            String filename = target_list.at(target_list.size() - 1);
            it = target_list.it(target_list.size()-1);
            target_list.erase(it);


            String ret;
            int index_folder = -1;
            for(unsigned int i = target_list.size() - 1; i >= 0; --i)
            {
                // On remonte pour trouver un repertoire

                index_folder = basepath_list.find(target_list.at(i));
                if(index_folder != -1)
                {
                    break;
                }
                else
                {
                    ret.append("../");
                }

            }

            for(unsigned int i = index_folder; i < basepath_list.size(); ++i)
            {
                ret.append(basepath_list.at(i));
                ret.append("/");
            }

            ret.append(filename);
            return ret;
        }

        String generateAbsolute(const String& base, const String& relativepath) const
        {
            char actualpath[PATH_MAX+1];
            realpath(relativepath.toCstChar(), actualpath);
            return String(actualpath);
        }

        bool isAbsolute(const String & path) const
        {
            if(path.isEmpty()) return false;
            return path.at(0) == '/';
        }

        bool isRelative(const String & path) const
        {
            return !isAbsolute(path);
        }

        char pathSeparator() const
        {
            return '/';
        }

        bool copy(const String& source, const String& target) const
        {
            if(source.isEmpty() || target.isEmpty()) return false;

            int read_fd;
            int write_fd;
            struct stat stat_buf;
            off_t offset = 0;

            read_fd = open(source.toCstChar(), O_RDONLY);
            if(read_fd < 0)
            {
                Console::get() << "\n[Unix FileSystem] Can't open file " << source << " to copy !";
                return false;
            }

            fstat(read_fd, &stat_buf);

            write_fd = open(target.toCstChar(), O_WRONLY | O_CREAT, stat_buf.st_mode);
            if(write_fd < 0)
            {
                Console::get() << "\n[Unix FileSystem] Can't open file " << target << " to copy !";
                close(read_fd);
                return false;
            }

            sendfile(write_fd, read_fd, &offset, stat_buf.st_size);
            Console::get() << "\n[Unix FileSystem] Copied " << (int) stat_buf.st_size << " bytes from " << source << " to " << target << ".";

            close(read_fd);
            close(write_fd);
            return true;
        }

        bool f_delete(const String& filepath) const
        {
            return remove(filepath.toCstChar()) == 0;
        }

        bool exists(const String& filepath) const
        {
            FILE* fp = NULL;

            fp = fopen(filepath.toCstChar(), "rb");
            if(fp != NULL)
            {
                fclose(fp);
                return true;
            }

            return false;
        }

        bool rename(const String& source, const String& target) const
        {
            return std::rename(source.toCstChar(), target.toCstChar()) == 0;
        }

    };
}

#endif // UNIX_FSI_H
