#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>

int main() {
    DIR * x = opendir("./");
    struct dirent *entry;
    entry = readdir(x);
    printf("Statistics for directory: %s\n", entry -> d_name);
    unsigned int size = 0;
    while (entry) {
        struct stat curr;
        stat(entry -> d_name, &curr);
        size += curr.st_size;
        entry = readdir(x);
    }
    rewinddir(x);
    entry = readdir(x);
    printf("Total Directory Size: %u Bytes\n", size);
    printf("Directories:\n");
    while (entry) {
        if (entry -> d_type == DT_DIR) {
            printf("\t%s\n", entry -> d_name);
        }
        entry = readdir(x);
    }
    rewinddir(x);
       
    printf("Regular Files:\n");
    entry = readdir(x);
    while (entry) {
        if (entry -> d_type == DT_REG) {
            printf("\t%s\n", entry -> d_name);
        }
        entry = readdir(x);
    }
}
