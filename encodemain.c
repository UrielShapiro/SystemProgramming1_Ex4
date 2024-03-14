#include <stdio.h>
#include <string.h>
#include "compress.h"

#define FILE_NAME_SIZE 50

int main(int argc, char **argv)
{
    char choice = ' ';
    char file_name[FILE_NAME_SIZE];
    for (int i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], "-c") == 0)
        {
            choice = 'c';
        }
        else if (strcmp(argv[i], "-d") == 0)
        {
            choice = 'd';
        }
        else
        {
            strcpy(file_name, argv[i]);
        }
    }
    printf("Choice: %c\n", choice);
    printf("File name: %s\n", file_name);

    FILE *file;
    if ((file = fopen(file_name, "r")) == NULL)
    {
        printf("Error: File not found\n");
        return 1;
    }
    if (choice == 'c')
    {
        compress(file, file_name);
    }
    else if (choice == 'd')
    {
        decompress(file);
    }

    if (fclose(file) == EOF)
    {
        printf("Error closing file\n");
        return (2);
    }
    return 0;
}