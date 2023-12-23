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

	- Đây gọi là RECURSIVE DECLARATION (KHAI BÁO ĐỆ QUY), vì thực thể được khai báo sẽ tham chiếu chính nó trước khi khai báo hoàn tất.


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
	- Bất kỳ chương trình nào được viết bằng ngôn ngữ "C" (quy ước này áp dụng cho gần như tất cả các ngôn ngữ lập trình) không trực tiếp giao tiếp với các tập tin, mà thông qua một thực thể trừu tượng được gọi là stream (luồng).

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

		. Tiêu chuẩn ngôn ngữ "C" giả định rằng môi trường lập trình (bao gồm trình biên dịch, các tệp đầu vào và thư viện liên quan, cũng như một số công cụ bổ sung) nên đảm bảo sự tồn tại của một kiểu có tên là FILE, được sử dụng để biểu diễn các luồng trong chương trình.

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


