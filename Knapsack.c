// // Greedy Techniques : Knapsack Algorithm
#include <stdio.h>
#include <stdlib.h>

struct ITEM
{
    int item_id;
    float item_profit;
    float item_weight;
    float profit_weight_ratio;
};

void heapify(struct ITEM arr[], int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && arr[left].profit_weight_ratio > arr[largest].profit_weight_ratio)
        largest = left;
    if (right < n && arr[right].profit_weight_ratio > arr[largest].profit_weight_ratio)
        largest = right;
    if (largest != i)
    {
        struct ITEM temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, n, largest);
    }
}
void heapSort(struct ITEM arr[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
    for (int i = n - 1; i >= 0; i--)
    {
        struct ITEM temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify(arr, i, 0);
    }
}
float fractionalKnapsack(struct ITEM items[], int n, float capacity)
{
    float total_profit = 0.0;
    for (int i = 0; i < n; i++)
    {
        if (capacity >= items[i].item_weight)
        {
            capacity -= items[i].item_weight;
            total_profit += items[i].item_profit;
            printf("%d %.6f %.6f %.6f\n", items[i].item_id, items[i].item_profit, items[i].item_weight, 1.0);
        }
        else
        {
            float fraction = capacity / items[i].item_weight;
            total_profit += items[i].item_profit * fraction;
            printf("%d %.6f %.6f %.6f\n", items[i].item_id, items[i].item_profit, items[i].item_weight, fraction);
            break;
        }
    }
    return total_profit;
}

int main()
{
    int n;
    float capacity;
    printf("Enter the number of items: ");
    scanf("%d", &n);
    struct ITEM *items = (struct ITEM *)malloc(n * sizeof(struct ITEM));
    for (int i = 0; i < n; i++)
    {
        items[i].item_id = i + 1;
        printf("Enter the profit and weight of item no %d: ", i + 1);
        scanf("%f %f", &items[i].item_profit, &items[i].item_weight);
        items[i].profit_weight_ratio = items[i].item_profit / items[i].item_weight;
    }
    printf("Enter the capacity of knapsack: ");
    scanf("%f", &capacity);
    heapSort(items, n);
    printf("Item No profit Weight Amount to be taken\n");
    float max_profit = fractionalKnapsack(items, n, capacity);
    printf("Maximum profit: %.6f\n", max_profit);
    free(items);
    return 0;
}