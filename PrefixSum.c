/* Aim of the program: Given an array arr[] of size N, find the prefix sum of the array. A prefix 
sum array is another array prefixSum[] of the same size, such that the value of prefixSum[i] is 
arr[0] + arr[1] + arr[2] . . . arr[i]. */

#include <stdio.h>
#include <stdlib.h>

#define N 100000

int main()
{
    FILE *file;
    int *numbers;
    int *prefix_sum;
    int i, n;

    file = fopen("C:/Users/KIIT/Desktop/input.txt", "r");
    if (file == NULL)
    {
        perror("Error opening file");
        return 1;
    }

    if (fscanf(file, "%d", &n) != 1)
    {
        perror("Error reading number from file");
        fclose(file);
        return 1;
    }

    numbers = (int *)malloc(n * sizeof(int));
    if (numbers == NULL)
    {
        perror("Error");
        fclose(file);
        return 1;
    }

    prefix_sum = (int *)malloc(n * sizeof(int));
    if (prefix_sum == NULL)
    {
        perror("Error");
        free(numbers);
        fclose(file);
        return 1;
    }

    for (i = 0; i < n; i++)
    {
        if (fscanf(file, "%d", &numbers[i]) != 1)
        {
            perror("Error");
            free(numbers);
            free(prefix_sum);
            fclose(file);
            return 1;
        }
    }

    fclose(file);

    prefix_sum[0] = numbers[0];
    for (i = 1; i < n; i++)
    {
        prefix_sum[i] = prefix_sum[i - 1] + numbers[i];
    }

    for (i = 0; i < n; i++)
    {
        printf("%d ", prefix_sum[i]);
    }
    printf("\n");

    free(numbers);
    free(prefix_sum);

    return 0;
}