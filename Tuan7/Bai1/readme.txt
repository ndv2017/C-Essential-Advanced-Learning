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

	- Vào thời điểm "C" được phát triển, một quá trình là phần nhỏ nhất và không thể chia nhỏ hơn của một đoạn code đang chạy. Để chính xác: một quá trình là một đoạn code đang chạy (được thực thi hiện tại). Chúng ta có thể nói rằng vào những ngày đó, một OS là một công cụ để đồng bộ hóa, lập lịch và kiểm soát các quá trình đang chạy song song.

	- Tình trạng này vẫn tiếp tục cho đến khi một khái niệm mới xuất hiện - khái niệm về một đơn vị "nhẹ" hơn so với quá trình cổ điển; nhẹ hơn, do đó dễ dàng khởi động, kiểm soát, đồng bộ hóa và hủy bỏ. Thực thể mới này, phổ biến trong các OS hiện đại, được gọi là một luồng (thread).

	- Tất nhiên, có thể làm việc với các luồng bằng cách sử dụng các ngôn ngữ lập trình tiêu chuẩn không nhận biết luồng. Trong thực tế, lập trình luồng đã có thể trong C language từ đầu, nhờ vào các thư viện chuyên biệt chứa các bộ hàm tổ chức thực thi luồng. Một số thư viện này đã trở thành tiêu chuẩn được công nhận phổ biến, trong khi một số khác rất cụ thể và liên quan chặt chẽ đến các OS hoặc nền tảng phần cứng cụ thể.

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

		. Cái thứ hai có nghĩa là GCC không chỉ là 1 C language compiler, nhưng cũng là foundation mà có thể dùng để implement bất kì compiler hay bất kì ngôn ngữ nào cho bất kì nền tảng phần cứng nào và bất kì OS nào. Trong những cái này, GCC còn có thể dùng để implement một cross compiler (biên dịch chéo) (compiler mà làm việc trên nền tảng X xây dựng code nhị phân cho nền tảng Y, trong đó X != Y).

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
			> software - OS khác nhau dùng phương thức access thiết bị, files và GUIs khác nhau.

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

	- Đôi lúc chtrinh muốn dọn dẹp một số thứ trước khi exit. Bước cleaning này có thể bao gồm xóa files hay directories tạm thời, hoàn thành các database transactions, output những thông báo chuẩn đoán, .... atexit() function có khả năng đăng kí 1 function sẽ được gọi trước khi trả lại quyền điều khiển cho OS. Ngoài ra nó còn có thể đki nhiều functions như vậy.

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
	- API (as in Application Programming Interface) là một bộ tiêu chuẩn, giao thức, quy tắc, thủ tục, quy ước, quyết định, thói quen và truyền thống, được các programmer sử dụng để kết nối code của họ một cách hiệu quả và an toàn với code hiện có và ngược lại, để làm cho các tính năng mới của code của họ tương thích với code của một programmer khác.

	- Lưu ý rằng thuật ngữ API chỉ đề cập đến source code mà thôi - một API điển hình nói ít hoặc gần như không nói gì về cách kết nối này hoạt động ở binary level.

	- Hai trong số những API đặc trưng nhất là:

		. POSIX (Portable Operating System Interface for Unix): một bộ tiêu chuẩn được định nghĩa cho các hệ thống Unix và giống Unix; thực ra bộ này is much more than just an API, nhưng API là một phần không thể tách rời của nó; nhiều trong số các hàm được định nghĩa trong C language standards cũng được bao gồm trong POSIX (đặc biệt là những hàm liên quan đến các dịch vụ của OS); chúng ta có thể nói, hơi hùng biện, rằng POSIX là bảo vệ của tính di động của phần mềm - code được viết với sự tôn trọng đối với yêu cầu API có cơ hội tốt để được compiler và chạy thành công trên nhiều, hoặc thậm chí trên tất cả, các nền tảng sử dụng các quy ước giống nhau; 

		. Windows API (hoặc gọi là WinAPI): một bộ tiêu chuẩn tương tự, nhưng được sử dụng trong môi trường Microsoft Windows; nó rộng lớn và phức tạp hơn nhiều so với POSIX, vì nó bao gồm gần như tất cả các loại dịch vụ của OS (ví dụ: tương tác với GUI).

	- Còn nhiều API khác trên thế giới. Trên thực tế, mỗi programmer đều định nghĩa API của riêng mình khi bắt đầu một dự án phần mềm mới.


3.1.1.3 Low-level IO
	- Thay đổi chỉ một chữ cái brings us into a completely different world.

	- Look:

		ABI

	ABI (viết tắt của Application Binary Interface) là một bộ tiêu chuẩn tương tự, nhưng liên quan đến level nhị phân. Một API có thể chỉ cho bạn cách viết một chương trình để tương thích với một OS hoặc nền tảng được chọn, nhưng nó không nói gì về cách code được biên dịch tương tác với các dịch vụ của OS hoặc các thành phần phần mềm khác. Ngược lại, ABI không phụ thuộc vào API. Thông thường, các hệ thống giống Unix sử dụng cùng một API (POSIX) nhưng triển khai một ABI hoàn toàn không tương thích, khiến code thực thi bị non-portable (khả năng portable chỉ có thể được đảm bảo ở source language level - điều này có nghĩa là code phải được biên dịch lại để có thể chuyển đến một nền tảng mới).

	- Chúng ta có thể nói rằng:

		. Nếu bạn không phải là một nhà phát triển OS, vấn đề quan trọng nhất đối với bạn là API;

		. ABI có thể là mối quan tâm đối với bạn nếu bạn bắt đầu phát triển các phần low-level của OS (hệ điều hành) như các trình điều khiển hoặc một compiler mới với bộ công cụ của nó.

	- Chương hiện tại xử lý low level (thực ra là level thấp nhất) của các hoạt động input/output có sẵn trong C language. Đây là nơi code nhị phân của bạn contacts trực tiếp với hệ điều hành. Chúng tôi đã nói rằng C language có mối liên quan chặt chẽ với Unix và các hệ thống giống Unix, vì vậy tất cả các hàm được thiết kế để thực hiện các hoạt động I/O ở low level thực sự chỉ là wrappers (bao bọc) của các dịch vụ hệ điều hành tương ứng.

	- Điều này có thể có nghĩa là các hệ điều hành không tương thích với Unix (theo nghĩa của API) có thể triển khai dịch vụ của họ một cách hoàn toàn khác nhau. Như câu nói nổi tiếng, trong Unix mọi thứ đều là một file. Đừng hiểu đó là đúng. Nhưng các hệ thống giống Unix thích treats nhiều đối tượng hệ thống như thể chúng là các file. Ví dụ, các network channels đặc biệt được sử dụng để truyền dữ liệu (gọi là network (ổ cắm mạng) - chúng ta sẽ thảo luận về chúng sau) được nhìn thấy bởi programmer như các file. Trong Unix, một hàm I/O ở low level cụ thể có thể hoạt động không chỉ trên các file thực sự mà còn trên thiết bị và các tiện ích khác.

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



~ Module 4 ~

	In this module, you will learn about:

	- manipulating memory blocks
	- string manipulation: strchr(), strrchr(), strstr(), strtok();
	- qsort(), bsearch();
	- aligned_alloc(), calloc(), malloc(), and realloc();
	- bcopy();
	- memcpy();
	- memccpy();
	- memmove();
	- bzero();
	- memset();
	- memcmp();
	- Internationalization I18N
		. UNICODE. UCS, UTF-8 - how to deal with multilingual environment?;
		. universal character names;
		. wide characters support in different C dialects (, , …);
		. strcoll() and wcscoll();


4.1.1.2 Memory and strings – how the memory is used and how to deal with it
	- Trước khi thảo luận về bộ nhớ và cách sử dụng nó, chúng ta cần nói vài lời về cách hệ điều hành và chương trình của bạn nhìn nhận về bộ nhớ. Hai quan điểm này khá khác biệt và sự khác biệt này là chìa khóa để hiểu cơ chế quản lý bộ nhớ.

	- Đầu tiên, có vài surprising news: không gian bộ nhớ mà hệ điều hành able sử dụng có thể lớn hơn đáng kể so với bộ nhớ vật lý thực sự được cài đặt trong máy tính của bạn. Điều này khả thi nhờ vào 1 phần của OS gọi là virtual memory (bộ nhớ ảo) và đây là một very sophisticated trick cho phép OS giả mạo các khối bộ nhớ không tồn tại bằng cách sử dụng một phần được dành riêng trên ổ cứng của bạn (phần không gian này thường được gọi là swap space hoặc swap file).

	- Không gian bộ nhớ ảo được chia thành hai phần chính:

		. Không gian nhân (the kernel space) - Đây là nơi mà hạt nhân OS được đặt; phần này của bộ nhớ không khả dụng cho các tiến trình hiện đang tồn tại trong hệ thống; cách duy nhất mà các tiến trình có thể giao tiếp với hạt nhân là thông qua việc kích hoạt các dịch vụ mà nó cung cấp; Note: không gian nhân thường bao gồm không chỉ kernel's code mà còn nhiều dữ liệu được sử dụng bởi kernel, chẳng hạn như buffers, caches, control block, ...

		. Không gian người dùng (the user space) - Đây là nơi mà các tiến trình tồn tại, làm việc và tương tác; phần này của bộ nhớ hoàn toàn truy cập được bởi kernel; OS có khả năng thao tác bộ nhớ của các tiến trình, nhưng ngược lại thì không - một tiến trình không thể truy cập bộ nhớ của kernel hoặc bộ nhớ được cấp phát cho các tiến trình khác - nếu nó cố gắng làm điều đó, một tình trạng gọi là protection fault sẽ xảy ra và tiến trình sẽ bị xóa khỏi bộ nhớ ngay lập tức; nói chung là tiến trình thì riêng, không có truy cập vào tiến trình khác được.


4.1.1.3
	- user space được chia đều giữa tất cả các tiến trình hiện đang tồn tại trong hệ thống. Tất nhiên, sự chia này rất dynamic (linh hoạt) - các tiến trình được tạo ra và hủy bỏ gần như không thể dự đoán. Hơn nữa, mỗi tiến trình có thể yêu cầu thêm bộ nhớ từ OS và có thể trả lại nó cho OS sau khi sử dụng. Vì bộ nhớ ảo được chia thành các trang, và các trang có thể được di chuyển tự do trong toàn bộ không gian địa chỉ, OS đáp ứng những yêu cầu này mà không ảnh hưởng đến tính toàn vẹn của các tiến trình khác và không làm tăng kích thước của các không gian chưa sử dụng.

	- Bạn không cần phải lo lắng về bất kỳ điều gì trong này - mọi thứ hoàn toàn tự động và hoàn toàn trong suốt.
		Ảnh:
			https://edube.org/learn/c-advanced/memory-and-strings-how-the-memory-is-used-and-how-to-deal-with-it-11

	- Process's space thường được chia thành bốn phần độc lập:

		. Text - Mặc dù tên của nó là dị nhma phần này lưu trữ code thực thi của chương trình.

		. Data - Đây là một khối bộ nhớ lưu trữ tất cả nonautomatic (static) data (dữ liệu không tự động (tĩnh)).

		. Stack - Một part mà grow và shrink vĩnh viễn của bộ nhớ lưu trữ automatic data.

		. Heap - Đây là một phần của bộ nhớ được thiết kế để lưu trữ dynamic data (dữ liệu động).

	- Note: Stack grow về hướng heap và heap grow về hướng stack.
		Ảnh:
			https://edube.org/learn/c-advanced/memory-and-strings-how-the-memory-is-used-and-how-to-deal-with-it-11

	- Đoạn code sau sẽ giúp bạn hiểu cách gán giá trị cho ba phần cuối cùng:

		int a;                             			static → data
		int main(void) {		
		    static int b;                  			static → data
		    int c;                         			automatic → stack
		    int *p = malloc(sizeof(int));  			p: automatic → stack
		    										*p: dynamic → heap
		    free(p);
		    return 0;
		}

	- Chúng tôi hy vọng bạn có thể giải thích tại sao stack liên tục thay đổi kích thước - mỗi lần gọi hàm đều làm cho stack mở rộng để tạo không gian cho biến cục bộ của hàm; khi rời khỏi hàm, kích thước của stack giảm tương ứng.

	- Như bạn có thể thấy, programmer - cũng chính là bạn - không thể quản lý bất kỳ phần bộ nhớ nào, ngoại trừ phần nằm trong heap. Các phần còn lại đều nằm ngoài sự kiểm soát của bạn.


4.1.1.4
	- C programming language cung cấp một bộ các hàm cơ bản giúp người dùng quản lý một bể nhớ được lưu trữ tại heap của tiến trình. Dưới đây là các hàm này:

		#include <stdlib.h>

		void *malloc(size_t size);
		void free(void *ptr);
		void *calloc(size_t nmemb, size_t size);
		void *realloc(void *ptr, size_t size);

	- Tuy nhiên có một điều cần rõ. Cơ chế mà chịu trách nhiệm cấp phát và giải phóng bộ nhớ là một black box. Cách hoạt động của nó khác nhau từ nền tảng này sang nền tảng khác và từ compiler này sang compiler khác. Ví dụ, bạn không nên giả định rằng hai lời gọi liên tiếp của malloc() sẽ trả về con trỏ đến các vùng bộ nhớ kề nhau. Hơn nữa, bạn cũng không thể giả định rằng lời gọi sau sẽ trả về một con trỏ lớn hơn so với lời gọi trước.

	- The allocator (Bộ cấp phát) (phần của runtime environment chịu trách nhiệm cho việc allocating and freeing - cấp phát và giải phóng bộ nhớ) là một phần mềm rất tinh tế: nó phải đảm bảo an toàn, nhanh chóng và thông minh. Một số C programming implementations cho phép các programmer thay thế allocator tích hợp sẵn bằng các thuật toán của họ. Ví dụ, môi trường gcc chứa bốn "hook" (một "hook" là một con trỏ đến một hàm tự động được gọi mỗi khi một sự kiện cụ thể xảy ra) được sử dụng để triển khai các chiến lược defined bởi người dùng để cấp phát, giải phóng, cấp phát lại và align các khối bộ nhớ (thêm thông tin tại đây: Memory Allocation Hooks).
		link:
			https://edube.org/learn/c-advanced/memory-and-strings-how-the-memory-is-used-and-how-to-deal-with-it-12

	- gcc cũng cung cấp một hàm có tên là mallopt() có thể sửa đổi một số cài đặt của allocator tích hợp sẵn (thêm thông tin tại đây: Malloc Tunable Parameters - link trên luôn).

	- Tất cả những tính năng này là các extensions cụ thể cho từng implementation, nên đừng mong chúng có thể portable. Chỉ có 4 hàm này đảm bảo có sẵn trong mọi môi trường.

	- Hàm malloc() cấp phát một khối bộ nhớ có kích thước được chỉ định bởi đối số:

		#include <stdlib.h>

		void *malloc(size_t size);

	- Chú ý: Kiểu size_t là một unsigned int đủ lớn để chỉ định kích thước tối đa của một thực thể (một khối bộ nhớ, một tệp, ...) có sẵn trong một môi trường cụ thể.

	- Hàm return một pointer đến khối bộ nhớ đã cấp phát thành công hoặc một NULL pointer trong trường hợp lỗi.

	- Khối bộ nhớ đã cấp phát không được khởi tạo bằng bất kỳ cách nào. Giả định an toàn nhất bạn có thể có ở đây là coi khối này như đã chứa đầy rác. Khởi tạo nó ngay lập tức.

	- Con trỏ được căn chỉnh để có thể lưu trữ một cách hiệu quả bất kỳ thực thể nào của các type chuẩn (được tích hợp sẵn).


4.1.1.5
	- Xem program sau:

		#include <stdio.h>
		#include <stdlib.h>

		int
		main (void)
		{
		  void *p = malloc (1);
		  unsigned long l = (unsigned long) p;
		  free (p);
		  printf ("%p\n", p);
		  int i;
		  for (i = 2; i <= 64; i <<= 1)
		    printf ("%02d -> %s\n", i, (l % i) ? "no" : "yes");
		  return 0;
		}

	- Chương trình này cấp phát một khối bộ nhớ nhỏ (nhỏ nhất có thể) và kiểm tra alignment (sự căn chỉnh) của con trỏ kết quả - nó cố gắng chia con trỏ cho 2, 4, 8, .. 32 và thông báo liệu phần dư có bằng 0 hay không.

	- Khi chương trình được biên dịch bởi CL compiler và chạy trên một nền tảng MS Windows 64-bit, output như sau:

		013372A8
		02 -> yes
		04 -> yes
		08 -> yes
		16 -> no
		32 -> no
		64 -> no

	- Như bạn có thể thấy, khối bộ nhớ này được căn chỉnh tốt để lưu trữ các giá trị kiểu double và long long int. Code tương tự khi được biên dịch bởi gcc compiler và chạy trong môi trường giống nhau tạo ra kết quả khác biệt đáng kể:

		00964FA0
		02 -> yes
		04 -> yes
		08 -> yes
		16 -> yes
		32 -> yes
		64 -> no

	- Code tương tự khi được biên dịch bởi trình biên dịch gcc trên nền tảng Raspberry Pi ra như sau:

		0xc54008
		02 -> yes
		04 -> yes
		08 -> yes
		16 -> no
		32 -> no
		64 -> no

	- Điều này đưa chúng ta đến kết luận rằng các allocators khác nhau rõ ràng là sử dụng các chiến lược khác nhau.


4.1.1.6
	- Hàm free() giải phóng (deallocates) 1 memory block mà trước đó được cấp phát bởi các hàm malloc() hoặc calloc():

		#include <stdlib.h>

		void free(void *ptr);

	- Note: Có một số hàm khác có khả năng cấp phát các khối bộ nhớ một cách ngầm định - chúng ta sẽ thảo luận sau.

	- Đừng quên rằng:
		
		. Con trỏ mà bạn sẽ truyền cho hàm free() phải giống đúng với con trỏ được nhận từ bộ cấp phát - mỗi byte đều quan trọng ở đây.
		
		. Đừng giải phóng cùng một khối nhiều lần.
		
		. Nếu đối số bằng NULL, hàm sẽ không thực hiện gì cả.
		
		. Một con trỏ đến khối bộ nhớ đã được giải phóng vẫn giữ giá trị của nó (it isn't set to NULL), nhưng nó không còn valid nữa - đừng sử dụng nó.

	- Hàm không trả về giá trị gì, vì vậy bạn sẽ không thể phát hiện bất kỳ lỗi nào xảy ra do việc gọi hàm này.

	- Note: Mọi bộ nhớ được cấp phát mà không được giải phóng một cách rõ ràng sẽ tự động được giải phóng khi chương trình của bạn kết thúc. Điều này tốt, nhưng không có nghĩa là bạn có quyền từ chối việc giải phóng bộ nhớ đã cấp phát. Nếu chương trình của bạn được thiết kế để xử lý dữ liệu phức tạp và sẽ làm việc trong thời gian dài, mỗi malloc() không được đi kèm với free() sẽ gây ra memory leak.

	- Rò rỉ bộ nhớ là một trong những source code errors khó tìm kiếm nhất. Khi chương trình của bạn lớn và phức tạp, việc tìm kiếm chúng giống như tìm kiếm một chiếc kim trong đống rơm. Hãy cẩn thận.

	- Có các tools được thiết kế để chẩn đoán các vấn đề này như Valgrind, được sử dụng trong môi trường Unix/Linux, và Rational Purify cho MS Windows. Đừng nghĩ về chúng như là các công cụ được sử dụng thường xuyên. Nếu bạn cần sử dụng chúng, điều đó rõ ràng có nghĩa là code của bạn is faulty. Sad but true.

	- Hàm calloc() là cousin dễ hiểu hơn của hàm malloc() đã được thảo luận trước đó:

		#include <stdlib.h>

		void *calloc(size_t nmemb, size_t size);

	- Nó hoạt động gần giống như malloc() (C language implementation của bạn có thể sử dụng malloc() để triển khai calloc()) nhưng:
		
		. Kích thước khối bộ nhớ được chỉ định dưới dạng một cặp giá trị: số lượng thực thể (tên là members ở đây) để cấp phát và kích thước của mỗi thực thể (member).
		
		. Toàn bộ khối bộ nhớ cấp phát được điền bằng giá trị 0 trước khi trả về.
		
		. Khối được aligned theo cách giống như malloc().


4.1.1.7
	- Xem xét program sau. Code hiển thị sự khác biệt giữa malloc() và calloc().

		#include <stdio.h>
		#include <stdlib.h>
		#define  N  5

		void
		print (float *t, int n)
		{
		  int i;
		  for (i = 0; i < n; i++)
		    printf ("%f; ", t[i]);
		  printf ("\n");
		}

		int
		main (void)
		{
		  float *t1 = malloc (N * sizeof (float));
		  float *t2 = calloc (N, sizeof (float));
		  print (t1, N);
		  print (t2, N);
		  free (t1);
		  free (t2);
		  return 0;
		}

	- Cả hai hàm đều cấp phát một khối bộ nhớ cùng kích thước (dòng 13 và 14). Cả hai khối đều được giải phóng bởi hàm free() (dòng 17 và 18).

	- Tuy nhiên, sự khác biệt khả quan nhất hiển thị trong đầu ra. Đây là kết quả chúng ta nhận được từ code khi được biên dịch bởi gcc và chạy hai lần trên Linux:

		0.000000; 0.000000; 14278959962015333082570753203765248.000000;

		0.000000; 0.000000;

		0.000000; 0.000000; 0.000000; 0.000000; 0.000000;



		0.000000; 0.000000; -203024357620850416598835527680.000000;

		0.000000; 0.000000;

		0.000000; 0.000000; 0.000000; 0.000000; 0.000000;

	- Chúng tôi nghĩ rằng đây là một lý lẽ rất quan trọng để đánh giá khả năng sử dụng của hàm calloc().


4.1.1.8
	- Hàm realloc() thay đổi kích thước của khối bộ nhớ đã được cấp phát trước đó:

		#include <stdlib.h>

		void *realloc(void *ptr, size_t size);

	- Hàm expects các đối số sau:
		
		. Một con trỏ đến khối bộ nhớ từ malloc(), calloc(), hoặc realloc().
		
		. Kích thước mới của khối; nếu kích thước lớn hơn kích thước ban đầu, toàn bộ nội dung của khối được preserved, nhưng bộ nhớ mới thêm vào không được khởi tạo; nếu kích thước nhỏ hơn kích thước ban đầu, phần còn lại của khối giữ giá trị trước đó; nếu kích thước mới được chỉ định là không, invocation này có cùng effect như free(ptr).
	  
	- Hàm returns:
		
		. Một con trỏ đến khối bộ nhớ mới được cấp phát với kích thước mong muốn nếu thành công (khối bộ nhớ cũ được giải phóng trong im lặng).
		
		. Một con trỏ NULL nếu có lỗi (khối bộ nhớ cũ được giữ nguyên).

	- Program ví dụ trong trình soạn thảo mô tả hành vi của hàm realloc():

		#include <stdio.h>
		#include <stdlib.h>

		void
		print (float *t, int n)
		{
		  int i;
		  for (i = 0; i < n; i++)
		    printf ("%f; ", t[i]);
		  printf ("\n");
		}

		int
		main (void)
		{
		  float *t = malloc (4 * sizeof (float));
		  int i;

		  for (i = 0; i < 4; i++)
		    t[i] = i + 1.;
		  print (t, 4);
		  t = realloc (t, 5 * sizeof (float));
		  print (t, 5);
		  t = realloc (t, 3 * sizeof (float));
		  print (t, 3);
		  free (t);
		  return 0;
		}

	
		. line 12: Chúng ta cấp phát một khối bộ nhớ đủ dài để lưu trữ bốn số thực.
	
		. line 15: Chúng ta khởi tạo tất cả các giá trị.
	
		. line 17: Bây giờ chúng ta chắc chắn rằng vòng lặp khởi tạo đã làm việc tốt.
	
		. line 18: Chúng ta mở rộng khối để có thể store one additional float.
	
		. line 19: Nội dung trước đó đã tồn tại? Yes.
	
		. line 20: Bây giờ chúng ta shrink khối - giờ nó chứa ba số thực.
	
		. line 21: Ba số thực có bị thay đổi không? No.
	
		. line 22: clean up after yourself (tự dọn dẹp)

	- Chúng ta quan sát output sau cùng từ chương trình:

	1.000000; 2.000000; 3.000000; 4.000000;
	1.000000; 2.000000; 3.000000; 4.000000; 0.000000;
	1.000000; 2.000000; 3.000000;


4.1.1.9
	- Trước đó, chúng ta đã nói rằng những hàm này được thiết kế để quản lý bộ nhớ được cấp phát bởi heap, nhưng đừng quên rằng có nhiều hàm có thể cấp phát bộ nhớ một cách im lặng. Bộ nhớ này phải được giải phóng một cách rõ ràng, trừ khi bạn muốn trải qua những destructive effects của rò rỉ bộ nhớ.

	- Một trong những hàm này là strdup():

		#include <string.h>

		char *strdup(char *s);

	- Hàm này tạo ra một bản sao (duplicate) của một string được truyền qua một đối số duy nhất. Điều này có nghĩa là hàm:
		
		. Cấp phát một khối bộ nhớ mới có kích thước bằng length of source string plus 1.
		
		. Sao chép string gốc vào khối bộ nhớ mới cấp phát.
		
		. Trả về con trỏ đến khối mới.

	- Khối bộ nhớ này nên được giải phóng ngay khi không còn cần thiết nữa.

	- Chương trình dưới đây mô tả cách strdup() hoạt động:

		#include <stdio.h>
		#include <string.h>
		#include <stdlib.h>

		int main(void) {
		  char *s1 = "string";
		  char *s2 = strdup(s1);
		  printf("%s\n", strcmp(s1, s2) ? "not equal" : "equal");
		  printf("%s\n", s1 == s2 ? "equal" : "not equal");
		  free(s2);
		  return 0;
		}

	- Chương trình outputs các dòng sau đến stdout:

		equal
		not equal

	- Điều này rõ ràng nói rằng:
		
		. Nội dung của s1 giống như s2.
		
		. s1 lưu trữ nội dung của mình trong một vùng bộ nhớ khác với s2.

	- Điều này làm đúng những gì cần phải được thể hiện.


4.1.1.10
	- Các hàm khác thuộc loại này là asprintf() và vasprintf():

		int asprintf(char **strp, char *fmt, ...);
		int vasprintf(char **strp, char *fmt, va_list ap);

	- Các hàm thực hiện công việc tương tự sprintf() và vsprintf() (in một formatted string vào bộ nhớ được trỏ tới bởi một trong các đối số), nhưng asprintf() và vasprintf() tự cấp phát bộ nhớ và địa chỉ kết quả được gán cho đối số đầu tiên (do đó, kiểu của nó là char**, không phải char*).

	- Các hàm này không phải là một phần của C language standard functions set, nhưng chúng có sẵn trong môi trường gcc và clang. Chúng tôi tin rằng việc reimplement một trong những hàm này sẽ là một bài tập và bài thực hành tốt cho bạn.

	- Trước khi bắt đầu công việc, chúng ta cần làm quen với hai hàm sau đây:

		int snprintf(char *str, size_t size, char *format, ...);
		int vsnprintf(char *str, size_t size, char *format, va_list ap);

	- Cả hai hàm này in formatted string vào bộ nhớ được trỏ bởi đối số đầu tiên, nhưng không chứa nhiều byte hơn được chỉ định trong đối số thứ hai. Vì các hàm trả về độ dài đầy đủ của string kết quả, các invocations sau:

		a = snprintf(NULL, 0, format);
		b = vsnprintf(NULL, 0, format, ap);

	trả về độ dài của string đầu ra có thể tưởng tượng mà không tạo ra nó.

	- Do đó, chúng ta không cần phải cấp phát trước một khối bộ nhớ rất lớn để lưu trữ tất cả các chuỗi có thể tưởng tượng được.

	- Bây giờ, chúng ta đã sẵn sàng để triển khai phiên bản của chúng ta cho hàm asprintf().


4.1.1.11
	- Dưới đây là một possible solution. Xem code:

		#include <stdio.h>
		#include <stdlib.h>
		#include <stdarg.h>

		int
		asprintf (char **buf, char *frm, ...)
		{
		  va_list var;
		  va_start (var, frm);
		  int size = vsnprintf (NULL, 0, frm, var);
		  *buf = calloc (size + 1, 1);
		  va_end (var);
		  va_start (var, frm);
		  vsprintf (*buf, frm, var);
		  va_end (var);
		  return size;
		}

		int
		main (void)
		{
		  char *msg;
		  asprintf (&msg, "Mary %s %c littl%x lamb.", "had", 'a', 14);
		  printf ("%s\n", msg);
		  free (msg);
		  return 0;
		}

		
		. line 5: Hàm này nhận một con trỏ đến con trỏ char để lưu địa chỉ của khối bộ nhớ mới được cấp phát.
		
		. line 6: Chúng ta khai báo một variadic list (danh sách biến)...
		
		. line 7: ... và sử dụng nó để catch các phần biến của danh sách đối số.
		
		. line 8: Chúng ta gọi vsnprintf() để tìm độ dài của string kết quả.
		
		. line 9: Biết độ dài, chúng ta có thể cấp phát bộ nhớ một cách chính xác (lưu ý nơi con trỏ được lưu trữ).
		
		. line 10: Chúng ta kết thúc processing variadic list ở đây và...
		
		. line 11: ... chúng ta bắt đầu process danh sách again...
		
		. line 12: ... chuyển nó cho vsprintf() thực hiện actual định dạng.
		
		. line 13: Chúng ta kết thúc công việc với variadic list hoàn toàn.
		
		. line 14: Chúng ta return độ dài của string kết quả (như các hàm trong printf() family làm).

	- Output của programm như sau:

		Mary had a little lamb.


4.2.1.1 Memory and strings – manipulating memory blocks
	- Ngoài các hàm đã thảo luận trong phần trước, C programming language còn cung cấp một wide range of functions được thiết kế để thao tác bộ nhớ và nội dung bộ nhớ. Chúng ta có thể chia chúng thành 4 nhóm:
		
		. copying;
		
		. setting (filling);
		
		. comparing;
		
		. searching.

	- Đừng quên rằng tất cả những hàm này xem xét bộ nhớ như một chuỗi các byte liên tục, amorphous (vô định hình). Chúng không phân biệt giữa các biến được khai báo tĩnh và các khối bộ nhớ được cấp phát động. Chúng không chú ý đến ranh giới mảng cũng như các trường của cấu trúc. Chúng cũng không nhận biết kích thước của biến, vì chúng chỉ hiểu địa chỉ và không quan tâm đến bất cứ điều gì khác.

	- Điều này khiến chúng rất mạnh mẽ và đồng thời rất nguy hiểm.


4.2.1.2
	- Hàm sao chép cơ bản nhất là memcpy():

		#include <string.h>

		void *memcpy(void *dest, void *src, size_t n);

	- Hàm này sao chép n byte từ địa chỉ được trỏ đến bởi src đến địa chỉ được trỏ đến bởi dest và không trả về gì.

	- Trong trường hợp đơn giản nhất, hàm có thể coi như là một phiên bản thay thế cho toán tử gán. Note: hàm giữ nguyên thứ tự của các đối số được sử dụng bởi toán tử gán kinh điển: destination đứng trước source, như sau:

		dest = src;

	- Dưới đây là ví dụ:

		#include <string.h>
		#include <stdio.h>

		int main(void) 
		{
		  double d1 = 1234.5678, d2 = 0.;

		  memcpy(&d2, &d1, sizeof(double));
		  printf("%f\n", d2);
		  return 0;
		}

	- Hàm memcpy() sao chép nội dung của biến d1 vào vị trí bộ nhớ được chiếm bởi biến d2 (để ý các toán tử &!). Số byte được sao chép được xác định bởi toán tử sizeof - nó có vẻ là phương pháp phổ quát và an toàn nhất để đếm số byte cần sao chép.

	- Kết quả của chương trình là:

		1234.567800


4.2.1.3
	- Tất nhiên, memcpy() có thể làm nhiều hơn. Nó có thể sao chép các tổ hợp dữ liệu phức tạp như structure và array, hoặc thậm chí là array of structures và ngược lại.

	- Xem code:

		#include <string.h>
		#include <stdio.h>

		typedef struct
		{
		  int i;
		  char c;
		} str_t;

		int
		main (void)
		{
		  str_t tab1[5], tab2[5];
		  int i;

		  for (i = 0; i < 5; i++)
		    {
		      tab1[i].i = i;
		      tab1[i].c = 'a' + i;
		    }

		  memcpy (tab2, tab1, sizeof (tab2));
		  for (i = 0; i < 5; i++)
		    printf ("%d %c\n", tab2[i].i, tab2[i].c);
		  return 0;
		}

	
	- tab1 bao gồm năm structures kiểu str_t. Hàm memcpy() sao chép mảng như một toàn bộ và đặt bản sao tại địa chỉ chiếm bởi mảng tab2.

	- Chúng ta không cần sử dụng toán tử & để có được con trỏ ở đây - tên mảng luôn là một con trỏ đến phần tử đầu tiên của nó.

	- Kết quả của chương trình là:

		0 a
		1 b
		2 c
		3 d
		4 e


4.2.1.4
	- Không có rắc rối gì khi sử dụng hàm memcpy() để chỉ sao chép một phần của một mảng hoặc cấu trúc.

	- Xem code:

		#include <string.h>
		#include <stdio.h>

		typedef struct
		{
		  int i;
		  char c;
		} str_t;

		int
		main (void)
		{
		  str_t tab1[4], tab2[4];
		  int i;

		  for (i = 0; i < 4; i++)
		    {
		      tab1[i].i = i;
		      tab1[i].c = 'a' + i;
		    }

		  memcpy (tab2 + 2, tab1, 2 * sizeof (str_t));
		  memcpy (tab2, tab1 + 2, 2 * sizeof (str_t));
		  for (i = 0; i < 4; i++)
		    printf ("%d %c\n", tab2[i].i, tab2[i].c);
		  return 0;
		}

	- Chúng ta sử dụng hàm để đổi chỗ hai phần của tab1. Lưu ý cách chúng ta chỉ định nguồn và đích cho cả hai lời gọi và cách chúng ta xác định kích thước của các khối được sao chép. Biểu thức:

		tab1 + 2

	đánh giá địa chỉ của phần tử thứ ba của tab1 nhờ vào phương thức được sử dụng để khai báo mảng:

		str_t tab1[4];

	- Thêm 2 vào địa chỉ của mảng đưa chúng ta đến phần tử thứ ba.

	- Kết quả của chương trình là:

		2 c
		3 d
		0 a
		1 b


4.2.1.5
	- Bất kể ưu điểm của nhiều trường hợp sử dụng memcpy(), hàm này không thể xử lý một trường hợp cụ thể - nó có thể có hành vi lạ lùng khi cả các khối nguồn và đích trùng lấp nhau (note: các ví dụ trước của chúng tôi đã cho thấy cả hai khu vực này hoàn toàn riêng biệt).

	- Xem code:

		#include <string.h>
		#include <stdio.h>

		void
		print (char *s, int n)
		{
		  int i;
		  for (i = 0; i < n; i++)
		    printf ("%c", s[i]);
		  printf ("\n");
		}

		int
		main (void)
		{
		  char a[4] = { 'a', 'b', 'c', 'd' }, b[4], c[4];

		  memcpy (b, a, 4);
		  memcpy (c, b, 4);
		  printf ("\n");
		  memcpy (b, b + 1, 3);
		  memcpy (c + 1, c, 3);
		  print (b, 4);
		  print (c, 4);
		  return 0;
		}

	- Mảng a được sao chép bằng cách tạo ra hai bản sao giống nhau có tên là b và c. Tiếp theo, ba phần tử đầu tiên của mảng b được sao chép từ đầu của mảng đến phần tử thứ hai (note: đây là điều chúng ta gọi là overlap). Tương tự, ba phần tử cuối cùng của mảng c được sao chép đến đầu của mảng.

	- Chúng tôi cần cảnh báo bạn rằng kết quả của chương trình phụ thuộc mạnh mẽ vào compiler được sử dụng để xây dựng executable code.

	- Chúng tôi đã sử dụng gcc 4.9.3 và đây là những gì chúng tôi nhận được:

		bcdd
		aaac

	- Đó không phải là điều tốt, phải không? Kết quả đầu tiên là ổn, nhưng kết quả thứ hai không trông như chúng tôi mong đợi. Chúng tôi muốn thấy kiểu như sau:

		aabc

	- Thật không may, hàm memcpy() không đủ thông minh để đáp ứng kỳ vọng của chúng tôi. Chúng ta cần sử dụng một cái gì đó khác, vì vậy hãy nhớ không sử dụng memcpy() trong những trường hợp như vậy.


4.2.1.6
	- Đây là cousin thông minh hơn của memcpy() - memmove():

		#include <string.h>

		void *memmove(void *dest, void *src, size_t n);

	- Hàm này sao chép n byte từ địa chỉ được trỏ đến bởi src đến địa chỉ được trỏ đến bởi dest và không trả về gì. Hơn nữa, nó có thể detect khi cả hai khối bộ nhớ overlap và thực hiện hành động tương ứng.

	- Xem code:

		#include <string.h>
		#include <stdio.h>

		void
		print (char *s, int n)
		{
		  int i;
		  for (i = 0; i < n; i++)
		    printf ("%c", s[i]);
		  printf ("\n");
		}

		int
		main (void)
		{
		  char a[4] = { 'a', 'b', 'c', 'd' }, b[4], c[4];

		  memcpy (b, a, 4);
		  memcpy (c, b, 4);
		  memmove (b, b + 1, 3);
		  memmove (c + 1, c, 3);
		  print (b, 4);
		  print (c, 4);
		  return 0;
		}

	- Đây là code giống như trước đó, nhưng hai lời gọi memcpy() đã được thay thế bằng memmove():

		bcdd 
		aabc

	- Yes, đây chính xác là điều chúng ta muốn.


4.2.1.7
	- Hàm memccpy() không thể xử lý các overlapping blocks, nhưng có thể thực hiện một điều thú vị hơn:

		#include <string.h>

		void *memccpy(void *dest, void *src, int c, size_t n);

	- Hàm này sao chép không quá n byte từ địa chỉ được trỏ đến bởi src đến địa chỉ được trỏ đến bởi dest, nhưng dừng ngay sau khi bất kỳ byte nào trong số các byte đã sao chép bằng c.

	- Hàm trả về con trỏ đến byte trong dest ngay sau c, hoặc NULL nếu không có byte đó.

	- Note: hàm tìm kiếm một byte - không phải bất cứ điều gì khác. Mặc dù tham số c được khai báo là một int, hàm sử dụng giá trị của nó được chuyển đổi thành kiểu unsigned char.

	- Xem code:

		#include <string.h>
		#include <stdio.h>

		int
		main (void)
		{
		  char s1[] = { 'a', 'b', 'c', 'd' };
		  char s2[] = { 'x', 'x', 'x', 'x' };
		  char *p = memccpy (s2, s1, 'c', 4);
		  printf ("%c%c%c%c %c\n", s2[0], s2[1], s2[2], s2[3], *p);
		  return 0;
		}

	- Hàm memccpy() sao chép không quá bốn ký tự (bytes) từ s2 đến s1 và dừng khi byte đầu tiên trong số các byte đã sao chép bằng 'c' (byte 'c' cũng được sao chép).

	- Kết quả của hàm trỏ đến phần tử đầu tiên của s2 sau 'c'.

	- Chương trình xuất dòng sau:

		abcx x


4.2.1.8
	- Chúng tôi đã modified code một chút - xem code:

		#include <string.h>
		#include <stdio.h>

		int
		main (void)
		{
		  short int t1[] = { 1, 2, 3 };
		  short int t2[] = { 0, 0, 0 };
		  char *p = memccpy (t2, t1, 0, sizeof (t1));
		  printf ("%d %d %d %d\n", t2[0], t2[1], t2[2], *p);
		  return 0;
		}

	- Bây giờ, cả hai mảng đều bao gồm các phần tử kiểu short int, không phải là ký tự. Chúng tôi đã rút gọn chúng một chút, nhưng phần còn lại của code vẫn giống như trước.

	- Program's output là:

		1 0 0 0

	- Bạn có thể nhìn thấy không? The copying không reach đến cuối mảng t1. Tại sao? Không có phần tử nào bằng không trong mảng t1. Làm thế nào có thể việc sao chép đã bị dừng?

	- Đúng là không có giá trị kiểu short int nào bằng không trong t1, nhưng có một byte bằng không. Đó là byte thứ hai của phần tử đầu tiên (giả sử nền tảng đích sử dụng kiểu chuẩn little-endian).

	- Đừng quên đặc điểm cơ bản này của memccpy().


4.2.1.9
	- Hàm memset() được thiết kế để điền một khối bộ nhớ bằng một byte có giá trị được chọn:

		#include <string.h>
		void *memset (void *s, int c, size_t n);

	- Hàm set giá trị của n byte bắt đầu từ con trỏ s bằng giá trị được xác định bởi c (note: mặc dù c được khai báo là một số nguyên, nhưng hàm sử dụng một unsigned char, không phải là một số nguyên).

	- Hàm returns nothing.

	- Dưới đây là ví dụ đơn giản về việc sử dụng hàm - xem code:

		#include <string.h>
		#include <stdio.h>

		int
		main (void)
		{
		  char t[4];

		  t[3] = '\0';
		  memset (t, '*', 3);
		  printf ("%s\n", t);
		  return 0;
		}

		
		. line 7: chúng ta đặt ký tự null ở cuối mảng;
		
		. line 8: chúng ta đặt tất cả các phần tử còn lại thành '*'.

	- Kết quả của chương trình là:

		***


4.2.1.10
	- Như đã làm trước đó, chúng ta sẽ thay đổi kiểu phần tử. Code hiện có dạng như sau:

		#include <string.h>
		#include <stdio.h>

		int
		main (void)
		{
		  short int t[4];

		  memset (t, 1, sizeof (t));
		  printf ("%d %d %d %d\n", t[0], t[1], t[2], t[3]);
		  return 0;
		}

	- Kết quả của chương trình là:

		257 257 257 257

	Why?

	- Mỗi phần tử t chiếm hai byte. Mỗi byte này đã được điền với giá trị 1. Kết quả là, tất cả các phần tử có cùng giá trị bằng 0x0101 trong hexadecimal.

	- Thật không may, hàm memcpy() không đủ thông minh để đáp ứng kỳ vọng của chúng ta. Chúng ta cần sử dụng cái khác, vì vậy nhớ không sử dụng memcpy() trong những trường hợp như này.

	- Và đây chính là giá trị 257.

	- Note: một số C programming language implementations cung cấp một hàm liên quan có tên là bzero(), thứ mà chỉ có hai tham số được thiết kế để điền một khối bộ nhớ với các byte bằng không. Hàm này không phải là một phần của C language standard. 

	- Hàm memcmp() so sánh n byte của hai khu vực bộ nhớ, từng byte một:

		#include <string.h>

		int memcmp (void *s1, void s2, size_t n);

	- Hàm returns:
		
		. 0 khi cả hai khu vực chứa n byte giống nhau;
		
		. một value > 0 khi byte khác biệt đầu tiên được tìm thấy (được treated as unsigned char) lớn hơn bên trong khu vực được trỏ đến bởi s1 so với bên trong khu vực được trỏ đến bởi s2;
		
		. một value < 0 trong trường hợp còn lại.

	- Nói cách khác, hàm returns a value whose sign is the same as the sign of the difference between hai byte khác biệt đầu tiên trong cả hai khu vực. 

	- Ví dụ sẽ làm sáng tỏ điều này, hy vọng thế.


4.2.1.11
	- Nhìn example:

		#include <string.h>
		#include <stdio.h>

		typedef char tab[10];

		int
		main (void)
		{
		  tab t1, t2, t3;

		  memset (t1, 'A', sizeof (t1));
		  memset (t2, 'A', sizeof (t2));
		  memset (t3, 'A', sizeof (t3));
		  t3[4] = 'Z';

		  printf ("%d\n", memcmp (t1, t2, sizeof (tab)));
		  printf ("%d\n", memcmp (t3, t2, sizeof (tab)));
		  printf ("%d\n", memcmp (t2, t3, sizeof (tab)));
		  return 0;
		}

	
		. line 7: Chúng ta khai báo ba mảng char với mỗi mảng chứa mười phần tử.
	
		. line 9 to 11: Chúng ta điền các mảng với ký tự 'A'.
	
		. line 12: Chúng ta đặt một 'Z' duy nhất vào phần tử thứ năm của mảng t3.

	- The program's possible output là:

		0
		25
		-25

	
		. 0 có nghĩa là sizeof(tab) byte đầu tiên của các mảng t1 và t2 chứa giá trị giống nhau;
	
		. 25 có nghĩa là byte khác biệt đầu tiên lớn hơn trong t3 so với t2; 

		. -25 có nghĩa tương tự, nhưng do thứ tự đảo ngược của các đối số, kết quả đã thay đổi dấu.

	- Thật không may, không có cách đơn giản hơn để tìm vị trí của các phần tử khác biệt.


4.2.1.12
	- Đương nhiên, bạn có thể sử dụng hàm memcmp() để so sánh bất cứ thứ gì, không chỉ là mảng, như code sau:

		#include <string.h>
		#include <stdio.h>

		typedef struct
		{
		  int i;
		  float f;
		} str_t;

		int
		main (void)
		{
		  str_t s1 = { 1, 1.23 }, s2 =
		  {
		  1, 3.21};

		  printf ("%d\n", memcmp (&s1, &s1, sizeof (str_t)));
		  printf ("%d\n", memcmp (&s1, &s2, sizeof (str_t)));
		  return 0;
		}

	- Thật không may, nó sẽ không đưa ra bất kỳ kết luận nào khác ngoài việc xác định xem hai cấu trúc này có chứa các giá trị giống nhau hay không. Không thể suy luận được thông tin nào khác.

	- Chương trình ví dụ xuất ra hai dòng sau đây (kết quả của bạn có thể khác nhau, nhưng dấu sẽ giống nhau):

		0
		80

	- Dòng đầu tiên là dễ hiểu - mọi cấu trúc đều bằng chính nó.

	- Dòng thứ hai nói rằng các cấu trúc không giống nhau, nhưng kết quả không nói gì về việc cấu trúc nào chứa trường lớn hơn. Như bạn có thể thấy, the result is misleading.


4.2.1.13
	- Hàm memchr() scans n byte đầu tiên trỏ bởi s, tìm kiếm giá trị được truyền trong c:

		#include <string.h>

		void *memchr (const void *s, int c, size_t n);

	- Note: như đã nói trước đó, giá trị c được xem xét như là một unsigned char.

	- Hàm returns:

		. Một con trỏ đến một byte chứa sự xuất hiện đầu tiên của giá trị c.

		. NULL nếu không có byte nào mang giá trị đó.

	- Xem code:

		#include <string.h>
		#include <stdio.h>


		void
		print (char *b, char *p)
		{
		  if (p)
		    printf ("'%c' [%ld]\n", *p, p - b);
		  else
		    printf ("(null)\n");
		}

		int
		main (void)
		{
		  char abc['Z' - 'A' + 1];
		  int i;

		  for (i = 'A'; i <= 'Z'; i++)
		    abc[i - 'A'] = i;

		  print (abc, memchr (abc, 'S', sizeof (abc)));
		  print (abc, memchr (abc, 'S', 10));
		  print (abc, memchr (abc, 's', sizeof (abc)));
		  return 0;
		}

	
		. line 5: the helper function nhận hai con trỏ kiểu char *; nếu đối số thứ hai không phải là NULL, hàm in ra một char mà nó trỏ đến, cũng như khoảng cách giữa nó và đầu mảng được truyền bởi đối số thứ nhất; khi đối số thứ hai là NULL, hàm in ra (null).
	
		. line 13: chúng ta khai báo một mảng char có 26 phần tử;
	
		. line 16: chúng ta điền mảng với bảng chữ cái Latin;
	
		. line 19 đến 21: chúng ta thực hiện một số tìm kiếm bằng cách sử dụng memchr() và output kết quả.


4.2.1.14
	- Một số C language implementations bao gồm một hàm được gọi là memrchr():

		#include <string.h>

		void *memrchr (const void *s, int c, size_t n);

	- Hàm này thực hiện công việc tương tự như memchr() nhưng bắt đầu tìm kiếm từ cuối của khối được trỏ đến bởi s và có kích thước là n.

	- Hàm này không phải là một phần của C language standard.


4.3.1.1 Memory and strings – searching strings
	- Cùng với những hàm được thiết kế để tìm kiếm trong bộ nhớ vô định hình, C programming language chứa một số hàm dành cho việc làm việc với strings. Sự khác biệt nhỏ là những hàm này không cần các đối số chỉ định chiều dài của khối bộ nhớ, vì chiều dài có thể suy ra từ vị trí của ký tự null ('\0'). Hơn nữa, những hàm này có khả năng thao tác trên chuỗi một cách có ích trong xử lý văn bản thực tế.

	- Hàm đơn giản nhất trong số những hàm này là strchr():

		#include <string.h>

		char *strchr(const char *s, int c);

	- Hàm này tìm kiếm string được trỏ đến bởi s để tìm ký tự c (note: bất kỳ kiểu tham số nào, hàm đều tìm kiếm một char, không phải một int).

	- Hàm returns con trỏ đến ký tự được tìm thấy hoặc NULL nếu string không chứa ký tự đó.

	- Lưu ý: hàm tìm kiếm string từ đầu đến cuối or, to be more pictorial, từ trái sang phải or, to be more precise, từ các chỉ số thấp đến các chỉ số cao.


4.3.1.2
	- Dưới đây là một ví dụ đơn giản về cách sử dụng hàm - xem code:

		#include <string.h>
		#include <stdio.h>

		void
		print (char *s, char *p)
		{
		  if (p == NULL)
		    printf ("(null)\n");
		  else
		    printf ("[%ld]\n", p - s);
		}

		int
		main (void)
		{
		  char *str = "Mary had a little lamb";
		  print (str, strchr (str, 'c'));
		  print (str, strchr (str, 'a'));
		  return 0;
		}

	- Chúng ta sử dụng hàm print() để đánh giá và xuất ra một chỉ số của ký tự được tìm thấy (sự khác biệt giữa vị trí của ký tự và đầu string). Nếu ký tự không có, hàm sẽ xuất ra (null).

	- Output của chương trình minh họa là:

		(null)
		[1]


4.3.1.3
	- Hàm strchr() có một sibling thực hiện công việc tương tự nhưng từ phía cuối của chuỗi:

		#include <string.h>

		char *strrchr(const char *s, int c);

	- Hàm strrchr() sử dụng các đối số giống như strchr() và trả về kết quả tương tự, nhưng bắt đầu tìm kiếm từ cuối string, đi từ các chỉ số cao đến thấp.

	- Chúng ta đã thay đổi ví dụ của mình, chỉ thêm vào đó hai chữ 'r' - this is how it look (xem code):

		#include <string.h>
		#include <stdio.h>

		void
		print (char *s, char *p)
		{
		  if (p == NULL)
		    printf ("(null)\n");
		  else
		    printf ("[%ld]\n", p - s);
		}

		int
		main (void)
		{
		  char *str = "Mary had a little lamb";
		  print (str, strrchr (str, 'c'));
		  print (str, strrchr (str, 'a'));
		  return 0;
		}

	- The program's output là:

		(null)
		[19]

	- So sánh kết quả từ đây với chương trình trước đó.


4.3.1.4
	- Mặc dù cả hai hàm trước chỉ tìm kiếm sự xuất hiện đầu tiên của ký tự đã chỉ định, chúng có thể dễ dàng được harnessed để tìm kiếm mọi nơi mà ký tự được đặt trong string.

	- Dưới đây là cách chúng ta thực hiện điều này - xem code:

		#include <string.h>
		#include <stdio.h>

		void
		print (char *s, char *p)
		{
		  if (p == NULL)
		    printf ("(null)\n");
		  else
		    printf ("[%ld]\n", p - s);
		}

		int
		main (void)
		{
		  char *str = "Mary had a little lamb", *p = strchr (str, 'a');
		  while (p)
		    {
		      print (str, p);
		      p = strchr (p + 1, 'a');
		    }
		  return 0;
		}

	- Note: chúng ta kiểm tra kết quả từ invocation trước đó (line 17) và nếu nó không phải là NULL, chúng ta sử dụng nó một lần nữa (tăng lên một) để tiếp tục tìm kiếm phần còn lại của string.

	- Chương trình sẽ outputs các dòng sau lên stdout:

		[1]
		[6]
		[9]
		[19]


4.3.1.5
	- Nếu bạn muốn thực hiện một tìm kiếm qua một string để tìm một substring thay vì một ký tự đơn, bạn có thể sử dụng hàm sau:

		#include <string.h>

		char *strstr (char *haystack, char *needle);

	- Hàm strstr() (chú ý đến tên của các tham số - chúng rất suggestive phải không?) cố gắng tìm sự xuất hiện đầu tiên của string được trỏ đến bởi đối số thứ hai bên trong string được trỏ đến bởi đối số đầu tiên.

	- Hàm returns một con trỏ đến substring được tìm thấy, hoặc NULL nếu không có.


4.3.1.6
	- Chương trình mẫu của chúng ta sẽ tìm kiếm chuỗi "ife" trong code sau:

		#include <string.h>
		#include <stdio.h>

		void
		print (char *s, char *p)
		{
		  if (p == NULL)
		    printf ("(null)\n");
		  else
		    printf ("+%ld\n", p - s);
		}

		int
		main (void)
		{
		  char *rhyme = "They all ran after the farmer's wife,"
		    "Who cut off their tails with a carving knife,"
		    "Did you ever see such a sight in your life,";
		  char *p = strstr (rhyme, "ife");
		  while (p)
		    {
		      print (rhyme, p);
		      p = strstr (p + 1, "ife");
		    }
		  return 0;
		}

	và khi nó thành công, nó sẽ in ra index của substring được tìm thấy.

	- The program's output như sau:

		+33
		+78
		+121


4.3.1.7
	- Hàm strtok() có vẻ tương tự với strstr(), nhưng công việc nó thực hiện phức tạp hơn nhiều:

		#include <string.h>

		char *strtok(char *str, const char *delim);

	- Hàm cố gắng chia chuỗi str thành một số phần được gọi là token (một token là một từ hoặc string ký tự khác cần được xử lý nguyên tố). Token trong text được phân tách bởi các delimiters (dấu phân tách) (nói cách khác, tất cả các substring tồn tại giữa các dấu phân tách đều là các token, ví dụ, nếu một khoảng trắng là một dấu phân tách, string sau chứa 3 token: "It’s 3 PM").

	- Hàm strtok() chia string theo cách rất phức tạp - có thể cần nhiều hơn một invocation để tìm tất cả các token.

	- Quy trình thông thường sử dụng hàm như sau:
	
		. Gọi hàm lần đầu tiên bằng cách chuyển con trỏ đến string chứa văn bản cần chia và con trỏ đến string chứa tất cả các delimiters xuất hiện trong văn bản.
	
		. Hàm trả về con trỏ đến token đầu tiên được tìm thấy hoặc NULL nếu không có token nào trong văn bản.
	
		. Gọi hàm lần thứ hai, và các lần gọi tiếp theo, để tìm tất cả các token còn lại, but - take notice! - với đối số đầu tiên được thiết lập thành NULL. Miễn là hàm không return NULL, nó cung cấp các token tiếp theo của string; khi nó trả về NULL, điều này có nghĩa là không còn token nào nữa.

	- A very important remark: hàm sửa đổi string mà được trỏ đến bởi đối số đầu tiên (nó đặt ký tự null ở cuối của các token - đừng lo, tất cả chúng sẽ bị xóa sau invocation cuối cùng); điều này có nghĩa là chuỗi str phải được đặt trong vùng nhớ có thể writable.


4.3.1.8
	- Nhìn code:

		#include <string.h>
		#include <stdio.h>

		int
		main (void)
		{
		  char hamlet[] =		// don't use char *hamlet = "abc"
		    "To be, or not to be: that is the question:\n"
		    "Whether 'tis nobler in the mind to suffer\n"
		    "The slings and arrows of outrageous fortune,\n"
		    "Or to take arms against a sea of troubles,\n"
		    "And by opposing end them?";
		  char *delim = ",:? \n";
		  char *token = strtok (hamlet, delim);
		  while (token)
		    {
		      printf ("%s ", token);
		      token = strtok (NULL, delim);
		    }
		  printf ("\n");
		  return 0;
		}

	- Mảng hamlet (từ line 5 trở đi) chứa một số dòng đầu tiên trong monologue nổi tiếng của Hamlet. Chúng ta sẽ sử dụng hàm strtok() để tìm tất cả các từ (token) từ văn bản. Chúng ta giả định có năm ký tự phân tách khác nhau:
		
		. a comma;
		
		. a colon;
		
		. a question mark;
		
		. a space;
		
		. a newline.

	- Chúng ta thu thập tất cả chúng vào chuỗi delim (line 11).
		
		. line 12: chúng ta gọi hàm lần đầu tiên - lưu ý các đối số chúng ta đã sử dụng;
		
		. line 13: trong khi hàm trả về một con trỏ khác NULL...
		
		. line 14: ... chúng ta in ra token...
		
		. line 15: ... và cố gắng tìm token tiếp theo (lưu ý các đối số).

	- The program's output như sau:

		To be or not to be that is the question Whether 'tis nobler in the mind to suffer The slings and arrows of outrageous fortune Or to take arms against a sea of troubles And by opposing end them

	- Lưu ý: việc thay đổi khai báo:

		char hamlet[] = ...

	thành dạng

		char *hamlet = ...

	- Phiên bản đầu tiên đặt string trong bộ nhớ có thể ghi của người dùng, trong khi phiên bản thứ hai không.


4.4.1.1 Memory and strings – sorting and searching
	- Bây giờ chúng ta sẽ thảo luận về hai hàm mạnh mẽ hoạt động trên bộ nhớ - hãy nhìn code:

		#include <stdlib.h>

		void qsort (void *base, size_t nmemb, size_t size,
			    int (*compar) (const void *, const void *));

		void *bsearch (const void *key, const void *base,
			       size_t nmemb, size_t size,
			       int (*compar) (const void *, const void *));

	- Cả hai hàm này nhìn nhận nội dung bộ nhớ như một series of amorphous (unstructured) bytes (được đại diện bằng các con trỏ, trừ cái cuối cùng là void *), nhưng nhờ vào một sophisticated trick, chúng có khả năng thao tác và tìm kiếm trong bộ nhớ một cách rất chính xác. Hãy kéo lại tấm màn bí mật một chút: những hàm này cede một phần công việc cho bạn - chúng sẽ làm nhiệm vụ của mình nếu bạn giúp chúng. Tham số cuối cùng, một con trỏ đến hàm, trỏ đến một helper function bạn đã viết. Hàm đó (và chỉ nó) biết về structure của nội dung bộ nhớ, và đó là đủ để làm cho cả hai hàm hoạt động.

	- Note: các khai báo sử dụng từ khoá const; chúng tôi sẽ thảo luận về vấn đề này trong chapter 8, nhưng tạm thời, chúng tôi chỉ nói rằng từ khoá này định nghĩa con trỏ là địa chỉ của nội dung không thể thay đổi, tức là bất kỳ hàm nào sử dụng tham số này sẽ không sửa đổi entity mà nó trỏ đến.

	- Hàm đầu tiên trong số này có khả năng sort bất kỳ mảng nào, không phụ thuộc vào kiểu của các phần tử. Hàm thứ hai có khả năng tìm kiếm một phần tử trong bất kỳ mảng nào.

	- Cả hai hàm nhìn nhận mảng dưới dạng con trỏ thuần tuý có type void *. Làm thế nào mà chúng có thể nhận ra internal structures của các phần tử?

	- Chính là nhờ tham số cuối cùng của chúng - một con trỏ đến một hàm. Nếu người dùng có thể cung cấp hàm này, thì mọi thứ đều khả thi.
		to be honest thì là hầu hết mọi thứ.


4.4.1.2
	- Hãy phân tích khai báo sau:

		int (*compar) (const void *, const void *);

	- Câu lệnh khai báo compar là một con trỏ hàm, có nghĩa là:
		
		. Nhận hai đối số có kiểu void *.
		
		. Trả về một giá trị kiểu int.

	- Nếu một hàm sử dụng một tham số được khai báo theo cách này, điều này có nghĩa là bạn phải triển khai hàm đó và truyền con trỏ đến nó qua tham số tương ứng.

	- Ví dụ, một hàm như sau có thể phù hợp:

		int f(const void *p1, const void *p2) 
		{
		  return 0;
		}

	- Nếu bạn muốn gán một con trỏ đến hàm này cho một biến được đặt tên là x, bạn nên làm như sau:

		int (*x)(const void *, const void *);
		x = f;

	- Nếu bạn muốn gọi hàm mà địa chỉ của nó được lưu trữ trong biến có tên là x và fetch kết quả của hàm đó, bạn có thể sử dụng một trong hai biểu thức tương đương sau:

		int result;
		result = (*x)(ptr1, ptr2);
		result = x(ptr1, ptr2);


4.4.1.3
	- Hàm qsort() sắp xếp một mảng bằng thuật toán hiệu quả gọi là quicksort (do đó hàm có tên là qsort). Nếu bạn muốn tìm hiểu thêm về thuật toán này, hãy xem trang này:
		https://en.wikipedia.org/wiki/Quicksort

	- Hàm này yêu cầu bốn tham số:

		void qsort(void *base,
		           size_t nmemb,
		           size_t size,
		           int (*compar)(const void *, const void *));


		. Con trỏ đến mảng là đối tượng được sắp xếp (base).

		. Số lượng phần tử trong mảng (nmemb).

		. Kích thước của mỗi phần tử (size) (note: tất cả các phần tử phải có kích thước giống nhau).

		. Con trỏ đến hàm so sánh (compar).

	- Biết kích thước của các phần tử và biết số lượng chúng, hàm có thể tự do đổi chỗ các phần tử của chúng, ví dụ bằng cách sử dụng hàm memcpy(), nhưng để sắp xếp một mảng, hàm cần có khả năng tìm ra mối quan hệ giữa hai phần tử bất kỳ nằm bên trong mảng. Không có phương pháp đơn giản, tự nhiên nào để nói cho hàm biết cách các phần tử được xây dựng và cách so sánh chúng.

	- Thay vào đó, bạn phải viết hàm của riêng mình - một hàm nhận biết cấu trúc bên trong của các phần tử mảng và có thể so sánh chúng trong mọi trường hợp.

	- Các hàm phải accept 2 con trỏ đến 2 phần tử mảng bất kì và return a value:
		
		. Bằng 0 khi cả hai phần tử bằng nhau (theo nghĩa của hàm so sánh).
		
		. Lớn hơn 0 khi phần tử đầu tiên nên đứng trước phần tử thứ hai.
		
		. Nhỏ hơn 0 khi phần tử thứ hai nên đứng trước phần tử đầu tiên.

	- Hàm qsort() returns nothing.

	- Bây giờ chúng ta sẽ thử sử dụng hàm để sắp xếp một mảng đơn giản chứa các floats.


4.4.1.4
	- Xem complete program:

		#include <stdio.h>
		#include <stdlib.h>

		int
		cmp (const void *v1, const void *v2)
		{
		  float vv1 = *((float *) v1);
		  float vv2 = *((float *) v2);
		  if (vv1 > vv2)
		    return 1;
		  if (vv2 > vv1)
		    return -1;
		  return 0;
		}

		int
		main (void)
		{
		  float t[] = { 3., 1., 5., 4., 2. };

		  qsort (t, 5, sizeof (t[0]), cmp);
		  int i;
		  for (i = 0; i < 5; i++)
		    printf ("%f; ", t[i]);
		  printf ("\n");
		  return 0;
		}

	
		. line 4: Hàm so sánh được khai báo theo cách yêu cầu của prototype của hàm qsort();
	
		. line 5 and 6: Vì cả hai con trỏ đều có kiểu void *, chúng ta cần chuyển đổi chúng thành float * và sau đó dereference chúng để lấy giá trị thực tế của các phần tử;
	
		. line 7 through 11: Chúng ta kiểm tra cả hai giá trị và trả về kết quả mô tả mối quan hệ giữa chúng; chúng ta làm điều này một cách hơi rối – đó là cái giá chúng ta phải trả cho sự readiness (chúng ta sẽ sửa đổi nó sớm)
	
		. line 15: Đây là mảng chúng ta muốn sắp xếp;
	
		. line 17: Chúng ta hy vọng rằng hàm qsort() sẽ thực hiện công việc đó cho chúng ta – chúng ta truyền các đối số sau cho nó:
		
			. một con trỏ đến mảng;
		
			. số lượng phần tử;
		
			. kích thước của một phần tử đơn (tất nhiên, sizeof(float) cũng hoạt động).
		
			. một con trỏ đến hàm so sánh (chúng ta sử dụng hàm cmp() cho mục đích này)

	- Chương trình output dòng sau:

		1.000000; 2.000000; 3.000000; 4.000000; 5.000000;

	- Điều này chính xác như chúng ta mong đợi. Nice.


4.4.1.5
	- Example program của chúng ta đã sắp xếp mảng theo thứ tự không giảm. Hãy giả sử chúng ta cần sắp xếp cùng một mảng, nhưng theo thứ tự không tăng. Chúng ta cần làm gì để đạt được mục tiêu này?

	- The only amendment mà chúng ta phải thực hiện là một sửa đổi nhỏ bên trong hàm so sánh – nhìn code: 

		#include <stdio.h>
		#include <stdlib.h>

		int
		cmp (const void *v1, const void *v2)
		{
		  float vv1 = *((float *) v1);
		  float vv2 = *((float *) v2);
		  if (vv1 > vv2)
		    return -1;
		  if (vv2 > vv1)
		    return 1;
		  return 0;
		}

		int
		main (void)
		{
		  float t[] = { 3., 1., 5., 4., 2. };

		  qsort (t, 5, sizeof (t[0]), cmp);
		  int i;
		  for (i = 0; i < 5; i++)
		    printf ("%f; ", t[i]);
		  printf ("\n");
		  return 0;
		}

	- Look carefully – chúng tôi đã thay đổi giá trị được return bởi các branches khác nhau của câu lệnh if().

	- Vậy là đủ

	- Chương trình output dòng sau:

		5.000000; 4.000000; 3.000000; 2.000000; 1.000000;

	- Yes, đó chỉ đơn giản như vậy!

	- Bạn có thể thấy được sức mạnh lớn lao của hàm so sánh bây giờ không?


4.4.1.6
	- Hàm so sánh hiện tại của chúng ta look so serious – quá dài dòng.

	- Chúng tôi đã cố gắng làm nó ngắn gọn hơn – bạn nghĩ sao? – nhìn code:

		#include <stdio.h>
		#include <stdlib.h>

		int
		cmp (const void *v1, const void *v2)
		{
		  return *((float *) v2) - *((float *) v1);
		}

		int
		main (void)
		{
		  float t[] = { 3., 1., 5., 4., 2. };

		  qsort (t, 5, sizeof (t[0]), cmp);
		  int i;
		  for (i = 0; i < 5; i++)
		    printf ("%f; ", t[i]);
		  printf ("\n");
		  return 0;
		}

	- Nhìn vào line 5: chúng tôi đã thay thế câu lệnh if lồng nhau bằng chỉ một phép trừ.
		Note: khi v1 lớn hơn v2, hiệu sẽ lớn hơn 0; khi v1 bằng v2, hiệu là bằng 0; khi v2 lớn hơn v1, hiệu sẽ nhỏ hơn 0.

	- Đây chính xác là điều chúng ta cần. Không có cách ngắn gọn hơn để thực hiện một hàm so sánh như vậy.

	- Note: hoán đổi v1 và v2 trong phép trừ sẽ đảo ngược thứ tự tìm kiếm.


4.4.1.7
	- Vì nhiệm vụ so sánh các phần tử của mảng đã được delegated cho bạn, cấu trúc của các phần tử có thể phức tạp theo bất kỳ cách nào. Miễn là bạn có thể chẩn đoán mối quan hệ giữa hai phần tử bất kỳ, hàm qsort() có thể sort mảng.

	- Nhìn code:

		#include <stdio.h>
		#include <stdlib.h>

		typedef struct
		{
		  char name[10];
		  int age;
		} person_t;

		int
		cmp (const void *v1, const void *v2)
		{
		  return ((person_t *) v1)->age - ((person_t *) v2)->age;
		}

		int
		main (void)
		{
		  person_t pp[] = { {"Zulu", 23},
		  {"Sierra", 40},
		  {"Bravo", 15},
		  {"Lima", 9}
		  };

		  qsort (pp, sizeof (pp) / sizeof (person_t), sizeof (person_t), cmp);
		  int i;
		  for (i = 0; i < sizeof (pp) / sizeof (person_t); i++)
		    printf ("(%s, %d)\n", pp[i].name, pp[i].age);
		  return 0;
		}

	
		. line 4: chúng tôi đã khai báo một loại cấu trúc có tên là person_t; cấu trúc này bao gồm 2 fields: một là một string (một mảng char) và một được khai báo là một int; cấu trúc này sẽ lưu trữ dữ liệu về tên và tuổi của some hypothetical figure (hình tượng giả định nào đó);
	
		. line 9: hàm so sánh nhận hai con trỏ và sử dụng chúng để tìm mối quan hệ giữa hai người dựa trên tuổi; Note: chúng tôi sử dụng kỹ thuật đã được chấp nhận trước đó;
	
		. line 14: chúng tôi tạo một mảng 4 phần tử được điền với 4 figure of data (chúng tôi đã đảm bảo rằng chúng không được sắp xếp theo tên hoặc theo tuổi)
	
		. line 19: chúng tôi gọi hàm qsort() – chú ý cách chúng tôi xác định số lượng phần tử.

	- Chương trình xuất ra 4 dòng sau:

		(Lima, 9)
		(Bravo, 15)
		(Zulu, 23)
		(Sierra, 40)


4.4.1.8
	- Nếu bạn muốn sắp xếp danh sách các figure theo tên, bạn phải sửa đổi hàm so sánh để nó có thể so sánh các tên, không phải là tuổi. May mắn thay, hàm strcmp() tiêu chuẩn trả về một giá trị có thể được sử dụng lại trực tiếp, mà không cần bất kỳ thay đổi nào.

	- Kết quả, hàm so sánh mới trông như sau - xem code:

		#include <stdio.h>
		#include <stdlib.h>
		#include <string.h>

		typedef struct
		{
		  char name[10];
		  int age;
		} person_t;

		int
		cmp (const void *v1, const void *v2)
		{
		  return strcmp (((person_t *) v1)->name, ((person_t *) v2)->name);
		}

		int
		main (void)
		{
		  person_t pp[] = { {"Zulu", 23},
		  {"Sierra", 40},
		  {"Bravo", 15},
		  {"Lima", 9}
		  };

		  qsort (pp, sizeof (pp) / sizeof (person_t), sizeof (person_t), cmp);
		  int i;
		  for (i = 0; i < sizeof (pp) / sizeof (person_t); i++)
		    printf ("(%s, %d)\n", pp[i].name, pp[i].age);
		  return 0;
		}

	- Output như sau:

		(Bravo, 15)
		(Lima, 9)
		(Sierra, 40)
		(Zulu, 23)


4.4.1.9
	- - Như bạn có thể suspect, trong quá trình làm việc, hàm qsort() liên tục di chuyển những phần tử đang ở các vị trí sai (theo nghĩa thứ tự sắp xếp). Điều này là lý do tại sao hàm cần biết kích thước của các phần tử và số lượng chúng. Điều này cũng có thể có nghĩa là the smaller the elements are, the faster the sort will be.

	- Liệu có khả năng giảm kích thước của các phần tử mà không loại bỏ các fields của chúng không?

	- Yes, it is possible – chúng ta có thể sử dụng con trỏ thay vì toàn bộ các phần tử và thay đổi con trỏ, chứ không phải là các phần tử.

	- Phân tích code sau:

		#include <stdio.h>
		#include <stdlib.h>
		#include <string.h>

		typedef struct
		{
		  char name[10];
		  int age;
		} person_t;

		int
		cmp (const void *v1, const void *v2)
		{
		  return strcmp (((person_t *) v1)->name, ((person_t *) v2)->name);
		}

		int
		main (void)
		{
		  person_t pp[] = { {"Zulu", 23},
		  {"Sierra", 40},
		  {"Bravo", 15},
		  {"Lima", 9}
		  };

		  qsort (pp, sizeof (pp) / sizeof (person_t), sizeof (person_t), cmp);
		  int i;
		  for (i = 0; i < sizeof (pp) / sizeof (person_t); i++)
		    printf ("(%s, %d)\n", pp[i].name, pp[i].age);
		  return 0;
		}
			

		. line 5: khai báo cấu trúc vẫn giữ nguyên;
		
		. line 10: hàm newperson() cấp phát bộ nhớ cho cấu trúc mới, thiết lập các trường của nó theo các đối số được truyền và return một con trỏ;
		
		. line 17: chúng ta đã thay đổi hàm so sánh để phản ánh việc nó bây giờ nhận con trỏ đến con trỏ đến cấu trúc (phải sử dụng thêm một lần dereference để đến được trường của cấu trúc)
		
		. line 22: mảng hiện giờ chứa con trỏ đến cấu trúc (note cách khởi tạo)
		
		. line 27: invocation hàm qsort() trông gần như giống như trước, nhưng hãy nhìn kỹ vào biểu thức xác định kích thước của phần tử.

	- Output giống như trước đó – kiểm tra nếu bạn không tin.


4.4.1.10
	- Tất nhiên, không có rào cản nào để triển khai một hàm so sánh phức tạp hơn mà xem xét hơn một criterion.

	- Ví dụ, chúng ta có thể muốn hàm so sánh của chúng ta sắp xếp tất cả các figure theo thứ tự của tên của họ, nhưng khi hai hoặc nhiều figure có cùng tên, chúng ta sau đó muốn sắp xếp chúng theo tuổi.

	- Yes, it is possible – chúng ta có thể sử dụng con trỏ thay vì toàn bộ các phần tử và thay đổi con trỏ, chứ không phải là các phần tử.

	- Điều này đơn giản – nhìn code:

		#include <stdio.h>
		#include <stdlib.h>
		#include <string.h>

		typedef struct
		{
		  char name[10];
		  int age;
		} person_t;

		person_t *
		newperson (char *name, int age)
		{
		  person_t *new = malloc (sizeof (person_t));
		  strcpy (new->name, name);
		  new->age = age;
		  return new;
		}

		int
		cmp (const void *v1, const void *v2)
		{
		  int res = strcmp ((*(person_t **) v1)->name, (*(person_t **) v2)->name);
		  if (res == 0)
		    res = (*(person_t **) v1)->age - (*(person_t **) v2)->age;
		  return res;
		}

		int
		main (void)
		{
		  person_t *pp[] = { newperson ("Delta", 23),
		    newperson ("Victor", 40),
		    newperson ("Victor", 15),
		    newperson ("Delta", 9)
		  };

		  qsort (pp, sizeof (pp) / sizeof (person_t *), sizeof (person_t *), cmp);
		  int i;
		  for (i = 0; i < sizeof (pp) / sizeof (person_t *); i++)
		    {
		      printf ("(%s, %d)\n", pp[i]->name, pp[i]->age);
		      free (pp[i]);
		    }
		  return 0;
		}

		
		. line 18: chúng ta so sánh tên trước;
		
		. line 19: nếu chúng bằng nhau...
		
		. line 20: ... chúng ta so sánh tuổi;
		
		. line 25: mảng pp chứa hai Delta và hai Victor để chứng minh rằng hàm so sánh của chúng ta hoạt động đúng cách.

	- Output như sau:

		(Delta, 9)
		(Delta, 23)
		(Victor, 15)
		(Victor, 40)


4.4.1.11
	- Hàm bsearch() tìm kiếm trong một mảng đã sắp xếp (note: đã sắp xếp! This is important!) bằng một thuật toán có tên là binary search (do đó là tên của hàm). Từ "binary" có nghĩa là mảng được chia thành hai phần trong mỗi bước. Nếu bạn muốn biết thêm, hãy đọc bài viết sau đây:

		https://en.wikipedia.org/wiki/Binary_search_algorithm

	- Hàm này cần bốn tham số:

		void *bsearch(const void *key, const void *base,
		              size_t nmemb, size_t size,
		              int (*compar)(const void *, const void *));

	
		. Con trỏ đến giá trị đang được tìm kiếm (key); note: key phải có cùng loại dữ liệu với các phần tử trong mảng đang được tìm kiếm;
	
		. Con trỏ đến mảng đang được tìm kiếm (base); mảng phải được sắp xếp theo thứ tự không giảm;
	
		. Số lượng phần tử trong mảng (nmemb);
	
		. Kích thước của một phần tử đơn lẻ (size);
	
		. Con trỏ đến hàm so sánh (compar).

	- Hàm này return hoặc một con trỏ đến phần tử được tìm thấy, hoặc NULL nếu mảng không chứa gì cả.

	- Như bạn có thể thấy, hàm sử dụng một giao diện rất giống với cái đã được mô tả trước đó. Sự khác biệt là nó sử dụng hàm so sánh không để sắp xếp các phần tử, mà để tìm phần tử liên quan đến key.


4.4.1.12
	- Hãy bắt đầu cuộc thảo luận của chúng ta từ một ví dụ rất đơn giản, xem code:

		#include <stdio.h>
		#include <stdlib.h>

		void
		print (float *base, float *found)
		{
		  if (found)
		    printf ("[%ld]\n", found - base);
		  else
		    printf ("(null)\n");
		}

		int
		cmp (const void *v1, const void *v2)
		{
		  return *((float *) v2) - *((float *) v1);
		}

		int
		main (void)
		{
		  float t[] = { 1., 2., 3., 4., 5. }, key;

		  qsort (t, 5, sizeof (t[0]), cmp);
		  key = 0.;
		  print (t,
			 bsearch (&key, t, sizeof (t) / sizeof (t[0]), sizeof (t[0]), cmp));
		  key = 3.;
		  print (t,
			 bsearch (&key, t, sizeof (t) / sizeof (t[0]), sizeof (t[0]), cmp));
		  key = 6.;
		  print (t,
			 bsearch (&key, t, sizeof (t) / sizeof (t[0]), sizeof (t[0]), cmp));
		  return 0;
		}

	
		. line 4: hàm print() cố gắng hiển thị giá trị được lưu trữ trong đối số thứ hai; nếu đối số không phải là NULL, hàm sẽ output khoảng cách của nó từ đầu mảng, được đo bằng đơn vị sizeof(float); nếu không, hàm sẽ in ra (null)
	
		. line 13: thân hàm so sánh trông như thường lệ;
	
		. line 22: đây là mảng chúng ta tìm kiếm qua (ban đầu đã được sắp xếp)
	
		. line 24: yes, we know, this is a little paranoid – chúng tôi sắp xếp mảng để đảm bảo rằng nó thực sự đã được sắp xếp (Note: chúng tôi sử dụng cùng một hàm so sánh như trong bsearch())

		. line 25 onward: chúng tôi thực hiện hai điều ở đây – chúng tôi đặt một key value (Note: chúng tôi không cần phải pass the key itself, mà chỉ cần một con trỏ đến nó, vì vậy chúng tôi cần một biến riêng để lưu trữ nó) và sau đó chúng tôi gọi hàm bsearch(); vì chúng tôi làm điều này bên trong lời gọi hàm print(), chúng tôi make immediate use of bsearch's result.

	- Chương trình tạo ra output sau đây:

		(null)
		[2]
		(null)

	- Điều này ổn – mảng chứa một phần tử có giá trị là 3. tại chỉ số 2 và không chứa giá trị 0. hoặc 6. nào cả.


4.4.1.13
	- Như trước đó, chúng ta có thể sử dụng bsearch() kèm theo một hàm so sánh phù hợp để tìm kiếm trong một mảng chứa các cấu trúc - hãy nhìn code:

		#include <stdio.h>
		#include <stdlib.h>

		typedef struct
		{
		  char name[10];
		  int age;
		} person_t;

		void
		print (person_t * base, person_t * found)
		{
		  if (found)
		    printf ("[%ld](%s, %d)\n", found - base, found->name, found->age);
		  else
		    printf ("(null)\n");
		}

		int
		cmp (const void *v1, const void *v2)
		{
		  return ((person_t *) v1)->age - ((person_t *) v2)->age;
		}

		int
		main (void)
		{
		  person_t pp[] = { {"Zulu", 9},
		  {"Sierra", 15},
		  {"Bravo", 23},
		  {"Lima", 40}
		  };
		  person_t key;
		  key.age = 9;
		  print (pp, bsearch (&key, pp, 4, sizeof (person_t), cmp));
		  key.age = 20;
		  print (pp, bsearch (&key, pp, 4, sizeof (person_t), cmp));
		  key.age = 40;
		  print (pp, bsearch (&key, pp, 4, sizeof (person_t), cmp));
		  return 0;
		}
	

		. line 4: our good old friend – cấu trúc person_t;
	
		. line 19: hàm so sánh trông cũng quen thuộc;
	
		. line 28: mảng được sắp xếp theo tuổi (tất nhiên là không giảm)

		. lines 34 onward: note: – chúng ta cần một biến riêng kiểu person_t để tạo ra một key hợp lệ; chúng ta không thể chỉ sử dụng một int, vì hàm so sánh của chúng ta không biết về nó – nó chỉ có thể so sánh các cấu trúc.

	- Output:

		[0](Zulu, 9)
		(null)
		[3](Lima, 40)


4.4.1.14
	- Chúng ta có thể viết một hàm so sánh hoạt động trên strings không? Of course, như đã làm trước đó - hãy nhìn code:

		#include <stdio.h>
		#include <stdlib.h>
		#include <string.h>

		typedef struct
		{
		  char name[10];
		  int age;
		} person_t;

		void
		print (person_t * base, person_t * found)
		{
		  if (found)
		    printf ("[%ld](%s, %d)\n", found - base, found->name, found->age);
		  else
		    printf ("(null)\n");
		}

		int
		cmp (const void *v1, const void *v2)
		{
		  return strcmp (((person_t *) v1)->name, ((person_t *) v2)->name);
		}

		int
		main (void)
		{
		  person_t pp[] = { {"Bravo", 23},
		  {"Lima", 40},
		  {"Sierra", 15},
		  {"Zulu", 9}
		  };
		  person_t key;
		  strcpy (key.name, "Sierra");
		  print (pp, bsearch (&key, pp, 4, sizeof (person_t), cmp));
		  strcpy (key.name, "Zulu");
		  print (pp, bsearch (&key, pp, 4, sizeof (person_t), cmp));
		  strcpy (key.name, "Mike");
		  print (pp, bsearch (&key, pp, 4, sizeof (person_t), cmp));
		  return 0;
		}
	

		. line 29: mảng được sắp xếp theo tên now;
	
		. lines 35 onward: việc chuẩn bị key bây giờ phức tạp hơn một chút, vì chúng ta phải sử dụng strcpy() thay vì một phép gán đơn giản, nhưng mọi thứ khác vẫn hoạt động giống như trước.

	- Output như sau:

		[2](Sierra, 15)
		[3](Zulu, 9)
		(null)


4.4.1.15
	- Nếu mảng lưu trữ một con trỏ thay vì các cấu trúc, bạn phải thay đổi không chỉ hàm so sánh (bạn đã biết cách làm điều đó) mà còn chuẩn bị key. Key cũng phải là một con trỏ – đừng quên điều này.

	- Hãy nhìn code:

		#include <stdio.h>
		#include <stdlib.h>
		#include <string.h>

		typedef struct
		{
		  char name[10];
		  int age;
		} person_t;

		person_t *
		newperson (char *name, int age)
		{
		  person_t *new = malloc (sizeof (person_t));
		  strcpy (new->name, name);
		  new->age = age;
		  return new;
		}

		void
		print (person_t ** base, person_t ** found)
		{
		  if (found)
		    printf ("[%ld](%s, %d)\n", found - base, (*found)->name, (*found)->age);
		  else
		    printf ("(null)\n");
		}

		int
		cmp (const void *v1, const void *v2)
		{
		  return strcmp ((*(person_t **) v1)->name, (*(person_t **) v2)->name);
		}

		int
		main (void)
		{
		  person_t *pp[] = { newperson ("Charlie", 23),
		    newperson ("Foxtrot", 40),
		    newperson ("Hotel", 15),
		    newperson ("Julliet", 9)
		  };
		  person_t key, *pkey = &key;
		  strcpy (key.name, "Hotel");
		  print (pp, bsearch (&pkey, pp, 4, sizeof (person_t *), cmp));
		  strcpy (key.name, "Quebec");
		  print (pp, bsearch (&pkey, pp, 4, sizeof (person_t *), cmp));
		  strcpy (key.name, "Charlie");
		  print (pp, bsearch (&pkey, pp, 4, sizeof (person_t *), cmp));
		  int i;
		  for (i = 0; i < 4; i++)
		    free (pp[i]);
		  return 0;
		}

	
		. line 43: chúng ta khai báo một key hiện tại (cấu trúc chứa giá trị cần tìm kiếm) và một con trỏ đến key (note cách chúng ta khởi tạo nó)
	
		. line 44: chúng ta sao chép string được tìm kiếm vào key hiện tại...
	
		. line 45: ... và chuyển một con trỏ đến con trỏ đến nó cho hàm bsearch()

	- Note: vì tất cả các con trỏ được truyền vào hàm bsearch() đều được khai báo là void*, chúng tôi khuyên nên cực kì cẩn trọng khi truyền các đối số. Compiler không thể phát hiện nhiều lỗi có thể xảy ra – bạn phải đảm bảo rằng key và các phần tử hoàn toàn tương thích.

	- Ví dụ của chúng tôi output sau:

		[2](Hotel, 15)
		(null)
		[0](Charlie, 23)


4.5.1.1 Wide characters and wide strings
	Wide characters and wide strings – what is I18N?

		- Từ "internationalization" (quốc tế hóa) chắc chắn là quá dài - không có gì ngạc nhiên khi nó thường được viết tắt thành I18N.

		- Tại sao lại như vậy? Hãy nhìn kỹ - có một "I" ở đầu từ, sau đó có 18 chữ cái khác nhau và một "N" ở cuối.

		- Mặc dù có nguồn gốc hơi hài hước, thuật ngữ này được chính thức sử dụng trong nhiều văn bản và tiêu chuẩn, và chúng ta cũng sẽ sử dụng nó.

		- The software I18N là một routine trong thời đại hiện nay. Mọi chương trình hữu ích phải được viết theo cách cho phép nó được sử dụng trên toàn thế giới, giữa các văn hóa, ngôn ngữ và bảng chữ cái khác nhau. Không có cách nào tránh khỏi nó.

		- A standard C language type (được đặt tên là char) được thiết kế để lưu trữ và xử lý văn bản bằng tám bit cho mỗi ký tự. Tám bit có nghĩa là 256 ký tự khác nhau. 128 đầu tiên được sử dụng cho bảng chữ cái Latin tiêu chuẩn (cả ký tự viết hoa và viết thường). Có thể nén tất cả các ký tự quốc gia khác sử dụng trên thế giới vào 128 ký tự còn lại không?
			No, tất nhiên là không. Có quá nhiều.


4.5.1.2
	Wide characters and wide strings – what is code point?

		- Một code point là một số làm nên một ký tự. Ví dụ, 32 là code point tạo ra một khoảng trắng trong bảng mã ASCII.

		- Chúng ta có thể nói rằng bảng mã ASCII tiêu chuẩn bao gồm 128 code point.

		- Vì bảng mã ASCII tiêu chuẩn chiếm 128 trong 256 code points có thể có, chúng ta chỉ có thể sử dụng 128 code points còn lại. Điều này không đủ cho tất cả các ngôn ngữ có thể có, nhưng có thể đủ cho một ngôn ngữ hoặc một nhóm nhỏ các ngôn ngữ tương tự. Chúng ta có thể đặt higher half của các code points khác nhau cho các ngôn ngữ khác nhau không?

	Wide characters and wide strings – what is code page?

		- Yes, we can.

		- Và this is called a "code page" .

		- Một code page là một tiêu chuẩn sử dụng 128 code points cao hơn để lưu trữ các ký tự quốc gia cụ thể. Ví dụ, có các bảng mã khác nhau cho Tây Âu và Đông Âu, bảng chữ cái Cyrillic và Greek, ngôn ngữ tiếng Ả Rập và tiếng Hebrew, và nhiều ngôn ngữ khác nữa. Điều này có nghĩa là cùng một code point có thể tạo ra các ký tự khác nhau khi sử dụng trong các bảng mã khác nhau.

		- Ví dụ, code point 200 tạo ra Č (một chữ cái được sử dụng trong một số ngôn ngữ Slavic) khi sử dụng bảng mã ISO/IEC 8859-2, và tạo ra Ш (một chữ cái Cyrillic) khi sử dụng bảng mã ISO/IEC 8859-5.

		- Vì vậy, để xác định ý nghĩa của một code point cụ thể, bạn phải biết target code page. 

		- Nói cách khác, các code point tạo ra từ các code pages có thể khá là mơ hồ.


4.5.1.3
	Wide characters and wide strings – what is Unicode?

		- Code pages đã giúp ngành công nghiệp máy tính giải quyết vấn đề I18N trong một thời gian dài, nhưng sớm trở nên rõ ràng rằng chúng không phải là một giải pháp lâu dài.

		- Concept giải quyết vấn đề lâu dài là Unicode.

		- Unicode gán unique (rõ ràng, không mơ hồ) characters (chữ cái, dấu gạch ngang, hình tượng v.v.) cho hơn một triệu code points. 128 code points Unicode đầu tiên giống với ASCII, và 256 code points Unicode đầu tiên giống với bảng mã ISO/IEC 8859-1 (một bảng mã được thiết kế cho các ngôn ngữ Tây Âu).


4.5.1.4
		- Tiêu chuẩn Unicode không nói gì về cách mã hóa và lưu trữ các ký tự trong bộ nhớ và tệp. Nó chỉ đặt tên tất cả các ký tự có sẵn và gán chúng vào cái mà so-called planes (nhóm ký tự có nguồn gốc, ứng dụng hoặc tính chất tương tự).

		- Có nhiều tiêu chuẩn mô tả các kỹ thuật được sử dụng để triển khai Unicode trong máy tính và hệ thống lưu trữ máy tính hiện tại. Trong số này, tiêu chuẩn phổ quát nhất là UCS-4.

		- Tên này comes from Universal Character Set (Bảng mã ký tự toàn cầu).

		- UCS-4 sử dụng 32 bits (bốn byte) để lưu trữ mỗi ký tự, và code chỉ là the Unicode code point's unique numbers. Mỗi số nên được lưu trữ dưới dạng multibyte value theo định dạng big-endian. Nếu một file hoặc character stream hoạt động với giá trị little-endian, dãy ký tự UCS-4 nên bắt đầu từ BOM (Byte Order Mark), một sự kết hợp không thể in của các bit chỉ định thứ tự byte được sử dụng trong tệp. Một big-endian multibyte file cũng có thể chứa một BOM phù hợp (một số công cụ có thể yêu cầu điều này).

		- Như bạn thấy, UCS-4 là một tiêu chuẩn khá lãng phí - nó làm tăng kích thước văn bản lên bốn lần so với ASCII tiêu chuẩn.

		- May mắn thay, có những cách thông minh hơn để mã hóa văn bản Unicode.


	Wide characters and wide strings – what is UTF-8?

		- Một trong những tiêu chuẩn được sử dụng phổ biến nhất là UTF-8.

		- Tên comes from Unicode Transformation Format (Định dạng biến đổi Unicode).

		- Concept rất thông minh. Để tóm gọn, chúng ta có thể nói rằng UTF-8 sử dụng số bit tùy thuộc vào số bit cần thiết để biểu diễn từng code point.

		- Example:
			
			. Tất cả các ký tự Latin (và tất cả các ký tự ASCII tiêu chuẩn) chiếm 8 bit.
			
			. Ký tự không Latin chiếm 16 bit.
			
			. Các biểu tượng CJK (China-Japan-Korea) chiếm 24 bit.

		- Phương pháp UTF-8 sử dụng để lưu trữ các code points độc lập, không phụ thuộc vào thứ tự byte, vì vậy không cần sử dụng BOM. Tuy nhiên, một số công cụ có thể tìm kiếm nó khi đọc file và nhiều editors thiết lập nó khi viết.

		- Nếu bạn muốn biết thêm về UTF-8, hãy xem tại đây:
			https://en.wikipedia.org/wiki/UTF-8


	Wide characters and wide strings – what is a wide char?

		- Một giá trị char chứa một số bit đủ lớn để lưu trữ tất cả điểm mã hóa Unicode được gọi là wide char.

		- Do Unicode hiện tại mô tả 1,114,112 code points khác nhau, 21 bit sẽ đủ cho mục đích đó (Check it yourself!). Thật không may, triển khai một phép toán cho số nguyên 21 bit không dễ dàng hoặc hiệu quả. Vì lý do này, hầu hết các triển khai ký tự rộng sử dụng 32 bit, nhưng những cái không sử dụng để lưu trữ các ký tự CJK có thể hoạt động đúng với chỉ 16 bit.


4.5.1.5
	Wide characters and wide strings – conditions and warnings
		Một số lưu ý:

		- Trước khi chúng tôi bắt đầu hiển thị một số ví dụ cụ thể, chúng tôi cần đưa ra một số điều kiện và cảnh báo quan trọng:
			
			. Để chỉnh sửa các example programs từ phần hiện tại, bạn cần một trình soạn thảo hiểu UTF-8 (Notepad hoặc Visual Studio trên MS Windows thuộc loại này); một số trình soạn thảo khác có thể hiển thị một số phần của code chúng tôi như là các dãy ký tự rác hoàn toàn không thể đọc được, vì các ví dụ của chúng tôi chứa một số điểm mã Unicode được mã hóa bằng UTF-8;
			
			. Để compile các chương trình này, bạn cần một trình biên dịch hiểu UTF-8; các phiên bản hiện tại của clang và gcc đáp ứng yêu cầu trực tiếp; phiên bản CL từ 19 trở lên yêu cầu một tùy chọn đặc biệt có tên là /utf8, thông báo cho trình biên dịch rằng tệp nguồn sử dụng UTF-8 như mã hóa Unicode mặc định của nó; Note: phiên bản CL trước phiên bản 19 bị hạn chế hỗ trợ wide char - không sử dụng chúng để compile các ví dụ của chúng tôi;
			
			. Để xem các ký tự Unicode như một phần output của chương trình, bạn cần sử dụng một bảng điều khiển có:
				
				+ hiểu biết về UTF-8;
				
				+ sử dụng một phông chữ hiểu biết về UTF.

		- Đa số các ứng dụng mô phỏng terminal Unix/Linux đáp ứng yêu cầu trực tiếp; bảng điều khiển CMD.EXE của MS Windows cần được chuẩn bị đúng:
			
			1. nó phải sử dụng một phông chữ UTF-8 chuyên dụng (một trong số đó là Lucida Console, được cài đặt mặc định);
			
			2. nó phải được đặt vào chế độ UTF-8 bằng cách sử dụng lệnh sau:

				chcp 65001

			điều này bật lên một special code page configuration phù hợp để hiển thị các UTF-8 encoded code point;

			3. Một chương trình muốn gửi các UTF-8 coded strings cần phải chuẩn bị luồng stdout cho nó; điều này được thực hiện bằng cách gọi một hàm chuyên biệt:

				_setmode(_fileno(stdout), _O_U8TEXT); (cái này của chatGPT)

				chcp 65001 (cái này hiện trong page)

			tạo ra từ tệp đầu vào <fcntl.h>;

				. Để tránh bị buộc tội về việc ưu tiên một số ngôn ngữ, chúng tôi đã quyết định sử dụng bảng chữ cái Hy Lạp và cài đặt ngôn ngữ Hy Lạp trong hầu hết các ví dụ của chúng tôi; bảng chữ cái Hy Lạp thực sự (do được sử dụng mạnh mẽ trong ký hiệu toán học) là một biểu tượng quốc tế, được biết đến trên toàn thế giới và thường được sử dụng chung.

		- Bây giờ chúng ta có thể tiếp tục hành trình của mình vào thế giới I18N.


4.5.1.6
	Wide characters and wide strings – the necessary header

		- Nếu bạn định sử dụng wide characters trong code của mình, bạn cần include header sau:

			#include <wchar.h>

		- Header này chứa:
			
			. Các khai báo type dữ liệu cần thiết;
			
			. Các hàm được sử dụng để thao tác trên wide characters và strings hình thành từ các wide characters (wide strings).


	Wide characters and wide strings – elementary types

		- Hai loại sau đây tạo nên cơ sở cho việc xử lý wide char:

			wchar_t
			wint_t
			
			. wchar_t: là một wide char type cơ bản và tương đương với loại ký tự thông thường (char);
			
			. wint_t: là một loại int cơ bản có khả năng lưu trữ các giá trị wchar_t được giải thích như giá trị số nguyên cũng như giá trị WEOF, là giá trị thay thế cho hằng số EOF thông thường.

		- Program sau:

			#include <stdio.h>
			#include <wchar.h>

			int
			main (void)
			{
			  printf ("%ld %ld\n", sizeof (wchar_t), sizeof (wint_t));
			  return 0;
			}

		output:

			4 4

		khi compile bởi clang phiên bản 3.7.1 và gcc phiên bản 4.9.3, và output:

			2 2

		khi compile bởi CL.


4.5.1.7
	Wide characters and wide strings – literals

		- Các literals của kiểu wchar_t cần syntax cụ thể:
			
			. L'x'
			
			. u'x'
			
			. U'x'

		trong đó x là bất kỳ ký tự nào từ không gian ký tự Unicode (tất cả các hình thức được hiển thị ở đây đều tương đương, mặc dù L không thể được thay thế bằng l).

		- Note:
			
			. Source code được mã hóa theo tiêu chuẩn UTF-8 sẽ chứa một code point có chiều dài được xác định bởi UTF-8;
			
			. Compiler chuyển đổi code này thành UCS-4 và sẽ sử dụng representation này cho xử lý tiếp theo.

		- Bây giờ, phân biệt giữa hai trường hợp này:

			. Một ký tự được nhúng trong source code có thể (nhưng không nhất thiết) sử dụng một chuỗi multibyte cho ký tự x;

			. Một chữ số chính nó được coi là một giá trị wchar_t và chứa 32/16 bit (tùy thuộc vào nền tảng) theo UCS-4.

		- Chương trình sau:

			#include <stdio.h>
			#include <wchar.h>

			int
			main (void)
			{
			  wchar_t omega = L'N)';
			  printf ("%d\n", omega);
			  return 0;
			}

		output là:

			3a9
	
		đó là Omega's code point ở hệ thống hex (937 in decimal).


4.5.1.8
	- Nếu bạn muốn chỉ định một wide character code bằng hexadecimal code point value của nó, bạn có thể sử dụng syntax sau:
	
		\uxxxx
		\Uxxxxxxxx

	- Note:

		. x là một chữ số hexadecimal;

		. tiền tố \u cần chính xác bốn chữ số hexadecimal và có thể được sử dụng cho các code points không dài hơn 16 bit;

		. tiền tố \U cần chính xác tám chữ số hexadecimal và nên được sử dụng cho các code points dài hơn 16 bit.

	- Program sau: 

		#include <stdio.h>
		#include <wchar.h>

		int
		main (void)
		{
		  wchar_t omega = L'\u03a9';
		  printf ("%d\n", omega == L'N)');
		  return 0;
		}

	có output là:

		1


4.5.1.9
	Wide characters and wide strings – wide character functions

		- Header <wctype.h> khai báo một số hàm được thiết kế để làm việc với các wide characters:

			#include <wctype.h>
	
		- Header này là một sự thay thế cho header <ctype.h>, nhưng được thiết kế cho các wide characters.

		- Một số hàm được cung cấp bởi header này bao gồm:

			. int iswalnum(wint_t wc) – kiểm tra xem wc có phải là một ký tự chữ số hoặc chữ cái không.

			. int iswalpha(wint_t wc) – kiểm tra xem wc có phải là một ký tự chữ cái không.

			. int iswblank(wint_t wc) – kiểm tra xem wc có phải là một ký tự trắng không.

			. int iswdigit(wint_t wc) – kiểm tra xem wc có phải là một ký tự số không.

			. int iswlower(wint_t wc) – kiểm tra xem wc có phải là một ký tự chữ thường không.

			. int iswupper(wint_t wc) – kiểm tra xem wc có phải là một ký tự chữ in hoa không.

			. wint_t towlower(wint_t wc) – chuyển đổi một ký tự chữ in hoa thành chữ thường (các ký tự khác không thay đổi).

			. wint_t towupper(wint_t wc) – chuyển đổi một ký tự chữ thường thành chữ in hoa (các ký tự khác không thay đổi).

		- Note: Để làm cho tất cả các hàm này hoạt động, bạn phải bật locale (đây là cơ chế của OS để nhận biết các đặc điểm cụ thể của các bảng chữ cái khác với chữ cái Latin và các quy ước địa phương khác nhau, chẳng hạn như cách hiển thị thời gian, cách hiển thị số tiền, và so on). Để làm điều này, bạn cần:
			
			. include a header file name <locale.h>.
			
			. Gọi một hàm có tên là setlocale(). Form đơn giản nhất của việc gọi này trông như sau:

				setlocale(LC_ALL, "");
	
		- Nếu bạn muốn biết thêm về các khu vực và các tính năng của chúng, bạn có thể bắt đầu tại đây:
			https://www.gnu.org/software/libc/manual/html_node/Locales.html


4.5.1.10
	- Chương trình dưới đây thực hiện một số hàm từ header <wctype.h>:

		#include <stdio.h>
		#include <wchar.h>
		#include <wctype.h>
		#include <locale.h>

		void
		is (wchar_t ch)
		{
		  printf ("%d %d %d\n", ! !iswlower (ch), ! !iswupper (ch), ! !iswalnum (ch));
		}

		int
		main (void)
		{
		  setlocale (LC_ALL, "");
		  is (L'N2');
		  is (towupper (L'N2'));
		  is (L'N(');
		  is (L'\u03B3');		// lower gamma
		  is (0x3A0);			// upper pi but as an int
		  return 0;
		}

		
		. line 9: Gọi printf() để hiển thị kết quả được trả về từ các hàm iswlower(), iswupper() và iswalnum(); lưu ý cặp toán tử ! – nó chuyển đổi kết quả thành 0 hoặc 1 vì những hàm này có thể trả về bất kỳ giá trị khác không để đưa ra câu trả lời khẳng định.
		
		. line 16: Hỏi về chữ beta thường.
		
		. line 17: Hỏi về chữ beta hoa (trả về từ hàm towupper()).
		
		. line 18: Hỏi về chữ psi hoa.
		
		. line 19: Hỏi về chữ gamma thường được encoded dưới dạng mã Unicode.
		
		. line 20: Hỏi về chữ pi hoa được encoded dưới dạng số nguyên thường.

	- Program's output như sau:

		1 0 1
		0 1 1
		0 1 1
		1 0 1
		0 1 1


4.5.1.11
	Wide characters and wide strings – wide character strings

		- Strings bao gồm các wide characters thực tế là mảng chứa các phần tử kiểu wchar_t và chúng được hiểu là con trỏ kiểu wchar_t*.

		- Những string này được mã hóa theo một cách tương tự như wide characters (cả hai dạng này là tương đương):

			L"xyz"
			u"xyz"

		- Bạn cũng có thể sử dụng các tiền tố \u và \U để nhúng hexadecimal codes vào trong string.

		- Nếu bạn thay thế tiền tố str bằng wcs trong tên của một hàm thông thường hoạt động trên string (tích hợp từ <string.h>), bạn sẽ có được phiên bản wide của nó. Tất cả những wide functions này đến từ <wchar.h>.

		- Ví dụ, để tìm độ dài của một wide string, bạn nên sử dụng hàm wcslen() thay vì strlen().

		- Wide string được kết thúc bằng một wide character có giá trị L'\0' (một biểu diễn ngắn gọn của L'\u0000'); tương tự như strings thông thường kết thúc bằng ký tự có giá trị '\0'.

		- Chương trình dưới đây:

			#include <stdio.h>
			#include <wchar.h>

			int
			main (void)
			{
			  wchar_t *str1 = L"υπολογιστή";	// computer
			  wchar_t str2[] = L"πρόγραμμα";	// program
			  wchar_t str[100];
			  printf ("%ld\n", wcslen (str1));
			  printf ("%ld\n", wcslen (str2));
			  wcscpy (str, str1);
			  wcscat (str, L" ");
			  wcsncat (str, str2, 5);
			  printf ("%ld\n", wcslen (str));
			  return 0;
			}

		có output là:

			10
			9
			16


4.5.1.12
	Wide characters and wide strings – comparing wide character strings

		- Để so sánh 2 wide strings, bạn có thể sử dụng một trong các hàm sau:

			int wcscmp(wchar_t *s1, wchar_t *s2);
			int wcscasecmp(wchar_t *s1, wchar_t *s2);

		- Hàm đầu tiên so sánh 2 wide strings, trong khi hàm thứ hai cũng làm điều tương tự nhưng bỏ qua việc phân biệt chữ hoa và thường. Cả hai hàm đều return 0 khi cả hai đối số đều trỏ đến string tương đương (có hoặc không phân biệt chữ hoa/thường).

		- Note: Những hàm này không thay thế hàm strcmp(), vì chúng không thể xác định thứ tự chữ cái tuyệt đối của các string được so sánh. Chúng chỉ có thể so sánh chúng character by character và tìm vị trí của sự khác biệt đầu tiên, rồi trả về dấu của sự khác biệt đó.

		- Điều này có thể không giống như việc so sánh string bằng cách sử dụng thứ tự chữ cái nguyên bản. Note: Một số ngôn ngữ châu Âu sử dụng các biến thể riêng của bảng chữ cái Latin - bảng chữ cái này chủ yếu bao gồm các ký tự Latin, nhưng chứa một số ký tự bản địa có thể nằm giữa các ký tự tiêu chuẩn, ví dụ, tiếng Séc sử dụng ký tự Č mà ban đầu nằm giữa C và D. Ký tự này có mã Unicode riêng không thể so sánh trực tiếp với C hoặc D (rõ ràng là lớn hơn cả hai ký tự này).

		- Để so sánh string trong những ngôn ngữ như vậy, bạn sử dụng hàm wcscoll().

		- Note: Môi trường biên dịch CL không cung cấp hàm wcscasecmp().

		- Chương trình dưới đây:

			#include <stdio.h>
			#include <wchar.h>
			#include <locale.h>

			int
			main (void)
			{
			  setlocale (LC_ALL, "");
			  wchar_t *str1 = L"πρόγραμμα";	// program
			  wchar_t *str2 = L"ΠΡΌΓΡΑΜΜΑ";	// programs   
			  printf ("%d\n", wcscmp (str1, str2));
			#ifndef _MSC_VER
			  printf ("%d\n", wcscasecmp (str1, str2));
			#endif
			  return 0;
			}

		output ra:

			1
			0

		khi compiled bởi CL compiler.


4.5.1.13
	- Prototype của hàm wcscoll():

		int wcscoll(wchar_t *s1, wchar_t *s2);
	
	- Note: Hàm lấy thông tin so sánh từ OS, không phải từ C language environment. Vì hàm wcscoll() cần biết về collection để so sánh đúng hai wide strings, OS của bạn phải biết về locale mà bạn muốn sử dụng.

	- Chương trình dưới đây thể hiện sự khác biệt giữa wcscmp() và wcscoll() - nhìn code:

		#include <stdio.h>
		#include <wchar.h>
		#include <locale.h>
		#include <stdlib.h>
		#include <stdio.h>
		#ifdef _MSC_VER
		#include <fcntl.h>
		#endif

		int
		cmp (const void *v1, const void *v2)
		{
		  wchar_t *p1 = *((wchar_t **) v1);
		  wchar_t *p2 = *((wchar_t **) v2);
		  return wcscmp (p1, p2);
		}

		int
		coll (const void *v1, const void *v2)
		{
		  wchar_t *p1 = *((wchar_t **) v1);
		  wchar_t *p2 = *((wchar_t **) v2);
		  return wcscoll (p1, p2);
		}

		void
		print (wchar_t ** p)
		{
		  int i;
		  for (i = 0; i < 3; i++)
		    wprintf (L"%ls\n", p[i]);
		  wprintf (L"\n");
		}

		int
		main (void)
		{
		#ifdef _MSC_VER
		  _setmode (_fileno (stdout), _O_U16TEXT);
		  setlocale (LC_ALL, "czech");
		#else
		  setlocale (LC_ALL, "cs_CZ.UTF-8");
		#endif
		  wchar_t *tab[3] = { L"ABDD", L"ABDD", L"ABCD" };
		  qsort (tab, 3, sizeof (tab[0]), cmp);
		  print (tab);
		  qsort (tab, 3, sizeof (tab[0]), coll);
		  print (tab);
		  return 0;
		}

	
		. line 10: chúng ta định nghĩa một hàm so sánh hai wide strings (được đưa ra dưới dạng con trỏ đến con trỏ wchar_t) sử dụng hàm wcscmp();
	
		. line 18: chúng ta định nghĩa một hàm so sánh thứ hai sử dụng wcscoll() thay vì wcscmp()
	
		. line 31: Note: chúng ta sử dụng hàm wprintf() để xuất string của chúng ta; đây là một "wide" variant của hàm printf() thông thường; hàm mong đợi rằng định dạng (đối số đầu tiên) là một wide string và sử dụng định dạng %ls để xuất wide strings ra stdout;
	
		. line 38 to 43: tùy thuộc vào nền tảng, chúng ta khởi tạo luồng stdout (hoặc không) và đặt locale theo yêu cầu của nền tảng;
	
		. line 44: chúng ta định nghĩa một mảng chứa ba wide strings và sắp xếp nó hai lần.

	- Chương trình, được compiled và chạy trên máy tính có cài đặt và cấu hình Czech locale info, tạo ra output sau:

		ABCD
		ABDD
		ABČD

		ABCD
		ABČD
		ABDD
	


~ Module 5 ~

	In this module, you will learn about:

		.definitions, implementations and history;

		.thread safety;

		.system(), getenv(), setenv();

		.processes in Unix way:
			.fork();
			.exit();
			.execxx();
			.wait() and waitpid();

		.processes in MS Windows way:
			.CreateProcess();
			.WaitForSingleObject();
			.POSIX threads;
			.MS Windows threads;

		.C11 threads ().


5.1.1.2 Processes and threads – the process and its environment
	- In a nutshell, chúng ta có thể nói rằng một process là một running code. Code thực thi, đặt trong một file thực thi, trở thành một process khi nó đã được bắt đầu và hiện đang chạy, và hoàn toàn được kiểm soát bởi OS. Process có thể kết thúc theo một trong hai cách:

		. Tự nguyện - khi nó hoàn thành hoặc gọi hàm exit() (cả hai trường hợp này đều giống nhau)
		
		. Bắt buộc - khi nó cố gắng mess up OS và không có cách nào khác để xử lý nó ngoại trừ stop the process ngay lập tức.

	- The running process được trang bị các tài nguyên sau:
	
		. Một unique identifier được gọi là PID (Process ID - thường là một giá trị số nguyên); note: có một sự khác biệt lớn giữa tên process (có thể lấy từ tên file thực thi) và PID; một file thực thi có thể tạo ra nhiều process chạy song song, và chúng phải được phân biệt bằng PID;
	
		. Một đoạn code - một phần của bộ nhớ nơi code của process được lưu trữ và thực thi; note: nhiều process được khởi chạy từ cùng một file thực thi có thể chia sẻ cùng một đoạn code, vì code không thể sửa đổi và không thể xâm phạm; biện pháp như vậy sẽ giúp tiết kiệm bộ nhớ;
	
		. Một đoạn dữ liệu - một phần của bộ nhớ nơi dữ liệu của process được lưu trữ; note: các process không được phép chia sẻ cùng một đoạn dữ liệu (nếu không dữ liệu sẽ bị hỏng)
	
		. Một context - một bộ dữ liệu cần thiết để tạm ngừng và tiếp tục process; thông thường, context bao gồm nội dung của tất cả thanh ghi bộ xử lý; note: nếu bạn lưu context và khôi phục nó sau này, bạn có thể hibernate trạng thái của process và đánh thức nó bất cứ lúc nào mà không có rủi ro thiệt hại miễn là đoạn dữ liệu không bị chạm vào.

	- Một process khởi chạy một process khác được gọi là parent process. Một process được khởi chạy bởi một process khác được gọi là child process. Lưu ý: Một child process cũng có thể đồng thời là một parent process.

	- Bây giờ chúng tôi sẽ chỉ cho bạn cách đơn giản nhất để tạo và thực thi một child process.


5.1.1.3
	
		#include 


		int system(char *command);

	- Hàm system() tạo một child process và thực thi lệnh được chỉ định trong đối số duy nhất của nó thay cho process mới đó. Lệnh có thể là một lệnh thực sự từ bảng điều khiển OS (như DIR trong MS Windows hoặc ls trong Unix/Linux) hoặc là tên của một chương trình ngoại vi để khởi chạy và thực thi. Lưu ý: cú pháp của lệnh phải tương thích với quy ước của OS.

	- Khi child process đang hoạt động, process gốc (parent) của bạn sẽ được đưa vào chế độ ngủ và sẽ được đánh thức khi child của bạn end.

	- The command argument (Đối số lệnh) có thể được chỉ định là NULL khi hàm chỉ kiểm tra xem có shell nào trong OS có thể thực hiện lệnh hay không (Note: quyền hạn của process của bạn có thể quá yếu để bắt đầu shell).

	- The return value là:

		. Nếu lệnh là NULL:
		
			. Số 0: không có shell nào khả dụng;
		
			. Số khác không: một shell khả dụng.

		. Nếu lệnh không phải là NULL:
			
			. -1 nếu không thể bắt đầu child process;
			
			. a return code của child process trong TH ngược lại; Note: trong Unix/Linux, mã trả về nằm trên tám bit cao hơn của kết quả, trong khi tám bit thấp hơn chứa termination reason code (mã lý do chấm dứt), vì vậy một retcode bằng 1 sẽ được return as 256; bạn có thể nhận được actual return code bằng cách dịch giá trị tám bit sang phải; cũng có một macro có tên WEXITSTATUS() thực hiện điều này cho bạn, ví dụ:

		int ret = system(cmd);
		int aret = WEXITSTATUS(ret);

	- Chúng tôi đã sử dụng hàm system() trong ví dụ đơn giản sau, xem code:

		#include <stdlib.h>
		#include <stdio.h>

		int
		main (void)
		{
		  int v = system (NULL);
		  printf ("Shell is %s available\n", v ? "" : "not");
		  if (v)
		    {
		      v = system ("echo MARY HAD A LITTLE PROCESS");
		      printf ("Child process returned %d\n", v);
		    }
		  return 0;
		}

	- Chúng tôi cũng đã sử dụng lệnh echo của shell, vì nó có sẵn cả trong bảng điều khiển MS Windows và trong shell Unix/Linux, điều này làm cho code này gần như hoàn toàn portable.
	
		. line 8: chúng ta kiểm tra xem có shell nào khả dụng cho chúng ta hay không;
	
		. line 11: nếu nó khả dụng, chúng ta thử thực hiện lệnh echo.

	- Program outputs:

		Shell is available
		MARY HAD A LITTLE PROCESS
		Child process returned 0
	
	- (bất kể host OS nào).


5.1.1.4
	- Đây không phải là về ecology. Đây là về một phần của bộ nhớ lưu trữ các biến môi trường, hoặc đơn giản là môi trường. Đó là một vài string có dạng sau:

		NAME=VALUE

	được lưu trữ liên tiếp nhau trong bộ nhớ của một tiến trình. Biến môi trường được sử dụng để lưu trữ một số dữ liệu cấu hình toàn cục mà có thể truy cập được từ tất cả các tiến trình đang chạy. Ví dụ, biến PATH liệt kê tất cả các thư mục mà phải được tìm kiếm để tìm một chương trình có tên cụ thể.

	- Mỗi tiến trình có bản sao riêng của môi trường.

	- Khi một tiến trình con được khởi chạy, nó nhận (kế thừa) một bản sao của môi trường của cha nó.

	- Một tiến trình có thể thay đổi môi trường của mình (ví dụ, xóa một biến, thêm một biến mới hoặc sửa giá trị của một biến hiện tại), nhưng sự thay đổi này chỉ thấy được đối với tiến trình đó và các tiến trình con của nó.

	- Làm thế nào tiến trình có thể truy cập môi trường của mình?

		int main(int argc,
		    char *argv[],
		    char **env) { ... }

	- C language standard cho phép bạn sử dụng ba form khác nhau của main() function header:
		
		. không có tham số nào cả (void)
		
		. với hai tham số (int và char**)
		
		. với ba tham số (int, char** và char**) khi tham số thứ ba trỏ đến một mảng string, trong đó mỗi string chứa một biến môi trường; note: nó có thể được khai báo theo hai cách (ít nhất):
		
			. char **env;
		
			. char *env[];

	- Note: Không có biến như argc hiển thị số lượng phần tử trong env. Bạn phải tự đếm chúng.

	- Đây là cách đơn giản nhất để xem xét môi trường của bạn. Hãy sử dụng nó.


5.1.1.5
	- Đây là cách một loại hàm main() mới trông như thế - hãy nhìn code:

		#include <stdio.h>

		int
		main (int argc, char *argv[], char **env)
		{
		  char **p = env;
		  int n = 1;
		  while (*p)
		    {
		      printf ("%03d: %s\n", n, *p);
		      p++;
		      n++;
		    }
		  return 1;
		}

	
		. line 6: chúng ta lấy con trỏ env gốc;
	
		. line 8: chúng ta lặp qua mảng cho đến khi đọc một phần tử bằng NULL (đây là một guardian đánh dấu cuối cùng của mảng)
	
		. line 10: chúng ta in biến và tăng giá trị con trỏ cũng như bộ đếm biến.

	- Chúng tôi nghĩ rằng bạn có thể ngạc nhiên về số lượng biến mà hệ thống của bạn lưu trữ trong môi trường của mỗi tiến trình. Hãy thử nghiệm nó!


5.1.1.6
	- Tham số thứ ba của hàm main() cung cấp toàn bộ môi trường. May mắn thay, có một cách để chỉ nhận giá trị của một biến môi trường duy nhất thay vì quét tất cả chúng. Thậm chí có một hàm thực hiện điều này cho bạn:

		#include <stdlib.h>

		char *getenv(char *name);

		
		. Tham số duy nhất được sử dụng để chỉ định tên của biến đang được tìm kiếm;
		
		. Kết quả là:
		
			. NULL nếu không có biến nào mang tên đó;
		
			. Một con trỏ đến giá trị của biến trong trường hợp khác.

	- Chúng ta đưa hàm vào hoạt động trong code:

		#include <stdio.h>
		#include <stdlib.h>

		int
		main (void)
		{
		  char *nam = "CPPINSTITUTE";
		  char *val = getenv (nam);
		  if (val == NULL)
		    {
		      printf ("%s undefined\n", nam);
		      return 1;
		    }
		  printf ("%s=%s\n", nam, val);
		  return 0;
		}

	
		. line 8: chúng ta thử lấy giá trị của biến môi trường có tên CPPINSTITUTE;
	
		. line 14: chúng ta in giá trị biến nếu nó đã được tìm thấy...
	
		. line 11: ... hoặc chúng ta in một thông điệp chẩn đoán trong trường hợp khác.

	- Note: chúng ta return các giá trị khác nhau trong cả hai trường hợp.

	- Code, được compiled và chạy mà không có bất kỳ chuẩn bị trước nào, in ra message:

		CPPINSTITUTE undefined

	- Có vẻ đoạn code có phần... vô dụng không?

	- Not at all - chúng tôi sẽ sử dụng nó sớm và nó sẽ giúp ích rất nhiều.

	- Chúng tôi giả định rằng bạn cũng đã biên dịch code và bạn có một file thực thi có tên:

		. 05.01.getenv trong Unix/Linux
		. 05.01.getenv.exe trong MS Windows

	- Thật không may, câu chuyện của chúng tôi phân nhánh ở điểm này. Chúng tôi không thể tiếp tục nó trong một thread duy nhất. Sẽ có hai con đường từ đây: một cho Unix/Linux và một cho MS Windows.


5.1.1.7
	- Để tạo một biến môi trường mới, hoặc sửa đổi hoặc loại bỏ một biến môi trường hiện có trong Unix/Linux, bạn nên sử dụng hai hàm khác nhau - xem code:

		#include <stdlib.h>

		int setenv (char *name, char *value, int overwrite);
		int unsetenv (char *name);

	- Hàm setenv() tạo một biến mới hoặc sửa đổi một biến hiện có. Nó cần ba tham số:

		1. Tên của biến (char *)

		2. Giá trị mới của nó (char *)

		3. Một overwrite flag (nếu giá trị khác 0, bạn đồng ý ghi đè giá trị đã được xác định trước đó; ngược lại thì, giá trị trước đó sẽ không thay đổi và setenv() coi đó là một hoạt động thành công)

	- Hàm unsetenv() loại bỏ bất kỳ biến môi trường đã defined nào. Nó chỉ cần một tham số chứa tên của biến.

	- Kết quả (trong cả hai trường hợp) là:
		
		. 0 nếu thành công;
		. -1 nếu có lỗi (errno sẽ cung cấp thông tin chi tiết hơn).


5.1.1.8
	- Bây giờ chúng ta giả sử rằng code đã được compiled trước đó đang nằm trong cùng một thư mục với example hiện tại - xem example:

		#include <stdio.h>
		#include <stdlib.h>

		int
		main (void)
		{
		  char *nam = "CPPINSTITUTE";
		  char *val = "YES";
		  char *prg = "./05.01.getenv";
		  int ret = system (prg);
		  printf ("ret=%d\n---------------\n", ret);
		  setenv (nam, val, 1);
		  ret = system (prg);
		  printf ("ret=%d\n---------------\n", ret);
		  unsetenv (nam);
		  ret = system (prg);
		  printf ("ret=%d\n---------------\n", ret);
		  return 0;
		}

	- The code is simple. Nó khởi chạy chương trình thực thi 05.01.getenv ba lần:
		
		. line 10: Lần đầu tiên, với môi trường không chứa biến yêu thích của chúng ta (biến được đặt tên là CPPINSTITUTE)
		
		. line 13: Tiếp theo, với biến được chèn vào môi trường bởi lời gọi setenv();
		
		. line 16: Cuối cùng, với môi trường đã loại bỏ biến bằng hàm unsetenv().

	- Output của code là:

		CPPINSTITUTE undefined
		ret=256
		---------------
		CPPINSTITUTE=YES
		ret=0
		---------------
		CPPINSTITUTE undefined
		ret=256
		---------------


5.1.1.9
	- Để tạo một biến môi trường mới, hoặc sửa đổi hoặc xóa một biến môi trường hiện tại trên MS Windows và trình biên dịch MS CL, bạn sử dụng một hàm:

		#include <stdlib.h>

		int putenv(char *nameval);

	- Hàm putenv() expects một tham số chứa một string ở một trong hai possible form như sau:
		
		. NAME=VAL để định nghĩa một biến có tên NAME với giá trị VAL;

		. NAME= để loại bỏ biến có tên NAME khỏi môi trường.

	- Kết quả (ở cả hai trường hợp) là:

		. 0 khi thành công;
		
		. -1 khi có lỗi.

	- Và đây là một phiên bản MS Windows của code đã được trình bày trước đó - hãy xem code:

		#include <stdio.h>
		#include <stdlib.h>

		int
		main (void)
		{
		  char *nam = "CPPINSTITUTE";
		  char *val = "YES";
		  char *prg = "05.01.getenv.exe";
		  int ret = system (prg);
		  printf ("ret=%d\n---------------\n", ret);
		  char buf[100];
		  sprintf (buf, "%s=%s", nam, val);
		  putenv (buf);
		  ret = system (prg);
		  printf ("ret=%d\n---------------\n", ret);
		  sprintf (buf, "%s=", nam);
		  putenv (buf);
		  ret = system (prg);
		  printf ("ret=%d\n---------------\n", ret);
		  return 0;
		}

	- Note: chúng tôi đã sử dụng hàm sprintf() để xây dựng các strings cần thiết cho putenv().

	- Kết quả của nó là:

		CPPINSTITUTE undefined
		ret=1
		---------------
		CPPINSTITUTE=YES
		ret=0
		---------------
		CPPINSTITUTE undefined
		ret=1
		---------------


5.1.2.1
	- Để tạo một process con mới trên Unix/Linux và chạy nó đồng thời với process cha, bạn nên sử dụng một hàm có tên là fork():

		#include <unistd.h>

		pid_t fork(void);

	- Hàm fork() là một hàm rất độc đáo và tuyệt vời, mặc dù nó trông khá khiêm tốn. Vậy nó đáng để xem xét như nào?

	- Nói chung, một hàm có một điểm vào và một điểm ra – điều này là rõ ràng. Nếu bạn gọi một hàm, bạn mong đợi rằng nó sẽ trả lại quyền kiểm soát cho điểm ban đầu. Tất nhiên, có một số ngoại lệ. Ví dụ, hàm exit() có một điểm vào và không có điểm ra nào cả (mặc dù tên của nó là exit). Nếu bạn gọi exit() và nó thành công, nó sẽ không trở lại cho bạn.

	- Nhưng fork() là độc đáo hơn nhiều. Nếu nó thành công, nó chỉ có một điểm vào, nhưng có hai điểm ra! Yes! Làm thế nào điều này có thể xảy ra?

	- Khi bạn gọi hàm fork(), những điều bí ẩn sau đây xảy ra:

		. Hệ điều hành đóng băng process của bạn (nó không hiển thị hoạt động)

		. Hệ điều hành nhân bản process của bạn, vì vậy thực tế có hai process sinh đôi, hoàn toàn giống nhau: một cha và một con;

		. Hệ điều hành đánh thức cả hai process – mỗi process đều có cảm giác rằng chúng đã trở lại từ hàm fork() (đây là lý do tại sao chúng tôi nói rằng fork() có hai điểm ra)

		. Các process bây giờ bắt đầu hoạt động song song.

	- Chúng tôi hy vọng rằng có một seed of doubt trong tâm trí của bạn và bạn sẵn sàng đặt câu hỏi sau: làm thế nào chúng ta phân biệt một cha từ một con và ngược lại? Cả hai process có nhận biết được rằng họ là cha hay con không?

	- Yes, chúng nhận biết được. Hãy xem cách điều này có thể xảy ra – thông tin đến từ kết quả của fork (BTW, kiểu pid_t là một từ đồng nghĩa của kiểu int đủ dài để lưu trữ PIDs):

		. -1 có nghĩa là fork() đã thất bại; không có process con nào được tạo (điều này có thể xảy ra khi bạn đã có quá nhiều process con, hoặc khi quyền của bạn quá yếu)

		. 0 có nghĩa là fork() đã thành công và bạn hiện có một process con;

		. một giá trị lớn hơn 0 có nghĩa là fork() đã thành công và bạn hiện có một process cha (giá trị này là PID của con của bạn).

	- Looks suspicious? Maybe, at first glance. Nhưng hãy để chúng tôi cho bạn xem một ví dụ.


5.1.2.2
	- Code sau:

		#include <stdio.h>
		#include <errno.h>
		#include <string.h>
		#include <unistd.h>

		int
		main (void)
		{
		  int v = fork ();
		  if (v == 0)
		    {				/* child */
		      printf ("I'm a child\n");
		      return 0;
		    }
		  else if (v > 0)
		    {				/* parent */
		      printf ("I'm a parent\n");
		      return 0;
		    }
		  else
		    {				/* failure */
		      printf ("fork() failed - %s\n", strerror (errno));
		      return 1;
		    }
		}

		
		. line 9: đây là nơi process của bạn được phân nhánh (nhân bản); hãy tưởng tượng rằng từ điểm này trở đi có hai process;
		
		. line 10: một trong số chúng (process con) nhận thấy rằng biến v bằng không; nó nói: "Okay, tôi là một đứa trẻ. Tôi sẽ cư xử như một đứa trẻ." Và nó thực hiện;
		
		. line 15: cái thứ hai (process cha) nhận giá trị biến v là một giá trị dương; nó kiểu: "Ôi Trời ơi, tôi là một cha. Tôi muốn nói với cả thế giới." Và nó làm điều đó.

	- Output của code trên như sau:

		I'm a parent
		I'm a child

	hoặc có thể như sau:

		I'm a child
		I'm a parent

	- Hoàn toàn là sự trùng hợp ngẫu nhiên khi quá trình nào trong hai quá trình ở dòng đầu tiên.


5.1.2.3
	- What does it really mean that the process is forked (phân nhánh)/cloned (nhân bản)?

	- Nó có nghĩa là process, với tất cả các thành phần cần thiết của nó, được nhân đôi. Việc nhân đôi bao gồm trạng thái của tất cả dữ liệu mà nó chứa, nhưng không nhất thiết phải là segment code. Như chúng ta đã nói trước đó, segment code, như một thành phần hoàn toàn không thể thay đổi của process, có thể được chia sẻ giữa các process khác nhau.

	- Hãy xem cách nó hoạt động - nhìn code:

		#include <stdio.h>
		#include <errno.h>
		#include <string.h>
		#include <unistd.h>

		char text[] = "ORIGINAL";

		int
		main (void)
		{
		  int v = fork ();
		  if (v == 0)
		    {				/* child */
		      strcpy (text, "CHILD");
		      printf ("I'm a child: %s\n", text);
		      return 0;
		    }
		  else if (v > 0)
		    {				/* parent */
		      strcpy (text, "PARENT");
		      printf ("I'm a parent: %s\n", text);
		      return 0;
		    }
		  else
		    {				/* failure */
		      printf ("fork() failed - %s\n", strerror (errno));
		      return 1;
		    }
		}

		
		. line 6: chúng ta khai báo một mảng chứa string ORIGINAL; mảng này được đặt bên ngoài bất kỳ hàm nào, vì vậy nó sẽ được tạo ra trước khi hàm main() được khởi chạy;
		
		. line 14: process con đặt string thành một giá trị mới phản ánh bản chất của process...
		
		. line 20: …và process cha cũng làm điều đó.

	- Output của code trên như sau:

		I'm a parent: PARENT
		I'm a child: CHILD

	- Như bạn đã biết, hai dòng này có thể xuất hiện theo thứ tự ngược lại. 

	- Chúng ta có thể nói rằng mỗi process có một đoạn dữ liệu riêng - chúng hoàn toàn tách biệt.


5.1.2.4
	- Để thực hiện một số thử nghiệm nâng cao hơn, chúng ta cần một số hàm mới - đây là hàm đầu tiên:

		#include <unistd.h>

		unsigned int sleep(unsigned int secs);

	- Hàm này thực hiện những gì nó hứa hẹn: nó đưa process vào chế độ ngủ; process sẽ ngủ ít nhất secs giây. Note: việc ngủ có thể bị gián đoạn bởi một cái gọi là signal (tín hiệu) - một loại gián đoạn ảnh hưởng đến process (ví dụ: một trong những tín hiệu có thể xảy ra do nhấn Ctrl-C). Khi không có tín hiệu nào xảy ra, quá trình ngủ sẽ không bị gián đoạn.

	- Hàm returns:
		
		. 0 nếu thời gian đã được xác định đã trôi qua.
		
		. Khác 0 nếu quá trình ngủ đã bị gián đoạn và kết quả cho biết còn bao nhiêu giây để ngủ.

	- Hàm khác được giới thiệu ở đây:

		#include <unistd.h>			(chatGPT tự thêm khúc <>)
		#include <sys/types.h>		(chatGPT tự thêm khúc <>)

		pid_t getpid(void);

	- Hàm này lấy PID của invoking process. Surprise! Hàm này luôn thành công!

	- Mặc dù có tên là wait(), hàm này không có gì chung với sleep():

		#include <sys/wait.h>		(chatGPT tự thêm khúc <>)

		pid_t wait(int *wstatus);

	- Hàm wait() đợi cho đến khi một trong những process con của nó hoàn tất. Nó có thể được gọi theo hai cách:
		
		. Khi đối số wstatus được thiết lập thành NULL - chúng ta không muốn biết về trạng thái kết thúc của process con (the return code)
		
		. Khi đối số wstatus trỏ đến bất kỳ biến int nào - chúng ta muốn trạng thái kết thúc của process con được lưu trữ trong biến đó.

	- Hàm return các kết quả sau:

		. -1 nếu có lỗi;

		. PID của process con đã chấm dứt (Note: nếu process con đã kết thúc trước khi wait() được gọi, nó sẽ trả về ngay lập tức).


5.1.2.5
	- Nhìn code:

		#include <unistd.h>
		#include <stdio.h>
		#include <string.h>
		#include <errno.h>
		#include <sys/types.h>
		#include <sys/wait.h>


		#define		SECS 	5

		int
		main (void)
		{
		  int pid = fork ();
		  if (pid == 0)
		    {
		      printf
			("Hi, I'm a child with PID=%d and I going to sleep for %d seconds...\n",
			 getpid (), SECS);
		      sleep (SECS);
		      printf ("Hi again, I'm a child and I woke up!\n");
		      return 27;
		    }
		  else if (pid == -1)
		    {
		      fprintf (stderr, "Fork failed: %s\n", strerror (errno));
		      return 1;
		    }
		  printf ("Hi, I'm a parent and I am waiting for my child to finish...\n");
		  int status, child = wait (&status);
		  printf ("PID=%d, retcode=%d\n", child, WEXITSTATUS (status));
		  return 0;
		}

	- Chúng ta cần nhấn mạnh một điều rất quan trọng – bạn đã để ý rằng tất cả các lời gọi printf() của chúng ta đều có định dạng kết thúc bằng \n chưa? Is it intensional? Yes. Tại sao chúng ta làm thế?

	- Hàm printf() thường giữ dữ liệu đang được gửi đến đầu ra trong bộ đệm, nhưng nó sẽ xả bộ đệm khi nó thấy một ký tự xuống dòng ở cuối dữ liệu. Khi có nhiều quá trình xuất ra stdout trong một phiên terminal, các luồng khác nhau có thể ảnh hưởng lẫn nhau, và khá có thể bạn sẽ không thấy bất kỳ điều gì trên màn hình cho đến khi các bộ đệm được xả. Việc sử dụng xuống dòng giúp chúng ta kiểm soát quá trình.

	- Vì vậy:
	
		. line 9: chúng ta định nghĩa một khoảng thời gian ngủ ở đây – bạn có thể thay đổi nó và xem nó làm thay đổi code thực thi như thế nào;
	
		. line 17: chúng ta tạo ra một process con; process con thông báo PID của mình và kể cho chúng ta về những kế hoạch của nó;
	
		. line 20: process con đang ngủ (không lâu);
	
		. line 21: process con thức dậy, thông báo và kết thúc hoạt động của mình bằng cách return a strange little return code;
	
		. line 30: process cha đang đợi cho đến khi process con hoàn thành và muốn biết return code của nó là gì;
	
		. line 31: điều ta mong đợi cuối cùng xảy ra và process cha nhận được những gì nó muốn.

	- Khi code được biên dịch và chạy, nó output như sau (bạn sẽ phải đợi năm giây để xem nó):

		Chào, tôi là một process cha và tôi đang đợi cho đến khi con tôi kết thúc...


		Chào, tôi là một process con với PID=7409 và tôi sẽ ngủ trong 5 giây...


		Chào lại, tôi là một process con và tôi đã thức dậy!


		PID=7409, mã trả về=27

	- Tất nhiên, một process cha có thể đợi nhiều hơn một process con cùng một lúc. Let see it.


5.1.2.6
	- Nhìn code:

		#include <unistd.h>
		#include <stdio.h>
		#include <stdlib.h>
		#include <string.h>
		#include <errno.h>
		#include <sys/types.h>
		#include <sys/wait.h>

		#define		SECS 		10
		#define		CHILDREN	3

		int
		main (void)
		{
		  int c;
		  for (c = 0; c < CHILDREN; c++)
		    {
		      int pid = fork ();
		      if (pid == 0)
			{
			  srand (getpid ());
			  int secs = rand () % SECS + 1;
			  printf ("Child: PID=%d sleep=%d sec\n", getpid (), secs);
			  sleep (secs);
			  printf ("Child: PID=%d woke up!\n", getpid ());
			  return 27;
			}
		      else if (pid == -1)
			{
			  fprintf (stderr, "Fork failed: %s\n", strerror (errno));
			  return 1;
			}
		    }
		  printf ("Parent is waiting...\n");
		  for (c = 0; c < CHILDREN; c++)
		    {
		      int status, child = wait (&status);
		      printf ("Parent: child exited: PID=%d, retcode=%d\n", child,
			      WEXITSTATUS (status));
		    }
		  return 0;
		}

	- Chúng tôi đã sửa đổi ví dụ trước để đạt được những mục tiêu sau:

		. sẽ có ba process con (giá trị được định nghĩa bởi ký hiệu CHILDREN);
		
		. thời gian ngủ của chúng là ngẫu nhiên (mỗi process con tự lấy nó), nhưng không lâu hơn SECS giây.

	- Code làm việc như thế nào?
		
		. line 16: vòng lặp for đầu tiên tạo ra ba process con;
		
		. line 21: mỗi process con đặt seed riêng của nó cho random generator (bộ sinh số ngẫu nhiên); note rằng sử dụng một trick đã sử dụng trước đó, random(time(NULL)) có thể không hoạt động ở đây, vì việc tạo ra các process con có thể diễn ra rất nhanh và tất cả các process con có thể nhận cùng một thời gian và do đó đặt cùng một seed;
		
		. line 35: một process cha đang đợi cho tất cả ba process con.

	- Code outputs như sau (be patient):

		Child: PID=7665 sleep=5 sec
		Parent is waiting...


		Child: PID=7667 sleep=8 sec


		Child: PID=7666 sleep=4 sec


		Child: PID=7666 woke up!


		Parent: child exited: PID=7666, retcode=27


		Child: PID=7665 woke up!


		Parent: child exited: PID=7665, retcode=27


		Child: PID=7667 woke up!


		Parent: child exited: PID=7667, retcode=27

	- Một process cha cũng có thể đợi cho một process con cụ thể. Có một hàm đặc biệt để làm điều đó.


5.1.2.7
	- Hàm waitpid() chờ đợi con của một PID cụ thể:

		#include <sys/wait.h>

		pid_t waitpid(pid_t pid, int *wstatus, int options);
	
	- Chúng tôi sẽ giới thiệu một trong những biến thể gọi hàm được sử dụng phổ biến nhất, nhưng bạn nên tham khảo trong OS manual để biết thêm chi tiết:
	
		. Đối số pid chỉ định PID của các process con chúng ta muốn đợi, hoặc nếu nó bằng -1, nó sẽ đợi cho bất kỳ process con nào;
		
		. Đối số wstatus nhận đúng vai trò giống như hàm wait();
		
		. Đối số options có giá trị là 0.

	- Hàm return kết quả như sau:
		
		. -1 nếu có lỗi;
		
		. PID của process con đã kết thúc.

	- Note: Cuộc gọi hàm sau:

		wait(&stat);
	
	tương đương với:

		waitpid(-1, &stat, 0);
	
	- Điều này có nghĩa là nếu bạn muốn đợi cho bất kỳ process con nào và có được trạng thái kết thúc của nó, bạn có thể sử dụng cả wait() hoặc waitpid() với các đối số cụ thể. (line này của chatGPT)


5.1.2.8
	- Nhìn code:

		#include <unistd.h>
		#include <stdio.h>
		#include <stdlib.h>
		#include <string.h>
		#include <errno.h>
		#include <sys/types.h>
		#include <sys/wait.h>

		#define		SECS 		10
		#define		CHILDREN	3

		int
		main (void)
		{
		  int c;
		  int pids[CHILDREN];

		  for (c = 0; c < CHILDREN; c++)
		    {
		      int pid = fork ();
		      if (pid == 0)
			{
			  srand (getpid ());
			  int secs = rand () % SECS + 1;
			  printf ("Child: PID=%d sleep=%d sec\n", getpid (), secs);
			  sleep (secs);
			  printf ("Child: PID=%d woke up!\n", getpid ());
			  return 27;
			}
		      else if (pid == -1)
			{
			  fprintf (stderr, "Fork failed: %s\n", strerror (errno));
			  return 1;
			}
		      pids[c] = pid;
		    }
		  for (c = 0; c < CHILDREN; c++)
		    {
		      printf ("Parent: waiting for child #%d\n", c);
		      int status, child = waitpid (pids[c], &status, 0);
		      printf ("Parent: child #%d exited: PID=%d, retcode=%d\n",
			      c, child, WEXITSTATUS (status));
		    }
		  return 0;
		}

	- Cha đã thay đổi thói quen đợi của nó. Bây giờ nó đợi cho các tiến trình con theo thứ tự chúng đã được tạo.
		
		. line 16: chúng ta thêm một mảng để lưu trữ các PID của các tiến trình con;
		
		. line 35: chúng ta cập nhật nó ở mỗi vòng lặp;
		
		. line 40: chúng ta sử dụng các giá trị từ mảng để gọi hàm waitpid().

	- Output như sau (yours will be different, of course):

		Child: PID=8261 sleep=3 sec


		Parent is waiting...


		Child: PID=8262 sleep=8 sec


		Parent: waiting for child #0


		Child: PID=8263 sleep=8 sec


		Child: PID=8261 woke up!


		Parent: child #0 exited: PID=8261, retcode=27


		Parent: waiting for child #1


		Child: PID=8262 woke up!


		Child: PID=8263 woke up!


		Parent: child #1 exited: PID=8262, retcode=27


		Parent: waiting for child #2


		Parent: child #2 exited: PID=8263, retcode=27


5.1.2.9
	- Bây giờ chúng tôi muốn giới thiệu với bạn về một họ các hàm rất tương tự - những siblings được thiết kế để thực hiện cùng một hành động, nhưng một cách khác nhau một chút.

	- Tất cả những hàm này đều có khả năng tải code thực thi vào bộ nhớ, và họ làm điều đó một cách triệt để: code mà chúng fetch thay thế code thực thi của người gọi. Điều này có nghĩa là hàm không return to the invoker và the invoker bị loại bỏ khỏi bộ nhớ khi hàm thành công.

	- Note: đây là hoạt động cơ bản nhất được thực hiện bởi các hệ thống Unix/Linux để bắt đầu mỗi quá trình mới.

	- The whole family’s gathered in the editor:

		#include <unistd.h>

		int execl (char *path, char arg, ... /* NULL */ );
		int execle (char *path, char *arg, ... /* NULL, char *envp[] */ );
		int execlp (char *file, char arg, ... /* NULL */ );
		int execv (char *path, char *argv[]);
		int execve (char *file, char *argv[], char *envp[]);
		int execvp (char *file, char *argv[]);
		int execvpe (char *file, char *argv[], char *envp[]);

	- Tất cả những tên của họ bắt đầu bằng exec, bởi vì chúng được thiết kế để thực thi một foreign (external) program. Tất cả những tên của họ có các hậu tố mô tả khả năng của chúng:
		
		. hậu tố l cho biết rằng hàm sử dụng một variadic argument list (danh sách đối số biến đổi) để truyền các đối số đến chương trình được khởi chạy (danh sách phải kết thúc bằng con trỏ NULL)
		
		. hậu tố p nói rằng hàm sẽ tìm kiếm chương trình để thực thi như cách nó được thực hiện bởi shell (nghĩa là tất cả các thư mục từ biến môi trường PATH sẽ được tìm kiếm); các hàm có hậu tố này interpret tham số đầu tiên như tên của file để chạy; các hàm không có hậu tố này cần đường dẫn đầy đủ đến chương trình;
		
		. hậu tố e nói rằng các hàm sẽ chuẩn bị một môi trường mới cho chương trình (sẽ được truyền qua một tham số bổ sung có tên envp); nếu không, hàm sẽ sao chép môi trường hiện tại;
		
		. hậu tố v nói rằng hàm không sử dụng danh sách đối số biến đổi, mà thay vào đó sử dụng một mảng.

	- Tất cả các hàm đều return -1 nếu xảy ra lỗi (errno hoạt động như thông thường). Chúng sẽ không return bất cứ điều gì nếu không có lỗi - tại sao?
		Chúng sẽ không return bất cứ điều gì vì chúng sẽ không return cho chúng ta chút nào - chúng sẽ chuyển quyền kiểm soát cho chương trình mới được khởi chạy.


5.1.2.10
	- Code sau:

		#include <stdio.h>
		#include <stdlib.h>
		#include <unistd.h>

		int
		main (int argc, char *argv[])
		{
		  if (argc != 2)
		    {
		      fprintf (stderr, "usage: %s seconds\n", argv[0]);
		      return 1;
		    }
		  char *endptr;
		  int secs = strtol (argv[1], &endptr, 10);
		  if (secs <= 0 || *endptr != '\0')
		    {
		      fprintf (stderr, "argument must be an int greater than 0 - exiting\n");
		      return 2;
		    }
		  printf ("#%d will wait %d seconds...\n", getpid (), secs);
		  int i;
		  for (i = 0; i < secs; i++)
		    {
		      printf ("#%d -> %d...\n", getpid (), secs - i);
		      sleep (1);
		    }
		  printf ("#%d completed\n", getpid ());
		  return 0;
		}

		
		. line 8: chương trình cần đúng một đối số - một số giây để sử dụng trong hệ thống;
		
		. line 14: chúng ta cố gắng chuyển đổi đối số đầu tiên thành một số nguyên và xuất một thông báo khi nó thất bại (hàm strtol() nhận ba đối số: một con trỏ đến chuỗi đang được chuyển đổi, một con trỏ đến con trỏ nơi hàm sẽ đặt địa chỉ của ký tự chưa được chuyển đổi lần đầu tiên (nó sẽ là \0 khi giá trị là một số nguyên hợp lệ) và một radix conversion (ở đây chúng ta sử dụng 10, điều này có vẻ là một sự lựa chọn rõ ràng)
		
		. line 20: chúng ta thông báo về sự bắt đầu của đếm ngược của chúng ta...
		
		. line 24: ...và chúng ta thực hiện nó.

	- Giả sử rằng source code đã được compiled và file thực thi có tên là 05.02.prog tồn tại, chương trình, được khởi chạy như sau:

		./05.02.prog 5

	tạo ra đầu ra như sau:

		#8759 will wait 5 seconds...
		#8759 -> 5...
		#8759 -> 4...
		#8759 -> 3...
		#8759 -> 2...
		#8759 -> 1...

	- Tất nhiên PID của quá trình có thể khác nhau.

	- Đầu tiên, hãy sử dụng code để hiển thị cách hàm execlp() hoạt động.


5.1.2.11
	- Code sau là một biến thể ít được sửa đổi của đoạn code 05.02.wait2:

		#include <unistd.h>
		#include <stdio.h>
		#include <stdlib.h>
		#include <string.h>
		#include <errno.h>
		#include <sys/types.h>
		#include <sys/wait.h>

		#define		SECS 		10
		#define		CHILDREN	3

		int
		main (void)
		{
		  int c;

		  for (c = 0; c < CHILDREN; c++)
		    {
		      int pid = fork ();
		      if (pid == 0)
			{
			  srand (getpid ());
			  int secs = rand () % SECS + 1;
			  char buf[10];
			  sprintf (buf, "%d", secs);
			  execlp ("./05.02.prog", "./05.02.prog", buf, NULL);
			  fprintf (stderr, "exec failed: %s", strerror (errno));
			  return 1;
			}
		      else if (pid == -1)
			{
			  fprintf (stderr, "Fork failed: %s\n", strerror (errno));
			  return 1;
			}
		    }
		  for (c = 0; c < CHILDREN; c++)
		    {
		      int status, child = wait (&status);
		      printf ("Parent: child #%d exited: PID=%d, retcode=%d\n",
			      c, child, WEXITSTATUS (status));
		    }
		  return 0;
		}

	- Code này có những thay đổi là:

	
		. line 25: số giây được chuyển đổi thành một string (chúng ta cần điều này để chuẩn bị một lời gọi execlp() đúng đắn)
	
		. line 26: chúng ta gọi hàm execlp() và các đối số tiếp theo chỉ định:
			
			. chương trình cần khởi chạy;
			
			. argv[0] cho chương trình (note: điều này không được lấy từ đối số đầu tiên mặc định, mà phải được chỉ định rõ ràng)
			
			. argv[1] cho chương trình;
			
			. và NULL được sử dụng as a variadic list guardian.
	
		. line 27: note: chúng ta không kiểm tra kết quả của execlp() - điều này không cần thiết; chúng ta đến đây khi và chỉ khi execpl() thất bại.

	- Giả sử rằng 05.02.prog tồn tại trong cùng thư mục với 05.02.execlp executable, chương trình sẽ tạo ra output như sau:

		#8817 will wait 9 seconds...


		#8817 -> 9...


		#8818 will wait 3 seconds...


		#8818 -> 3...


		#8819 will wait 2 seconds...


		#8819 -> 2...


		#8817 -> 8...


		#8818 -> 2...


		#8819 -> 1...


		#8817 -> 7...


		#8818 -> 1...


		#8819 completed


		Parent: child #0 exited: PID=8819, retcode=0


		#8817 -> 6...


		#8818 completed


		Parent: child #1 exited: PID=8818, retcode=0


		#8817 -> 5...


		#8817 -> 4...


		#8817 -> 3...


		#8817 -> 2...


		#8817 -> 1...


		#8817 completed


		Parent: child #2 exited: PID=8817, retcode=0

	- Your PIDs will be different than ours, we suppose.


5.1.2.12
	- Dưới đây là đoạn code sau khi được sửa đổi để sử dụng execvp() thay vì execlp():

		#include <unistd.h>
		#include <stdio.h>
		#include <stdlib.h>
		#include <string.h>
		#include <errno.h>
		#include <sys/types.h>
		#include <sys/wait.h>

		#define		SECS 		10
		#define		CHILDREN	3

		int
		main (void)
		{
		  int c;

		  for (c = 0; c < CHILDREN; c++)
		    {
		      int pid = fork ();
		      if (pid == 0)
			{
			  srand (getpid ());
			  int secs = rand () % SECS + 1;
			  char buf[10];
			  sprintf (buf, "%d", secs);
			  char *newargv[3];
			  newargv[0] = "./05.02.prog";
			  newargv[1] = buf;
			  newargv[2] = NULL;
			  execvp ("./05.02.prog", newargv);
			  fprintf (stderr, "exec failed: %s", strerror (errno));
			  return 1;
			}
		      else if (pid == -1)
			{
			  fprintf (stderr, "Fork failed: %s\n", strerror (errno));
			  return 1;
			}
		    }
		  for (c = 0; c < CHILDREN; c++)
		    {
		      int status, child = wait (&status);
		      printf ("Parent: child #%d exited: PID=%d, retcode=%d\n",
			      c, child, WEXITSTATUS (status));
		    }
		  return 0;
		}

		
		. line 26: Chúng ta khai báo một mảng ba phần tử để xây dựng một mảng argv[] mới;
		
		. line 27: Chúng ta thiết lập nó với các giá trị tiếp theo (lưu ý NULL được đặt ở phần tử cuối cùng);
		
		. line 30: Chúng ta gọi execvp().

	- Chúng ta mong đợi to see very similar output as previously. Check if we're right.


5.1.2.13
	- Hiện tượng cuối cùng chúng tôi muốn kể cho bạn về là bom fork.

	- Thực tế, đó là một đoạn code rất ngắn và đơn giản mà không lâu trước đây có thể kill nhiều hệ thống Unix/Linux. May mắn thay, modern OS kernels biết cách quản lý những loại đe dọa như vậy.

	- Một trong những dạng bom fork có thể trông như sau:

		#include <unistd.h>

		int main(void) { for(;;) fork(); }

	- Như bạn có thể đã nghi ngờ, đoạn code tạo ra zillions of children để overpower the OS, và nếu OS tuân theo code và thực hiện những gì đã được yêu cầu, nó sẽ chết trong đau đớn sau vài giây.

	- Bạn có thể thử nghiệm đoạn code này trên hệ thống của bạn - nếu bạn dám.

	- Nhớ, bạn đã được cảnh báo - đó là một quả bom. Nó có thể phát nổ.


5.1.3.1 Processes and threads – creating processes (the MS Windows way)
	- Như bạn có thể đã chú ý, triết lý của MS Windows khác biệt đáng kể so với những gì được quan sát trong Unix/Linux. Thông thường, Unix/Linux cung cấp một nhóm các hàm đơn giản, cơ bản và nhẹ sử dụng giao diện ngắn và trực tiếp. Một tập hợp các hàm này phải được kết hợp với nhau để thực hiện một hành động.

	- MS Windows thích chia sẻ các hàm rất phức tạp, có nhiều tham số và nặng nề có thể thực hiện các hành động phức tạp một cách hoàn toàn độc lập. Ví dụ, MS Windows không có hàm tương đương trực tiếp của hàm fork(), mặc dù chức năng rất tương đồng được ẩn bên trong một cơ chế khác, linh hoạt hơn.

	- Tất nhiên, nhiều trong số các hàm của MS Windows mô phỏng hành vi của các dịch vụ Unix/Linux - không thể khác được, vì C language có nguồn gốc từ Unix.

	- Hãy bắt đầu cuộc hành trình của chúng ta đến MS Windows process world với quan sát rằng bộ hàm exec..() nổi tiếng cũng có sẵn ở đây.

	- This is what they look like:

		#include <process.h>

		intptr_t execl (char *cmdname, char *arg0, ... const char *argn, NULL);
		intptr_t execle (char *cmdname, char *arg0, ... const char *argn, NULL,
				 char **envp);
		intptr_t execlp (char *cmdname, char *arg0, ... const char *argn, NULL);
		intptr_t execlpe (char *cmdname, char *arg0, ... char *argn, NULL,
				  char *envp);
		intptr_t execv (char *cmdname, char *const *argv);
		intptr_t execve (char *cmdname, char *const *argv, char *const *envp);
		intptr_t execvp (char *cmdname, char *const *argv);
		intptr_t execvpe (char *cmdname, char *const *argv, char **envp);

	- Note: kiểu intptr_t là một kiểu signed integer đủ lớn để lưu trữ một con trỏ (32 bits long in a 32-bit OS, and 64 bits long in a 64-bit OS).

	- Các ý nghĩa của hậu tố là giống nhau như trong Unix/Linux:
	
		. e – một môi trường được chuyển đến một process mới;
	
		. l – các đối số dòng lệnh được chuyển đến một process mới dưới dạng một variadic list;
	
		. p – biến môi trường PATH sẽ được sử dụng để tìm một file thực thi;
	
		. v – các đối số dòng lệnh được chuyển đến một process mới dưới dạng một mảng.

	- Kết quả cũng giống nhau: -1 - đã xảy ra lỗi (errno biết thêm). Hàm không return to the invoker khi nó thành công, vì vậy việc kiểm tra giá trị trả về của nó với các số khác -1 là vô nghĩa.


5.1.3.2
	- Chương trình sau:

		#include <stdio.h>
		#include <string.h>

		int
		main (int argc, char *argv[], char **envp)
		{
		  int i;
		  for (i = 0; i < argc; i++)
		    printf ("\nargv[%d] = \'%s\'", i, argv[i]);
		  printf ("\n\n");
		  char **p = envp;
		  char *path = "Path=";
		  int len = strlen (path);
		  while (*p != NULL)
		    {
		      if (strncmp (path, *p, len) == 0)
			{
			  printf ("%s\n", *p);
			  break;
			}
		      p++;
		    }
		  return 0;
		}

	thực hiện hai công việc:

		1. Chuyển tất cả các giá trị từ argv[] ra stdout;
		2. Quét môi trường để tìm biến Path và in nó ra stdout.

	- Nhiệm vụ đầu tiên được thực hiện theo cách rất bình thường. Nhiệm vụ thứ hai được thực hiện bằng cách sử dụng hàm strncmp(), nó tìm string Path= ở đầu của mỗi biến được lưu trữ trong môi trường. Khi nó tìm thấy nó, nó in ra giá trị và vòng lặp while is broken.


5.1.3.3
	- Ví dụ đầu tiên của chúng ta cho thấy cách sử dụng hàm execlp() để khởi chạy một chương trình bên ngoài, thay thế process hiện tại, và cách chuẩn bị môi trường hoàn toàn mới cho nó.

		#include <stdio.h>
		#include <process.h>

		int
		main (int argc, char *argv[], char **envp)
		{
		  char *myenv[2] = {
		    "Path=If the path be beautiful, let us not ask where it leads.",
		    NULL
		  };
		  execle ("05.03.prog.exe", "05.03.prog.exe", "arg1", "arg2", NULL, myenv);
		  printf ("Something really bad happened - we should not be here!\n");
		  return 1;
		}


		. line 7: Môi trường mới của chúng ta được đơn giản hóa hết mức - nó chỉ chứa một biến với một câu trích dẫn từ Anatole France;

		. một chương trình có tên là 05.03.prog.exe được tìm kiếm, được fetched và bắt đầu (chúng tôi giả định rằng file thực thi được đặt trong cùng một thư mục như 05.03.execle.exe); có hai đối số cho chương trình.

	- Chương trình tạo ra đầu ra sau:

		argv[0] = '05.03.prog.exe'
		argv[1] = 'arg1'
		argv[2] = 'arg2'

		Path=If the path be beautiful, let us not ask where it leads.


5.1.3.4
	- Và bây giờ almost the same code, nhưng với hàm execve():

		#include <stdio.h>
		#include <string.h>
		#include <stdlib.h>
		#include <process.h>

		int
		main (int argc, char *argv[], char **envp)
		{
		  char **p = envp;
		  while (*p)
		    {
		      if (strncmp (*p, "Path=", 5) == 0)
			{
			  *p =
			    "Path=If the path be beautiful, let us not ask where it leads.";
			  break;
			}
		      p++;
		    }
		  int i;
		  char *myargv[5];
		  myargv[0] = "05.03.prog.exe";
		  for (i = 1; i < 4; i++)
		    {
		      myargv[i] = malloc (2);
		      myargv[i][0] = '0' + i;
		      myargv[i][1] = '\0';
		    }
		  myargv[4] = NULL;
		  execve ("05.03.prog.exe", myargv, envp);
		  printf ("Something really bad happened - we should not be here!\n");
		  return 1;
		}

	
		. line 10: Lần này, chúng ta không xây dựng một môi trường mới, mà là sửa đổi môi trường hiện tại; chúng ta tìm biến Path và đặt nó theo cách của chúng ta;
	
		. line 21: Chúng ta xây dựng một mảng argv mới:
			
			. Phần tử đầu tiên (argv[0]) chứa tên của chương trình được khởi chạy;
			
			. Phần tử cuối cùng (argv[4]) chứa NULL (guardian);
			
			. Các phần tử còn lại chứa các số tiếp theo bắt đầu từ 1.

	- Chương trình tạo ra đầu ra sau:

		argv[0] = '05.03.prog.exe'
		argv[1] = '1'
		argv[2] = '2'
		argv[3] = '3'

		Path=If the path be beautiful, let us not ask where it leads.


5.1.3.5
	- Ngoài exec..() family, MS Windows cung cấp một bộ hàm rất tương tự mà chức năng của chúng không chỉ bao gồm việc fetching và launching một file thực thi bên ngoài, mà còn tạo một process mới (các hàm exec..() thực hiện hành động của mình thay mặt cho quá trình hiện tại).

	- Bộ hàm có dạng như sau:

		#include <process.h>

		intptr_t spawnl (int mode, char *cmdname, char *arg0, ... const char *argn,
				 NULL);
		intptr_t spawnle (int mode, char *cmdname, char *arg0, ... const char *argn,
				  NULL, char **envp);
		intptr_t spawnlp (int mode, char *cmdname, char *arg0, ... const char *argn,
				  NULL);
		intptr_t spawnlpe (int mode, char *cmdname, char *arg0, ... char *argn, NULL,
				   char **envp);
		intptr_t spawnv (int mode, char *cmdname, char *const *argv);
		intptr_t spawnve (int mode, char *cmdname, char *const *argv,
				  char *const *envp);
		intptr_t spawnvp (int mode, char *cmdname, char *const *argv);
		intptr_t spawnvpe (int mode, char *cmdname, char *const *argv, char **envp);

	
		. So với họ exec..(), tất cả các hàm đều có một tham số bổ sung, là tham số đầu tiên, được đặt tên là mode - nó xác định cách mà process mới được tạo ra; giá trị có thể là các ký tự định nghĩa như các ký tự sau đây:
			
			. _P_OVERLAY – thay thế invoker bằng process mới và thực thi nó (nói cách khác, nó hoạt động như exec())
			
			. _P_WAIT – đợi đến khi process mới tạo ra hoàn tất (chế độ đồng bộ)
			
			. _P_NOWAIT – thực thi process mới theo cách song song (chế độ không đồng bộ)
			
			. _P_DETACH – đặt process mới into the background (process sẽ không có quyền truy cập vào stdin và stdout của bảng điều khiển)

	- Các hàm trả về một giá trị mà ký hiệu của nó thay đổi tùy thuộc vào giá trị tham số mode:
		
		. _P_OVERLAY – chỉ có -1 có ý nghĩa thực sự và chỉ ra một lỗi (errno biết thêm)
		
		. _P_WAIT – -1 khi có lỗi, hoặc trạng thái exit của các process được tạo ra;
		
		. _P_NOWAIT, _P_DETACH – -1 khi có lỗi, hoặc bộ xử lý process của process mới được tạo ra (điều này không phải là PID!)

	- Let's go use it!


5.1.3.6
	- Dưới đây là example:

		#include <stdio.h>
		#include <string.h>
		#include <stdlib.h>
		#include <process.h>
		#include <errno.h>

		int
		main (void)
		{
		  int i;
		  char *myenvp[] = {
		    "Path=PATHx",
		    NULL
		  };
		  char *myargv[] = {
		    "05.03.prog.exe",
		    "processx",
		    NULL
		  };
		  for (i = 0; i < 3; i++)
		    {
		      myargv[1][strlen (myargv[1]) - 1] = '1' + i;
		      myenvp[0][strlen (myenvp[0]) - 1] = '1' + i;
		      int ret = spawnve (_P_NOWAIT, "05.03.prog.exe", myargv, myenvp);
		      printf ("Spawn #%d: retcode=%d", i + 1, ret);
		      if (ret < 0)
			printf (" errno=%d", errno);
		      printf ("\n");
		    }
		  return 0;
		}

	
		. line 11: Chúng tôi định nghĩa một môi trường mới đơn giản với một biến (chúng tôi sửa đổi giá trị của nó cho mỗi process mới được tạo ra)
	
		. line 15: Chúng tôi cũng xây dựng một mảng argv mới với cùng một mục đích như trước;
	
		. line 20: Chúng tôi sửa đổi môi trường và argv để tạo ra một process mới với các unique settings;
	
		. line 24: Chúng tôi sử dụng tùy chọn _P_NOWAIT, vì vậy các process mới được khởi chạy một cách không đồng bộ.

	- Chương trình output như sau (lưu ý: thứ tự của các thông báo có thể khác nhau):

		Spawn #1: retcode=136
		Spawn #2: retcode=144
		Spawn #3: retcode=160
		argv[0] = '05.03.prog.exe'
		argv[0] = '05.03.prog.exe'
		argv[1] = 'process3'
		argv[1] = 'process2'
		Path=PATH3
		Path=PATH2
		argv[0] = '05.03.prog.exe'
		argv[1] = 'process1'
		Path=PATH1


5.1.3.7
	- Bây giờ chúng tôi sẽ chỉ cho bạn một giao diện MS Windows nguyên bản được thiết kế để thao tác trên các process. Giao diện này phức tạp và nặng, nên chúng tôi phải bắt đầu từ đầu. Cách này là tốt nhất.

	- Vấn đề đầu tiên mà bạn cần biết về là cấu trúc của STARTUPINFO:

		#include <windows.h>				(chatGPT thêm khúc trong <>)

		typedef struct _STARTUPINFO (...) 
		STARTUPINFO, *LPSTARTUPINFO;

	- Cấu trúc này bao gồm 18 trường định nghĩa chính xác môi trường GUI cho process mới được tạo (ví dụ: window's location, kích thước, tiêu đề, bộ đệm bảng điều khiển (nếu cần) v.v.). Trường đầu tiên, có tên là cb, lưu trữ kích thước thực tế của cấu trúc (người dùng có thể chỉ sử dụng trường đã chọn thay vì điền tất cả chúng). Trường có tên dwFlags là một bit mask chứa thông tin về các trường đã sử dụng và không sử dụng.

	- Cấu trúc này rất tổng quát và bao phủ nhiều trường hợp sử dụng khả dụng. Chúng tôi sẽ không sử dụng tất cả chúng.

	- Mô tả chi tiết về cấu trúc có sẵn xem ở link sau:
		https://learn.microsoft.com/en-us/windows/win32/api/processthreadsapi/ns-processthreadsapi-startupinfoa?redirectedfrom=MSDN

	- Hãy sử dụng cấu trúc này để chỉ định yêu cầu của chúng ta đối với process mới mà chúng ta muốn tạo ra.

	- Cấu trúc thú vị thứ hai là PROCESS_INFORMATION:

	- Hai trường quan trọng của nó là:

		. HANDLE hProcess – phần xử lý của process mới được tạo ra (không phải PID)

		. DWORD dwProcessId - PID của process.

	- Lưu ý:
		
		. Kiểu HANDLE là tương đương với void*;
		
		. Kiểu DWORD là tương đương với một four-byte long unsigned int

	- Mô tả chi tiết về structure có sẵn tại link sau:
		https://learn.microsoft.com/en-us/windows/win32/api/processthreadsapi/ns-processthreadsapi-process_information?redirectedfrom=MSDN

	- MS Windows API native types được mô tả trong link sau:
		https://learn.microsoft.com/en-us/windows/win32/winprog/windows-data-types?redirectedfrom=MSDN

	- Chúng tôi sẽ sử dụng cấu trúc này để lấy một số thông tin về process mới được tạo.


5.1.3.8
	- Một process mới được natively tạo ra bằng hàm CreateProcess() - hãy nhìn code:

		#include <windows.h>

		int CreateProcess (char *lpApplicationName,
				   char *lpCommandLine,
				   SECURITY_ATTRIBUTES * lpProcessAttributes,
				   SECURITY_ATTRIBUTES * lpThreadAttributes,
				   int bInheritHandles,
				   int dwCreationFlags,
				   void lpEnvironment,
				   char lpCurrentDirectory,
				   STARTUPINFO * lpStartupInfo,
				   PPROCESS_INFORMATION * lpProcessInformation);

	- Note: chúng tôi đã sử dụng lại the original function's header để làm cho nó rõ ràng hơn (nghĩa là chúng tôi đã thay thế các types nguyên thủy của MS Windows như BOOL bằng their direct equivalents).

	- Hàm returns:
		
		. khác 0 khi thành công;
		
		. 0 khi có lỗi (hàm GetLastError() trước đó có thể được sử dụng để tìm nguyên nhân gây ra lỗi).

	- Mô tả chi tiết về hàm có sẵn trong link sau:
		https://msdn.microsoft.com/library/windows/desktop/ms682425.aspx

	- Chúng tôi sẽ cung cấp một giải thích ngắn về các tham số của hàm.

	lpApplicationName

		char *lpApplicationName,

	- Đây là tên của chương trình cần khởi chạy. Hàm không sử dụng biến PATH để tìm file thực thi, vì vậy đối số này phải chỉ định vị trí của nó một cách rõ ràng. Nếu không có thư mục nào được chỉ định, thư mục hiện tại sẽ được assumed.

	- Đối số có thể là NULL - trong trường hợp này, tên của file thực thi phải được chỉ định trong tham số lpCommandLine, cùng với các đối số của chương trình (nếu có).

	lpCommandLine

		char *lpCommandLine,

	- Đây là một string chứa các đối số cho chương trình được khởi chạy, được định dạng giống như một dòng lệnh đơn giản được nhập trong một bảng điều khiển hệ thống. Nếu đối số trước đó là NULL, lpCommandLine phải chứa tên của chương trình làm đối số đầu tiên.

	- Đối số có thể là NULL nếu chương trình không yêu cầu bất kỳ đối số nào hoặc nếu các đối số không cần thiết.

	lpProcessAttributes và lpThreadAttributes

		SECURITY_ATTRIBUTES *lpProcessAttributes,
		SECURITY_ATTRIBUTES *lpThreadAttributes,

	- Những đối số này chỉ định security descriptor cho các đối tượng mới được tạo, process và thread chính của nó. The security descriptor kiểm soát quyền truy cập vào các đối tượng. Khi cả hai đối số đều được đặt là NULL, descriptor sẽ được sử dụng và, chúng tôi sẽ thường xuyên sử dụng tính năng này.


5.1.3.9
	bInheritHandles

		int bInheritHandles,
	
	- Nếu đối số là khác 0, process con sẽ kế thừa tất cả các handles của process cha (khái niệm "handles" ám chỉ tất cả các đối tượng được duy trì bởi hệ thống được tạo cho process, ví dụ: các file đã mở).

	- A zero value turns the inheritance off.

	dwCreationFlags

		int dwCreationFlags,
	
	- Đối số này đặt ưu tiên cho process con (MS Windows phân biệt giữa sáu loại lớp ưu tiên khác nhau).

	- Nếu đối số được đặt là 0, process con được tạo ra với NORMAL_PRIORITY_CLASS.

	lpEnvironment

		void *lpEnvironment,
	
	- Đây là con trỏ đến một environment variables block (khối biến môi trường), hoặc NULL nếu môi trường của cha sẽ được sử dụng instead.

	- Khối được chấp nhận bởi đối số được xây dựng theo cách khác so với biến thực thi của hàm main() với ba tham số. Nó là một null-terminated substrings chứa các null-terminated substring chứa biến. Điều này có nghĩa là một môi trường được định nghĩa bởi khai báo sau:

		char *env[] = { "VAR1=1", "VAR2=2", NULL };
	
	nên được lưu trữ as:

		"VAR1=1\0VAR2=2\0"
	
	lpCurrentDirectory

		char *lpCurrentDirectory,
	
	- Đây là một string chứa tên của thư mục mà nên được thiết lập làm thư mục làm việc của process con.

	- Nó được đặt là NULL nếu process con sử dụng thư mục làm việc của cha.

	lpStartupInfo

		STARTUPINFO *lpStartupInfo,
	
	- Đây là cấu hình khởi động cho process con.

	lpProcessInformation

		PROCESS_INFORMATION *lpProcessInformation
	
	- Đây là thông tin về process con vừa được tạo.


5.1.3.10
	- Nếu cha muốn đợi cho đến khi con hoàn thành execution của nó, nó có thể sử dụng hàm này - hãy nhìn code:

		#include <windows.h>

		int WaitForSingleObject (HANDLE hHandle, DWORD dwMilliseconds);

	- Hàm này được thiết kế để đợi nhiều OS objects khác nhau (do đó có tên là WaitFor...), và đợi các process chỉ là một trong nhiều khả năng của nó.

	- Các đối số chỉ định:
		
		. hHandle – cánh cửa của process mà hàm sẽ đợi;
		
		. dwMilliseconds – thời gian đợi tối đa (tính bằng mili giây), hoặc biểu tượng INFINITE nếu chúng ta quyết định đợi process con cho đến khi cần thiết.

	- Đối với các process, hàm có thể return:
		
		. WAIT_OBJECT_0 – process con đã hoàn thành;
		
		. WAIT_TIMEOUT – thời gian đợi tối đa đã vượt quá và process con vẫn đang chạy;
		
		. WAIT_FAILED – hàm đã thất bại (hàm GetLastError() sẽ cung cấp thông tin chi tiết hơn).

	- Mô tả chi tiết về hàm có sẵn trong link sau:
		https://learn.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-waitforsingleobject?redirectedfrom=MSDN


5.1.3.11
	- Dưới đây là một ví dụ minh họa tương tác giữa hai hàm - hãy nhìn code:

		#include <windows.h>
		#include <stdio.h>

		#define  CHILDREN  3

		int
		main (void)
		{
		  STARTUPINFO si;
		  PROCESS_INFORMATION pi[CHILDREN];
		  char argline[50];
		  memset (&si, 0, sizeof (si));
		  memset (&pi, 0, sizeof (pi));
		  si.cb = sizeof (si);

		  int i;
		  for (i = 0; i < CHILDREN; i++)
		    {
		      sprintf (argline, "05.03.prog.exe Process=%d arg1 arg2", i + 1);
		      if (CreateProcess
			  (NULL, argline, NULL, NULL, 0, 0, "Path=C:\\My\\Path\0\0", NULL,
			   &si, pi + i) == 0)
			{
			  printf ("CreateProcess #%d failed (%d).\n", i + 1, GetLastError ());
			  return 2;
			}
		      printf ("Process #%d created: handle=%p, identifier=%d\n", i + 1,
			      pi[i].hProcess, pi[i].dwProcessId);
		    }
		  for (i = CHILDREN - 1; i >= 0; i--)
		    {
		      WaitForSingleObject (pi[i].hProcess, INFINITE);
		      CloseHandle (pi[i].hProcess);
		      CloseHandle (pi[i].hThread);
		      printf ("Process #%d terminated.\n", i + 1);
		    }
		  return 0;
		}

	
		. line 4: Chúng tôi định nghĩa một biểu tượng mà chỉ đến số lượng các process con cần tạo;
	
		. line 10: Chúng tôi định nghĩa một mảng các cấu trúc PROCESS_INFORMATION (một cấu trúc cho mỗi process con)
	
		. line 12: Chúng tôi điền các cấu trúc si và pi với các giá trị 0;
	
		. line 19: Chúng tôi chuẩn bị một dòng lệnh để khởi chạy "đối tượng thử nghiệm" cũ (our old guinea pig) của chúng ta với các đối số xác định số thứ tự của process con;

		. line 20: Chúng tôi gọi hàm CreateProcess() với cấu hình sau:

			. Chúng tôi không sử dụng tên của application, vì vậy tên file thực thi nên được nhúng vào dòng lệnh;

			. Dòng lệnh chỉ định 05.03.prog.exe là chương trình cần khởi chạy;

			. Không sử dụng thuộc tính quy trình và luồng;

			. Chúng tôi không muốn kế thừa handles;

			. Chúng tôi đặt các creation flags là 0;

			. Chúng tôi định nghĩa một môi trường mới và đơn giản, chỉ với một biến;

			. Các process con sẽ kế thừa thư mục làm việc của cha;

			. Chúng tôi đặt một con trỏ đến thông tin khởi động trống;

			. Chúng tôi đặt một con trỏ đến i-th process information structure.

	
		. line 30: Chúng tôi đợi đến khi các process con hoàn thành, nhưng ngược lại so với thứ tự chúng được tạo;
	
		. line 33 to 34: Đây là một bước bắt buộc và phải được thực hiện để tránh rò rỉ bộ nhớ (hàm CloseHandle() giải phóng tất cả các tài nguyên liên quan đến handle).

	- Giả sử rằng các file thực thi 05.03.StartProcess.exe và 05.03.prog.exe được đặt trong cùng một thư mục (hiện tại), chương trình outputs như sau:

		Process #1 created: handle=00000084, identifier=3076
		Process #2 created: handle=00000088, identifier=5016
		argv[0] = '05.03.prog.exe'
		argv[1] = 'Process=1'
		argv[2] = 'arg1'
		Process #3 created: handle=000000A0, identifier=3776
		argv[3] = 'arg2'
		argv[0] = '05.03.prog.exe'
		argv[1] = 'Process=2'
		Path=C:\My\Path
		argv[2] = 'arg1'
		argv[0] = '05.03.prog.exe'
		argv[3] = 'arg2'
		argv[1] = 'Process=3'
		argv[2] = 'arg1'
		Path=C:\My\Path
		argv[3] = 'arg2'
		Path=C:\My\Path
		Process #3 terminated.
		Process #2 terminated.
		Process #1 terminated.


5.1.4.1 Processes and threads – why might we need threads?
	- Trong một thời gian dài sau khi các hệ điều hành thực sự được triển khai, một process là thực thể duy nhất được sử dụng để tổ chức thực thi chương trình. Các hệ thống khác nhau sử dụng các tên khác nhau cho cùng một phenomena (ví dụ như job hoặc task), nhưng ý nghĩa vẫn giữ nguyên - tất cả các hệ điều hành, bất kể nguồn gốc và lĩnh vực ứng dụng, luôn có các công cụ và dịch vụ được thiết kế để duy trì các process.

	- Tuy nhiên, sự tiến bộ công nghệ đã buộc phải có một thay đổi lớn đối với phương pháp này. Sự xuất hiện của các multicore processors (bộ xử lý đa lõi) giá rẻ đã mở ra các khả năng mới cho phần mềm đòi hỏi công suất tính toán lớn. Dường như, việc tăng hiệu suất phần mềm có thể được đạt được không chỉ bằng cách tăng tốc độ của một bộ xử lý đơn, mà còn bằng cách chia code thành các phần nhỏ hơn, cooperating hơn, có thể được thực hiện song song trên các lõi riêng biệt. Kỹ thuật này rất hứa hẹn, đặc biệt là trong thực tế ảo và đồ họa máy tính 3D, cũng như trong các mô phỏng khoa học phức tạp.

	- Process truyền thống turned out là công cụ không phù hợp cho phương pháp mới này - nó đơn giản là quá nặng. Việc tạo một process mới mất thời gian và tốn kém (nó sử dụng rất nhiều tài nguyên khan hiếm; bộ nhớ hoạt động đặc biệt được sử dụng rất lavishly, vì các process khác nhau phải chiếm dụng các đoạn dữ liệu riêng biệt).

	- Một entity mới cần được tạo ra, nhẹ hơn nhiều so với một process. Entity này cần:
		
		. Dễ dàng tạo ra, đồng bộ hóa và dừng lại;
		
		. Có khả năng chia sẻ bộ nhớ chung với các entity khác cùng loại;
		
		. Dễ triển khai và sử dụng.

	- Đó là lý do tại sao một thread (process nhẹ) xuất hiện.


5.1.4.2
	- Một typical, classical process thực thi code của mình bằng cách chạy qua một execution path duy nhất và tất cả các tài nguyên của nó (đoạn code, đoạn dữ liệu, file, register, stack, ...) không thể được sử dụng bởi bất kỳ process nào khác, ngay cả khi chúng đi qua cùng một execution path (ví dụ: khi hai process khác nhau đang thực thi code từ cùng một program file).

	- Khi có nhiều hơn một processor/core trong hệ thống, bạn có thể chạy đồng thời nhiều process, nhưng không có process nào có thể sử dụng nhiều hơn một lõi, ngay cả khi có lõi khả dụng trong hệ thống.

	- Một process như vậy được gọi là đơn luồng (single-threaded).


	** Xem ảnh


5.1.4.3
	- Các OS hiện đại có khả năng tạo và duy trì nhiều execution path bên trong mỗi process. Mỗi path được gọi là một thread (luồng). Các luồng khác nhau có thể thực thi cùng code, nhưng cũng có thể làm cho mỗi luồng thực thi các lệnh khác nhau. Tất cả các luồng chia sẻ các resources nặng như file cùng với các đoạn code và đoạn dữ liệu, nhưng tất cả chúng đều có các resources riêng, cô lập, ví dụ như register, một stack và các biến cục bộ. Hơn nữa, OS có thể liên kết một luồng với một lõi cụ thể có thể tăng hiệu suất tổng của process (kỹ thuật này thường được gọi là "CPU pinning", "processor affinity" hoặc đơn giản là "colligation").

	- So với một process, một luồng:
		
		. Nhanh hơn khi khởi động;
		
		. Dễ bảo trì hơn;
		
		. Tiết kiệm hơn về các resources của OS.


	** xem ảnh


5.1.4.4
	- Một luồng là công cụ hoàn hảo cho các problems có thể chia thành các phần độc lập. Mỗi phần có thể được xử lý bởi một luồng khác nhau và tất cả các luồng có thể làm việc song song. (Tất nhiên, thực thi song song thực sự chỉ có thể xảy ra khi và chỉ khi bạn có nhiều hơn một lõi CPU khả dụng. Việc tăng vô hạn số lượng luồng không phải là một thay thế cho sự thiếu nguồn công suất tính toán.)

	- Hãy xem snippet sau:

		:
		for(int i = 0; i < VECT_LEN; i++)
		    vector[i] = do_evaluation(i);
		:

	- Đây là một đoạn code đơn giản thực hiện một phép đánh giá lớn trên dữ liệu được thu thập trong một vector. Chúng ta không cần biết cách nó được thực hiện, chúng ta chỉ cần biết rằng mỗi lời gọi hàm do_evaluation() là một quá trình tốn thời gian rất lớn - vector càng dài, càng mất nhiều thời gian để đánh giá tất cả các phần tử của nó.

	- Hãy giả sử chúng ta có một two-core CPU - liệu chúng ta có thể tăng tốc code không? Yes, we can - chúng ta có thể sử dụng luồng để thực hiện điều đó.

	- Cách đơn giản, hiệu quả nhất là chia dữ liệu thành hai phần và giao 50% công việc cho mỗi luồng trong hai luồng riêng biệt.

	- Just like this:

		. Thread #1	
			:
			for(int i = 0; i < VECT_LEN/2; i++)
			    vector[i] = do_evaluation(i);
			:

		. Thread #2
			:
			for(int i = VECT_LEN/2; i < VECT_LEN; i++)
			    vector[i] = do_evaluation(i);
			:

	- Chúng ta giả định rằng VECT_LEN có thể chia đều cho hai.

	- Nếu chúng ta có thể thực thi cả hai luồng một cách song song, chúng ta sẽ có thể tăng gấp đôi tốc độ đánh giá.


5.1.4.5
	- Thực tế, các luồng được xây dựng từ các hàm - nó xảy ra như thể một hàm đơn được gọi đồng thời và tất cả các lời gọi diễn ra cùng một lúc.

	- Chúng ta cần viết hàm - có thể như code sau:

		void
		do_part (float *vec, int low, int high)
		{
		  for (int i = low; i < high; i++)
		    vec[i] = do_evaluation (i);
		}

	- Câu hỏi là: làm thế nào chúng ta có thể buộc nó hoạt động song song trong hai bản copy?

	- Câu hỏi chỉ có một câu trả lời thực sự đúng: it depends.

	- Tại sao?

	- Well, không có một phương pháp chung và phổ quát cho việc tạo luồng, ở cả source code level và binary level. Các OS khác nhau sử dụng các kỹ thuật khác nhau. Tất nhiên, các cơ chế mà chúng cung cấp là khá tương đồng, nhưng chi tiết có thể hoàn toàn khác nhau.

	- Chúng tôi muốn giới thiệu 3 tiêu chuẩn - theo ý kiến của chúng tôi là đại diện nhất - về việc làm việc với luồng:
		
		. Các hệ thống POSIX cung cấp các tiêu chuẩn có tên là POSIX Threads (aka Pthreads).
		
		. Các tiêu chuẩn được giới thiệu vào C programming language bởi tiêu chuẩn C11 (đến nay, chỉ có một tiêu chuẩn này thống nhất quản lý luồng ở source code level).
		
		. Các hệ thống MS Windows cung cấp các tiêu chuẩn riêng của mình.

	- Trước khi chúng tôi nói về bất kỳ giải pháp cụ thể nào, hãy hoàn thành example của chúng tôi. Chúng tôi giả định rằng có một instruction (chỉ thị) riêng trong programming language của chúng tôi có tên là "start". Chỉ thị này tạo một luồng mới từ một hàm cụ thể và khởi tạo việc thực thi của nó. Từ thời điểm đó, luồng starts to live its own life.


5.1.4.6
	- Chúng ta có thể sử dụng chỉ thị mới của chúng ta như sau:

		for(i = 0; i < 2; i++)
		    start do_part(vector,i * VECT_LEN/2,(i+1) * VECT_LEN/2);

	- Câu hỏi chúng ta cần đặt ra là: có an toàn không? Liệu có chắc chắn rằng các kết quả chúng ta nhận được sẽ chính xác như những gì được tạo ra bởi the single-threaded version of the code?
		Chà, nó phụ thuộc.

	- Yếu tố quan trọng nhất nằm bên trong hàm do_evaluation(). Và đây là thời điểm hoàn hảo để giới thiệu một thuật ngữ quan trọng mới.

	- Một hàm (or another isolated piece of code) được gọi là thread-safe khi nó hoạt động đúng đắn (tức là cung cấp kết quả chính xác và đi qua các execution path đúng) ngay cả khi nó được gọi đồng thời từ nhiều luồng khác nhau.

	- Thread-safe bao gồm các yêu cầu sau:

		. reentrancy (khả năng thực thi lại) - code được viết sao cho nó có thể được thực hiện một cách tương đối, ví dụ, được thực thi partially bởi một luồng, suspended, được thực thi bởi một luồng thứ hai, suspended again, được tiếp tục trong code đầu tiên, finished, được tiếp tục trong code thứ hai và finished again; nói cách khác, không có vụ một execution này ảnh hưởng đến những executions khác; yêu cầu này được đáp ứng khi code có thể lưu và khôi phục context của nó; nói chung, reentrancy code được cung cấp bởi compiler at binary level;

		. thread-local storage (bộ nhớ cục bộ của luồng) - mỗi luồng có bản sao riêng của dữ liệu mà không thể truy cập từ các luồng khác; yêu cầu như vậy hoàn toàn do chúng ta quyết định.

	- Hãy xem ví dụ sau:

		int i;

		void
		sqr (float *v, int l, int h)
		{
		  for (i = l; i < h; i++)
		    v[i] *= v[i];
		}

	- Hàm rõ ràng không thread-safe, vì các luồng khác nhau sẽ sử dụng cùng bản copy biến i, điều này sẽ làm hỏng execution của vòng lặp for.

	- Di chuyển int i declaration vào bên trong hàm sẽ fix the issue.


5.1.4.7
	- Một thuật ngữ quan trọng khác đề cập đến tình huống khi các luồng khác nhau sử dụng một shared resource.

	- Thuật ngữ này nghe có vẻ seriously: critical section

	- Critical section là một phần của một thread's code mà không được thực thi trong nhiều hơn một luồng cùng một lúc.

	- Bạn có thể hỏi bây giờ: điều này có trái với thread safety không?
		Yes and no.

	- Thread safety nói cho chúng ta biết cách viết một luồng để thực thi nó an toàn cùng với các luồng khác.

	- The critical section xuất hiện khi nhiều luồng sửa đổi trạng thái của cùng một shared resource mà không thể được nhân bản và dispersed giữa các luồng.

	- Ví dụ sẽ giúp bạn hiểu thêm, hãy xem code:

		float account_balance;

		void
		buy_something (float price)
		{
		  int ok = 0;
		  if (price >= account_balance)
		    {
		      ok = 1;
		      account_balance = account_balance - price;
		    }
		  if (ok)
		    printf ("accepted");
		  else
		    printf ("rejected");
		}

	- Hãy tưởng tượng rằng đây là một phần của một internet store và có trách nhiệm đảm bảo rằng khách hàng có đủ tiền để mua something. Does it look clear? Yes, it does

	- Có an toàn khi sử dụng nó không?
		Hell, no.

	- Hãy thử tưởng tượng điều gì xảy ra khi hàm buy_something() được gọi hai lần vào cùng một khoảnh khắc cho cùng một khách hàng, và tổng giá vượt quá số dư.

	- Đây là những gì có thể xảy ra:

		. threađ #1 so sánh giá và số dư và kết quả là tích cực;
		. threađ #2 làm điều tương tự và nó cũng thành công;
		. threađ #1 giảm số dư và mọi thứ dường như ổn;
		. threađ #2 giảm số dư và tài khoản trở nên nợ - thật không may!

	- Vấn đề này không thể giải quyết bằng cách phân chia biến account_balance và làm riêng cho cả hai luồng. Số dư phải tồn tại trong chỉ một bản copy - không có cách nào khác để làm điều này.

	- Có vẻ như phải có một phương thức để đảm bảo rằng phần của code bắt đầu bằng việc kiểm tra số dư và kết thúc bằng cách sửa đổi giá trị số dư được thực hiện chỉ trong một luồng.

	- Nói cách khác, phần của code được in đỏ là một critical section.

	- Có nhiều kỹ thuật để giải quyết vấn đề này. Phổ biến nhất dựa trên mutex.


5.1.4.8
	- Mutex là một data type trừu tượng, thường được quản lý exclusively bởi OS hoặc một specialized service layer.

	- Mutex có thể ở một trong hai trạng thái sau:

		. unlocked (aka released)
		. locked (aka granted)

	- Thay đổi trạng thái của một mutex được thực hiện thông qua các hàm chuyên biệt, một để locking và một để unlocking mutex.
		
		. Khi mutex được unlocked, bất kỳ luồng nào cũng có thể lock nó - it become looked ngay lập tức;
		
		. Khi một luồng khác cố gắng lock mutex đã được looked, luồng đó bị suspended - nó sẽ được tiếp tục khi mutex được unlocked again;
		
		. Luồng đã lock mutex, và cũng chỉ có luồng này, có thể unlock nó.


5.1.4.9
	- Hãy giả sử trong một hệ thống cụ thể:
		
		. Mutex được biểu diễn bằng một kiểu dữ liệu được đặt tên là MUTEX;
		
		. Các thao tác khóa và mở khóa được thực hiện thông qua các hàm có tên là LOCK() và UNLOCK() tương ứng.

	- Nhìn đoạn code sau - đây là cách một mutex giúp giải quyết vấn đề của chúng ta:

		float account_balance;
		MUTEX mutex;

		void
		buy_something (float price)
		{
		  int ok = 0;
		  LOCK (mutex);
		  if (price >= account_balance)
		    {
		      ok = 1;
		      account_ballance = account_ballance - price;
		    }
		  UNLOCK (mutex);
		  if (ok)
		    printf ("accepted");
		  else
		    printf ("rejected");
		}

	- Dưới đây là điều đang xảy ra:
	
		. thread #1 khóa the critical section, sau đó so sánh price và balance và kết quả là dương;
	
		. thread #2 cố gắng khóa cùng một section - kết quả là thread #2 bị suspended;
	
		. thread #1 giảm balance và mọi thứ đều ổn;
	
		. thread #1 mở khóa mutex;
	
		. thread #2 được tiếp tục, nó khóa mutex và kiểm tra balance - nó thất bại - transaction bị từ chối;
	
		. thread #2 mở khóa mutex.

	- Vậy là đã oki.


5.1.4.10
	- Bây giờ chúng tôi sẽ giới thiệu cho bạn hai ví dụ đơn giản được triển khai một cách tương tự trong ba môi trường khác nhau.

		. Ví dụ 1:
		   - Chương trình đầu tiên tạo ba luồng.
		   - Mỗi luồng báo cáo its creation, rút một số từ phạm vi (1..5), ngủ trong số giây đã rút được, báo cáo its completion và exit.
		   - Hàm main() chờ tất cả các luồng hoàn thành.

		. Ví dụ 2:
		   - Chương trình thứ hai tạo 50 luồng.
		   - Mỗi luồng chịu trách nhiệm kiểm tra một phần tử trong vector.
		   - Nếu phần tử là số lẻ, nó được đếm và cộng lại.

	- Chúng tôi sẽ cho bạn thấy cách sử dụng mutex để tạo critical section.

	- Ready, steady, go!


5.1.5.1 Processes and threads – POSIX threads
	- Luồng POSIX (Pthreads) are available ở mọi nơi mà môi trường tuân thủ POSIX tồn tại. Điều này bao gồm các hệ điều hành UNIX® và các hệ thống tương thích Unix/Linux nói chung, mặc dù cũng có một phiên bản không chính thức của Pthreads cho MS Windows.

	- Nếu bạn muốn biên dịch và chạy các ví dụ của chúng tôi trong Unix/Linux bằng các trình biên dịch gcc hoặc clang, đừng quên sử dụng tùy chọn dòng lệnh pthread - việc biên dịch sẽ không thành công nếu thiếu nó.

	- Tất cả các entity cần thiết để sử dụng Pthreads trong source code của bạn được khai báo trong header file sau:

		#include <pthread.h>		(chatGPT thêm phần trong <>)
	
	- Một luồng đơn được biểu diễn bằng giá trị của kiểu pthread_t:

		pthread_t
	
	- Implementation của kiểu này được giữ bí mật, nhưng có thể được coi là tương đương với kiểu long int.

	- Một hàm chứa thread's code nên được khai báo như sau:

		void *thread(void *data);
	

		. Tên của hàm chọn tùy ý.

		. Hàm return một con trỏ kiểu void* (có thể được sử dụng để trả về bất kỳ giá trị nào được đánh giá bởi luồng, hoặc nó có thể được bỏ qua).

		. Hàm mong đợi một đối số kiểu void* (có thể được sử dụng để truyền bất kỳ giá trị nào vào luồng, hoặc nó có thể được bỏ qua).

	- Một luồng mới được tạo ra bằng hàm pthread_create() - xem snippet sau:

		int pthread_create (pthread_t * thread,
				    pthread_attr_t * attr,
				    void *(*start_routine) (void *), void *arg);

		
		. Một con trỏ đến một biến kiểu pthread_t - hàm điền giá trị của biến này với thread identity mới nếu thành công.
		
		. Một con trỏ đến dữ liệu kiểu pthread_attr_t - dữ liệu chỉ định các thuộc tính của luồng hoặc có thể là NULL để tạo một bộ thuộc tính luồng tiêu chuẩn.
		
		. Một con trỏ đến hàm, thứ mà sẽ là thread's code (aka thread text).
		
		. Một con trỏ kiểu void* có thể được sử dụng để truyền dữ liệu tùy ý vào luồng.
		
	- Hàm return:

		. 0 trong trường hợp thành công.
		. error code trong các trường hợp khác.

	- Thread mới được tạo và lauched ngay lập tức.


5.1.5.2
	- Nếu bạn muốn đợi cho đến khi một luồng hoàn thành, bạn có thể gọi hàm pthread_join() - nhìn nó như sau:

		int pthread_join (pthread_t thread, void **retval);

	- Hàm sử dụng các tham số sau:

		. Một giá trị kiểu pthread_t - identity của luồng bạn sẽ đợi.

		. Một con trỏ đến một con trỏ void* - nếu nó không phải NULL, hàm sẽ thêm giá trị return từ thread text.

	- Hàm return:

		. 0 trong trường hợp thành công.
		. error code trong các trường hợp khác.

	- Invoker sẽ bị suspended cho đến khi luồng hoàn thành.

	- Nếu bạn cần biết identity của luồng từ bên trong chính cái luồng đó, bạn có thể sử dụng hàm pthread_self():

		pthread_t pthread_self(void);
	
	- Hàm return giá trị giống như giá trị được đặt bởi hàm pthread_create() vào đối số đầu tiên của nó.


5.1.5.2
	- Dưới đây là ví dụ đầu tiên - hãy xem code:

		#include <stdio.h>
		#include <stdlib.h>
		#include <pthread.h>
		#include <unistd.h>

		#define THREADS 3

		void *
		thread (void *data)
		{
		  char *msg = (char *) data;
		  pthread_t self = pthread_self ();
		  srand (self);
		  printf ("Thread %lxd started: \'%s\'\n", self, msg);
		  long delay = rand () % 5 + 1;
		  sleep (delay);
		  printf ("Thread %lxd finished\n", self);
		  return (void *) delay;
		}

		int
		main (void)
		{
		  pthread_t threads[THREADS];
		  char data[THREADS][20];

		  printf ("main() started...\n");
		  for (int i = 0; i < THREADS; i++)
		    {
		      sprintf (data[i], "Thread #%d!", i + 1);
		      pthread_create (threads + i, NULL, thread, data[i]);
		    }
		  for (int i = 0; i < THREADS; i++)
		    {
		      long retval;
		      pthread_join (threads[i], (void *) &retval);
		      printf ("Thread %d joined: %ld\n", i + 1, retval);
		    }
		  return 0;
		}
		

		. line 8: Đây là thread text của chúng ta - một hàm có tên là thread (điều này thực sự chỉ là một sự trùng hợp)
		
		. line 11: Hàm nhận một string làm đối số - chúng ta phải typecast con trỏ để có được actual string
		
		. line 12: Luồng nhận identity của mình;
		
		. line 13: Chúng ta sử dụng nó as a new random generator seed;
		
		. line 14: Luồng introduces itself;
		
		. line 16: Luồng vào chế độ ngủ;
		
		. line 17: Luồng return the delay time as its result (lưu ý phép ép kiểu)
		
		. line 24: Chúng ta khai báo một mảng để lưu tất cả identity của luồng;
		
		. line 30: Chúng ta chuẩn bị một đối số cho luồng;
		
		. line 31: Chúng ta tạo ra một luồng mới và launch nó (ba lần)
		
		. line 36: Chúng ta đợi cho đến khi tất cả các luồng hoàn thành và in ra kết quả của chúng (the delay time)
	
	- Output có thể như sau:

		main() started...


		Thread 7f2d63861700d started: 'Thread #1!'


		Thread 7f2d6285f700d started: 'Thread #3!'


		Thread 7f2d63060700d started: 'Thread #2!'


		Thread 7f2d63861700d finished


		Thread 1 joined: 1


		Thread 7f2d6285f700d finished


		Thread 7f2d63060700d finished


		Thread 2 joined: 4


		Thread 3 joined: 5


5.1.5.4
	- A single mutex được biểu diễn bằng một biến kiểu pthread_mutex_t:

		pthread_mutex_t
	
	- The type is black-boxed.

	- Nếu bạn muốn sử dụng một mutex trong code của bạn, bạn phải khởi tạo nó: bạn có thể sử dụng một hàm chuyên biệt có tên là pthread_mutes_init() cho mục đích này, hoặc bạn có thể chỉ cần gán một symbolic value of PTHREAD_MUTEX_INITIALIZER cho nó trước khi sử dụng lần đầu tiên.

	- Chúng tôi ưa thích cách thứ hai.

	- Để thực hiện lock trên một mutex, bạn sử dụng hàm pthread_mutex_lock():

		int 
		pthread_mutex_lock(pthread_mutex_t *mutex);
	
	- Đối số duy nhất trong hàm là một con trỏ đến một biến đại diện cho một mutex được khởi tạo đúng cách.

	- Hàm return:

		. 0 nếu thành công;
		. error code trong trường hợp khác.

	- Để thực hiện unlocked trên một mutex, bạn sử dụng hàm pthread_mutex_unlock():

		int 
		pthread_mutex_unlock(pthread_mutex_t *mutex);
	
	- Các đối số và kết quả are the same as hàm trước đó.


5.1.5.5
	- Đây là ví dụ thứ hai:

		#include <stdio.h>
		#include <stdlib.h>
		#include <pthread.h>
		#include <unistd.h>

		#define THREADS 50

		pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

		int sum = 0;
		int cnt = 0;

		void *
		thread (void *data)
		{
		  int *p = (int *) data;
		  sleep (2);
		  if (*p % 2)
		    {
		      //      pthread_mutex_lock(&mutex);
		      int s, c;
		      s = sum;
		      c = cnt;
		      c = c + 1;
		      s = s + *p;
		      sum = s;
		      cnt = c;
		      //      pthread_mutex_unlock(&mutex);
		    }
		  return NULL;
		}

		int
		main (void)
		{
		  pthread_t threads[THREADS];
		  int data[THREADS];

		  for (int i = 0; i < THREADS; i++)
		    data[i] = i + 1;
		  for (int i = 0; i < THREADS; i++)
		    pthread_create (threads + i, NULL, thread, data + i);
		  for (int i = 0; i < THREADS; i++)
		    pthread_join (threads[i], NULL);
		  printf ("Results: cnt=%d, sum=%d\n", cnt, sum);
		  return 0;
		}

	
		. line 8: Chúng ta khai báo một mutex để tạo ra một critical section trong luồng của chúng ta;
	
		. line 10: Hai biến này trong shared resource sẽ đóng vai trò: biến đầu tiên tính tổng các giá trị lẻ, biến thứ hai để đếm chúng;
	
		. line 13: Luồng của chúng ta nhận một con trỏ đến một giá trị để kiểm tra (nó phải được typecast để nhận một giá trị int);
	
		. line 17: Chúng ta ngủ trong hai giây để tối đa hóa khả năng các luồng sẽ chạy đồng thời; không may, the thread text quá ngắn có thể làm cho luồng được tạo trước đó có thể complete trước khi luồng tiếp theo được launched; trick này compensates for cho hiệu ứng đó;
	
		. line 18: Nếu giá trị là số lẻ, chúng ta bắt đầu critical section của chúng ta; note the weird way of modifying our shared resources - chúng ta muốn làm cho section này dài hơn và thêm nhiều hơn machine instructions để cho OS thực hiện;
	
		. line 28: the critical section kết thúc ở đây;
	
		. line 30: Chúng ta không cần any return value nào nên chúng ta return NULL;
	
		. line 36: Chúng ta khai báo một mảng cho các identity của các luồng;
	
		. line 37: Chúng ta khai báo một mảng cho các giá trị đang được tìm kiếm, được đếm và được tính tổng;
	
		. line 45: Chúng ta output kết quả.

	- Output có thể như sau:

		Results: cnt=25, sum=625

	- Nếu bạn comment out (nhận xét) các line 20 và 28, bạn cũng có thể expect một số kết quả kỳ lạ, ví dụ:

		Results: cnt=24, sum=624


5.1.6.1 Processes and threads – C11 threads
	- C11 standard giới thiệu một new, portable standard để triển khai luồng. Thật không may, phần này của tiêu chuẩn vẫn chưa được wide implemented yet - cả gcc và clang đều không tuân theo nó. Chúng tôi hy vọng điều này sẽ thay đổi sớm.

	- Các ví dụ của chúng tôi đã được compiled và tested trong môi trường Pelles C - link về Pelles C như sau:
		http://www.smorgasbordet.com/pellesc/

	- Một chương trình sử dụng luồng C11 phải include header sau:

		#include <threads>			(chatGPT tự thêm vào trong <>)

	- Một C11 thread được biểu diễn bằng một giá trị kiểu thrd_t:

		thrd_t

	- The type is black-boxed (it may be a structure actually).

	- A thread's text được đặt trong một hàm với prototype sau:

		int thread(void *data);


		. Hàm return một giá trị int (có thể được sử dụng để trả về một giá trị được đánh giá bởi luồng, hoặc nó có thể bị bỏ qua). 

		. Hàm mong đợi một đối số kiểu void* (giống như trong Pthreads).

	- This function is typed as thrd_start_t in C11.

	- Hàm thrd_create() creates and launches một luồng mới:

		int thrd_create(
		    thrd_t *thr,
		    thrd_start_t func,
		    void *arg
		);

	- Hàm sử dụng các tham số sau:
		
		. Một con trỏ đến biến kiểu thrd_t* - hàm điền giá trị của biến này bằng identity của luồng mới nếu thành công;
		
		. Một con trỏ đến một hàm chứa thread text;
		
		. Một con trỏ đến dữ liệu tùy ý.
	
	- Hàm return:

		. thrd_success nếu thành công;
		. an error code trong trường hợp ngược lại (một trong các symbols sau: thrd_timedout, thrd_busy, thrd_nomem, thrd_error).

	- Joining to (waiting for) a thread được thực hiện bằng hàm thrd_join():

		int thrd_join(
		    thrd_t thr,
		    int *res
		);

	- Hàm sử dụng các tham số sau:

		. the identity của luồng để gắn kết;

		. một con trỏ đến một con trỏ int - nếu nó không phải NULL, hàm sẽ add giá trị được returned từ thread text.

	- Hàm trả về các giá trị giống như hàm thrd_create().

	- The current thread's identity được returned bằng hàm thrd_current():

		thrd_t thrd_current();

	- Hàm return cùng giá trị như giá trị mà hàm thrd_create() đặt vào đối số đầu tiên của nó.


5.1.6.2
	- Dưới đây là ví dụ đầu tiên:

		#include <stdio.h>
		#include <stdlib.h>
		#include <threads.h>

		#define THREADS 3

		int
		thread (void *data)
		{
		  char *msg = (char *) data;
		  thrd_t self = thrd_current ();
		  unsigned long fakeid = *((unsigned long *) &self);
		  srand (fakeid);
		  struct timespec delay = { rand () % 5 + 1, 0 };
		  printf ("Thread %lx started: \'%s\'\n", fakeid, msg);
		  thrd_sleep (&delay, NULL);
		  printf ("Thread %lx finished\n", fakeid);
		  return delay.tv_sec;
		}

		int
		main (void)
		{
		  thrd_t threads[THREADS];
		  char data[THREADS][20];

		  printf ("main() started...\n");
		  for (int i = 0; i < THREADS; i++)
		    {
		      sprintf (data[i], "Thread #%d!", i + 1);
		      thrd_create (threads + i, thread, data[i]);
		    }
		  for (int i = 0; i < THREADS; i++)
		    {
		      int retval;
		      thrd_join (threads[i], &retval);
		      printf ("Thread %d joined: %ld\n", i + 1, retval);
		    }
		  return 0;
		}

	- Chúng tôi sẽ chỉ giải thích những phần khác biệt so với ví dụ Pthreads:
		
		. line 12: Vì thrd_t is black-boxed, chúng ta cần thực hiện a not very clean trick để lấy unique long int value từ nó; chúng ta lấy con trỏ đến nó, typecast nó thành long int* và lấy giá trị từ nó;
		
		. line 16: Các C11 threads cung cấp một hàm chuyên biệt để thực hiện a delay - hàm được đặt tên là thrd_sleep() và expect hai con trỏ đến cấu trúc kiểu struct timespec; một cấu trúc như vậy bao gồm hai trường:
			
			. one for a time measured in whole seconds;
			. one for a time measured in nanoseconds.

	- The actual delay time được lấy là tổng của cả hai giá trị đó (xem line 14 để xem structure đang hoạt động); đối số thứ hai được sử dụng để return thời gian còn lại để chờ till after the function is broken by an interrupt; bạn có thể sử dụng NULL để ngăn chặn hành vi này.

	- Kết quả có thể nhìn như sau:

		main() started...
		Thread a00144 started: 'Thread #1!'
		Thread a0028c started: 'Thread #2!'
		Thread a003d4 started: 'Thread #3!'
		Thread a0028c finished
		Thread a003d4 finished
		Thread a00144 finished
		Thread 1 joined: 5
		Thread 2 joined: 2
		Thread 3 joined: 2


5.1.6.3
	- C11 biểu diễn một single mutex dưới dạng một biến kiểu mtx_t.

	- Mutex phải được khởi tạo trước khi sử dụng lần đầu tiên - điều này được thực hiện bởi hàm mtx_init() - nhìn snippet sau:

		int mtx_init (mtx_t * mutex, int type);
		int mtx_destroy (mtx_t * mutex);

		
		. Đối số đầu tiên là một con trỏ đến mutex đã được khởi tạo;
		
		. Đối số thứ hai chỉ ra loại mutex: mtx_plain symbol cấu hình một mutex tổng quát - cái mà chúng ta cần.

	- Để tránh any memory leak, mutex đã được khởi tạo nên bị destroyed sau khi sử dụng bằng hàm mtx_destroy() - đối số duy nhất của nó đại diện cho mutex cần bị hủy.

	- Các return values giống như đã mô tả trước đó.

	- Hàm mtx_lock() khóa mutex:

		int mtx_lock(mtx_t* mutex);
	
	- Đối số duy nhất trong hàm là một con trỏ đến biến đại diện cho mutex được khởi tạo đúng cách.

	- The return values giống như đã mô tả trước đó.

	- Để thực hiện việc mở khóa mutex, bạn sử dụng hàm mtx_unlock():

		int mtx_unlock(mtx_t* mutex);
	
	- Các đối số và kết quả giống như cho hàm trước đó.


5.1.6.4
	- Đây là example thứ hai:

		#include <stdio.h>
		#include <stdlib.h>
		#include <threads.h>

		#define THREADS 50

		mtx_t mutex;
		int sum = 0;
		int cnt = 0;

		int
		thread (void *data)
		{
		  int *p = (int *) data;
		  struct timespec delay = { 2, 0 };
		  thrd_sleep (&delay, NULL);
		  if (*p % 2)
		    {
		      mtx_lock (&mutex);
		      int s, c;
		      s = sum;
		      c = cnt;
		      c = c + 1;
		      s = s + *p;
		      sum = s;
		      cnt = c;
		      mtx_unlock (&mutex);
		    }
		  return 0;
		}

		int
		main (void)
		{
		  thrd_t threads[THREADS];
		  int data[THREADS];

		  mtx_init (&mutex, mtx_plain);
		  for (int i = 0; i < THREADS; i++)
		    data[i] = i + 1;
		  for (int i = 0; i < THREADS; i++)
		    thrd_create (threads + i, thread, data + i);
		  for (int i = 0; i < THREADS; i++)
		    thrd_join (threads[i], NULL);
		  printf ("Results: cnt=%d, sum=%d\n", cnt, sum);
		  mtx_destroy (&mutex);
		  return 0;
		}

	- Không cần bình luận gì thêm đâu nhỉ


5.1.7.1 Processes and threads – MS Windows thread
	- Vì luồng MS Windows được kết nối chặt chẽ với OS kernel (Pthreads và C11 threads được triển khai ở level cao hơn), chúng không cần bất kỳ thư viện đặc biệt nào, và tất cả các entity cần thiết có thể được tìm thấy trong header <windows.h>, hoặc trong bất kỳ header nào được implicitly included với nó:

		#include <windows.h>
	
	- Một MS Windows thread là một relative của tất cả các system objects khác, nên nó được biểu diễn bởi một kiểu dữ liệu thông dụng có tên là HANDLE.

	- Bạn có thể xem nó như một untyped pointer (void *).

	- A thread's text được đặt trong một hàm với prototype sau:

		DWORD WINAPI thread(LPVOID data);
	
	- Hàm này thường được gọi là luồng công việc (worker thread):
		
		. Hàm return một unsigned long int được sử dụng để báo hiệu trạng thái hoàn thành (nó có thể không được sử dụng để return một kết quả như Pthreads hoặc luồng C11).
		
		. Hàm expect một đối số kiểu void* (sử dụng nó cho mục đích giống như trong Pthreads và luồng C11).

	- Hàm này thuộc type named LPTHREAD_START_ROUTINE.

	- WINAPI specifier đánh dấu hàm này as using the standard MS Windows calling convention.

	- Hàm CreateThread() creates và launches một luồng mới:

		HANDLE WINAPI CreateThread(
		    LPSECURITY_ATTRIBUTES   lpThreadAttributes,
		    SIZE_T  dwStackSize,
		    LPTHREAD_START_ROUTINElpStartAddress,
		    LPVOIDlpParameter,
		    DWORD   dwCreationFlags,
		    LPDWORD lpThreadId
		);
	
		
		. Một con trỏ đến một set of desired thread attributes, hoặc NULL để sử dụng các standard attributes.
		
		. Kích thước của stack cho luồng, hoặc 0 để sử dụng default flag (kích thước ngăn xếp mặc định).
		
		. Một con trỏ đến worker thread function.
		
		. Một con trỏ đến dữ liệu tùy ý.
		
		. Một bit mask với các thread's creation flags, hoặc 0 để sử dụng default flag.
		
		. Một con trỏ đến một biến nơi ID của luồng mới được đặt (note: ID của luồng không giống với handle của luồng).
	
	- Hàm return:

		. Một handle của luồng đã được tạo nếu thành công.
		. Một con trỏ NULL trong trường hợp ngược lại.

	- Để tránh rò rỉ bộ nhớ, handle của luồng nên được giải phóng sau khi sử dụng bằng hàm CloseHandle() - đối số duy nhất của nó đại diện cho handle cần close (release).


5.1.7.2
	- Waiting for a thread được thực hiện bằng hàm WaitForSingleObject(), thứ mà bạn đã biết rồi.

	- Nếu bạn muốn chờ nhiều hơn một luồng, bạn có thể sử dụng hàm WaitForMultipleObjects():

		DWORD WINAPI WaitForMultipleObjects(
		    DWORD   nCount,
		    HANDLE  *lpHandles,
		    BOOL    bWaitAll,
		    DWORD   dwMilliseconds
		);
	
	- Hàm sử dụng các tham số sau:
	
		. Số lượng luồng để chờ;
	
		. Một con trỏ đến một vector chứa các handle của các luồng;
	
		. TRUE (khác 0) nếu bạn muốn chờ đợi tất cả các handle, hoặc FALSE (0) nếu bạn muốn chờ đợi bất kỳ thằng nào trong số các handle được liệt kê;
	
		. Thời gian tối đa bạn đồng ý chờ đợi, hoặc INFINITE để chờ hiệu quả mong muốn một cách vô thời hạn.

	- Hàm return (chỉ liệt kê các kết quả có liên quan):

		. WAIT_OBJECT_0 khi tất cả các handle's signalled threads đã kết thúc;
		. WAIT_FAILED trong trường hợp có lỗi.

	- Identity của luồng hiện tại được returned bởi hàm GetCurrentThreadId():

		DWORD WINAPI GetCurrentThreadId(void);
	
	- Hàm return giá trị giống như giá trị mà hàm CreateThread() đặt vào đối số cuối cùng của nó.


5.1.7.3
	- Dưới đây là ví dụ đầu tiên - hãy nhìn code:

		#include <stdio.h>
		#include <stdlib.h>
		#include <windows.h>

		#define THREADS 3

		typedef struct
		{
		  char msg[20];
		  int retval;
		} DATA;

		DWORD WINAPI
		thread (LPVOID data)
		{
		  DATA *dat = (DATA *) data;
		  DWORD self = GetCurrentThreadId ();
		  printf ("Thread %xd started: \'%s\'\n", self, dat->msg);
		  srand (self);
		  DWORD delay = rand () % 5 + 1;
		  Sleep (delay * 1000);
		  printf ("Thread %xd finished\n", self);
		  dat->retval = delay;
		  return 0;
		}

		int
		main (void)
		{
		  HANDLE threads[THREADS];
		  DWORD thrdids[THREADS];
		  DATA data[THREADS];

		  printf ("main() started...\n");
		  for (int i = 0; i < THREADS; i++)
		    {
		      sprintf (data[i].msg, "Thread #%d!", i + 1);
		      threads[i] = CreateThread (NULL, 0, thread, data + i, 0, thrdids + i);
		    }

		  for (int i = 0; i < THREADS; i++)
		    {
		      WaitForSingleObject (threads[i], INFINITE);
		      printf ("Thread %d completed: %ld\n", i + 1, data[i].retval);
		    }
		  return 0;
		}

	
		. line 7: Chúng tôi sử dụng cùng một vector để truyền đối số vào luồng và đọc kết quả của luồng - do đó vector bao gồm các cấu trúc;
	
		. line 21: Chúng tôi sử dụng đương đương của hàm POSIX sleep() trong Windows API - được gọi là Sleep() - và có một đối số chỉ định thời gian trễ theo mili giây.

	- Output có thể như sau:

		main() started...
		Thread 1394d started: 'Thread #1!'
		Thread 1c8d started: 'Thread #2!'
		Thread 14dcd started: 'Thread #3!'
		Thread 1394d finished
		Thread 1 completed: 1
		Thread 14dcd finished
		Thread 1c8d finished
		Thread 2 completed: 3
		Thread 3 completed: 2


5.1.7.4
	- Trong MS Windows, một mutex đơn lẻ được biểu diễn bằng handle của nó.

	- Mutex phải được tạo ra bằng hàm có tên là CreateMutex():

		HANDLE WINAPI CreateMutex(
		    LPSECURITY_ATTRIBUTES   lpMutexAttributes,
		    BOOL    bInitialOwner,
		    LPCTSTR lpName
		);
	
		
		. Đối số đầu tiên chỉ ra các security attributes cho mutex mới (NULL có nghĩa là các thuộc tính mặc định sẽ được sử dụng).
		
		. Nếu là TRUE, mutex mới lúc đầu đã bị khóa bởi người tạo; FALSE tạo ra một unlocked mutex giống như trong Pthreads hoặc C11; note: MS Windows sử dụng các thuật ngữ như "obtain a mutex" hoặc "own a mutex" thay vì "lock a mutex"; tương tự, việc mở khóa mutex được gọi là "release mutex".
		
		. Đối số cuối cùng là tên của mutex mới được tạo ra, hoặc NULL cho một unnamed mutex.

	- Kết quả là:

		. Handle của mutex khi thành công;
		. NULL trong trường hợp ngược lại.

	- Để tránh rò rỉ bộ nhớ, handle của mutex nên được giải phóng bằng CloseHandle().

	- The lock operation (Hoạt động khóa) (tức là lấy mutex) được thực hiện bằng cách sử dụng our old friend:

		WaitForSingleObject(mutex, INFINITE);
	
	- Hãy nhìn vào section 5.6.8 để nhớ lại các kết quả có thể của hàm.

	- Hàm ReleaseMutex() thực hiện unlock operation:

		BOOL WINAPI ReleaseMutex(HANDLE hMutex);
	
	- Đối số duy nhất trong hàm chỉ định mutex để unlock (release):
	
		. khác 0 (TRUE) khi thành công;
		. bằng 0 (FALSE) trong trường hợp ngược lại.


5.1.7.5
	- Đây là example thứ hai:

		#include <stdio.h>
		#include <stdlib.h>
		#include <windows.h>

		#define THREADS 50

		HANDLE mutex;
		int sum = 0;
		int cnt = 0;

		DWORD WINAPI
		thread (LPVOID * data)
		{
		  int *p = (int *) data;
		  Sleep (2000);
		  if (*p % 2)
		    {
		      WaitForSingleObject (mutex, INFINITE);
		      int s, c;
		      s = sum;
		      c = cnt;
		      c = c + 1;
		      s = s + *p;
		      sum = s;
		      cnt = c;
		      ReleaseMutex (mutex);
		    }
		  return 0;
		}

		int
		main (void)
		{
		  HANDLE threads[THREADS];
		  DWORD thrdids[THREADS];
		  int data[THREADS];

		  mutex = CreateMutex (NULL, FALSE, NULL);
		  for (int i = 0; i < THREADS; i++)
		    data[i] = i + 1;
		  for (int i = 0; i < THREADS; i++)
		    {
		      threads[i] = CreateThread (NULL, 0, thread, data + i, 0, thrdids + i);
		      if (threads[i] == NULL)
			{
			  printf ("ERROR %d\n", i);
			  exit (0);
			}
		    }
		  WaitForMultipleObjects (THREADS, threads, TRUE, INFINITE);
		  for (int i = 0; i < THREADS; i++)
		    CloseHandle (threads[i]);
		  printf ("Results: cnt=%d, sum=%d\n", cnt, sum);
		  CloseHandle (mutex);
		  return 0;
		}

	- Chắc chắn là không cần giải thích thêm cái gì đâu nhỉ.



~ Module 6 ~
	...