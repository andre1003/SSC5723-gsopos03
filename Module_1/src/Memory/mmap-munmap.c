#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
* arquivo para teste das chamadas de sistema mmap e munmap.
*/

int main(int argc, char *argv[]) {
    struct stat sb;
    const char *file_path = "./file.txt";
    int fd = open(file_path, O_RDONLY);
    
    if (fd == -1 || fstat(fd, &sb) == -1) {
        printf("Erro ao abrir ou ler informações sobre o arquivo! :(\n");
        return EXIT_FAILURE;
    }
    
    off_t offset = 0;
    off_t pa_offset = offset & ~(sysconf(_SC_PAGE_SIZE) - 1);
    size_t length = sb.st_size - offset;
    
    char *addr = mmap(NULL, length + offset - pa_offset, PROT_READ, MAP_PRIVATE, fd, pa_offset);
    
    if (addr == MAP_FAILED) {
        printf("Não foi possível mapear o arquivo! :(\n");
        return EXIT_FAILURE;
    }
    
    write(STDOUT_FILENO, addr + offset - pa_offset, length);
    
    int resp = munmap(addr, length + offset - pa_offset);
    
    if (resp != 0) {
        printf("Erro ao liberar o mapa da memória! :(\n");
    }
    
    close(fd);
    return 0;
}