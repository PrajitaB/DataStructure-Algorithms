// Prim’s algorithm : Find the minimum spanning tree T(V, E’). Display the cost adjacency matrix of ‘T’ and Display total cost of the minimum spanning tree T.

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 100

    void
    readGraph(const char *filename, int graph[MAX_VERTICES][MAX_VERTICES], int *numVertices)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        perror("Unable to open file");
        exit(EXIT_FAILURE);
    }

    fscanf(file, "%d", numVertices);
    for (int i = 0; i < *numVertices; i++)
    {
        for (int j = 0; j < *numVertices; j++)
        {
            fscanf(file, "%d", &graph[i][j]);
        }
    }

    fclose(file);
}

void primMST(int graph[MAX_VERTICES][MAX_VERTICES], int numVertices, int startVertex)
{
    int parent[MAX_VERTICES]; // Store the MST
    int key[MAX_VERTICES];    // Key values to pick minimum weight edge
    int mstSet[MAX_VERTICES]; // To track vertices included in MST

    for (int i = 0; i < numVertices; i++)
    {
        key[i] = INT_MAX;
        mstSet[i] = 0;
    }

    key[startVertex] = 0;
    parent[startVertex] = -1; // Starting vertex has no parent

    for (int count = 0; count < numVertices - 1; count++)
    {
        int minKey = INT_MAX, minIndex;
        for (int v = 0; v < numVertices; v++)
        {
            if (!mstSet[v] && key[v] < minKey)
            {
                minKey = key[v];
                minIndex = v;
            }
        }

        mstSet[minIndex] = 1;

        for (int v = 0; v < numVertices; v++)
        {
            if (graph[minIndex][v] && !mstSet[v] && graph[minIndex][v] < key[v])
            {
                parent[v] = minIndex;
                key[v] = graph[minIndex][v];
            }
        }
    }

    // Display the cost adjacency matrix of the MST
    int mstCost = 0;
    int mstAdjMatrix[MAX_VERTICES][MAX_VERTICES] = {0};

    for (int i = 1; i < numVertices; i++)
    {
        mstAdjMatrix[parent[i]][i] = graph[parent[i]][i];
        mstAdjMatrix[i][parent[i]] = graph[parent[i]][i];
        mstCost += graph[parent[i]][i];
    }

    printf("Cost Adjacency Matrix of the Minimum Spanning Tree:\n");
    for (int i = 0; i < numVertices; i++)
    {
        for (int j = 0; j < numVertices; j++)
        {
            printf("%d ", mstAdjMatrix[i][j]);
        }
        printf("\n");
    }
    printf("Total Weight of the Spanning Tree: %d\n", mstCost);
}

int main()
{
    int graph[MAX_VERTICES][MAX_VERTICES];
    int numVertices;
    int startVertex;

    // Read the graph from the file
    readGraph("inUnAdjMat.dat", graph, &numVertices);

    // User input for starting vertex
    printf("Enter the Number of Vertices: %d\n", numVertices);
    printf("Enter the Starting Vertex (1 to %d): ", numVertices);
    scanf("%d", &startVertex);
    startVertex--; // Convert to 0-based index

    primMST(graph, numVertices, startVertex);

    return 0;
}