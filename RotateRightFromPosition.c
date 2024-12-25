/*Aim of the program: Write a function to ROTATE_RIGHT(p1, p2 ) right an array for first p2
elements by 1 position using EXCHANGE(p, q) function that swaps/exchanges the numbers p &
q. Parameter p1 be the starting address of the array and p2 be the number of elements to be
rotated.*/

#include <stdio.h>
void EXCHANGE(int *p, int *q)
{
    int temp = *p;
    *p = *q;
    *q = temp;
}
void ROTATE_RIGHT(int *p1, int p2)
{
    if (p2 <= 1)
        return;

    int lastElement = p1[p2 - 1];
    for (int i = p2 - 1; i > 0; i--)
    {
        EXCHANGE(&p1[i], &p1[i - 1]);
    }
    p1[0] = lastElement;
}
int main()
{
    int A[] = {11, 22, 33, 44, 55, 66, 77, 88, 99};
    int N = sizeof(A) / sizeof(A[0]);
    printf("Before ROTATE: ");
    for (int i = 0; i < N; i++)
    {
        printf("%d ", A[i]);
    }
    printf("\n");
    ROTATE_RIGHT(A, 5);
    printf("After ROTATE: ");
    for (int i = 0; i < N; i++)
    {
        printf("%d ", A[i]);
    }
    printf("\n");
    return 0;
}