/*Write a program in C to sort an array of elements from a file and search an element using binary search tree and find the time taken for loop execution in searching*/

#include <stdio.h>
#include <stdlib.h>

void readArrayFromFile(const char *filename, int arr[], int size)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("Unable to open file");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < size; i++)
    {
        fscanf(file, "%d", &arr[i]);
    }
    fclose(file);
}

void printArray(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void bubbleSort(int arr[], int size)
{
    int temp;
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - 1 - i; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int binarySearch(int arr[], int size, int element, int *count)
{
    int left = 0, right = size - 1;
    while (left <= right)
    {
        (*count)++;
        int mid = left + (right - left) / 2;
        if (arr[mid] == element)
        {
            return mid;
        }
        if (arr[mid] < element)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }
    return -1;
}

int main()
{
    int size;
    const char *filename = "input.txt";

    printf("Enter the size of the array: ");
    scanf("%d", &size);

    int arr[size];
    readArrayFromFile(filename, arr, size);

    printf("Array before sorting: ");
    printArray(arr, size);

    bubbleSort(arr, size);

    printf("Array after sorting: ");
    printArray(arr, size);

    int searchElement;
    printf("Enter the element to search for: ");
    scanf("%d", &searchElement);

    int count = 0;
    int result = binarySearch(arr, size, searchElement, &count);

    if (result != -1)
    {
        printf("Element %d found at index %d.\n", searchElement, result);
    }
    else
    {
        printf("Element %d not found in the array.\n", searchElement);
    }

    printf("Number of loop iterations for binary search: %d\n", count);

    return 0;
}
