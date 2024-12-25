// Write a program in C to implement the Binary Search (sorted array) using recursion and calculate the execution time

#include <stdio.h>
#include <stdlib.h>

int binarySearch(int ar[], int low, int high, int ele);
void selectionSort(int ar[], int n);
void printArray(int arr[], int size);
unsigned long long rdtsc();

int main()
{
    FILE *file;
    int i, size;

    printf("Enter the number of elements in the array: ");
    scanf("%d", &size);

    int ar[size];

    file = fopen("input.txt", "r");
    if (file == NULL)
    {
        printf("Error: Could not open file\n");
        return 1;
    }

    for (i = 0; i < size; i++)
    {
        if (fscanf(file, "%d", &ar[i]) != 1)
        {
            printf("Error reading number %d\n", i + 1);
            fclose(file);
            return 1;
        }
    }

    fclose(file);

    printf("The numbers read from the file are:\n");
    printArray(ar, size);

    selectionSort(ar, size);
    printf("Array after sorting:\n");
    printArray(ar, size);

    int ele;
    printf("Enter element to be searched: ");
    scanf("%d", &ele);

    int low = 0;
    int high = size - 1;

    unsigned long long start_time = rdtsc();

    int result = binarySearch(ar, low, high, ele);

    unsigned long long end_time = rdtsc();

    unsigned long long time_spent = end_time - start_time;

    if (result != -1)
    {
        printf("Element found at index %d\n", result);
    }
    else
    {
        printf("Element not found\n");
    }

    printf("Binary search execution time: %llu CPU cycles\n", time_spent);

    return 0;
}

int binarySearch(int arr[], int left, int right, int target)
{
    while (right >= left)
    {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target)
        {
            return mid;
        }

        if (arr[mid] > target)
        {
            right = mid - 1;
        }
        else
        {
            left = mid + 1;
        }
    }

    return -1;
}

void selectionSort(int ar[], int n)
{
    int i, j, minIndex, temp;

    for (i = 0; i < n - 1; i++)
    {
        minIndex = i;
        for (j = i + 1; j < n; j++)
        {
            if (ar[j] < ar[minIndex])
            {
                minIndex = j;
            }
        }

        if (minIndex != i)
        {
            temp = ar[minIndex];
            ar[minIndex] = ar[i];
            ar[i] = temp;
        }
    }
}

void printArray(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

unsigned long long rdtsc()
{
    unsigned int lo, hi;
    asm volatile("rdtsc" : "=a"(lo), "=d"(hi));
    return ((unsigned long long)hi << 32) | lo;
}
