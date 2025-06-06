#ifndef Ben_LIBFS_H
#define Ben_LIBFS_H

#include <stdio.h>

typedef struct {
    FILE *fp;
    char filename[256];
} FS_File;

int fileCreate(const char *filename);
FS_File* fileOpen(const char *filename, const char *mode);
int fileWrite(FS_File *fs_file, const char *content);
int fileRead(FS_File *fs_file);
int fileClose(FS_File *fs_file);
int fileDelete(const char *filename);

#endif
