#include "triangle.h"

void triangle()
{
    int num;
    scanf("%d", &num);
    int i = 1;
    while (i < num)
    {
        int j = i;
        while (j--)
            printf("\\");
        printf("\n");
        i++;
    }
}