// Write a program in c to implement job scheduling with deadlines and find out the maximum profit taking user inputs for number of processes, deadlines and profit. Apply heap sort technique to sort the items in non-increasing order, according to their profit / deadline and print it in tabular form.

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int id;     
    int deadline;
    int profit; 
} Job;

void swap(Job *a, Job *b)
{
    Job temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(Job arr[], int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && arr[left].profit > arr[largest].profit)
        largest = left;
    if (right < n && arr[right].profit > arr[largest].profit)
        largest = right;
    if (largest != i)
    {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(Job arr[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
    for (int i = n - 1; i >= 0; i--)
    {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

int findMaxDeadline(Job jobs[], int n)
{
    int max = jobs[0].deadline;
    for (int i = 1; i < n; i++)
    {
        if (jobs[i].deadline > max)
        {
            max = jobs[i].deadline;
        }
    }
    return max;
}

int jobScheduling(Job jobs[], int n)
{
    heapSort(jobs, n);
    int maxDeadline = findMaxDeadline(jobs, n);
    int slot[maxDeadline + 1];
    for (int i = 0; i <= maxDeadline; i++)
        slot[i] = -1;

    int totalProfit = 0;
    for (int i = n - 1; i >= 0; i--)
    {
        for (int j = jobs[i].deadline; j > 0; j--)
        {
            if (slot[j] == -1)
            {
                slot[j] = jobs[i].id;
                totalProfit += jobs[i].profit;
                break;
            }
        }
    }
    return totalProfit;
}
void printJobs(Job jobs[], int n)
{
    printf("\nSorted Jobs in Decreasing Order of Profit:\n");
    printf("Job ID\tDeadline\tProfit\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t\t%d\n", jobs[i].id, jobs[i].deadline, jobs[i].profit);
    }
}

int main()
{
    int n;
    printf("Enter the number of jobs: ");
    scanf("%d", &n);
    Job jobs[n];
    for (int i = 0; i < n; i++)
    {
        printf("Enter job ID, deadline, and profit for job %d: ", i + 1);
        scanf("%d %d %d", &jobs[i].id, &jobs[i].deadline, &jobs[i].profit);
    }
    heapSort(jobs, n);
    printJobs(jobs, n);
    int maxProfit = jobScheduling(jobs, n);
    printf("\nMaximum profit: %d\n", maxProfit);
    return 0;
}