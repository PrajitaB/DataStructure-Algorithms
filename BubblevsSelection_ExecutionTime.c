/*WAP in C to compare the execution time taken by the two sorting technique : bubble sort & selection sort*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void bubble_sort(int arr[], int n)
{
    for (int i = n - 1; i >= 1; i--)
    {
        int swap = 0;
        for (int j = 0; j <= i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j + 1];
                arr[j + 1] = arr[j];
                arr[j] = temp;
                swap = 1;
            }
        }
        if (swap == 0)
        {
            break;
        }
    }
}
void selection_sort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int min = i;
        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[min])
            {
                min = j;
            }
        }
        int temp = arr[min];
        arr[min] = arr[i];
        arr[i] = temp;
    }
}
int main(int argc, char const *argv[])
{
    srand(time(0));
    int n = 20000;
    int *arr = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % n;
    }
    clock_t t1, t2;
    double t;
    t1 = clock();
    bubble_sort(arr, n);
    t2 = clock();
    t = (double)(t2 - t1) / CLOCKS_PER_SEC;
    printf("Time complexity for bubble sort will be %lf\n", t);
    t1 = clock();
    selection_sort(arr, n);;
    t2 = clock();
    t = (double)(t2 - t1) / CLOCKS_PER_SEC;
    printf("Time complexity for selection sort will be %lf\n", t);
    free(arr);
    return 0;
}