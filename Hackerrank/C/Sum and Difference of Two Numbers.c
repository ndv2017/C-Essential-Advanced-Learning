#include <stdio.h>
#include <string.h>

int main()
{
	int a, b;
	float m, n;
	scanf("%d %d %f %f", &a, &b, &m, &n);
	printf("%d %d\n%.1f %.1f", a + b, a - b, m + n, m - n);
	return 0;
}