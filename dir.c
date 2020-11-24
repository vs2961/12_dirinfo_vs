#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

int main(int argc, char **argv) {
    char loc[256];
    DIR * x;
    if (argc == 1) {
        printf("File Location: ");
        if (fgets(loc, sizeof loc, stdin) != NULL) {
            int len = strlen(loc);
            if (len > 0 && loc[len - 1] == '\n') {
                loc[len - 1] = '\0';
            }
        }
        x = opendir(loc);
    }
    else {
        strncpy(loc, argv[1], sizeof loc);
        int len = strlen(loc);
        if (len > 0 && loc[len - 1] == '\n') {
            loc[len - 1] = '\0';
        }
        x = opendir(loc);
    }
    if (x == NULL) {
        printf("errno %d: %s %s\n", errno, strerror(errno), loc);
        return 0;
    }
    struct dirent *entry;
    entry = readdir(x);
    printf("Statistics for directory: %s\n", loc);
    unsigned int size = 0;
    while (entry) {
        if (entry -> d_type == DT_REG) {
            char path[256]; 
            struct stat curr;
            int len = strlen(loc);
            if (loc[len - 1] != '/') {
                loc[len] = '/';
                loc[len + 1] = '\0';
                len++;
            }
            strcat(loc, entry -> d_name);
            printf("%s\n", loc);
            stat(loc, &curr);
            size += curr.st_size;
            loc[len] = '\0';
        }
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
