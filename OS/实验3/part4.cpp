#include <iostream>
#include <cstdint>
#include <cstring>
#include <windows.h>
#include <psapi.h>

#define MB 1024*1024
#define KB 1024

using namespace std;

void printMemoryUsage(const char* label, PROCESS_MEMORY_COUNTERS& counters) {
    cout << label << endl;
    cout << "    Virtual Memory: " << counters.PagefileUsage << " Byte" << std::endl;
    cout << "    Physical Memory: " << counters.WorkingSetSize << " Byte" << std::endl;
}

int main() {
    size_t Memory = 256 * MB;
    uint8_t* memory = (uint8_t*)malloc(Memory);
    PROCESS_MEMORY_COUNTERS beforeCounters, afterCounters;
    beforeCounters.cb = sizeof(beforeCounters);
    afterCounters.cb = sizeof(afterCounters);
    GetProcessMemoryInfo(GetCurrentProcess(), &beforeCounters, sizeof(beforeCounters));
    for (size_t i = 0; i < Memory; i += 4*KB) {
        memory[i]++;
    }
    GetProcessMemoryInfo(GetCurrentProcess(), &afterCounters, sizeof(afterCounters));
    printMemoryUsage("Before Memory Allocation", beforeCounters);
    printMemoryUsage("After Memory Allocation", afterCounters);
    free(memory);
    return 0;
}
