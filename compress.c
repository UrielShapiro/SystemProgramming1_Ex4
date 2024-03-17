#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "compress.h"

typedef struct{
    unsigned char first_bits   :4;
    unsigned char next_bits    :4;
}fourBits;

int compress(FILE* file, char* file_name)
{
    file_name[strlen(file_name) - 4] = '\0';
    char* new_file_name = strcat(file_name, ".bin");
    FILE* bin_file = fopen(file_name, "ab");
    printf("New file name: %s\n", new_file_name);

    fourBits num;
    fseek(file, 0, SEEK_END);
    size_t length = ftell(file) - 1;
    printf("Length: %ld\n", length);
    size_t i = 1;
    fflush(stdin);
    fseek(file, 0, SEEK_SET);
    while (i <= length/2)
    {
        printf("i: %ld\n", i);
        int number = fgetc(file);
        printf("Number: %c\n", number);
        num.first_bits = ~number;
        number = fgetc(file);
        printf("Second Number: %c\n", number);
        num.next_bits = ~number;
        printf("Stuck in the loop, first bits: %d, Second bits: %d\n", num.first_bits, num.next_bits);
        fwrite(&num, sizeof(num), 1, bin_file);
        i++;
    }
    if(length % 2 != 0)
    {
        int number = fgetc(file);
        printf("Got out of the loop, Number: %c\n", number);
        num.first_bits = ~number;
        num.next_bits = 0x0000;
        printf("first bits: %d, Second bits: %d\n", num.first_bits, num.next_bits);
        fwrite(&num, sizeof(num), 1, bin_file);
    }

    int checkError = fclose(bin_file);
    if(checkError == EOF)
    {
        printf("Error closing file\n");
        return 2;
    }
    printf("Compressed file\n");
    return 0;
}

int decompress(FILE* file, char* file_name)
{
    file_name[strlen(file_name) - 4] = '\0';
    char* new_file_name = strcat(file_name, ".txt");
    FILE* txt_file = fopen(file_name, "a");
    printf("New file name: %s\n", new_file_name);

    fourBits num;
    fseek(file, 0, SEEK_END);
    size_t length = ftell(file);
    printf("Length: %ld\n", length);
    size_t i = 1;
    fflush(stdin);
    fseek(file, 0, SEEK_SET);
    while (i <= length - 1)
    {
        char number;
        fread(&number, sizeof(number), 1, file);
        printf("Number: %d\n", number);
        number = ~number;
        num.first_bits = number;
        num.next_bits = number >> 4;
        printf("First bits: %d, Second bits: %d\n", num.first_bits, num.next_bits);
        fprintf(txt_file, "%d", num.first_bits);
        fprintf(txt_file, "%d", num.next_bits);
        i++;
    }

    if(length % 2 != 0)
    {
        char number;
        fread(&number, sizeof(number), 1, file);
        printf("Number: %d\n", number);
        number = ~number;
        num.first_bits = number;
        num.next_bits = 0;
        printf("First bits: %d, Second bits: %d\n", num.first_bits, num.next_bits);
        fprintf(txt_file, "%d", num.first_bits);
    }

    int checkError = fclose(txt_file);
    if(checkError == EOF)
    {
        printf("Error closing file\n");
        return 2;
    }
    printf("Decompressing file\n");
    return 0;
}