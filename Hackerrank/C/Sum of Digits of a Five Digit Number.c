#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int recursion(int n)
{
	int modulo = n % 10;
	return n ? modulo + recursion(n / 10) : 0;
}

int main() 
{
	int n;
	scanf("%d", &n);
	
	printf("%d", recursion(n));   
	
	return 0;
}