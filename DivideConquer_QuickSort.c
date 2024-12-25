// Divide & Conquer Method : Quick Sort
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int comparisons = 0;

void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++)
    {
        comparisons++;
        if (arr[j] < pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void quickSortDescending(int arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);

        quickSortDescending(arr, low, pi - 1);
        quickSortDescending(arr, pi + 1, high);
    }

    for (int i = 0; i < (high - low + 1) / 2; i++)
    {
        swap(&arr[low + i], &arr[high - i]);
    }
}

const char *checkScenario(int arr[], int low, int high, int pi)
{
    int leftSize = pi - low;
    int rightSize = high - pi;

    if (leftSize == 0 || rightSize == 0)
    {
        return "Worst-case";
    }
    else if (leftSize == rightSize)
    {
        return "Best-case";
    }
    else
    {
        return "Intermediate-case";
    }
}

int readFile(const char *filename, int arr[])
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        printf("Error opening file %s\n", filename);
        return -1;
    }

    int i = 0;
    while (fscanf(file, "%d", &arr[i]) != EOF)
    {
        i++;
    }

    fclose(file);
    return i;
}

void writeFile(const char *filename, int arr[], int n)
{
    FILE *file = fopen(filename, "w");
    if (!file)
    {
        printf("Error opening file %s\n", filename);
        return;
    }

    for (int i = 0; i < n; i++)
    {
        fprintf(file, "%d ", arr[i]);
    }

    fclose(file);
}

void displayFile(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        printf("Error opening file %s\n", filename);
        return;
    }

    int value;
    while (fscanf(file, "%d", &value) != EOF)
    {
        printf("%d ", value);
    }

    fclose(file);
    printf("\n");
}

void generateRandomArray(int arr[], int n, int maxElementCount)
{
    srand(time(NULL));
    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % maxElementCount;
    }
}

int main()
{
    int arr[500];
    int n;
    int choice;

    do
    {
        printf("MAIN MENU (QUICK SORT)\n");
        printf("1. Ascending Data\n");
        printf("2. Descending Data\n");
        printf("3. Random Data\n");
        printf("4. Exit\n");
        printf("Enter option: ");
        scanf("%d", &choice);

        const char *inputFilename;
        const char *outputFilename;

        switch (choice)
        {
        case 1:
            inputFilename = "input.txt";
            outputFilename = "SaveHere.txt";
            n = readFile(inputFilename, arr);
            if (n == -1)
            {
                continue;
            }
            break;

        case 2:
            inputFilename = "input.txt";
            outputFilename = "SaveHere.txt";
            n = readFile(inputFilename, arr);
            if (n == -1)
            {
                continue;
            }
            quickSortDescending(arr, 0, n - 1);
            break;

        case 3:
            printf("Enter the number of elements : ");
            scanf("%d", &n);
            outputFilename = "SaveHere.txt";
            generateRandomArray(arr, n, 1000); 
            quickSort(arr, 0, n - 1);
            break;

        case 4:
            printf("Exiting program.\n");
            exit(0);

        default:
            printf("Invalid choice! Try again.\n");
            continue;
        }

        printf("\nBefore Sorting:\n");
        displayFile(inputFilename);
        writeFile(outputFilename, arr, n);
        printf("\nAfter Sorting:\n");
        displayFile(outputFilename);
        printf("\nNumber of Comparisons: %d\n", comparisons);
        const char *scenario = checkScenario(arr, 0, n - 1, (n - 1) / 2);
        printf("\nScenario: %s\n", scenario);
        comparisons = 0;

    } while (choice != 4);

    return 0;
}
