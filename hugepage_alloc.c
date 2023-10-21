#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <linux/hugetlb.h> // Required for huge page flags

int main() {
    // Allocate 1 GB of memory using mmap with huge pages
    size_t size = 1 * 1024 * 1024 * 1024; // 1 GB
    size_t huge_page_size = 2 * 1024 * 1024; // 2 MB (adjust based on your system's huge page size)

    void *ptr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS | MAP_HUGETLB, -1, 0);
    
    if (ptr == MAP_FAILED) {
        perror("Memory allocation using mmap with huge pages failed");
        exit(1);
    }

    // Touch the memory
    memset(ptr, 0, size);

    // Lock the memory to prevent swapping
    if (mlock(ptr, size) != 0) {
        perror("Failed to lock memory");
        exit(1);
    }

    // Print the process ID
    printf("Process ID: %d\n", getpid());

    // Unmap the memory when done
    if (munmap(ptr, size) != 0) {
        perror("Failed to unmap memory");
        exit(1);
    }

    return 0;
}

