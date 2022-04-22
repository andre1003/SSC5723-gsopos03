#include <stdio.h>
#include <stdlib.h>

#define NUM_ITER 10000

int main(int argc, char const *argv[]) {
    FILE *file_1, *file_2;
    char info[50];
    int i;

    file_1 = fopen("file_1.txt", "r");
    remove("file_2.txt");
    file_2 = fopen("file_2.txt", "w");

    if(file_1 != NULL) {
        while((fgets(info, sizeof(info), file_1)) != NULL) {
           for(i = 0; i < NUM_ITER; i++) {
               fprintf(file_2, "%s\n", info);
           }
        }
    }

    fclose(file_1);
    fclose(file_2);
    return 0;
}