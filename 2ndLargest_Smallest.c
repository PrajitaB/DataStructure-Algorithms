/*  Aim  of  the  program:  Write a program to find out the second smallest and second largest
element stored in an array of n integers.
Input: Size of the array is ‘n’ and read ‘n’ number of elements from a disc file.
Output: Second smallest, Second largest */

#include <stdio.h>
#include <limits.h>
void search(int arr[], int n, int *secondSmallest, int *secondLargest)
{
    int smallest = INT_MAX, largest = INT_MIN;
    *secondSmallest = INT_MAX;
    *secondLargest = INT_MIN;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] < smallest)
        {
            *secondSmallest = smallest;
            smallest = arr[i];
        }
        else if (arr[i] < *secondSmallest && arr[i] != smallest)
        {
            *secondSmallest = arr[i];
        }
        if (arr[i] > largest)
        {
            *secondLargest = largest;
            largest = arr[i];
        }
        else if (arr[i] > *secondLargest && arr[i] != largest)
        {
            *secondLargest = arr[i];
        }
    }
}
int main()
{
    FILE *file;
    file = fopen("C:/Users/KIIT/Desktop/DAA Lab/input.txt", "r");
    if (file == NULL)
    {
        printf("Error\n");
        return 1;
    }
    int n;
    fscanf(file, "%d", &n);
    int arr[n];
    for (int i = 0; i < n; i++)
    {
        fscanf(file, "%d", &arr[i]);
    }
    fclose(file);
    int secondSmallest, secondLargest;
    search(arr, n, &secondSmallest, &secondLargest);
    printf("Second smallest element: %d\n", secondSmallest);
    printf("Second largest element: %d\n", secondLargest);
    return 0;
}