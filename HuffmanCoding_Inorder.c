// Huffman Coding : Create Huffman Coding (In-order Travarsal)
#include <stdio.h>
#include <stdlib.h>

struct Node
{
    char alphabet;
    int frequency;
    struct Node *left, *right;
};

struct MinHeap
{
    int size;
    int capacity;
    struct Node **array;
};

struct Node *newNode(char alphabet, int frequency)
{
    struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
    temp->alphabet = alphabet;
    temp->frequency = frequency;
    temp->left = temp->right = NULL;
    return temp;
}

struct MinHeap *createMinHeap(int capacity)
{
    struct MinHeap *minHeap = (struct MinHeap *)malloc(sizeof(struct MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (struct Node *)malloc(minHeap->capacity * sizeof(struct Node));
    return minHeap;
}

void swapNode(struct Node **a, struct Node **b)
{
    struct Node *t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(struct MinHeap *minHeap, int idx)
{
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;
    if (left < minHeap->size && minHeap->array[left]->frequency < minHeap->array[smallest]->frequency)
        smallest = left;
    if (right < minHeap->size && minHeap->array[right]->frequency < minHeap->array[smallest]->frequency)
        smallest = right;
    if (smallest != idx)
    {
        swapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

struct Node *extractMin(struct MinHeap *minHeap)
{
    struct Node *temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    --minHeap->size;
    minHeapify(minHeap, 0);
    return temp;
}

void insertMinHeap(struct MinHeap *minHeap, struct Node *node)
{
    ++minHeap->size;
    int i = minHeap->size - 1;
    while (i && node->frequency < minHeap->array[(i - 1) / 2]->frequency)
    {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->array[i] = node;
}

struct MinHeap *createAndBuildMinHeap(char alphabet[], int frequency[], int size)
{
    struct MinHeap *minHeap = createMinHeap(size);
    for (int i = 0; i < size; ++i)
        minHeap->array[i] = newNode(alphabet[i], frequency[i]);
    minHeap->size = size;
    for (int i = (minHeap->size - 1) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
    return minHeap;
}

struct Node *buildHuffmanTree(char alphabet[], int frequency[], int size)
{
    struct Node *left, *right, *top;
    struct MinHeap *minHeap = createAndBuildMinHeap(alphabet, frequency, size);
    while (minHeap->size != 1)
    {
        left = extractMin(minHeap);
        right = extractMin(minHeap);
        top = newNode('$', left->frequency + right->frequency);
        top->left = left;
        top->right = right;
        insertMinHeap(minHeap, top);
    }
    return extractMin(minHeap);
}

void inOrderTraversal(struct Node *root)
{
    if (root)
    {
        inOrderTraversal(root->left);
        if (root->alphabet != '$')
            printf("%c ", root->alphabet);
        inOrderTraversal(root->right);
    }
}

int main()
{
    int n;
    printf("Enter the number of distinct alphabets: ");
    scanf("%d", &n);
    char alphabet[n];
    int frequency[n];
    printf("Enter the alphabets: ");
    for (int i = 0; i < n; ++i)
    {
        scanf(" %c", &alphabet[i]);
    }
    printf("Enter their frequencies: ");
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &frequency[i]);
    }
    struct Node *root = buildHuffmanTree(alphabet, frequency, n);
    printf("In-order traversal of the tree (Huffman): ");
    inOrderTraversal(root);
    printf("\n");
    return 0;
}