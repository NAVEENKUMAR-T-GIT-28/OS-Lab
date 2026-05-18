#include <stdio.h>
#include <dirent.h>
int main() {
    DIR *d = opendir(".");
    struct dirent *entry;
    if (!d) { 
        perror("opendir"); 
        return 1; 
    }
    printf("Files in current directory:\n");
    while ((entry = readdir(d)) != NULL)
        printf("  %s\n", entry->d_name);
    closedir(d);
    return 0;
}