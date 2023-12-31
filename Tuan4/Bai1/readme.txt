		C Essentials - Part 2 (Intermediate)


~ Module 6 ~

6.1.1.3 The structures: why?
	- STRUCTURE: là tập hợp các elements có các types khác nhau.
	- Structure chứa số lượng bất kì của những elements có type bất kì.
	- Mỗi element gọi là FIELD, identified bởi name, không phải bởi number của nó.
	- Field names phải là duy nhất, không có nhân bản trong 1 structure.

	- Ví dụ khai báo 1 structure (Declaration of structure):

		struct STUDENT
		{
    		char  name[26];
	    	float time;
	    	int   recent_chapter;
		};

			Trong đó:
				keyword: 	struct
				struct tag: STUDENT (tên của struct - nên viết hoa)
				3 fields: 	name, time và recent_chapter
				kết thúc declaration phải có semicolon ";"

		--> Ví dụ trên chỉ mô tả structure sẽ dùng, không phải khai báo variable.


6.1.1.4

	- Khai báo một variable theo structure (structured variable):

		struct STUDENT stdnt;

	- Access vào named fields của stdnt bằng cách dùng dấu "." (selection operator):

		stdnt.time = 1.5;


6.1.1.5
	- Hầu như tất cả data đều có thể dùng như một structure's field, ngoại trừ structure không thể là field của chính nó.
	- Structure có thể được chứa trong array như sau:

		struct STUDENT stdnt[100000];

	- Access vào fields được chọn:

		stdnt[0].time

	- Example:
		strcpy(stdnts[0].name, "Bond");
		stdnts[0].time = 3.5;
		stdnts[0].recent_chapter = 4;


6.1.1.6
	- Đồng thời define một structure tag và declare số lượng variables bất kì trong một câu lệnh:

		struct DATE
		{
    		int year, month, day;
		} DateOfBirth, visits[100];

	- Declare struct không cần tag (DATE) cũng được nhưng khi phải xác định loại biến của variable sẽ rất phiền, ví dụ như dùng sizeof:

		sizeof(struct {int year, month, day;})

	thay vì thế thì nên:

		sizeof(struct DATE)


6.1.1.7
	- Một structure có thể là field của một structure khác.
		struct STUDENT 
		{
		    char  name[26];
		    float time;
		    int   recent_chapter;
		    struct DATE last_visit;
		} HarryPotter;


6.1.2.1 Declaring and initializing structures
	- Structure's field có thể trùng với tag names:

		struct STRUCT
		{
    		int STRUCT;
		} Structure;

		Structure.STRUCT = 0; /* STRUCT is a field name here */


6.1.2.2 Structures - a few important rules
	- Không nên để structure's tag name trùng với variable's name như này:

		struct STR
		{
			int field;
		} Structure;
		int STR;

		Structure.field = 0;
		STR = 1;


6.1.2.3
	- 2 structures có thể chứa fields trùng tên:

		struct
		{ 
			int f1;
		} str1;

		struct 
		{
		 	char f1;
		} str2;

		str1.f1 = 32;
		str2.f1 = str1.f1;


6.1.2.4 Initializing structures
	- Example:

		struct DATE date = {2012, 12, 21};

	- Initiator trên tương đương với:

		date.year = 2012;
		date.month = 12;
		date.day = 21;

	- Có thể khởi tạo structured variable đơn giản như sau:

		struct STUDENT he = { "Bond", 3.5, 4, 2012, 12, 21 };

	- Cũng có thể như này (curly brackets chỗ 2012 có thể omit):

		struct STUDENT she = { "Mata Hari", 12., 12, { 2012 }  

			lúc này thì year sẽ là 2012, còn month và day tự động bằng 0.

	- Khởi tạo một variable trống:

		strruct STUDENT nobody = {};


6.1.3.1 Pointers to structures and arrays of structures
	- Declare một pointer đến structures of type struct STUDENT:

		struct STUDENT *sptr;

	- Cấp phát bộ nhớ cho 1 structure:

		sptr = (struct STUDENT *) malloc(sizeof(struct STUDENT));

	- Vì selector operator "." có mức độ ưu tiên rất cao, cao hơn deference operator "*" nên thao táo:

		*sptr.time

	tương đương với thao táo:

		*(sptr.time)

	viết như vậy chtrinh sẽ hiểu sprt là 1 structure, trong khi nó không phải như thế.

	- Do vậy ta phải thao tác như sau:

		(*sptr).time


6.1.3.2
	- Access field thông qua pointer sử dụng toán tử "->" như sau:

		pointer -> field

	tương đương với:

		(*pointer).field

	- Example:

		trcpy(sptr -> name, "Dobby");
		sptr -> time = 0.1;
		sptr -> recent_chapter = 0;
		sptr -> last_visit.year = 2002;
		sptr -> last_visit.month = 1;
		sptr -> last_visit.day = 1;


6.1.3.3
	- Giới thiệu union - incarnation of structure:

		struct {
			int a;
			int b;
		} Data1;
		union {
			int a;
			int b;
		} Data2;

	hầu như là giống nhau, sự khác biệt nằm ở phần computer's memory, sẽ được đề cập sau.


6.1.3.4
	- Trong 1 structure, các fields được đặt nối tiếp nhau. Mỗi field chiếm phần computer memory riêng, không trùng lặp nhau. Nếu sửa đổi field này thì field kia vẫn giữa nguyên.
	- Size của structure >= tổng size của tất cả fields của nó.

	- Còn với union, tất cả fields đều cùng memory location, do đó contents của các fields không thể phân biệt được với nhau.
	- Vì vậy bộ khởi tạo union phải có 1 element (vì chỉ có một value để khởi tạo).
	- Sửa đổi trường này cũng là sửa đổi trường kia ngay lập tức (đồng thời).

		#include <stdio.h>

		int main(void) 
		{
			struct
			{
				int a;
				int b;
			} Data1 = { 0, 0 };

			union
			{
				int a;
				int b;
			} Data2 = { 0 };
			
			Data1.a++;
			Data2.a++;
			printf("%d %d\n", Data1.b, Data2.b);
			return 0;
		}

	OUTPUT của chtrinh trên:

		0 1


6.1.3.5
	- Nếu 2 fields của union cùng type thì sẽ có tính chất như trên, nhưng nếu khác type thì như ví dụ sau:

		#include <stdio.h>

		int main(void) {
			
			union {
				int a;
				float b;
			} Data;

			scanf("%d", &Data.a);
			printf("\n%f\n", Data.b);
			return 0;
		}

	- Tóm lại, các điểm khác nhau giữa union và structure:
		. size of memory:
			struct: tổng sizes của all members.
			union: chỉ max member size mới quan trọng.

		. Mỗi lần chỉ có thể access 1 member của union, còn struct thì all members

		. 1 union chỉ chứa 1 value, 1 struct chứa tất cả values của members


6.1.3.6 Basics of recursive data collections
	- Bất kỳ structure's fields nào cũng có thể là pointer đến structure đang được khai báo.

		struct ELEMENT {
		    int value;
		    struct ELEMENT *next;
		};

	- Đây gọi là RECURSIVE DECLARATION (KHAI BÁO ĐỆ QUY), vì entity được khai báo sẽ tham chiếu chính nó trước khi khai báo hoàn tất.


6.1.3.7
	- Kiểu dữ liệu ONE-WAY LINKED LIST
	- Ý tưởng: Nếu có nhiều dữ liệu (e.g. Int), ta có thể link chúng với nhau, như các hạt trong chuỗi và đính chuỗi vào những điểm cố định.

	- Example: Data được thiết kế phân luồng một cách cụ thể 
		. Threaded elements là structures với cùng type.

		. Mỗi structures chứa 1 giá trị integer (việc này là cho mục đích học tập, còn real data đương nhiên phức tạp hơn).

		. Mỗi structure sẽ có một "móc" - thứ giúp attach đến hạt tiếp theo trong chuỗi, giống như một lỗ kim để kéo sợi chỉ qua.

		. Một field cụ thể sẽ chứa pointer chỉ đến element tiếp theo trong chuỗi.

		. hạt phải được attach vĩnh viễn nên cần có "đinh", và đóng vai trò này sẽ là 1 pointer variable thường được gọi là "head" hay "list header".

	- Quay lại với khai báo structure ELEMENT:
		. "value" sẽ dùng để lưu trữ giá trị cần thiết.

		. "next" sẽ dùng để attach đến structure tiếp theo trong chain.

		. structure đầu tiên được attached vào "head" variable, được khai báo như sau:

			struct ELEMENT *head;

		. structure cuối cùng sẽ được attached vào nothing, vì vậy ta gán NULL pointer value cho "next" field của nó


6.1.3.8
	- Thực hiện in các giá trị ghi trong list. Không thể truy cập bất kì element nào thông qua số của nó, mà phải duyệt qua tất cả các phần tử trước nó:
		. dùng "head" variable để access element đầu tiên.
		. dùng "next" field để access element thứ hai.
		. dùng "next" field của element thứ n - 1 để access element thứ n.

	- Snippet bên dưới thực hiện lặp lại tất cả elements trong list và in ra field value của mỗi element:

		struct ELEMENT 
		{
			int value;
			struct ELEMENT *next;
		};

		struct ELEMENT *head, *ptr;		/* the head points to element #1 */

		ptr = head;
		
		while(ptr != NULL)
		{ 
		    printf("value = %d\n", ptr -> value);
		    ptr = ptr -> next;
		}

		printf("done!");


6.1.4.2 Scalars as function parameters
	- Về mặt hình thức, tham số có thể được thay đổi qua function:

		#include <stdio.h>

		void function(int param)
		{
		    printf("I've received value %d\n", param);
		    param++;
		}

		int main(void)
		{
		    int variable = 111;

		    function(variable);
		    printf("variable %d\n", variable);
		    return 0;
		}

	=> Tuy vậy nó không thay đổi giá trị của variable ban đầu được gán, OUTPUT của variable trong snippet trên vẫn là 111.


6.1.4.3
	- Function không thể thay đổi giá trị thực của thông số.
	- Giá trị của tham số thực được copy vào tham số hình thức. Thay đổi tham số hình thức sẽ không tác động gì đến tham số thực.
	- Hai tham số này là hai entities riêng biệt, và sự tương tác duy nhất giữa chúng là khi gọi hàm.

	=> Kiểu tương tác này chính là by-value parameter passing (truyền tham số theo giá trị).

	- Tuy vậy vẫn xử lí nó được bằng cách dùng pointers. Đó là cách hàm scanf lấy value từ user rồi gán vào biến
	- Example:

		void function(int *p)
		{
			*p += 100;
		}

		int main()
		{
			int n = 11;
			function(&n);
			printf("%d", n);
			
			return 0;
		}


6.1.4.4 -> 6.1.4.6
	- Khi ta gọi function thì thông số giá trị thực của nó sẽ không đổi. Trong trường hợp này chính là con trỏ p sẽ không đổi, nhưng ta lấy giá trị của nó bằng cách dùng *p trong hàm, như vậy thì giá trị của n đã được thay đổi trong hàm thành công.


6.1.5.1 -> 6.1.5.2 Structures and strings as function parameters
	- Structure cũng truyền theo giá trị, giống như scalars. Tức là fields của nó cũng không đổi sau khi gọi hàm
	- Tuy vậy ta cũng có thể dùng pointer trong structure như một thông số thực:
		
		struct ELEMENT
		{
			int value;
		};

		void func(struct ELEMENT *p)
		{
			p->value = 2;
		}

		int main()
		{
			struct ELEMENT str;
			str.value = 1;
			func(&str);
		}
		

6.1.5.3
	CÁC THAM SỐ HÀM LÀ MẢNG MỘT CHIỀU (ONE-DIMENSIONAL ARRAYS)

	- Array luôn được truyền dưới dạng pointer tới phần tử đầu tiên
	- Tên của array cũng chính là pointer chỉ tới phần tử đầu tiên
	- Khi dùng hàm với arr:

		void plus4(int *ptrarr)			// ptrarr = arr và đều là pointer chỉ arr[0]
		{
			int i = 0;
			for (int i = 0; i < 4; i++)
				ptrarr[i] += 4;
		}

		int main()
		{
			int arr[4] = {0, 1, 2, 3};
			
			plus4(arr);
			for (int i = 0; i < 4; i++)
			{
				printf("%d ", arr[i]);
			}
			printf("\n");
		}


		Ngoài ra có thể declare formal parameter như:

			void plus4(int arr[]);		// compiler sẽ hiểu cái này tương đương với *ptrarr


6.1.5.4
	- Function gửi pointer tới array dưới dạng tham số không thể biết được số lượng phần tử array đang chứa. Do đó toán tử "sizeof" cũng không thể dùng được


6.1.5.5
	- String là một special type của array:
		. là array of type "char"
		. array content phải kết thúc với ký tự '\0'
	- Tự tạo một hàm mystrlen():

		int mystrlen(char str[])
		{
			int cnt = 0, i = 1;
			char c = str[0];
			while (c)				// tương đương với (c != '\0')
			{
				cnt++;
				c = str[i];
				i++;
			}

			return cnt;
			
		}


6.1.5.6 -> 6.1.5.10
	MAKING IMPROVEMENTS

	- Improvement #1:

			while (*str != '\0')

		đổi thành

			while (*str)

	- Improvement #2:
			while(*str)
			{
		        counter++;
		        str++;
		    }

	    đổi thành

			while(*str++)
			{
		        counter++;
		    }

	- Improvement #3:
		Mô tả dưới dạng "for" loop

			int alter(char *str)
			{
				int cnt;

				for (cnt = 0; *str++; cnt++)
					;
				
				return cnt;
			}

		Chú ý: Trong loop's body không chứa instructions (tức là nó trống), và encode (mã hóa) dưới dạng 1 ";". Semicolon được gọi trong 1 empty instruction, không có bất kỳ tác dụng nào.

	- Improvement #4:
		. Để ý redundancy (sự dư thừa) ở snippet trên, ta tăng 2 values riêng biệt là cnt và str.
		. Simplify algorithm và chỉ tăng 1 variable:

			int alter(char *str)
			{
				int cnt;
				
				for (cnt = 0; str[cnt]; cnt++)
					;
				
				return cnt;
			}

	- Improvement #5:
		. Tăng pointer và loại bỏ hoàn toàn cnt khỏi code:
		. Cần 1 pointer để trỏ đến đầu string

			int alter(char *str)
			{	char *begin = str;

				for (; *str; str++)
					;
				
				return str - begin;
			}


6.1.5.11
	- Original function của "strcpy" function có prototype (nguyên mẫu) như sau:

		char *strcpy(char *destination, char *source);

	- Tạo một function tên "mystrcpy":

		char *mystrcpy(char *destination, char *source)
		{
			char *res = destination;

			for ( ; ; )
			{
				*destination = *source;
				if (*source == '\0')	break;
				destination++;
				source++;
			}

			return res;
		}


		int main()
		{
			char source[10] = "Vionce";
			char destination[10] = {};

			mystrcpy(destination, source);
			printf("%s", destination);


			return 0;

		}


6.1.5.12
	- Shorten function ở "for" loop:

		for ( ; ; )
			{
				if (!(*destination = *source))	break;		// thực hiện assign 2 pointers và check *source có bằng '\0' không
				destination++;
				source++;
			}


6.1.5.13
	- Implement code in a more comprehensive way:

		char *mystrcpy(char *destination, char *source)
		{
			char *res;

			for (res = destination; *destination = *source; )
			{
				destination++;
				source++;
			}

			return res;
		}


6.1.5.14
	- Và 1 alternative, more compact way (gọn hơn) để implement:

		char *mystrcpy(char *destination, char *source)
		{
			char *res;

			for (res = destination; *destination++ = *source++; )
				;

			return res;
		}


6.1.5.15
	- Prototype của "strcat" function:

		char *strcat (char *destination, char *source);

	- Tạo một own version của "strcat" function:

 		char *mystrcat(char *destination, char *source)
		{
			char *res;
			for (res = destination; *destination++; )
				;
			
			for (--destination; *destination++ = *source++; )
				;

			return res;
		}


6.1.5.16 LAB: Structures
	- Viết một chtrinh tạo firstname, lastname của 4 người và print ra:

		/* ~ Vion ~ Learning ~ */

		#include <stdio.h>
		#include <stdlib.h>
		#include <string.h>

		struct PERSON
		{
			char firstname[10];
			char lastname[10];
			int value;
			struct PERSON *next;
		};

		void assign(struct PERSON *ptr, char first[10], char last[10], int v, struct PERSON *alterptr)
		{
			strcpy(ptr->firstname, first);
			strcpy(ptr->lastname, last);
			ptr->value = v;
			ptr->next = alterptr;
		}

		void print(struct PERSON *ptr)
		{
			while (ptr)
			{
				printf("%s %s\n", ptr->firstname, ptr->lastname);
				ptr = ptr->next;
			}
		}

		int main()
		{
			struct PERSON *person1 = (struct PERSON *)malloc(sizeof(struct PERSON));
			struct PERSON *person2 = (struct PERSON *)malloc(sizeof(struct PERSON));
			struct PERSON *person3 = (struct PERSON *)malloc(sizeof(struct PERSON));
			struct PERSON *person4 = (struct PERSON *)malloc(sizeof(struct PERSON));


			assign(person1, "Mary", "Smith", 1, person2);
			assign(person2, "James", "Johnson", 2, person3);
			assign(person3, "Patricia", "Williams", 3, person4);
			assign(person4, "John", "Brown", 4, NULL);

			print(person1);


			free(person1);
			free(person2);
			free(person3);
			free(person4);

			return 0;
		}


6.1.5.17
	- Check the program in the editor. Add code to print all the neighbors in ascending and descending order. Use only pointers and loops (don't use the houseX variables).

		/* ~ Vion ~ Learning ~ */

		#include <stdio.h>
		#include <stdlib.h>

		struct house
		{
			int houseNumber;
			struct house *previous;
			struct house *next;
		};

		int main(void)
		{
			struct house house1;
			struct house house2;
			struct house house3;
			struct house house4;
			house1.houseNumber = 1;
			house2.houseNumber = 3;
			house3.houseNumber = 5;
			house4.houseNumber = 7;
			house1.next = &house2;
			house2.next = &house3;
			house3.next = &house4;
			house4.next = NULL;
			house1.previous = NULL;
			house2.previous = &house1;
			house3.previous = &house2;
			house4.previous = &house3;
			struct house *firstHouse = &house1;
			struct house *lastHouse = &house4;
			struct house *current;
			
			\\ My code:
			printf("Ascending order:\n");
			struct house *ptr = &house1;
		    while (ptr)
			{
				printf("%d\n", ptr->houseNumber);
				ptr = ptr->next;
			}

			printf("Descending order:\n");
			ptr = &house4;
			while (ptr)
			{
				printf("%d\n", ptr->houseNumber);
				ptr = ptr->previous;
			}

			\\ done.
			return 0;
		}


6.1.5.18
	- Write a program that creates a FIFO queue and prints some values. For this lab, use structures, pointers to structures and the malloc function.

		/* ~ Vion ~ Learning ~ */

		#include <stdio.h>
		#include <stdlib.h>

		struct ELEMENT
		{
			int value;
			struct ELEMENT *next;
		};

		void assign(struct ELEMENT *ptr, int i, struct ELEMENT *nextElement)
		{
			ptr->value = i;
			ptr->next = nextElement;
		}

		void print(struct ELEMENT *p, int num)
		{
			printf("First %d values\n", num);
			while (num--)
			{
				printf("%d\n", p->value);
				p = p->next;
			}
		}

		int main()
		{
			int values[10] = { 2, 4, 5, 6, 7, 8, 9, 1, 3, 0};

			struct ELEMENT *arrptr[10];

			for (int i = 0; i < 10; i++)
				arrptr[i] = (struct ELEMENT *)malloc(sizeof(struct ELEMENT));

			for (int i = 0; i < 9; i++)
				assign(arrptr[i], values[i], arrptr[i + 1]);

			assign(arrptr[6], values[6], NULL);

			print(arrptr[0], 5);
			print(arrptr[0], 7);

			for (int i = 0; i < 10; i++)
				free(arrptr[i]);

			printf("Memory is freed.");

			return 0;
		}


6.1.6.1 -> 6.1.6.3 Arrays as function parameters
	- Khai báo một multidimensional array:

		int arr[3][3];

	- Và print array ra một cách dễ hiểu:

		void printarr( ??? )
		{
		    int i, j;

		    for(i = 0; i < 3; i++)
		    {
		        for(j = 0; j < 3; j++) 
		            printf("%d ", t[i][j]);

		        printf("\n");
		    }
		}


6.1.6.4
	- Hàm printarr không cần thiết phải biết có bao nhiêu hàng, nhưng nó phải biết có bao nhiêu cột. Do đó printarr's prototype sẽ như sau:

		void printarr(int arr[][3]);

	=> Universal principal (Nguyên tắc phổ quát):
		Nếu khai báo 1 formal parameter là 1 array, được phép disregard thông tin size của first dimension, nhưng phải cung cấp tất cả sizes còn lại


6.1.6.7
	- Cũng như trên nhưng ta sẽ làm việc cùng với một array of pointers *arr[3]:

		void printarrptr(int **t)								// t là con trỏ chỉ đến con trỏ
		{
		    int i, j;
		    for(i = 0; i < 3; i++) 
		    {
		        for(j = 0; j < 3; j++) 
		            printf("%d\t",t[i][j]);

		        printf("\n");
		    }
		}

		int main(void) 
		{
		    int *arrptr[3];
		    int i, j;

		    for(i = 0; i < 3; i++) 
		    {
		        arrptr[i] = (int *) malloc(3 * sizeof(int));	// arrptr[i][j] là kiểu int, không phải pointer

		        for(j = 0; j < 3; j++)
		            arrptr[i][j] = (3 * i) + j + 1;				// output 1 2 3; 4 5 6; 7 8 9; theo kiểu 2 chiều
		    }

		    printarrptr(arrptr);
		    for(i = 0; i < 3; i++)
		        free(arrptr[i]);
		    return 0;
		}


6.1.7.1 Parameterizing the main function
	Tham số hóa "main" function

	- Khai báo "int main(void)" không còn sử dụng nhiều vì nó không retrieved (truy vấn) dữ liệu từ người dùng tại thời điểm bắt đầu

	- Ví dụ như "dir" command (Win) hay "ls" command (Linux), các lệnh này vẫn chạy khi có hoặc không có arguments.

		Windows: c:\windows> dir
		Linux: user@host:~$ ls

	- Bây giờ có arguments:

		Windows: c:\windows> dir /w
		Linux: user@host:~$ ls -lR

	- Để arguments có thể được retrieved và interpreted bởi chương trình thì phải có cơ chế truyền command-line arguments (đối số dòng lệnh) được tích hợp trong hàm main, và hàm main phải khai báo như sau:

		int main(int argc, char *argv[]);

	. argc (argument counter - bộ đếm đối số):
		Chứa số lượng arguments truyền vào chương trình cộng thêm 1, tức là 1 chương trình chạy mà không có đối số nào thì argc parameter value là 1.

	. argv (argument values - giá trị đối số):
		Array of pointers tới strings chứa các arguments được cung cấp cho chương trình, chúng được lưu trữ như sau:

			argv[0]: chứa tên của chương trình đang chạy
			argv[1]: chứa string được truyền vào chương trình dưới dạng first argument
			argv[n]: chứa string được truyền vào chương trình dưới dạng n-th argument


6.1.7.3
	- Simple code print all arguments trong 1 column:

		#include <stdio.h>

		int main(int argc, char *argv[]) {
		    int i;

		    for(i = 0; i < argc; i++)
		        printf("%s\n", argv[i]);
		    return 0;
		}

	- Mở lại để xem ví dụ cụ thể khi hoạt động
		https://edube.org/learn/c-essentials-part-2/parameterizing-the-main-function-6


6.1.7.5 -> 6.1.7.8 LAB (làm lại)


6.1.8.1 -> 6.1.8.4 The basics of disjoint compilation
	- Tạo một factorial function để tính giai thừa của số n, dùng recursion:

		int factorial(int n) 
		{
		    if(n == 1)
		        return 1;
		    else
		        return n * factorial(n – 1);
		}


6.1.8.5
	- Three-argument operator: "?:"

		expression1 ? expression2 : expression3


6.2.8.6
	- Modify code một cách gọn hơn:

		int factory(int n)
		{
			return n ? n * factory(n - 1) : 1;
		}


6.1.8.7 -> 6.1.8.10
	File .c và .h, include file .h
	Thực hành bên Ubuntu


6.1.8.11 LAB



~ Module 7 ~

7.1.1.1
	In this module, you will learn about:

	- files vs. streams,
	- header files needed for stream operations,
	- the "FILE" structure,
	- opening and closing streams, open modes, the errno variable,
	- reading and writing to/from a stream,
	- predefined streams: "stdinstdout", and "stderr",
	- stream manipulation: the fgetc(), fputc(), fgets(), and fputs() functions,
	- raw input/output: the fread(), and fwrite() functions.


7.1.1.2 File systems: definitions and conventions
	- Một trong những vấn đề phổ biến nhất trong công việc của programmer là xử lý dữ liệu được lưu trữ trong tệp. Hãy tưởng tượng một chương trình sắp xếp 20 số và người dùng chương trình này nhập 20 số này trực tiếp từ bàn phím. Bây giờ hãy tưởng tượng nhiệm vụ tương tự khi có 20.000 số cần sắp xếp – không có người dùng nào có thể nhập những số này mà không mắc lỗi. Sẽ dễ hình dung hơn nhiều khi những con số này được lưu trữ trong tệp đĩa được chương trình của bạn đọc.

	- Nếu chúng ta muốn triển khai ngay cả những cơ sở dữ liệu đơn giản nhất, cách duy nhất để lưu trữ thông tin giữa các lần chạy chương trình là lưu nó vào một tệp (hoặc các tệp, nếu cơ sở dữ liệu của bạn phức tạp hơn). Về nguyên tắc, hầu hết mọi vấn đề lập trình đều dựa vào việc sử dụng tệp, cho dù nó xử lý hình ảnh (được lưu trữ trong tệp), nhân ma trận (được lưu trữ trong tệp) hay tính toán tiền lương và thuế (đọc dữ liệu được lưu trữ trong tệp).


7.1.1.3
	NAMES OF FILES

	- Hệ điều hành khác nhau xử lý files khác nhau. Ví dụ Win và Linux quy ước đặt tên khác nhau, e.g.:

		Notion of canonical file name:

		. Win: C:\directory\file
		. Linux: /directory/files

	- Ngoài ra, tên files của hệ thống Unix thì case sensitive (phân biệt chữ hoa chữ thường), còn Win thì không

	- Sự khác biệt chính và striking (nổi bật) nhất là phải sử dụng 2 separators (dấu phân cách) khác nhau cho tên thư mục:

		. Win là \
		. Linux là /

		=> sự khác nhau này có sự tác động cực lớn khi viết 1 chtrinh C.


7.1.1.4
	- Nếu ta interested in 1 file cụ thể trong dir directory, tên là file. Giả sử gán 1 chuỗi chứa tên tệp:

		. Unix: char *name = "/dir/file";
		. Win:	char *name = "c:\dir\file";


7.1.2.1 Introduction to files and streams
	- Bất kỳ chương trình nào được viết bằng ngôn ngữ "C" (quy ước này áp dụng cho gần như tất cả các ngôn ngữ lập trình) không trực tiếp giao tiếp với các tập tin, mà thông qua một entity trừu tượng được gọi là stream (luồng).

	- Người lập trình, có một bộ các hàm được định nghĩa chủ yếu trong tệp đầu vào stdio.h, có thể thực hiện một số thao tác trên stream (luồng) ảnh hưởng đến các tập tin thực sự bằng cách sử dụng các cơ chế chứa trong operating system kernel. 

	- Như vậy, có thể truy cập vào bất kỳ tệp nào, ngay cả khi tên của tệp không được biết vào thời điểm viết chương trình.

	- Các thao tác được thực hiện với stream trừu tượng phản ánh các hoạt động liên quan đến tệp vật lý. Để link stream với tệp, bạn cần thực hiện một thao tác rõ ràng.

	- Thao tác link stream với một tệp được gọi là opening the file, trong khi disconnecting this link được gọi là closing the file. 

	=> Có thể kết luận rằng thao tác đầu tiên được thực hiện trên stream luôn luôn là opening và thao tác cuối cùng là closing. 

	- Chương trình thực tế có thể thao tác trên stream giữa hai sự kiện này và xử lý tệp tương ứng. Tuy nhiên, sự tự do này bị hạn chế bởi các đặc điểm vật lý của tệp và cách tệp đã được mở.


	- Tuy nhiên, việc mở stream có thể thất bại vì một số lý do: 
		. Lý do phổ biến nhất là lack of a file with a specified name. 
		. Hoặc là tệp vật lý tồn tại, nhưng chương trình không được phép mở nó. 
		. Hoặc là chương trình đã mở quá nhiều streams và hệ điều hành cụ thể có thể không cho phép mở đồng thời hơn N (ví dụ: 20) tệp. Một well-written program nên phát hiện các failed opening này và react accordingly.

	- Chúng ta có thể làm gì với một stream?
		. Việc mở stream liên quan đến tệp và cũng nên khai báo cách mà stream sẽ được xử lý. 

		.Việc khai báo này được gọi là open mode.
			Nếu việc mở thành công, chương trình chỉ được phép thực hiện các thao tác phù hợp với chế độ mở đã được khai báo.

	- Có hai thao tác cơ bản được thực hiện trên stream:

		. read from the stream: các phần dữ liệu được "retrieved" từ tệp và đặt vào một khu vực bộ nhớ được quản lý bởi chương trình (ví dụ: một biến);
		
		. write to the stream: các phần dữ liệu từ bộ nhớ (ví dụ: một biến) được "transferred" đến một tập tin.


7.1.2.2
	- Chúng ta có thể mở một luồng (stream) như thế nào?
	Có ba modes cơ bản được sử dụng để mở luồng (stream):

		. read mode: một luồng mở trong chế độ này chỉ cho phép các thao tác đọc - cố gắng ghi vào luồng sẽ gây ra lỗi thời gian chạy (runtime error);'

		. write mode: một luồng mở trong chế độ này chỉ cho phép các thao tác ghi - cố gắng đọc từ luồng sẽ gây ra lỗi thời gian chạy (runtime error);

		. update mode: một luồng mở trong chế độ này cho phép cả việc ghi và đọc.

	- Luồng hoạt động gần giống một băng ghi âm. Khi bạn đọc một cái gì đó từ một luồng, một đầu đọc ảo di chuyển qua luồng tùy theo số lượng byte được chuyển từ luồng. Khi chúng ta ghi một cái gì đó vào luồng, cùng một đầu đọc di chuyển theo luồng, ghi lại dữ liệu từ bộ nhớ.

	- Tưởng tượng việc đọc và ghi trên luồng giống như việc sử dụng băng ghi âm, để dễ dàng hình dung và hiểu cách hoạt động của luồng.

	- Điều quan trọng là hiểu rõ data type chịu trách nhiệm đại diện cho các luồng trong chương trình.

	- Làm thế nào chúng ta biểu diễn một luồng trong chương trình?

		. Tiêu chuẩn ngôn ngữ "C" giả định rằng môi trường lập trình (bao gồm compiler, các tệp đầu vào và thư viện liên quan, cũng như một số công cụ bổ sung) nên đảm bảo sự tồn tại của một kiểu có tên là FILE, được sử dụng để biểu diễn các luồng trong chương trình.

		. Các hệ điều hành và nền tảng phần cứng khác nhau có thể yêu cầu các dữ liệu khác nhau để mô tả trạng thái của một luồng. Cách mà FILE được khai báo không quan trọng. Programmer không bao giờ sử dụng dữ liệu trực tiếp mà chỉ thông qua các hàm thư viện, không nên can thiệp vào dữ liệu của kiểu này.

		. Một biến có kiểu FILE được tạo ra khi bạn mở tệp và bị hủy khi tệp được đóng. Trong khoảng thời gian giữa hai sự kiện này, bạn có thể sử dụng dữ liệu này để chỉ định những thao tác nào nên được thực hiện trên một luồng cụ thể.
			Tuy nhiên, do định nghĩa của các hàm hoạt động trên dữ liệu này, chương trình không sử dụng biến có kiểu FILE mà thay vào đó sử dụng pointer đến chúng.

		. Kiểu FILE được định nghĩa bên trong "stdio.h" header file.


7.1.2.3
	- Binary streams vs text streams
		. Do loại nội dung của luồng, all các luồng được chia thành luồng văn bản và luồng nhị phân.

		. Các luồng văn bản được structured in line; tức là chúng chứa các ký tự chữ (chữ cái, chữ số, dấu câu, v.v.) được sắp xếp thành các hàng (dòng), có thể thấy khi xem nội dung của một tệp trong trình soạn thảo. Tệp này được viết (hoặc đọc) chủ yếu theo từng ký tự hoặc từng dòng.

		. Các luồng nhị phân không chứa text mà là một "chuỗi các byte có giá trị bất kỳ". Chuỗi này có thể là một chương trình thực thi, một hình ảnh, một đoạn âm thanh hoặc video, một tệp cơ sở dữ liệu, v.v. Vì những tệp này không chứa các dòng, việc đọc và viết liên quan đến các phần dữ liệu có kích thước bất kỳ. Do đó, dữ liệu được đọc/viết theo từng byte hoặc từng khối, trong đó kích thước của một khối thường dao động từ 1 đến một giá trị được chọn một cách tùy ý.


			. Tuy nhiên, trong các hệ thống Unix, line ends được đánh dấu bằng một ký tự duy nhất được gọi là "LF" (ASCII code 10), được đặc trưng trong các chương trình "C" là \n.

			. Các hệ điều hành khác, đặc biệt là những hệ thống dẫn xuất từ hệ thống CP/M tiền sử (áp dụng cho cả họ hệ điều hành Windows), sử dụng một quy ước khác: kết thúc dòng được đánh dấu bằng một cặp ký tự CR và LF (ASCII code 13 và 10), có thể được mã hóa thành \r\n.

		. Sự mơ hồ này có thể gây ra nhiều hậu quả không mong muốn. Nếu bạn tạo một chương trình có trách nhiệm xử lý một tệp văn bản và viết nó cho hệ thống Windows, bạn có thể nhận diện kết thúc của các dòng bằng cách tìm các ký tự \r\n, nhưng chương trình tương tự được biên dịch và chạy trong môi trường Unix sẽ hoàn toàn không hữu ích và ngược lại. Những đặc điểm không mong muốn của một chương trình, gây ra việc ngăn chặn hoặc gây trở ngại trong việc sử dụng chương trình trong các môi trường khác nhau, được gọi là non-portability. Tương tự, đặc điểm của chương trình cho phép biên dịch và thực thi trong các môi trường khác nhau được gọi là portability. Một chương trình có tính di động được gọi là portable program.


7.1.2.4
	- Giải quyết vấn đề của portability tại library functions level - thứ chịu trách nhiệm cho việc đọc và ghi ký tự từ luồng và đến luồng. Quá trình diễn ra như sau:

		. Khi luồng được open, dữ liệu trong tệp tương ứng nên được xử lý dưới dạng text;

		. Trong quá trình đọc/ghi dòng từ/vào tệp tương ứng, không có gì đặc biệt xảy ra trong môi trường Unix, nhưng khi thực hiện các hoạt động tương tự trong môi trường Windows, một quá trình gọi là dịch các ký tự xuống dòng diễn ra: khi bạn đọc một dòng từ tệp, mỗi cặp ký tự \r\n sẽ được thay thế bằng một ký tự \n duy nhất. Và ngược lại, trong quá trình ghi, mỗi ký tự \n sẽ được thay thế bằng một cặp ký tự \r\n;
		
		. Cơ chế này giúp những chương trình được viết chỉ để xử lý tệp văn bản Unix; thì source code cũng có thể được biên dịch trong môi trường Windows, và cũng sẽ hoạt động đúng.


7.1.3.1 Opening streams
	- The fopen() fucntion:
		. Prototype:

			FILE *fopen(char *filename, char *openmode);


		. Tên của hàm được tạo từ hai từ "file open".

		. Nếu việc mở thành công, hàm sẽ return a pointer tới một biến mới được tạo có kiểu FILE, ngược lại, nó sẽ trả về NULL. Điều này giúp kểm tra lời gọi hàm có thành công hay không;

		. Tham số đầu tiên của hàm chỉ định tên của tệp mà muốn gắn với luồng. Tên tệp phải được viết theo các quy ước áp dụng trong hệ điều hành cụ thể;

		. Tham số thứ hai chỉ định open mode được sử dụng cho luồng. Nó được mô tả bằng một chuỗi các ký tự và mỗi ký tự đều có ý nghĩa đặc biệt của riêng nó (chi tiết hơn sẽ được giải thích sau);

		. Việc mở tệp phải là very first operation được thực hiện trên luồng (có ba trường hợp ngoại lệ cho quy tắc này – chi tiết sẽ được giải thích sau).

	- Open modes: r => read
		. Tệp tương ứng với luồng phải tồn tại và có thể đọc được, nếu không, hàm fopen sẽ thất bại.

	- Open modes: w => write
		. Tệp tương ứng với luồng không cần phải tồn tại
			> nếu nó không tồn tại, tệp sẽ được tạo mới
			> nếu tệp đã tồn tại, nó sẽ bị cắt bớt đến độ dài bằng không (xóa nội dung)
			> nếu việc tạo không thành công (ví dụ, do system permissions) thì hàm fopen sẽ thất bại.

	- Open modes: a => append
		. Tệp tương ứng với luồng không cần tồn tại
			> nếu không tồn tại, tệp sẽ được tạo mới
			> nếu tệp đã tồn tại, đầu ghi ảo sẽ được đặt vào cuối tệp (nội dung trước đó của tệp vẫn được giữ nguyên).

	- Open modes: r+ => read and update
		. Tệp tương ứng với luồng phải tồn tại và có thể ghi được, nếu không, hàm fopen sẽ thất bại;
		. Đều đọc và viết được

	- Open modes: w+ => write and update
		. Luồng sẽ được mở ở chế độ "ghi và cập nhật";
		. Tệp tương ứng với luồng không cần phải tồn tại
			> nếu không tồn tại, tệp sẽ được tạo mới; nội dung trước đó của tệp sẽ bị loại bỏ (tệp bị cắt bớt đến độ dài bằng không);
		. Đều đọc và viết được


7.1.3.2
	- Ký tự 'b' đặt ở cuối mode string --> stream được mở trong chế độ nhị phân (binary mode). Mặc định khi không chỉ định binary/text mode là mở stream trong chế độ text.

	- Một vài compilers chỉ định rằng nếu mode string kết thúc bằng ký tự 't', stream sẽ được mở trong text mode.
		. Mở file trong text mode là cần thiết cho các programs chạy trên hệ thống Windows

		. nhưng không bắt buộc đối với các chương trình được thiết kế cho môi trường Unix (trong Unix không có translation của các ký tự end line, vì vậy không quan trọng là file được mở ở text hay binary mode).

	- Cuối cùng, việc mở file thành công sẽ đặt vị trí hiện tại của file (the virtual reading/writing/head) trước byte đầu tiên của file nếu mode không phải là 'a', và sau byte cuối cùng của file nếu mode được thiết lập là 'a'.

7.1.3.3
	Opening the stream: an example

	- Example về 1 program đọc file named "file.txt":
		. Đường dẫn:
			c:\users\user\Desktop\file.txt

		. Open file for reading:

			FILE *file;
	
			if ((file = fopen("V:\\AE learning - Mr.Phong\\My own\\Buoi 2\\Owncode.txt", "rt")) == NULL)
			{
				printf("File cannot be read");
				return 1;
			}


7.1.4.1 Pre-opened streams
	- Mặc dù đã nói là mọi hoạt động trên stream phải thực hiện gọi hàm fopen() trước. Nhưng có 3 ngoại lệ, khi program bắt đầu thì 3 streams đã mở sẵn.

	- Program có thể dùng 3 streams này nếu chứa directive sau:

		#include <stdio.h>

	Bởi vì đó là nơi declaration của 3 streams được đặt.

	- Declarations như sau:

		FILE *stdin, *stdout, *stderr;

		+ The stdin stream:
			. stdin (standard input);
			. "stdin" stream được liên kết với keyboard, pre-opened for reading và được coi là data src chính của programs đang chạy;
			. "scanf" function đọc data từ "stdin" mặc định.

		+ The stdout stream:
			. stdout (standard output);
			. "stdout" stream được liên kết với screen, pre-opened for writing và được coi là target chính để output data bởi programs đang chạy;
			. "printf" function đọc data từ "stdout" mặc định.

		+ The stderr stream:
			. stderr (standard error output);
			. "stderr" stream được liên kết với screen, pre-opened for writing, được coi là nơi mà program đang chạy gửi inf về errors gặp phải trong lúc làm việc;
			. sẽ nói về fuction dùng để gửi data tới stream này sau

	- Tách biệt "stdout" (useful results đưa ra bởi program) với "stderr" (thông báo lỗi, hữu ích nhưng không đưa results) giúp ta chuyển hướng 2 loại inf này đến targets khác nhau.

		Tuy vậy, cái này không nằm trong phạm vi khóa học này. Muốn biết thì học về Hệ điều hành.


7.1.5.1 Closing the stream and error handling
	The fclose() function

	- Last operation được thực hiện trên stream (không bao gồm stdin, stdout, stderr - những thứ không cần function này) là closing. 
	- Prototype:

		int fclose(FILE *stream);

		. Chỉ có 1 parameter: 1 pointer chỉ đến biến type FILE, đại diện cho stream cần đóng, tất nhiên stream đã được mở trước đó.
		. Nếu thành công thì return 0 / Nếu thất bại thì return 1 value identifier bởi symbol EOF (EOF symbol được khai báo trong "stdio.h" file và đại diện cho value equal -1)

	- Nếu stream được mở để writing và theo sau là một loại hành động write, data gửi tới stream có thể chưa được transferred to thiết bị vật lý (do cơ chế "caching" hay còn gọi là "buffering").
		Vì close stream sẽ force buffers flush them (bộ đệm xả chúng), the flushes có thể fail -> fclose fail luôn

	- Muốn close stream được opened ở example trước, cần invoke hàm fclose như sau:

		fclose(file);

	- Khi thực thi fclose, stream không còn liên kết với file nào nữa, trừ fopen thì tất cả hoạt động khác đều thất bại

	- Ta đã nói về failures gây ra bởi functions hoạt động với stream, nhưng chưa nói cách chính xác để xác định cause of failure

	- Make a diagnosis bằng 1 variable được đề cập tiếp theo sau.


7.1.5.2
	The "errno" variable

	- Định nghĩa biến "errno" (tên bắt nguồn từ phrase "error number") nằm trong "errno.h" header file, có dạng như sau:

		extern int errno;

	- Theo định nghĩa, thực thi bất kì function nào hoạt động trên stream đều thiết lập biến errno, với error code nhận diện nguyên nhân failure.

	- Value của errno có thể so sánh với 1 trong những predefined symbolic constants (hằng số tượng trưng đã xác định), thứ cũng được defined trong "errno.h" file
		cung cấp cơ sở để xác định nguyên nhân thực sự gây error

	+ Một vài constants hữu ích để detect stream errors:

		- EACCES: Permission denied - Xảy ra khi mở một file có thuộc tính read only để writing.

		- EBADF: Bad file number - Xảy ra khi thao tác với một stream chưa được mở.

		- EEXIST: File exists - Xảy ra khi đổi tên một tệp với tên trước đó của nó.

		- EFBIG: File too large - Xảy ra khi tạo file lớn hơn kích thước tối đa cho phép bởi hệ điều hành.

		- EISDIR: Is a directory - Xảy ra khi treat tên directory như tên của file thông thường.

		- EMFILE: Too many open files - Xảy ra khi mở đồng thời nhiều stream hơn so với giới hạn cho phép của hệ điều hành của bạn.

		- ENOENT: No such file or directory - Xảy ra khi truy cập vào một file/directory không tồn tại.

		- ENOSPC: No space left on device - Xảy ra khi không còn không gian trống trên thiết bị lưu trữ.

		Danh sách đầy đủ là RẤT DÀI (nó cũng bao gồm các error codes không liên quan đến stream processing).


7.1.5.3
	- Very careful programmer:

		FILE *file = fopen("c:\\file.txt","rt");
		if(file == NULL) { 
		    switch(errno) {
		    case ENOENT: printf("The file doesn't exist\n"); 
		                 break;
		    case EMFILE: printf("You've opened too many files\n"); 
		                 break;
		    default:     printf("The error number is %d\n",errno);
		    }
		}		


7.1.5.4
	- Có 1 function giúp simplify error-handling code
	- Gọi là "strerror", prototype của nó nằm trong "string.h" file và có dạng như sau:

		char *strerror (int errnum);

	- Its role:
		Ta cung cấp an error number, và sẽ nhận được 1 pointer trỏ đến text mô tả ý nghĩa của error đó.


7.1.6.1 Reading from the stream
	The fgetc() function

	- Chức năng: Đọc 1 ký tự từ stream
	- Giờ ta sẽ nói về các functions dùng để read từ stream
	- Đầu tiên là fgetc(), prototype:

		int fgetc(FILE *stream);

		. Tên function bắt nguồn từ "file get character"

		. Trong hàm sẽ là 1 tham số type FILE *, là pointer trỏ đến stream đã được mở để reading hoặc updating.

		. Function này đọc 1 ký tự (byte) từ stream được xác định bởi tham số.
			Nếu có thể, hàm return kết quả là code của retrieved character.
			
			Nó sẽ là 1 số thuộc khoảng 0 - 225, vị trí hiện tại trong file di chuyển 1 byte về cuối file
		
		. Nếu fails (e.g. vị trí hiện tại trong file đã nằm sau kí tự cuối cùng) thì fgetc returns value của EOF (-1) và file position không thay đổi
		
		. Function này có thể dùng để đọc character từ text file cũng như đọc bytes từ binary file

	- Có 1 function với prototype như sau:
		
		int getchar(void);		// dùng để đọc 1 single character từ "stdin" stream

	và nó tương đương với invocation sau:

		fgetc(stdin);


7.1.6.2
	The fgetc() function
	- Write a simple program whose task is to copy the contents of any file to the screen (this is to the "stdout" stream). We assume that the name of the file to be copied is given as the program's argument.

	- Be aware: displaying the content of a binary file can cause various unexpected and unwanted results.

		#include <stdio.h>
		#include <errno.h>

		int main(int argc, char *argv[]) {
			FILE *inp;	
			int  chr;

			/* check if there is one argument */
			if(argc != 2) {
				printf("usage: show file_name\n");
				return 1;
			}

			/* check if we are able to open the input file */
			if((inp = fopen(argv[1],"rt")) == NULL) {
				printf("Cannot open the file %s\n", argv[1]);
				return 2;
			}

			/* we will try to read the file char by char and print the chars to screen */

			while((chr = fgetc(inp)) != EOF)
				printf("%c",chr);

			/* it's time to close the stream */
			fclose(inp);
			return 0;
		}


7.1.6.3
	The fgets() function: reading 1 string từ stream

	- Prototype của fgets():

		char *fgets(char *str, int maxsize, FILE *stream);

		. Tên bắt nguồn từ file get string;

		. 3 tham số
			. str: pointer to string mà trong đó fgets sẽ chứa 1 line lấy từ stream

			. maxsize: số lượng kí tự tối đa có thể stored trong "str";
				bao gồm cả kí tự không hiển thị như '\0' và kí tự LF ('\n') lấy từ stream

				Vì string phải end bằng '\0' nên nếu "maxsize" không phải 0 thì '\0' sẽ dùng mất 1 ký tự của "maxsize"

				Ví dụ: nếu stream read là "No"
					maxsize = 0 = NULL,
					maxsize = 1 = '\0',
					maxsize = 2 = 'N' '\0',
					maxsize >= 3 = 'N' 'o' '\0';
			. stream: pointer to stream đang mở để reading hoặc updating

		. Function sẽ đọc 1 line của text từ stream
			nếu thành công, function sẽ lưu trữ tối đa masize kí tự trong string trỏ bởi "str"

			nếu file chứa nhiều lines với độ dài lớn, chúng sẽ được đọc part by part

		. Nếu reading thành công, functions sẽ return giá trị của tham số str, và vị trí hiện tại trong file được di chuyển đến sau kí tự cuối cùng được truy vấn

		. Ngược lại function returns NULL và vị trí hiện tại file không đổi

	- Function này không dùng cho reading binary files. Files loại này không có cấu trúc dòng, do đó không thể đọc line by line

	- Thêm nữa, nếu có 1 byte với giá trị = 0 trong file, nó sẽ bị hiểu lầm là end of string maker.

	- Có 1 function với prototype:

		char* gets(char *str);

	và nó tương đương với:

		fgets(str, INT_MAX, stdin);

	trong đó, INT_MAX là hằng số biểu thị maximum value của type "int"

	- Function này đọc 1 line từ "stdin" stream, nhưng không check xem line có dài hơn limit hay không. Do đó, function này khá nguy hiểm, vì nếu lượng kí tự đọc vượt quá size của "str", nó có thể gây ra memory protection violation và termination of program.


7.1.6.4
	- Rewrite previous program, thay fgetc bằng fgets:

		#include <stdio.h>
		#include <errno.h>

		int main(int argc, char *argv[]) {
			FILE *inp;
			char line[128];
			if(argc != 2) {
				printf("usage: show2 file_name\n");
				return 1;
			}
			if((inp = fopen(argv[1],"rt")) == NULL) {
				printf("Cannot open the file %s\n", argv[1]);
				return 2;
			}
			while((fgets(line,sizeof(line),inp)) != NULL)
				printf("%s",line);
			fclose(inp);
			return 0;
		}


7.1.6.5
	The fread() function: reading bytes from the stream

	- Prototype của fread():

		int fread(void *mem, int size, int count, FILE *stream);

		. Tên function bắt nguồn từ file read
		. 4 tham số:
			. mem: pointer to memory trong đó "fread" sẽ store 1 phần các byte được đọc từ stream

			. size: size (in bytes) của phần cần đọc

			. count: số lượng phần cần đọc

			. stream: pointer chỉ đến stream đã được mở để reading hay updating

		. function đọc "size *count" bytes từ stream
			Nếu thành công, function sẽ lưu trữ bytes đã được đọc vào trong bộ nhớ được pointed bởi "mem"

		. function returns số lượng phần đã đọc thành công
			. Có thể (nhưng không nhất thiết) bằng giá trị của "count"
			. Value of 0 nghĩa là hàm không thể đọc được bất kì phần nào
			. Vị trí hiện tại của file được di chuyển đến sau byte cuối cùng được đọc

	- Function này rất lý tưởng để đọc binary file, bởi vì có thể dùng nó để đọc một lượng cụ thể bytes. Có thể dùng để đọc text files, nhưng nếu muốn treat nội dung của nó as lines, phải tìm được ends của lines, điều này rất phiền. "fgets" function sẽ thuận tiện hơn cho việc này.

	- "fread" function dùng 2 tham số để specify kích thước dữ liệu cần đọc:
		size và count

	- Tưởng tượng có 1 "int" value trong binary file (chú ý, nó không được stored dưới dạng cặp kí tự mà được sử dụng bởi máy tính, tốn chính xác sizeof (int) bytes). Giả sử ta muốn retrieve giá trị từ input stream và lưu các bytes vào trong biến "number". Khai báo như sau:

		int number;
		FILE *input;

	- Reading có thể được thể hiện qua 2 cách tương đương nhau như sau:

		. fread(&number, sizeof(int), 1, input);
		
		. fread(&number, 1, sizeof(int), input);

	- Case đầu tiên:
		"fread" sẽ đọc 1 portion kích thước sizeof(int)

	- Case thứ hai:
		"fread" sẽ đọc sizeof(int) phần, mỗi phần kích thước 1 byte

	- Trong cả 2 case, "fread" sẽ cố gắng đọc sizeof(int) bytes, nhưng kết quả được returned bởi function sẽ khác nhau
		. Vì "fread" returns số lượng chính xác của những phần được đọc, trong case 1 sẽ ra 1, còn case 2 sẽ ra sizeof(int), miễn là mọi thứ đúng.
		. Nếu không, sẽ return về tổng số phần đọc đúng


7.1.6.6
	- Viết lại chtrinh, dùng "fread" để đọc các bytes và in chúng dưới dạng hexadecimals. Nó sẽ giúp ta dùng chtrinh để hiển thị các binary files.

		#include <stdio.h>
		#include <errno.h>

		int main(int argc, char *argv[]) 
		{
			FILE *inp;
			unsigned char buffer[1024]; 		/* 1 kilobyte */
			int i, read;

			if(argc != 2) 
			{
				printf("usage: show3 file_name\n");
				return 1;
			}

			if((inp = fopen(argv[1],"rb")) == NULL) 
			{
				printf("Cannot open the file %s\n", argv[1]);
				return 2;
			}

			do 
			{
				read = fread(buffer,1,sizeof(buffer),inp);
				for(i = 0; i < read; i++)
					printf("%02X",buffer[i]);
			} while (read > 0);

			fclose(inp);
			return 0;
		}

	- Khai báo 1 array lớn tên "buffer", lưu trữ các bytes đọc từ file

	- Sau đó, in nội dung của nó byte by byte, convert các values sang hexadecimal. Operation này sẽ được lặp lại miễn là vẫn còn dữ liệu để đọc trong file.

	- Note: "buffer" là common name được dùng cho bộ nhớ dùng tạm để chứa dữ liệu input hay output. Chú ý cách chúng ta mở stream: nó được mở dưới dạng binary

	- Giải thích được tại sao không có & trước buffer không?


7.1.6.7
	fscanf() function: đọc định dạng từ stream

	- Function trước giờ đều đọc data từ file và gửi nó vào bộ nhớ một cách gần như không đổi (trừ TH đọc 1 text file với các ký tự xuống dòng được dịch; nhưng kể cả TH này thì line không chịu bất kì sự sửa đổi nào)

	- Tuy vậy, chúng ta thường đọc text và muốn nội dung của nó được convert qua binary image ngay lập tức. Ví dụ, giả sử 1 line gồm 3 ký tự tạo thành số như sau:

		128

	Ta muốn đọc nó và store nó vào biến type int, như sau:

		int number;

	Không có hàm nào trong các hàm trước đó thuận tiện cho việc này

	- Ta cần 1 function có thể đọc string biểu thị bất kỳ giá trị nào và convert nó trực tiếp thành internal representation (biểu diễn nội bộ). Có 1 hàm ta đã sử dụng, nhưng ở dạng cho phép ta chỉ đọc data từ "stdin" stream
		Đó chính là scanf với prototype:

			int scanf(char * format, ...);

	- Function này là case đặc biệt của 1 hàm khác, tổng quát hơn, có thể làm việc với bất kì stream nào. Được gọi là fscanf, với prototype:

		int fscanf(FILE *stream, const char *format, ...);

	- Điều đó có nghĩa là invocation như này:

		scanf("%d", &number);

	tương đương với:

		fscanf(stdin, "%d", &number);

	- Function này expects những tham số sau:
		. "stream": pointer to stream mà đã được mở cho reading hoặc updating

		. "format": pointer to string mô tả data nào sẽ được đọc từ stream; các mô tả chi tiết của định dạng có thể tìm lại trong Chapter 2 của khóa học này

		. "...": list những pointers to variables được gán values mà đọc từ data stream.

	- function returns số lượng giá trị đọc đúng từ stream. Số lượng này có thể ít hơn số lượng pointers trong "..." list và thậm chí có thể = 0 nếu stream không chứa kí tự nào có thể interpreted as values được specified bởi định dạng.


7.1.6.8
	- Hãy xem xét hàm fscanf thông qua ví dụ sắp xếp các số nguyên, cái mà chúng ta đã sử dụng trong khóa học trước đó. Chương trình đã được sửa đổi để đọc các số cần sắp xếp từ một text file.

	- Giả định rằng mỗi line trong input file chỉ chứa một số và không có nhiều hơn 1000 số

	- Cũng giả định rằng khi không thể lấy được một số nào thì sẽ kết thúc việc nhập dữ liệu bất kể lý do (cho dù là end of file hoặc bất kỳ lỗi nào khác). Để chạy chương trình, bạn cần chỉ định 1 input file làm 1 tham số. Các số được sắp xếp sẽ được hiển thị trên màn hình.

		Chương trình tương tự, nhưng ở dạng được chỉnh sửa một chút, sẽ xuất hiện trong phần tiếp theo của khóa học, cùng với một test data type.

	- Chú ý cách xử lý lỗi khi mở file và cách đếm data được đọc.

		#include <stdio.h>
		#include <errno.h>
		#include <string.h>

		int main(int argc, char *argv[]) 
		{
			int numbers[1000];
			int	i, aux;
			int	numbersread = 0;
			int	swapped;
			FILE	*inp;

			if(argc != 2) 
			{
				printf("usage: intsort input_file\n");
				return 1;
			}

			if((inp = fopen(argv[1],"rt")) == NULL) 
			{
				printf("Cannot open %s - %s\n",argv[1],strerror(errno));
				return 2;
			}

			while(fscanf(inp,"%d",&numbers[numbersread]) == 1) 
			{
				numbersread++;
				if(numbersread == 1000)
					break;
			}
			fclose(inp);

			if(numbersread == 0) 
			{
				printf("No numbers found in the files %s\n",argv[1]);
				return 3;
			}

			do 
			{
				swapped = 0;
				for(i = 0; i < numbersread - 1; i++)
					if(numbers[i] > numbers[i + 1]) 
					{
						swapped = 1;
						aux = numbers[i];
						numbers[i] = numbers[i + 1];
						numbers[i + 1] = aux;
					}
			} while (swapped);

			printf("The sorted values: ");
			for(i = 0; i < numbersread; i++)
				printf("%d ",numbers[i]);


			printf("\n");
			return 0;
		}


7.1.7.1 Writing to the stream
	The fputc() function: writing one character to the stream

	- Tiếp đây là 1 bộ set các function bổ sung được thiết kế để write data to streams

	- Đầu tiên là fputc(), prototype như sau:

		int fputc(int chr, FILE *stream);

		. Tên function bắt nguồn từ file put character
		. Expect 2 thông số:
			. chr: code của character (hoặc chính character) để xuất ra stream
			. stream: pointer to stream đã được mở cho writing hoặc updating

		. Nếu function thành công, nó return code của "chr" character
			Nó sẽ luôn là số giữa 0 và 255
			Vị trí hiện tại của file di chuyển 1 byte về phía cuối của file

		. Nếu fail (e.g. vì insufficient disk space), hàm returnss giá trị của EOF (-1) và vị trí file không đổi

		. Ngược lại, return NULL và vị trí file hiện tại không đổi

	- Còn 1 hàm bổ sung với prototype như sau:

		int putchar (int chr);

	tương đương với:

		fputc(chr, stdout);

	và được dùng để ghi 1 character/byte vào "stdout" stream.


7.1.7.2
	- Xem xét fputc bằng 1 chtrinh phức tạp hơn chút: copy contents của 1 file sang 1 file khác một cách tương đối giống lệnh copy ở Window hay cp ở Unix

	- Chtrinh sẽ interpret đối số của nó theo the same way:
		Đối số đầu là tên của src file
		Đối số 2 là tên của target (tệp đích)

	- Phân tích các khía cạnh sau:
		. Các chế độ đã sử dụng để mở input và output streams

		. Reaction to lỗi mà xuất hiện khi writting vào output stream
			Có thể đưa ra giải pháp tốt hơn để xử lí lỗi không?

		#include <stdio.h>
		#include <errno.h>

		int main(int argc, char *argv[]) {
			FILE *inp, *out;
			int	chr;

			/* check if we've got exactly two arguments */
			if(argc != 3) {
				printf("usage: copyc source_file target_file\n");
				return 1;
			}

			/* check if we are able to open the source file */
			if((inp = fopen(argv[1],"rb") )== NULL) {
				printf("Cannot open %s\n", argv[1]);
				return 2;
			}

			/* check if we are able to open the target file */
			if((out = fopen(argv[2],"wb")) == NULL) {
				printf("Cannot create %s\n", argv[2]);
				fclose(inp);
				return 3;
			}

			/* we are going to read char by char until we reach EOF */
			while((chr = fgetc(inp)) != EOF)
				if(fputc(chr, out) == EOF)
					break;
			fclose(inp);
			fclose(out);
			return 0;
		}


7.1.7.3
	The fputs() function: writing a string to the stream

	- Prototype:

		int fputs(char *string, FILE *stream);

		. Tên function từ file put string;
		. Expect 2 thông số:
			. string: pointer to string sẽ được viết vào stream
				note: function sẽ không tự động thêm '\n' vào cuối string (khác với puts)

			. stream: pointer to stream đã mở for writing or updating

		. Functions sẽ viết nội dung của string vào stream

		. Nếu thành công, return 1 số không âm và vị trí hiện tại của file được di chuyển về cuối file

		. Nếu có lỗi, return EOF, vị trí file không đổi

		. Function này chắc chắn không được dùng để ghi data vào binary files bởi vì nó không thể ghi 1 byte có giá trị 0 - giải thích tại sao?

			Vì hàm này để ghi string, dựa vào '\0' để end string, trong khi binary file thì các byte có thể có bất kỳ giá trị nào trong đoạn 0 - 255.

		. Function với prototype:

			int puts(char *string);

		tương đương với:

			fputs(string, stdout);


7.1.7.4
	- Sửa đổi chtrinh, giờ nó chỉ có thể copy text files.

	- Warning:
		. Không cố dùng nó để copy binary files, trừ phi muốn thí nghiệm.
		. Nếu src file chứa những dòng dài hơn 128 characters thì kết quả copy có thể khác biệt đáng kể. Giải thích tại sao?

			Vì fputs chỉ đọc 1 số lượng kí tự nhất định mỗi lần gọi, nếu vượt quá lượng này, data sẽ bị cắt ngắn.

		#include <stdio.h>
		#include <errno.h>

		int main(int argc, char *argv[]) {
			FILE	   *inp, *out;
			char	     line[128];

			if(argc != 3) {
				printf("usage: copys source_file target_file\n");
				return 1;
			}

			if((inp = fopen(argv[1],"rt")) == NULL) {
				printf("Cannot open %s\n", argv[1]);
				return 2;
			}
			if((out = fopen(argv[2],"wt")) == NULL) {
				printf("Cannot create %s\n", argv[2]);
				fclose(inp);
				return 3;
			}
			while((fgets(line,sizeof(line),inp)) != NULL)
				if(fputs(line,out) == EOF)
					break;
			fclose(inp);
			fclose(out);
			return 0;
		}


7.1.7.5
	The fwrite() function: writing bytes to the stream

	- "fwrite" function có prototype:

		int fputs(char *string, FILE *stream);

		. Tên function từ file write
		. Expect 4 tham số:
			. mem: pointer to memory area cần được ghi vào stream
			. size: kích thước (theo bytes) của 1 phần bộ nhớ đang được ghi
			. count: số lượng phần dự định được ghi
			. stream: pointer to stream đã được mở để writing hoặc updating

		. function sẽ ghi (size *count) bytes từ "mem" vào stream
		. function return số lượng phần được ghi thành công và vị trí hiện tại của file được di chuyển về phía cuối của file
			result có thể khác giá trị count, vì vài lỗi khiến writing không thành công

		. function này lí tưởng để ghi vào binary files, nhưng có thể dùng nó để tạo text files cũng được nếu cung cấp xử lí phù hợp cho các kí tự "endline"


7.1.7.6
	- Giờ ta sửa đổi chtrinh mà ta làm khi nói về hàm fread
	- Check cách ta lấy số lượng bytes cần được ghi. Giải thích cách nó thực sự hoạt động?

		#include <stdio.h>
		#include <errno.h>

		int main(int argc, char *argv[]) {
			FILE	*inp, *out;
			char 	buffer[16384]; /* 16 kilobytes */
			int	read, written;

			if(argc != 3) {
				printf("usage: copyw source_file target_file\n");
				return 1;
			}
			if((inp = fopen(argv[1],"rb")) == NULL) {
				printf("Cannot open %s\n", argv[1]);
				return 2;
			}
			if((out = fopen(argv[2],"wb")) == NULL) {
				printf("Cannot create %s\n", argv[2]);
				fclose(inp);
				return 3;
			}
			do {
				read = fread(buffer,1,sizeof(buffer),inp);
				if(read)
					written = fwrite(buffer,1,read,out);
			} while (read && written);
			fclose(inp);
			fclose(out);
			return 0;
		}


7.1.7.7
	The fprintf() function: formatted writing to the stream

	- Function này liên quan đến printf function, nhưng nó versatile (linh hoạt) hơn
		printf chỉ có thể ghi vào "stdout"
		fprintf thì stream nào cũng được

	- Printf có prototype:

		int printf (char *format, ...);

	- Có thể đoán được fprintf thì như sau:

		int fprintf(FILE *stream, char *format, ...);

	- Điều đó imply rằng invocation sau:

		printf("%d", number);

	là tương đương với:

		fprintf(stdout, "%d", number);

	- Expect những tham số sau:
		. stream: pointer to stream được mở để writing hoặc updating
		. format: pointer to string mô tả data sẽ được ghi vào stream
		. "...": list những biểu thức mà values của nó sẽ được converted thành human-readable form và được ghi vào stream

	- Function returns số lượng kí tự (không phải values, khác với hàm fscanf) được ghi correctly vào stream

	- Function này cho phép gửi thông báo lỗi trực tiếp tới "stderr" stream.


7.1.7.8
	- Sửa đổi chtrinh mà ta đã dùng để thí nghiệm hàm fscanf.
	- Chtrinh đã revised sẽ không chỉ đọc numbers từ 1 text file, mà còn lưu chuỗi đã sắp xếp vào trong 1 file khác (tất nhiên sẽ tốt hơn nếu output file không phải là file mà input data được đọc)

	- Ngoài ra, chtrinh sẽ ghi thông báo lỗi vào "stderr" stream
	- Như đã giả định trước đó, các số được lưu trữ 1 lần trên mỗi line trong cả input và output files. Để run chtrinh, ta phải chỉ định file names là arguments

		#include <stdio.h>
		#include <errno.h>
		#include <string.h>
		int main(int argc, char *argv[]) {
			int 	numbers[1000];
			int	i,aux;
			int	numbersread = 0;
			int	swapped;
			FILE	*inp, *out;
			if(argc != 3) {
				fprintf(stderr,"usage: intsort2 source_file target_file\n");
				return 1;
			}
			if((inp = fopen(argv[1],"rt")) == NULL) {
				fprintf(stderr,"Cannot open %s: %s\n",argv[1],strerror(errno));
				return 2;
			}
			if((out = fopen(argv[2],"wt")) == NULL) {
				fprintf(stderr,"Cannot create %s: %s\n",argv[2],strerror(errno));
				fclose(inp);
				return 3;
			}
			while(fscanf(inp,"%d",&numbers[numbersread]) == 1) {
				numbersread++;
				if(numbersread == 1000)
					break;
		}
			fclose(inp);
			if(numbersread == 0) {
				printf("No numbers found in the file %s\n",argv[1]);
				return 3;
			}
			do {
				swapped = 0;
				for(i = 0; i < numbersread - 1; i++)
					if(numbers[i] > numbers[i + 1]) {
						swapped = 1;
						aux = numbers[i];
						numbers[i] = numbers[i + 1];
						numbers[i + 1] = aux;
				}
			} while(swapped);
			for(i = 0; i < numbersread; i++)
				fprintf(out,"%d\n",numbers[i]);
			printf("\n");
			fclose(out);
			return 0;
		}


7.1.8.1 Dealing with the stream

	The ftell() function: getting the stream's position

	- Nhiều lần nói về vị trí hiện tại của file, nhưng chưa nói gì về cách affect trực tiếp đến vị trí này, thực hiện không hoạt động writing hoặc reading.

	- Thực hiện thông qua hai function:
		. function đầu tiên chỉ định vị trí hiện tại của file. Vị trí này được đếm từ đầu file và giả định khi file được mở trong chế độ khác "a", nó bằng 0 (tức là nó chỉ vào vị trí trước byte đầu tiên của file).

	- Function này có prototype như sau:

		long ftell(FILE *stream);
	
	- Tên function đến từ "file tell";
		. Expect 1 tham số: 1 pointer đến stream đã mở;

		. Function này return khoảng cách (theo byte) đếm từ đầu của file đến vị trí hiện tại của file; do đó, byte đầu tiên của file được đặt tại vị trí số 0;

		. Nếu có lỗi, function trả về EOF (-1);

		. Function không ảnh hưởng đến vị trí của file cũng như nội dung của nó.

	- Sẽ sớm có một ví dụ về sử dụng function này.


7.1.8.2
	The fseek() function: setting the stream's position

	- Hàm fseek cho phép thiết lập vị trí hiện tại của tệp. Nếu việc thiết lập thành công, thao tác read/write tiếp theo sẽ ảnh hưởng đến vị trí đó.

	- Vì lý do này, cách thức này trong việc điều khiển tệp thường được gọi là random access (truy cập ngẫu nhiên), ngược với sequential access (truy cập tuần tự), trong đó dữ liệu được written/read theo thứ tự liên tục.

	- Prototype như sau:

		int fseek(FILE *stream, long offset, int whence);

		- Tên function từ "file seek"
		- Expect 3 tham số sau đây:
			. stream: pointer to stream đã mở;
			
			. offset: value mô tả target position (có thể là số âm)

			. whence: value chỉ định reference point (điểm tham chiếu), nghĩa là cách tính vị trí mới
				Thông thường, tham số này thường được thể hiện bằng một trong ba symbolic constants sau:

				. SEEK_SET: tham số offset chỉ định vị trí được tính từ đầu của file

				. SEEK_CUR: tham số offset chỉ định vị trí được tính từ vị trí hiện tại của file

				. SEEK_END: tham số offset chỉ định vị trí được tính từ cuối của file

			. Trường hợp có lỗi xảy ra, hàm trả về EOF (-1); nếu không có lỗi, giá trị trả về là 0;

			. Hàm rõ ràng ảnh hưởng đến vị trí hiện tại của file.

		- Nhớ rằng không phải tất cả các files đều cho phép thiết lập vị trí hiện tại. 
			Ví dụ rõ ràng nhất là các file liên quan đến các stream stdin, stdout và stderr. 

		. Thiết lập vị trí cũng không thể thực hiện được cho các stream liên quan đến các thiết bị hoạt động tuần tự, như bàn phím hoặc máy in.


7.1.8.3
	- Một vài ví dụ đơn giản. Giả định khai báo sau hoạt động:

		FILE *F;

	- Thực hiện vài "fseek" invocations và mô tả effects của chúng.

		fseek(F, 0, SEEK_SET);

	đặt file ở vị trí bắt đầu của nó.

		fseek(F, 100, SEEK_SET);

	đặt file ở byte thứ 100 từ đầu file.

		fseek(F, 0, SEEK_END);

	đặt file ở cuối.

		fseek(F, 0, SEEK_CUR);

	không thay đổi vị trí của file (why?).

		fseek(F, -1, SEEK_CUR);

	dịch chuyển vị trí hiện tại của file đi 1 byte.

	- Bây giờ xem một ví dụ về một chương trình đơn giản hiển thị total size của một file (tính bằng byte). Chương trình này expects tên của file là đối số. Bạn sẽ nhận được size của file hoặc một thông báo lỗi.

		#include <stdio.h>
		#include <errno.h>
		#include <string.h>

		int main(int argc, char *argv[]) 
		{
			FILE *file;
			long size;

			if(argc != 2) 
			{
				fprintf(stderr,"usage: getsize file_name\n");
				return 1;
			}

			if((file = fopen(argv[1],"rt")) == NULL) 
			{
				fprintf(stderr,"Cannot open %s: %s\n",argv[1],strerror(errno));
				return 2;
			}
			/* attempt to skip to the end of file */

			if(fseek(file,0,SEEK_END)) 
				if(errno == EBADF)
					fprintf(stderr,"The file has no size: %s\n",argv[1]);
				else
					fprintf(stderr,"Error in fseek: #%d\n",errno);
			else 
			{
				size = ftell(file);
				printf("File: %s size: %d\n", argv[1], size);
			}
			
			fclose(file);
			return 0;
		}


7.1.8.4
	Rewinding the stream

	- Function này từ thời xưa, khi mà magnetic tape storage devices (thiết bị lưu trữ dùng băng từ) còn phổ biến

	- Những thiết bị này không thể thực hiện random access, và ta phải rewind lại cuộn băng từ đầu để re-read hoặc re-written

	- Prototype của hàm rewind:

		void rewind(FILE *stream);

	- Và khi gọi nó, nó sẽ có chức năng giống "fseek" invocation như sau:

		fseek(stream, 0, SEEK_SET);

	trừ 1 fact rằng rewind không return giá trị nào và cũng không set biến errno.


7.1.8.5
	Checking the end of the file

	- Trạng thái end of file (EOF) xảy ra khi không còn gì để đọc trong file.

	- Ta thường phát hiện trạng thái EOF một cách indirectly:
		Chỉ cần thử read stream và khi nó fail, ta cho rằng trạng thái EOF đã xảy ra. Nói cách khác, ta làm dứt khoát, không hỏi xem thao tác đọc có feasible không.

	- Nhưng cẩn thận hơn: ta trước tiên hỏi xem có gì để đọc không, rồi sau đó mới đọc nó.

	- Có một hàm là feof cho mục đích này:

		int feof(FILE *stream);

	- Function returns một non-zero value nếu stream đang ở trạng thái EOF; và nếu không, returns 0.

	- Sử dụng hàm này trong một snippet lấy từ một trong các chương trình trước đó

		while (!feof(input)) 
		{
		    fgets(line, sizeof(line), input);
		    fputs(line, output);
		}


7.1.8.6 LAB
7.1.8.7
7.1.8.8


8.1.1.1 C Essentials - Part 2: Module 8
	In this module, you will learn about:

	preprocessor,
	#include - how to make use of a header file,
	#define - simple and parameterized macros,
	the #undef directive,
	predefined preprocessor symbols,
	macrooperators: # and ##,
	conditional compilation: the #if and #ifdef directives,
	avoiding multiple compilations of the same header files,
	scopes of declarations, storage classes,
	user-defined types,
	pointers to functions,
	analyzing and creating complex declarations.


8.1.1.2 -> 8.1.1.3 Preprocessor: absolute basics
	The role of preprocessing

	- Preprocessor: chịu trách nhiệm initial processing của chtrinh
	- Muốn thấy src như nào sau khi preprocessing, dùng -E:

		gcc -E prog.c 		// Giả sử src được located trong prog.c file

	- Option này làm compiler stop ngay khi preprocessor hoàn thành function của nó.
		src tiền xử lí được gửi tới standard output và tất cả sửa đổi bởi preprocessor sẽ được marked một cách đặc biệt

	- Muốn preserve text tiền xử lí để phân tích:

		gcc -E prog.c > outputfilename

	- Có thể chọn tên output thoải mái, nhưng đảm bảo output file name không phải tên của source file hay tên gì mà mình muốn giữ, vì có thể sẽ mất nó.

	- Note: preprocessor insert nhiều thông tin khác nhau vào code. Marking bị bỏ qua trong quá trình verification và translation củc chtrinh. Ta nhận diện nó bằng kí tự # trong lines, giống như trong preprocessor directives.
		. "-E" option nên dùng thường xuyên vì cực kì instructive và useful
	- Các nguyên tắc:
		. preprocessor directives (chỉ thị tiền xử lý) luôn bắt đầu với #
		. Nếu không thể viết trong 1 line và cần split, phải put ký tự '\' nơi directive bị broken

			#include \
			<stdio.h>

		. Bất kì chỉ thị tiền xử lý nào được đặt trong particular file chỉ hoạt động trong file này chứ không có ở nơi khác


8.1.2.1 Preprocessor: the #include directive
	- "#include" directive hoạt động như sau:
		. Bộ tiền xử lý tìm file tên filename, nhưng nếu để tên đó trong quotes, thì nó sẽ tìm file đó trong cùng thư mục với tệp chứa directive
			Không thì nó sẽ tìm file trong thư mục mặc định của compiler.
			Unix thường dùng /usr/include.

		. Nếu không tìm thấy file, bộ tiền xử lý sẽ report 1 error; Nếu không, chỉ thị #include được thay thế bởi nội dung của file được included

		. File được included cũng có thể chứa chỉ thị #include; thêm nữa, 1 compiler cụ thể có thể impose (áp đặt) 1 giới hạn nhất định số lượng lần lồng nhau của các file
			Kiểu như có 1 tệp A bao gồm tệp B, tệp B bao gồm tệp C và tiếp tục như vậy. Tuy nhiên, 1 số compiler có thể giới hạn sâu độ lồng nhau này để ngăn chặn việc sử dụng quá nhiều tệp được nhúng lồng nhau, tránh gây ra vấn đề về quản lý bộ nhớ hoặc thời gian biên dịch không cần thiết.

		. Có thể dùng chỉ thị #include ở bất kì đâu, không chỉ ở đầu.

			#include <filename>

			#include "filename"


8.1.2.2
	- Giả sử có 2 source files:
		. src1.c:

			int main(void) 
			{
				#include "src2.c"
			}

		. src2.c:

			int i = 0;
			return i;
	- Khi start gcc compiler với command như sau:

		gcc -E src1.c

	trên màn hình sẽ hiện như này:

		# 1 "src1.c"
		# 1 ""
		# 1 ""
		# 1 "src1.c"
		int main(void) {

		# 1 "src2.c" 1
		int i = 0;

		return i;
		# 4 "src1.c" 2
		}

	- Vì các lines được đánh dấu bằng ký tự # được compiler sử dụng nội bộ nên chúng ta có thể bỏ qua chúng và giả sử rằng dạng cuối cùng của preprocessed code như sau:

		int main(void)
		{
			int i = 0;
			return i;
		}

	- Nên làm vài thử nghiệm với nested include directives


8.1.3.1
	Three forms of the directive

	- Chỉ thị #define có thể là 1 trong 3 dạng sau:

		#define identifier text

		#define identifier(parameter_list) text

		#define identifier

	- Dạng đầu tiên:
		. Bộ tiền xử lý nhớ từ khóa identifier và text đã liên kết với nó
		. Từ thời điểm này, bộ tiền xử lý phân tích src, thay thế bất kì sự xuất hiện nào của identifier với text đã liên kết
		. Chỉ thị #define tự nó sẽ không xuất hiện trong preprocessed src.


8.1.3.2
	#define: simple substitution

	- Example:

		/* Source code: */

		#define PI 3.1415

		int main(void) 
		{
			float s = 2 * PI * 10.0;
			return 0;
		}


		/* Preprocessed code: */


		int main(void) 
		{
			float s = 2 * 3.1415 * 10.0;
			return 0;
		}

	- Note: PI là 1 identifier, 3.1415 là text

	- Identifier được sử dụng bên trong #define (giống như PI) gọi là macro và quá trình thay thế nó bằng text tương ứng được gọi là macro substitution. Thông thường, tên macro in hoa, giúp phân biệt với tên variable thông thường. 
		Điều này không phải là một quy tắc tuyệt đối, nhưng được rất nhiều người công nhận và sử dụng.


8.1.3.3
	- Dạng chỉ thị này thường được sử dụng để cải thiện khả năng đọc của chương trình và làm cho việc sửa đổi dễ dàng hơn.

	- Example:

		#include <stdio.h>

		int main(void) 
		{
			int arr[100], i, sum = 0;

			for(i = 0; i < 100; i++)
				arr[i] = 2 * i;
			for(i = 0; i < 100; i++)
				sum += arr[i];
			for(i = 0; i < 100; i++)
				printf("%d\n", arr[i]);

			printf("%d\n", sum);
			return 0;
		}

	- Tưởng tượng rằng phải sửa đổi chương trình để có thể xử lý một mảng chứa không chỉ 100 mà là 5000 giá trị int.

	- Ở bao nhiêu nơi bạn sẽ phải thay đổi mã nguồn? Bạn có chắc rằng bạn sẽ không bỏ sót bất kỳ nơi nào không?

	- Những sửa đổi này thường là nguyên nhân gây ra những lỗi phiền toái và dai dẳng, có thể tốn thời gian và cực kỳ khó tìm ra.


8.1.3.4
	- Giờ chỉ cần dùng chỉ thị #define như sau:
		
		#define SIZE 100

	và thay bằng line:

		#define SIZE 5000

	là easy game ngay.

	- Example:

		#include <stdio.h>

		#define	SIZE	100

		int main(void) 
		{
			int arr[SIZE], i, sum = 0;
			for(i = 0; i < SIZE; i++)
				arr[i] = 2 * i;
			for(i = 0; i < SIZE; i++)
				sum += arr[i];
			for(i = 0; i < SIZE; i ++)
				printf("%d\n", arr[i]);
			printf("%d\n", sum);
			return 0;
		}


8.1.3.5 -> 8.1.3.6
	#define: disadvantages and perils

	- Nếu dùng không cẩn thận sẽ sai, ví dụ:

		#define SIZE 4 + 4
		int main(void) 
		{
		    int i;
		    i = 2 * SIZE;
		    printf("%d\n",i);
		    return 0;
		}

	- Thoạt nhìn thì có vẻ Output là 16, nhưng mà thực ra là 12

	- Muốn khắc phục thì chỉ cần thêm brackets

		#define SIZE (4 + 4)

	#define: predefined identifiers

	- Nhiều identifiers ta từng dùng như NULL, EOF,... thực ra là macros

	- Nếu nhìn vào "stdio.h" và "stdlib.h" header files, ta sẽ thấy các #define như sau:

		#define NULL        ((void *) 0)

		#define EOF     (-1)

		#define SEEK_SET    0
		#define SEEK_CUR    1
		#define SEEK_END    2


8.1.4.1 Preprocessor: the parameterized #define directive
	The second form of the #define directive

	- Syntax như sau:

		#define identifier(parameter_list) text

	- Chỗ parameter_list nên bao gồm ít nhất một pairwise identifier (cặp định danh), separated by commas

	- Note: dấu mở ngoặc nên dính với identifier, không cho phép có kí tự nào giữa identifier và ngoặc mở. Nếu không thì bộ xử lý sẽ coi nó là variant đầu tiên của chỉ thị #define.

	- Macro định nghĩa theo cách này gọi là macro with parameters, hoặc là parameterized macro.

	- Nếu bộ tiền xử lý gặp identifier giống với định nghĩa của 1 macro, nó sẽ:
		. Mỗi tham số macro trong text được thay thế bằng argument được chỉ định trong src

		. Macro identifier, cùng với parameter list, được thay thế bởi text tạo ra trong bước đầu tiên


8.1.4.2
	Parameterizing the #define directive

	- Phân tích 1 example:

		/* Source code: */

		#define SQR(x)	(x * x)
		float f = SQR(length);

		/* Preprocessed code: */

		float f = (length * length);

	- First step of the macro substitution sẽ làm cho tham số x bị thay thế bằng đối số của macro (tức "length"). String sau sẽ được tạo ra:

		(length * length)

	- Second step sẽ thay thế macro bằng string mới tạo ra.


8.1.4.3
	A macro is not a function!

	- Note: Macro chỉ giống hàm chứ không phải hàm.
		Có 2 khác biệt quan trọng

	- Giả sử parameterized macro được sử dụng như sau:

		/* Source code: */

		#define SQR(x)	(x * x)
		float f = SQR(length + 1)

		/* Preprocessed code: */

		float f = (length + 1 * length + 1)

	- Nếu SQR là 1 function thì không có gì đặc biệt ở đây, expression (length + 1) được squared và return value

	- Thực ra SQR là 1 macro, nó sẽ trông giống fragment thứ 2 trong đoạn code trên.


8.1.4.4
	- Phân tích 1 ví dụ khác:

		/* Source code: */

		#define SQR(x)	((x) * (x))
		float f = SQR(length++)

		/* Preprocessed code: */

		float f = ((length++) * (length++))

	- Nếu SQR là function thì:
		. returns value của (length * length);
		. biến length tăng 1

	- Nhưng vì là macro nên "f" variable field được gán với giá trị của expression sau:

		((length++) * (length++))

	tức là lúc này biến length sẽ tăng 2 chứ không phải 1.


8.1.4.5
	Một vài ví dụ về parameterized macros

	- Xét ví dụ sau:

		/* Source code: */

		#define	MAX(X,Y)	(((X) > (Y)) ? (X) : (Y))

		int main(void) {
			int var1 = 100, var2 = 200, var;
			float v1 = -1.0, v2 = 1.0, v;

			var = MAX(var1,var2);
			v = MAX(v1,v2);

			return 0;
		}

		/* Preprocessed code: */


		int main(void) { 
			int var1 = 100, var2 = 200, var; 
			float v1 = -1.0, v2 = 1.0, v; 

			var = (((var1) > (var2)) ? (var1) : (var2)); 
			v = (((v1) > (v2)) ? (v1) : (v2)); 

			return 0; 
		}

	- "MAX" macro dùng để tìm số lớn hơn trong 2 số

	- Giải thích điều gì sẽ xảy ra nếu không có parentheses trong macro?


8.1.4.6
	- Dựa vào "MAX" macro như trên, ta vẫn viết được macro phức tạp hơn.

	- E.g. MAX3 là tìm số lớn nhất trong 3 số
		Có thể nhìn rất lú, nhưng mà preprocessed code còn lú hơn.

		/* Source code: */


		#define MAX(X,Y)    (((X) > (Y)) ? (X):(Y))
		#define MAX3(X,Y,Z) (MAX((MAX((X),(Y))),(MAX((Y),(Z)))))

		int main(void) {
			int a = 1, b = 2, c = 3, w;
			w = MAX3(a + 1,b - 1,2 * c);
		}


		/* Preprocessed code: */


		int main(void) { 
		int a = 1, b = 2, c = 3, w; 
		w = (((((((((a + 1)) > ((b – 1))) ? ((a + 1)) : ((b – 1))))) > ((((((b – 1)) > ((2 * c))) ? ((b – 1)) : ((2 * c)))))) ?

		 ((((((a + 1)) > ((b – 1))) ? ((a + 1)) : ((b – 1))))) : ((((((b – 1)) > ((2 * c))) ? ((b – 1)) : ((2 * c))))))); 
		}


8.1.5.1 Preprocessor: the third variant of the #define and #undef directives

	- Variant thứ 3 của chỉ thị #define, cũng là variant đơn giản nhất:

		#define identifier

	- Chỉ thị này ảnh hưởng đến các hoạt động tiền xử lý như sau:

		. Khiến bộ tiền xử lý assume rằng identifier là 1 identifier đã defined (tức là compiler đã biết nó)

		. The directive sẽ không xuất hiện trong preprocessed src.

		. Src sẽ không đổi bằng bất kì cách nào

	- Bộ tiền xử lý có 1 vài features dùng để kiểm tra xem 1 identifier được defined hay chưa. Điều này để xác định liệu một phần của src có được biên dịch hay bị bỏ qua hay không.
		Cơ chế này gọi là conditional compilation (Biên dịch có điều kiện), sẽ được nói sau.


	The #undef directive
	- Chỉ thị #undef thì cancels những effects của chỉ thị #define đã chọn và có cú pháp như sau:

		#undef identifier

	- The "identifier" không cần phải được defined trước đó.

	- Từ lúc #undef được dùng, identifier không còn được defined nữa


8.1.5.2 the third variant of the #define and #undef directives
	- Phân tích src sau:

		int add(int x) 
		{
			return x + 1;
		}

		int main(void) 
		{
			int i = 100;
			i = add(i);

		#define add(x)    (2 * (x))

			i = add(i);
		
		#undef add
		
			i = add(i);
			printf("%d",i);
			return 0;
		}

	- Preprocessed của src trên như sau:

		int add(int x) 
		{
		    return x + 1;
		}

		int main(void) 
		{
		    int i = 100;
		    i = add(i);
		    i = (2 * ( i )) ;
		    i = add(i);
		    printf("%d",i);
		    return 0;
		}

8.1.6.1 Preprocessor: predefined identifiers
	The __LINE__ identifier

	- Đã biết:
		. "#define" directive có thể dùng để define own identifier.
		. cách các definitions này bị canceled.
		. có 1 lượng identifiers được defined bởi chính preprocessor.
			Có thể sử dụng những symbols này nhưng không được phép undefined chúng

	Xem xét những identifier quan trọng nhất và những examples

	- Đầu tiên là __LINE__
		note: the double underscores enclosing its name (dấu gạch dưới kép bao quanh) là quy ước chung cho các identifier được declared implicitly (khai báo ngầm)

	- Khi sử dụng LINE thì nó sẽ thay thế bằng kí tự số nguyên là số dòng nơi ký hiệu xuất hiện
		Cũng có nghĩa là mỗi nơi kí hiệu sẽ có giá trị khác nhau

	- Example:

		1	#include <stdio.h>
		2
		3	int main(void) {
		4		printf("this is line #%d\n", __LINE__);
		5
		6		printf("this is line #%d\n", __LINE__); 
		7
		8
		9
		10		printf("this is line #%d\n", __LINE__);
		11		return 0;
		12	}

	- Code này khi qua preprocessor có form như sau:

		#include <stdio.h>

		int main(void) {
		    printf("this is line #%d\n", 4);

		    printf("this is line #%d\n", 6);



		    printf("this is line #%d\n", 10);
		    return 0;
		}

	- Có thể dùng symbol này trong các error messages để thông báo cho user/developer vị trí lỗi encountered và diagnosed


8.1.6.2
	The __FILE__ identifier

	- __FILE__ sẽ thay thế bởi string chứa tên của source file mà identifier được dùng trong nó

	- Note: string sẽ được enclosed trong double quotes (như những string khác trong "C"), tức là chuỗi sẽ có giá trị khác nhau trong mỗi source file

		#include <stdio.h>

		int main(void) {
			puts("Hello from the source file named "__FILE__);
			return 0;
		}

	- Giả sử code này được đặt trong file tên filesym.c, sau khi qua preprocessor nó sẽ có form như sau:

		#include <stdio.h>

		int main(void) {
		    puts("Hello from the source file named ""filesym.c");
		    return 0;
		}

	- Để ý ký tự ", có 1 rule trong C đó là 1 string có thể broken tại 1 điểm nào đó với kí tự ", và sau đó là bất kì số lượng (kể cả 0) khoảng trắng, rồi chuỗi có thể tiếp tục với ký tự " khác.


8.1.6.3
	The __DATE__ identifier

	- __DATE__ thay thế 1 string chứa text denoting the day (chỉ ngày) mà source file được compiled.

	- String được enclosed trong double quotes. Tức là symbol có nhiều giá trị mỗi ngày.

		#include <stdio.h>

		int main(void) {
			puts("The program was successfully compiled on " __DATE__);
			return 0;
		}

	- Code này qua preprocessor nhìn như sau:

		#include <stdio.h>

		int main(void) {
		    puts("The program was successfully compiled on " "Aug 22 2012");
		    return 0;
		}

	- Date string luôn chứa 11 ký tự

	- Code trên khi compiled và run sẽ emit text sau:

		The program was successfully compiled on Aug 22 2012


8.1.6.4
	The __TIME__ identifier

	- __TIME__ luôn thay thế bởi string chứa text denoting the time (hours, minutes, seconds) the source file đã compiled.

	- String sẽ được enclosed trong double quotes. Tức là symbol này có giá trị khác nhau mỗi lần nó được compiled.

		#include <stdio.h>

		int main(void) {
			puts("I was compiled at " __TIME__);
			return 0;
		}

	- Code này sau khi qua preprocessor nhìn như sau:

		#include <stdio.h>

		int main(void) {
		    puts("
		I was compiled at " "12:13:23");
			return 0;
		}

	- Time string luôn chứa 8 ký tự

	- Khi compiled và run, code sẽ emit text sau:

		I was compiled at 12:13:23


8.1.6.5
	The __STDC__ identifier

	__STDC__ (as in Standard C) được defined khi và chỉ khi:

		Compiler hoạt động in compliance with ANSI "C" standard

	- Khi ANSI mode is on, compiler chỉ tuân theo các yếu tố ngôn ngữ được mô tả trong standard documents, và không áp dụng bất kì extensions hay limitations nào.

	- Nếu compiler không hoạt động trong ANSI mode, symbol này sẽ không được defined.


8.1.7.1 Preprocessor: operators
	The # operator

	- Preprocessor chỉ recognizes và interprets được 2 operators. Chúng được sử dụng để thuận tiện cho xử lý string diễn ra trong qutrinh mở rộng macro.

	- Important: Những operators này chỉ hoạt động trong preprocessing phase (giai đoạn) và biến mất khỏi src khi preprocessor hoàn thành việc của nó.
		Không dùng nó ngoài chỉ thị #define.

	- Toán tử # (đừng nhầm với # ở đầu các directive) là một prefix unary operator (toán tử tiền tố đơn ngôi) được sử dụng như sau:

		#argument

		trong này argument là 1 string, được retrieved từ tham số macro

	- Toán tử affects macro trong expansion phase và khiến argument của nó được enclosed bởi a pair of quotes, biến đổi initial "argument" thành như sau:

		"argument"

	- Note: Không thể làm điều này bằng cách nào khác, vì 1 macro như sau:

		#define QUOTE(X) "X"

	sẽ không hoạt động như mong đợi. Preprocessor không nhìn vào string bên trong. Chúng là untouchable đối với preprocessor và do đó kí hiệu X không được nhận diện như một formal macro parameter

	- Correct solution:

		#define QUOTE(X) #X

	- Macro này, khi được dùng trong chtrinh theo cách sau:

		QUOTE(MaryHadALittleLamb)

	sẽ được mở rộng thành:

		"MaryHadALittleLamb”


8.1.7.2
	- Minh họa mục đích của toán tử này bằng 1 practical và useful example

	- Tưởng tượng đang phát triển một program phức tạp. Bạn muốn có 1 cơ chế đơn giản, tiện lợi cho phép hiển thị các giá trị cảu các key variables.

	- Chắc chắn ta sẽ không muốn viết các snippets như này:

		printf ("var i = %d", i);
		printf ("var counter = %d", count);
		printf ("variable TotalSheep  = %d", TotalSheep);

	- Viết những snippets này làm cho developer weary (mệt mỏi), vấn đề là phải viết cùng 1 cụm (tên của biến cần hiển thị) 2 lần: bên trong 1 format string và 1 lần nữa as printf's parameter.

	- 1 godsend đến từ form của 1 macro được xây dựng thông minh, sử dụng toán tử #

		#define SNAP(X) printf("variable "#X" = %d\n",X);

	- Dùng nó để "chụp" ảnh của các biến.


8.1.7.3
	- Ta sử dụng macro mới trong đoạn code sau:

		#include <stdio.h>

		#define SNAP(X) printf("variable "#X" = %d\n",X)

		int main(void) {
			int i = 0;
			int counter = 1;
			int SheepTotal = 261;

			SNAP(i);
			SNAP(counter);
			SNAP(SheepTotal);

			return 0;
		}

	- Code trên được mở rộng thành form như sau:

		int main(void) {
		    int i = 0;
		    int counter = 1;
		    int SheepTotal = 261;

		    printf("variable ""i"" = %d\n",i);
		    printf("variable ""counter"" = %d\n",counter);
		    printf("variable ""SheepTotal"" = %d\n",SheepTotal);

		    return 0;
		}

	- Xem cẩn thận cách macro SNAP được mở rộng để hình dung đầy đủ về khả năng của toán tử #.


8.1.7.4 Preprocessor: operators
	The ## operator

	- Toán tử ## là 1 binary operator yêu cầu 2 arguments, được sử dụng như sau:

		ARGUMENT1 ## ARGUMENT2

	- Note: bạn không thể làm điều này theo bất kì cách nào khác, vì 1 macro như sau:

		#define GLUE (X,Y) XY

	sẽ không hoạt động. Preprocessor nhận diện XY identifier, không phải X và Y.

	- Correct solution:

		#define GLUE(X,Y)  X##Y

	- 1 macro GLUE được dùng như sau:

		GLUE(MaryHad, ALittleLamb)

	sẽ được mở rộng thành form:

		MaryHadALittleLamb


8.1.8.1 Preprocessor: conditional compilation
	The #if, #endif, #else and #elif directives
	- Nhìn chung thì các conditional compilation directives được sử dụng giống trong code dưới:

		#if expression0
		text0
		#elif expression1
		text1
		#elif expression2
		text2
		  :
		  :
		#elif expressionn
		textn
		#else
		texte
		#endif

	- Nếu dùng #if thì phải dùng #endif. Giữa 2 directives này, có thể dùng bất kì số lượng bao nhiêu #elif (viết tắt của else if) và tối đa 1 #else. Các expressions đặt sau các #if và #elif được dùng để quyết định texts nào sẽ được chuyển đến để compile tiếp theo.

	- Vì những expressions này được evaluated bởi preprocessor, không phải bởi compiler, nên vào thời điểm variable values chưa được biết, chúng phải được evaluated riêng, thông qua:
		. preprocessor symbols mà được gán giá trị số (dùng #define)

		. Toán tử: +, -, *(nhân), /, >>, <<, >, <, >=, <=, ==, !=, %, & (AND logic), &&, |, ||;

		. Các sub-expressions (biểu thức con) được enclosed trong parentheses

		. Một pseudo-function tên là defined, có đối số là 1 symbol và kết quả của nó là 1 nếu symbol đó được defined - nếu không kết quả sẽ là 0.

	- Một số directives có thể đơn giản hóa. Ví dụ:

		#if defined(IDENT)

	có thể viết như sau:

		#ifdef IDENT

	và 1 directive như sau:

		#if !defined(IDENT)

	có thể có form:

		#ifndef IDENT

	- Quá trình interpreting những chỉ thị này như sau:
		. Giá trị của expression0 được evaluated trước tiên và nếu kết quả của nó khác 0, text0 được chuyển đến compiler; Trong trường hợp này, tất cả texts khác đều bị bỏ qua và không được compiled.

		. Nếu không, preprocessor sẽ tính toán giá trị của expression1; Nếu khác 0, text1 được compiled và tất các texts khác đều bỏ qua.

		. Khi không có expression nào được evaluated là khác 0, chỉ có text liên kết với #else directive được compiled.


8.1.8.2
	- Xem 2 ví dụ đơn giản để minh họa cách sử dụng các directives trên:

		int ElementsToSort = ReadElementsFromFile();
		#ifdef DEBUG
		SNAP(ElementsToSort);
		#endif

	- Tưởng tượng rằng, do 1 vài vấn đề, ta quyết định dùng macro SNAP trong code. Macro này giúp xác định lỗi và định vị nguyên nhân đầu tiên gây ra. Chtrinh có vẻ hoạt động đúng khi code như sau:

	- Tất nhiên có thể xóa hết code liên quan SNAP, nhưng nếu sự cố xảy ra lại thì sao? Bạn có thể loại trừ khả năng có 1 số lỗi khác trong code và phải kiếm chúng 1 lần nữa.

	- Quá trình tìm lỗi và loại bỏ nó gọi là debugging. Ta phải debug code khi nghi ngờ rằng nó không hoạt động đúng.

	- Có thể dùng SNAP khi đang debug code và tắt nó khi debug xong

	- Có thể dùng các conditional compilation directives cho việc này, xem code sau:

		int ElementsToSort = ReadElementsFromFile();
		SNAP(ElementsToSort);

	- Line mà tham chiếu đến SNAP sẽ được compiled khi và chỉ khi chỉ thị DEBUG được defined, và nó sẽ hoàn toàn bỏ qua trong trường hợp ngược lại.

	- 2 cách define chỉ thị DEBUG. 
		. Cách 1 đã biết: thêm 1 line như sau vào bất kì chỗ nào của code (nhưng tất nhiên phải trước #if đầu tiên)

			#define DEBUG

		- Cách thứ 2: dựa trên 1 điều rằng các C language compilers đều có thể define 1 identifier bên nogài src. Ta có thể yêu cầu compiler define bất kì identifier nào trước khi bắt đầu biên dịch src. Tham khảo documentation để biết thêm. GCC compiler cần một tùy chọn để thực hiện, trông như sau:

			gcc -D DEBUG filec.c

		- Source file có tên filec.c sẽ được compiled, giả định rằng DEBUG đã được defined trước đó.

8.1.8.3
	Avoiding multiplied compilations
	- Thường 1 header file được included ngầm nhiều lần trong source file. Ta có thể tượng tượng mẫu như sau:

		defs.h → functions.h → functions.c 
		defs.h → functions.h → main.c
		defs.h → main.c

		. Header file có tên là defs.h định nghĩa một số entities (ví dụ: kích thước của mảng) được sử dụng bởi tất cả các file khác;

		. Header file có tên là functions.h chứa các prototypes của một số function hữu ích; file này bao gồm file defs.h;

		. Source file có tên là functions.c chứa các khai báo cho các function ở trên; file này bao gồm file functions.h;

		. Source file có tên là main.c chứa main function mà gọi các function được khai báo trong file nguồn functions.c bằng cách bao gồm header của nó. Ngoài ra, main.c cũng bao gồm file defs.h.

	- Giả sử rằng ký hiệu mũi tên là tương đương với cụm "is included by" chúng ta có thể vẽ sơ đồ như có thể thấy trong editor.

	- Điều này có nghĩa là khi chúng ta biên dịch file nguồn main.c, chúng ta khiến "defs.h" file header được included (và biên dịch) 2 lần: lần đầu tiên bởi functions.h header file và lần thứ hai bởi main.c file.

	- Tình huống này là tình huống không mong muốn, bởi vì một số identifiers không thể được defined/declared nhiều lần.


8.1.8.4
	- Conditional compilation directives có thể lồng như các chỉ thị điều kiện thông thường. Phân tích src sau:

		#include <stdio.h>
		#define	SIZE 100

		int main(void) {
			int	array[SIZE];

		#if SIZE < 1000
			puts("The array is not so large");
		#else
			puts("The array is "
		#if SIZE > 10000
			"very "
		#endif
			"large ");
		#endif
			return 0;
		}

	- Biên dịch chương trình này sẽ tạo ra 1 code thực thi phát ra text sau đây đến "stdout" stream:

		The array is not so large

	khi SIZE được định nghĩa với một giá trị nhỏ hơn 1000.

	The text:

		The array is very large

	xuất hiện nếu SIZE có giá trị lớn hơn 10000.

	The text:

		The array is large

	xuất hiện trong trường hợp còn lại.

8.1.8.5
	- Đây là một mẫu contents của những files.

	- Phân tích tất cả inclusions diễn ra khi main.c file được compiled.

		defs.h

		#define SIZE 100

		functions.h

		#include "defs.h"
		int set(int t[][SIZE]);

		main.c

		#include "defs.h"
		#include "functions.h"
		int main(void) {
		    int arr[100][SIZE];
		    printf("%d", set(arr));
		    return 0;
		}
		int set(int t[][SIZE])
		{
		    return 0;
		}

	- Làm sao ngăn việc "defs.h" header được included nhiều lần?

	- Làm điều đó bằng cách sử dụng các conditional compilation directives. Mỗi header file dùng trick sau:
		. Check xem 1 ký hiệu đặc biệt có được defined trước đó không và bỏ qua phần còn lại của file nếu điều này đúng.

		. Nếu không, define ký hiệu này

	- Một điều được chấp nhận rộng rãi, là ký hiệu đặc biệt này được tạo ra từ header file theo cách đơn giản sau:

		. file name: header.h
		. identifier: __HEADER_H__

	- Giờ ta có thể sửa 1 chút những headers.

	- Phân tích code đã sửa đổi

	- Giải thích tại sao "defs.h" header file được compiled chỉ 1 lần?

		defs.h

		#ifndef __DEFS_H__
		#define __DEFS_H__
		#define SIZE 100
		#endif

		functions.h

		#ifndef __FUNCTIONS_H__
		#define __FUNCTIONS_H__
		#include "defs.h"
		int set(int t[][SIZE]);
		#endif

		main.c

		#include "defs.h"
		#include "functions.h"
		int main(void) {
		    int arr[100][SIZE];
		    printf("%d", set(arr));
		    return 0;
		}


8.1.8.6 LAB: Preprocessing: Part 1

8.1.8.7 LAB: Preprocessing: Part 2

8.1.9.1 The scope of the declaration
	The scope: what it really is

	- Bằng cách khai báo một số identifier cụ thể trong chương trình C, bạn không chỉ tạo ra một entity mới (ví dụ: một biến hoặc một hàm), mà bạn cũng xác định nơi mà entity đó có thể truy cập.

	- Xem xét đoạn code:

		int variable;

		int fun1(int x) {
			int i;

			i = 2 * x;
			return i;
		}

		int fun2(void) {
			variable *= 2;
		}

	Đây là một source file hoàn chỉnh. Ta có thể thấy:
		. variable có thể truy cập trong toàn bộ source file; bạn có thể sử dụng nó bên trong bất kỳ hàm nào;

		. x chỉ có thể truy cập trong hàm fun1; fun2 không biết gì về nó và không được phép sử dụng nó; kết luận tương tự áp dụng cho ký hiệu i;

		. fun1 và fun2 có thể truy cập trong toàn bộ module.

	- Scope of a declaration (Phạm vi của một khai báo) là 1 phần của chương trình mà một identifier cụ thể được nhận diện và có thể truy cập.

	Ngoài ra, bạn có thể thêm một kiểu linkage (liên kết) vào khai báo. Linkage là quá trình quyết định xem một identifier đã được khai báo nhiều lần có đề cập đến cùng một đối tượng (hoặc hàm) hay không. Có ba loại linkage:
		. internal linkage: mỗi khai báo identifier lặp lại bên trong một source file chỉ định cùng một đối tượng;

		. external linkage: mỗi khai báo identifier lặp lại trong toàn bộ chương trình chỉ định cùng một đối tượng;

		. No linkage: có nghĩa là mỗi khai báo mô tả một đối tượng duy nhất.


8.1.9.2
	Different scopes

	- Phạm vi của các scopes khác nhau được mô tả bởi các quy tắc sau:
		. Scope của 1 identifier được khai báo bên ngoài function body mở rộng từ điểm mà nó được khai báo đến cuối module;

		. Scope của 1 identifier được khai báo như một tham số hàm mở rộng từ khai báo đến cuối function body;

		. Scope của 1 identifier được khai báo bên trong hàm mở rộng từ khai báo đến cuối block mà khai báo đó xuất hiện.

	- Quy tắc thứ ba có thể gây ngạc nhiên một chút. Ta đã đề cập cách đây một thời gian rằng mỗi block có thể chứa các khai báo của riêng mình và điều này rất quan trọng đối với quy tắc này. Xem xét code sau:

		int func(int param) {
			int var = 2;
			if(param > 0) {
				int i = param + 1;
				var = 2 * i;
			}
			return var;
		}

	- Chúng ta có thể thấy rằng:
		. Scope của identifier "param" mở rộng cho toàn bộ function body;
		. Scope của identifier "var" mở rộng từ vị trí khai báo đến cuối function body;
		. Scope của identifier "i" mở rộng từ vị trí khai báo đến cuối của innermost block và có phạm vi lớn hơn đáng kể so với function body.


8.1.9.3
	Different linkages

	- Hãy giả sử rằng project của chúng ta bao gồm 2 modules:

		/* module1.c */

		int variable;

		int fun1(int x) {
		    int i;

		    i = 2 * x;
		    return i;
		}

		int fun2(void) {
		    variable *= 2;
		}


		/* module2.c */

		extern int variable;

		int fun2(void);

		int fun3(int param) {
		    variable = param;
		    return fun2();
		}

	- Chúng ta có thể nói rằng:
		. Phạm vi của param không có liên kết và có phạm vi khối;
		. Linkage của fun2 là external (identifier đã được khai báo trong module1.c, nhưng sau khi trích dẫn prototype hàm, nó đã trở nên có sẵn trong module2.c);
		. Vì chỉ định lớp bộ nhớ extern, nhận dạng biến variable có thể được định nghĩa (với external linkage) bên trong hoặc bên ngoài translation unit của module2.c.


8.1.9.4
	Hiding identifiers

	- Chúng tôi đã sửa đổi code của chúng tôi một chút. Chúng tôi đã thêm một khai báo bên trong innermost block, ngay sau từ khóa if. Xem code dưới đây:

		int func(int param) {
		    int var = 2;
		    if(param > 0) {
		        int var;
		        int i = param + 1;
		        var = 2 * i;
		    }
		    return var;
		}

	- Đây không phải lỗi! Chúng ta có hai biến có cùng tên (var) và scope của biến thứ hai được hoàn toàn bao gồm trong scope của biến thứ nhất. Điều này sẽ có tác động như thế nào?

	- Ví dụ minh họa cơ chế được biết đến là hiding. Cơ chế này hoạt động như thế nào?
		. Khai báo đầu tiên của biến var giúp biến được known to the compiler;
		. Khai báo tiếp theo (bên trong inner block) của biến có cùng tên ẩn đi khai báo trước đó; điều này có nghĩa là khai báo trước đó tạm thời mất đi ý nghĩa và trở thành không khả dụng;
		. Biến var thứ hai (bên trong) mất đi ý nghĩa của nó khi kết thúc block mà nó được khai báo; cùng lúc đó, biến var đầu tiên trở lại được truy cập.


8.1.10.1 Storage classes
	Three storage classes

	- Mỗi từ khóa được hiển thị phía dưới chỉ định lớp bộ nhớ, một hướng dẫn chi tiết cho compiler về cách allocate và manipulate bộ nhớ.

	- Một số từ khóa có thể precede (đứng trước) các khai báo biến (như từ khóa extern, mà chúng ta đã quen thuộc). Một số từ khóa cũng có thể đứng trước các khai báo hàm, và trong trường hợp đó, ý nghĩa của chúng có thể khác nhau. Bây giờ chúng ta sẽ thảo luận về việc sử dụng các từ khóa này trong một số ngữ cảnh khác nhau.

8.1.10.2
	An internal variable declared as an extern

	- Example:

		extern int amount;

	Ta đã hiểu ý nghĩa của khai báo này.

	- Một biến được khai báo như một local variable trong một module (ngoài mọi block) khiến compiler cho rằng một biến có cùng tên được định nghĩa trong một module khác. Điều này cũng có nghĩa là các biến khác được khai báo với từ khóa extern, và có cùng tên, sẽ được coi là một tham chiếu đến cùng một biến.

	- Hãy xem xét 2 module sau:

		/* module1.c */

		extern int variable;

		void increment(void) {
		    variable++;
		}


		/* module2.c */

		#include 


		int variable;

		void increment(void);

		int main(void) {
			variable = 0;
			increment();
			printf("%d",variable);
			return 0;
		}

	- Chương trình xuất kết quả là 1. Bạn có thể giải thích tại sao không?

	- Chương trình cũng xuất kết quả là 1 vì khai báo của hàm increment trong module2 được ẩn ý là có external linkage, tức là nó có thể được định nghĩa ở một nơi khác.


8.1.10.3
	A local function variable

	- Biến cục bộ của hàm được khai báo as static

	- Một ví dụ về loại khai báo này có thể là câu lệnh sau:

		static int counter;

	- Một biến được khai báo bên trong một hàm với thuộc tính static là một static variable - biến tĩnh (để phân biệt nó với automatic variable - biến tự động). Nếu một khai báo biến được đặt trước bởi từ khóa static, điều này có nghĩa là biến được tạo ra khi chương trình bắt đầu và bị hủy khi chương trình kết thúc công việc của nó.

	- Hãy xem xét function sau:

		void fun(void) {
			int i = 0;

			printf("entering fun: i = %d\n", i);
			i++;
			printf("exiting fun: i = %d\n", i);
			return;
		}

	- Biến i được khai báo mà không có thuộc tính static, vì vậy nó là một automatic variable. Nó sẽ được tạo ra mỗi khi hàm được gọi và bị hủy khi hàm kết thúc.

	- Điều này có nghĩa là mỗi khi bạn gọi hàm fun, bạn sẽ nhận được text không đổi sau được gửi đến stream stdout:

		entering fun: i = 0
		exiting fun: i = 1


8.1.10.4
	- Hãy xem xét code đã được sửa đổi. Biến i giờ đây là một biến tĩnh (static).

	- Expect các kết quả sau:

		. Biến i sẽ được thiết lập một lần (trong phần đầu của chương trình);
		. Biến sẽ được gán giá trị ban đầu một lần (!);
		. Do đó, biến sẽ có thể giữ giá trị của nó giữa các lần gọi của hàm.

	- Điều này có nghĩa là lần gọi hàm đầu tiên sẽ tạo ra text sau:

		entering fun: i = 0
		exiting fun: i = 1

	trong khi lần gọi thứ hai sẽ tạo ra đầu ra sau:

		entering fun: i = 1
		exiting fun: i = 2

	- Lần gọi thứ ba:

		entering fun: i = 2
		exiting fun: i = 3

	và cứ tiếp tục như vậy.

8.1.10.5
	A local module variable declared as static

	- Khai báo của một biến tĩnh có phạm vi mở rộng đến toàn bộ module có thêm 1 ý nghĩa nữa: nó không cho phép phạm vi của biến được mở rộng ra ngoài parent module.

	- Biến sẽ không được truy cập trong các module khác, ngay cả khi có sử dụng từ khóa extern.

	- Xem xét ví dụ sau. Chúng ta có 2 modules riêng biệt

		/* module1.c */

		static int variable;

		void fun1(void) {
			variable = 1;
		}


		/* module2.c */

		#include <stdio.h>

		extern int variable;

		void increment(void);

		int main(void) {
			variable = 0;
			increment();
			printf("%d",variable);
			return 0;
		}

	- Biến từ module đầu tiên giờ đây là biến tĩnh. Phạm vi của nó chỉ mở rộng đến module1.c, tức là nó không khả dụng trong bất kỳ module nào khác.

	- Điều này có nghĩa rằng chương trình mẫu sẽ bị erroneous (bị sai). Bạn sẽ không thể biên dịch nó thành công, vì module thứ hai thông báo sai cho compiler rằng biến được định nghĩa với external linkage bên trong module khác.

	- 1 entity (biến hoặc hàm) mà phạm vi chỉ giới hạn trong một module duy nhất được gọi là have internal linkage.

	- "variable" identifier có internal linkage. Module có quyền duy nhất sử dụng biến đó.


8.1.10.6
	A function declared as static

	- Nếu thuộc tính static mà precede khai báo của hàm, điều này có nghĩa là hàm có liên kết nội bộ với module cha.

	- Phạm vi của hàm chỉ giới hạn trong module mà khai báo của hàm diễn ra.

	- Chúng thường được sử dụng cho các hàm mà user không cần phải nhìn thấy của module.

	- Xem xét ví dụ sau – chương trình của chúng ta giờ đây bao gồm 3 module:

		/* module1.c */

		static void fun(void) {
			puts("#1");
		}


		/* module2.c */

		void fun(void) {
			puts("#2");
		}


		/* module3.c */

		void fun(void);
		int main(void) {
			fun();
			return 0;
		}

	- Câu hỏi là: hàm fun nào được gọi bởi hàm main?

	- Câu trả lời: fun là một hàm có liên kết nội bộ trong module đầu tiên, vì vậy nó không có sẵn ở bất kỳ nơi nào khác. Do đó, nó không thể được gọi từ một module khác. Hàm fun được khai báo trong module thứ hai không phải là hàm có liên kết nội bộ và được gọi thành công từ hàm main.

	- Hãy lưu ý rằng việc loại bỏ từ khóa static sẽ làm cho chương trình không còn đúng nữa. Bạn có thể giải thích vì sao không?


8.1.10.7
	A variable declared as a register

	- Một ví dụ về biến register được cho ở đây:

		register int time;

	- Như đã biết, cả program code và data của nó được lưu trữ trong bộ nhớ của máy tính. Bộ xử lý truy cập bộ nhớ mỗi khi nó cần lấy lệnh tiếp theo và khi cần đọc hoặc ghi bất kỳ giá trị dữ liệu nào. Tuy nhiên, mỗi bộ xử lý đều có bộ nhớ nhỏ riêng, độc lập. Nó được kết hợp với phần còn lại của CPU trong cùng một chip và cho phép dữ liệu được chuyển tiếp số lần nhanh hơn so với từ hay đến bộ nhớ thông thường. Các integrated memory areas (khu vực bộ nhớ tích hợp) này được chia thành các processor registers (thanh ghi bộ xử lý).

	- Số lượng registers rất hạn chế. Chúng được sử dụng để thực hiện các phép toán số học và logic, để lưu trữ tạm thời kết quả trung gian và để điều khiển các con trỏ. Thông thường, developer thậm chí không biết việc sử dụng các processor registers vì compiler quyết định một cách độc lập how to quản lý chúng.

	- Tuy nhiên, đôi khi, developer có thể muốn thông báo cho compiler biết rằng một số biến được sử dụng một cách intensively và do đó không nên được lưu trữ trong bộ nhớ thông thường, mà thay vào đó là trong các registers. Trong một số trường hợp, điều này có thể làm cho chương trình thực thi nhanh hơn.

	- Mặc dù có những ưu điểm, việc khai báo biến as 1 biến variable cũng có những hạn chế. Dưới đây là một số hạn chế:
		. một compiler cụ thể có thể từ chối xử lý một biến như một biến variable nếu kích thước của nó vượt quá một số bit cụ thể; lý do là, nếu bộ xử lý sử dụng registers 64 bit, không có khả năng nào về mặt vật lý để lưu trữ một mảng lớn trong đó;

		. một compiler có thể chỉ chấp nhận một vài lượng đầu tiên khai báo biến variable và có thể lặng lẽ bỏ qua tất cả các khai báo sau này; điều này là do số lượng registers bị hạn chế và không phải tất cả chúng có thể được sử dụng một cách tự do;
		
		. một biến được khai báo as a register không thể được sử dụng làm argument cho unary & operator (toán tử & đơn ngôi): điều này là một simple consequence của việc một biến như vậy không có địa chỉ.


8.1.10.8 Storage classes
	A variable declared as a register

	- Nhìn lại hàm strlen:

		int strlen2(char *str) {
		    int len = 0;
		    char *ptr = str;

		    while(*ptr++)
		        len++;
		    return len;
		}

	- Ta thấy biến len và ptr được dùng rất intensively. Ta có thể cải thiện hiệu suất của code bằng cách khai báo chúng as registers như sau:

		int strlen3(char *str) {
		    register int len = 0;
			register char *ptr = str;
			
			while(*ptr++)
			    len++;
			return len;
		}


8.1.11.1 Pointers to functions
	- Loại pointer như này xác định loại function mà địa chỉ của nó có thể giữ.

	- Xem khai báo sau:

		float (*ptr)(float);

	- Dù có ưu điểm nhưng khai báo biến as a register cũng có những hạn chế như sau:
		. Khai báo 1 biến tên ptr, trỏ đến các functions (không phải tất cả, mà chỉ những function có 1 tham số kiểu float) và return kết quả kiểu float

	- Sẽ giải thích syntax những khai báo này sau


8.1.11.2
	Pointers to functions: assigning a pointer

	- Giả sử viết 2 functions tương ứng với prototype trên như sau:

		float square(float x) {
			return x * x;
		}

		float cube(float x) {
			return x * x * x;
		}

	- 2 thằng đều có 1 tham số float và return float

	- Ta có thể thực hiện gán:

		ptr = square;

	Lúc này, ptr chỉ tới hàm square

		ptr = cube;

	Còn giờ ptr chỉ tới hàm cube

	- Note: tên của các functions này không cần parentheses. Bởi vì mục đích của ta không phải gọi hàm, mà là lấy địa chỉ của nó.
		Ta không dùng toán tử & cho mục đích này

	- The statement:

		ptr = square(2.0);

	sẽ là sai, vì hàm square cung cấp data kiểu float, điều này không phù hợp với kiểu của biến ptr.

8.1.11.3
	Pointers to functions: invoking a function

		. function được trỏ bởi biến ptr sẽ được gọi
		. Giá trị 2.0 sẽ được truyền như 1 tham số
		. Kết quả được cung cấp bởi hàm đã được gọi sẽ được gán cho biến f

	- Note: Chúng ta không thể dự đoán function nào sẽ được gọi. Nó dựa vào phép gán được thực hiện trước đó.

	- Vậy thứ này useful for gì? Useful để truyền 1 hàm như 1 tham số của hàm, ví dụ như sau.


8.1.11.4
	Pointers to functions: an example

	- Ta muốn viết 1 function in ra bảng giá trị cho bất kì hàm 1 đối số nào, và cho các giá trị của đối số lấy trong khoảng 0 đến 1, với bước nhảy 0.01

	- Function như sau:

		void printlookup(float (*fun)(float)) {
			float x, fx;

			for(x = 0.0; x <= 1.0; x += 0.01) {
				fx = fun(x);
				printf("%10.3f - %10.3f\n", x, fx);
			}
		}

	- Khi ta muốn in ra bảng giá trị cho hàm square, ta thực hiện invocation như sau:

		printlookup(square);

	- Đây là cách chúng ta chuẩn bị bảng giá trị cho hàm cube:

		printlookup(cube);


8.1.12.1 Complex declarations
	Declarations: analysis and synthesis

	- Syntax được áp dụng trong C language để encode những declaration statement (câu lệnh khai báo) rất ngắn gọn súc tích, những làm cho các khai báo trở nên vague và unclear. Xem xét 2 khía cạnh của sự phức tạp này:

		. Analytic, khi task của ta là giải mã 1 khai báo hoàn chỉnh như sau:

			int *(*tab[10])[10];

		. Synthetic, khi task của ta là code 1 khai báo được đưa dưới dạng mô tả bằng lời, như sau:

			Khai báo tab là một 10-element array of pointers trỏ đến 10-element array of pointers trỏ đến kiểu int.

	- Note: cả 2 forms đều mô tả chính xác cùng 1 khai báo.

	- Giới thiệu 1 khái niệm mới: a declarator là 1 text dùng để khai báo 1 identifier.

	- Trong ví dụ sau:

		int *p;

	*p là declarator dùng để khai báo identifier p:

	- Nói chung, 1 khai báo trong C language có form như sau:

		T D;

	trong đó:
		. T là type (built-in hoặc defined bởi programmer)
		. D là declarator.

	- Chúng tôi sẽ chỉ bạn các quy tắc viết và đọc C language declarations. Sau đó sẽ hướng dẫn cách sử dụng chúng để bạn có thể interpret hoặc viết bất kì declarator phức tạp nào.

	- Số lượng declarators khác nhau có thể được xây dựng trong C language gần như là vô hạn.


8.1.12.2
	- Declarations: rule #1
		Nếu declaration có dạng như sau:

			T D

		và D chỉ là identifier đơn giản, điều đó có nghĩa là D là 1 entity of type T.

	- Declarations: rule #2
		Nếu declaration có dạng sau:

			T D[n]

		điều đó có nghĩa là identifier chứa trong declarator D[n] là 1 array of size n và type T.

	- Declarations: rule #3
		Nếu declaration có dạng sau:

			T *D

		điều đó có nghĩa là identifier chứa trong declarator *D là 1 pointer to data of type T.

	- Declarations: rule #4
		Nếu declaration có dạng sau:

			T D()

		điều đó có nghĩa là identifier chứa trong declarator D() là 1 function mà return giá trị kiểu T.

	- Note: Những declarators khác có thể xuất hiện bên trong parentheses, chỉ định các loại tham số của hàm.

	- Khi 2 hoặc nhiều rules mâu thuẫn nhau, ta tuân theo rule dựa trên ưu tiên của các toán tử trong chúng.


8.1.12.3
	Declarations: an example

	- Ta luôn bắt đầu phân tích từ điểm mà identifier được located.

	- Example:

		int *(*(*p)[3])();

	- Ta thấy rằng identifier được đặt tên p. Giả sử substring *p là 1 declarator D tạm thời, và sử dụng rule số 3, ta thấy kết quả tạm thời của phân tích của chúng ta là "pointer".

	- Viết nó 1 cách semi-formally như sau:

		D <- *p 	pointer

	- Ta loại bỏ declarator sub-string đã identified bằng cách thay thế nó bằng D declarator tạm thời, nhận được statement như sau:

		int *(*(D)[3])();

	- Cặp parentheses bên trong không còn cần thiết và cũng có thể bỏ:

		int *(*D[3])();

	- Vì toán tử [] có mức độ ưu tiên cao hơn *, ta có thể nhận ra rằng phân tích tiếp theo dẫn đến sub-string sau:

		D[3]

	- Điều này có nghĩa là declarator D tạm thời là một 3-element array.

	- Ta có thể mô tả nó như sau:

		D <- D[3]	array[3]

	- Ta đơn giản hóa khai báo tiếp, nhận được:

		int *(*D)()

	- Ta thấy:

		D <- *D 	pointer

	- Khai báo được rút gọn như sau:

		int *D()

	- Toán tử () có độ ưu tiên cao hơn * nên:

		D <- D()	function

	- Bước tiếp theo như sau:

		int *D

		D <- *D 	pointer

	- Ta đạt được dạng đơn giản nhất của declarator bây giờ:

		int D 	int type

	- Tập hợp tất cả các kết quả trung gian lại với nhau:

		pointer, array [3], pointer, function, pointer, int

	- Ta có thể đọc chuỗi này một cách tổng quát hơn như sau:

		p is a pointer to a 3-element array of pointers to functions returning a pointer to int.


8.1.12.4
	- Thử phân tích declaration sau:

		char (*(*ptr)[3])[20];

	Step1:

		identifier	ptr
		temporary declarator	D ← *ptr
		conclusion	pointer
		simplified form	char (*D[3])[20];

	Step 2:

		temporary declarator	D ← D[3]
		conclusion	array[3]
		simplified form	char (*D)[20];

	Step 3:

		temporary declarator	D ← *D
		conclusion	pointer
		simplified form	char D[20];

	Step 4:

		temporary declarator	D ← D[20]
		conclusion	array[20]
		simplified form	char D;

	Step 5:

		conclusion	char type

	- Chuỗi kết luận:

		pointer, array [3], pointer, array [20], char

	- Ý nghĩa của khai báo:

		ptr is a pointer to an array [3] of pointers to an array [20] of char

8.1.12.5
	- Đây là declaration khác:

		float (*fun)(float);

	Step 1:

		identifier	fun
		temporary declarator	D ← *fun
		conclusion	pointer
		simplified form	float D(float);

	Step 2:

		temporary declarator	D ← D(float)
		conclusion	function (one parameter of type float)
		simplified form	float D; (*D)[20];

	Step 3:

		conclusion	float type
	
	- The chain of conclusions:
		pointer, function(float), float

	- The meaning of the declaration:
		ptr is a pointer to an array [3] of pointers to an array [20] of char


8.1.12.6
	Declarations: examples of synthesis

	- 3 ví dụ về declaration synthesis (tổng hợp khai báo)

	- Đây là ví dụ đầu tiên:

		arr is a 100-element array of pointers to 5-element array of pointers to float

	- Làm gọn thành như sau:

		array[100], pointer, array[5], pointer, float

	- Quay ngược lại quá trình, nhận được chuỗi các bước như sau:

		Step 1		array[100]		D[100]
		Step 2		pointer			*D[100]
		Step 3+		array[5]		(*D[100])[5]
		Step 4		pointer			*(*D[100])[5];
		Step 5		float			float *(*D[100])[5];
		Step 6		arr				float *(*arr[100])[5];

		+ Các dấu ngoặc đơn là bắt buộc phải có, tại sao?

	- Đây là khai báo hoàn chỉnh:

		float *(*arr[100])[5];"


8.1.12.7
	
	- Ví dụ tiếp theo là:

		ptr is a pointer to 5-element array of pointers to 10-element array of int


	- Làm gọn câu trên thành dạng như sau:

		pointer, array[5], pointer, array[10], int

	- The synthesis:

		Step 1		pointer			*D;	
		Step 2		array[5]		(*D)[5];				The parentheses are obligatory here – why?
		Step 3		array[5]		(*D[100])[5];
		Step 4		array[10]		(*(*D)[5])[10];			Ditto!
		Step 5		int				int (*(*D)[5])[10];	
		Step 6		ptr				int (*(*ptr)[5])[10];	

	- Khai báo hoàn thiện:

		int (*(*ptr)[5])[10];


8.1.12.8
	- Ví dụ cuối cùng:

		fun is a pointer to function with two parameters (char and int) returning a pointer to char

	- Làm gọn đoạn trên thành dạng như sau:

		pointer, function(char,int), pointer, char

	- The synthesis:

		Step 1		pointer						*D;
		Step 2		function(char,int)			(*D)(char,int);
		Step 3		pointer						*(*D)(char,int);
		Step 4		char						char *(*D)(char,int);
		Step 5		fun	char 					*(*fun)(char,int);
	
	- Khai báo hoàn thiện:

		char *(*fun)(char,int);

