#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
//Complete the following function.


void calculate_the_maximum(int n, int k) {
	int a = 1, b = 2, and = 0, or = 0, xor = 0;
	while (a < n)
	{
		while (b <= n)
		{
			if (and < (a & b) && (a & b) < k)	and = a & b;
			if (or < (a | b) && (a | b) < k) 	or = a | b;
			if (xor < (a ^ b) && (a ^ b) < k)	xor = a ^ b;
			
			b++;
		}
		a++;
		b = a + 1;
	}
	
	printf("%d\n%d\n%d", and, or, xor);
}

int main() {
	int n, k;
	
	scanf("%d %d", &n, &k);
	calculate_the_maximum(n, k);
	
	return 0;
}