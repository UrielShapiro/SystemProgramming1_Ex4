#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "compress.h"

typedef struct{
    char first_bits   :4;
    char next_bits  :4;
}fourBits;

int writeToFile(fourBits num, char* file_name)
{
    FILE* file = fopen(file_name, "a");
    if (file == NULL)
    {
        printf("Error: File not found\n");
        return 1;
    }
    fputc(num.first_bits, file);
    fputc(num.next_bits, file);
    int checkError = fclose(file);
    if(checkError == EOF)
    {
        printf("Error closing file\n");
        return 2;
    }
    return 0;
}

int compress(FILE* file, char* file_name)
{
    file_name[strlen(file_name) - 4] = '\0';
    char* new_file_name = strcat(file_name, ".bin");
    fourBits num;
    printf("First char: %c\n", fgetc(file));
    printf("New file name: %s\n", new_file_name);
    char length[5000];
    fgets(length, 5000, file);
    printf("Length: %ld\n", strlen(length));
    size_t i = 1;
    fflush(stdin);
    fseek(file, 0, SEEK_SET);
    while (i <= strlen(length)/2)
    {
        printf("i: %ld\n", i);
        int number = fgetc(file);
        printf("Number: %c\n", number);
        num.first_bits = ~number;
        number = fgetc(file);
        printf("Second Number: %c\n", number);
        num.next_bits = ~number;
        printf("Stuck in the loop, first bits: %d, Second bits: %d\n", num.first_bits, num.next_bits);
        writeToFile(num, new_file_name);
        i++;
    }
    if(strlen(length) % 2 != 0)
    {
        int number = fgetc(file);
        printf("Got out of the loop, Number: %c\n", number);
        num.first_bits = ~number;
        num.next_bits = 0x0000;
        printf("Stuck in the loop, first bits: %d, Second bits: %d\n", num.first_bits, num.next_bits);
        writeToFile(num, new_file_name);
    }
        

    return 0;
}
int decompress(FILE* file)
{
    fclose(file);
    printf("Decompressing file\n");
    return 0;
}