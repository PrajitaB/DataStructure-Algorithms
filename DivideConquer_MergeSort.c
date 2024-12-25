// Divide & Conquer Method : Merge Sort
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int comparisons = 0;

unsigned long long rdtsc() // Count CPU Cycle
{
    unsigned int lo, hi;
    asm volatile("rdtsc" : "=a"(lo), "=d"(hi));
    return ((unsigned long long)hi << 32) | lo;
}

void merge(int arr[], int l, int m, int r, int descending)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;

    while (i < n1 && j < n2)
    {
        comparisons++;
        if (descending ? L[i] >= R[j] : L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

void mergeSort(int arr[], int l, int r, int descending)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m, descending);
        mergeSort(arr, m + 1, r, descending);
        merge(arr, l, m, r, descending);
    }
}

void readFile(const char *filename, int **arr, int *size)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    int temp, count = 0;
    while (fscanf(file, "%d", &temp) != EOF)
    {
        (*size)++;
        *arr = (int *)realloc(*arr, (*size) * sizeof(int));
        (*arr)[count++] = temp;
    }

    fclose(file);
}

void writeFile(const char *filename, int arr[], int size)
{
    FILE *file = fopen(filename, "w");
    if (!file)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < size; i++)
    {
        fprintf(file, "%d ", arr[i]);
    }

    fclose(file);
}

void generateRandomData(int **arr, int *size)
{
    srand(rdtsc());
    *size = 300 + rand() % 201;

    *arr = (int *)malloc(*size * sizeof(int));
    for (int i = 0; i < *size; i++)
    {
        (*arr)[i] = rand() % 1000;
    }
}

void displayArray(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main()
{
    int choice;
    char input_file[20], output_file[20];
    int *arr = NULL;
    int size = 0;

    while (1)
    {
        printf("MAIN MENU (MERGE SORT)\n");
        printf("1. Ascending Data\n");
        printf("2. Descending Data\n");
        printf("3. Random Data\n");
        printf("4. EXIT\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        int descending = 0;

        if (choice == 1)
        {
            strcpy(input_file, "input.txt");
            strcpy(output_file, "SaveHere.txt");
            readFile(input_file, &arr, &size);
            descending = 0;
        }
        else if (choice == 2)
        {
            strcpy(input_file, "input.txt");
            strcpy(output_file, "SaveHere.txt");
            readFile(input_file, &arr, &size);
            descending = 1;
        }
        else if (choice == 3)
        {
            strcpy(output_file, "SaveHere.txt");
            generateRandomData(&arr, &size);
            descending = 0;
        }
        else if (choice == 4)
        {
            printf("Exiting program.\n");
            break;
        }
        else
        {
            printf("Invalid choice, please try again.\n");
            continue;
        }

        printf("Before Sorting: ");
        displayArray(arr, size);

        comparisons = 0;

        unsigned long long start_time = rdtsc();
        mergeSort(arr, 0, size - 1, descending);
        unsigned long long end_time = rdtsc();

        unsigned long long time_spent_ns = (end_time - start_time);

        writeFile(output_file, arr, size);

        printf("After Sorting: ");
        displayArray(arr, size);

        printf("Sorting completed.\n");
        printf("Execution time: %llu ns\n", time_spent_ns);
        printf("Number of comparisons: %d\n", comparisons);

        free(arr);
        arr = NULL;
        size = 0;
    }

    return 0;
}
