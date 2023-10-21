#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <psapi.h>

#define SIZE_512MB 512*1024*1024
#define SIZE_1024MB 1024*1024*1024

using namespace std;

void PrintMemoryUsage() {
    HANDLE hProcess = GetCurrentProcess();
    PROCESS_MEMORY_COUNTERS memCounters;
    memCounters.cb = sizeof(PROCESS_MEMORY_COUNTERS);
    if (GetProcessMemoryInfo(hProcess, &memCounters, sizeof(PROCESS_MEMORY_COUNTERS))) {
        SIZE_T workingSetSize = memCounters.WorkingSetSize;
        SIZE_T peakWorkingSetSize = memCounters.PeakWorkingSetSize;
        SIZE_T pagefileUsage = memCounters.PagefileUsage;
        SIZE_T peakPagefileUsage = memCounters.PeakPagefileUsage;

        cout << "Working Set Size: " << workingSetSize / (1024 * 1024) << " MB\n";
        cout << "Peak Working Set Size: " << peakWorkingSetSize / (1024 * 1024) << " MB\n";
        cout << "Pagefile Usage: " << pagefileUsage / (1024 * 1024) << " MB\n";
        cout << "Peak Pagefile Usage: " << peakPagefileUsage / (1024 * 1024) << " MB\n";
        cout << endl;
        
    }
    else {
        cout << "Failed to get process memory info\n";
    }
}

int main() {
    string command;
    int* p1{}, * p2{}, * p3{}, * p4{};
    while (cin >> command) {
        if (command == "Allocate") {
            p1 = (int*)malloc(SIZE_512MB);
            if (p1 == NULL) {
                printf("Failed to allocate memory for p1\n");
                free(p1);
                return 1;
            }
            printf("Allocate P1\n");
            PrintMemoryUsage();
            p2 = (int*)malloc(SIZE_512MB);
            if (p2 == NULL) {
                printf("Failed to allocate memory for p2\n");
                free(p2);
                return 1;
            }
            printf("Allocate P2\n");
            PrintMemoryUsage();
            p3 = (int*)malloc(SIZE_512MB);
            if (p3 == NULL) {
                printf("Failed to allocate memory for p3\n");
                free(p3);
                return 1;
            }
            printf("Allocate P3\n");
            PrintMemoryUsage();
        }
        else if (command == "ReAllocate") {
            free(p2);
            printf("Release P2\n");
            PrintMemoryUsage();
            p4 = (int*)malloc(SIZE_1024MB);
            if (p4 == NULL) {
                printf("Failed to allocate memory for p4\n");
                free(p4);
                return 1;
            }
            printf("Allocate P4\n");
            PrintMemoryUsage();
        }
        else if (command == "Release") {
            if (p1 && p3 && p4) {
                free(p1);
                printf("Release P1\n");
                PrintMemoryUsage();
                free(p3);
                printf("Release P3\n");
                PrintMemoryUsage();
                free(p4);
                printf("Release P4\n");
                PrintMemoryUsage();
            }
        }
        else if (command == "Exit") {
            return 1;
        }
        else {
            printf("The instruction is wrong, please re-enter it");
            continue;
        }
    }
}
