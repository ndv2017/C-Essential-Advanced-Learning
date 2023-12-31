		Hackerank - C language - Easy - 10 bài



~ "Hello World!" in C ~

		#include <stdio.h>

		int main()
		{
		    char str[100];
		    scanf("%[^\n]", str);
		    printf("Hello, World!\n%s", str);
		    return 0;
		}


~ Playing With Characters ~

		#include <stdio.h>
		#include <string.h>

		int main()
		{
		    char ch, s[100], sen[100];
		    scanf("%c%s%*c%[^\n]", &ch, s, sen);
		    printf("%c\n%s\n%s", ch, s, sen);
		    return 0;
		}


~ Sum and Difference of Two Numbers ~

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


~ Functions in C ~

		#include <stdio.h>

		int max_of_four(int a, int b, int c, int d)
		{
		    int max = a;
		    if (max < b)
		        max = b;
		    if (max < c)
		        max = c;
		    if (max < d)
		        max = d;
		    return max;
		}

		int main() {
		    int a, b, c, d;
		    scanf("%d %d %d %d", &a, &b, &c, &d);
		    int ans = max_of_four(a, b, c, d);
		    printf("%d", ans);
		    
		    return 0;
		}


~ Pointers in C ~

		#include <stdio.h>

		void update(int *a,int *b) {
		    (*a) = (*a) + (*b);
		    (*b) = (*a) - 2 * (*b);
		    if ((*b) < 0)   (*b) = - (*b);
		}

		int main() {
		    int a, b;
		    int *pa = &a, *pb = &b;
		    
		    scanf("%d %d", &a, &b);
		    update(pa, pb);
		    printf("%d\n%d", a, b);

		    return 0;
		}


~ Conditional Statements in C ~

		#include <stdio.h>

		int main()
		{
		    int n;  
		    scanf("%d", &n);
		    
		    if (n == 1)         printf("one");
		    else if (n == 2)    printf("two");
		    else if (n == 3)    printf("three");
		    else if (n == 4)    printf("four");
		    else if (n == 5)    printf("five");
		    else if (n == 6)    printf("six");
		    else if (n == 7)    printf("seven");
		    else if (n == 8)    printf("eight");
		    else if (n == 9)    printf("nine"); 
		    else                printf("Greater than 9");
		    
		    return 0;
		}

~ For Loop in C ~

		#include <stdio.h>
		#include <string.h>
		#include <math.h>
		#include <stdlib.h>



		int main() 
		{
		    int a, b;
		    scanf("%d\n%d", &a, &b);
		  	
		    for (int i = a; i <= b; i++)
		    {
		        if (i == 1)     printf("one\n");
		        else if (i == 2)     printf("two\n");
		        else if (i == 3)     printf("three\n");
		        else if (i == 4)     printf("four\n");
		        else if (i == 5)     printf("five\n");
		        else if (i == 6)     printf("six\n");
		        else if (i == 7)     printf("seven\n");
		        else if (i == 8)     printf("eight\n");
		        else if (i == 9)     printf("nine\n");
		        else i % 2 ? printf("odd\n") : printf("even\n");
		    }

		    return 0;
		}



~ Sum of Digits of a Five Digit Number ~

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


~ Bitwise Operators ~

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


~ Calculate the Nth term ~

		#include <stdio.h>
		#include <string.h>
		#include <math.h>
		#include <stdlib.h>

		int find_nth_term(int n, int a, int b, int c) {
		    if (n == 1)         return a;
		    else if (n == 2)    return b;
		    else if (n == 3)    return c;
		    else                return find_nth_term(n - 1, a, b, c) + find_nth_term(n - 2, a, b, c) + find_nth_term(n - 3, a, b, c);
		}

		int main() {
		    int n, a, b, c;
		  
		    scanf("%d %d %d %d", &n, &a, &b, &c);
		    int ans = find_nth_term(n, a, b, c);
		 
		    printf("%d", ans); 
		    return 0;
		}


~ Students Marks Sum ~

		#include <stdio.h>
		#include <string.h>
		#include <math.h>
		#include <stdlib.h>

		int marks_summation(int* marks, int number_of_students, char gender) {
		    int i = (gender == 'b' ? 0 : 1), s = *(marks + i);
		    while ((i += 2) <= number_of_students)
		        s += *(marks + i);
		   
		    return s;
		}

		int main() {
		    int number_of_students;
		    char gender;
		    int sum;
		  
		    scanf("%d", &number_of_students);
		    int *marks = (int *) malloc(number_of_students * sizeof (int));
		 
		    for (int student = 0; student < number_of_students; student++) {
		        scanf("%d", (marks + student));
		    }
		    
		    scanf(" %c", &gender);
		    sum = marks_summation(marks, number_of_students, gender);
		    printf("%d", sum);
		    free(marks);
		 
		    return 0;
		}


~ Boxes through a Tunnel ~

		#include <stdio.h>
		#include <stdlib.h>
		#define MAX_HEIGHT 41

		struct box
		{
			int length;
		    int width;
		    int height;
		};

		typedef struct box box;

		int get_volume(box b) {
			return b.height * b.length * b.width;
		}

		int is_lower_than_max_height(box b) {
			return b.height >= 41 ? 0 : 1;
		}

		int main()
		{
			int n;
			scanf("%d", &n);
			box *boxes = malloc(n * sizeof(box));
			for (int i = 0; i < n; i++) {
				scanf("%d%d%d", &boxes[i].length, &boxes[i].width, &boxes[i].height);
			}
			for (int i = 0; i < n; i++) {
				if (is_lower_than_max_height(boxes[i])) {
					printf("%d\n", get_volume(boxes[i]));
				}
			}
			return 0;
		}