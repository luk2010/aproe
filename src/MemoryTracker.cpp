/** @file MemoryTracker.cpp
 *
 *  @author Luk2010
 *  @version 0.1A
 *
 *  @date 22/05/2012 - 26/05/2012
 *
 *  @addtogroup Memory
 *
 *  This file implements the Memory Tracker.
 *
**/
#include "MemoryTracker.h"

#if APRO_MEMORYTRACKER == APRO_ON

#include <sstream>
#include <cstdio>
#include <iostream>

#undef new
#undef  delete

namespace APro
{
    //MemoryTracker* MemoryTracker::instance = nullptr;

    MemoryTracker::MemoryTracker()
    {
        file.file = nullptr;
        file.filename = "";
        file.liveWriting = false;

        statistics.objectNumber = 0;
        statistics.totalBytesAllocated = 0;

        totalStats.objectNumber = 0;
        totalStats.totalBytesAllocated = 0;

        stack.retain = true;
        stack.cutFilename = false;
        stack.maxSize = 0;
    }

    MemoryTracker::~MemoryTracker()
    {
        if(!stack.buffer.empty())
        {
            updateStack(true);
        }
        reportLeaks();
        deinitfile();

        blockMap.clear();
        file.file = nullptr;
    }

    MemoryTracker* MemoryTracker::get()
    {

        static MemoryTracker tracker;
        return &tracker;
    }

    void MemoryTracker::reportAllocation(void* ptr, size_t byte, const char* func, const char* file, int line)
    {
        if(ptr == nullptr)
        {
            return;
        }

        std::string filename = processFilename(file);

        MemoryBlock* block = findBlock(ptr);
        if(block != nullptr)
        {
            std::stringstream stream;
            stream << "\n[" << filename << "]{" << func << "}(" << line << ") Allocation of already allocated adress : " << ptr << ".";

            stack.buffer += stream.str();

            updateStack();
            return;
        }

        MemoryBlock newBlock;
        newBlock.func = func;
        newBlock.file = filename;
        newBlock.line = line;
        newBlock.bytes = byte;
        blockMap[ptr] = newBlock;

        statistics.totalBytesAllocated += byte;
        statistics.objectNumber += 1;

        totalStats.objectNumber += 1;
        totalStats.totalBytesAllocated += byte;

        std::stringstream stream;
        stream << "\n[" << filename << "]{" << func << "}(" << line << ") Allocation of " << byte << " bytes in block " << ptr << ".";

        if(stack.retain)
        {
            stack.buffer += stream.str();
            stack.dumper += stream.str();

            updateStack();
        }

        return;
    }

    void MemoryTracker::reportReallocation(void* ptr, void* new_ptr, size_t byte, const char* func, const char* file, int line)
    {
        if(new_ptr == nullptr)
        {
            reportDeallocation(ptr, func, file, line);
            return;
        }
        if(ptr == nullptr)
        {
            reportAllocation(new_ptr, byte, func, file, line);
            return;
        }

        std::string filename = processFilename(file);

        MemoryBlock* block = findBlock(ptr);
        if(block == nullptr)
        {
            std::stringstream stream;
            stream << "\n[" << filename << "]{" << func << "}(" << line << ") Block not found for adress " << ptr << ", reporting as new allocation for adress " << new_ptr << ".";

            stack.buffer += stream.str();

            updateStack();

            reportAllocation(new_ptr, byte, func, file, line);

            return;
        }

        MemoryBlockMap::iterator it;
        for(it = blockMap.begin(); it != blockMap.end(); ++it)
        {
            if(it->first == ptr)
                break;
        }

        if(it == blockMap.end())
        {
            std::stringstream stream;
            stream << "\n[" << filename << "]{" << func << "}(" << line << ") Can't find block with adress " << ptr << ". Not releasing it will make fake-leaking appears.";

            stack.buffer += stream.str();

            updateStack();
        }
        else
        {
            statistics.totalBytesAllocated -= it->second.bytes;
            statistics.objectNumber -= 1;

            blockMap.erase(it);
        }

        MemoryBlock newBlock;
        newBlock.file = filename;
        newBlock.func = func;
        newBlock.line = line;
        newBlock.bytes = byte;
        blockMap[new_ptr] = newBlock;

        statistics.totalBytesAllocated += newBlock.bytes;
        statistics.objectNumber += 1;

        totalStats.objectNumber += 1;
        totalStats.totalBytesAllocated += newBlock.bytes;

        std::stringstream stream;
        stream << "\n[" << filename << "]{" << func << "}(" << line << ") Reallocation from block " << ptr << " to block " << new_ptr << " of " << byte << " bytes.";

        if(stack.retain)
        {
            stack.buffer += stream.str();
            stack.dumper += stream.str();

            updateStack();
        }

        return;
    }

    void MemoryTracker::reportDeallocation(void* ptr, const char* func, const char* file, int line)
    {
        if(ptr == nullptr)
        {
            return;
        }

        std::string filename = processFilename(file);

        MemoryBlock* block = findBlock(ptr);
        if(block == nullptr)
        {
            std::stringstream stream;
            stream << "\n[" << filename << "]{" << func << "}(" << line << ") Block not found for adress " << ptr << ", can't register deallocation.";

            stack.buffer += stream.str();

            updateStack();
            return;
        }

        MemoryBlockMap::iterator it;
        for(it = blockMap.begin(); it != blockMap.end(); ++it)
        {
            if(it->first == ptr)
                break;
        }

        if(it == blockMap.end())
        {
            std::stringstream stream;
            stream << "\n[" << filename << "]{" << func << "}(" << line << ") Can't find block with adress " << ptr << ". Not releasing it will make fake-leaking appears.";

            stack.buffer += stream.str();

            updateStack();
            return;
        }

        std::stringstream stream;
        stream << "\n[" << filename << "]{" << func << "}(" << line << ") Deallocation of " << block->bytes << " bytes in block " << ptr << ".";

        statistics.totalBytesAllocated -= it->second.bytes;
        statistics.objectNumber -= 1;

        blockMap.erase(it);

        if(stack.retain)
        {
            stack.buffer += stream.str();
            stack.dumper += stream.str();

            updateStack();
        }

        return;
    }

    std::string MemoryTracker::getFilename() const
    {
        return file.filename;
    }

    void MemoryTracker::setFilename(const std::string & filename)
    {
        file.filename = filename;

        deinitfile();
        updateStack();
    }

    bool MemoryTracker::isLiveWriting() const
    {
        return file.liveWriting;
    }

    void MemoryTracker::setLiveWriting(bool liveWriting)
    {
        file.liveWriting = liveWriting;
    }

    double MemoryTracker::getTotalBytesAllocated() const
    {
        return totalStats.totalBytesAllocated;
    }

    double MemoryTracker::getAverageBytesAllocated() const
    {
        return totalStats.totalBytesAllocated / totalStats.objectNumber;
    }

    int MemoryTracker::getObjectAllocatedNumber() const
    {
        return totalStats.objectNumber;
    }

    void MemoryTracker::updateStack(bool bypass)
    {
        if(!file.file)
        {
            initfile();
        }

        if( (file.file) &&
            (stack.buffer.size() > APRO_MEMORYTRACKERMAXBUFFERSIZE ||
             file.liveWriting == true ||
             bypass == true) )
        {
            fprintf(file.file, stack.buffer.c_str());
            stack.buffer.clear();
        }
    }

    void MemoryTracker::deinitfile()
    {
        if(file.file != nullptr)
        {
            fclose(file.file);
            file.file = nullptr;
        }
    }

    void MemoryTracker::initfile()
    {
        deinitfile();

        if(file.filename.size() == 0)
            return;

        file.file = fopen(file.filename.c_str(), "w+");

        if(file.file != nullptr)
        {
            fprintf(file.file, "Atlanti's Project Engine Memory Tracker - %s", APRO_MEMORY_VERSION);
            fprintf(file.file, "\n----------------------------------------------");
            fprintf(file.file, "\n\nLogging...\n");
        }
        else
        {
#if APRO_EXCEPTION == APRO_ON
            std::stringstream stream;
            stream << "Couldn't init file " << file.filename << " !";

            APRO_THROW("Memory Tracker", stream.str().c_str(), "Memory Tracker");
#endif
        }
    }

    void MemoryTracker::reportLeaks()
    {
        if(!blockMap.empty() || statistics.totalBytesAllocated > 0)
        {
            fprintf(file.file, "\n\nReporting Leaks...");
#if APRO_USECPLUSPLUS0X == APRO_ON
            for(auto it : blockMap)
#else
            for(MemoryBlockMap::iterator it = blockMap.begin(); it != blockMap.end(); ++it)
#endif

            {
                std::stringstream stream;
                stream << "\n[" << it->second.file << "]{" << it->second.func << "}(" << it->second.line << ") "
                << it->second.bytes << " bytes leak in adress " << it->first << ".";

                fprintf(file.file, stream.str().c_str());
            }

            fprintf(file.file, "\n\nTotal Bytes leaked : %f bytes.", statistics.totalBytesAllocated);
        }
        else
        {
            fprintf(file.file, "\n\nNo leaks detected ! Good job ;)");
        }

        fprintf(file.file, "\n\nStatistics report : ");
        fprintf(file.file, "\n+ Total Bytes Allocated : %f bytes.", totalStats.totalBytesAllocated);
        fprintf(file.file, "\n+ Total Object Allocated : %d Blocks.", totalStats.objectNumber);
        fprintf(file.file, "\n+ Strict Average Allocation Size : %f bytes.", totalStats.totalBytesAllocated / totalStats.objectNumber);
    }

    MemoryTracker::MemoryBlock* MemoryTracker::findBlock(void* ptr)
    {
#if APRO_USECPLUSPLUS0X == APRO_ON
        for(auto it : blockMap)
#else
        for(MemoryBlockMap::iterator it = blockMap.begin(); it != blockMap.end(); ++it)
#endif

        {
            if(it->first == ptr)
                return &(it->second);
        }

        return nullptr;
    }

    bool MemoryTracker::isCuttingFilename() const
    {
        return stack.cutFilename;
    }

    int MemoryTracker::maxFilenameSize() const
    {
        return stack.maxSize;
    }

    void MemoryTracker::setCutFilename(bool cut)
    {
        stack.cutFilename = cut;
    }

    void MemoryTracker::setMaxFilenameSize(int sz)
    {
        stack.maxSize = sz;
    }

    std::string MemoryTracker::processFilename(const char* file)
    {
        std::string filename(file);

        if(stack.cutFilename && (int) filename.size() > stack.maxSize)
        {
            size_t erasesz = filename.size() - stack.maxSize - 4;
            filename.erase(0, erasesz);
            filename.insert(0, "...");
        }

        return filename;
    }

    double MemoryTracker::getCurrentBytesAllocated() const
    {
        return statistics.totalBytesAllocated;
    }

    int MemoryTracker::getCurrentObjectAllocated() const
    {
        return statistics.objectNumber;
    }

    void MemoryTracker::dump(const std::string & filename)
    {
        FILE* f = fopen(filename.c_str(), "w+");
        FILE* f2 = file.file;
        file.file = f;

        fprintf(file.file, "Atlanti's Project Engine Memory Tracker - %s", APRO_MEMORY_VERSION);
        fprintf(file.file, "\n----------------------------------------------");
        fprintf(file.file, "\n\nLogging...\n");

        fprintf(f, stack.dumper.c_str());

        reportLeaks();

        file.file = f2;
        fclose(f);
    }

    void MemoryTracker::setRetain(bool r)
    {
        stack.retain = r;
    }
}

#endif
