/*
    References: https://man7.org/linux/man-pages/man2/open.2.html
                https://man7.org/linux/man-pages/man2/write.2.html
*/

// Includes
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h> 
#include <unistd.h>

int main(int argc, char **argv) {
    // Declaration of variables
    char *path_name, *buf;
    int flags, fd;
    mode_t mode;
    
    path_name = "./file.txt"; // Path name

    flags = O_RDWR | O_CREAT | O_TRUNC; // Flags
    /*
        O_RDWR: Opening the file read/write
        O_CREAT: If pathname does not exist, create it as a regular file
        O_TRUNC: If the file already exists and is a regular file and the access mode allows writing, it will be truncated to length 0
    */

    mode = 00744; // The file mode bits to be applied when a new file is created
    // 00744: -rwxr--r--

    fd = open(path_name, flags, mode); // Open or create a file
    // Return the file descriptor (fd)
    
    buf = "This is a test!"; // Buffer used to store the data to be written
    write(fd, buf, strlen(buf)); // Write to file

    close(fd); // Close the file
    return 0;
}