#include <stdbool.h>

#include <stdint.h>
#include "platform.h"

#if defined(__linux__) || defined(TARGET_OS_MAC)

#include <unistd.h>
#include <sys/mman.h>

i32 platform_get_page_size(void) {
    return getpagesize();
}

void *reserve_memory(u64 size) {
    // PROT_NONE - can't write or read data store here
    // MAP_ANONYMOUS - set all data to zero and is not connected to a file
    // MAP_PRIVATE - data isn't visible to other programs
    // MAP_NORESERVE - doesn't reserve any swap space for the reserve virtual data on your drive
    void *ptr = mmap(NULL, size, PROT_NONE, MAP_ANONYMOUS | MAP_PRIVATE | MAP_NORESERVE, -1, 0);

    if (ptr == MAP_FAILED) {
        return NULL;
    }

    return ptr;
}

bool commit_memory(void *ptr, u64 size) {
    // function that changes read/write/execute rules for data
    return mprotect(ptr, size, PROT_READ | PROT_WRITE) == -1;
}

bool release_memory(void *ptr, u64 size) {
    // deallocates the mapped reagion of memory
    return munmap(ptr, size) == -1;
}

#elif _WIN32
#include <windows.h>

i32 platform_get_page_size(void) {
    SYSTEM_INFO info = {0};
    GetSystemInfo(&info);

    return info.dwPageSize;
}

void *reserve_memory(u64 size) {
    return VirtualAlloc(NULL, size, MEM_RESERVE, PAGE_NOACCESS);
}

bool commit_memory(void *ptr, u64 size) {
    return VirtualAlloc(ptr, size, MEM_COMMIT, PAGE_READWRITE) == NULL;
}

bool release_memory(void *ptr, u64 size) {
    return VirtualFree(ptr, size, MEM_RELEASE) == 0;
}

#endif
