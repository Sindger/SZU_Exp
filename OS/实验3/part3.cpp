#include <stdio.h>
#include <iostream>
#include <cstdlib>

#define MB (1024*1024)

using namespace std;

int main() {
	size_t maxMemory = 0;
	size_t allocationSize = 1;
	while (true) {
		void* memory = malloc(allocationSize);
		if (memory != nullptr) {
			maxMemory = allocationSize;
			free(memory);
			allocationSize *=2;
		}
		else {
			break;
		}
	}
	allocationSize = maxMemory;
	while (true) {
		void* memory = malloc(allocationSize);
		if (memory != nullptr) {
			maxMemory = allocationSize;
			free(memory);
			allocationSize += 1000*MB;
		}
		else {
			break;
		}
	}
	allocationSize = maxMemory;
	while (true) {
		void* memory = malloc(allocationSize);
		if (memory != nullptr) {
			maxMemory = allocationSize;
			free(memory);
			allocationSize += 100 * MB;
		}
		else {
			break;
		}
	}allocationSize = maxMemory;
	while (true) {
		void* memory = malloc(allocationSize);
		if (memory != nullptr) {
			maxMemory = allocationSize;
			free(memory);
			allocationSize += 10 * MB;
		}
		else {
			break;
		}
	}allocationSize = maxMemory;
	cout << "Maximum virtual memory size:" << maxMemory / MB << "MB" << endl;
}