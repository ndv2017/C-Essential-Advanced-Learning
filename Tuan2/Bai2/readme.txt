		C Essentials - Part 2 (Intermediate)


~ Module 6 ~

6.1.1.3
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


6.1.2.1
	- Structure's field có thể trùng với tag names:

		struct STRUCT
		{
    		int STRUCT;
		} Structure;

		Structure.STRUCT = 0; /* STRUCT is a field name here */


6.1.2.2
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


6.1.2.4
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


6.1.3.6
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

