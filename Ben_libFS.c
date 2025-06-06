#include "/Users/benhb/Desktop/CWU/CWU third year/Spring/operating systems/C/Lab4/Ben_libFS.h"
#include <string.h>
#include <stdlib.h>

int fileCreate(const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) return -1;
    fclose(fp);
    return 0;
}

FS_File* fileOpen(const char *filename, const char *mode) {
    FS_File *fs_file = (FS_File*)malloc(sizeof(FS_File));
    fs_file->fp = fopen(filename, mode);
    if (!fs_file->fp) {
        free(fs_file);
        return NULL;
    }
    strncpy(fs_file->filename, filename, sizeof(fs_file->filename));
    return fs_file;
}

int fileWrite(FS_File *fs_file, const char *content) {
    if (!fs_file || !fs_file->fp) return -1;
    fprintf(fs_file->fp, "%s", content);
    return 0;
}

int fileRead(FS_File *fs_file) {
    if (!fs_file || !fs_file->fp) return -1;
    fseek(fs_file->fp, 0, SEEK_SET);
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), fs_file->fp) != NULL) {
        printf("%s", buffer);
    }
    return 0;
}

int fileClose(FS_File *fs_file) {
    if (!fs_file) return -1;
    if (fs_file->fp) fclose(fs_file->fp);
    free(fs_file);
    return 0;
}

int fileDelete(const char *filename) {
    return remove(filename);
}
