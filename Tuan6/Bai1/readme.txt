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

	- Vào thời điểm "C" được phát triển, một quá trình là phần nhỏ nhất và không thể chia nhỏ hơn của một đoạn code đang chạy. Để chính xác: một quá trình là một đoạn code đang chạy (được thực thi hiện tại). Chúng ta có thể nói rằng vào những ngày đó, một hệ điều hành là một công cụ để đồng bộ hóa, lập lịch và kiểm soát các quá trình đang chạy song song.

	- Tình trạng này vẫn tiếp tục cho đến khi một khái niệm mới xuất hiện - khái niệm về một đơn vị "nhẹ" hơn so với quá trình cổ điển; nhẹ hơn, do đó dễ dàng khởi động, kiểm soát, đồng bộ hóa và hủy bỏ. Thực thể mới này, phổ biến trong các hệ điều hành hiện đại, được gọi là một luồng (thread).

	- Tất nhiên, có thể làm việc với các luồng bằng cách sử dụng các ngôn ngữ lập trình tiêu chuẩn không nhận biết luồng. Trong thực tế, lập trình luồng đã có thể trong C language từ đầu, nhờ vào các thư viện chuyên biệt chứa các bộ hàm tổ chức thực thi luồng. Một số thư viện này đã trở thành tiêu chuẩn được công nhận phổ biến, trong khi một số khác rất cụ thể và liên quan chặt chẽ đến các hệ điều hành hoặc nền tảng phần cứng cụ thể.

	- Do sự phổ biến ngày càng tăng của các luồng (thực tế là gần như tất cả phần mềm hiện đại không đơn giản đều sử dụng luồng), trở nên rõ ràng rằng C language nên hỗ trợ kỹ thuật này ở mức ngôn ngữ. Điều này có thể đảm bảo rằng code nguồn được viết rõ ràng, dễ viết và đọc hơn, và di động hơn. Các phiên bản C language mới nhất đã làm điều này.

	- Chúng tôi sẽ cung cấp thông tin thêm về các quá trình và luồng sớm. Hãy tiếp tục theo dõi.


1.2.1.1 Trigraphs and digraphs
	- Mở lại link để xem các kí tự trong bảng
		https://edube.org/learn/c-advanced/trigraphs-and-digraphs-8


1.2.1.2
	- Đầu tiên, note rằng có tận 3 spaces khác nhau, ASCII chỉ dùng 1, coded as 32(0x20). Trong EBCDIC, cái thứ 2 là khoảng trắng non-breaking, còn cái thứ 3 là để tách digits in long number.

		Decimal		Hex			Sign

		64			40			Space
		65			41			Required Space
		225			E1			Numeric Space

	- Một vài sign của EBCDIC đến từ các ngôn ngữ lập trình khác, do IBM phát minh và quảng bá. Đây là một trong số đó - sign dùng trong PL/I như một toán tử logical negation (giống exclamation, tức ! ở trong ngôn ngữ C)

		Decimal		Hex			Sign
		
		95			5F			¬


1.2.1.3 -> 1.2.1.4
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


1.2.1.5
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


1.2.1.6
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


1.2.1.7
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


1.2.1.8
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


1.3.1.1 Standardization and standards
	- Tiêu chuẩn hóa mọi thứ sẽ giúp chúng ta làm việc, hoạt động tốt hơn, không bị nhầm lẫn.

	- Tất nhiên, ngôn ngữ lập trình cũng thế. Thực tế thì C language không phải real, nó chỉ là 1 abstract entity. Nó sẽ trở thành real khi được implemented thành công.
		Ta có thể nói có nhiều C languages, có nhiều compilers đang tồn tại, bao gồm cả những versions, subversions và ports của chúng

	- Có hàng tá các triển khai ngôn ngữ C hoàn toàn độc lập - hãy xem qua một vài cái thú vị nhất


1.3.1.2
	GCC
	- GCC là một cái gì đó còn hơn cả 1 compiler - gọi là toolchain và compiler collection.
		. Cái đầu tiên có nghĩa là GCC chứa 1 loạt các tools độc lập nhưng cooperating với nhau, cho phép programmers thực hiện tất cả jobs của họ với những phương tiện từ cùng 1 source, và dùng chúng một cách tương tự nhau.

		. Cái thứ hai có nghĩa là GCC không chỉ là 1 C language compiler, nhưng cũng là foundation mà có thể dùng để implement bất kì compiler hay bất kì ngôn ngữ nào cho bất kì nền tảng phần cứng nào và bất kì hệ điều hành nào. Trong những cái này, GCC còn có thể dùng để implement một cross compiler (biên dịch chéo) (compiler mà làm việc trên nền tảng X xây dựng code nhị phân cho nền tảng Y, trong đó X != Y).

		. Trong nhiều năm, GCC thống trị, nhưng gần đây có 1 đối thủ nặng kí nổi lên - Clang


1.3.1.3 -> 1.3.1.9
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


1.3.1.10
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


1.4.1.1 New keywords and capabilities
	- Giờ chúng ta sẽ review nhanh về vài keywords và capabilities mới được giới thiệu cho C language bởi những tiêu chuẩn C95 và C11.
		. Làm quen với trends và hướng đi hiện nay của sự phát triển ngôn ngữ

		. Đánh giá how far C language đã đi được từ thời K&R đến hiện tại: từ quá khứ đến vĩnh hằng.

	- Note những bảng nhỏ ở cuối mỗi slide - thứ sẽ cho ta biết về compiler nào trong những compilers nổi tiếng sẽ chấp nhận những feature đang thảo luận.


1.4.1.2
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


1.4.1.3
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


1.4.1.4
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


1.4.1.5
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


1.4.1.6
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


1.4.1.7
	_Complex keyword

	- _Complex đề cập đến khái niệm toán học của cái gọi là số phức.

	- Vì cả 2 phần số phức đều là float, nên _Complex thường được dùng cùng với bất kì bộ khai báo nào của float, tức là:

		float _Complex a;
		double _Complex b;
		long double _Complex c;

	- Trong C11, tất cả các phép toán số học được redefined lại để tuân thủ với số phức, do đó ta có thể thoải mái dùng các toán tử +, -, *, /. Thêm nữa, có những phiên bản hàm phức tạp cũng được thêm vào và các biến thể phức tạp của chúng được đặt tên bằng cách thêm prefix c (là complex):

		abs() → cabs(), exp() → cexp(), sqrt() → csqrt() and so on...

	- Include file header "complex.h", nó chứa:
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


1.4.1.8
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
		. _Alignof( type ) là toán tử trả về yêu cầu căn chỉnh được hiển thị theo type; nếu type đại diện cho một mảng, phần tử của mảng _Alignof sẽ được trả về; Note: nếu _Alignof(x) > _Align(y) thì chúng ta nói rằng việc căn chỉnh của x chặt chẽ hơn việc căn chỉnh của y;

		. _Alignas ( type | expression | pack ) là một công cụ xác định, thông báo yêu cầu căn chỉnh của một loại hoặc một biến; các biến thể có thể là:
			> _Alignas ( type ) – triển khai thực thể có cùng căn chỉnh như được sử dụng thường xuyên cho loại có tên type

			> _Alignas ( biểu thức ) trong đó biểu thức ước tính thành một số nguyên, giá trị không âm – triển khai thực thể ở ranh giới giá trị của biểu thức; Note: _Alignas(0) không có hiệu lực; lưu ý một lần nữa: không phải tất cả các giá trị của biểu thức đều có thể được chấp nhận - bạn có thể cho rằng chỉ có lũy thừa của hai là an toàn.

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

	- file tiêu đề có tên stdalign.h xác định hai macro thuận tiện căn chỉnh và căn chỉnh có thể làm cho code của bạn đẹp hơn, đặc biệt là khi bạn không bị mê hoặc bởi dấu gạch dưới.

	gcc x.x		Clang y.y		CL 19.x

	+			+				-


1.4.1.9
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



~ Module 2 ~

	In this module, you will learn about:

		. calling conventions, parameters passing, stack usage, stack frame, . returning a value, recursion;
		. va_start();
		. va_arg();
		. va_end();
		. va_copy();
		. vsprintf(), vprintf(), vfprintf();
		. vscanf(), vsscanf(), vfscanf().


2.1.1.2 Handling a variable number of parameters – calling conventions
	- Question: Làm sao để các functions như printf() và scanf() có khả năng xử lý số lượng đối số khác nhau. Ta dùng những hàm này nhiều lần mà bỏ qua cơ chế chúng sử dụng và không nói gì về cách viết những hàm đó.

	- Trước khi vén màn bí mật, ta cần biết cách những hàm giao tiếp với nhau như thế nào.

	- Trước tiên ta cần xác định 2 thuật ngữ:
		. caller (hoặc invoker) - 1 hàm mà gọi 1 hàm khác. caller chịu trách nhiệm chuẩn bị đối số và nhận kết quả

		. callee (hoặc invokee) - 1 hàm được gọi có trách nhiệm ngăn chặn các đối số, liên kết tụi nó với các tham số, và cuối cùng chuẩn bị và trả về kết quả.

	- The way mà caller và callee giao tiếp với nhau gọi là calling convention.
		Hãy cùng nhau nói về nó một chút.

		printf ("Hello Mary!");
		printf ("Mary had a little %s", "lamb");
		printf ("Mary had %d little %s", 2, "lambs");
		printf ("%f + %f = %f", 2, 3, 2 + 3);
		printf ("%d", printf ("%c%c%c", 'x', 'y', 'z'));


2.1.1.3
	- Thông thường (hầu hết C language implementations dùng phương pháp này) một cấu trúc dữ liệu gọi là Stack (ngăn xếp) được dùng để truyền giá trị đối số từ caller sang callee.

	- Stack là một phần riêng biệt của bộ nhớ, hoạt động theo 1 cách đặc biệt ở binary code level. Thường thì processor của máy tính cung cấp ít nhất 2 lệnh chuyên biệt tên là push và pop, dùng để put giá trị vào stack và get giá trị từ stack.

	- Hình ảnh cho thấy cách hoạt động (xem qua link):

		https://edube.org/learn/clp-c-programming-language-certified-professional/handling-a-variable-number-of-parameters-calling-conventions-1

	- Dựa theo hình có thể thấy, push làm cho stack grow và đưa các giá trị mới lên trên cùng. Tương tự, pop làm stack shrink (co lại) và lấy giá trị mới từ trên cùng. Ngoài ra, các giá trị trong stack có thể được truy cập theo cách truyền thống như những items trong 1 array, vì có 1 thanh ghi bộ xử lý chuyên dụng lưu trữ địa chỉ của phần tử trên cùng. Nếu biết được địa chỉ của top of the stack, ta có thể truy cập vào tất cả giá trị nằm dưới nó.

	- Note: stack đôi khi được gọi là LIFO, tức Last In First Out.
		Giá trị được đưa vào stack cuối cùng là giá trị đầu tiên được lấy ra.

	- Giờ tưởng tượng cách stack có thể dùng để truyền đối số của hàm - caller sẽ đưa những đối số vào stack, callee sử dụng chúng, và cuối cùng ai đó xóa chúng khỏi stack khi hàm returns to the caller.
		Note: Việc khôi phục trạng thái ban đầu của stack có thể được thực hiện ở 2 nơi - trong callee hoặc trong caller.

	- Việc cleaning the stack, được thực hiện bởi invokee, có thể làm cho toàn bộ code nhỏ hơn 1 chút - cleaning code chỉ được đưa vào dạng nhị phân 1 lần mỗi hàm. Đặt code bên trong invoker yêu cầu code phải tồn tại trong mọi nơi mà callee được gọi. May mắn là các microprocessors có thể thực hiện the cleaning bằng 1 lệnh của máy, vừa đơn giản vừa nhanh.

	- Có lựa chọn khác: Đối số nên được đặt theo thứ tự như nào trong stack? Có ít nhất 2 khả năng hợp lý.

	- Ý tưởng đầu tiên là push chúng vào stack theo đúng thứ tự mà nó được listed trong function header.

		f (a, b, c);
		push a;
		push b;
		push c;
		push c;
		push b;
		push a;


2.1.1.4
	- Ảnh:
		https://edube.org/learn/clp-c-programming-language-certified-professional/handling-a-variable-number-of-parameters-calling-conventions-2

	- Ảnh minh họa cách gọi 1 hàm đơn giản và các sử dụng stack để làm trung gian cho việc trao đổi đối số/tham số.

	- Giả sử hàm được khai báo như sau:

		void
		fun (int a, int b, int c)
		{
		...}

	và nó được gọi như sau:

		fun (1, 2, 3);

	- Callee chịu trách nhiệm khôi phục stack. Nó có thể làm điều này, bởi vì nó biết có bao nhiêu tham số cần phải loại bỏ.

	- Callee biết nó nhận chính xác bao nhiêu đối số bởi vì nó biết một cách trực tiếp từ khai báo của nó. Thêm nữa, nó cần phải biết thì mới hoạt động đúng được. Và điều đó cũng có nghĩa là kiểu vận hành với stack có thể không phù hợp để sử dụng với số lượng đối số khác nhau. Trong TH này, chỉ có invoker mới biết có bao nhiêu đối số nó đã push vào stack.

	- Chúng tôi sẽ nghĩ về nó sớm, nhưng bây giờ chúng tôi có thể thông báo rằng bạn đã làm quen với quy ước gọi đầu tiên, có tên là Pascal, do thực tế đó là hành vi mặc định của compiler ngôn ngữ Pascal. Điều thú vị là nó cũng sử dụng một số dịch vụ MS Windows.

	- C language compilers hiện đại tránh điều này

	- Giờ thử sửa đổi sơ đồ chúng ta một chúng


2.1.1.5
	- Hình ảnh:
		https://edube.org/learn/clp-c-programming-language-certified-professional/handling-a-variable-number-of-parameters-calling-conventions-3

	- Giờ invokee được giảm bớt áp lực vì giờ nó không bắt buộc phải clean the stack nữa. Điều này liệu có nghĩa là hàm đã được chuẩn bị đầy đủ để phục vụ các lệnh gọi với số lượng đối số khác nhau?
		Không hẳn

	- Đặt bản thân và hàm và hỏi: Đối số nào hàm muốn truy cập vào lúc ban đầu: cái đầu tiên hay cái cuối cùng, nói cách khác, hàm muốn thấy gì ở đầu stack?

	- Truy cập đối số đầu tiên là hợp lý, vì nếu biết đối số đầu, nó có thể nói cho bạn biết có bao nhiêu đối số tổng cộng. Đối số cuối cùng sẽ không nói điều đó.

	- Note: Đối số đầu tiên của hàm printf() là 1 thông báo mang đến cho chúng ta kiến thức này. Invokee chỉ cần đếm dấu % trong string và sẽ biết chính xác có bao nhiêu đối số.

	- Một calling convention khác - tên là stdcall.
		Một số C language compilers có thể dùng nó nếu được yêu cầu.


2.1.1.6
	- Ảnh:
		https://edube.org/learn/clp-c-programming-language-certified-professional/handling-a-variable-number-of-parameters-calling-conventions-4

	- Chúng tôi đã đảo ngược các thứ tự các đối số được push vào stack. Giờ đối số đầu tiên nằm đầu stack. Callee có thể phân tích nó và learn everything about tất cả đối số còn lại.

	- Và đây là phương pháp tiêu chuẩn dùng bởi C language compilers để thiết lập interface giữa callers và callees. Do đó nó tên cdecl (C - declared)

	- Có nhiều calling conventions có thể được dùng thay thế. Ví dụ một số thanh ghi bộ xử lý có thể được sử dụng để transfer đối số thay vì dùng stacks - giải pháp này rõ ràng là nhanh hơn và memory-saving. Thực tế là các compilers khác nhau có thể dùng những tricks khác nhau, hoàn toàn không tương thích. Thêm nữa, same compilers có thể dùng các tactics khác nhau cho những nền tảng khác nhau (e.g. một cho 32-bit environment và một cái khác cho 64-bit environment).

	- May mắn là, chúng ta có thể kiểm soát được quá trình truyền các đối số khác nhau trực tiếp ở C language level và treat mọi thứ bên dưới nó như 1 black box. Đây là những gì chúng tôi sẽ làm.

	- Một điều cần giải thích - Kết quả của hàm trả về cho caller như nào?
		Nó phụ thuộc. Một vài compilers có thể dùng 1 trong những thanh ghi bộ xử lý làm nơi lưu trữ tạm thời cho giá trị của kết quả. Một số khác có thể dùng 1 phần bộ nhớ chuyên dụng của máy tính. Nó ít thú vị hơn so với việc truyền đối số.


2.2.1.1 Handling a variable number of parameters – the ellipsis
	- Một variable number của những tham số được xử lý bằng C language ở 2 level khác nhau:
		. the higher level - the language's syntax level, phải được compiler phục vụ chính xác trong quá trình compilation, giúp nó nhận biết các tính năng đặc biệt của hàm.

		. the lower level - the execution environment level, có nhiệm vụ physically access vào những tham số và cung cấp giá trị của chúng.

	- Vai trò đầu tiên được thực hiện bởi 1 symbol đặc biệt (thực chất là punctuator - dấu câu) có 1 tên đặc biệt - ellipsis (dấu 3 chấm).
		Thuật ngữ này đề cập đến 1 hình thức lược bỏ 1 phần của 1 số từ trong khi không làm thay đổi ý nghĩa, vì vẫn đoán được phần còn thiếu là gì.

	- Xem prototype sau:

		int fun(int a, ...);

	Nó khai báo fun là 1 function returning int và lấy ít nhất (ít nhất nha) 1 đối số type int

	- Tức là compiler sẽ chấp nhận tất cả invocations sau:

		fun (1);
		fun (1, 2);
		fun (1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 0, 0, 0, 0, 0, 0,
		     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

	và tất nhiên không chấp nhận thằng này:

		fun();


2.2.1.2
	RULE #1:
		- Ellipsis phải là element cuối cùng của list tham số
			
		- Như này không được:

				int fun(int a, ..., int b);

	Rule #2:
		- Ellipsis không được chỉ là element duy nhất trong list tham số:

			int fun(...);

	Rule #3:
		- Không được dùng nhiều lần ellipsis:

			int fun(..., ...);

	Rule #4:
		- Lượng tham số trước ellipsis là tùy ý (tất nhiên là trừ 0):

			int fun(int a, char c, float c, ...);

	- Ellipsis có thể dùng như 1 tham số macro, nhưng sẽ được bàn sau.

	- Giờ cho ta thấy cách hàm printf() được khai báo trong 1 vài implementations.

	- This is how gcc 4.9.3 sees it:

		extern int printf (const char *__restrict __format, ...);

	- Một vài phần của header này nhìn unfamiliar -> sẽ được giải thích ở chapter sau.

	- CL 19.00.24210 có view hơi khác:

		_inline int __cdecl printf(char const* const _Format, ...);

	- Note 2 từ khóa _inline và __cdecl.
		. Từ đầu tiên đặt ra 1 số cách xử lý đặc biệt cho hàm (nó gợi ý compiler insert phần thân hàm thay vì invocation; các gợi ý này có thể bỏ qua khi có nhiều invocations trong cùng 1 hàm)

		. Từ thứ hai xác định calling convention (quy ước gọi hàm) cho hàm.

	- Giới thiệu 3 thuật ngữ quan trọng:
		. 1 hàm mà có thể được gọi với 1 list tham số thay đổi được được gọi là variadic function.

		. Tất cả các tham số được liệt kê rõ ràng tạo thành cái gọi là fixed part của list tham số và cũng có thể được gọi là fixed parameters (tham số cố định).

		. Tất cả tham số ẩn sau ellipsis tạo thành variable/varying part của list tham số.


2.3.1.1 Handling a variable number of parameters – stdarg.h and its facilities
	- Level thấp hơn của các cơ chế phụ thuộc vào macro (mặc dù 1 số chúng nhìn giống và hoạt động giống hàm) được defined trong stdarg.h, do đó nếu định triển khai 1 hàm với list tham số biến thiên (hay variadic function), ta phải:

		#include <stdarg.h>

	- Quy trình truy cập các tham số từ variable part (được biểu thị bằng ellipsis) được tổ chức theo cách sau:
		. Vị trí trong stack, nơi mà các tham số được triển khai, phải được tìm thấy và ghi nhớ. Như đã biết, đối số đầu tiên của bọn này nằm ngay bên dưới tham số cuối cùng của fixed part.

		. Mỗi tham số của phần biến phải được định vị và được đưa đến một cách riêng lẻ for further processing.

		. Các tham số chỉ có thể được truy cập một cách tuần tự - từ cái đầu tiên đến cái cuối cùng; Không có cách nào truy cập phần tử thứ n một cách trực tiếp, bỏ qua những phần tử khác.

		. Trở về bất kì tham số nào phía trước cũng bị cấm luôn

		. Có thể reset quá trình xử lý về trạng thái ban đầu và cũng có thể truy cập lại tất cả tham số 1 lần nữa

		. Không có cơ chế tự động nào cho phép invokee xác định độ dài của variable part của list tham số.

	- Xem snippet sau - nó đúng nhan:

		#include 


		int
		sum (int n, ...)
		{
		}

	- Đó là 1 seed of code và chúng ta sẽ enrich nó để xây dựng 1 example hoàn chỉnh và hoạt động được. Chúng ta muốn viết 1 function để thực hiện tính tổng các giá trị nguyên của tất cả đối số của nó.

	- Bởi vì như đã nói trước đó, 1 hàm dùng số lượng biến thiên các tham số không thể tự động xác định (ở level ngôn ngữ) có bao nhiêu tham số đã được truyền vào nó. Có 2 cách:
		. Sử dụng 1 trong các tham số từ fixed part để pass thông tin về độ dài của variable part.

		. put 1 giá trị đặc biệt vào cuối variable part (còn được gọi là guardian).

	- Hàm printf() sử dụng phương pháp đầu tiên. Còn hàm execl() - bạn chưa biết hàm này đâu - dùng phương pháp sau.

	- Chúng ta sẽ dùng cái đầu tiên, và ta muốn hàm hoạt động theo cách sau:
		. sum(0) return 0 

		. sum(2,1,3) return 4 (2 elements - 1 và 3)

		. sum(10,1,1,1,1,1,1,1,1,1,1) return 10, of course.

	- Note: Không có check tự động nào được thực hiện bởi compiler hay environment để xác định liệu bạn có cung cấp số lượng tham số tương đương với tham số đầu tiên không. Đó là trách nhiệm của bạn.


2.3.1.2
	- Bước đầu tiên là khai báo 1 biến với 1 type đặc biệt được thiết kế để theo dõi các tham số bên trong variable part của list tham số. Type này được defined trong stdarg.h, tên là:

		va_list

	- Note: Tất cả những items từ stdarg.h đều có tên prefixed by va_

	- va_list thực ra là 1 macro, và nó mở rộng sang các định nghĩa hoàn toàn khác nhau phụ thuộc vào compiler hay nền tảng. Điều này là bình thường. Nó có thể là một kiểu pointer (có khả năng cao). Nhma không cần quan tâm lắm.

	- Khai báo 1 biến tên list:

		#include 


		int
		sum (int n, ...)
		{
		  va_list list;
		  int tot = 0;
		}

	- Có thể khai báo nhiều biến kiểu này và sử dụng nó riêng biệt để xử lý cùng variable part. Chúng sẽ hoạt động độc lập.

	- Khai báo một biến tot để lưu trữ tổng mà ta sắp tính và khởi tạo = 0.

	- Giờ ta liên kết biến mới với list tham số. Thực hiện việc này bằng 1 macro tên va_start()

	- va_start() expect 2 đối số:
		. tên của list cần liên kết (đã được khai báo trước đó)

		. tên của tham số cuối cùng trong fixed part.

	- Nhớ lại calling conventions, và giải thích ý nghĩa của macro argument thứ hai.

	- Khi nhìn vào stack có thể thấy tham số cố định cuối cùng nằm cạnh biến đầu tiên. Đây là điểm mà ta có thể bắt đầu đi qua variable part.

	- Updated snippet:

		#include 


		int
		sum (int n, ...)
		{
		  va_list list;
		  va_start (list, n);
		  int tot = 0;
		}

	- Note: va_start() return no value.


2.3.1.3
	- Giờ nghĩ lại chúng ta muốn làm gì đã:
		. ta muốn lấy n giá trị từ variable part của list tham số.

		. Tất cả giá trị này đều type int (đây là cách chúng ta xác định vấn đề)

	- Đầu tiên: sử dụng 1 loop. Phần còn lại được thực hiện bởi macro tên va_arg()

	- va_arg() expects 2 đối số:
		. tên của list cần lấy giá trị (list này phải được khởi tạo trước đó bằng va_start() invocation)

		. tên của type của giá trị đang được tìm để đưa vào

	- va_arg() thực hiện 2 thứ:
		. Vô hiệu hóa con trỏ ẩn dưới đối số va_list (đây là lí do tại sao nó cần biết type của giá trị)

		. Cập nhật con trỏ - di chuyển con trỏ tới giá trị tiếp theo trong stack (cần biết type của giá trị)

	- Snippet đã gần như hoàn thiện:

		#include 


		int
		sum (int n, ...)
		{
		  va_list list;
		  va_start (list, n);
		  int tot = 0;
		  while (n--)
		    {
		      int v = va_arg (list, int);
		      tot += v;
		    }
		}


	- Tất nhiên, biến v là dư thừa. Giới thiệu nó chỉ để code dễ đọc hơn thôi.

	- Note: va_arg() returns 1 giá trị có type giống hệt với giá trị được chỉ định bởi đối số thứ hai.

	- stdarg.h yêu cầu list của va_list type phải được closed/terminated/ended sau khi xử lý. Việc này được thực hiện bởi macro tên va_end()

	- va_end() expects 1 đối số - tên của list được kết thúc. Từ thời điểm này, list không được truy cập nữa, mặc dù vẫn có thể khởi tạo lại bằng cách gọi va_start() một lần nữa.

	- Chúng ta cần bổ sung function thêm lần cuối. Ta sẽ thêm va_end() và câu lệnh return - giờ function sẽ hoàn thiện:

		#include 


		int
		sum (int n, ...)
		{
		  va_list list;
		  va_start (list, n);
		  int tot = 0;
		  while (n--)
		    {
		      int v = va_arg (list, int);
		      tot += v;
		    }
		  va_end (list);
		  return tot;
		}

	Note: va_end() returns no value.


2.3.1.4
	- Thêm hàm main() vào để test code mới

		#include <stdarg.h>

		#include <stdio.h>

		int
		sum (int n, ...)
		{
		  va_list list;
		  va_start (list, n);
		  int tot = 0;
		  while (n--)
		    {
		      int v = va_arg (list, int);
		      tot += v;
		    }
		  va_end (list);
		  return tot;
		}

		int
		main (void)
		{
		  printf ("%d\n", sum (0));
		  printf ("%d\n", sum (2, 1, 3));
		  printf ("%d\n", sum (10, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1));
		  return 0;
		}


2.3.1.5
	- Giờ đến với cái gì đó phức tạp hơn

	- Code:

		#include <stdarg.h>

		#include <string.h>

		#include <stdio.h>

		#include <stdlib.h>

		char *
		concat (char *str, ...)
		{
		  if (str == NULL)
		    return NULL;
		  int totlen = strlen (str);
		  va_list lenlist, strlist;
		  va_start (lenlist, str);
		  va_copy (strlist, lenlist);
		  char *p = va_arg (lenlist, char *);
		  while (p)
		    {
		      totlen += strlen (p);
		      p = va_arg (lenlist, char *);
		    };
		  va_end (lenlist);
		  char *newstr = malloc (totlen);
		  strcpy (newstr, str);
		  p = va_arg (strlist, char *);
		  while (p)
		    {
		      strcat (newstr, p);
		      p = va_arg (strlist, char *);
		    }
		  va_end (strlist);
		  return newstr;
		}

		int
		main (void)
		{
		  char *s1 = concat ("Mary ", "had ", "a little lamb", NULL);
		  char *s2 = concat ("Single string", NULL);
		  printf ("%s\n", s1);
		  printf ("%s\n", s2);
		  free (s1);
		  free (s2);
		  return 0;
		}

	- Viết 1 hàm concatenate tất cả các string nhận được thành 1 string mới nhất được allocated và return về con trỏ tới string đó. Hàm phải được gọi ít nhất 1 lần, không phải con trỏ NULL, char *, và list tham số biến thiên phải được kết thúc bằng con trỏ NULL, đóng vai trò là guardian.

	- Chú ý:
		. Ta cần xem lại danh sách tham số biến 2 lần: thứ nhất, tính tổng độ dài của tất cả strings được concatenated (để tiết kiệm khi allocating bộ nhớ) và thứ hai, nối các strings; điều này có thể thực hiện nhiều cách, nhưng ta quyết định dùng 2 lists tên lenlist và strlist (line 13)

		. Khởi tạo lenlist theo cách bình thường (line 14)

		. strlist có thể khởi tạo tương tự, nhưng chúng tôi muốn cho bạn biết 1 macro nữa từ stdarg.h và đã quyết định chỉ gán strlist dùng giá trị hiện tại của lenlist; chúng ta không thể dùng phép gán thông thường (=) cho mục đích này, vì bản chất cả va_list là điều chúng tôi không biết, và chúng tôi cũng không biết liệu 1 phép gán có thể thực hiện điều đó ở đây hay không (e.g. một số implementations có thể dùng 1 array để store list - 1 phép gán không thể handle nó)

		. Đó là lý do chúng tôi dùng va_copy() macro (line 15) - nó gán đối số bên phải cho đối số bên trái, nhưng thực hiện theo cách mà sẽ hoạt động ở mọi nơi và mọi lúc.

		. Note: list được khởi tạo thông qua va_copy() phải được kết thúc theo cách tương tự như list thu được từ va_start() - do đó macro va_end() cũng cần thiết cho strlist (line 29)

		. Cả 2 while loops (lines 17 và 25) lặp qua phần biến của list tham số, fetching các con trỏ type char * từ chúng.

	- Ask: Chuyện gì sẽ xảy ra nếu ai đó quên guardian và không có NULL at the end của list tham số?

	- Note: va_copy() returns no value


2.3.1.6
	- Một code khác - đoạn cuối cùng trong phần này - cho thấy một very poor attempt (nhưng vẫn hoạt động) trong việc triển khai lại hàm printf().

	- Tất nhiên, không thể viết lại toàn bộ hàm printf() chỉ trong một slide. Chúng tôi đã phải đơn giản hóa nhiều điều. May mắn thay, không ai sẽ sử dụng hàm của chúng tôi trong thực tế - nó chỉ là một thử nghiệm.

	- Hàm của chúng tôi expects ít nhất một đối số chứa một formatting string (chuỗi định dạng). Chỉ có ba định dạng được phép trong đó:

		. c - cho giá trị char;
		. d - cho giá trị int;
		. s - cho chuỗi (char *).

	- Hàm sẽ cố gắng trích xuất càng nhiều đối số nào được chỉ định bên trong formatter. Note: không có kiểm tra nào được thực hiện, vì vậy hàm rất vulnerable nếu mắc bất kỳ lỗi nào khi gọi.

	- Nhìn code:

		#include <stdio.h>

		#include <stdarg.h>

		void
		printstr (char *s)
		{
		  while (*s)
		    putchar (*s++);
		}

		void
		print (char *form, ...)
		{
		  va_list list;
		  va_start (list, form);
		  char c = *form++;
		  char digs[10], *p;
		  while (c)
		    {
		      switch (c)
			{
			case 's':
			  printstr (va_arg (list, char *));
			  break;
			case 'c':
			  putchar (va_arg (list, int));
			  break;
			case 'd':
			  p = digs;
			  int i = va_arg (list, int);
			  do
			    {
			      *p++ = (i % 10) + '0';
			      i /= 10;
			    }
			  while (i);
			  while (p > digs)
			    {
			      putchar (*--p);
			    }
			  break;
			}
		      c = *form++;
		    }
		  va_end (list);
		}

		int
		main (void)
		{
		  print ("sdscs", "Mary had ", 21, " little lambs and ", '1',
			 " tiny rhinoceros.\n");
		  return 0;
		}

		. Vì chúng tôi muốn tránh sử dụng hoàn toàn hàm printf() tiêu chuẩn, nên chúng tôi đã định nghĩa một hàm hỗ trợ mang tên printstr() (line 5) để output strings (chúng tôi không thể sử dụng puts() vì nó output ký tự xuống dòng ngay sau chuỗi được in); prinstr() sử dụng putchar() để xuất từng ký tự một;
		
		. Main loop của hàm print() (line 13) lặp qua nội dung của form parameter và sử dụng câu lệnh switch để chọn hành vi thích hợp của nó;
		
		. Trường hợp cho 'c' (line 20) gọi va_arg() chỉ định type là int - bạn không nên sử dụng char ở đây vì giá trị char luôn được thăng cấp thành ints khi được chuyển làm đối số của hàm;
		
		. Trường hợp cho 's' (line 17) gọi va_arg() chỉ định type là char* (không có gì đặc biệt)
		
		. Trường hợp cho 'd' (line 23) chứa một loop rất đơn giản (và rất rủi ro), chuyển đổi int thành một series các ký tự; như bạn có thể đoán, nó hoàn toàn ngớ ngẩn - ví dụ, nó không thể chuyển đổi số âm; bạn có thể cải thiện nó nếu bạn muốn nó trở nên đáng tin cậy hơn.


2.4.1.1 Handling a variable number of parameters – va_list as a parameter
	- Variable part của list tham số (mang theo bởi biến type va_list) có thể truyền dưới dạng tham số.

	- Xem đoạn sau:

		int
		max (int n, va_list vals)
		{
		}

	- Tham số đầu tiên được thiết kế để truyền thông tin về số lượng giá trị cần tìm kiếm để tìm giá trị lớn nhất trong tham số thứ hai.

	- Làm thế nào chúng ta gọi một hàm như vậy?

	Chúng ta có thể thực hiện nó như thế này không?

		k = max (2, 1, 2, 3);

	Không, không thể. Hàm yêu cầu 2 tham số, không thể cung cấp 4.

	- Nhưng chúng ta có thể gọi hàm với một giá trị va_list đã được khởi tạo trước đó.

	- Nhìn code:

		int
		va_max (int n, ...)
		{
		  va_list l;
		  va_start (l, n);
		  int r = max (n, l);
		  va_end (l);
		  return r;
		}

	- Việc gọi đã được triển khai bên trong một variadic function (hàm biến tham số), tạo, khởi tạo và kết thúc một biến va_list. Đó là một ví dụ hoàn chỉnh, hoạt động về việc kết hợp hai hàm: một hàm biến tham số và một hàm không biến tham số (non-variadic function). Chúng ta có thể nói rằng va_max() là một wrapper (bọc) cho max() - nó thay đổi giao diện mà không thay đổi chức năng.

	- Bây giờ chúng ta sẽ triển khai hàm cơ bản - max().


2.4.1.2
	- Đây là một trong những dạng có thể có của hàm max()

		int
		max (int n, va_list vals)
		{
		  int m = va_arg (val;
				  s, int);
		  while (--n > 0)
		    {
		      int k = va_arg (vals, int);
		      if (k > m)
			  m = k;
		    }
		  return m;
		}

	- Note: Hàm giả sử có ít nhất 1 giá trị bên trong vals.


2.4.1.3
	- Program hoàn chỉnh, including cả 2 hàm:

		#include <stdarg.h>

		#include <stdio.h>

		int
		max (int n, va_list vals)
		{
		  int m = va_arg (vals, int);
		  while (--n > 0)
		    {
		      int k = va_arg (vals, int);
		      if (k > m)
			m = k;
		    }
		  return m;
		}

		int
		va_max (int n, ...)
		{
		  va_list l;
		  va_start (l, n);
		  int r = max (n, l);
		  va_end (l);
		  return r;
		}

		int
		main (void)
		{
		  int x = va_max (3, 1, 2, 3);
		  printf ("%d\n", x);
		  return 0;
		}


2.4.1.4
	- Chúng tôi đã thu thập một số prototypes hàm:

		#include <stdio.h>

		int printf(char *format, ...);
		int fprintf(FILE *stream, char *format, ...);
		int dprintf(int fd, char *format, ...);
		int sprintf(char *str, char *format, ...);
		int snprintf(char *str, size_t size, char *format, ...);

	- Tất cả các hàm này đều là variadic (biến tham số) và chấp nhận số lượng đối số cần thiết để thực hiện các hành động mong muốn. Dành thời gian tìm hiểu về chúng:

		. printf() xây dựng một string theo format và gửi nó đến stdout;
		
		. fprintf() làm tương tự như printf(), nhưng gửi string đến bất kỳ luồng nào, không chỉ stdout;
		
		. dprintf() làm tương tự như fprintf(), nhưng gửi string đến một file được xác định bởi descriptor (chỉ số) (chúng ta sẽ thảo luận về file descriptor sớm);
		
		. sprintf() làm tương tự như printf(), nhưng gửi string kết quả đến một string khác;
		
		. snprintf() làm tương tự như sprintf(), nhưng giới hạn độ dài của string kết quả thành một giá trị cụ thể.

	- Tất cả các hàm này đều có những phiên bản variadic - dưới đây là dạng chúng:

		#include <stdarg.h>

		int vprintf(char *format, va_list ap);
		int vfprintf(FILE *stream, char *format, va_list ap);
		int vdprintf(int fd, char *format, va_list ap);
		int vsprintf(char *str, char *format, va_list ap);
		int vsnprintf(char *str, size_t size, char *format, va_list ap);

		. Tất cả các tên đều có "v" prefix.

		. Tham số char *format được thay thế bằng va_list ap trong tất cả các trường hợp.

	Làm thế nào chúng ta sử dụng những hàm này? Liệu chúng có thực sự cần thiết không? Có hữu ích không?

	Hãy tưởng tượng rằng khách hàng của bạn muốn bạn viết một hàm hoạt động giống như printf(), nhưng puts the whole output into an elegant frame.

	Vâng, chúng tôi đồng ý, đó là một yêu cầu hơi eccentric.


2.4.1.5
	- Nhìn code:

		#include <stdio.h>

		#include <stdarg.h>

		#include <string.h>

		void
		line (int n)
		{
		  putchar ('+');
		  n -= 2;
		  while (n--)
		    putchar ('-');
		  putchar ('+');
		  putchar ('\n');
		}

		int
		frprintf (char *format, ...)
		{
		  va_list list;
		  int len;
		  char buf[1024];

		  va_start (list, format);
		  vsprintf (buf, format, list);
		  len = strlen (buf) + 4;
		  line (len);
		  printf ("| %s |\n", buf);
		  line (len);
		  va_end (list);
		  return len * 3;
		}

		int
		main (void)
		{
		  frprintf ("Hello world!");
		  frprintf ("Mary had %d little %s", 2, "hippos");
		  return 0;
		}

	- Giải thích vài thứ:
		. Hàm line() (line 7) xuất ra các phần trên và dưới của khung;

		. Hàm frprintf() (line 16) nhận định dạng, gọi hàm vsprintf() (line 22) để có được các giá trị được định dạng từ phần biến, mở rộng nó với các phần trái và phải của khung và cuối cùng (line 25) gửi nó đến stdout;

		. Hàm frprintf() trả về số ký tự đã gửi đến stdout mà không tính các ký tự xuống dòng - liệu chúng ta đã đếm chúng đúng không?


2.4.1.6
	- Hãy xem xét các khía cạnh khác nhau của nhập/ xuất. Bạn có biết về các hàm này không?

		#include <stdio.h>

		int scanf(const char *format, ...);
		int fscanf(FILE *stream, const char *format, ...);
		int sscanf(const char *str, const char *format, ...);

	. scanf() đọc một series ký tự từ stdin và chuyển đổi chúng thành các giá trị của các type mong muốn theo các định dạng đã được định nghĩa trong format;

	. fscanf() làm tương tự như scanf(), nhưng đọc các ký tự từ bất kỳ stream nào, không chỉ stdin;

	. sscanf() làm tương tự như scanf(), nhưng đọc các ký tự từ string khác, không phải là stream.

	- Như bạn có thể đoán, những hàm này cũng có các phiên bản variadic (biến tham số).

	- Dưới đây là chúng:

		#include <stdarg.h>

		int vscanf(const *format, va_list ap);
		int vfscanf(FILE *stream, char *format, va_list ap);
		int vsscanf(char *str, char *format, va_list ap);

	- Chúng hoạt động theo cùng cách như các hàm đã được hiển thị trước đó từ printf family.


2.5.1.1 Handling a variable number of parameters – variadic macros
	- Functions không phải là thứ duy nhất có thể là variadic - các macro cũng có thể có tính chất tương tự, mặc dù cách "variadism" ("biến tham số") hoạt động cho chúng là hoàn toàn khác nhau.

	- Dưới đây là một khai báo của một variadic macro đơn giản:

		#define MYPRINT(...)    printf("Hi!\n")
	
	- Note: các variadic macro có thể không có tham số cố định nếu chúng chỉ chứa dấu ba chấm. Macro của chúng ta hiện tại không sử dụng bất kỳ tham số nào. Điều đó sẽ thay đổi sớm thôi.

	- __VA_ARGS__ symbol chứa tất cả các phần tử được truyền vào macro thông qua dấu ba chấm.

	- Dưới đây là một ví dụ đơn sử dụng symbol:

		#define MYPRINT(...)    printf(__VA_ARGS__)

	- Note:
		. Symbol chỉ có sẵn bên trong các macro giống như hàm;

		. Nó chỉ có thể sử dụng khi biểu tượng dấu ba chấm đã xuất hiện trước đó trong định nghĩa của macro.

	- Bây giờ chúng ta có thể sử dụng macro trong ngữ cảnh ví dụ sau:

		MYPRINT("Alfa\n");
		MYPRINT("Bravo %s\n", "Charlie");
	

2.5.1.2
	- Cũng có thể kết hợp các đối số cố định và biến tham số, nhưng bạn cần dấu ba chấm phải là phần cuối cùng của danh sách tham số của macro, như sau:

		#define PUT(x, ...) fprintf(x, __VA_ARGS__)

	- Bây giờ chúng ta có thể sử dụng macro như sau:

		PUT(stdout, "Delta\n");
		PUT(stderr, "Echo %s\n", "Foxtrot");

	- Toán tử macro # có thể được áp dụng cho biểu tượng __VA_ARGS__, như sau:

		#define OUT(...) puts(#__VA_ARGS__)

	- Một macro được sử dụng như sau:

		OUT("Alfa\n");
		OUT("Bravo %s\n", "Charlie");

	tạo ra đầu ra như sau:

		"Alfa\n"
		"Bravo %s\n", "Charlie"

	- Chúng tôi đã thu thập tất cả các ví dụ trước đó trong một source file - bạn có thể sử dụng nó cho own experiments, link:

		https://edube.org/learn/c-advanced/handling-a-variable-number-of-parameters-variadic-macros-3



~ Module 3 ~

	In this module, you will learn about:

		. POSIX, API, ABI, WINAPI, etc.;
		. access();
		. open();
		. errno;
		. close();
		. read();
		. write();
		. lseek();
		. dprintf();
		. stat();
		. symlink(), link();
		. readlink();
		. unlink();
		. fcntl() and ioctl().


3.1.1.2 Low-level I/O – some mysterious abbreviations
	- API (as in Application Programming Interface) là một bộ tiêu chuẩn, giao thức, quy tắc, thủ tục, quy ước, quyết định, thói quen và truyền thống, được các lập trình viên sử dụng để kết nối code của họ một cách hiệu quả và an toàn với code hiện có và ngược lại, để làm cho các tính năng mới của code của họ tương thích với code của một lập trình viên khác.

	- Lưu ý rằng thuật ngữ API chỉ đề cập đến source code mà thôi - một API điển hình nói ít hoặc gần như không nói gì về cách kết nối này hoạt động ở binary level.

	- Hai trong số những API đặc trưng nhất là:

		. POSIX (Portable Operating System Interface for Unix): một bộ tiêu chuẩn được định nghĩa cho các hệ thống Unix và giống Unix; thực ra bộ này is much more than just an API, nhưng API là một phần không thể tách rời của nó; nhiều trong số các hàm được định nghĩa trong C language standards cũng được bao gồm trong POSIX (đặc biệt là những hàm liên quan đến các dịch vụ của hệ điều hành); chúng ta có thể nói, hơi hùng biện, rằng POSIX là bảo vệ của tính di động của phần mềm - code được viết với sự tôn trọng đối với yêu cầu API có cơ hội tốt để được compiler và chạy thành công trên nhiều, hoặc thậm chí trên tất cả, các nền tảng sử dụng các quy ước giống nhau; 

		. Windows API (hoặc gọi là WinAPI): một bộ tiêu chuẩn tương tự, nhưng được sử dụng trong môi trường Microsoft Windows; nó rộng lớn và phức tạp hơn nhiều so với POSIX, vì nó bao gồm gần như tất cả các loại dịch vụ của hệ điều hành (ví dụ: tương tác với GUI).

	- Còn nhiều API khác trên thế giới. Trên thực tế, mỗi lập trình viên đều định nghĩa API của riêng mình khi bắt đầu một dự án phần mềm mới.


3.1.1.3 Low-level IO
	- Thay đổi chỉ một chữ cái brings us into a completely different world.

	- Look:

		ABI

	ABI (viết tắt của Application Binary Interface) là một bộ tiêu chuẩn tương tự, nhưng liên quan đến level nhị phân. Một API có thể chỉ cho bạn cách viết một chương trình để tương thích với một hệ điều hành hoặc nền tảng được chọn, nhưng nó không nói gì về cách code được biên dịch tương tác với các dịch vụ của hệ điều hành hoặc các thành phần phần mềm khác. Ngược lại, ABI không phụ thuộc vào API. Thông thường, các hệ thống giống Unix sử dụng cùng một API (POSIX) nhưng triển khai một ABI hoàn toàn không tương thích, khiến code thực thi bị non-portable (khả năng portable chỉ có thể được đảm bảo ở source language level - điều này có nghĩa là code phải được biên dịch lại để có thể chuyển đến một nền tảng mới).

	- Chúng ta có thể nói rằng:

		. Nếu bạn không phải là một nhà phát triển hệ điều hành, vấn đề quan trọng nhất đối với bạn là API;

		. ABI có thể là mối quan tâm đối với bạn nếu bạn bắt đầu phát triển các phần low-level của OS (hệ điều hành) như các trình điều khiển hoặc một compiler mới với bộ công cụ của nó.

	- Chương hiện tại xử lý low level (thực ra là level thấp nhất) của các hoạt động input/output có sẵn trong C language. Đây là nơi code nhị phân của bạn contacts trực tiếp với hệ điều hành. Chúng tôi đã nói rằng C language có mối liên quan chặt chẽ với Unix và các hệ thống giống Unix, vì vậy tất cả các hàm được thiết kế để thực hiện các hoạt động I/O ở low level thực sự chỉ là wrappers (bao bọc) của các dịch vụ hệ điều hành tương ứng.

	- Điều này có thể có nghĩa là các hệ điều hành không tương thích với Unix (theo nghĩa của API) có thể triển khai dịch vụ của họ một cách hoàn toàn khác nhau. Như câu nói nổi tiếng, trong Unix mọi thứ đều là một file. Đừng hiểu đó là đúng. Nhưng các hệ thống giống Unix thích treats nhiều đối tượng hệ thống như thể chúng là các file. Ví dụ, các network channels đặc biệt được sử dụng để truyền dữ liệu (gọi là network (ổ cắm mạng) - chúng ta sẽ thảo luận về chúng sau) được nhìn thấy bởi lập trình viên như các file. Trong Unix, một hàm I/O ở low level cụ thể có thể hoạt động không chỉ trên các file thực sự mà còn trên thiết bị và các tiện ích khác.

	- Các hệ điều hành khác có thể hoạt động theo cách khác. Chúng có thể triển khai các hàm giống nhau một cách khác, hoặc có thể có tên khác, hoặc thậm chí có thể không được triển khai chút nào.

	- Điều này là hoàn toàn bình thường. Đừng ngạc nhiên.

	- Hầu hết các hàm mà chúng ta sẽ thảo luận đến đây đều đến từ file tiêu đề unistd.h. Chính cái tên của nó đã nói lên điều đó.

	- Vậy nên, mà không có thêm trì hoãn nào, hãy đào sâu vào low level of input/output.


3.1.1.4
	- Bạn có thể đặt câu hỏi: tại sao chúng tôi gọi vấn đề này là "low-level"? Tại sao level lại thấp? Nó thấp hơn bất kỳ level nào khác như thế nào?

	- Bạn đã quen thuộc với một số hàm được thiết kế để xử lý file như fopen(), fread(), fwrite() hoặc fclose(). Chúng có đủ thấp không? Hay chúng quá cao?

	- Chúng khá cao. Có một khoảng lớn giữa những hàm này và input/ouput vật lý. Nhiều điều bí ẩn xảy ra trong không gian này. Hãy nói một chút về ba trong số chúng:

		. Data buffering occurs (Đệm dữ liệu diễn ra) – khi bạn gọi fwrite() hoặc fprintf() ở đây, không có gì đảm bảo rằng dữ liệu của bạn sẽ ngay lập tức được ghi vào phương tiện; rất có thể nó sẽ được đệm và sẽ đợi một thời điểm thuận lợi để được đẩy xuống đĩa hoặc terminal; quy tắc tương tự (nhưng ngược lại) áp dụng khi đọc dữ liệu với các hàm fread() hoặc fscanf(); bạn có thể mong đợi rằng có rất nhiều dữ liệu trong bộ đệm hệ thống hơn là bạn cần để hoàn thành các chức năng của mình; chúng ta có thể nói rằng buffering (đệm) được hướng dẫn bởi quy tắc sau: đọc càng sớm càng tốt, ghi càng trễ càng tốt; hành động sau cùng đôi khi được gọi là "readahead", hành động đầu tiên: "write-behind"; lưu ý rằng những cơ chế như vậy hoàn toàn trong suốt và gần như hoàn toàn độc lập với bạn; bạn có một chút control thông qua các hàm như setvbuf() (control kích thước bộ đệm) và flush() (đẩy các bộ đệm đầu ra ngay lập tức), nhưng bạn không thể chỉ đơn giản tắt nó đi.

		. line translation occurs (Chuyển đổi dòng) – khi bạn gọi một hàm như fgets(), nó phải thực hiện một readahead để lấy một phần dữ liệu có thể chứa các ký tự kết thúc dòng (đừng quên rằng một đĩa vật lý có thể đọc và ghi dữ liệu bằng một lượng cố định được gọi là các sector, ví dụ: 512 bytes); tiếp theo, hàm trích xuất một dòng đầy đủ từ phần đó hoặc phải lặp lại đọc để đạt đến ký tự kết thúc dòng gần nhất; tương tự, fputs() phải trì hoãn việc write vật lý đến khi dữ liệu đã ghi đủ để điền vào sector; hơn nữa, các hệ điều hành khác nhau có thể sử dụng các byte khác nhau để đánh dấu kết thúc dòng - fgets() cần có thể xử lý điều này;

		. data translation occurs (Chuyển đổi dữ liệu) – các hàm như fprintf() hoặc fread() có khả năng chuyển đổi dữ liệu từ biểu diễn internal sang một dạng có thể đọc được cho human và ngược lại.

	- Hãy tưởng tượng rằng chúng ta muốn thực hiện các hành động sau:

		. Tạo một file tạm thời có tên là file.tmp và open nó để ghi;
		. Ghi hai byte có giá trị khác nhau vào file;
		. Close và reopen file để đọc;
		. Đọc hai byte into một biến short int;
		. Close file;
		. Xuất biến ra stdout;
		. Xóa file tạm thời.

	- Dưới đây là cách code có thể nhìn ở C language libraries level, hãy xem code:

		#include <stdio.h>

		#define FILE_NAME "file.tmp"

		int
		main (void)
		{
		  FILE *f = fopen (FILE_NAME, "wb");
		  if (f)
		    {
		      unsigned char c = 0x02;
		      fwrite (&c, 1, 1, f);
		      c = 0x04;
		      fwrite (&c, 1, 1, f);
		      fclose (f);
		      f = fopen (FILE_NAME, "rb");
		      if (f)
			{
			  short i;
			  fread (&i, 2, 1, f);
			  fclose (f);
			  printf ("%d\n", i);
			}
		      unlink (FILE_NAME);
		    }
		  return 0;
		}

	- Code đã tự giải thích rồi, còn một hàm cần phải được giải thích - unlink(). Nó đơn giản là xóa file có tên được chỉ định trong đối số duy nhất.


3.1.1.5
	- Rewrte code chỉ sử dụng các hàm low-level I/O. Chức năng duy nhất mà chúng tôi sẽ không loại bỏ là chức năng được trình bày bởi printf() - chúng tôi không muốn triển khai nó từ đầu. Thay vào đó, chúng tôi sẽ sử dụng sprintf() và tự viết string kết quả.

	- Do một số sự khác biệt trong implementation, chúng tôi không thể hiển thị cho bạn code một cách tổng quát. Chúng tôi đã chuẩn bị hai code khác nhau: một phù hợp với các compiler Unix và tương thích Unix (gcc, Clang, mingw-gcc, v.v.), và một code khác cho compiler CL của Microsoft.

	- Phiên bản đầu tiên:

		#include <stdio.h>

		#define FILE_NAME "file.tmp"

		int
		main (void)
		{
		  FILE *f = fopen (FILE_NAME, "wb");
		  if (f)
		    {
		      unsigned char c = 0x02;
		      fwrite (&c, 1, 1, f);
		      c = 0x04;
		      fwrite (&c, 1, 1, f);
		      fclose (f);
		      f = fopen (FILE_NAME, "rb");
		      if (f)
			{
			  short i;
			  fread (&i, 2, 1, f);
			  fclose (f);
			  printf ("%d\n", i);
			}
		      unlink (FILE_NAME);
		    }
		  return 0;
		}

	Trông khác biệt, phải không?

	- Giờ chúng tôi muốn bạn nghiên cứu ví dụ và đoán xem nó hoạt động như thế nào.

	- Chúng tôi đã cung cấp cho bạn các liên kết đến cả hai phiên bản ở dưới đây. Chú ý đến sự khác biệt giữa chúng.

	- Note: khi chạy trên một máy tính với kiến trúc little-endian, chương trình sẽ xuất ra:

		1026
		output

	và với kiến trúc khác:

		516
		output

	- Bạn nên có khả năng giải thích tại sao.


3.2.1.1 Low-level I/O – what is a file descriptor
	- Bạn có nhớ cách mà các file đã mở được biểu diễn bởi các hàm từ stdio.h không? Đúng, chúng sử dụng một black-box structure riêng biệt được đặt tên là FILE. Để chính xác, việc sử dụng cấu trúc này như một toàn bộ có thể gây rắc rối, vì vậy chúng ta thường sử dụng một con trỏ đến nó. Cách sử dụng tiêu biểu của nó như sau:

		FILE *f = fopen(FILE_NAME, "wb");

		. Hàm fopen() trả về một con trỏ đến structure mới được tạo;

			. structure này được điền với dữ liệu cần thiết để vận hành file một cách đúng đắn;

			- Nếu việc mở file không khả dụng, fopen() trả về NULL;
		
		. Tất cả các hàm khác expect con trỏ như là một đối số xác định file đã mở; chúng thực hiện nhiệm vụ của mình và cập nhật structure để phản ánh trạng thái file đã thay đổi;
		
		. Hàm fclose() đóng file liên quan và làm vô hiệu hóa structure (nó không được sử dụng nữa).

	- Hãy xem xét level thấp hơn.

		int fd = open(FILE_NAME, O_WRONLY | O_CREAT);

	- Như bạn thấy, hàm open() trả về một giá trị int. Thật là một bất ngờ! Làm thế nào mà một entity phức tạp như một file (hơn nữa, một file đã mở) có thể được biểu diễn chỉ bằng một int đơn giản?

	- Hãy tưởng tượng giá trị int này như là một chỉ số đến một mảng mà trong đó có nhiều các mục phức tạp hơn rất nhiều, ví dụ: các structure. Mảng này được đặt ở một nơi rất sâu bên trong kernel của hệ điều hành. Bạn không cần phải biết nơi mảng được đặt. Không chỉ vậy, bạn không nên biết nơi nó ở. Cách duy nhất để truy cập các phần tử của nó là bằng cách sử dụng các hàm chuyên dụng sử dụng các chỉ số được trả về bởi hàm open().

	- Chỉ số này được đặt tên là một file descriptor, mặc dù nó có thể xác định nhiều entity khác nhau hơn là chỉ là các file được hiểu theo cách truyền thống. Bạn biết, trong Unix mọi thứ đều là một file.

	- Một số chỉ số (file descriptors) khá dễ dự đoán, ngược lại với các con trỏ FILE *, mà hoàn toàn ngẫu nhiên, và bạn không thể dự đoán kết quả của fopen(). Ba trong số các descriptors này là:
		
		. 0 – kết nối với stdin;
		
		. 1 – kết nối với stdout;
		
		. 2 – kết nối với stderr.

	-  unistd.h header file chứa 3 symbols đại diện cho các giá trị này:

		. STDIN_FILENO;
		
		. STDOUT_FILENO;
		
		. STDERR_FILENO.

	- file được mở sau đó có khả năng có descriptors of increasing numbers (giống như các chỉ số thông thường), vì vậy khi bạn gọi open() lần đầu tiên, bạn có thể mong đợi kết quả là 3.

	- Open() trả về -1 nếu có bất kỳ lỗi nào xảy ra.


3.2.1.2
	- Có kết nối nào giữa các FILE structures và các file descriptors không?

		Yes

	- Mọi file được biểu diễn bởi một cấu trúc FILE trong thực tế đều được assigned/connected với một file descriptor tương ứng. Không có cách nào khác để sử dụng một file ngoại trừ việc sử dụng các dịch vụ của hệ điều hành, và các dịch vụ của hệ điều hành không chấp nhận bất kỳ phương pháp xác định một file đã mở nào khác ngoại trừ một file descriptor.

	- Có thể tìm thấy file descriptor được kết nối với cấu trúc FILE bằng cách sử dụng hàm fileno(), như sau:

		#include <stdio.h>

		int main(void) {
		  printf("%dn", fileno(stderr));
		  return 0;
		}

	Chương trình xuất ra 2.

	- Không thể tìm thấy cấu trúc FILE được kết nối với một descriptor, vì hệ điều hành không biết gì về cách bạn sử dụng các descriptor của nó. Thật đáng tiếc.


	- Chúng tôi đã nói cho bạn biết cách kết quả của hàm open() cho biết việc mở file không thành công, nhưng bạn có thể muốn biết thêm một chút về các lý do và nguyên nhân.

	- Một tiêu đề có tên là errno.h định nghĩa một biến có tên là errno (thật ngẫu nhiên!). Khi xảy ra bất kỳ lỗi I/O nào, biến này chứa số của lỗi. Các số lỗi được định nghĩa trong các tiêu chuẩn POSIX, tất cả đều có tên biểu tượng, và đây là một danh sách các số quan trọng nhất cùng với ý nghĩa của chúng:

		. EACCES (13) – Permission denied (bạn đã cố gắng truy cập một tài nguyên mà bạn không có quyền);
		
		. EBADF (9) – Bad file descriptor (bạn đã cố gắng sử dụng một descriptor không hợp lệ);
		
		. EEXIST (17) – File exists (bạn đã cố gắng tạo một file mới khi đã có một file cùng tên tồn tại);
		
		. ENOENT (2) – No such file or directory (bạn đã cố gắng truy cập một tài nguyên không tồn tại);
		
		. EMFILE (24) - Too many open files (xin lỗi, tất cả các descriptor khả dụng đã được sử dụng);
		
		. ENOSPC (28) - No space left on the device (ổ đĩa của bạn đầy);
		
		. EIO (5) – I/O error (đã xảy ra điều gì đó xấu và không ai biết đó là gì).

			#include <stdio.h>
			#include <unistd.h>
			#include <errno.h>
			#include <fcntl.h>

			int main(void) {
			  close(29887126);
			  printf("%dn", errno);
			  return 0;
			}

	- Chương trình outputs 9 - why?

	- Bởi vì không phải không thể có một descriptor với một số lượng đối số như thế.


3.3.1.1 Low-level I/O – opening and closing a file
	- Mở file (và đôi khi còn tạo file) chủ yếu được thực hiện bằng hàm open(), với prototype:

		. gcc, Clang, etc.				#include <fcntl.h>
		
		. CL							#include <io.h>

		int open(char *pathname, int flags);

	- Tham số đầu tiên của nó khá rõ ràng - đó là tên của file đang được mở. Đừng quên rằng tên phải đáp ứng các yêu cầu của hệ điều hành. Việc mở thực sự sẽ được hệ điều hành thực hiện và sẽ thất bại nếu hệ thống không thích cái tên bạn đã cung cấp.

	- Tham số thứ hai phức tạp và thú vị hơn nhiều. Đó là một bit mask chỉ định cách mở file. May mắn thay, bạn không cần phải nhớ ý nghĩa của mỗi bit tham gia vào hoạt động. fcntl.h header file chứa tất cả các symbolic constants có thể cần.

	- Bit mask kết quả thường được tạo thành từ các hằng số kết hợp với nhau bằng OR bitwise operator (the bar - |)

	- Note: một số flags cần phải được sử dụng duy nhất, trong khi những cái khác không cần phải hiển thị tính năng này.

	- Hãy xem một số ký hiệu thú vị nhất từ fcntl.h.


	- Biểu tượng O_RDONLY chỉ định rằng bạn chỉ đang đọc file đã mở.

	- Nó không được kết hợp với các biểu tượng O_WRONLY và O_RDWR (điều đó khá rõ ràng, phải không?)

		. gcc, Clang, etc.			#include <fcntl.h>
		. CL						#include <fcntl.h>

	- Biểu tượng O_WRONLY chỉ định rằng file đã mở sẽ chỉ được ghi (không có việc đọc nào xảy ra).

	- Nó không được kết hợp với các biểu tượng O_RDONLY và O_RDWR.

		. gcc, Clang, etc.			#include <fcntl.h>
		. CL						#include <fcntl.h>


3.3.1.2
	- Biểu tượng O_RDWR chỉ định rằng file đã mở có thể được ghi và đọc.

	- Nó không được kết hợp với các biểu tượng O_RDONLY và O_WRONLY.

		. gcc, Clang, etc.			#include <fcntl.h>
		. CL						#include <fcntl.h>

	- Thường, hàm open() sẽ thất bại nếu file được chỉ định trong đối số đầu tiên không tồn tại. Nếu bạn muốn tạo file, bạn phải sử dụng hằng số O_CREAT.

	- Nếu file đã tồn tại, nó sẽ được left intact. File mới được tạo sẽ trống rỗng (độ dài của nó sẽ là 0).

		. gcc, Clang, etc.			#include <fcntl.h>
		. CL						#include <fcntl.h>

	- Nếu bạn muốn xóa/tạo mới nội dung của file đã tồn tại trong quá trình mở, sử dụng biểu tượng O_TRUNC. Nó cũng có thể được sử dụng cùng với biểu tượng O_CREAT.

		. gcc, Clang, etc.			#include <fcntl.h>
		. CL						#include <fcntl.h>

	- Note: Nếu bạn định bắt đầu công việc của mình với một file cụ thể và bạn muốn đảm bảo rằng file là trống rỗng, bạn nên sử dụng sự kết hợp sau của các flags đã được giới thiệu trước đó:

		O_CREAT | O_WRONLY | O_TRUNC

	- Nếu bạn muốn tất cả các lần ghi của bạn vào một file luôn được thực hiện ở cuối file, bạn phải sử dụng biểu tượng O_APPEND:

		O_APPEND

		. gcc, Clang, etc.			#include <fcntl.h>
		. CL						#include <fcntl.h>

	- Okay, điều này có vẻ hơi đáng nghi. Làm thế nào mà bất kỳ thao tác ghi nào của tôi cũng không được located/targeted ngay sau thao tác ghi trước đó, tức là, ở cuối file?

	- It's possible! Hãy tưởng tượng rằng có một tiến trình khác (ngoài tiến trình của bạn) đang ghi vào cùng một file (ví dụ hoàn hảo cho tình huống như vậy là ghi vào nhật ký). O_APPEND đảm bảo rằng tất cả những bản ghi song song này không can thiệp vào nhau.

	- Nếu bạn muốn hệ điều hành tắt bất kỳ (hoặc hầu hết) the buffering (các bộ đệm) liên quan đến file, bạn có thể sử dụng biểu tượng O_DIRECT. Tuy nhiên, sẽ giảm hiệu suất đáng kể.

		. gcc, Clang, etc.			#include <fcntl.h>
		. CL						Not implemented


3.3.1.3
	- Thường, một số thao tác I/O có thể được thực hiện asynchronously. Điều đó có nghĩa gì?

	- Ví dụ, khi hàm write() trả lại control cho invoker, điều này không nhất thiết có nghĩa là thao tác đã được hoàn thành và dữ liệu đã được ghi thành công vào phương tiện lưu trữ. Có khả năng một phần tiếp theo của code của bạn và OS services đang chạy concurrently.

	- Biểu tượng O_SYNC buộc hệ điều hành hoạt động synchronously. Việc trả về từ hàm write() sẽ có nghĩa là actual completion of the operation.

		. gcc, Clang, etc.			#include <fcntl.h>
		. CL						not implemented

		O_BINARY

		O_TEXT

		. gcc, Clang, etc.			Not implemented
		. CL							#include <fcntl.h>

	- Cả hai biểu tượng này chỉ được sử dụng trong môi trường MS Windows, do một vấn đề thú vị.

	- Các hệ điều hành khác nhau khác biệt trong nhiều khía cạnh cơ bản. Điều này là hiển nhiên. Một trong những vấn đề này là câu trả lời cho câu hỏi sau: làm thế nào để đánh dấu cuối dòng trong một file văn bản?

		Câu trả lời của Unix là: thêm một ký tự duy nhất có tên là LF (line feed - code của nó bằng 10 = 0x0A = 012; đây là cùng một ký tự như \n trong C language).

		Câu trả lời của Windows là: thêm một cặp ký tự: CR LF (CR - carriage return - code của nó bằng 13 = 0x0D = 015; đây là cùng một ký tự như \r trong C language).

	- Cả hai chuẩn này đều có phần không tương thích. Khi bạn tạo một file văn bản trong Unix/Linux và mở nó trong Windows bằng Notepad, bạn thấy toàn bộ nội dung file ở một dòng dài. Khi bạn tạo một file văn bản trong Windows và mở nó trong Unix/Linux trong một trình soạn thảo không nhận biết (như vi), bạn thấy một số ký tự lạ ở cuối mỗi dòng. May mắn thay, mọi trình soạn thảo nâng cao (nâng cao hơn Notepad và vi) đều có thể chuyển đổi file thành dạng mong muốn.

	- Việc sử dụng hai ký tự liên tiếp để đánh dấu cuối dòng rất rắc rối. Ví dụ, khi bạn sử dụng printf() như sau:

		printf("\n");

	và bạn làm điều này trong một chương trình chạy trong Windows, thời gian chạy (một set of libraries cần thiết để chạy chương trình) phải chuyển đổi một \n duy nhất thành \r\n. Khi bạn gọi fgets() để đọc một dòng từ một file, thời gian chạy chuyển đổi \r\n thành một \n duy nhất.

	- Quá trình translation hầu như là trong suốt.

	- Khi bạn mở một file bằng hàm open() trong Windows, bạn phải xác định trước cách bạn muốn treat the file. Nói cách khác, bạn nên quyết định liệu bạn muốn the runtime thực hiện translation hay không.

		. O_BINARY có nghĩa là: "I don’t want the translation, I want my data left intact."
		
		. O_TEXT có nghĩa là: "Oh yes do it"; 
			thú vị là, chế độ hoạt động này là mặc định, vì vậy bạn không thể tránh khỏi việc sử dụng O_BINARY nếu bạn muốn file của bạn được xử lý như nguyên bản.

	- Cả hai biểu tượng này không thể được sử dụng cùng nhau (rõ ràng).

	- Nhớ rằng:
	
		. Các biểu tượng này không được biết đến trong các compilers tương thích POSIX.
	
		. Một trong hai biểu tượng này may be necessary để biên dịch và chạy code của bạn trong Windows.


3.3.1.4
	- Đóng file dường như đơn giản hơn so với việc mở nó. Nó được thực hiện bằng một hàm có tên là close():

		. gcc, Clang, etc.			#include <unistd.h>

		. CL 						#include <io.h>

		int close (int fd);

	- Hàm này expects the file descriptor của một file đã được mở trước đó. Ngược lại với quan điểm phổ biến trên, hàm có thể fail.

	- Một số người nói rằng close() là dư thừa, vì tất cả các file đã mở sẽ bị đóng một cách bắt buộc bởi hệ điều hành khi chương trình của bạn kết thúc. Khi hệ điều hành đóng file của bạn thay vì bạn tự đóng, bạn không thể kiểm soát nó. Ví dụ, bạn không thể kiểm tra xem tất cả các lệnh đóng có thành công hay không, vì vậy bạn không thể phản ứng với bất kỳ vấn đề nào và bạn không thể sửa chữa chúng.

	- Khi nàolệnh gọi hàm close() có thể thất bại?

	- Hãy tưởng tượng kịch bản sau:

		. Bạn mở một file nằm trên 1 removable media, chẳng hạn như một USB;
		
		. Bạn ghi một số dữ liệu vào file (việc ghi thực tế có thể được thực hiện một cách asynchronously, vì vậy việc returning từ hàm write() không có nghĩa là dữ liệu đã được đặt trên thiết bị lưu trữ có thể tháo rời của bạn);
		
		. Bạn tháo thiết bị mà không có cảnh báo; đã quá muộn để hàm write() thông báo về một lỗi;
		
		. Bạn gọi hàm close() và nó thất bại vì hiện không thể flush the buffers (xả các bộ đệm) - bạn có thể ngăn chặn lỗi và xử lý nó (ví dụ, thông báo cho người dùng biết rằng dữ liệu có thể bị mất); bạn không thể làm điều này nếu bạn giao phó việc đóng cửa file cho hệ điều hành.

	- Nên sử dụng hàm close()!

	- Bạn có thể hỏi liệu việc thử mở một file cụ thể có phải là cách duy nhất để biết liệu nó có thể mở được hay không (hành động này giống như một cuộc tấn công theo kiểu "reconnaissance by fire" - một chiến thuật chiến tranh).

	- Không, có một cách khác, tuy nhiên, nó có thể hơi misleading.

	- Bạn có thể sử dụng một hàm có tên là access() trước khi thực sự mở file:
		
		. gcc, Clang, etc.				Not implemented
		
		. CL							#include <io.h>

		
		int access (char *pathname, int mode);

	- Tham số đầu tiên đóng vai trò giống như open().

	- Tham số thứ hai có thể là sự kết hợp của bất kỳ trong các ký hiệu sau được định nghĩa trong unistd.h (các ký hiệu này phải được OR lại để tạo thành một specification hoàn chỉnh):

		. F_OK: file có tồn tại không?
	
		. R_OK: có thể đọc từ file không?
	
		. W_OK: có thể ghi vào file không?
	
		. X_OK: có thể thực thi file không?

	- Note: CL sử dụng io.h thay vì unistd.h.

	- Note: các ký hiệu force hàm phải kiểm tra xem quy trình của bạn có được phép thực hiện các thao tác cụ thể hay không - đừng quên rằng bạn may have limited rights để thao tác với một file cụ thể. Bất kỳ file nào cũng có thể được truy cập hoàn toàn bởi một người dùng khác nhưng không phải là bạn.

	- Hàm access() trả về 0 khi thành công (tất cả các yêu cầu của bạn đã được đáp ứng), hoặc -1 trong trường hợp ngược lại (bất kỳ yêu cầu nào của bạn chưa được đáp ứng). Trong trường hợp sau, biến errno được thiết lập thành một giá trị phù hợp.

	- Ví dụ, nếu bạn muốn kiểm tra xem bạn có thể mở một file tin có sẵn có tên là file.txt và ghi vào nó và đọc từ nó, bạn có thể sử dụng đoạn code sau:

	- Tại sao việc sử dụng hàm này có thể misleading?

	- Có khả năng một trong những thuộc tính được kiểm tra đã thay đổi giữa các lời gọi access() và open(). Có nhiều quy trình khác nhau đang chạy trong hệ thống. Một số trong số chúng có thể hoạt động trên file của bạn cùng với bạn và sửa đổi nội dung hoặc quyền của nó.


3.3.1.5
	- Chúng tôi nên mention một điều: hàm open() có thêm 1 variant được sử dụng khi hàm dự kiến có khả năng tạo 1 file mới.

		. gcc, Clang, etc.				#include <unistd.h>
		. CL							#include <io.h>

		int open (char *pathname, int flags, , mode_t mode);

	- Tham số thứ ba chỉ định quyền của file mới được tạo và kết nối chặt chẽ với các quy ước Unix. Nói chung, một giá trị là 0666 (lưu ý - nó được viết ở octal (hệ cơ số tám)) đảm bảo rằng file mới có thể đọc và ghi được bởi bạn. Nếu bạn muốn biết thêm chi tiết, hãy xem Wikipedia.

	- Notation of traditional Unix permissions, link below:

		https://en.wikipedia.org/wiki/File-system_permissions#Notation_of_traditional_Unix_permissions

	- Tham số này không có ý nghĩa trong MS Windows và bị silently ignored.


3.4.1.1 Low-level I/O – reading from and writing to a file
	- Việc đọc từ một file đã mở được thực hiện bằng hàm read(). Hàm này cần 3 tham số:

		ssize_t read(int fd, void *buf, size_t count);
		
		. Một descriptor của file đang được đọc;
		
		. Một con trỏ đến vị trí bộ nhớ mà dữ liệu đọc vào phải được chuyển đến;
		
		. Số byte cần đọc; 

			Note: đó là trách nhiệm của bạn để đảm bảo rằng bộ đệm được chỉ định bởi tham số thứ hai là đủ lớn để chứa dữ liệu; nếu bộ đệm của bạn quá ngắn, dữ liệu có thể ghi đè lên một số khu vực bộ nhớ đã được chiếm đó, điều này sẽ gây nguy hiểm cho chương trình của bạn.

	- Hàm trả về số byte đã đọc thành công - note: kết quả có thể ít hơn giá trị count - đó không phải là một lỗi. Nếu nó bằng 0, bạn đã đến cuối file - không có thêm byte nào để đọc từ file.

	- Khi kết quả bằng -1, quá trình đọc đã không thành công - biến errno sẽ cho bạn biết thêm về điều đó.

	- Thường thì, tham số count chỉ có thể chấp nhận giá trị trong một phạm vi giới hạn. Hiển nhiên là nó không được nhỏ hơn 0. Nhưng nó có thể bằng 0 - điều này không hiển nhiên. Biến thể này của việc gọi có thể được sử dụng để phát hiện một số lỗi mà không thực hiện bất kỳ actual reads nào. Count không thể arbitrarily large - nó phải nhỏ hơn giá trị được biểu diễn bằng một biểu tượng có tên là SSIZE_MAX (biểu tượng này xuất phát từ file header limits.h và bằng giá trị tối đa của signed long type, nhưng ít máy tính được trang bị với một RAM lớn như vậy).

	- Đừng quên rằng hàm không thực hiện conversions hoặc translations nào cả. Dữ liệu từ file được triển khai trong bộ nhớ theo kiểu byte by byte, as is. Đừng mong đợi hàm sẽ biến một series ký tự thành giá trị int một cách kỳ diệu.

	- Hàm write() giống như twin của hàm read(), hoặc chính xác hơn, giống như bản phản ánh của nó trong gương. Vâng, đây chắc chắn là một phương pháp tốt.

	- Hàm write() cần ba tham số:

		ssize_t write(int fd, void *buf, size_t count);
	
		
		. Một descriptor của file đang được ghi;
		
		. Một con trỏ đến vị trí bộ nhớ nơi dữ liệu của bạn đang chờ được ghi xuống phương tiện vật lý;
		
		. Số byte cần được ghi.

	- Hàm trả về số byte đã được ghi thành công
		note, một kết quả dương có thể ít hơn giá trị count khi không có đủ không gian trên thiết bị (điều này cũng có thể nghĩa là đã vượt quá hạn mức đĩa của bạn).

	- Khi kết quả bằng -1, việc ghi đã không thành công - biến errno sẽ cho bạn biết thêm về điều đó.

	- Tham số count tuân theo các ràng buộc giống như twin của nó từ hàm read().

	- Hàm không thực hiện conversions hoặc translations nào cả. Dữ liệu từ bộ nhớ được gửi xuống đĩa byte by byte, nguyên vẹn.


3.4.1.2
	- Giờ chúng tôi sẽ show cho bạn 2 chtrinh đơn giản sử dụng cả 2 hàm trước đó để store và restore a portion of data.

	- Nhìn code:

		#include <stdio.h>

		#include <stdlib.h>

		#include <fcntl.h>

		#include <time.h>

		#ifndef _MSC_VER

		#include <unistd.h>

		#endif

		#define N 10

		int
		main (void)
		{
		  int arr[N];
		  int i;

		  srand (time (NULL));
		  for (i = 0; i < N; i++)
		    {
		      arr[i] = rand () % 10 + 1;
		      printf ("%d ", arr[i]);
		    }
		  printf ("\n");
		  int out = open ("arr.dat", O_CREAT | O_TRUNC | O_WRONLY, 0666);
		  if (out > 0)
		    {
		      int n = write (out, arr, sizeof (arr));
		      printf ("%d bytes written\n", n);
		      close (out);
		    }
		  return 0;
		}

	- Chú ý đến các phần sau trong source code:
		
		. Line 9: Vì compiler MS CL không hiểu về file header unistd.h, chúng tôi đã thêm hướng dẫn #ifndef, kiểm tra xem biểu tượng _MSC_VER có được định nghĩa hay không; sự xuất hiện của biểu tượng này cho biết code đang được biên dịch bởi CL, vì vậy chúng tôi phải loại bỏ một #include.
		
		. Line 23: Vì chúng tôi sẽ tạo ra một số dữ liệu ngẫu nhiên (pseudo), chúng tôi sử dụng hàm srand() để khởi tạo seed của bộ tạo số ngẫu nhiên; seed mới sẽ được lấy từ kết quả của hàm time(), trả về đồng hồ hệ thống hiện tại theo định dạng Epoch (đây là số giây đã trôi qua từ 1 tháng 1 năm 1970, 00:00:00 giờ thế giới); giá trị này đủ ngẫu nhiên để sử dụng như một seed;
		
		. Line 26: Chúng tôi tạo ra N số ints ngẫu nhiên trong khoảng từ 1 đến 10: hàm rand() trả về một số trong khoảng từ 0 đến MAX_INT và chúng tôi sử dụng toán tử modulo để giảm khoảng và di chuyển nó về phía bên phải một lần (theo số . 
		Line source code);
		
		. Line 24: Chúng tôi điền dữ liệu ngẫu nhiên (gần như) vào mảng và hiển thị các giá trị;
		
		. Line 30: Chúng tôi tạo một file mới hoặc cắt giảm file hiện tại và chuẩn bị nó để writing;
		
		. Line 33: Chúng tôi ghi toàn bộ mảng vào file;
		
		. Line 35: Chúng tôi đóng file lại.

	- Note: các thông báo chẩn đoán gần như không có - điều này chấp nhận được trong một đoạn code như vậy, nhưng không chấp nhận được trong một code bạn muốn bán hoặc chạy trong môi trường thực tế.

	- Okay, giờ chúng ta chuyển sang chương trình thứ hai.


3.4.1.3
	- Nhìn vào code:

		#include <stdio.h>

		#include <fcntl.h>

		#ifndef _MSC_VER

		#include <unistd.h>

		#endif

		#define N 10

		int
		main (void)
		{
		  int arr[N];

		  int in = open ("arr.dat", O_RDONLY);
		  if (in > 0)
		    {
		      int n = read (in, arr, sizeof (arr));
		      printf ("%d bytes read in\n", n);
		      close (in);
		    }
		  int i;
		  for (i = 0; i < N; i++)
		    printf ("%d ", arr[i]);
		  return 0;
		}
	

		. line 18: Chúng tôi mở cùng một file như đã được ghi bởi chương trình trước đó nhưng chuẩn bị nó để đọc;
	
		. line 21: Chúng tôi đọc nội dung của file vào một int array;
	
		. line 23: Chúng tôi đóng file;
	
		. line 26: Chúng tôi output mảng.

	- Chạy chương trình theo thứ tự này nên output chính xác N số nguyên.

	- Hãy thử nghiệm code. Viết thêm dữ liệu hơn sẽ được đọc, đọc nhiều hơn đã được viết, và phân tích kết quả.


3.4.1.4
	- Đến nay, chúng tôi đã xử lý các file như một magnetic tape - cuộn băng từ. Chúng tôi đã ghi nó từ đầu đến cuối và đọc nó theo cùng một cách.

	- Liệu có thể xử lý file theo cách ngẫu nhiên không? Ví dụ, có thể skip to địa điểm cụ thể bên trong một file và thực hiện một thao tác ghi hoặc đọc ở đó không?

	- Yes, hoàn toàn có thể. Một sự skip như vậy được gọi là reposition (sự tái đặt vị trí), và dựa trên khái niệm của file pointers (đừng để nhầm lẫn bởi thuật ngữ này - nó không có in common with actual pointers).

	- Con trỏ file là một khái niệm trừu tượng - đó là nơi mà thao tác read/write đã kết thúc và thao tác read/write tiếp theo sẽ được kích hoạt. Đó là một khoảng trống tưởng tượng giữa phần của file đã được xử lý và phần chưa được xử lý. Vị trí của con trỏ file được đo bằng byte, đếm từ đầu của file - file đã được mở có con trỏ file của nó ở vị trí 0.

	- Có một hàm cho phép bạn di chuyển con trỏ file đến một vị trí (hầu như) tùy ý. Dưới đây là prototype:

		off_t lseek (int fd, off_t offset, int whence);

		. off_t là một kiểu giống như kiểu int nhưng đủ lớn để biểu diễn kích thước của file lớn nhất mà hệ điều hành cụ thể có thể chấp nhận;

		. fd là một file descriptor của file mà bạn muốn di chuyển;
	
		. offset là độ dài của bước nhảy bạn sẽ thực hiện (chi tiết hơn sẽ được nói sau)
	
		. whence cho hệ điều hành biết nơi bước nhảy của bạn sẽ bắt đầu. Các giá trị có thể có:

			. SEEK_SET - di chuyển con trỏ file đến vị trí offset (sự di chuyển là tuyệt đối lúc này)
		
			. SEEK_CUR - di chuyển con trỏ file đến vị trí được tính như new_location = current_location + offset (sự di chuyển là tương đối với vị trí hiện tại; Note: offset có thể là âm ở đây)
		
			. SEEK_END - di chuyển con trỏ file đến offset byte từ cuối file.

	- Kết quả của hàm là giá trị của con trỏ file cuối cùng (được đặt sau lệnh seek) hoặc -1 nếu seek không thành công (giá trị errno sẽ cung cấp thêm thông tin).

	- Có vẻ thú vị, phải không? Chắc chắn rồi! Bây giờ chúng tôi sẽ chỉ cho bạn một ví dụ hấp dẫn.


3.4.1.5
	- Có thể di chuyển con trỏ file đến trước đầu của nó không? Không, không thể. Điều này sẽ gây ra lỗi.

	- Có thể di chuyển con trỏ file đến sau cuối của nó không? Có!
	Xem code:

		#include <stdio.h>

		#include <unistd.h>

		#include <fcntl.h>

		int
		main (void)
		{
		  int fd = open ("newfile", O_TRUNC | O_CREAT | O_WRONLY, 0666);
		  if (fd > 0)
		    {
		      long pos = lseek (fd, 9, SEEK_SET);
		      char c = 1;
		      int wrtn = write (fd, &c, 1);
		      close (fd);
		      printf ("position: %ld, written: %d\n", pos, wrtn);
		      fd = open ("newfile", O_RDONLY);
		      if (fd > 0)
			{
			  while (read (fd, &c, 1) > 0)
			    printf ("%d ", c);
			  printf ("\n");
			  close (fd);
			}
		    }
		  return 0;
		}

	
		. line 10: chúng ta tạo một file mới (con trỏ file được đặt lại ở vị trí 0 sau điều này)
		
		. line 13: chúng ta di chuyển con trỏ file đến vị trí 9;
		
		. line 15: chúng ta viết một byte tại vị trí mới;
		
		. line 18: chúng ta mở lại file và in nội dung của nó: chương trình output:

			0 0 0 0 0 0 0 0 0 1

	- Kết luận: Con trỏ file có thể được di chuyển đến sau cuối file và nếu nó được theo sau bởi bất kỳ non-empty write nào, file sẽ được mở rộng và khoảng trắng sẽ được điền bằng các số không.

	- Cùng một ví dụ với line 15 được chú thích sẽ không thực hiện công việc, và file sẽ vẫn trống.

	- Còn một hàm khác cũng có thể hữu ích khi bạn muốn sử dụng một file descriptor để viết dữ liệu được định dạng vào một file mở. Dưới đây là prototype:

		int dprintf (int fd, char *format, ...);

	- Hàm này rất giống với fprintf() và làm cùng một điều như fprintf() nhưng sử dụng file descriptor thay vì con trỏ FILE *.

	- Xin lỗi nhưng there's no dscanf() function.


3.4.1.6
	- Tóm tắt những điều chúng ta đã học thông qua một chương trình có mục tiêu là một phiên bản đơn giản của tiện ích cp (Unix) / copy (Windows). Chương trình này có khả năng sao chép nội dung của một file đến một file khác.

	- Xem code:

		#include <fcntl.h>
		#include <stdio.h>
		#include <stdlib.h>
		#include <string.h>
		#include <errno.h>
		#include <stdarg.h>

		#ifndef _MSC_VER
		#include <unistd.h>
		#define  O_BINARY	0
		#endif

		int fdin = -1, fdout = -1;

		void
		closefds (void)
		{
		  if (fdin != -1)
		    close (fdin);
		  if (fdout != -1)
		    close (fdout);
		}

		void
		error (int ret, char *fmt, ...)
		{
		  char buf[512];
		  va_list vlist;

		  va_start (vlist, fmt);
		  vsprintf (buf, fmt, vlist);
		  va_end (vlist);
		  fprintf (stderr, "ERROR: %s\n       %s\n", buf, strerror (errno));
		  exit (ret);
		}

		int
		main (int argc, char *argv[])
		{
		  char buffer[4096];

		  if (argc != 3)
		    {
		      fprintf (stderr, "Usage: %s source_file target_file\n", argv[0]);
		      return 1;
		    }
		  atexit (closefds);
		  fdin = open (argv[1], O_RDONLY | O_BINARY);
		  if (fdin < 0)
		    error (2, "Cannot open source file: %s", argv[1]);
		  fdout = open (argv[2], O_CREAT | O_TRUNC | O_WRONLY | O_BINARY, 0666);
		  if (fdout < 0)
		    error (3, "Cannot open target file: %s", argv[2]);
		  int rres;
		  while ((rres = read (fdin, buffer, sizeof (buffer))) > 0)
		    {
		      int wres = write (fdout, buffer, rres);
		      if (wres != rres)
			error (4, "Error when writing %s", argv[2]);
		    }
		  if (rres < 0)
		    error (5, "Error while reading %s", argv[1]);
		  if (close (fdin) < 0)
		    error (6, "Error while closing %s", argv[1]);
		  fdin = -1;
		  if (close (fdout) < 0)
		    error (7, "Error while closing %s", argv[2]);
		  fdout = -1;
		  return 0;
		}


		. line 8 to 11: Khi compiler của chúng ta không phải là CL, chúng ta include "unistd.h" và định nghĩa biểu tượng O_BINARY giả mạo - với giá trị 0, nó không có ý nghĩa gì đối với hàm open();
	
		. line 13: Chúng ta đã quyết định khai báo hai biến cho hai file descriptors khác nhau ở ngoài bất kỳ hàm nào - điều này làm cho biến trở nên toàn cục (nó sẽ giúp đơn giản hóa một số hành động và giao diện của hàm);
	
		. line 15 to 22: Hàm được đăng ký bởi atexit() và được gọi khi chương trình kết thúc - mục đích của nó là đóng mọi descriptors trước đó mà chưa được đóng;
	
		. line 24 to 35: Hàm được gọi khi xảy ra bất kỳ lỗi không thể phục hồi nào; Note: tham số cuối cùng là va_list - chúng tôi sẽ sử dụng nó giống như printf(); hàm in ra thông báo lỗi và kết thúc chương trình với code trả về được chỉ định trong tham số đầu tiên; chúng tôi sử dụng hàm strerror() để chuyển đổi số lỗi được lưu trữ trong errno thành một thông báo có thể đọc được;
	
		. line 40: Đây là bộ đệm chúng ta sử dụng để tăng tốc quá trình sao chép;
	
		. line 42 to 46: Chúng ta kiểm tra cách mà code của chúng ta đã được kích hoạt và in một thông báo nếu chúng ta không tìm thấy một số lượng tham số phù hợp;
	
		. line 48 to 53: open/create cả hai file (source and target) và phản ứng với các lỗi có thể xảy ra;
	
		. line 55 to 60: actual copying;
	
		. line 51 to 70: final cleaning và smooth return to OS.

	- Buffer size có quan trọng không? Tăng buffer size có thể làm tăng tốc độ sao chép không?

	Có thể. Bộ đệm lớn hơn có nghĩa là ít lần gọi hàm đọc/viết hơn tại level hệ điều hành.

	- Hãy kiểm tra nó bằng cách sử dụng một file rất lớn, ít nhất là 1GB.

	- Kết quả như thế nào?


3.5.1.1 Low-level I/O – retrieving file metadata
	- Prefix "meta-" có vẻ hơi mơ hồ. Tóm lại, chúng ta có thể nói rằng "metasomething" là một cái gì đó liên quan đến original something. Ví dụ, "metamathematics" là một dạng toán học mô tả chính toán học. Khi bạn hỏi bạn bè xem cô ấy có muốn đi xem kịch với bạn và cô ấy hỏi về bộ phim bạn sẽ xem, chúng ta có thể nói rằng cô ấy đã đặt cho bạn một câu hỏi về "meta."

	- Metadata là data about other data.

	- Nếu có một file chứa toàn bộ văn bản của vở kịch Hamlet của William Shakespeare, data của nó là chính cái văn bản đó. Metadata của nó có thể là:

		. Kích thước của file được đo bằng byte;
		. Ngày và giờ tạo file;
		. Quyền của file.

	- Note: một số metadata có thể phụ thuộc vào hệ điều hành, ví dụ, kích thước của một file văn bản có thể phụ thuộc vào cách ký tự xuống dòng được encoded (và việc truyền file như vậy có thể sửa đổi nội dung của nó).

	- Trong phần này, chúng tôi sẽ giới thiệu về một hàm được gọi là stat() - được thiết kế để truy xuất metadata của một file. Chúng ta có thể nói rằng đây là một trong những hàm "Unix-iest" trong C programming language - nó được thiết kế cho Unix và có thể không được triển khai đầy đủ trong các hệ điều hành khác, nên chúng tôi quyết định trước tiên giới thiệu về phiên bản gốc và sau đó là cách nó được triển khai trong môi trường biên dịch MS CL.

	- Prototype của hàm:

		#include <sys>
		#include <sys>
		#include <unistd.h>

		int stat (char *pathname, struct stat *buf);

	- Vai trò của tham số đầu tiên: tên của một file mà metadata sẽ được truy xuất từ đó. 
		Note: do một số giả định của Unix, một thư mục là một trường hợp đặc biệt của một file, vì vậy cả hai thực thể này đều có thể được sử dụng as input. Yêu cầu quan trọng: thực thể phải tồn tại khi gọi hàm stat.

	- Kết quả của hàm cũng rõ ràng - nó trả về 0 khi thành công và -1 khi có lỗi. Trong trường hợp sau, biến errno sẽ chứa một giá trị mô tả cho bạn bản chất của sự cố.

	- Điều thú vị nhất là tham số thứ hai - đó là một con trỏ đến một cấu trúc phải được cấp phát trong process address space của bạn (nói cách khác, nhiệm vụ của bạn là đảm bảo rằng con trỏ trỏ đến một khu vực bộ nhớ phù hợp).

	- Cấu trúc này bao gồm một số trường đại diện cho các metadata khác nhau của file. Note: tiêu chuẩn sẽ đảm bảo cấu trúc chứa tất cả các trường, nhưng không đảm bảo thứ tự của chúng (it may change from implementation to implementation). May mắn thay, điều này không làm thay đổi gì đối với chúng ta.

	- Chúng tôi sẽ hiển thị tất cả các trường theo thứ tự thông thường với mô tả ngắn nhưng có ý nghĩa.


3.5.1.2
		dev_t st_dev;

	- Trường st_dev (lưu ý tiền tố st_ - đến từ việc tất cả các trường này thuộc hàm stat) là một identifier của thiết bị lưu trữ file vật lý. Các hệ điều hành tương thích với Unix biểu thị tất cả các thiết bị kết nối dưới dạng cây con của cùng một cây thư mục, vì vậy không có cách đơn giản nào để đoán xem thiết bị nào chứa một file và/hoặc thư mục cụ thể. Việc sử dụng trường này và so sánh giá trị của nó với st_dev của một file/thư mục khác có thể cho bạn biết liệu những file này có thuộc cùng một thiết bị hay không.

	- Trường này có thể được sử dụng cho mục đích tương tự trong các hệ điều hành không phải là Unix.

	- dev_t type thường là một synonym của bất kỳ (not very long) int type.

		ino_t st_ino;

	- Trường st_ino có mối liên quan chặt chẽ với khái niệm inode của Unix. Đây là phần tử của hệ thống file và là carrier của thực thể được dành cho việc đại diện cho một file/directory và mô tả vị trí đĩa chiếm dụng trên media của file vật lý. Trong số đó, inode có thể lưu trữ nhiều thông tin về metadata của file. Tất cả các inode được xác định bằng unique numbers (trên thiết bị, không phải trên toàn bộ hệ điều hành).

	- st_ino lưu trữ số lượng inode được gán cho file mà metadata của nó đang được truy xuất.

	- Kiểu ino_t thường là một synonym của một int type đủ dài để đại diện cho tất cả các số inode có sẵn trong một hệ thống file cụ thể.

		mode_t st_mode;

	- Trường st_mode là một trường bit - có nghĩa là nó không chứa một giá trị đơn (e.g. an int) mà là một bộ bit với ý nghĩa cụ thể được gán cho mỗi bit đó.

	- Trường này rất "Unix" về mặt bản chất và chủ yếu được sử dụng để lưu trữ quyền của file. May mắn thay, chúng ta không cần nhớ ý nghĩa của tất cả các bit, vì có một file header chứa tất cả các ký hiệu đại diện cho tất cả các interesting bit. Công thức chung để sử dụng các ký hiệu này là đặt chúng như một đối số của toán tử bitwise and (&) cùng với trường st_mode và kiểm tra kết quả - nếu nó khác không, file có feature; nếu nó bằng không, nó không có.

	- Những ký hiệu phổ biến nhất:
		
		. S_IFREG - file là một file thông thường
		
		. S_IFDIR - file là một thư mục
		
		. S_IRUSR - owner có quyền đọc
		
		. S_IWUSR - owner có quyền ghi
		
		. S_IXUSR - owner có quyền thực thi
		
		. S_IRGRP - group có quyền đọc
		
		. S_IWGRP - group có quyền ghi
		
		. S_IXGRP - group có quyền thực thi
		
		. S_IROTH - others có quyền đọc
		
		. S_IWOTH - others có quyền ghi
		
		. S_IXOTH - others có quyền thực thi

	- Nếu bạn là owner của một file cụ thể và muốn kiểm tra xem bạn có thể sửa đổi nó hay không, bạn có thể làm như sau:

		if (buf.st_mode & S_IWUSR)
		  {


		    puts ("OK, let's do it!");


		  }


3.5.1.3
		nlink_t st_nlink;

	- Trường st_nlink là sự phản ánh của một khái niệm Unix khác được gọi là hard link (liên kết cứng). Đây là một kết nối vô hình (ở level user) giữa một file thực tế và các tên phụ của nó. Điều này có nghĩa là một file (hoặc một thư mục) có thể có nhiều hơn một tên. Do đó, một và cùng một file có thể hiển thị trong nhiều thư mục.

	- Việc xóa actual file sẽ không làm cho dữ liệu biến mất miễn là có số lượng linked names nhiều hơn 0.

	- st_nlink lưu trữ số lượng của tất cả linked (secondary) names. Note: giả định rằng file gốc được liên kết chặt chẽ với chính nó, vì vậy bất kỳ file nào không có liên kết bổ sung chặt chẽ đều hiển thị st_nlink bằng 1.

	- Có hai cách triển khai liên kết:
		
		. Ở inodes level (những liên kết này được gọi là hard - những liên kết này chỉ có thể được đếm bởi trường st_nlink)
		
		. Ở filesystem level (những liên kết này được gọi là soft).

	- Kiểu nlink_t thường là một synonym của kiểu int.

		uid_t st_uid;

	- Trong Unix và các hệ điều hành tương thích, mỗi file đều có its owner (user được biết đến bởi hệ điều hành) và tất cả owner đều có ID của họ. Trường st_uid chứa ID của người dùng sở hữu file.

	- Kiểu uid_t thường là một synonym của kiểu int (not so long).


		gid_t st_gid;

	- Trong Unix và các hệ điều hành tương thích, mỗi file không chỉ thuộc về một người dùng, mà còn thuộc về một nhóm người dùng. Tất cả các thành viên của nhóm chia sẻ cùng một quyền với file, nhưng quyền của họ khác biệt so với quyền của chủ sở hữu (thường thì yếu hơn).

	- Trường st_gid chứa ID của một nhóm chia sẻ file.

	- Kiểu gid_t thường là một synonym của kiểu int (not so long).

		dev_t st_rdev;

	- Trong Unix và các hệ điều hành tương thích, một file có thể đại diện cho một thiết bị vật lý, không có chung cái gì với một file thông thường; ví dụ tốt nhất là một sound card. Viết vào một file như vậy có thể làm cho thẻ phát nhạc.

	- Một file đại diện cho một thiết bị được gọi là special file trong Unix, và trường st_rdev chứa một ID duy nhất cho thiết bị.

	- Note: trường này khác với trường st_dev được mô tả trước đó.

		off_t st_size;

	- Trường st_size lưu trữ kích thước của file, được đo bằng byte. Lưu ý rằng trong môi trường nhiều người dùng và nhiều tiến trình, giá trị này là tương đối instantaneous - nó có thể thay đổi in the background.

	- Kiểu off_t là một kiểu mà bạn đã biết - hàm lseek() sử dụng cùng một type để return kết quả của nó.


3.5.1.4
		blksize_t st_blksize;

	- Phương tiện được sử dụng để lưu trữ nội dung file không được allocated theo cách tuyến tính - nó luôn được allocated và deallocated using 1 quantum of allocation (lượng cấp phát). Thông thường, một file chiếm không gian lớn hơn đáng kể kích thước của nó. The quantum được gọi là một block và kích thước của nó phụ thuộc vào kích thước của toàn bộ bộ nhớ lưu trữ (nói chung, thiết bị lớn hơn cung cấp các block lớn hơn).

	- Trường st_blksize chứa kích thước (theo byte) của block đang được sử dụng trên thiết bị lưu trữ file.

	- Kiểu blksize_t là một kiểu giống như int, đủ dài để biểu diễn kích thước block.

		blkcnt_t st_blocks;
	
	- Trường st_blocks chứa số block hiện đã được allocated cho file.

	- Note: st_blocks * st_blksize >= st_size

	- Kiểu blkcnt_t là một kiểu giống như int, đủ dài để biểu diễn tổng số block.

		struct timespec st_atim;
		struct timespec st_mtim;
		struct timespec st_ctim;
		
	- 3 trường st_atim, st_mtim và st_ctim đại diện cho 3 thời điểm quan trọng trong cuộc đời của mỗi file. Tất cả chúng được lưu trữ dưới dạng giá trị của struct timespec. Chúng ta không cần biết internal structure của nó (đừng nhầm lẫn bởi các ý nghĩa khác nhau của từ "structure") vì nói chung thì chúng ta không làm việc trực tiếp với giá trị đó (ví dụ: có một hàm được đặt tên là ctime() chuyển đổi nó thành dạng có thể đọc được bởi con người).

		. st_atim (a như trong access) lưu trữ thời gian truy cập cuối cùng vào file (e.g. thực thi file nếu nó chứa nội dung có thể thực thi hoặc đọc nội dung của file)

		. st_mtim (m như trong modify) lưu trữ thời gian thay đổi cuối cùng của file (e.g. viết vào file); Note: một sự thay đổi của st_mtim thường cũng ngay lập tức gây ra một sự thay đổi của st_atim;

		. st_ctim (c như trong create) lưu trữ thời gian tạo file, nhưng đừng quên rằng thuật ngữ creation được hiểu rộng hơn so với thông thường, e.g. việc thay đổi sở hữu của file hoặc sửa đổi quyền có thể được coi là một sự tái tạo của file và gây ra sự thay đổi của st_ctim.


3.5.1.5
	- Hãy xem qua ví dụ đơn giản này, code sử dụng hàm stat():

		#include <stdio.h>
		#include <errno.h>
		#include <sys/types.h>
		#include <sys/stat.h>
		#include <unistd.h>
		#include <time.h>

		int
		file (char *name)
		{
		  printf ("%s:\n", name);
		  struct stat buf;
		  if (stat (name, &buf) < 0)
		    {
		      printf ("\tCannot stat it -- errno=%d\n", errno);
		      return -1;
		    }
		  printf ("\tDevice ID:\t%ld\n", buf.st_dev);
		  printf ("\tInode no:\t%ld\n", buf.st_ino);
		  printf ("\tFile mode:\t%o\n", buf.st_mode);
		  if (buf.st_mode & S_IFREG)
		    printf ("\t\tordinary file\n");
		  if (buf.st_mode & S_IFDIR)
		    printf ("\t\tdirectory\n");
		  if (buf.st_mode & S_IRUSR)
		    printf ("\t\treadable for owner\n");
		  if (buf.st_mode & S_IWUSR)
		    printf ("\t\twritable for owner\n");
		  if (buf.st_mode & S_IXUSR)
		    printf ("\t\texecutable for owner\n");
		  if (buf.st_mode & S_IRGRP)
		    printf ("\t\treadable for group\n");
		  if (buf.st_mode & S_IWGRP)
		    printf ("\t\twritable for group\n");
		  if (buf.st_mode & S_IXGRP)
		    printf ("\t\texecutable for group\n");
		  if (buf.st_mode & S_IROTH)
		    printf ("\t\treadable for others\n");
		  if (buf.st_mode & S_IWOTH)
		    printf ("\t\twritable for others\n");
		  if (buf.st_mode & S_IXOTH)
		    printf ("\t\texecutable for others\n");
		  printf ("\tHard links:\t%ld\n", buf.st_nlink);
		  printf ("\tOwner UID:\t%d\n", buf.st_uid);
		  printf ("\tGroup GID:\t%d\n", buf.st_gid);
		  printf ("\tSpecial ID:\t%ld\n", buf.st_rdev);
		  printf ("\tFile size:\t%ld\n", buf.st_size);
		  printf ("\tBlk size:\t%ld\n", buf.st_blksize);
		  printf ("\tBlk count:\t%ld\n", buf.st_blocks);
		  printf ("\tAccess time:\t%s", ctime (&buf.st_atime));
		  printf ("\tCreation time:\t%s", ctime (&buf.st_ctime));
		  printf ("\tModifictn time:\t%s", ctime (&buf.st_mtime));
		  return 0;
		}

		int
		main (int argc, char *argv[])
		{
		  if (argc < 2)
		    {
		      fprintf (stderr, "usage: %s filename...\n", argv[0]);
		      return 1;
		    }
		  int i;
		  for (i = 1; i < argc; i++)
		    file (argv[i]);
		  return 0;
		}

	
	- Ghi chú đầu tiên ở đây là ví dụ này chỉ có thể compiled thành công trên hệ điều hành Unix/Linux. Đừng thử biên dịch bằng CL hoặc bất kỳ trình biên dịch Windows nào khác, ngay cả khi nó đã được chuyển từ Unix/Linux.

	- Tất nhiên, bạn có thể thử, nhưng chúng tôi nghĩ bạn sẽ không thành công lắm. Hãy cho chúng tôi biết kết quả của bạn. (nào rảnh làm)

	- Chúng tôi sẽ sớm hướng dẫn bạn cách thực hiện chương trình này trên Windows. Be patient!

		. Line 8: chúng tôi đã khai báo một wrapper function ở đây; hàm nhận một đối số (tên của file) và cố gắng in tất cả các metadata mà nó nhận được từ hàm stat();

		. Line 12: chúng tôi đã khai báo một biến kiểu struct stat; địa chỉ của nó được sử dụng ở line 11 để gọi hàm stat();

		. Line 15: nếu lời gọi không thành công, chúng tôi in một thông báo chẩn đoán ngắn và trả về -1;

		. Line 18: nếu không, chúng tôi in nội dung của trường struct stat theo từng trường; lưu ý rằng hầu hết các trường đều thuộc loại long int và do đó cần đối số %ld;

		. Line 20: trường st_mode được in dưới dạng bát phân (%o) – dạng này giúp đơn giản hóa việc giải thích giá trị của nó (đúng, chúng tôi biết, chỉ có những người sử dụng Unix mới thực sự hài lòng với tính năng này; chúng tôi có thể không cần nó)

		. Line 21: chúng tôi cố gắng hiển thị nội dung của st_mode theo một hình thức dài hơn – chúng tôi kiểm tra tất cả các bit quan trọng bằng cách sử dụng các predefined bit masks để tìm hiểu khả năng và quyền của file; tất nhiên, hành động tương tự có thể được thực hiện một cách tinh tế và ngắn gọn hơn, nhưng chúng tôi ưu tiên sự dễ đọc;

		. Line 50: để in thời gian thì cần một hàm chuyên biệt tên là ctime(); nó mong đợi một địa chỉ của một giá trị thời gian (bạn còn nhớ Epoch không? – đây là điều chúng tôi sử dụng ở đây) và chuyển đổi nó thành một string, hiển thị thời gian dưới dạng đọc được bằng ngôn ngữ con người, theo tiêu chuẩn địa phương;

		. Line 59: chúng tôi kiểm tra xem người dùng đã cung cấp cho chúng tôi ít nhất một đối số chưa và in một thông báo chẩn đoán nếu chưa;

		. Line 65: chúng tôi lặp lại qua tất cả các tham số và gọi hàm file() cho mỗi tham số.


3.5.1.6
	- Microsoft's implementation về hàm stat() cổ điển khác biệt đáng kể so với bản gốc. Điều này không ngạc nhiên, vì triết lý của MS Windows khá xa lạ so với nhiều khái niệm Unix. Hãy đi qua những khác biệt quan trọng nhất:

		. Các trường st_dev và st_rdev lưu trữ số ổ đĩa (A: → 0, B: → 1, v.v.).
	
		. Trường st_ino không có ý nghĩa trong MS Windows và chứa giá trị 0;
	
		. Trường st_mode phần nào phản ánh quyền truy cập file trong MS Windows (chỉ một phần, vì hệ thống quyền của Windows hoàn toàn khác biệt so với Unix); Note: thuộc tính thực thi được giả định từ tên file, không phải từ quyền truy cập của nó;
	
		. st_uid và st_gid luôn luôn là 0;
	
		. st_blksize và st_blocks không xuất hiện trong MS Windows – bạn không nên sử dụng những trường này trong code của bạn;
	
		. Các trường st_atime và st_mtime chỉ chứa giá trị hợp lý cho các file được lưu trữ trên các ổ đĩa NTFS, nếu không chúng được sao chép từ st_ctime;

	- Bây giờ chúng ta đã sẵn sàng để hiển thị cho bạn phiên bản Windows của đoạn code trước đó.


3.5.1.7
	- Code đây:

		#include <stdio.h>
		#include <errno.h>
		#include <sys/types.h>
		#include <sys/stat.h>
		#include			// for ctime()

		#define S_IRUSR (1 << 2)
		#define S_IWUSR (1 << 1)
		#define S_IXUSR (1 << 0)

		#define S_IRGRP (1 << 5)
		#define S_IWGRP (1 << 4)
		#define S_IXGRP (1 << 3)

		#define S_IROTH (1 << 8)
		#define S_IWOTH (1 << 7)
		#define S_IXOTH (1 << 6)

		int
		file (char *name)
		{
		  printf ("%s:\n", name);
		  struct stat buf;
		  char timestr[32];

		  if (stat (name, &buf) < 0)
		    {
		      printf ("\tCannot stat it -- errno=%d\n", errno);
		      return -1;
		    }
		  printf ("\tDevice ID:\t%ld\n", buf.st_dev);
		  printf ("\tInode no:\t%ld\n", buf.st_ino);

		  printf ("\tFile mode:\t%o\n", buf.st_mode);
		  if (buf.st_mode & S_IFREG)
		    printf ("\t\tordinary file\n");
		  if (buf.st_mode & S_IFDIR)
		    printf ("\t\tdirectory\n");
		  if (buf.st_mode & S_IRUSR)
		    printf ("\t\treadable for owner\n");
		  if (buf.st_mode & S_IWUSR)
		    printf ("\t\twritable for owner\n");
		  if (buf.st_mode & S_IXUSR)
		    printf ("\t\texecutable for owner\n");
		  if (buf.st_mode & S_IRGRP)
		    printf ("\t\treadable for group\n");
		  if (buf.st_mode & S_IWGRP)
		    printf ("\t\twritable for group\n");
		  if (buf.st_mode & S_IXGRP)
		    printf ("\t\texecutable for group\n");
		  if (buf.st_mode & S_IROTH)
		    printf ("\t\treadable for others\n");
		  if (buf.st_mode & S_IWOTH)
		    printf ("\t\twritable for others\n");
		  if (buf.st_mode & S_IXOTH)
		    printf ("\t\texecutable for others\n");
		  printf ("\tHard links:\t%ld\n", buf.st_nlink);
		  printf ("\tOwner UID:\t%d\n", buf.st_uid);
		  printf ("\tGroup GID:\t%d\n", buf.st_gid);
		  printf ("\tSpecial ID:\t%ld\n", buf.st_rdev);
		  printf ("\tFile size:\t%ld\n", buf.st_size);
		//      printf("\tBlk size:\t%ld\n", buf.st_blksize);      absent in MS Windows
		//      printf("\tBlk count:\t%ld\n", buf.st_blocks);      absent in MS Windows
		  printf ("\tAccess time:\t%s", ctime (&buf.st_atime));
		  printf ("\tCreation time:\t%s", ctime (&buf.st_ctime));
		  printf ("\tModifictn time:\t%s", ctime (&buf.st_mtime));
		  return 0;
		}

		int
		main (int argc, char *argv[])
		{
		  if (argc < 2)
		    {
		      fprintf (stderr, "usage: %s filename...\n", argv[0]);
		      return 1;
		    }
		  int i;
		  for (i = 1; i < argc; i++)
		    file (argv[i]);
		  return 0;
		}

	- Note: Chúng ta phải tự define một vài ký tự - môi trường CL không định nghĩa những ký tự chịu trách nhiệm cho quyền truy cập file. Chúng tôi thực hiện bằng cách sử dụng một kí hiệu dấu phẩy động - kí hiệu đó di chuyển đến vị trí của nó thông qua toán tử <<.


3.6.1.1 Low-level I/O – addendum
	- Để hoàn thiện câu chuyện về low-level I/O của chúng ta, chúng tôi muốn chia sẻ với bạn về cách bạn có thể (gần như) implement cùng một khái niệm trên các hệ điều hành khác nhau. Sự khác biệt không chỉ nằm ở low-level system và ABIs, mà còn ở các high level API và ở highest level (giao diện người dùng). Chúng tôi sẽ minh họa câu chuyện của mình bằng một khái niệm rất hữu ích: liên kết mềm, hay còn được gọi là soft link.

	- Soft link là một loại file rất đặc biệt được thiết kế để lưu trữ thông tin về vị trí của một file khác. Thực tế, bất kỳ soft link nào cũng có thể được sử dụng như original, linked file.

	- Note: sự softness của loại link này nằm ở việc cơ chế được triển khai ở một level tương đối của hệ điều hành. Hard link được tạo trực tiếp bên trong hệ thống file, trong khi soft link không được – các filesystem services thì treat chúng như bất kỳ file thông thường nào khác, và bản chất của chúng trở nên rõ ràng hơn ở level cao hơn.

	- Một sự khác biệt quan trọng khác là hard links không được phép vượt qua ranh giới volume – tức là bạn sẽ không thể tạo hard link đến một file đang tồn tại trên một ổ đĩa khác. Điều này trở nên rõ ràng khi bạn xem xét việc hard link sử dụng absolute media addressing (địa chỉ truy cập phương tiện tuyệt đối), điều này sẽ không hoạt động đúng khi bất kỳ volumes/devices nào bị ngắt kết nối đột ngột.

	- Soft link sử dụng một loại địa chỉ hỗn hợp – chúng sử dụng tên volume và thư mục, giữ nguyên tính hợp lệ ngay cả khi một volume bị ngắt kết nối. Tất nhiên, liên kết sẽ không hợp lệ cho đến khi volume được kết nối lại (file đã liên kết sẽ không thể truy cập, nhưng điều này sẽ thay đổi ngay khi volume được kết nối lại).

	- Let's start from the Unix side of this world.

	- Tại system command level, soft link trong Unix được tạo bằng lệnh ln (liên kết) equipped with an -s (soft hoặc symbolic) option. Command cần hai đối số: tên của file thực tế và tên của liên kết được tạo.

	- Nếu bạn biết tên của symbolic link và muốn biết tên của linked (actual) file, bạn nên sử dụng lệnh readlink.

	- Liên kết mềm có thể được xóa bằng cách sử dụng general command rm (remove).

	- Dưới đây là tất cả các lệnh này:

		ln -s actual_file link_name

		readlink link_name

		rm link_name

	- Để tạo một liên kết mềm ở API level, bạn có thể sử dụng một hàm có tên symlink(). Prototype của nó như sau:

		#include <unistd.h>

		int symlink(char *target, char *linkpath);

	- Note: các tham số và thứ tự của chúng phản ánh cú pháp của lệnh ln.

	- Hàm return 0 nếu thành công và -1 nếu ngược lại (biến errno được thiết lập để hiện lỗi đang xảy ra)


3.6.1.2
	- Hãy sử dụng hàm theo một cách hơi điên rồ – chúng ta sẽ viết một chương trình tạo một symbolic link đến một file có tên cho trước, và liên kết mới đã được tạo sẽ được xây dựng từ một pseudorandom int value.

	- code như sau:

		#include <sys/stat.h>
		#include <errno.h>
		#include <stdio.h>
		#include <string.h>
		#include <stdlib.h>
		#include <unistd.h>
		#include <time.h>

		int
		main (int argc, char *argv[])
		{
		  if (argc != 2)
		    {
		      fprintf (stderr, "usage: %s filename\n", argv[0]);
		      return 1;
		    }
		  struct stat st;
		  if (stat (argv[1], &st) == 0)
		    {
		      if (st.st_mode & S_IFREG)
			{
			  char newname[16];
			  srand (time (NULL));
			  sprintf (newname, "link_%d", rand ());
			  if (symlink (argv[1], newname) != 0)
			    {
			      fprintf (stderr, "link failed: %s\n", strerror (errno));
			      return 3;
			    }
			  printf ("Link \"%s\" created\n", newname);
			}
		    }
		  else
		    {
		      fprintf (stderr, "%s does not exist or is not a regular file\n",
			       argv[1]);
		      return 2;
		    }
		  return 0;
		}

	- Note các fragments sau:
		
		. line 18: Chúng ta kiểm tra xem liệu file được chọn để tạo liên kết có tồn tại và là một file thông thường hay không (chúng ta không muốn tạo liên kết đến một thư mục hoặc đến một symbolic link khác – điều này hoàn toàn hợp pháp và khả thi, nhưng chúng ta muốn tránh điều này)
		
		. line 25: Liên kết được tạo ở đây và nếu có lỗi xảy ra, một thông báo sẽ được in ra.

	- The code, chạy trên máy tính của chúng tôi với một đối số được chỉ định là 03.06.slink.c, tạo ra đầu ra sau đây:

		Link "link_436831867" created
	
	- Sử dụng bất kỳ system utility (tiện ích hệ thống) nào để khám phá thư mục của bạn (ls -l là lựa chọn đầu tiên cho một nhiệm vụ như vậy) và kiểm tra xem liên kết đã được xây dựng đúng cách chưa.


3.6.1.3
	- Bây giờ chúng ta sẽ tìm tên của actual file từ tên của liên kết. Chúng ta sẽ sử dụng hàm readlink() cho mục đích đó.

	- Prototype:

		ssize_t readlink(char *pathname, char *buf, size_t bufsiz);


		. Tham số đầu tiên đã truyền tên liên kết đang tồn tại;
		
		. Tham số thứ hai nên là một con trỏ đến bộ đệm đủ lớn để chứa tên của actual file;
		
		. Tham số thứ ba chỉ định độ dài thực tế của bộ đệm.

	- Hàm trả về độ dài của tên kết quả – đây là một giá trị rất quan trọng, vì hàm không đặt một \0 ở cuối tên và bạn phải tự làm điều này. Nhờ vào giá trị này, bạn sẽ biết nơi kết thúc string.

	- Nếu xảy ra bất kỳ lỗi nào, readlink() returns -1 (and the errno, blah, blah, blah – you get it).


3.6.1.4
	- Chúng ta sẽ sử dụng hàm để tìm liên kết thực sự cho bất kỳ liên kết mềm nào – đây sẽ là một phiên bản đơn giản của real readlink system command.

	- Đây là code:

		#include <stdio.h>
		#include <string.h>
		#include <errno.h>
		#include <unistd.h>

		int
		main (int argc, char *argv[])
		{
		  if (argc != 2)
		    {
		      fprintf (stderr, "usage: %s linkname\n", argv[0]);
		      return 1;
		    }
		  char realname[512];
		  int len = readlink (argv[1], realname, sizeof (realname) - 1);
		  if (len > 0)
		    {
		      realname[len] = '\0';
		      printf ("%s -> %s\n", argv[1], realname);
		    }
		  else
		    {
		      fprintf (stderr, "readlink failed: %s\n", strerror (errno));
		      return 2;
		    }
		  return 0;
		}

	- Chú ý các fragments sau:
	
		. line 15: chúng ta gọi hàm readlink() và lưu giá trị trả về của nó;
		
		. line 16: chúng ta kiểm tra giá trị và xem liệu nó lớn hơn 0 hay không;
		
		. line 18: chúng ta bổ sung chuỗi bằng ký tự \0 ở cuối;
		
		. line 23: chúng ta in một thông điệp chẩn đoán nếu ngược lại.

	- The code, chạy trên máy tính của chúng tôi, với một đối số được chỉ định là link_436831867, tạo ra output sau đây:

		link_436831867 -> 03.06.slink.c


3.6.1.5
	- Việc xóa một liên kết được thực hiện bằng một hàm bạn đã quen thuộc: unlink().

	- Prototype như sau:

		int unlink(const char *pathname);

	- Note: trái ngược với tên của nó, hàm có thể remove more than just links!

	- Hàm returns 0 khi thành công và -1 trong trường hợp ngược lại (và biến errno hoạt động như thường lệ).

	- Ví dụ tiếp theo của chúng tôi sử dụng unlink() để xóa liên kết có tên được chỉ định, nhưng chỉ đồng ý xóa các soft link và từ chối xóa bất cứ thứ gì khác.

	- Code như sau:

		#include <sys/stat.h>
		#include <errno.h>
		#include <stdio.h>
		#include <string.h>
		#include <unistd.h>

		int
		main (int argc, char *argv[])
		{
		  if (argc != 2)
		    {
		      fprintf (stderr, "usage: %s linkname\n", argv[0]);
		      return 1;
		    }
		  struct stat st;
		  if ((lstat (argv[1], &st) == 0) && S_ISLNK (st.st_mode))
		    {
		      if (unlink (argv[1]) != 0)
			{
			  fprintf (stderr, "delete failed: %s\n", strerror (errno));
			  return 3;
			}
		      printf ("Link \"%s\" deleted\n", argv[1]);
		    }
		  else
		    {
		      fprintf (stderr, "%s does not exist or is not a soft link\n", argv[1]);
		      return 2;
		    }
		  return 0;
		}

	- Note các fragments sau:
		
		. line 15: chúng tôi đã sử dụng hàm lstat() thay vì stat() thông thường; sự khác biệt này rất quan trọng: stat() xử lý soft link như các files thông thường (không thể phân biệt giữa chúng), trong khi lstat() phát hiện đúng soft link;
		
		. line 15 (ở một phần tiếp theo): chúng tôi đã sử dụng một macro có tên là S_ISLNK(), được định nghĩa trong sys/stat.h, nó trả về một giá trị khác không khi đối số của nó mô tả một soft link.

	- The code, chạy trên máy tính của chúng tôi, với một đối số được chỉ định là link_436831867, tạo ra đầu ra sau đây:

		Link "link_436831867" deleted


3.6.1.6
	- Bây giờ chúng ta sẽ nhảy vào phần của thế giới MS Windows. Hãy chuẩn bị cho nhiều điều bất ngờ.

	- Ở system command level, soft link trong MS Windows được tạo bằng MKLINK (make link). Lệnh cần hai đối số: tên của liên kết được tạo và tên của file thực tế (note: thứ tự của các đối số được đảo ngược so với ln trong Unix).

	- MS Windows không có phiên bản tương đương với readlink từ Unix.

	- Soft link có thể được xóa bằng lệnh chung có tên là DEL (delete).

	- Tất cả các lệnh đều ở đây:

		MKLINK link_name actual_file

		DEL link_name


3.6.1.7
	- Bây giờ chúng ta sẽ viết lại chương trình trước đó để thích ứng nó hoạt động trong MS Windows, sử dụng một số hàm nguyên bản của nó.

	- Code sau:

		#include <sys/stat.h>
		#include <stdio.h>
		#include <string.h>
		#include <stdlib.h>
		#include <time.h>

		#include <Windows.h>

		int
		main (int argc, char *argv[])
		{
		  if (argc != 2)
		    {
		      fprintf (stderr, "usage: %s filename\n", argv[0]);
		      return 1;
		    }
		  long Attrs = GetFileAttributes (argv[1]);
		  if ((Attrs != INVALID_FILE_ATTRIBUTES) &&
		      !(Attrs & FILE_ATTRIBUTE_DIRECTORY) &&
		      !(Attrs & FILE_ATTRIBUTE_REPARSE_POINT))
		    {
		      char newname[16];
		      srand (time (NULL));
		      sprintf (newname, "link_%d", rand ());
		      if (CreateSymbolicLink (newname, argv[1], 0) == 0)
			{
			  wchar_t msg[256];
			  FormatMessageW (FORMAT_MESSAGE_FROM_SYSTEM, NULL, GetLastError (),
					  MAKELANGID (LANG_NEUTRAL, SUBLANG_DEFAULT), msg,
					  256, NULL);
			  fprintf (stderr, "link failed: %ws\n", msg);
			  return 3;
			}
		      printf ("Link \"%s\" created\n", newname);
		    }
		  else
		    {
		      fprintf (stderr, "%s does not exist or is not a regular file\n",
			       argv[1]);
		      return 2;
		    }
		  return 0;
		}

	- Chú ý đến các fragments sau:
	
		. line 7: chúng ta đã include <Windows.h> header chứa các prototypes của các hàm nguyên bản MS Windows hoạt động trên files và filesystems;
	
		. line 17: chúng ta không sử dụng hàm stat() – nó quá yếu để khám phá một số tính năng của các native MS Windows files; thay vào đó, chúng ta sẽ sử dụng GetFileAttributes(); hàm cần tên của file và trả lại các thuộc tính của nó nếu có thể;
	
		. line 18: nếu nó không thể có được các thuộc tính, hàm trả về giá trị INVALID_FILE_ATTRIBUTES – đây là điều kiện đầu tiên chúng ta kiểm tra;
	
		. line 19: bây giờ chúng ta kiểm tra xem file có phải là thư mục hay không (hằng số FILE_ATTRIBUTE_DIRECTORY) – chúng ta không muốn file là một thư mục, vì vậy chúng ta thêm not trước biểu thức (!)
	
		. line 20: một kiểm tra tương tự nhưng nhằm vào các symbolic link (FILE_ATTRIBUTE_REPARSE_POINT)
	
		. line 25: liên kết mới được tạo bằng hàm CreateSymbolicLink() với hai đối số: tên của liên kết mới và tên của file đã tồn tại (thứ tự của đối số lại được đảo ngược); hàm trả về 0 trong trường hợp có lỗi;
	
		. line 28: chúng ta sử dụng hàm FormatMessage() MS Windows để chuẩn bị một thông điệp chẩn đoán; code của lỗi được lấy từ hàm GetLastError(); nếu bạn muốn biết thêm về các chức năng mà hàm FormatMessage() cung cấp, vui lòng tham khảo:
	
			FormatMessage function link:

			https://edube.org/learn/c-advanced/low-level-i-o-addendum-14

	- Sử dụng bất kỳ tiện ích hệ thống nào để khám phá thư mục của bạn (dir là lựa chọn đầu tiên cho công việc này) và kiểm tra xem liên kết có được xây dựng đúng cách không.

	- Note: bạn phải có quyền quản trị viên để tạo symbolic link trong MS Windows – khó khăn nhưng là sự thật! Xin lỗi vì sự bất tiện này.


3.6.1.8
	- Vì API MS Windows không chứa bất kỳ hàm nào cung cấp những khả năng tương tự như readlink(), chúng tôi cảm thấy có trách nhiệm hiển thị cho bạn một chương trình đơn giản để xóa các symbolic link.

	- Code như sau:

		#include <stdio.h>
		#include <Windows.h>

		int
		main (int argc, char *argv[])
		{
		  if (argc != 2)
		    {
		      fprintf (stderr, "usage: %s linkname\n", argv[0]);
		      return 1;
		    }
		  long Attrs = GetFileAttributes (argv[1]);
		  if ((Attrs != INVALID_FILE_ATTRIBUTES)
		      && (Attrs & FILE_ATTRIBUTE_REPARSE_POINT))
		    {
		      if (DeleteFile (argv[1]) == 0)
			{
			  wchar_t msg[256];
			  FormatMessageW (FORMAT_MESSAGE_FROM_SYSTEM, NULL, GetLastError (),
					  MAKELANGID (LANG_NEUTRAL, SUBLANG_DEFAULT), msg,
					  256, NULL);
			  fprintf (stderr, "delete failed: %ws\n", msg);
			  return 3;
			}
		      printf ("Link \"%s\" deleted\n", argv[1]);
		    }
		  else
		    {
		      fprintf (stderr, "%s does not exist or is not a symbolic link\n",
			       argv[1]);
		      return 2;
		    }
		  return 0;
		}

	- Có 1 element duy nhất cần giải thích là hàm DeleteFile():
		
		. Nó cần một đối số chứa tên của file tin cần xóa;
		
		. Nó trả về 0 trong trường hợp có lỗi.

	- Phần còn lại của code nên clear với bạn.


3.7.1.1 Low-level I/O – file control
	- Ở cuối câu chuyện về low-level I/O của chúng tôi, chúng tôi muốn kể cho bạn về cách kiểm soát các file descriptors. Thật không may, phần này của cốt truyện chỉ dành riêng cho Unix/Linux.

	- Có một hàm trong POSIX cho phép programmer thao tác với các file descriptors và kiểm tra hoặc đặt một số khả năng của chúng trong quá trình chạy. Hãy xem các prototypes:

		#include <unistd.h>
		#include <fcntl.h>

		int fcntl (int fd, int cmd);
		int fcntl (int fd, int cmd, long arg);
		int fcntl (int fd, int cmd, struct flock *lock);

	- Bây giờ, đừng nghĩ rằng có ba hàm khác nhau có tên là fcntl() – điều này không thể xảy ra trong "C" (cho đến nay – ai biết tương lai có thể mang lại điều gì?). Đây là một bảng trình bày ba phương thức gọi hàm fcntl() khả dụng.

	- Gọi hàm fcntl() yêu cầu hai đối số:
		
		. Đối số đầu tiên, đại diện cho một file descriptors đã mở;
		
		. Đối số thứ hai, đại diện cho một command (một code of action cần thực hiện bởi hàm).

	- Trong một số trường hợp, hành động có thể yêu cầu các đối số bổ sung và sau đó sử dụng một đối số thứ ba.

	- Hàm trả về một giá trị int, nhưng ý nghĩa của giá trị của nó thay đổi tùy thuộc vào hành động được chỉ định.

	- Chúng tôi sẽ chỉ bạn ba ví dụ về cách sử dụng hàm này.


3.7.1.2
	- Lệnh F_DUPFD được sử dụng để force duplication một file descriptor đã cho (do đó có tên là: DUPLICATE File Descriptor). Duplication có nghĩa là bạn nhận được một file descriptor mới liên kết với cùng một file đã mở. Điều này cho phép bạn thao tác với một file vật lý từ nhiều logical "places" khác nhau trong code của bạn, e.g. khi tất cả các hành động này được thực hiện song song, ví dụ: trong các threads khác nhau.

	- Hàm đảm bảo rằng resulting descriptor sẽ lớn hơn hoặc bằng giá trị được truyền làm đối số thứ ba.

	- Hàm fcntl() được gọi với lệnh F_DUPFD returns the new (duplicated) descriptor, hoặc -1 nếu có lỗi (yes, errno will do its job too).

	- Note: có một hàm có tên là dup() hoạt động theo cách rất tương tự và cũng có sẵn trong MS Windows.

	- Hãy nhìn code:

		#include <unistd.h>
		#include <fcntl.h>
		#include <stdio.h>
		#include <errno.h>
		#include <string.h>

		int
		main (void)
		{
		  int fd = open ("__file__.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
		  if (fd > 0)
		    {
		      int fd2 = fcntl (fd, F_DUPFD, fd);
		      if (fd2 > 0)
			{
			  printf ("fd=%d,fd2=%d\n", fd, fd2);
			  int c;
			  for (c = 'A'; c <= 'Z'; c++)
			    write (c % 2 ? fd : fd2, &c, 1);
			  close (fd2);
			}
		      close (fd);
		    }
		  else
		    {
		      fprintf (stderr, "failed to open: %s\n", strerror (errno));
		    }
		  return 0;
		}

	- Chương trình tạo ra một new (empty) file có tên là __file__.txt (trước khi bạn chạy file thực thi, hãy kiểm tra xem bạn có file riêng với tên đó không!) và sau đó nhân bản file descriptor của nó. Vòng lặp for đảm bảo rằng các chữ cái lẻ được viết vào fd trong khi chữ cái chẵn được viết vào fd2.

	- Sau khi chtrinh hoàn thành, kiểm tra nội dung file – chúng tôi tin rằng nó sẽ chứa toàn bộ bảng chữ cái.


3.7.1.3
	- Lệnh F_GETFL được sử dụng để fetch (tìm và mang về) status flags (do đó có tên là: GET FLags). Đây gần như là những flags giống những flags được sử dụng trong đối số thứ hai của cuộc gọi hàm open(). Điều này cho phép bạn kiểm tra khả năng của file descriptor, e.g. khi bạn nhận được một descriptor đã được mở bởi người khác và bạn không thể chắc chắn về bản chất của nó.

	- Note: một số trong những flags (the open-time flags) không được bảo tồn sau cuộc gọi hàm open() - ví dụ: O_CREAT và O_TRUNC.

	- Kết quả là một giá trị int phản ánh các flags của descriptor hoặc -1 nếu có lỗi (sử dụng errno để biết thêm).

	- Nhìn code sau:

		#include <stdio.h>
		#include <errno.h>
		#include <string.h>
		#include <sys/types.h>
		#include <unistd.h>
		#include <fcntl.h>

		#define check(val,flag)	((val & flag) && printf("\t"#flag"\n"))

		int
		main (void)
		{
		  int fd = open ("__file__.txt", O_WRONLY | O_CREAT | O_TRUNC | O_SYNC, 0666);
		  if (fd > 0)
		    {
		      int flags = fcntl (fd, F_GETFL);
		      printf ("fd=%d\n", fd);
		      /* access mode */
		      check (flags, O_WRONLY);
		      check (flags, O_RDONLY);
		      check (flags, O_RDWR);
		      /* operating mode */
		      check (flags, O_APPEND);
		      check (flags, O_SYNC);
		    }
		  else
		    {
		      fprintf (stderr, "error: %s\n", strerror (errno));
		      return 1;
		    }
		  return 0;

	- Nó hiển thị một phương pháp đơn giản để kiểm tra các descriptor's flags. Điểm chủ chốt của trick này được ẩn bên trong macro check() – nó đơn giản hóa code và làm nó ngắn gọn hơn. Lưu ý, chúng tôi đã sử dụng toán tử && như một loại chỉ thị điều kiện rất đặc biệt – phía bên phải của nó được đánh giá (tức là hàm printf() sẽ được gọi) khi và chỉ khi bên trái của nó đánh giá khác không.

	- Chương trình xuất ra:

		fd=3
		    O_WRONLY
		    O_SYNC


3.7.1.4
	- Lệnh F_SETFL được sử dụng để sửa đổi trạng thái của một số file status flags (do đó có tên là: SET FLags). Đây gần như là những flag giống những flag được sử dụng bởi F_GETFL, nhưng bạn không được phép thay đổi chế độ truy cập trong khi file vẫn còn mở (tức là bất cứ thứ gì mở ở một chế độ nhất định phải ở lại trong chế độ này cho đến khi nó được đóng).

	- Điều này cho phép bạn thay đổi một số khả năng của descriptor trong quá trình chạy.

	- Đối số thứ ba của fcntl() được sử dụng để truyền một bit mask mới (một bộ flag mới).

	- Kết quả là -1 nếu có lỗi (sử dụng errno để biết thêm) hoặc 0 nếu không có lỗi.

	- Hãy nhìn code:

		#include <stdio.h>
		#include <errno.h>
		#include <string.h>
		#include <sys/types.h>
		#include <unistd.h>
		#include <fcntl.h>

		#define check(val,flag)	((val & flag) && printf("\t"#flag"\n"))

		int
		main (void)
		{
		  int fd = open ("__file__.txt", O_WRONLY | O_CREAT | O_TRUNC | O_SYNC, 0666);
		  if (fd > 0)
		    {
		      int flags = fcntl (fd, F_GETFL);
		      printf ("fd=%d\n", fd);
		      /* access mode */
		      check (flags, O_WRONLY);
		      check (flags, O_RDONLY);
		      check (flags, O_RDWR);
		      /* operating mode */
		      check (flags, O_APPEND);
		      check (flags, O_SYNC);
		    }
		  else
		    {
		      fprintf (stderr, "error: %s\n", strerror (errno));
		      return 1;
		    }
		  return 0;

	- Cờ O_APPEND được sửa đổi hai lần trong code (invocation của hàm open() đặt nó ban đầu vào trạng thái ON). Note cách chúng tôi đã sử dụng các toán tử &= và |= để thay đổi trạng thái của the only chosen bit, giữ nguyên tất cả các bit khác. Chương trình output:

		    O_APPEND
		-----------------------
		-----------------------
		    O_APPEND


3.7.1.5
	- Bạn có thể đặt câu hỏi: liệu chúng ta có thể đi sâu hơn không? Có thể kiểm soát hệ thống I/O ở level thấp hơn so với những hàm chúng tôi mô tả trước đó, level mà không sử dụng assembly hoặc sửa đổi một số phần của OS không?

	- Yes, it's possible, nhưng bạn phải lưu ý rằng gần như mọi thứ dưới level này hoàn toàn phụ thuộc vào phần cứng và nền tảng. Bạn phải có kiến thức chi tiết về các thiết bị bạn muốn kiểm soát và, rất có thể, phải có quyền quản trị viên để thao tác trên chúng.

	- Giao diện chung (nhưng thông thường không thể chuyển đổi) đến level thấp hơn của một hệ thống I/O được cung cấp bởi hàm sau:

		#include <sys/ioctl.h>
		int ioctl (int fd, unsigned long request, ...);

	- Chúng ta có thể nói - một cách deceitfully - rằng hàm không làm gì cả. Nó chỉ đơn giản chuyển các đối số của nó đến các hàm hệ điều hành cơ bản (thường là đến device driver hoặc module khác có vai trò tương tự) và báo cáo reaction của nó đối với request/command mà chúng ta đã gửi.

	- Vì vậy, chúng ta đã đến ranh giới rồi, xa hơn nó chỉ có OS. Ta không muốn đến đó. Let it remain a black box.