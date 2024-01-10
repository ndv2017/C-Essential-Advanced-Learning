		C Essentials - Part 3 (Advanced)


~ Module 1 ~

	In this module, you will learn about:

	- milestones: ANSI C, C89, C95, C99, C11;
	- obsolete (but still valid) language elements;
	- how function declaration changed over time?;
	- trigraphs and digraphs;
	- new C11 keywords:
		. __Noreturn
		. _Alignof and _Alignas
		. _Bool
		. _Exit
		. _Complex
		. _Pragma, _ _func_ _
		. _Generic


1.1.1.2 -> 1.1.1.3 Evolution of the C programming language
	- Một vài khái niệm ngôn ngữ C ban đầu khá khó hiểu và gây bất tiện, ví dụ khai báo:

		int count = 1;

	thì ngày xưa khai báo như này:

		int count(1);

	=> Phải thay đổi vì quá reminiscent of function invocation

	- Một function kiểu như sau:

		int fnew (int n)
		{

		}

	thì ngày xưa nó như này:

		int fold (n)
			int n;
		{

		}

	nhưng tất cả đều được chấp nhận hết, code is valid.

	- Code như sau, và tất nhiên là valid:

		#include <stdio.h>

		int fnew (int n)
		{
			return n * n;
		}

		int fold (n)
		    int n;
		{
			return n * n;
		}

		int main (void)
		{
			printf ("%d %d\n", fnew (2), fold (2));
			return 0;
		}


1.1.1.4
	- Nếu sửa đổi một chút, ta sẽ phát hiện ra 2 forms trên nó hoạt động không giống nhau, không tương đương nhau:

		#include <stdio.h>

		int fnew (int n)
		{
			return n * n;
		}

		int fold (n)
		    int n;
		{
			return n * n;
		}

		int main (void)
		{
			printf ("%d %d\n", fnew (2, 0), fold (2, 0));
			return 0;
		}

	thêm 2 đối số vào chỗ gọi function, output sẽ ra lỗi ở fnew function.


1.1.1.5
	- Đối với fold trên, thì nếu ta gọi hàm mà:
		. Cung cấp quá ít đối số, random value sẽ được truyền vào (với mỗi lần gọi)
		. Cung cấp quá nhiều đối số, cái nào dư thì bị bỏ qua

			#include <stdio.h>

			int fold (n, m)
			    int n;
				int m;
			{
				printf ("%d %d\n", n, m);
			}

			int main (void)
			{
				fold(2);
				fold(2, 2);
				fold(2, 2, 2);
				return 0;
			}


1.1.1.6 -> 1.1.1.7 New keywords and capabilities
	- Snippet:

		#include <stdio.h>

		int f ()
		{
			printf ("Greetings from the past!");
		}

		int main (void)
		{
			f ();
			f (1);
			f (1, 2);
			return 0;
		}

	gọi function và thêm đối số vào cho nó, output ra là gì?

	- Có 2 kết luận:
		#1: Đây là form cũ, ngày nay nếu muốn khai báo 1 parameterless function thì viết như sau:

			int f(void)		{}

		#2: (hệ quả của cái đầu tiên) Cái header:

			int f()

		không có nghĩa là function không nhận đối số, mà function có thể nhận bao nhiêu đối số tùy mình muốn (kể cả 0 đối số).

	- Liệu có thể access được những đối số không được mentioned trong header hay không?
		Được, và sẽ bàn nó ở chapter sau.

	=> Có sự khác biệt rất lớn giữa 2 cách khai báo:

		int main()		{}

		int main(void)	{}

	nên phải khai báo đúng!


1.1.1.8 Evolution of the C programming language
	- Các khía cạnh cuối cùng được đề cập ở đầu vẫn còn chưa được giải thích:
		làm thế nào ngôn ngữ lập trình có thể áp dụng các kỹ thuật lập trình mới và các kỹ thuật này có thể ảnh hưởng đến sự phát triển của ngôn ngữ?

	- Vào thời điểm "C" được phát triển, một quá trình là phần nhỏ nhất và không thể chia nhỏ hơn của một đoạn mã đang chạy. Để chính xác: một quá trình là một đoạn mã đang chạy (được thực thi hiện tại). Chúng ta có thể nói rằng vào những ngày đó, một hệ điều hành là một công cụ để đồng bộ hóa, lập lịch và kiểm soát các quá trình đang chạy song song.

	- Tình trạng này vẫn tiếp tục cho đến khi một khái niệm mới xuất hiện - khái niệm về một đơn vị "nhẹ" hơn so với quá trình cổ điển; nhẹ hơn, do đó dễ dàng khởi động, kiểm soát, đồng bộ hóa và hủy bỏ. Thực thể mới này, phổ biến trong các hệ điều hành hiện đại, được gọi là một luồng (thread).

	- Tất nhiên, có thể làm việc với các luồng bằng cách sử dụng các ngôn ngữ lập trình tiêu chuẩn không nhận biết luồng. Trong thực tế, lập trình luồng đã có thể trong ngôn ngữ "C" từ đầu, nhờ vào các thư viện chuyên biệt chứa các bộ hàm tổ chức thực thi luồng. Một số thư viện này đã trở thành tiêu chuẩn được công nhận phổ biến, trong khi một số khác rất cụ thể và liên quan chặt chẽ đến các hệ điều hành hoặc nền tảng phần cứng cụ thể.

	- Do sự phổ biến ngày càng tăng của các luồng (thực tế là gần như tất cả phần mềm hiện đại không đơn giản đều sử dụng luồng), trở nên rõ ràng rằng ngôn ngữ "C" nên hỗ trợ kỹ thuật này ở mức ngôn ngữ. Điều này có thể đảm bảo rằng mã nguồn được viết rõ ràng, dễ viết và đọc hơn, và di động hơn. Các phiên bản ngôn ngữ "C" mới nhất đã làm điều này.

	- Chúng tôi sẽ cung cấp thông tin thêm về các quá trình và luồng sớm. Hãy tiếp tục theo dõi.


1.1.2.1 Trigraphs and digraphs
	- Mở lại link để xem các kí tự trong bảng
		https://edube.org/learn/c-advanced/trigraphs-and-digraphs-8


1.1.2.2
	- Đầu tiên, note rằng có tận 3 spaces khác nhau, ASCII chỉ dùng 1, coded as 32(0x20). Trong EBCDIC, cái thứ 2 là khoảng trắng non-breaking, còn cái thứ 3 là để tách digits in long number.

		Decimal		Hex			Sign

		64			40			Space
		65			41			Required Space
		225			E1			Numeric Space

	- Một vài sign của EBCDIC đến từ các ngôn ngữ lập trình khác, do IBM phát minh và quảng bá. Đây là một trong số đó - sign dùng trong PL/I như một toán tử logical negation (giống exclamation, tức ! ở trong ngôn ngữ C)

		Decimal		Hex			Sign
		
		95			5F			¬


1.1.2.3 -> 1.1.2.4
	- Trong ASCII, tất cả kí hiệu alphabet từ a đến z đều được set một cách coherent và có logic. Kiểu nếu lấy a - z + 1 hay kiểu như vậy thì vẫn hiểu được ra cái gì

	- Còn trong EBCDIC, thì có những cái khác như kiểu giữa I với J, hay giữa R với S có thêm kí tự gì đó, cụ thể xem link

		https://edube.org/learn/c-advanced/trigraphs-and-digraphs-10

	- Nhìn snippet sau:

		int
		main (int argc, char *argv[])
		{
		  return 1;
		}

	chtrinh này có thể viết và compiled trên những máy sử dụng EBCDIC version được hiển thị trước đấy không?

	- Đáp án là KHÔNG!

	- Bởi vì EBCDIC thiếu 2 characters quan trọng được dùng trong code trên: opening and closing square bracket []

	- Sửa code một chút là oki:

		int
		main (int argc, char **argv)
		{
		  return 1;
		}

	- Note: tất nhiên các phiên bản hiện đại của EBCDIC đã bổ sung 2 signs này và những signs cần thiết khác. Tuy vậy ta đang xét trên vị trí người sáng tạo.


1.1.2.5
	- Ta không thể viết lại hết tất cả chtrinh, trong khi dùng square bracket gần như là bắt buộc, ví dụ như khi khai báo array.

	- Cách để khắc phục: mở rộng language definition bởi 1 chuỗi kí tự được defined một cách đặt biệt. Và cái tên trigraph - 1 three-character-long sequence được chọn.

	- 9 trigraphs đã được định nghĩa và vẫn được sử dụng đến nay:

		trigraph		meaning

		??=				#
		??/				\
		??'				^
		??(				[
		??)				]
		??!				|
		??<				{
		??>				}
		??-				~


1.1.2.6
	- Một snippet sử dụng các trigraphs:

		??=include <stdio.h>

		int main(int argc, char *argv??(??)) ??<
			int i = 2 ??! 1;
			printf("i=%d??/n",i);
			return 0;
		??>

	- Làm sao để compile code with trigraphs?
		. Đối với gcc:

			gcc -trigraphs example.c

		. Đối với những cái khác thì tự tìm hiểu


1.1.2.7
	- Mặc dù vẫn legal và có thể viết chtrinh C với trigraphs, nhưng chúng đã được thay thế (hoặc đúng hơn là bổ sung) 1 concept đơn giản tên:

		digraph

	- Digraph chỉ chứa 2 kí tự.

	- Hiện nay có 5 digraphs được defined:

		digraph		meaning

		<:			[
		:>			]
		<%			{
		%>			}
		%:			#


1.1.2.8
	- Snippet dùng digraphs:

		%:include < stdio.h > 

		int
		main (int argc, char *argv <::>) < %
		puts ("Digraphs are here!");
		return 0;
		%>

	- Gcc compilers (và tương tự) có thể chạy bình thường.

	- Tổng kết:
		. Chuyển trigraphs thành kí tự tương ứng luôn luôn được thực hiện bởi preprocessor, trước khi quá trình compilation thực sự chạy

		. Chuyển trigraphs thành kí tự tương ứng được thực hiện bởi compiler

		. trigraphs cũng được nhận diện bên trong string literals

		. digraphs không được nhận diện bên trong strings

		. Nếu không muốn một chuỗi 3 kí tự bị nhận diện như là trigraph, có thể tách literal thành 2 phần hoặc dùng 1 escape sequence \?, được thiết kế đặc biệt cho những tình huống như này, 2 kĩ thuật trên được thể hiện qua snippet sau:

			#include <stdio.h>

			int
			main (int argc, char *argv[])
			{
			  puts ("??(??)");      /* outputs [] */
			  puts ("??" "(" "?" "?)"); /* outputs ??(??) */
			  puts ("\??(?\?)");        /* outputs [??) */
			  return 0;
			}


1.1.3.1 Standardization and standards
	- Tiêu chuẩn hóa mọi thứ sẽ giúp chúng ta làm việc, hoạt động tốt hơn, không bị nhầm lẫn.

	- Tất nhiên, ngôn ngữ lập trình cũng thế. Thực tế thì C language không phải real, nó chỉ là 1 abstract entity. Nó sẽ trở thành real khi được implemented thành công.
		Ta có thể nói có nhiều C languages, có nhiều compilers đang tồn tại, bao gồm cả những versions, subversions và ports của chúng

	- Có hàng tá các triển khai ngôn ngữ C hoàn toàn độc lập - hãy xem qua một vài cái thú vị nhất


1.1.3.2
	GCC
	- GCC là một cái gì đó còn hơn cả 1 compiler - gọi là toolchain và compiler collection.
		. Cái đầu tiên có nghĩa là GCC chứa 1 loạt các tools độc lập nhưng cooperating với nhau, cho phép programmers thực hiện tất cả jobs của họ với những phương tiện từ cùng 1 source, và dùng chúng một cách tương tự nhau.

		. Cái thứ hai có nghĩa là GCC không chỉ là 1 C language compiler, nhưng cũng là foundation mà có thể dùng để implement bất kì compiler hay bất kì ngôn ngữ nào cho bất kì nền tảng phần cứng nào và bất kì hệ điều hành nào. Trong những cái này, GCC còn có thể dùng để implement một cross compiler (biên dịch chéo) (compiler mà làm việc trên nền tảng X xây dựng code nhị phân cho nền tảng Y, trong đó X != Y).

		. Trong nhiều năm, GCC thống trị, nhưng gần đây có 1 đối thủ nặng kí nổi lên - Clang


1.1.3.3 -> 1.1.3.9
	- Clang
	- ICC
	- XL C/C++
	- Microsoft tools
	- Open Watcom C/C++

	- Và tất nhiên còn nhiều compilers khác, một số thì rất quan trọng, còn một số rất funny và frivolous (phù phiếm)

	- ANSI (American National Standards Institute) and ISO (International Organization for Standardization)
		Đây là 2 tổ chức chịu trách nhiệm tài liệu hóa và kiểm soát sự phát triển và suy yếu của C language.

	- K&R C
		Thời điểm ban đầu thì C không được tiêu chuẩn hóa. Thời đó vai trò tiêu chuẩn được đảm nhận bởi 1 cuốn sách của tác giả Brian W. Kernighan và Dennis Ritchie, tên là The C Programming Language, xuất bản lần đầu 1978.

	- Tài liệu đầu tiên được ANSI xuất bản vào năm 1989 as a standard và có tên chính thức là ANSI X3.159-1989 "C Programming Language" (do đó có tên được sử dụng rộng rãi là ANSI C). Nó cũng (không hoàn toàn chính xác) được gọi là C89 (tương tự như một tài liệu ISO sau này xác định tiêu chuẩn C90).
		. ANSI C là tổ tiên của tất cả các tiêu chuẩn và định nghĩa tiếp theo và chúng ta có thể nói rằng mỗi chương trình được viết bằng ANSI C có thể được biên dịch và chạy thành công trong bất kỳ môi trường nào sau này.

		. Note: có thể, chứ không phải là sẽ như thế. Why?

		. Nhiều lý do:
			> software - hệ điều hành khác nhau dùng phương thức access thiết bị, files và GUIs khác nhau.

			> hardware - nền tảng phần cứng khác nhau có thể dùng data sizes and ordering khác nhau


1.1.3.10
	- Có 2 loại computers trên thế giới, chúng khác nhau trong cách multibyte data được sắp xếp trong bộ nhớ. Giả sử rằng các giá trị nguyên kiểu short chiếm 2 byte (16 bit). Hai byte này của biến nằm ở địa chỉ x và x + 1. Giá trị 16 bit được chia thành 2 byte: byte thấp hơn (chứa các bit ít quan trọng hơn) và byte cao hơn (chứa các bit quan trọng hơn).

	- Nhưng: byte nào trong hai byte này nằm ở địa chỉ x (địa chỉ cao hơn hay thấp hơn?) và byte nào nằm ở địa chỉ x + 1 (địa chỉ thấp hơn hay cao hơn?)?
		. Các máy sử dụng endian nhỏ đặt byte thấp hơn ở địa chỉ nhỏ hơn.

		. Các máy sử dụng endian lớn đặt byte thấp hơn ở địa chỉ lớn hơn.

	- Xem đoạn code sau:

		#include <stdio.h>

		int main()
		{
		    short v = 0x0102;
		    char *p = (char *) &v;

		    printf("%d", *p);
		    return 0;
		}

	code này compiled và chạy trên phần cứng endian nhỏ sẽ output 2, nếu ngược lại thì output 1.

	- Analyze the code và giải thích tại sao?


1.1.4.1 New keywords and capabilities
	- Giờ chúng ta sẽ review nhanh về vài keywords và capabilities mới được giới thiệu cho C language bởi những tiêu chuẩn C95 và C11.
		. Làm quen với trends và hướng đi hiện nay của sự phát triển ngôn ngữ

		. Đánh giá how far C language đã đi được từ thời K&R đến hiện tại: từ quá khứ đến vĩnh hằng.

	- Note những bảng nhỏ ở cuối mỗi slide - thứ sẽ cho ta biết về compiler nào trong những compilers nổi tiếng sẽ chấp nhận những feature đang thảo luận.


1.1.4.2
	_Noreturn keyword

	- Thêm 1 keyword vào 1 chtrinh đã tồn tại khá nguy hiểm. Bởi có thể từ này đã được dùng trước đó, có thể gây compilation error.

	- Cách để giảm thiểu vấn đề này là thiết kế 1 keyword hợp lí, như _Noreturn không gợi đến bất kì keywords nào trước đó. Bắt đầu bằng underscore và chứa kí tự in hoa, cũng khó có programmers nào có ý tưởng để tên biến hoặc function như này.

	- _Noreturn là 1 function specifier, cung cấp thông tin rằng hàm sẽ không trả về người gọi nó. Compiler sẽ dùng thông tin để check liệu:
		. function tự nó hoạt động đúng như cách đã khai báo?

		. người gọi function đã chuẩn bị cho phản ứng của function.

	- Thắc mắc liệu có khả thi không khi function sẽ không return lại cho người gọi? Tất nhiên là có.
		e.g. Hàm exit() - dùng để kết thúc thực thi chtrinh - không return lại người gọi nếu nó được thực hiện.

	- _Noreturn có thể dùng như ví dụ snippet sau:

		#include <stdio.h>
		#include <stdlib.h>

		_Noreturn void
		byebye (char *msg, int ret)
		{
		    puts (msg);
		    exit (ret);
		}

		int
		main (void)
		{
		    puts ("Time is long but...");
		    byebye ("... life is short", 1);
		}


	gcc x.x			Clang y.y			CL 19.x

	+				+					-


1.1.4.3
	_Bool keyword

	- _Bool được thiết kế để giới thiệu một kiểu data mới.

	- Yêu cầu duy nhất của kiểu mới là có khả năng lưu trữ giá trị 0 và 1. Điều này có nghĩa là compiler có thể dùng 1 bit để triển khai các biến thuộc kiểu đó.

	- Note: không có thêm keywords nào để biểu thị bằng chữ các giá trị true hoặc false

	- Trong những expressions, những giá trị kiểu _Bool được treated như là 1 unsigned ints. Bất kì giá trị đơn, không bằng 0 nào được chuyển qua kiểu _Bool được treated as 1, ngược lại thì được treated as 0. 

	- Ví dụ snippet sau:

		#include <stdio.h>

		int main (void)
		{
		    _Bool yes = -1, no = 0;
		    yes = yes || no;
		    no = no && yes;
		    yes--;
		    ++no;
		    ++no;
		    printf ("%d %d\n", yes, no);
		    return 0;
		}

	Output là:	0 1

	gcc x.x			Clang y.y			CL 19.x

	+				+					+


1.1.4.4
	_Exit keyword

	- Hàm _Exit là một bản sao mạnh mẽ hơn của hàm exit(), và giống như các hàm cũ của nó, cần include header "stdlib.h" vào trước lần sử dụng đầu tiên, nhưng nếu cần bàn về nó, chúng ta nên nói vài lời về cơ chế được cung cấp bởi hàm atexit() (nó cũng từ stdlib.h).

	- Đôi lúc chtrinh muốn dọn dẹp một số thứ trước khi exit. Bước cleaning này có thể bao gồm xóa files hay directories tạm thời, hoàn thành các database transactions, output những thông báo chuẩn đoán, .... atexit() function có khả năng đăng kí 1 function sẽ được gọi trước khi trả lại quyền điều khiển cho hệ điều hành. Ngoài ra nó còn có thể đki nhiều functions như vậy.

	- Prototype của atexit() như sau:

		int atexit(void (*function)(void));

	- Function này return lại một giá trị khác 0 nếu thành công, hoặc không thành công thì = 0.

	- Các functions được đki sẽ được gọi theo thứ tự như đã đki, và việc gọi sẽ thực hiện ngay trước khi chtrinh end, bất kể việc chấm dứt chtrinh có chạy bình thường hay bất bình thường.

	- Hàm _Exit() kết thúc chtrinh một cách forcibly, bỏ qua tất cả các functions đã đki bởi atexit()

	- Nhìn snippet sau:

		#include <stdio.h>
		#include <stdlib.h>

		void washer (void)
		{
		    printf ("3\n");
		}

		void sweeper (void)
		{
		    printf ("2\n");
		}

		int main (void)
		{
		    int val;
		    printf ("Enter an int value:");
		    scanf ("%d", &val);
		    printf ("1\n");

		    atexit (sweeper);
		    atexit (washer);

		    if (val)
		        exit (1);
		    else
		        _Exit (1);
		}

	nếu nhập 1 giá trị khác 0 thì Output là:
		1
		2
		3

	còn nếu nhập 0 thì là:
		1

	gcc x.x			Clang y.y			CL 19.x
	+				+					+


1.1.4.5
	_Generic keyword

	- _Generic keyword là 1 thành phần của syntax/mệnh đề mới được thêm vào C11 và được đặt tên là generic selection (lựa chọn chung), dùng để chỉ cho compiler nên chọn thực thể nào tùy thuộc vào loại expression.

	- Form chung của clause này như sau:

		_Generic(selector, type1: item1, type2: item2, ... , default: item)

	- Compiler sẽ tìm type của selector và tìm nó trong những type1, type2,... Khi type tương ứng được tìm thấy, item liên quan đến nó sẽ được lấy làm giá trị cuối cùng của clause. Nếu không tìm thấy type phù hợp, clause này biểu thị giá trị liên kết với default. The default branch thì tùy chọn.

	- Nó là họ hàng xa của câu lệnh switch.

	- Ví dụ sử dụng _Generic: Giả sử ta muốn có 1 function tên snap(), có thể output 1 giá trị của biến kiểu int, char and float. Không có cách đơn giản nào để làm được với chỉ 1 function vì ta phải tách ra 3 functions riêng cho từng kiểu. Nhờ generic selection, ta có thể chỉ cần gọi 1 function, vì compiler sẽ có thể chọn function phù hợp.

	- Xem snippet sau:

		#include <stdio.h>

		void
		snapi (int i)
		{
		  printf ("%d\n", i);
		}

		void
		snapc (char c)
		{
		  printf ("%c\n", c);
		}

		void
		snapf (float f)
		{
		  printf ("%f\n", f);
		}

		#define snap(x) _Generic((x), char: snapc, int: snapi,
		default:
		snapf) (x) int main (void)
		{
		  char c = 'y';
		    snap ('x');
		    snap ((char) 'x');
		    snap (c);
		    snap (3.1415);
		    snap (13);
		    return 0;
		}

	- Note: Chỉ thị #define định nghĩa một universal macro và phân tích cẩn thận cách sử dụng _Generic để chọn hàm thích hợp.

	- Output của code trên là:
		120
		x
		y
		3.141500
		13

	- Chú ý là chữ char (x) có kiểu int. Bạn phải dùng kiểu chữ để compiler hiểu rằng bạn muốn nó được trình bày dưới dạng char.

	gcc x.x		Clang y.y		CL 19.x
	+			+				-


1.1.4.6
	__func__ symbol

	- __func__ là 1 preprocessor symbol. Bộ tiền xử lý của C language định nghĩa 2 symbols, thứ có thể dùng để xác định vị trí chúng xuất hiện. Những symbols đó là:

		__FILE__

		__LINE__

	C11 thêm 1 symbol thứ ba nữa là:

		__func__

	- Nếu sử dụng, nó luôn biểu thị 1 string chứa tên của hàm kèm theo. Dùng nó bên ngoài bất kì function nào sẽ gây ra compilation error.

	- Xem đoạn code sau:

		#include <stdio.h>
		#include <string.h>

		char s[100];

		char *
		f (void)
		{
		  strcpy (s, __func__);
		  return s;
		}

		void
		g (void)
		{
		  puts (__func__);
		}

		int
		main (void)
		{
		  puts (f ());
		  g ();
		  return 0;
		}

	Output của nó như sau:
		f
		g

	gcc x.x		Clang y.y		CL 19.x

	+			+				+


1.1.4.7
	_Complex keyword

	- _Complex đề cập đến khái niệm toán học của cái gọi là số phức.

	- Vì cả 2 phần số phức đều là float, nên _Complex thường được dùng cùng với bất kì bộ khai báo nào của float, tức là:

		float _Complex a;
		double _Complex b;
		long double _Complex c;

	- Trong C11, tất cả các phép toán số học được redefined lại để tuân thủ với số phức, do đó ta có thể thoải mái dùng các toán tử +, -, *, /. Thêm nữa, có những phiên bản hàm phức tạp cũng được thêm vào và các biến thể phức tạp của chúng được đặt tên bằng cách thêm prefix c (là complex):

		abs() → cabs(), exp() → cexp(), sqrt() → csqrt() and so on...

	- Include tệp header "complex.h", nó chứa:
		. Một kí hiệu complex (thực ra là macro không tham số) thay thế tên loại _Complex được built-in.

		. Kí tự I cũng được dùng thay thế cho i được built-in.

		. các hàm creal(), crealf() và creall() (tương ứng với các đối số phức tạp double, float và long double) trả về phần thực của đối số;

		. Các hàm cimag(), cimagf() và cimagl() trả về phần ảo của đối số.

	- Note: Cả scanf() và printf() đều không hỗ trợ cụ thể cho việc input/output số phức.

	- Example về sử dụng số phức:

		#include <stdio.h>
		#include <complex.h>

		int
		main (void)
		{
		  float _Complex cplx1, cplx2, cplx;

		  cplx1 = 1.0 + 2.0 i;
		  cplx2 = 2.0 - 1.0 I;
		  cplx = cplx1 * cplx2;
		  printf ("(%f+%fi)\n", creal (cplx), cimag (cplx));
		  return 0;
		}

	- Output của code trên:

		(4.000000+3.000000i)

	gcc x.x		Clang y.y		CL 19.x
	+			+				-


1.1.4.8
	_Alignof and _Alignas keywords

	- Trước khi giải thích mục đích của những keyword này thì phải giải thích trước về term alignment (hay đúng hơn là data alignment).

	- Có thể một mẫu bộ vi xử lý nhất định sẽ đọc/ghi multibyte data nhanh hơn khi nó được đặt tại một địa chỉ cụ thể. Ví dụ. một thực thể int dài 4 byte có thể được xử lý hiệu quả hơn khi nó nằm ở địa chỉ chia hết cho 4. Điều này có nghĩa là compiler có thể tạo ra code thực thi nhanh hơn nếu nó triển khai các thực thể, không phải theo kiểu tuyến tính (giá trị nối tiếp giá trị), mà bằng cách xem xét các vị trí thuận lợi nhất. Điều này có thể được thực hiện bằng cách sử dụng padding (phần đệm) - chèn các byte giả, không được sử dụng giữa các thực thể khác nhau, ví dụ: field biến hoặc field cấu trúc.

	- Xem xét example sau:

		#include <stdio.h>

		struct s
		{
		  char c;
		  double d;
		};
		int
		main (void)
		{
		  printf ("%ldn", sizeof (struct s));
		  printf ("%ldn", sizeof (char) + sizeof (double));
		  return 0;
		}

	- Output của code trên:

		16
		9

	- Điều này có nghĩa là field thứ 2 đã được aligned (căn chỉnh) theo địa chỉ chia hết cho 8, và do đó 7 padding bytes (byte đệm) đã được inserted vào.

	- Giờ có 2 keywords mới:
		. _Alignof( type ) là toán tử trả về yêu cầu căn chỉnh được hiển thị theo type; nếu type đại diện cho một mảng, phần tử của mảng _Alignof sẽ được trả về; lưu ý: nếu _Alignof(x) > _Align(y) thì chúng ta nói rằng việc căn chỉnh của x chặt chẽ hơn việc căn chỉnh của y;

		. _Alignas ( type | expression | pack ) là một công cụ xác định, thông báo yêu cầu căn chỉnh của một loại hoặc một biến; các biến thể có thể là:
			> _Alignas ( type ) – triển khai thực thể có cùng căn chỉnh như được sử dụng thường xuyên cho loại có tên type

			> _Alignas ( biểu thức ) trong đó biểu thức ước tính thành một số nguyên, giá trị không âm – triển khai thực thể ở ranh giới giá trị của biểu thức; lưu ý: _Alignas(0) không có hiệu lực; lưu ý một lần nữa: không phải tất cả các giá trị của biểu thức đều có thể được chấp nhận - bạn có thể cho rằng chỉ có lũy thừa của hai là an toàn.

	- Note: _Alignas(type) tương đương với Alignas(_Alignof(type)).

	- Một điều kiện quan trọng phải được đáp ứng: _Alignas không được giảm sự liên kết của bất kỳ thực thể nào, tức là nó không thể làm cho nó ít nghiêm ngặt hơn mặc định.

	- Do đó, cái này thì được:

		struct s { float x; float _Alignas(double) y; };

	còn cái này thì không:

		struct s { double x; double _Alignas(float) y; };

	- Example dùng các thứ trên:

		#include <stdio.h>

		#
		define ptrdiff (a, b) (int) ((char *) &(b) - (char *) &(a))
		     typedef struct
		     {
		       float
			 x;
		       float
			 y;
		     }
		s1;
		     typedef struct
		     {
		       float
			 x;
		       float
		       _Alignas (double)
			 y;
		     }
		s2;
		     typedef struct
		     {
		       char
			 a;
		       char
			 b;
		       char
			 c;
		     }
		t1;
		     typedef struct
		     {
		       char
			 a;
		       char
		       _Alignas (short)
			 b;
		       char
		       _Alignas (int)
			 c;
		     }
		t2;

		     int
		     main (void)
		{
		  s1 a;
		  printf ("%ld %d %d\n", sizeof (s1), ptrdiff (a, a.x), ptrdiff (a, a.y));
		  s2 b;
		  printf ("%ld %d %d\n", sizeof (s2), ptrdiff (b, b.x), ptrdiff (b, b.y));
		  t1 c;
		  printf ("%ld %d %d %d\n", sizeof (t1), ptrdiff (c, c.a), ptrdiff (c, c.b),
			  ptrdiff (c, c.c));
		  t2 d;
		  printf ("%ld %d %d %d\n", sizeof (t2), ptrdiff (d, d.a), ptrdiff (d, d.b),
			  ptrdiff (d, d.c));
		  return 0;
		}

	- Macro có tên ptrdiff được thiết kế để tìm sự khác biệt giữa các con trỏ (được đo bằng đơn vị sizeof(char), tức là byte). Chúng tôi sử dụng nó để tiết lộ cách các trường được triển khai bên trong các loại cấu trúc khác nhau.

	- Output của code trên là:

		8 0 4
		16 0 8
		3 0 1 2
		8 0 2 4

	- Tệp tiêu đề có tên stdalign.h xác định hai macro thuận tiện căn chỉnh và căn chỉnh có thể làm cho mã của bạn đẹp hơn, đặc biệt là khi bạn không bị mê hoặc bởi dấu gạch dưới.

	gcc x.x		Clang y.y		CL 19.x

	+			+				-


1.1.4.9
	_Pragma preprocessor operator

	- Để biết về _Pragma, trước tiên cần biết về #pragma. #pragma là một preprocessor directive (lệnh tiền xử lý) được sử dụng để giao tiếp với compiler và được thiết kế để sửa đổi hành vi của compiler; do đó; nó phụ thuộc rất nhiều vào việc triển khai và nền tảng mục tiêu. Tập hợp các pragma có thể và có thể sử dụng được không phải là một phần của tiêu chuẩn ngôn ngữ và có thể được tìm thấy trong tài liệu về compiler và môi trường.

	- Ví dụ: gcc compiler định nghĩa một pragma thú vị có tên là GCC poison.

	- Pragma buộc compiler phải tìm kiếm tất cả các identifiers đã đăng ký và coi chúng là bị poisoned (có nghĩa là chúng không được chào đón đối với bạn và bạn muốn được thông báo cách thức và nơi các identifiers này đã được sử dụng - đó là một công cụ rất tốt để kiểm tra code của bạn sau khi loại bỏ một số khai báo không cần thiết).

	- Example code sau:

		#pragma GCC poison a b
		int
		main (void)
		{
		  int a;
		  int b;
		  int c;
		  int d;
		  d = 1;
		  c = 2;
		  a = d + c;
		  b = c - d;
		  return 0;
		}

	làm cho gcc compiler phát ra các thông báo như sau:

		prag.c: In function ‘main’:
		prag.c:4:6: error: attempt to use poisoned "a"
		  int a; int b; int c; int d;
		      ^
		prag.c:4:13: error: attempt to use poisoned "b"
		  int a; int b; int c; int d;
		             ^
		prag.c:8:2: error: attempt to use poisoned "a"
		  a = d + c;
		  ^
		prag.c:9:2: error: attempt to use poisoned "b"
		  b = c - d;
		  ^

	- Quay lại chủ đề chính. Toán tử _Pragma cho phép programmer sử dụng pragma bên trong macro, điều này là không thể nếu không có nó.

	- Toán tử này yêu cầu cú pháp sau:

		_Pragma( string_literal )

	và thực hiện (trong giai đoạn tiền xử lý) theo cách sau:
		. string_literal được destringized bằng cách thay thế tất cả \\ bằng một \ và tất cả \" bằng một ";

		. string đã destringized được coi như thể nó xuất hiện dưới dạng đối số của lệnh #pragma thông thường.

	- Example code:

		#define var(v)	int v; \
		_Pragma("GCC poison a")

		int
		main (void)
		{
		  int a;
		  int y;
		  a = 1;
		  var (x) a = 2;
		  x = 3;
		  y = 4;
		  return 0;
		}

	- Code gây ra output chẩn đoán của compiler sau:

		01.04._Pragma.c: In function 'main':
		01.04._Pragma.c:8:2: error: attempt to use poisoned "a"
		  a = 2;
		  ^

	- Note: Thay thế _Pragma bằng #pragma sẽ tạo ra output sau:

		01.04._Pragma.c:1:14: error: '#' is not followed by a macro parameter
		 #define var(v) int v;\
		              ^
		01.04._Pragma.c: In function 'main':
		01.04._Pragma.c:7:6: error: 'x' undeclared (first use in this function)
		  var(x)
		      ^
		01.04._Pragma.c:7:6: note: each undeclared identifier is reported only once for each function it appears in
		01.04._Pragma.c:8:2: error: expected ';' before 'a'
		  a = 2;
		  ^

	vì #pragma sẽ không được công nhận là một phần của macro hiện đang được defined.