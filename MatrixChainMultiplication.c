// Implement the matrix chain multiplication problem using M-table & S-table to find optimal parenthesization of a matrix-chain product. Print the number of scalar multiplications required for the given input. 

#include <stdio.h>
#include <limits.h>

void print_optimal_parenthesization(int s[][10], int i, int j)
{
    if (i == j)
        printf("A%d", i + 1);
    else
    {
        printf("(");
        print_optimal_parenthesization(s, i, s[i][j]);
        print_optimal_parenthesization(s, s[i][j] + 1, j);
        printf(")");
    }
}

int main()
{
    int n;

    printf("Enter number of matrices: ");
    scanf("%d", &n);

    int p[10];           
    int m[10][10] = {0}; 
    int s[10][10] = {0};

    for (int i = 0; i < n; i++)
    {
        int row, col;
        printf("Enter row and col size of A%d: ", i + 1);
        scanf("%d %d", &row, &col);
        p[i] = row;
        if (i == n - 1)
            p[n] = col; 
    }

    for (int len = 2; len <= n; len++)
    {
        for (int i = 0; i < n - len + 1; i++)
        {
            int j = i + len - 1;
            m[i][j] = INT_MAX;
            for (int k = i; k < j; k++)
            {
                int q = m[i][k] + m[k + 1][j] + p[i] * p[k + 1] * p[j + 1];
                if (q < m[i][j])
                {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }

    printf("\nM Table:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i <= j)
                printf("%d\t", m[i][j]);
            else
                printf("0\t");
        }
        printf("\n");
    }

    printf("\nS Table:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i < j)
                printf("%d\t", s[i][j]);
            else
                printf("0\t");
        }
        printf("\n");
    }

    printf("\nOptimal parenthesization: ");
    print_optimal_parenthesization(s, 0, n - 1);

    printf("\nThe optimal ordering of the given matrices requires %d scalar multiplications.\n", m[0][n - 1]);

    return 0;
}