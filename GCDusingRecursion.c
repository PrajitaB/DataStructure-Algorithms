/*Aim  of  the  program:  Write a program in C to find GCD of two numbers using recursion.
Read all pair of numbers from a file and store the result in a separate file.*/

#include <stdio.h>
#include <stdlib.h>

// Function to find GCD using recursion
int gcd(int a, int b)
{
    if (b == 0)
    {
        return a;
    }
    else
    {
        return gcd(b, a % b);
    }
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: %s <source file> <destination file>\n", argv[0]);
        return 1;
    }

    char *sourceFile = argv[1];
    char *destFile = argv[2];

    FILE *inFile = fopen(sourceFile, "r");
    if (inFile == NULL)
    {
        perror("Error opening source file");
        return 1;
    }

    FILE *outFile = fopen(destFile, "w");
    if (outFile == NULL)
    {
        perror("Error opening destination file");
        fclose(inFile);
        return 1;
    }

    int a, b;
    int count = 0;

    while (fscanf(inFile, "%d %d", &a, &b) != EOF)
    {
        int result = gcd(a, b);
        fprintf(outFile, "The GCD of %d and %d is %d\n", a, b, result);
        count++;
    }

    fclose(inFile);
    fclose(outFile);

    // Ensure there are at least 20 pairs in the input file
    if (count < 20)
    {
        printf("The source file must contain at least 20 pairs of numbers.\n");
        remove(destFile); // Remove output file if condition is not met
        return 1;
    }

    // Display the contents of the output file
    outFile = fopen(destFile, "r");
    if (outFile == NULL)
    {
        perror("Error opening destination file for reading");
        return 1;
    }

    char ch;
    while ((ch = fgetc(outFile)) != EOF)
    {
        putchar(ch);
    }

    fclose(outFile);

    return 0;
}