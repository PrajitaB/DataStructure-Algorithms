// Krushkal’s algorithm : Find the minimum spanning tree T(V, E’) and Display the selected edges of G and Display total cost of the minimum spanning tree T

#include <stdio.h>
#include <stdlib.h>

// Structure to represent an edge
struct Edge
{
    int u, v, w;
};

// Structure to represent a graph
struct Graph
{
    int V, E;           // Number of vertices and edges
    struct Edge *edges; // Array of edges
};

// Create a graph with V vertices and E edges
struct Graph *createGraph(int V, int E)
{
    struct Graph *graph = (struct Graph *)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->E = E;
    graph->edges = (struct Edge *)malloc(E * sizeof(struct Edge));
    return graph;
}

// Function to find set of an element i (uses path compression)
int find(int parent[], int i)
{
    if (parent[i] != i)
        parent[i] = find(parent, parent[i]);
    return parent[i];
}

// Function that does union of two sets (uses union by rank)
void unionSets(int parent[], int rank[], int x, int y)
{
    int rootX = find(parent, x);
    int rootY = find(parent, y);

    if (rank[rootX] < rank[rootY])
    {
        parent[rootX] = rootY;
    }
    else if (rank[rootX] > rank[rootY])
    {
        parent[rootY] = rootX;
    }
    else
    {
        parent[rootY] = rootX;
        rank[rootX]++;
    }
}

// Comparison function to sort edges by their weights
int compareEdges(const void *a, const void *b)
{
    struct Edge *edgeA = (struct Edge *)a;
    struct Edge *edgeB = (struct Edge *)b;
    return edgeA->w - edgeB->w;
}

// Function to implement Kruskal's algorithm to find MST
void kruskalMST(struct Graph *graph)
{
    int V = graph->V;
    struct Edge result[V]; // Array to store the resulting MST
    int parent[V + 1], rank[V + 1];
    int e = 0; // Counter for result[]
    int i = 0; // Counter for sorted edges

    // Initialize sets for each vertex
    for (int v = 1; v <= V; v++)
    {
        parent[v] = v;
        rank[v] = 0;
    }

    // Sort all edges by weight
    qsort(graph->edges, graph->E, sizeof(graph->edges[0]), compareEdges);

    // Iterate through all sorted edges
    while (e < V - 1)
    {
        struct Edge nextEdge = graph->edges[i++];
        int u = nextEdge.u;
        int v = nextEdge.v;

        int setU = find(parent, u);
        int setV = find(parent, v);

        // Check if including this edge will form a cycle
        if (setU != setV)
        {
            result[e++] = nextEdge;              // Include this edge in result
            unionSets(parent, rank, setU, setV); // Union the two sets
        }
    }

    // Print the edges of the MST and calculate total cost
    int totalWeight = 0;
    printf("Edge   Cost\n");
    for (i = 0; i < e; i++)
    {
        printf("%d--%d  %d\n", result[i].u, result[i].v, result[i].w);
        totalWeight += result[i].w;
    }
    printf("Total Weight of the Spanning Tree: %d\n", totalWeight);
}

int main()
{
    int V, E;
    printf("Enter the number of nodes and edges: ");
    scanf("%d %d", &V, &E);

    struct Graph *graph = createGraph(V, E);

    printf("Enter the edges (u, v, weight):\n");
    for (int i = 0; i < E; i++)
    {
        scanf("%d %d %d", &graph->edges[i].u, &graph->edges[i].v, &graph->edges[i].w);
    }

    // Apply Kruskal's algorithm
    kruskalMST(graph);

    return 0;
}