/*Write a program in C to sort an array of elements from a file using insertion sort and find the execution time taken for best case and worst case*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void insertion_sort(int arr[], int n)
{
    for (int i = 0; i <= n - 1; i++)
    {
        int j = i;
        while (j > 0 && arr[j - 1] > arr[j])
        {

            int temp = arr[j - 1];
            arr[j - 1] = arr[j];
            arr[j] = temp;

            j--;
        }
    }
}

void printArray(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main()
{
    int n = 1000; 
    int *arr = (int *)malloc(n * sizeof(int));
    clock_t start, end;
    double cpu_time_used;

    // Best Case
    for (int i = 0; i < n; i++)
    {
        arr[i] = i;
    }
    start = clock();
    insertion_sort(arr, n);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Best Case Execution Time: %f seconds\n", cpu_time_used);

    // Worst Case 
    for (int i = 0; i < n; i++)
    {
        arr[i] = n - i;
    }
    start = clock();
    insertion_sort(arr, n);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Worst Case Execution Time: %f seconds\n", cpu_time_used);

    free(arr);
    return 0;
}