// eatmemory.cpp : Defines the entry point for the console application.
//

#include <Windows.h>

#include <exception>
#include <iostream>
#include <memory>
#include <vector>


template<int ChunkSize>
struct MemoryChunk
{
    std::shared_ptr<char> chunk;
    MemoryChunk() : chunk()
    {
        chunk.reset(new char[ChunkSize]);
    }
};

int main()
{
    long GBToBytes = 1024 * 1024 * 1024;

    long long MaxMemoryToAllocateInBytes = 0;
    std::cout << "Max Memory to allocate in GB:\t";
    std::cin >> MaxMemoryToAllocateInBytes;
    std::cout << std::endl;

    MaxMemoryToAllocateInBytes = MaxMemoryToAllocateInBytes * GBToBytes;
    static const int AllocationSize = 20 * 1024; // 20KB chunk
    const long long MaxAllocations = MaxMemoryToAllocateInBytes / AllocationSize + 1;

    std::cout << "Allocating " << MaxMemoryToAllocateInBytes << " Bytes in " << MaxAllocations << " Chunks of 20KB" << std::endl;
    
    std::vector<MemoryChunk<AllocationSize>> alloccedMemory;
    alloccedMemory.reserve(MaxAllocations);

    long long counter = 0;
    long long allocatedTillNowInMB = 0;
    try
    {
        while (true && counter < MaxAllocations)
        {
            if (counter % 1000 == 0)
            {
                std::cout << "allocated- " << allocatedTillNowInMB << " MB" << std::endl;
                allocatedTillNowInMB += 20;
                Sleep(100);
            }

            ++counter;
            alloccedMemory.push_back(MemoryChunk<AllocationSize>());
        }
    }
    catch (std::exception& ex)
    {
        std::cout << "Caught exception: " << ex.what() << std::endl;
        std::cout << "Exiting now.." << std::endl;
    }

    std::cout << "done allocating.." << std::endl;
    std::cin.ignore();

	return 0;
}

