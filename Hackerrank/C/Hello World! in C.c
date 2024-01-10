#include <stdio.h>

int main()
{
    char str[100];
    scanf("%[^\n]", str);
    printf("Hello, World!\n%s", str);
    return 0;
}
