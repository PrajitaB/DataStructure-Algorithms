/*Aim of the program: Write a program in C to convert the first ‘n’ decimal numbers of a disc
file to binary using recursion. Store the binary value in a separate disc file.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void decimalToBinary(int n, char *binary, int index)
{
    if (n > 1)
    {
        decimalToBinary(n / 2, binary, index - 1);
    }
    binary[index] = (n % 2) + '0';
}

void writeBinary(FILE *outputFile, int num)
{
    char binary[17];
    memset(binary, '0', 16);
    binary[16] = '\0';
    decimalToBinary(num, binary, 15);
    fprintf(outputFile, "The binary equivalent of %d is %s", num, binary);
}

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        fprintf(stderr, "Usage: %s <n> <source file> <destination file>\n", argv[0]);
        return 1;
    }
    int n = atoi(argv[1]);
    char *sourceFileName = argv[2];
    char *destFileName = argv[3];
    FILE *sourceFile = fopen(sourceFileName, "r");
    if (sourceFile == NULL)
    {
        fprintf(stderr, "Could not open file %s\n", sourceFileName);
        return 1;
    }
    FILE *destFile = fopen(destFileName, "w");
    if (destFile == NULL)
    {
        fprintf(stderr, "Could not open file %s\n", destFileName);
        fclose(sourceFile);
        return 1;
    }
    int num;
    for (int i = 0; i < n && fscanf(sourceFile, "%d", &num) != EOF; i++)
    {
        writeBinary(destFile, num);
    }
    fclose(sourceFile);
    fclose(destFile);
    destFile = fopen(destFileName, "r");
    if (destFile == NULL)
    {
        fprintf(stderr, "Could not open file %s\n", destFileName);
        return 1;
    }
    char line[256];
    while (fgets(line, sizeof(line), destFile))
    {
        printf("%s\t", line);
    }
    fclose(destFile);
    return 0;
}