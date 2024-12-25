/*All Pairs Shortest Path : Floyd-Warshall Algorithm*/

#include <stdio.h>
#define INF 99999 // Representation of infinity

// Function to display the shortest path matrix
void displayMatrix(int n, int dist[n][n])
{
    printf("Shortest Path Weight Matrix:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (dist[i][j] == INF)
                printf("INF ");
            else
                printf("%d ", dist[i][j]);
        }
        printf("\n");
    }
}

// Function to print the shortest path from u to v
void printPath(int u, int v, int path[][v + 1])
{
    if (path[u][v] == -1)
    {
        printf("No path exists between %d and %d\n", u + 1, v + 1);
        return;
    }

    printf("Shortest Path from vertex %d to vertex %d: %d", u + 1, v + 1, u + 1);
    while (u != v)
    {
        u = path[u][v];
        printf(" --> %d", u + 1);
    }
    printf("\n");
}

// Floyd-Warshall algorithm
void floydWarshall(int n, int graph[n][n], int u, int v)
{
    int dist[n][n], path[n][n];

    // Initialize distance and path matrices
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == j)
                dist[i][j] = 0;
            else if (graph[i][j] != 0)
                dist[i][j] = graph[i][j];
            else
                dist[i][j] = INF;

            if (dist[i][j] == INF || i == j)
                path[i][j] = -1;
            else
                path[i][j] = j;
        }
    }

    // Floyd-Warshall algorithm
    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    path[i][j] = path[i][k];
                }
            }
        }
    }

    // Display shortest path weight matrix
    displayMatrix(n, dist);

    // Display shortest path from given vertices
    printf("\n");
    printf("Shortest Path from vertex %d to vertex %d: ", u, v);
    printPath(u - 1, v - 1, path);
    if (dist[u - 1][v - 1] == INF)
        printf("Path weight: INF\n");
    else
        printf("Path weight: %d\n", dist[u - 1][v - 1]);
}

int main()
{
    int n, u, v;
    FILE *file = fopen("inDiAdjMat2.dat", "r");

    if (!file)
    {
        printf("Error: Could not open input file.\n");
        return 1;
    }

    // Read number of vertices
    printf("Enter the number of vertices: ");
    scanf("%d", &n);

    // Read the adjacency matrix from the file
    int graph[n][n];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            fscanf(file, "%d", &graph[i][j]);
        }
    }
    fclose(file);

    // Get source and destination vertices
    printf("Enter the source and destination vertex: ");
    scanf("%d %d", &u, &v);

    // Run Floyd-Warshall algorithm and print result
    floydWarshall(n, graph, u, v);

    return 0;
}
