#include <stdio.h>
#include <string.h>

int main()
{
	char ch, s[100], sen[100];
	scanf("%c%s%*c%[^\n]", &ch, s, sen);
	printf("%c\n%s\n%s", ch, s, sen);
	return 0;
}