#include "/Users/benhb/Desktop/CWU/CWU third year/Spring/operating systems/C/Lab4/Ben_libFS.h"
#include <stdio.h>
#include <stdlib.h>

void displayMenu() {
    printf("\n==== File System Menu ====\n");
    printf("1. Create file\n");
    printf("2. Write to file\n");
    printf("3. Read file\n");
    printf("4. Delete file\n");
    printf("5. Exit\n");
    printf("Choose an option: ");
}

int main() {
    const char *filename = "Ben_Introduction.txt";
    FS_File *fs_file = NULL;
    int choice;

    while (1) {
        displayMenu();
        scanf("%d", &choice);
        getchar(); // consume newline

        switch (choice) {
            case 1:
                if (fileCreate(filename) == 0)
                    printf("File '%s' created successfully.\n", filename);
                else
                    printf("Failed to create file.\n");
                break;
            case 2:
                fs_file = fileOpen(filename, "w");
                if (!fs_file) {
                    printf("Failed to open file for writing.\n");
                    break;
                }
                fileWrite(fs_file,
                    "Hello, my name is Ben.\n"
                    "I am a student working on file systems in C.\n\n"
                    "I enjoy programming and problem solving.\n"
                    "This is a sample file to demonstrate libFS features.\n"
                );
                fileClose(fs_file);
                printf("File written successfully.\n");
                break;
            case 3:
                fs_file = fileOpen(filename, "r");
                if (!fs_file) {
                    printf("Failed to open file for reading.\n");
                    break;
                }
                printf("\n--- File Contents ---\n");
                fileRead(fs_file);
                fileClose(fs_file);
                break;
            case 4:
                if (fileDelete(filename) == 0)
                    printf("File deleted successfully.\n");
                else
                    printf("Failed to delete file.\n");
                break;
            case 5:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid option.\n");
        }
    }
}
