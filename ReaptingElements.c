/*Aim of the program: Write a program to read ‘n’ integers from a disc file that must contain
some  duplicate  values  and  store  them  into  an  array.  Perform  the  following  operations  on  the
array.
a) Find out the total number of duplicate elements.
b) Find out the most repeating element in the array.*/

#include <stdio.h>

int main()
{
    FILE *file;
    int n, i, j;
    int countDuplicates = 0;
    int maxCount = 0;
    int mostRepeatingElement;
    int numArray[100];      
    int frequency[100] = {0};
    file = fopen("input.txt", "r");
    if (file == NULL)
    {
        printf("Error\n");
        return 1;
    }
    printf("Enter the number of numbers you want to read from file: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        fscanf(file, "%d", &numArray[i]);
    }
    fclose(file);
    printf("The array: ");
    for (i = 0; i < n; i++)
    {
        printf("%d ", numArray[i]);
    }
    printf("\n");
    for (i = 0; i < n; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (numArray[i] == numArray[j])
            {
                frequency[i]++;
            }
        }
    }
    for (i = 0; i < n; i++)
    {
        if (frequency[i] > 0)
        {
            countDuplicates++;
        }
        if (frequency[i] > maxCount)
        {
            maxCount = frequency[i];
            mostRepeatingElement = numArray[i];
        }
        else 
        {
            printf("No element found.");
        }
    }
    printf("Total number of duplicate values = %d\n", countDuplicates);
    printf("The most repeating element in the array = %d\n", mostRepeatingElement);
    return 0;
}