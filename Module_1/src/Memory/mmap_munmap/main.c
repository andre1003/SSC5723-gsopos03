// MMAP and MUNMAP system calls program
// Reference: https://man7.org/linux/man-pages/man2/mmap.2.html

// Imports
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
    // Struct for store file info
    struct stat statBuffer;

    // Path of the file to be read
    const char *filePath = "./file.txt";

    printf("###################################\n");
    printf("#   MMAP and MUNMAP system calls  #\n");
    printf("###################################\n\n");

    // Open file in read-only mode
    int file = open(filePath, O_RDONLY);
    
    // Check if cannot open file OR cannot collect file info
    if(file == -1 || fstat(file, &statBuffer) == -1) {
        // Print error message and exit
        printf(">> Error with file openning or with file info! :(\n");
        return EXIT_FAILURE;
    }
    
    // Start ptr for file reading. Setting it to 0 means that all file should be read
    off_t offset = 0;

    // Bitwise operation for mapping system page length
    off_t pageOffset = offset & ~(sysconf(_SC_PAGE_SIZE) - 1);

    // File length
    size_t length = statBuffer.st_size - offset;
    
    // Use mmap to map a file in the memory. After the execution, the memory address of mapped file is returned or an error code
    /* mmap takes the following params:
            Hint address to guide where to map file. NULL will let OS choose;
            Map length (not necessarly of file);
            Page modification specifier. PROT_READ for read and PROT_WRITE for write;
            Flags that establish map access/visibility modifiers for other processes. MAP_PRIVATE for only the owner or MAP_SHARED for shared process;
            File to be mapped;
            Start position of mapping. */
    char *addr = mmap(NULL, length + offset - pageOffset, PROT_READ, MAP_PRIVATE, file, pageOffset);
    
    // Check if mapping was successful
    if(addr == MAP_FAILED) {
        // Print error message and exit
        printf(">> Impossible to map file! :(\n");
        return EXIT_FAILURE;
    }

    // Print the file content
    printf(">> File content: %s", addr);
    
    // Use munmap to unmap file from memory
    /* munmap uses the following params:
            Memory address to be unmapped
            Map length */
    int resp = munmap(addr, length + offset - pageOffset);
    
    // Check if the unmap has returned an error
    if(resp != 0) {
        // Print error message
        printf(">> Error at unmap file!\n");
    }
    
    // Close the file and exit
    close(file);

    return 0;
}