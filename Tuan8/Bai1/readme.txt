		C Essentials - Part 3 (Advanced)


~ Module 6 ~
	
	In this module, you will learn about:

		IEEE-754: a different universe;
		NaN, infinity, zero;
		floats and doubles – should we trust them?;
		numerical anomalies vs precision;
		ULP;
		what is pragma?;
		FENV_ACCESS pragma;
		floating-point exceptions;
		rounding;
		multi-precision libraries (GMP, MPFR, MPIR).


6.1.1.2 Floats vs. ints – what are floats worth anyway?
		
		float x;

	- Floating point data types (Các loại dữ liệu dấu chấm động) là một trong những phương tiện được sử dụng trong gần như tất cả các chương trình phức tạp. Việc đánh giá khoa học đơn giản là không thể thiếu chúng. Mỗi khi bạn phải xử lý dữ liệu đại diện cho các giá trị vật lý (tốc độ, trọng lượng, nhiệt độ, v.v.), bạn sẽ sử dụng các biến dấu chấm động. Đôi khi bạn chọn kiểu float, đôi khi là double - điều này không quan trọng. Khái niệm mà các giá trị này dựa trên luôn luôn giống nhau, và các thuật toán được sử dụng để đánh giá dữ liệu cũng giống nhau.

	- Floats là những công cụ mạnh mẽ. Nhưng giống như bất kỳ công cụ nào khác, floats cũng có một số nhược điểm. Chúng tôi sẽ chỉ cho bạn.

	- Note: các vấn đề và anomaly mà chúng tôi muốn thảo luận không chỉ liên quan đến C programming language. Mỗi ngôn ngữ lập trình sử dụng xử lý dữ liệu dấu chấm động (nói cách khác, mỗi ngôn ngữ lập trình) đều gặp phải những vấn đề tương tự.

	- Và những người lập trình cũng trải qua chúng.

	- Hãy conduct một số thí nghiệm đơn giản bây giờ. Stay focus!

	- Đoạn code này nên làm bạn cười:

		#include <stdio.h>

		int main(void) {
			int x = 1;

			while(x != x + 1) 
				x *= 2;
			printf("%d\n", x);		
			return 0;
		}

	- Yes, nó rõ ràng không chính xác. Không có cách nào điều kiện được biểu diễn dưới dạng x != x + 1 có thể sai.

	- Yes - chạy code sẽ không làm gì ngoại trừ lãng phí nguồn CPU - code sẽ không output bất cứ điều gì đến stdout. Vòng lặp sẽ go round indefinitely.


6.1.1.3
	- Xem code:

		#include <stdio.h>

		int
		main (void)
		{
		  double x = 1.;

		  while (x != x + 1.)
		    x *= 2.;
		  printf ("%f\n", x);
		  return 0;
		}

	- Chúng tôi thay đổi nó một chút - thay tất cả ints (một biến và the literals) thành floats.

	- Run code và nó ra như này:

		16777216.000000

	- Nhưng mà đừng tin chúng tôi, hãy tự thử.


6.1.1.4
	- "Blame the floats! Độ chính xác của chúng thấp, vì vậy hãy thay thế chúng bằng double."

	- Xem code:

		#include <stdio.h>

		int
		main (void)
		{
		  double x = 1.;

		  while (x != x + 1.f)
		    x *= 2.f;
		  printf ("%f\n", x);
		  return 0;
		}

	- Chương trình đã được sửa lại in ra:

		9007199254740992.000000

	- Có vẻ tốt hơn không? Hoàn toàn không. Nó trông thậm chí còn tồi tệ hơn.


6.1.1.5
	- Hãy tiếp tục thí nghiệm.

	- Nhìn code:

		#include <stdio.h>

		int
		main (void)
		{
		  float arr[] = { 70000000000.,
		    7000000000.,
		    700000000.,
		    7000000.,
		    700000.,
		    70000.,
		    7000.,
		    700.,
		    70.,
		    7.,
		    .7,
		    .07,
		    .007,
		    .0007,
		    .00007,
		    .000007,
		    .0000007,
		    .00000007,
		    .000000007,
		    .0000000007
		  };
		  float sum1 = 0.f, sum2 = 0.f;
		  int i, n = sizeof (arr) / sizeof (arr[0]);
		  for (i = 0; i < n; i++)
		    sum1 += arr[i];
		  for (i = n - 1; i >= 0; i--)
		    sum2 += arr[i];
		  printf ("sum1=%f\n", sum1);
		  printf ("sum2=%f\n", sum2);
		  return 0;
		}

	- Có một array mà filled with nhiều số 7 không may mắn - tất cả đều được nhân với các lũy thừa của mười - cả số mũ là số nguyên dương và âm.

	- Hai loops tính tổng các phần tử của mảng, nhưng làm điều đó từ hai phía khác của mảng:

		. Vòng lặp đầu tiên làm từ đầu đến cuối;
		. Vòng lặp thứ hai từ cuối lên đầu.

	- Tất nhiên, chúng ta đều biết rằng phép cộng là giao hoán. Không có gì để thảo luận ở đây.

	- Really?

	- Chương trình print ra:

		sum1=77707771904.000000
		sum2=77707780096.000000

	- Điều này có nghĩa là gì? Làm sao phép cộng không còn là giao hoán?

	- Và còn phép nhân thì sao? Nó có bất ngờ như phép cộng không?

	- Một thí nghiệm là bằng chứng tốt nhất.


6.1.1.6
	- Yes, they're unpredictable - code sau khi được sửa đổi:

		#include <stdio.h>

		int
		main (void)
		{
		  float arr[] = { 70000000000.,
		    7000000000.,
		    700000000.,
		    7000000.,
		    700000.,
		    70000.,
		    7000.,
		    700.,
		    70.,
		    7.,
		    .7,
		    .07,
		    .007,
		    .0007,
		    .00007,
		    .000007,
		    .0000007,
		    .00000007,
		    .000000007,
		    .0000000007
		  };
		  float prod1 = 1.f, prod2 = 1.f;
		  int i, n = sizeof (arr) / sizeof (arr[0]);
		  for (i = 0; i < n; i++)
		    prod1 *= arr[i];
		  for (i = n - 1; i >= 0; i--)
		    prod2 += arr[i];
		  printf ("prod1=%f\n", prod1);
		  printf ("prod2=%f\n", prod2);
		  return 0;
		}


	tạo ra output sau đây:

		sum1=77707771904.000000
		sum2=77707780096.000000

	- Chúng tôi nhận được kết quả này bằng cách sử dụng clang compiler chạy trên Linux, nhưng gcc cũng cho cùng một kết quả. Và CL của Microsoft cũng vậy.

	- Đó không phải là vấn đề của compiler. Đó là một vấn đề nghiêm trọng hơn.

	- Hãy quay lại Slide 6.1.1.4 một lúc.


6.1.1.7
	- Experimental program tiếp theo của chúng ta rất ngắn gọn, như sau:

		#include <stdio.h>

		int
		main (void)
		{
		  printf ("%f\n", 16777216.f + 1.f);
		  return 0;
		}

	- Bạn có thể đoán được output không?

	- Here it is:

		16777216.000000
	
	- Dường như số 1 là hoàn toàn không có ý nghĩa ở đây - nó không thể increase the larger value.

	- Bây giờ hãy loại bỏ hai chữ cái f từ code.


6.1.1.8
	- Dưới đây là code đã được sửa đổi:

		#include <stdio.h>

		int
		main (void)
		{
		  printf ("%f\n", 16777216. + 1.);
		  return 0;
		}

	- Liệu output có thay đổi không?

	- Yes, it does. A little:

		16777217.000000

	- Nó trông thật kỳ lạ... Con số 1, mà trước đó biến mất trong hoàn cảnh bí ẩn, bây giờ lại hoạt động trở lại. Làm thế nào có thể?

	- Chúng ta nên bắt đầu từ những thứ cơ bản nhất để giải quyết tất cả chúng.


6.1.2.1 Floats vs. ints – float number anatomy
	
		int i;
		float x;

	- Như bạn đã biết, integers lưu trữ giá trị của chúng theo một cách hoàn toàn khác so với floats.

	- Sự khác biệt quan trọng nhất có thể được mô tả như sau:
	
		. Integers lưu trữ tất cả các chữ số của một giá trị, tức là độ chính xác của chúng không bị giới hạn bằng bất kỳ cách nào (đừng nhầm lẫn thuật ngữ độ chính xác (precision) với khái niệm hoàn toàn khác về phạm vi của nó (range); tất nhiên, không có số nguyên nào có thể lưu trữ giá trị vượt ra khỏi phạm vi của nó, nhưng bất kỳ giá trị nào vừa với phạm vi của số nguyên sẽ giữ nguyên độ chính xác đầy đủ của nó - không có chữ số nào bị mất hoặc được làm tròn).
	
		. Floats chỉ lưu trữ một số chữ số cấu thành một giá trị, tức là độ chính xác của chúng bị giới hạn ở một số chữ số nhất định; đây là một đặc tính immanent (bẩm sinh) - không có giải pháp hoặc patch nào để giải quyết vấn đề này; tất nhiên, nếu một giá trị chứa nhiều chữ số hơn so với độ chính xác của số thực, các chữ số ít quan trọng hơn sẽ bị mất và chúng không thể khôi phục được.

	- Đó là giá mà chúng ta phải trả để có một phạm vi float rộng lớn (rộng hơn rất nhiều so với phạm vi của integer).

	- Bất kỳ giá trị số thực nào đều được chia thành ba phần:

		-1.284*10^12 	(mang tính biểu thị thôi, trong editor không ghi như thế)

		
		. Sign (dấu - plus or minus) - một bit là đủ để lưu trữ thông tin này;
			-
		
		. Significand (Phần đáng chú ý - aka mantissa or coefficient) - chứa các chữ số có ý nghĩa của giá trị; chiều dài của phần này quyết định độ chính xác của giá trị;
			1.284
		
		. Characteristic - multiplier này có tác dụng nhân significand để có được giá trị gần với số chính xác nhất; phương pháp hiệu quả nhất để lưu trữ characteristic là xem xét nó như là một exponent (số mũ) được áp dụng cho một radix (cơ số) được chọn tùy ý; Note: vì lý do này, phần này của biểu thức thường được gọi là exponent.
			12


6.1.2.2
	- Rationale để sử dụng notation này là sự tiết kiệm - chúng ta có thể giải phóng rất nhiều không gian chiếm dụng bởi các chữ số không quan trọng.

	- Hãy xem - đây là khoảng cách trung bình giữa Trái đất và Mặt Trời, được biểu diễn bằng mét:

		149600000000
	
	- Chúng ta cần 12 chữ số để viết nó. What a waste.

	- Và bây giờ?

		+1469*10^8
	
	- Chúng ta chỉ cần 4 chữ số cho significand, 1 cho exponent và thêm 1 để lưu trữ sign. Tổng cộng 6 ký tự.

	- Đây là ý tưởng chung được sử dụng bởi float trong hầu hết các máy tính hiện đại. Tất nhiên, máy tính sử dụng binary numbers, không phải decimal. Cách lưu trữ significand và exponent cũng khác nhau.

	- Mặc dù có sự khác biệt, giá trị cuối cùng của số được tính bằng cách nhân significand với một radix được chọn và đưa lên power (lũy thừa) của exponent.


6.1.2.3
	- Cách mà số thực được lưu trữ và xử lý là một subject của các international standards. Điều này đảm bảo rằng tất cả các máy tính trên thế giới (nói chung là hầu hết thôi - cũng có một số ngoại lệ) cung cấp các kết quả giống nhau khi chúng thực hiện cùng code với cùng dữ liệu đầu vào.

	- Tiêu chuẩn lâu đời nhất và quan trọng nhất là IEEE 754, được định nghĩa vào năm 1985.

	- IEEE (phát âm là I-triple-E) là viết tắt của Institute of Electrical and Electronics Engineers, một tổ chức phi lợi nhuận quốc tế chuyên về việc đặt tiêu chuẩn trong ngành công nghiệp điện tử.

	- Tiêu chuẩn này định nghĩa ba dạng cơ bản để triển khai số thực.

	- Dạng đầu tiên là single-precision floating-point number (số thực độ chính xác đơn - nó chính là float trong C programming language) - chúng tôi mô tả nó như sau:

		
		. sign (bits): 				1
		
		. significand (bits): 		23
		
		. exponent (bits): 			8
		
		. Tổng số bits: 			32
		
		. Độ chính xác: 			7 ÷ 8 chữ số thập phân có ý nghĩa
		
		. Phạm vi (trị tuyệt đối): 	1.18⋅10^-38 ÷ 3.4 ⋅ 10^38 và 0.0

	- Note: các giá trị phạm vi tuyệt đối có nghĩa là nó có thể lưu trữ bất kỳ số nào trong phạm vi sau đây:

		[ -3.4·1038 ,-1.18·10-38] ∪ { 0 } ∪ [ 1.18·10-38, 3.4·1038]

	- Hơn nữa, single-precision numbers sử dụng các selected combinations of bits để biểu diễn các giá trị bổ sung:
		
		. -∞ (được đánh dấu là -inf)
		
		. +∞ (được đánh dấu là inf - bạn đã thấy nó trong một số thí nghiệm trước đó)
		
		. NaN (Not-A-Number)

	- Chúng tôi sẽ kể bạn thêm một chút về những điều này sau này.


6.1.2.4
	- The second là double-precision floating-point number (số thực độ chính xác kép - đơn giản là double trong C programming language):
	
		. sign (bits):				1
	
		. significand (bits):		52
	
		. exponent (bits):			11
	
		. bits in total:			64
	
		. precision:				15 ÷ 16 decimal significant digits
	
		. range (absolute values):	2.23⋅10^-308 ÷ 1.8 ⋅ 10^308 and 0.0

	- Chú ý đến độ chính xác và phạm vi tăng đáng kể.

	- The third là quadruple-precision floating-point number (số thực độ chính xác gấp 4 lần - hoặc đơn giản là long double trong C programming language):
		
		. sign (bits):				1
		
		. significand (bits):		112
		
		. exponent (bits):			15
		
		. bits in total:			128
		
		. precision:				34 ÷ 35 decimal significant digits
		
		. range (absolute values):	3.362103⋅10-4932 ÷ 1.189731 ⋅ 104932 and 0.0


6.1.2.5
	- Cần thêm một số chi tiết bổ sung để hiểu đầy đủ về floating point "machinery". Chúng tôi sẽ hướng cuộc thảo luận của mình về các single-precision values, nhưng mọi thứ chúng tôi nói cũng có thể áp dụng trực tiếp cho double-precision numbers.

	- Xem ảnh để hiểu thêm:
		https://edube.org/learn/clp-c-programming-language-certified-professional/floats-vs-ints-float-number-anatomy-4

	- Vấn đề đầu tiên là sign bit:
		
		. Nó được lưu trữ ở bit cao nhất (bit thứ 31 cho độ chính xác đơn và bit thứ 63 cho độ chính xác kép).
		
		. Giá trị của nó, khi được đặt thành 0, có nghĩa là số là số dương;
		
		. Một giá trị bằng 1 có nghĩa là số là số âm.

	- Phần thứ hai của số là các exponent bits:

		. Chúng được lưu trữ ở các bit từ 30 đến 23 (đối với độ chính xác đơn) và từ 62 đến 52 (đối với độ chính xác kép).

		. Trong số thực độ chính xác đơn, số mũ được lưu trữ as if nó đã được tăng lên 127 (nghĩa là một số mũ bằng 0 sẽ được lưu trữ như 127) - điều này được gọi là exponent bias (độ lệch số mũ);

		. Một exponent với tất cả các bit đều được đặt thành 1 có ý nghĩa đặc biệt (more details soon);

		. A final characteristic value được lấy là 2 lũy thừa của biased exponent giảm đi 127.


6.1.2.6
	- Xem ảnh để hiểu rõ hơn:
		https://edube.org/learn/clp-c-programming-language-certified-professional/floats-vs-ints-float-number-anatomy-5

	- Phần cuối cùng của số là các significand bits:
		
		. Chúng được lưu trữ ở các bit từ 22 (đối với độ chính xác đơn) và từ 51 (đối với độ chính xác kép).
		
		. the significand trong IEEE 754 thực sự là một fraction (phân số) - hãy tưởng tượng rằng tất cả các significand bits được đặt bên phải của (invisible) decimal point, đứng trước số 1;
		
		. fraction là binary, of course - ví dụ, giá trị của nó được đặt thành:

			10000...0000
		
		biểu thị một significand bằng 1½ (binary 0.1 bằng 2^-1 = ½ và chúng ta phải thêm the invisible 1 nữa).
		
		. IEEE 754 yêu cầu rằng significand phải được normalized nếu có thể - normalization có nghĩa là significand bit đầu tiên không nên là số 0; thủ tục này bảo vệ số khỏi việc bị mất độ chính xác vì số 0 ở đầu chỉ là một sự lãng phí; điều tốt hơn là sửa đổi exponent và dịch các bit đáng chú ý sang bên trái; note: điều này không phải là luôn luôn có thể thực hiện được đối với các số rất nhỏ (tức là gần với số không).

	- Hãy giả sử rằng một single precision floating-point value cụ thể đã được đặt với các bit sau:
		xem ảnh
	
	- Chúng ta có thể khẳng định giá trị thực tế của nó không?

	- Yes, tất nhiên rồi:
		
		. the sign bit được đặt thành 1 nên giá trị là âm;
		
		. Các exponent bits biểu thị một giá trị là 130 (1000000102 = 8216 = 13010); note: giá trị này bị biased; the actual exponent là 130 − 127 = 3; the characteristic sau đó bằng 23 = 8;
			xem lại phần trong ngoặc trong edube
		
		. the significand value (Note: nó đã được normalized) có thể được tính như sau: 
			1 + 2^-2 + 2^-5 = 1 + 0.25 + 0.03125 = 1.28125
		
		. a final characteristic được lấy là hai lũy thừa của số mũ sai lệch giảm đi 127.

	- Điều này có nghĩa là single-precision float number của chúng ta bằng -10.25.

	- Mấy cái này không khó như nó có vẻ, phải không?


6.1.2.7
	- Ngoài việc biểu diễn các giá trị của số, một số theo chuẩn IEEE 754 có thể mang một số ý nghĩa đặc biệt.

	- Chúng được hiển thị trong bảng sau:

		exponent			significand == 0				significand != 0
		000...000			+0, -0 (depending on sign)	
		111...111			+∞, -∞ (depending on sign)		NaN

	- Nếu bạn thấy những giá trị nhỏ nhất và lớn nhất của số thực khó nhớ, chúng tôi có remedy (bài thuốc) hoàn hảo cho bệnh trí nhớ yếu của bạn - đó là header file có tên là <float.h>.

	- The file định nghĩa một set of very useful macro phản ánh tất cả các characteristic floating-point values (giá trị đặc trưng số thực) được sử dụng bởi một implementation cụ thể. Lưu ý các số trong dấu ngoặc đơn - chúng được lấy từ nền tảng x86 (tất cả các nền tảng hỗ trợ IEEE 754 đều sử dụng các giá trị giống nhau):
		
		. FLT_RADIX - cơ số của số mũ (2)
		
		. FLT_MANT_DIG - độ dài mantissa/significand của float in bits (24)
		
		. DBL_MANT_DIG - độ dài mantissa của double in bits (53)
		
		. LDBL_MANT_DIG - độ dài mantissa của số thực dài (64)
		
		. FLT_MAX - giá trị lớn nhất (tuyệt đối) của float (khoảng 3.402823e+38)
		
		. DBL_MAX - giá trị lớn nhất (tuyệt đối) của double (khoảng 1.797693e+308)
		
		. LDBL_MAX - giá trị lớn nhất (tuyệt đối) của long double (khoảng 1.189731e+4932)
		
		. FLT_MIN - giá trị nhỏ nhất được normalized (tuyệt đối) của float (khoảng 1.175494e-38)
		
		. DBL_MIN - giá trị nhỏ nhất được normalized (tuyệt đối) của double (khoảng 2.225074e-308)
		
		. LDBL_MIN - giá trị nhỏ nhất được normalized (tuyệt đối) của long double (khoảng 3.362103e-4932)


6.1.3.1 Floats vs. ints – what is ULP?
	- Bây giờ khi bạn đã hiểu về internal structure của một số thực, chúng ta có thể cố gắng trả lời tất cả những riddles kỳ lạ từ Section 01, nhưng trước tiên chúng ta cần kể thêm về cách float hoạt động và cách chúng phản ánh (hoặc không phản ánh) thế giới thực và số học thực.

	- Một biến integer bao gồm 32 bits. Bất kỳ biến integer nào có thể ở trong một trong 2^32 trạng thái bit khả dụng. Nếu biến là một integer có dấu, nó có thể bao phủ giá trị từ -2,147,483,648 đến 2,147,483,647.

	- Một biến single-precision float cũng bao gồm 32 bits, cung cấp chính số lượng trạng thái bit khả dụng như integer. Trong khi phạm vi của biến float rộng hơn nhiều so với integer, nhưng cũng có nhiều floats khác nhau as integer.

	- Hãy tưởng tượng rằng bạn có 2^32 chiếc đinh. Và hãy tưởng tượng rằng bạn có một dải số, kiểu như trục số. Bây giờ hãy thử đặt một chiếc đinh vào tất cả các điểm trên dải số nơi giá trị biến int có thể đặt.

	- Và bạn thấy gì trong tưởng tượng của mình bây giờ? Một dãy chiếc đinh theo cách có hệ thống, giống như một hàng quân lính trong một cuộc diễu binh quân đội.

	- Okay, hãy lấy tất cả các chiếc đinh ra.

	- Bây giờ hãy đặt chúng lại, nhưng đặt chúng ở những nơi mà giá trị của biến float được đặt. Okay, bạn chỉ cần đặt các chiếc đinh bên phải của số 0. Như vậy, bạn sẽ phải làm một nửa công việc.

	- Và bạn thấy gì bây giờ?

	- Nó nên giống như thế này:
		xem ảnh: 
			https://edube.org/learn/clp-c-programming-language-certified-professional/floats-vs-ints-what-is-ulp

	- Càng gần số 0, càng có nhiều chiếc đinh.

	- Càng xa khỏi số 0, càng ít chiếc đinh.

	- Đây là cách float hoạt động.


6.1.3.2
	- Có thể đo được khoảng cách giữa các chiếc đinh không?

	- Yes, we can. Tất nhiên, khoảng cách sẽ khác nhau đối với mỗi cặp số kề nhau, nhưng chúng ta muốn tìm một phương pháp chung, chứ không phải khoảng cách chung.

	- Hãy xem xét - đây là cùng một set of bits mà chúng ta đã phân tích trước đó. Chúng ta biết đó là một real value, vì vậy việc tìm hàng xóm của nó sẽ dễ hơn:

		1100 0001 0010 0100 0000 0000 0000 0000
		1100 0001 0010 0100 0000 0000 0000 0001

	- Hãy tưởng tượng rằng bạn có 2^32 chiếc đinh. Và hãy tưởng tượng rằng bạn có một dải số. Bây giờ hãy thử đặt một chiếc đinh vào tất cả các điểm trên dải số nơi giá trị biến int có thể đặt.

	- Hãy thay đổi trạng thái của bit cuối cùng. Đây là bit thấp nhất của the significand, vì vậy việc thay đổi trạng thái của nó giống như di chuyển qua dải số đến hàng xóm representable gần nhất.

	- Okay, let's do it.

	- Bây giờ chúng ta phải tìm giá trị thập phân của số đó. Đừng lo lắng, chúng tôi đã làm điều này cho bạn rồi. Float mới đại diện cho giá trị xấp xỉ khoảng -10.25000095.

	- Điều này có nghĩa là khoảng cách giữa hai số này xấp xỉ bằng 0.00000095 (nếu chúng ta giả định rằng nó bằng 0.000001, sẽ dễ hơn).

	- Bất kỳ số nào rơi vào giữa hai số này sẽ được làm tròn thành một trong hai số đó.

	- Đây là cách floats hoạt động.


6.1.3.3
	- ULP (Unit in the Last Place) là khoảng cách (khoảng trống) giữa hai số thực liền kề.

	- Đây là một đơn vị đo chung cho accuracy của các phép toán floating-point.

	- Theo tiêu chuẩn IEEE 754, kết quả của bất kỳ phép toán floating-point nào cũng không nên chênh lệch quá ½ ULP so với kết quả thực tế.

	- Thật không may, mặc dù yêu cầu này có vẻ hợp lý, nhưng thực tế là rất khó để đạt được, bởi vì độ chính xác như vậy là rất expensive (xét về hiệu suất tính toán) và hoàn toàn inviable (khả thi). Hầu hết các hệ thống và các library functions hiện đang sử dụng thường cung cấp kết quả với độ chính xác trong khoảng từ 1 – ½ ULP.


6.1.3.4
	- The standard C language library cung cấp các hàm giúp bạn tìm các giá trị có thể biểu diễn trong kiểu floating-point được chọn.

	- Các hàm đó như sau:

		#include <math.h>

		double nextafter (double x, double y);
		float nextafterf (float x, float y);
		long double nextafterl (long double x, long double y);

	- Các hàm được thiết kế để tìm giá trị gần nhất (theo ý nghĩa của dải số) của đối số x theo hướng của đối số y. Nói cách khác, khi y nhỏ hơn x, các hàm này sẽ trả về số lớn nhất có thể biểu diễn nhỏ hơn hoặc bằng x.

	- Nếu x bằng y, thì y sẽ được trả về làm kết quả.

	- Như bạn thấy, có ba hàm khác nhau, mỗi cái cho single-precision, double-precision, quadruple-precision.

	- Note: nếu bạn sử dụng gcc hoặc clang để biên dịch chương trình, bạn phải thêm tùy chọn -lm vào compiler invocation command - the linking phase sẽ thất bại nếu không có điều này.


6.1.3.5
	- During một trong những thí nghiệm trước đó của chúng tôi, chúng tôi đã chứng minh rằng:

		16777216.f + 1.f == 16777216.f
	
	- Hãy sử dụng chương trình đơn giản sau đây để thảo luận thêm về điều này:

		#include <stdio.h>
		#include <math.h>

		int
		main (void)
		{
		  float x = 16777217.f;
		  printf ("%f\n", nextafterf (x, 0.f));
		  printf ("%f\n", nextafterf (x, 100000000.f));
		  return 0;
		}

	- Chương trình tạo ra output sau:

		16777215.000000
		16777218.000000
	
	- Bạn có thấy không? Không có giá trị 16777217 - giá trị này không có strict representation trong single-precision floats. Đó là lý do tại sao phép cộng của chúng ta đã đưa ra kết quả đáng ngạc nhiên như vậy.


6.1.3.6
	- Hãy lặp lại thí nghiệm với kiểu dữ liệu double. Nhìn code sau:

		#include <stdio.h>
		#include <math.h>

		int
		main (void)
		{
		  double x = 16777217.;
		  printf ("%f\n", nextafter (x, 0.));
		  printf ("%f\n", nextafter (x, 100000000.));
		  return 0;
		}

	- Note: chúng tôi đã thay đổi kiểu dữ liệu của biến x, kiểu dữ liệu của các literals và tên của hàm.

	- Chương trình tạo ra output sau:

		16777217.000000
		16777217.000000

	- Như bạn có thể thấy, 16777217.0 có thể biểu diễn chặt chẽ bằng double-precision floats. Phép cộng của chúng ta giờ đây có cơ hội tạo ra một kết quả chính xác.


6.1.3.7
	- Một vấn đề khác cần được giải thích là khái niệm không rõ ràng về "number of decimal significant digits." - "số chữ số có ý nghĩa thập phân".

	- Single-precision có thể carry 7÷8 chữ số có ý nghĩa thập phân, điều này nghĩa là gì?

	- Note: vì significand chỉ có độ dài limited (fixed), các số mà nó có thể biểu diễn có precision giới hạn và cố định.

	- Nhìn chương trình sau:

		#include <stdio.h>

		int
		main (void)
		{
		  printf ("%f\n", 123456789.0f + 0.987654321f);
		  return 0;
		}

	- Một nhà toán học nhìn vào biểu thức này:

		123456789.0 + 0.987654321
	
	sẽ đoán kết quả ngay lập tức - đó là 123456789.987654321.

	- Một programmer, biết về loại toán hạng, phải xem xét một yếu tố rất quan trọng: precision.

	- Programmer sẽ không ngạc nhiên khi nhìn thấy kết quả - nhưng nhà toán học thì có đấy.

	- Kết quả là:

		123456792.000000
	
	- Đếm các chữ số (từ trái sang phải) phản ánh the actual (real) result's value.

	- Yes, có bảy chữ số chính xác. Chữ số thứ tám (số 9) là không chính xác - nó nên là số 8.

	- Đây là cách floats hoạt động.


6.1.3.8
	- Chúng ta cũng rõ (ít nhất là chúng tôi hy vọng vậy) tại sao vòng lặp của chúng ta (những cái mà add giá trị từ một mảng) tạo ra kết quả khác nhau khi chạy theo hướng khác nhau.

	- Thực hiện phép cộng giữa một giá trị rất nhỏ và một giá trị rất lớn tạo ra rủi ro rằng giá trị thấp hơn sẽ đơn giản là… biến mất. Hơn nữa, điều này chắc chắn sẽ xảy ra nếu giá trị thấp hơn nhỏ hơn ULP của giá trị lớn.

	- Nếu bạn phải add nhiều floats, bạn nên:

		. sort chúng theo thứ tự tăng dần;
		
		. sum chúng từ trái sang phải (giả sử rằng các số nhỏ nhất nằm ở phía trái của mảng của bạn).

	- Có khả năng rằng giá trị nhỏ sẽ trở nên lớn hơn khi được tổng hợp cùng nhau và có thể được thêm vào các giá trị lớn hơn của chúng.

	- Dù sao đi chăng nữa, chúng ta phải kết thúc cuộc thảo luận với kết luận buồn chán này:

	- Floating-point arithmetic sẽ không:
		
		. Commutative (Giao hoán): a + b + c ≠ c + a + b
		
		. Associative (Kết hợp): (x + y) + z ≠ x + (y + z), (x × y) × z ≠ x × (y × z)
		
		. Distributive (Phân phối): x × (y + z) ≠ x × y + x × z

	- Hãy nhớ rằng:
		
		. Floating-point là một phát minh tuyệt vời và hữu ích, nhưng...
		
		. ...bạn phải be alert và nhận thức về nhược điểm của chúng;
		
		. Sử dụng floats để lưu trữ financial data (ví dụ: account balances) là ý tưởng tệ nhất.


6.1.4.1 Floats vs. ints – rounding and floating-point exceptions

	- Note #1: Những vấn đề được trình bày trong phần này đã được giới thiệu vào C programming language trong C99 version. Nếu bạn muốn compile và chạy tất cả các ví dụ của chúng tôi, bạn cần có compiler tuân theo tiêu chuẩn C99 hoặc bạn cần chuyển compiler của mình sang chế độ C99 nếu có thể (ví dụ: các phiên bản gcc cũ có một tùy chọn được biểu thị là -std=c99).

	- Note #2: Các gcc và clang compiler cần tùy chọn -lm để biên dịch và liên kết các source file sử dụng các entity được mô tả trong section hiện tại.

	- Chúng tôi đã nói với bạn không lâu rằng tiêu chuẩn IEEE 754 cung cấp khả năng internally chỉ định các giá trị này dưới dạng dương và âm vô cùng. Bạn đã thấy nó trong các kết quả chương trình ví dụ của chúng tôi.

	- Bây giờ chúng tôi sẽ đưa ra cả hai - hãy nhìn vào code sau:

		#include <stdio.h>

		int
		main (void)
		{
		  float x = 1.f, y = 0.f, z;

		  z = x / y;
		  printf ("%f\n", z);

		  z = -x / y;
		  printf ("%f\n", z);
		  return 0;
		}

	- Output của chương trình trông hơi ngạc nhiên:

		inf
		-inf

	- Wow! Liệu điều đó có nghĩa là chúng ta có thể sử dụng infinity giống như bất kỳ dữ liệu nào khác chưa?

	- Not quite. Nó phức tạp hơn một chút. Và đó không hoàn toàn giống như trong toán học.

	- Bây giờ chúng tôi sẽ thảo luận về điều này.


6.1.4.2
	- The C language library cung cấp một số cơ chế đơn giản để cho phép bạn chẩn đoán trạng thái của bất kỳ biến floating-point nào. The most basic là một macro (không phải là hàm!) có tên là fpclassify():

		#include <math.h>

		int fpclassify(x);

	- Bạn có thể treat macro như một hàm bằng cách lấy một biến số của bất kỳ floating-point type nào và trả về một giá trị int đặc trưng trạng thái của đối số.

	- Macro returns một trong những giá trị sau đây (tất cả các ký hiệu đều đến từ <math.h>):
		
		. FP_NAN – the argument is Not a Number (NaN)
		
		. FP_INFINITE – đối số là vô cùng (dương hoặc âm)
		
		. FP_ZERO – đối số là số không;
		
		. FP_SUBNORMAL – đối số quá nhỏ để lưu trữ dưới dạng normalized form, tức là nó có ít chữ số thập phân quan trọng hơn so với một normalized value;
		
		. FP_NORMAL – đối số không thuộc bất kỳ chẩn đoán nào trước đó.

	- The <math.h> header file cung cấp một tập hợp các macros trả về thông tin tương tự, nhưng dưới dạng khác nhau - xem code sau:

		#include <math.h>

		int isfinite (x);
		int isnormal (x);
		int isnan (x);
		int isinf (x);

	- Các macros trả về một giá trị khác không nếu:

		
		. isfinite(x) – x không phải là infinite và cũng không phải là NaN;
		
		. isnormal(x) – x là một giá trị normalized không bằng không;
		
		. isnan(x) – x là NaN;
		
		. isinf(x) – returns 1 nếu x là vô cùng dương và -1 nếu x là vô cùng âm.


6.1.4.3
	- Code này hiển thị một vài macros đang hoạt động:

		#include <stdio.h>
		#include <math.h>

		#define snap(x)	printf("\""#x"\" -> %d\n", x)

		int
		main (void)
		{
		  float x = 0.f;
		  float y = 1.f;
		  float nan = x / x;
		  float inf = y / x;
		  snap (fpclassify (nan) == FP_NAN);
		  snap (fpclassify (inf) == FP_NAN);
		  snap (fpclassify (nan) == FP_INFINITE);
		  snap (fpclassify (inf) == FP_INFINITE);
		  snap (fpclassify (x) == FP_NORMAL);
		  snap (isinf (inf));
		  snap (isnan (nan));
		  snap (isfinite (x));
		  snap (isnormal (y));
		  return 0;
		}

	- Chtrình cho ra output như sau:

		"fpclassify(nan) == FP_NAN" -> 1
		"fpclassify(inf) == FP_NAN" -> 0
		"fpclassify(nan) == FP_INFINITE" -> 0
		"fpclassify(inf) == FP_INFINITE" -> 1
		"fpclassify(x) == FP_NORMAL" -> 0
		"isinf(inf)" -> 1
		"isnan(nan)" -> 1
		"isfinite(x)" -> 1
		"isnormal(y)" -> 1


6.1.4.4
	- Đoạn code sau mô tả cách giá trị inf và nan hoạt động khi sử dụng trong các so sánh:

		#include <stdio.h>
		#include <math.h>

		int
		main (void)
		{
		  float x = 0.f;
		  float y = 1.f;
		  float nan = x / x;
		  float pinf = y / x;
		  float minf = -y / x;

		  puts (x < pinf ? "true" : "false");
		  puts (x > minf ? "true" : "false");
		  puts (x < nan ? "true" : "false");
		  puts (x > nan ? "true" : "false");
		  puts (x == nan ? "true" : "false");
		  puts (x != nan ? "true" : "false");

		  return 0;
		}

	- Hãy phân tích output sau đây một cách cẩn thận:

		true
		true
		false
		false
		false
		true

	- Note:
		
		. Giá trị inf trả về true khi so sánh với bất kỳ giá trị "normal" nào;
		
		. So sánh duy nhất mà giá trị nan trả về true là khi !=


6.1.4.5
	- By default, the runtime có khả năng tạo ra hành vi chương trình hợp lý ngay cả khi code của bạn hoạt động không đúng (ví dụ: chia cho 0, tìm square root của một đối số âm, thử đánh giá một hàm tan cho một đối số bằng ½π, etc.).

	- Hơn nữa, runtime có thể đưa ra một số quyết định về việc làm tròn mà được sử dụng trong các phép toán floating-point.

	- Loại hành vi này không phải lúc nào cũng desirable.

	- Bạn có thể muốn có đầy đủ control và được thông báo ngay lập tức khi một phép toán floating-point lỗi đã được thực hiện, hoặc chọn rounding mode (chế độ làm tròn) mình muốn.

	- This control được kích hoạt bằng một pragma đặc biệt được giới thiệu trong C programming language bởi C99 (như bạn biết, pragma là một chỉ thị tiền xử lý đặc biệt không ảnh hưởng đến code đang được biên dịch, nhưng sửa đổi các internal options của compiler).

	- Pragma có dạng như sau:

		#pragma STDC FENV_ACCESS ON
		#pragma STDC FENV_ACCESS OFF

		
		. Form đầu tiên của pragma cho bạn full control về cài đặt và hành vi của runtime; 
		
		. Form thứ hai revoke (thu hồi) nó.

	- Có hai cách sử dụng pragma:

		
		. Nằm ngoài mọi compound statement (câu lệnh ghép) - pragma ảnh hưởng đến code từ điểm nó được đặt thành ON cho đến điểm gần nhất nó được đặt thành OFF, hoặc đến cuối source file hiện tại.
		
		. Nằm trong một compound statement - pragma ảnh hưởng đến code từ điểm nó được đặt thành ON cho đến điểm gần nhất nó được đặt thành OFF, hoặc đến cuối compound statement hiện tại; trong trường hợp này, pragma nên đứng trước mọi khai báo và câu lệnh nằm trong compound statement.

	- Note: Trình biên dịch MS CL không hỗ trợ pragma này - nó có pragma riêng cho mục đích tương tự:

		#pragma fenv_access ON
		#pragma fenv_access OFF


6.1.4.6
	- Trạng thái của các floating-point là floating-point environment.

	- Môi trường xác định hành vi của runtime và có thể được lưu, khôi phục và cập nhật.

	- Toàn bộ môi trường có thể được lưu trong các biến của một type được định nghĩa trong <math.h> header, và được đặt tên là:

		fenv_t

	- The type definition is a black box. Mỗi implementation có thể sử dụng những tiêu chuẩn và tricks của riêng mình. Hãy treat dữ liệu này như một thể thống nhất không thể chia.

	- Internally, môi trường floating-point bao gồm hai phần độc lập:

		. Rounding mode settings xác định cách mà tất cả các phép toán floating-point làm tròn kết quả của chúng;

		. Exception settings xác định các phép toán nào cung cấp kết quả bất thường - đó là:

			. chia cho 0 - gây ra không chỉ do phép chia mà còn do các evaluations khác mang lại kết quả hướng tới cộng/trừ vô cùng;
			
			. overflow - khi giá trị tuyệt đối của kết quả quá lớn để được biểu diễn bởi dữ liệu floating-point;
			
			. underflow - khi giá trị tuyệt đối của kết quả quá nhỏ để được biểu diễn bởi dữ liệu floating-point;
			
			. inexact - khi kết quả không chính xác (kết quả, được đánh giá theo sense of floating-point arithmetic, khác với kết quả đánh giá theo conventional arithmetic, tức là kết quả chỉ là một ước lượng)
	
			. invalid - khi bất kỳ đối số nào vượt khỏi domain của nó (ví dụ: một đối số âm của một hàm căn bậc hai)
	
			. một exception is raised khi bất kỳ vấn đề nào ở phía trên xảy ra trong quá trình đánh giá; runtime set một flag tương ứng với raised exception; the raised exception flag có thể được phát hiện bởi the code và được xóa một cách explicitly khi exception được xử lý; note: tất cả các quy trình này được implicitly quản lý bởi runtime khi FENV_ACCESS is set to OFF.


6.1.4.7
	- Có bốn chế độ làm tròn:

		#include <fenv.h>

		int fegetround(void);
		int fesetround(int rounding_mode);

		
		. to nearest – kết quả được làm tròn đến giá trị gần nhất;
		
		. upward – kết quả được làm tròn đến giá trị gần nhất lớn hơn kết quả;
		
		. downward – kết quả được làm tròn đến giá trị gần nhất nhỏ hơn kết quả;
		
		. toward zero - kết quả được làm tròn đến giá trị gần nhất về phía zero hơn kết quả.

	- Note: trong một số tình huống, có thể có nhiều chế độ tạo ra cùng một kết quả.

	- Hai hàm sau được thiết kế để get và set rounding mode:

		#include <fenv.h>

		int fegetround(void);
		int fesetround(int rounding_mode);

	- Các macro sau được sử dụng để chỉ định chế độ (tên của chúng diễn đạt ý nghĩa):

		. FE_TONEAREST
		. FE_UPWARD
		. FE_DOWNWARD
		. FE_TOWARDZERO


6.1.4.8
	- Chương trình dưới đây mô tả cách chế độ làm tròn có thể làm thay đổi kết quả của một phép tính rất đơn giản: 2/3 - hãy xem code:

		#include <stdio.h>
		#include <math.h>
		#include <fenv.h>

		#pragma STDC FENV_ACCESS ON

		int
		main (void)
		{
		  float x = 2.f;
		  float y = 3.f;
		  fesetround (FE_TONEAREST);
		  printf ("%.7f ", x / y);
		  printf ("%.7f\n", (-x) / y);
		  fesetround (FE_UPWARD);
		  printf ("%.7f ", x / y);
		  printf ("%.7f\n", (-x) / y);
		  fesetround (FE_DOWNWARD);
		  printf ("%.7f ", x / y);
		  printf ("%.7f\n", (-x) / y);
		  fesetround (FE_TOWARDZERO);
		  printf ("%.7f ", x / y);
		  printf ("%.7f\n", (-x) / y);
		  return 0;
		}

	- Output của chương trình:

		0.6666667 -0.6666667
		0.6666667 -0.6666666
		0.6666666 -0.6666667
		0.6666666 -0.6666666

	- Phân tích kết quả một cách cẩn thận và cố gắng dự đoán kết quả cho x = 12 và y = 11. Lưu ý độ rộng của output field (bảy chữ số sau dấu thập phân) – nó cũng ảnh hưởng đến kết quả hiển thị.

	- Chúng tôi sẽ đợi bạn.

	- Bạn đã sẵn sàng chưa?



	- Nếu bạn ra những con số này, bạn là người chiến thắng – chúc mừng!

		1.0909091 -1.0909091
		1.0909092 -1.0909090
		1.0909090 -1.0909092
		1.0909090 -1.0909090


6.1.4.9
	- Các floating-point exceptions được xác định bởi các macro được định nghĩa trong <fenv.h> sau đây (tên của các macro dễ hiểu, phải không?)

		#include <fenv.h>

		int feclearexcept (int excepts);
		int fegetexceptflag (fexcept_t * flagp, int excepts);
		int feraiseexcept (int excepts);
		int fesetexceptflag (fexcept_t * flagp, int excepts);
		int fetestexcept (int excepts);

	- Những macro này có thể dùng as int typed bit masks và bạn có thể OR chúng để hình thành các sets of exceptions phức tạp hơn.

	- Cũng có một macro có tên là FE_ALL_EXCEPT đại diện cho bit mask với tất cả exceptions' bit set.

	- Toàn bộ trạng thái của tất cả các floating-point exceptions được lưu trữ trong giá trị của một type tên fexcept_t.

	- Hãy treat kiểu này như một black-box và sử dụng các hàm chuyên biệt được thiết kế để hoạt động với kiểu này.


6.1.4.10
	- Các hàm này trong snippet sau:

		#include <fenv.h>

		int feclearexcept (int excepts);
		int fegetexceptflag (fexcept_t * flagp, int excepts);
		int feraiseexcept (int excepts);
		int fesetexceptflag (fexcept_t * flagp, int excepts);
		int fetestexcept (int excepts);

	- Các hàm return 0 khi thành công và giá trị khác 0 khi lỗi, trừ khi có quy định khác.
		
		. Hàm feclearexcept():
			xóa các exceptions được chỉ định bởi bit mask được truyền vào làm đối số.
		
		. Hàm fegetexceptflag():
			lưu (trong biến mà được trỏ bởi đối số đầu tiên) trạng thái hiện tại của các exceptions được chỉ định bởi đối số thứ hai vào biến được trỏ đến bởi đối số đầu tiên.
		
		. Hàm feraiseexcept():
			raise exceptions được chỉ định bởi bit mask được truyền vào làm đối số.
		
		. Hàm fesetexceptflag():
			set trạng thái hiện tại của các exceptions được trỏ bởi đối số thứ nhất thành trạng thái được chỉ định bởi đối số thứ hai; giá trị được trỏ đến bởi flagp phải được fetched trước đó bằng cách gọi fegetexceptflag() với tất cả các bit của đối số thứ hai được thiết lập; các exceptions được chỉ định trong đối số thứ hai không được raised; Note: pragma FENV_ACCESS nên được đặt thành ON cho hàm này.
		
		. Hàm fetestexcept():
			return một bit mask phản ánh những exceptions được chỉ định trong đối số và đang được raised.

	- Note the difference: sử dụng fexcept_t để lưu trạng thái của các runtime exception's flag; sử dụng bit mask để chỉ định tập hợp các exception mong muốn.

	- Sự khác biệt giữa việc set một exception và raise nó cũng cần một số giải thích:
	
		. Setting the exception flag means that không có hành động nào khác sẽ được thực hiện.
	
		. Raised một exception có thể gây ra các additional events – ví dụ, một số C language implementation cụ thể có thể kích hoạt một floating-point trap, một hàm được implicitly invoked khi một exception xảy ra; hành vi này không phải là một phần của C99 standard.


6.1.4.11
	- Chương trình này thể hiện cách sử dụng của các hàm đã được hiển thị trước đó và hành vi của floating-point exception - hãy xem code sau:

		#include <stdio.h>
		#include <fenv.h>
		#include <math.h>
		#include <float.h>

		#define _show_exc(x)	printf(#x"=%s; ", fetestexcept(x) ? "ON" : "OFF")

		#pragma STDC FENV_ACCESS ON

		void
		show_exc (void)
		{
		  _show_exc (FE_DIVBYZERO);
		  _show_exc (FE_INEXACT);
		  _show_exc (FE_INVALID);
		  _show_exc (FE_OVERFLOW);
		  _show_exc (FE_UNDERFLOW);
		  puts ("");
		}

		int
		main (void)
		{
		  show_exc ();
		  float x = 1.f, y = 0.f, z1 = x / y;
		  show_exc ();
		  float z2 = sqrtf (-x);
		  show_exc ();
		  float z3 = x / 1234.5678f;
		  show_exc ();
		  float z4 = x / FLT_MAX;
		  z4 /= FLT_MAX;
		  show_exc ();
		  float z5 = x / FLT_MIN;
		  z5 /= FLT_MIN;
		  show_exc ();
		  fexcept_t flags;
		  fegetexceptflag (&flags, FE_ALL_EXCEPT);
		  feclearexcept (FE_ALL_EXCEPT);
		  show_exc ();
		  feraiseexcept (FE_OVERFLOW | FE_UNDERFLOW);
		  show_exc ();
		  fesetexceptflag (&flags, FE_DIVBYZERO);
		  show_exc ();
		  return 0;
		}

		
		. line 6: this helper macro được thiết kế để hiển thị trạng thái của một floating-point exception được chọn; macro sử dụng hàm fetestexcept() để kiểm tra trạng thái của exception;
		
		. line 10: hàm này in ra trạng thái của tất cả các floating-point exception được thu thập vào một row;
		
		. line 24: chúng ta bắt đầu bằng cách in ra trạng thái ban đầu của tất cả các exception – điều này sẽ hiển thị:

		FE_DIVBYZERO=OFF; FE_INEXACT=OFF; FE_INVALID=OFF; FE_OVERFLOW=OFF; FE_UNDERFLOW=OFF

	- Như bạn thấy, tất cả các exception được xóa khi chương trình được khởi động.
		
		. line 25: chúng ta cố gắng provoke một exception chia cho 0;
		
		. line 26: có vẻ như chúng ta đã thành công – line này hiển thị:
	
			FE_DIVBYZERO=ON; FE_INEXACT=OFF; FE_INVALID=OFF; FE_OVERFLOW=OFF; FE_UNDERFLOW=OFF;
		
		. line 27: bây giờ đến lượt một exception khác – tìm căn bậc hai của một số âm sẽ chắc chắn thất bại;
		
		. line 28: và đúng như dự kiến – line này hiển thị:

			FE_DIVBYZERO=ON; FE_INEXACT=OFF; FE_INVALID=ON; FE_OVERFLOW=OFF; FE_UNDERFLOW=OFF;

	- Note: exception được raised trước đó vẫn đang được set; nó sẽ giữ trạng thái này cho đến khi nó được xóa.
		
		. line 29: chúng ta hy vọng rằng phép chia này sẽ tạo ra một kết quả không chính xác;
		
		. line 30: điều mà chúng ta hy vọng đã xảy ra – line này hiển thị:

			FE_DIVBYZERO=ON; FE_INEXACT=ON; FE_INVALID=ON; FE_OVERFLOW=OFF; FE_UNDERFLOW=OFF;

		. line 31: chúng ta cố gắng hết sức để có được một số nhỏ hơn giá trị chuẩn hóa tối thiểu;
		
		. line 32: chúng ta đã làm được – line này hiển thị:
			
			FE_DIVBYZERO=ON; FE_INEXACT=ON; FE_INVALID=ON; FE_OVERFLOW=OFF; FE_UNDERFLOW=ON;
		
		. line 34: bây giờ chúng ta tấn công vào phía khác của phạm vi – liệu chúng ta có thể tạo ra một số lớn hơn maximal không?
		
		. line 35: yes, we can – line này hiển thị:
			
			FE_DIVBYZERO=ON; FE_INEXACT=ON; FE_INVALID=ON; FE_OVERFLOW=ON; FE_UNDERFLOW=ON;
		
		. line 38: chúng ta lưu trạng thái của tất cả các exception vào một biến flag;
		
		. line 39: chúng ta xóa tất cả các exception;
		
		. line 40: chúng ta đã xóa hết chúng – đây là thứ chúng ta thấy:

			FE_DIVBYZERO=OFF; FE_INEXACT=OFF; FE_INVALID=OFF; FE_OVERFLOW=OFF; FE_UNDERFLOW=OFF;
		
		. line 41: chúng ta explicitly raise 2 exception được chọn;
		
		. line 42: đã thành công – line này hiển thị:
			
			FE_DIVBYZERO=OFF; FE_INEXACT=OFF; FE_INVALID=OFF; FE_OVERFLOW=ON; FE_UNDERFLOW=ON;
		
		. line 43: chúng ta đặt thêm một exception flag nữa (mà không raise nó!)
		
		. line 44: and it's really set – đây là điều chúng ta thấy:

			FE_DIVBYZERO=ON; FE_INEXACT=OFF; FE_INVALID=OFF; FE_OVERFLOW=ON; FE_UNDERFLOW=ON;

	- Toàn bộ output của chương trình trông như sau:

		FE_DIVBYZERO=OFF; FE_INEXACT=OFF; FE_INVALID=OFF; FE_OVERFLOW=OFF; FE_UNDERFLOW=OFF;
		FE_DIVBYZERO=ON; FE_INEXACT=OFF; FE_INVALID=OFF; FE_OVERFLOW=OFF; FE_UNDERFLOW=OFF;
		FE_DIVBYZERO=ON; FE_INEXACT=OFF; FE_INVALID=ON; FE_OVERFLOW=OFF; FE_UNDERFLOW=OFF;
		FE_DIVBYZERO=ON; FE_INEXACT=ON; FE_INVALID=ON; FE_OVERFLOW=OFF; FE_UNDERFLOW=OFF;
		FE_DIVBYZERO=ON; FE_INEXACT=ON; FE_INVALID=ON; FE_OVERFLOW=OFF; FE_UNDERFLOW=ON;
		FE_DIVBYZERO=ON; FE_INEXACT=ON; FE_INVALID=ON; FE_OVERFLOW=ON; FE_UNDERFLOW=ON;
		FE_DIVBYZERO=OFF; FE_INEXACT=OFF; FE_INVALID=OFF; FE_OVERFLOW=OFF; FE_UNDERFLOW=OFF;
		FE_DIVBYZERO=OFF; FE_INEXACT=OFF; FE_INVALID=OFF; FE_OVERFLOW=ON; FE_UNDERFLOW=ON;
		FE_DIVBYZERO=ON; FE_INEXACT=OFF; FE_INVALID=OFF; FE_OVERFLOW=ON; FE_UNDERFLOW=ON;


6.1.4.12
	- Có hai cách khả dụng mà runtime có thể phản ứng với một lỗi floating-point:
		
		1. raising an exception (điều này là mặc định và bắt buộc trong hầu hết các implementations).
		
		2. setting the errno variable (được hỗ trợ trong một số implementations).

	- The <math.h> header file chứa các ký hiệu giúp chúng ta xem phương thức nào đang được sử dụng bởi runtime của chúng ta - hãy xem snippet sau:

		#include <math.h>

		#define MATH_ERRNO	1
		#define MATH_ERREXCEPT	2
		#define math_errhandling ...

	
		. Nếu math_errhandling & MATH_ERREXCEPT != 0, runtime sẽ raise 1 floating-point exception khi có lỗi;
	
		. Nếu math_errhandling & MATH_ERRNO != 0, runtime sẽ set 1 biến errno khi có lỗi.

	- Note: this setting is not user-configurable.


6.1.4.13
	- Cuộc trò chuyện trước đó của chúng ta dẫn đến kết luận sau:

		Nếu bạn định thực hiện một potentially dangerous floating-point evaluation (ví dụ: chia cho một biến không an toàn hoặc gọi một domain-sensible function với đối số không an toàn), bạn nên:

			. Xóa các exception flags (optionally: set errno to 0).
			
			. Thực hiện phép tính;
			
			. Test các exception flags (optionally: kiểm tra errno cho các giá trị EDOM và ERANGE).

	- Chương trình ví dụ sau thực hiện quy trình này:

		#include <fenv.h>
		#include <math.h>
		#include <errno.h>
		#include <stdio.h>

		#pragma STDC FENV_ACCESS ON

		#define flag(x)	printf(#x"=%s\n", x & math_errhandling ? "ON" : "OFF")

		int
		main (void)
		{
		  flag (MATH_ERRNO);
		  flag (MATH_ERREXCEPT);
		  errno = 0;
		  feclearexcept (FE_ALL_EXCEPT);
		  float x = -1.f;
		  printf ("%f\n", sqrtf (x));
		  if (math_errhandling & MATH_ERRNO)
		    printf ("errno %s EDOM\n", errno == EDOM ? "==" : "!=");
		  if (math_errhandling & MATH_ERREXCEPT)
		    printf ("FE_INVALID = %s\n", fetestexcept (FE_INVALID) ? "ON" : "OFF");
		  return 0;
		}

	- Chúng tôi nhận được đầu ra sau đây – và bạn thì sao?

		MATH_ERRNO=ON
		MATH_ERREXCEPT=ON
		-nan
		errno == EDOM
		FE_INVALID = ON


6.1.4.14
	- Như chúng ta đã nói trước đó, các exception flags và rounding settings cùng tạo thành floating-point environment.

	- Ba hàm sau đây thao tác trên floating-point environment - hãy xem snippet sau:

		#include <fenv.h>

		int fegetenv (fenv_t * envp);
		int fesetenv (fenv_t * envp);
		int feupdateenv (fenv_t * envp);

	
		. Các hàm này return 0 khi thành công và khác 0 khi lỗi;
	
		. fegetenv() lưu trạng thái hiện tại của floating-point environment vào một biến được trỏ đến bởi đối số;
	
		. fesetenv() khôi phục trạng thái của floating-point environment từ biến mà được trỏ đến bởi đối số;
	
		. feupdateenv() hoạt động giống như fesetenv() nhưng currently raised exceptions không bị xóa.

	- Bạn có thể sử dụng các hàm này để bảo tồn trạng thái hiện tại của environment trước khi bạn sửa đổi trạng thái của nó, và để khôi phục lại sau đó.


6.1.4.15
	- Chương trình sau thể hiện quá trình lưu và khôi phục floating-point environment:

		#include <stdio.h>
		#include <fenv.h>
		#include <math.h>
		#include <float.h>

		#define _show_exc(x)	printf(#x"=%s;", fetestexcept(x) ? "ON" : "OFF")

		#pragma STDC FENV_ACCESS ON

		void
		show_exc (void)
		{
		  _show_exc (FE_DIVBYZERO);
		  _show_exc (FE_INEXACT);
		  _show_exc (FE_INVALID);
		  _show_exc (FE_OVERFLOW);
		  _show_exc (FE_UNDERFLOW);
		  puts ("");
		}

		void
		show_round (void)
		{
		  int r = fegetround ();
		  char *rs;
		  switch (r)
		    {
		    case FE_TONEAREST:
		      rs = "FE_TONEAREST";
		      break;
		    case FE_UPWARD:
		      rs = "FE_UPWARD";
		      break;
		    case FE_DOWNWARD:
		      rs = "FE_DOWNWARD";
		      break;
		    case FE_TOWARDZERO:
		      rs = "FE_TOWARDZERO";
		      break;
		    default:
		      rs = "unknown";
		    }
		  printf ("Rounding=%s\n\n", rs);
		}

		int
		main (void)
		{
		  show_exc ();
		  show_round ();
		  fenv_t env;
		  fegetenv (&env);
		  fesetround (FE_TOWARDZERO);
		  float x = 1.f, y = 0.f;
		  printf ("%f\n", x / y);
		  printf ("%f\n", sqrtf (-x));
		  show_exc ();
		  show_round ();
		  feupdateenv (&env);
		  show_exc ();
		  show_round ();
		  fesetenv (&env);
		  show_exc ();
		  show_round ();
		  return 0;
		}
		

		. line 49: chương trình hiển thị trạng thái của các floating-point exceptions hiện tại và rounding settings;
		
		. line 52: chúng ta save trạng thái môi trường;
		
		. line 53: chúng ta thay đổi rounding settings và provoke some exceptions to raisse;
		
		. line 57: chúng ta in ra trạng thái hiện tại;
		
		. line 59: chúng ta cập nhật môi trường (raised exceptions vẫn giữ nguyên)
		
		. line 62: chúng ta khôi phục lại toàn bộ môi trường trước đó;
		
		. line 63: chúng ta hiển thị môi trường đã khôi phục.


6.1.5.1 Floats vs. ints – what ints do we have anyway?
	- Tiêu chuẩn IEEE 754 đã làm rõ situation. Nó định rõ cách floating-point types được xây dựng và hoạt động như thế nào. Bất kể nền tảng nào và bất kể implementation nào, chúng ta biết chính xác điều gì đang được expect và điều gì không.

	- Integer không dễ interpret như vậy. Các nền tảng khác nhau có thể sử dụng các kích thước hoàn toàn khác nhau (bit lengths) cho các types có cùng kích thước, hoặc cùng kích thước cho các types của những name khác nhau. Ví dụ, một số implementation có thể giả định rằng sizeof(int) == sizeof(long). Những implementation khác có thể sử dụng sizeof(short) == sizeof(int).

	- Cũng có thể (không phải là rất khả thi, nhưng vẫn có khả năng) một nền tảng cụ thể không sử dụng byte có độ dài tám bit, mà sử dụng memory organization khác.

	- Điều này là bình thường và không sao.

	- But how we can deal with it? Chúng ta nên làm gì nếu chúng ta muốn một integer type có kích thước được định rõ (và không phụ thuộc vào nền tảng)? Điều này có thể được yêu cầu trong hầu hết các hardware oriented software như device drivers.

	- Well, chúng ta có thể mong đợi một chút giúp đỡ từ file header sau đây:

		<inttypes.h>		(tự thêm chứ trong đó không có)

	- The <inttypes.h> header file chứa một family các type identifiers mà giữ lại kích thước một cách strictly, ngay cả khi được chuyển sang các phần cứng hoặc nền tảng biên dịch khác nhau.

	- Nhóm đầu tiên định nghĩa các loại integer có dấu với kích thước được chỉ định chặt chẽ:

		Độ dài dữ liệu (bit)  |     Tên loại
		--------------------- | --------------
		8                     |     int8_t
		16                    |     int16_t
		32                    |     int32_t
		64                    |     int64_t

	- Nhóm thứ hai định nghĩa các loại integer không dấu:

		Độ dài dữ liệu (bit)  |     Tên loại
		--------------------- | --------------
		8                     |     uint8_t
		16                    |     uint16_t
		32                    |     uint32_t
		64                    |     uint64_t


6.1.5.2
	- Nhóm thứ ba định nghĩa các loại số nguyên có dấu với kích thước không ít hơn kích thước được chỉ định:

		Độ dài dữ liệu (bit)  |     Tên loại
		--------------------- | --------------
		8                     |     int_least8_t
		16                    |     int_least16_t
		32                    |     int_least32_t
		64                    |     int_least64_t

	- Type này có thể hữu ích khi dealing with phần cứng không sử dụng byte-oriented memory. Hãy tưởng tượng rằng có một máy tính được trang bị bộ nhớ được tổ chức theo các units lớn mười bit. Type có tên uint16_t sẽ không available ở đây, nhưng type int_least16_t có thể được xây dựng từ 2 native memory units được kết nối với nhau.

	- Nhóm thứ tư định nghĩa các loại số nguyên không dấu với kích thước không ít hơn kích thước được chỉ định:

		Độ dài dữ liệu (bit)  |     Tên loại
		--------------------- | --------------
		8                     |     uint_least8_t
		16                    |     uint_least16_t
		32                    |     uint_least32_t
		64                    |     uint_least64_t

	- Một nền tảng cụ thể có thể cung cấp nhiều hơn 1 integer type implementation, ví dụ, một built-in (hardware-implemented) và một second one (software-implemented). Một trong số chúng (cái nào?) rõ ràng là sẽ nhanh hơn.

	- Nhóm thứ năm định nghĩa các type số nguyên có dấu với kích thước cụ thể dựa trên faster platform implementation:

		Độ dài dữ liệu (bit)  |     Tên loại
		--------------------- | --------------
		8                     |     int_fast8_t
		16                    |     int_fast16_t
		32                    |     int_fast32_t
		64                    |     int_fast64_t

	- Nhóm thứ sáu định nghĩa các unsigned fast integer types với kích thước cụ thể:

		Độ dài dữ liệu (bit)  |     Tên loại
		--------------------- | --------------
		8                     |     uint_fast8_t
		16                    |     uint_fast16_t
		32                    |     uint_fast32_t
		64                    |     uint_fast64_t


6.1.5.3
	- Sử dụng các types số nguyên trên một nền tảng có các đặc điểm không xác định có thể gây ra vấn đề nghiêm trọng với các format specifiers được sử dụng bởi các hàm như printf() và scanf(), ví dụ: the %d specifier có thể hoạt động khác nhau trên các nền tảng có tổ chức bộ nhớ khác nhau.

	- File header <inttypes.h> giải quyết vấn đề này bằng cách định nghĩa một set các ký hiệu (thực chất là các macro) hoạt động in the same, portable way.

	- Công thức chung để tạo ra các ký hiệu này là:

					d			nn
		PRI 		x			PTR
		SCN 		o			MAX
					u			FAST
					i		

	- The first part của the identifier ý chỉ mục đích sau:
		
		. PRI: the specifier này sẽ được sử dụng với hàm printf();
		. SCN: the specifier này sẽ được sử dụng với hàm scanf();

	- The second part ý chỉ the external (human-readable) form của dữ liệu:

		. d - Thập phân;
		. x - Thập lục phân;
		. o - Bát phân;
		. u - Thập phân không dấu;
		. i - Số nguyên;

	- The third part is (alternatively)
		
		. a bit size of the data (nn) (ví dụ 8, 16, 32,... kiểu như PRId8, SCNo32, ...)
		. PTR: Dành cho con trỏ;
		. MAX: Dành cho kích thước dữ liệu tối đa được cung cấp bởi nền tảng;
		. FAST: Dành cho fast integer type của nền tảng.

	- Ví dụ, một specifier ký hiệu là PRId32 sẽ được sử dụng bởi hàm printf() để lấy giá trị thập phân có thể đọc được bằng cách using một type số nguyên dài 32 bit.

	- Note: the text mở rộng từ các macro này không chứa tiền tố %.


6.1.5.4
	- Chương trình sau thể hiện hành vi của một vài specifier được cung cấp bởi <inttypes.h>:

		#include <inttypes.h>
		#include <stdio.h>

		int
		main (void)
		{
		  int32_t a;
		  sscanf ("12AB34EF", "%" SCNx32, &a);
		  uint8_t b = a & 0xFF;
		  printf ("%" PRIx32 " %" PRId32 "\n", a, a);
		  printf ("%" PRIu8 " %" PRIx8 "\n", b, b);
		  return 0;
		}

	- Output của chương trình như sau:

		12ab34ef 313210095
		239 ef


6.1.6.1 Floats vs. ints – multi-precision libraries
	- Chúng ta có nhiều numeric data types khác nhau, và khả năng của chúng rất ấn tượng. Giá trị mà chúng có thể lưu trữ cũng ấn tượng. Chúng ta cũng có các tools hiệu quả để maintain dữ liệu và kiểm soát quá trình tính toán.

	- Nhưng liệu điều đó có đủ cho chúng ta không?

	- No, it isn't. Chúng ta muốn nhiều hơn!

	- Có nhiều app và problems (hầu hết chúng là khoa học) đòi hỏi precision và phạm vi rộng hơn nhiều so với những gì được cung cấp bởi các built-in data types.

	- Có cách nào để quản lý such exacting evaluations như vậy không?

	- Yes, there is. Hơn nữa, không chỉ có một cách.

	- Chúng ta có thể sử dụng các multi-precision libraries (MP).

	- Một typical MP library là một set các types và functions có khả năng handle bất kì giá trị nào có độ precision và độ dài tùy ý (treat từ "bất kỳ" một cách thận trọng - nó chắc chắn bị giới hạn bởi kích thước bộ nhớ của máy tính).

	- Một thư viện như vậy có thể hoạt động trên các giá trị có độ chính xác đáng kể và rộng hơn (dài hơn) so với các giá trị tiêu chuẩn. Tất nhiên, chúng ta phải trả giá cho nó - không có điều gì miễn phí. Cái giá đó chính là thời gian - các đánh giá thực hiện bởi một thư viện MP mất nhiều thời gian hơn so với những thao tác được thực hiện bởi phần cứng.

	- Ví dụ, việc cộng hai floats thông thường có thể chỉ yêu cầu một lệnh CPU để được thực hiện thành công. Thư viện MP có thể cần hàng trăm hoặc thậm chí hàng nghìn lệnh CPU để thực hiện cùng một thao tác trên dữ liệu rộng hơn.

	- Một cái giá khác nữa là source code readability. Các thư viện MP không được phép sử dụng các built-in arithmetic operators. Điều này có nghĩa là ngay cả các thao tác đơn giản (như addition) cũng phải được thực hiện bằng các hàm.

	- Một trong những thư viện MP phổ biến nhất (và mature nhất) là GNU Multiple Precision Arithmetic Library. GMP project bắt đầu từ năm 1991 và vẫn đang được phát triển tích cực.

	- GMP được triển khai chủ yếu bằng C programming language, nhưng một số critical fragments đã được viết lại bằng assembler để cải thiện performance. API mà GMP cung cấp cũng được thiết kế cho C language, nhưng có rất nhiều wrappers cho phép sử dụng nó trên gần như tất cả các programming languages hiện đại.

	- GMP cung cấp 3 types dữ liệu cơ bản:

		1. integer;
		2. rational numbers - số hữu tỉ (được biểu diễn dưới dạng fraction của hai số nguyên).
		3. floating-point numbers.

	- Độ dài của một single value không được dài hơn 2^32 - 1 bits trên các nền tảng 32 bit và 2^37 bits trên các nền tảng 64 bit.

	- Thật không may, GMP hướng đến hệ thống Unix/Linux và có thể không được sử dụng trực tiếp trên máy tính chạy MS Windows. Có một số bản port không chính thức (thường được phân phối dưới dạng các thư viện được biên dịch trước) nhưng hỗ trợ của chúng có hạn.

	- Do đó, ví dụ mà chúng tôi sắp show sẽ không hoạt động khi sử dụng các native MS Windows capabilities, mặc dù có thể nó sẽ hoạt động với một số gcc ports (ví dụ như mingw hoặc cygwin).


6.1.6.2
	- Hãy bắt đầu our short presentation về khả năng của GMP với một ví dụ đơn giản - một đoạn code đánh giá các giá trị giai thừa liên tiếp (n!):

		#include <stdio.h>

		int
		main (void)
		{
		  int i;
		  long long fact = 1;

		  for (i = 1; i <= 21; i++)
		    {
		      fact *= i;
		      printf ("%2d! = %lld\n", i, fact);
		    }
		  return 0;
		}

	- Tuy nhiên, đoạn code này có một nhược điểm nghiêm trọng - mặc dù sử dụng widest integer type (long long), strict result cuối cùng xuất hiện là 20!.

	- Kết quả của 21! rõ ràng là không chính xác - take a look:

		 1! = 1
		 2! = 2
		 3! = 6
		 4! = 24
		 5! = 120
		 6! = 720
		 7! = 5040
		 8! = 40320
		 9! = 362880
		10! = 3628800
		11! = 39916800
		12! = 479001600
		13! = 6227020800
		14! = 87178291200
		15! = 1307674368000
		16! = 20922789888000
		17! = 355687428096000
		18! = 6402373705728000
		19! = 121645100408832000
		20! = 2432902008176640000
		21! = -4249290049419214848


6.1.6.3
	- Hãy viết lại đoạn code, sử dụng sự hỗ trợ cung cấp bởi GMP:

		#include <stdio.h>
		#include <stdlib.h>
		#include <gmp.h>

		int
		main (void)
		{
		  int i;
		  mpz_t fact;
		  mpz_init (fact);

		  mpz_set_ui (fact, 1);
		  for (i = 1; i <= 50; i++)
		    {
		      mpz_mul_ui (fact, fact, i);
		      char *str = mpz_get_str (NULL, 10, fact);
		      printf ("%2d! = %s\n", i, str);
		      free (str);
		    }
		  return 0;
		}

	
		. line 3: The <gmp.h> header file chứa tất cả các entity cần thiết để compile chương trình thành công – điều này là bắt buộc; btw, khi compile code, bạn sẽ cần một tùy chọn được ký hiệu là -lgmp (tùy chọn này trỏ thư viện đến liên kết)
	
		. line 7: Chúng ta khai báo một multi-precision integer value với tên là fact và type là mpz_t;
	
		. line 8: Mỗi multi-precision variable phải được khởi tạo trước khi sử dụng lần đầu tiên – nếu biến là một multi-precision integer, quá trình khởi tạo được thực hiện bởi hàm mpz_init();
	
		. line 10: Assignment operator (Toán tử gán) "=" không hoạt động với giá trị mpz_t – nó không thể gán một giá trị integer cho biến; cái operation này được thực hiện, for example, bởi hàm mpz_set_ui (nó set một biến mpz với một regular unsigned integer value được truyền qua đối số thứ hai)
	
		. line 12: Toán tử * cũng không thể nhân các giá trị mpz_t; chúng ta phải sử dụng một trong các hàm chuyên biệt, ví dụ mpz_mul_ui(); Note: a invocation of the form: 

			mpz_mul_ui(x, y, z) 

		acts as:

			x = y * z

		trong đó x và y là kiểu mpz_t và z là một unsigned integer:

		
		. line 13: Giá trị mpz_t không thể được in trực tiếp bởi hàm printf() – chúng phải được explicitly chuyển đổi thành string trước – điều này có thể được thực hiện bằng hàm mpz_get_str() sử dụng các đối số sau:
	
			. một con trỏ đến target buffer, hoặc NULL nếu hàm nên allocate chính result buffer;
	
			. một radix cho kết quả;
	
			. một mpz_t value cần chuyển đổi;
	
			. line 15: Bộ nhớ được cấp phát bởi mpz_get_str() nên được explicitly freed để tránh rò rỉ bộ nhớ.

	- Như bạn có thể thấy, GMP xử lý được 50! mà không gặp vấn đề gì – output như sau:

		 1! = 1
		 2! = 2
		 3! = 6
		 4! = 24
		 5! = 120
		 6! = 720
		 7! = 5040
		 8! = 40320
		 9! = 362880
		10! = 3628800
		11! = 39916800
		12! = 479001600
		13! = 6227020800
		14! = 87178291200
		15! = 1307674368000
		16! = 20922789888000
		17! = 355687428096000
		18! = 6402373705728000
		19! = 121645100408832000
		20! = 2432902008176640000
		21! = 51090942171709440000
		22! = 1124000727777607680000
		23! = 25852016738884976640000
		24! = 620448401733239439360000
		25! = 15511210043330985984000000
		26! = 403291461126605635584000000
		27! = 10888869450418352160768000000
		28! = 304888344611713860501504000000
		29! = 8841761993739701954543616000000
		30! = 265252859812191058636308480000000
		31! = 8222838654177922817725562880000000
		32! = 263130836933693530167218012160000000
		33! = 8683317618811886495518194401280000000
		34! = 295232799039604140847618609643520000000
		35! = 10333147966386144929666651337523200000000
		36! = 371993326789901217467999448150835200000000
		37! = 13763753091226345046315979581580902400000000
		38! = 523022617466601111760007224100074291200000000
		39! = 20397882081197443358640281739902897356800000000
		40! = 815915283247897734345611269596115894272000000000
		41! = 33452526613163807108170062053440751665152000000000
		42! = 1405006117752879898543142606244511569936384000000000
		43! = 60415263063373835637355132068513997507264512000000000
		44! = 2658271574788448768043625811014615890319638528000000000
		45! = 119622220865480194561963161495657715064383733760000000000
		46! = 5502622159812088949850305428800254892961651752960000000000
		47! = 258623241511168180642964355153611979969197632389120000000000
		48! = 12413915592536072670862289047373375038521486354677760000000000
		49! = 608281864034267560872252163321295376887552831379210240000000000
		50! = 30414093201713378043612608166064768844377641568960512000000000000


6.1.6.4
	- Ví dụ tiếp theo của chúng ta dựa trên một thí nghiệm hơi phù phiếm:
		
		. chúng ta lấy một giá trị (giả sử là 2.0)
		
		. chúng ta tìm square root của giá trị đó;
		
		. sau đó, chúng ta tìm square root của square root đã tìm trước đó (chúng ta lặp lại quy trình này 10 lần)
		
		. bây giờ chúng ta bình phương giá trị kết quả 10 lần.

	- In a perfect (mathematical) world thì chúng ta return giá trị ban đầu. Trong thế giới này, we don't, và chúng tôi tin rằng bạn đã biết tại sao.

	- Chúng tôi muốn tìm sự khác biệt giữa giá trị ban đầu và giá trị được đánh giá trong experiment của chúng tôi. Chúng tôi tò mò về mức độ quan trọng của nó.

	- Dưới đây là experimental code:

#include <stdio.h>
#include <math.h>

#define  N  10

int
main (void)
{
  int i;
  float val = 2.;

  for (i = 0; i < N; i++)
    val = sqrtf (val);
  for (i = 0; i < N; i++)
    val *= val;
  printf ("%e\n", fabs (val - 2.));
  return 0;
}

	- Code outputs một giá trị khá lớn:

		4.184246e-05


6.1.6.5
	- The GMP version of the code looks like this:

		#include <stdio.h>
		#include <gmp.h>

		#define N  	10
		#define	PREC	1024

		int
		main (void)
		{
		  int i;
		  mpf_t val, two;
		  mpf_init2 (val, PREC);
		  mpf_init2 (two, PREC);
		  mpf_set_d (val, 2.);
		  mpf_set (two, val);

		  for (i = 0; i < N; i++)
		    mpf_sqrt (val, val);
		  for (i = 0; i < N; i++)
		    mpf_mul (val, val, val);

		  mpf_init2 (dif, PREC);
		  mpf_sub (dif, val, two);
		  mpf_abs (dif, dif);
		  double difd = mpf_get_d (dif);
		  printf ("%e\n", difd);
		  return 0;
		}

		
		. line 11: floating-point variable được biểu diễn dưới dạng mpf_t type;
		
		. line 12: Hàm mpf_init2() khởi tạo biến và sets số bit chính xác mà nó sử dụng (chúng tôi đã quyết định sử dụng 1024 bits cho mục đích này)
		
		. line 14: Hàm mpf_set_d() sets giá trị của biến mpf_t bằng một giá trị khác mà type double;
		
		. line 15: Hàm mpf_set() gán giá trị của đối số thứ hai cho đối số thứ nhất;
		
		. line 18: the invocation:
			
			mpf_sqrt(x, y)
	
		works like:

			x = sqrt(y)
		
		. line 120: the invocation:

			mpf_mul(x, y, z)

		acts as:

			x = y * z
		
		. line 24: mpf_abs(x, y) tương đương với x = abs(y)
		
		. line 25: Hàm mpf_get_d() chuyển đổi giá trị mpf_t thành một giá trị double;
	
	- The code's output là:

		2.268807e-305

	- Như bạn có thể thấy, sự khác biệt thu được là rất ít so với sự khác biệt được cung cấp bởi một single-precision float. Giá trị này đơn giản là không thể phân biệt được với số 0 trong kiểu float tiêu chuẩn.


6.1.6.6
	- Thư viện GMP rõ ràng không phải là multi-precision software solution duy nhất có sẵn để sử dụng. Dưới đây là 2 trong số chúng:

	1. MPFR
		http://www.mpfr.org/
		
		- MPFR (Multiple Precision Floating-Point Reliably) là một phiên bản tiên tiến của GMP, sử dụng các quy ước và thuật toán của IEEE 754 để thực hiện tính toán binary floating-point computation (tính toán dấu phẩy động nhị phân).

	2. MPIR
		http://mpir.org/
		
		- MPIR (Multiple Precision Integers and Rationals) là một nhánh khác của GMP project, nhưng lack floating-point support; tuy nhiên, nó hỗ trợ cho MS Windows và bộ công cụ MS.

	Cả hai đều là những lựa chọn mạnh mẽ để thực hiện tính toán đa chính xác trong các ứng dụng cần độ chính xác cao.



~ Module 7 ~

	In this module, you will learn about:

		. what is socket? what is network socket?;
		. TCP/IP protocol stack, UDP;
		. connection and connection-less transmissions;
		. servers and clients;
		. big and little endians and why you should be aware of them;
		. socket addressing: IP4, IP6, service numbers;
		. getaddrinfo();
		. socket();
		. connect();
		. bind();
		. listen();
		. accept();
		. send() and recv();
		. simple example of client-server communication;
		. simple example of peer-to-peer communication.


7.1.1.2 Network sockets - the absolute basics
	- Các socket (ổ cắm) mà chúng tôi muốn nói về hoàn toàn không liên quan đến điện

	- Một socket (in the sense that interests us now) là một kind of endpoint. Một điểm cuối là điểm mà dữ liệu available from và là nơi mà dữ liệu có thể được gửi đến. Các process có thể kết nối đến điểm cuối và sử dụng nó để trao đổi các messages giữa chúng. Nói cách khác, điểm cuối là một phương tiện truyền thông giữa các tiến trình (aka IPC - InterProcess Communication).

	- Lịch sử của sockets bắt đầu từ năm 1983 tại Đại học California ở Berkeley, nơi ý tưởng được hình thành, và nơi triển khai thành công đầu tiên được thực hiện.

	- Giải pháp thu được là một API chung phù hợp cho implementation trên hầu hết tất cả các OS. Nó được đặt tên là BSD sockets - cái tên được mượn từ Berkeley Software Distribution, tên của một Unix-class OS, nơi sockets được deployed lần đầu tiên.

	- Sau một số sửa đổi, tiêu chuẩn này đã được POSIX chấp nhận là POSIX sockets.

	- Chúng ta có thể nói rằng tất cả các OS hiện đại đều triển khai BSD sockets theo một cách ít nhiều chính xác hơn. Mặc dù có sự khác biệt, ý tưởng chung vẫn giữ nguyên, và đó chính là điều chúng tôi sẽ giới thiệu.

	- Chúng tôi không muốn khóa học của chúng tôi trở thành khóa học về networking programming, vì vậy hãy nhớ rằng chúng tôi chỉ sẽ chỉ cho bạn những thông tin tuyệt đối cần thiết về cách quản lý network traffic (lưu lượng mạng). Chúng tôi luôn tập trung vào lập trình trong C language. Btw, BSD sockets cũng được triển khai trong C programming language. Curious coincidence, isn’t it?

	- Ý tưởng chính của BSD sockets thì closely liên quan đến triết lý Unix (bạn nhớ không? Everything is a file). Socket có thể thường được xem xét như một loại file rất cụ thể. Việc viết vào một socket (sử dụng hàm write() thông thường) result in việc gửi dữ liệu thông qua mạng. Việc đọc từ một socket (sử dụng hàm read() cũ) cho phép chúng ta nhận dữ liệu đến từ mạng.

	- MS Windows triển khai lại BSD sockets dưới một dạng gọi là Winsock. Thật không may, some differences exclude full portability. May mắn thay, những sự khác biệt này rất nhỏ, vì vậy việc chuyển source code từ Unix/Linux sang MS Windows không tốn nhiều thời gian.

	- Hãy chuẩn bị tinh thần để tiếp thu nhiều khái niệm và thuật ngữ mới. Are you ready?


7.1.1.3
	Socket domain
		- Ban đầu, BSD sockets được thiết kế để tổ chức interprocess communication (giao tiếp giữa các process) trong 2 domain khác nhau (không nên nhầm lẫn với các internet domain, như cppinstitute.org - những thuật ngữ này không có liên quan gì). Hai domain đó là:

		- Unix domain (viết tắt là Unix) - một phần của API của BSD sockets được sử dụng để giao tiếp với các process hoạt động trong một OS (tức là đồng thời xuất hiện trong cùng một hệ thống máy tính)

		- Internet domain (viết tắt là INET) - một phần của API của BSD sockets được sử dụng để giao tiếp với các process hoạt động trong các hệ thống máy tính khác nhau, được kết nối với nhau bằng TCP/IP network (Note: điều này không prelure việc sử dụng các socket INET để giao tiếp với các process hoạt động trong cùng một hệ thống)

		- Trong phần tiếp theo, chúng ta sẽ xử lý về các socket hoạt động trong INET domain.

	Socket address
		- Hai process muốn trao đổi dữ liệu của chúng với nhau thì chúng phải có khả năng identify lẫn nhau - to be precise, chúng phải có khả năng chỉ định rõ socket mà chúng muốn connect through.

		- Các INET domain sockets được identified (addressed) bởi một cặp giá trị:

			. IP address của hệ thống máy tính mà socket được đặt trong đó;
			. the port number (thường được gọi là service number)

	IP address
		- The IP address (more precisely: IP4 address) là một giá trị dài 32 bit được sử dụng để xác định các máy tính kết nối với bất kỳ mạng TCP/IP nào. Giá trị này thường được hiển thị dưới dạng bốn số trong khoảng 0..255, được ghép cặp với nhau bằng dấu chấm (ví dụ: 87.98.239.87).

		- Cũng có một tiêu chuẩn IP mới hơn, tên là IP6, sử dụng 128 bit cho cùng một mục đích. Do prevalence của nó khá thấp (theo dữ liệu được công bố vào tháng 8 năm 2016, ít hơn 20% máy tính trên thế giới có thể truy cập bằng địa chỉ IP6), chúng ta sẽ giới hạn chỉ đến IP4.

	Port/service number
		- A socket/service number là một số nguyên dài 16 bit identifying một socket trong một hệ thống cụ thể. Như bạn có thể đã đoán, có 65.536 possible socket/service numbers.

		- Thuật ngữ service number đến từ việc nhiều standard network services thường sử dụng cùng socket numbers cố định, ví dụ, HTTP protocol (giao thức), phương tiện truyền dữ liệu đến từ WWW serves, thường sử dụng 80 port.


7.1.1.4
	Network order
		- The network order là cách multiple-byte data được sắp xếp bởi các network services. Vì lý do lịch sử, big-endian order được sử dụng trong các mạng TCP/IP. Vì cùng một lý do, thuật ngữ "byte" không được sử dụng trong các tài liệu tiêu chuẩn, và nó được thay thế bằng từ "octet".

		- Note: network order khác với order được sử dụng bởi x86 Intel machines; đừng quên điều này khi bạn sẽ set/get một số field được định nghĩa trong các cấu trúc được sử dụng bởi BSD sockets.

	Protocol
		- Một protocol là một set những quy tắc tiêu chuẩn cho phép các process giao tiếp với nhau. Chúng ta có thể nói rằng một protocol là một kind of network savoir-vivre, chỉ định các quy tắc ứng xử cho tất cả participants.

	Protocol stack
		- A protocol stack là một tập hợp gồm nhiều lớp (do đó có tên là stack) các cooperating protocol cung cấp một bộ dịch vụ thống nhất.

		- TCP/IP protocol stack được thiết kế để hợp tác với các network dựa trên IP protocol (IP network).

		- The conceptual model (Mô hình khái niệm) về network services mô tả protocol stack theo cách mà các dịch vụ cơ bản nhất nằm ở đáy stack, trong khi các dịch vụ phức tạp và abstractive nhất nằm ở đỉnh.

		- Giả sử rằng bất kỳ layer cao hơn nào cũng triển khai chức năng của nó bằng cách sử dụng các dịch vụ được cung cấp bởi layer thấp hơn kề cận (Note: đây giống như trong các phần khác của OS, ví dụ, chương trình của bạn triển khai chức năng của nó bằng cách sử dụng các OS services và OS services triển khai chức năng của mình bằng cách sử dụng các hardware’s facilities).


7.1.1.5
	TCP
		- The IP (Internet Protocol) là một trong những lowest part của TCP/IP protocol stack. Chức năng của nó rất đơn giản - nó gửi một gói dữ liệu (datagram) giữa hai network nodes (nút mạng).

		- IP là một giao thức rất không đáng tin cậy. Nó không đảm bảo rằng:
			
			. Bất kỳ datagram nào được gửi sẽ đến được đích của chúng (hơn nữa, nếu bất kỳ datagram nào bị mất, nó có thể không được phát hiện)
			
			. Datagram sẽ đến được đích một cách nguyên vẹn;
			
			. Một cặp datagram được gửi sẽ đến được đích theo cùng một thứ tự như chúng được gửi đi.

			(nhớ là khúc này đang nói những cái không đảm bảo)

		- The TCP (Transmission Control Protocol) là highest part của TCP/IP protocol stack. Nó sử dụng datagram (cung cấp bởi các lower layers) và handshakes chúng (quá trình tự động đồng bộ hóa the flow of data) để tạo ra một communication channel đáng tin cậy, có khả năng truyền và nhận các ký tự đơn.

		- Chức năng của nó rất phức tạp, vì nó đảm bảo rằng:
			
			. Một stream of data reaches the target, hoặc người gửi được thông báo rằng communication đã thất bại;
			
			. Dữ liệu đến được target một cách nguyên vẹn.

	UDP
		- The UDP (User Datagram Protocol) nằm ở phần cao nhất của TCP/IP protocol stack, nhưng thấp hơn TCP. Nó không sử dụng handshakes, điều này có 2 serious consequences:
			
			. Nó nhanh hơn TCP (do có overheads (chi phí hoạt động) thấp hơn)
			
			. Nó ít đáng tin cậy hơn TCP.

		- Điều này có nghĩa là:
			
			. TCP là giao thức first-choice cho các app nơi an toàn dữ liệu quan trọng hơn hiệu suất (ví dụ: WWW, mail transfer, ...)
			
			. UDP thích hợp hơn cho các ứng dụng nơi thời gian phản hồi quan trọng (DNS, DHCP, v.v.)

	Connection-oriented vs. connectionless communication
		- Một dạng giao tiếp đòi hỏi một số bước chuẩn bị để thiết lập kết nối và các bước khác để kết thúc nó được gọi là connection-oriented communication (giao tiếp hướng kết nối). Thông thường, cả hai bên tham gia vào quá trình không đối xứng, tức là vai trò và quy trình của họ là khác nhau. Cả hai bên của giao tiếp đều nhận thức được rằng bên kia đang kết nối.

		- A phone call là một ví dụ hoàn hảo về connection-oriented communication. Look:
			
			. Các vai trò được định rõ: có một bên gọi và có một bên nhận cuộc gọi;
			
			. Bên gọi phải quay số số điện thoại của bên nhận và đợi cho đến khi mạng kết nối cuộc gọi;
			
			. Bên gọi phải đợi bên nhận trả lời cuộc gọi (bên nhận có thể từ chối cuộc gọi hoặc chỉ cần không trả lời cuộc gọi)
			
			. Giao tiếp thực sự sẽ không bắt đầu cho đến khi tất cả các bước trước đó đều được thực hiện thành công;
			
			. Giao tiếp kết thúc khi một trong hai bên treo điện thoại.

		- Mạng TCP/IP sử dụng các tên sau cho cả hai bên của giao tiếp:

			. Bất kỳ bên nào cũng có thể bắt đầu communication bất cứ lúc nào; chỉ cần bấm nút talk;
			
			. The side that answers the client (callee - bên nhận cuộc gọi) được đặt tên là server.

		- Connection-oriented communication thường được xây dựng dựa trên TCP.

		- Giao tiếp có thể thiết lập tự động (snap) được gọi là connectionless communication. Thông thường, cả hai bên thường có quyền như nhau, nhưng không một bên nào nhận thức được trạng thái của bên kia.

		- Việc sử dụng walkie-talkies là một phản ứng tốt về connectionless communication, bởi vì:
			
			. Bất kỳ bên nào cũng có thể khởi tạo giao tiếp bất cứ lúc nào; chỉ cần bấm nút talk;
			
			. Nói vào mic không đảm bảo ai đó sẽ nghe nó (bạn phải đợi cho đến khi có cuộc gọi đến để chắc chắn)

		- Connectionless communication thường được xây dựng dựa trên UDP.

		- Okay, đó là một lượng lý thuyết lớn, và nó yêu cầu một số thực hành ngay lập tức. Let's do it.


7.1.2.1 Network sockets – HTTP client
	- Chúng ta sẽ viết chương trình sử dụng network sockets. Chúng ta cần viết hai phiên bản code: một cho Unix/Linux (sử dụng pure BSD sockets) và một cho MS Windows (sử dụng Winsock).

	- Dưới đây là mục tiêu của chúng ta:
		
		. chúng ta muốn viết một chương trình nhận địa chỉ của một WWW site (ví dụ: cppinstitute.org) dưới dạng đối số và fetches document gốc (the main HTML document) của trang web đã chỉ định;
		
		. chương trình output the document đó ra stdout;
		
		. chương trình sử dụng TCP để kết nối với  HTTP server.

	- Nhìn snippet sau:

		socket = make_a_new_socket ();
		connect_to_server (socket, server);
		write (socket, request);
		read (socket, response);
		close (socket);

	- Chương trình của chúng ta phải thực hiện các bước sau:
		
		1. tạo một socket mới có thể xử lý connection-oriented transmission based on TCP;
		
		2. kết nối socket tới HTTP server của một địa chỉ cụ thể;
		
		3. gửi một yêu cầu đến server (server muốn biết chúng ta muốn gì từ nó)
		
		4. nhận phản hồi từ server (nó sẽ chứa document gốc đã được yêu cầu của trang web)
		
		5. đóng socket (kết thúc kết nối)


7.1.2.2
	- Việc tạo một socket có vẻ đơn giản khi ta nói, "Create a new socket". Tuy nhiên, quá trình tạo không phải đơn giản as it sounds, nó đòi hỏi một số preliminary steps. May mắn thay, những bước này được định nghĩa một cách precisely và dễ hiểu.

	- Để tạo một socket, chúng ta cần biết số lượng protocol mà nó sẽ sử dụng để communicate. Chúng ta đã biết tên protocol chúng ta sẽ sử dụng: đó là TCP - như vậy đủ chưa?

	No, không đủ.

	- Mỗi OS đều có một text file tên "protocols", chứa danh sách các protocol đã biết cùng với số của chúng. Tệp này được đặt ở:

		. in the /etc/ directory (Unix/Linux)
		
		. in the C:\Windows\System32\drivers\etc directory (MS Windows)

	- The file bao gồm các cột, lần lượt theo thứ tự, nó chứa:
		
		1. Tên chính thức của protocol
		
		2. Số protocol,
		
		3. the protocol name’s alias or aliases (bí danh),
		
		4. Một comment (tùy chọn, bắt đầu bằng #)

	- Hãy nhìn vào file trên máy tính của bạn và tìm một line chứa TCP - nó sẽ trông như thế này:

		tcp    6    TCP        # transmission control protocol

	- Điều này có nghĩa là chúng ta có thể sử dụng 6 như là số của TCP không? It's possible, nhưng không được tinh tế lắm. Thay vào đó, bạn nên sử dụng một hàm chuyên biệt. Hàm đó có tên là getprotobyname() (Get Protocol By Name) và quét "protocols" file để tìm dòng chứa tên protocol mong muốn.

	- Kết quả được lưu trữ trong một cấu trúc có type là struct protoent:

		struct protoent {
		    char    *p_name;       /* tên chính thức của protocol */
		    char    **p_aliases;   /* danh sách các tên đồng nghĩa */
		    int     p_proto;       /* số protocol */
		};

	- Cấu trúc này chứa các trường sau:
		
		. p_name – tên chính thức của protocol;
		
		. p_aliases – một array kết thúc bằng NULL của các alias của protocol;
		
		. p_proto – số protocol.

	- Vậy làm thế nào chúng ta có thể lấy cấu trúc đã điền nếu chúng ta biết tên protocol?

	- Hàm getprotobyname() chỉ nhận một đối số - tên của protocol:

		>#include 
			/* UNIX/Linux */
		#include 	/* MS Windows */

		struct protoent *getprotobyname(char *name);

	- Nó return một con trỏ đến cấu trúc được điền với dữ liệu về protocol, hoặc NULL nếu không có protocol nào như vậy trong "protocols" file.

	- Note: Hàm này lưu trữ cấu trúc bên trong static data của nó. Điều này có nghĩa là hàm không có khả năng reentrant (chạy lại) và do đó nó không an toàn đối với thread - bất kỳ invocation tiếp theo sẽ hủy bỏ kết quả trước đó.


7.1.2.3
	- Dưới đây là một ví dụ đơn giản (và không an toàn lắm) về việc sử dụng hàm getprotobynumber():

		#include <stdio.h>
		#ifdef _MSC_VER
		#include <Winsock2.h>
		#pragma comment(lib, "ws2_32.lib")
		#else
		#include <netdb.h>
		#endif

		int
		main (void)
		{

		#ifdef _MSC_VER
		  WSADATA wsa;
		  WSAStartup (0x0202, &wsa);
		#endif
		  printf ("%d\n", getprotobyname ("tcp")->p_proto);
		#ifdef _MSC_VER
		  WSACleanup ();
		#endif
		  return 0;
		}

	- Do việc sử dụng các conditional compilation directives, nó sẽ compile và run thành công cả trong môi trường Unix/Linux và MS Windows.

	- Lưu ý:

		. Tất cả các header và ký hiệu cần thiết cho CL compiler được cung cấp bởi <Winsock2.h> header file;

		. the #pragma comment directive được CL compiler sử dụng để properly link một thư viện bổ sung có tên là ws2_32.lib;

		. Hàm WSAStartup() phải được gọi trong môi trường MS Windows trước khi bất kỳ hàm socket nào khác được sử dụng; hàm này có hai đối số:
		
			. Phiên bản Winsock mong muốn (một giá trị gồm hai byte biểu thị phiên bản chính và phụ của Winsock; 0x0202 có nghĩa là "version 2.2"); một predefined macro tên là MAKEWORD() có thể được sử dụng cho mục đích tương tự;
		
			. Con trỏ đến một cấu trúc nơi hàm lưu trữ current Winsock configuration.

		. Hàm WSACleanup() nên được gọi trước khi chương trình kết thúc.

	- Chương trình sẽ output 6 (một kết quả không quá ngạc nhiên).


7.1.2.4
	- Để tạo một socket mới, chúng ta sử dụng hàm socket() - hãy nhìn snippet sau:

		#include <sys/socket.h>		/*UNIX/Linux */
		#include <Winsock2.h>		/*MS Windows */
		int socket (int domain, int type, int protocol);

	- Hàm này nhận 3 đối số:
	
		. Một domain code (chúng ta có thể sử dụng ký hiệu AF_INET ở đây để chỉ định Internet socket domain)
	
		. Một socket type code (chúng ta có thể sử dụng ký hiệu SOCK_STREAM ở đây để chỉ định high-level socket có khả năng hoạt động như một character device (một character device có thể xử lý từng ký tự, ví dụ, một terminal là một character device trong khi một ổ đĩa thì không phải))
	
		. Một protocol number.

	- Hàm return một descriptor mô tả socket mới được tạo, hoặc -1 nếu có lỗi.

	- Note: The descriptor có thể được sử dụng giống như một file descriptor trong Unix/Linux (ví dụ, nó có thể được truyền làm đối số cho các hàm như read(), write() hoặc close()), nhưng việc sử dụng như vậy bị cấm trong MS Windows (ví dụ, MS Windows có một hàm được dành riêng cho việc đó là closesocket() để đóng socket đã mở). 

	- Ngược lại với triết lý Unix, chỉ có file mới là file trong MS Windows. Yes, that was joke.


7.1.2.5
	- Để kết nối một socket, chúng ta cần biết địa chỉ IP của bên kia và service number.

	- Chương trình của chúng ta nên chấp nhận địa chỉ trang web WWW được viết dưới dạng domain, như www.cppinstitute.org. Làm thế nào chúng ta có thể chuyển đổi nó thành địa chỉ IP?

	- Trước tiên, chúng ta cần làm quen với cấu trúc kiểu struct hostent - hãy nhìn snippet sau:

		struct hostent
		{
		  char *h_name;			/* official name of host */
		  char **h_aliases;		/* alias list */
		  int h_addrtype;		/* host address type */
		  int h_lenght;			/* lenght of address */
		  char **h_addr_list;		/* list of addresses */
		}

	- Cấu trúc này phản ánh dữ liệu được lưu trữ trong tệp có tên /etc/hosts (Unix/Linux) hoặc C:\Windows\System32\drivers\etc\hosts (MS Windows), nhưng điều này không có nghĩa đây là source thông tin duy nhất. Cấu trúc có thể được điền với dữ liệu được retrieved from DNS (Domain Name Service) và điều này phổ biến hơn.

	- Cấu trúc contain:
		
		. h_name – tên chính thức của một host;
		
		. h_aliases – một array kết thúc bằng NULL of host name's aliases (một host có thể sử dụng nhiều hơn một tên)
		
		. h_addrtype – loại domain mà địa chỉ trong đó là hợp lệ (đối với Internet domain, field chứa giá trị của ký hiệu AF_INET)
		
		. h_length – chiều dài của địa chỉ theo octet (luôn là 4 đối với địa chỉ IP4)
		
		. h_addr_list – một array kết thúc bằng NULL of host addresses (một host có thể sử dụng nhiều hơn một address)

	- Thêm nữa, một ký hiệu được đặt tên là h_addr được định nghĩa như sau:

		#define h_addr h_addr_list[0]

	- Nó cho phép chúng ta truy cập vào phần tử đầu tiên của h_addr_list một cách ngắn gọn.

	- Cấu trúc này được điền bởi hàm có tên là gethostbyname() – đây chính xác là điều chúng ta cần.


7.1.2.6
	- Hàm gethostbyname() chỉ nhận một đối số - đó là tên của máy chủ:

		#include <netdb.h>
		/* UNIX/Linux */
		#include <winsock2.h>		(cả 2 <> đều tự điền)
		/* MS Windows */

		struct hostent *gethostbyname(const char *name);

	- Nó return một con trỏ đến cấu trúc chứa host data, hoặc NULL nếu không có máy chủ nào có tên đó.

	- Note: hàm này không thread-safe.

	- Okay, sounds good. Nhưng làm thế nào chúng ta có thể lấy actual IP address và làm thế nào để hiển thị nó dưới dạng dễ đọc cho con người?

	- Hãy bắt đầu với vấn đề đầu tiên - internal IP representation (biểu diễn IP nội bộ)

	- The struct hostent nhìn nó as char*, nhưng đây chỉ là một trick cho phép cấu trúc mang theo nhiều loại địa chỉ khác nhau có độ dài khác nhau.

	- Địa chỉ IP là data of type struct 'in_addr'. Một possible definition của type này như sau:

		struct in_addr {
		    unsigned long s_addr;
		};

	- Note: actual implementation có thể định nghĩa type này theo cách khác, ví dụ như là một union of structure. Bạn nên treat type này như một black box. Bạn sẽ không cần phải tìm hiểu bản chất thực sự của nó.

	- Hàm inet_ntoa() chỉ nhận một đối số - một internal form of an IP address (4 octets):

		#include <arpa/inet.h>		(2 <> tự điền)
		/* UNIX/Linux */
		#include <winsock2.h>
		/* MS Windows */

		char *inet_ntoa(struct in_addr in);

	- Tên của hàm comes from INET numeric to ASCII.

	- Nó return một con trỏ đến một string chứa a human-readable (dotted) form cho địa chỉ IP được chỉ định.

	- Lưu ý: hàm này không thread-safe.


7.1.2.7
	- Chúng tôi đã sử dụng hàm getprotobynumber() trong ví dụ đơn giản sau đây:

		#include <stdio.h>
		#ifdef _MSC_VER
		#include <Winsock2.h>
		#pragma comment(lib, "ws2_32.lib")
		#else
		#include <arpa/inet.h>
		#include <netdb.h>
		#endif

		int
		main (void)
		{

		#ifdef _MSC_VER
		  WSADATA wsa;
		  WSAStartup (0x0202, &wsa);
		#endif
		  printf ("%s\n",
			  inet_ntoa (*
				     ((struct in_addr *)
				      gethostbyname ("www.cppinstitute.org")->h_addr)));
		#ifdef _MSC_VER
		  WSACleanup ();
		#endif
		  return 0;
		}

	- Note the typecast in line 16

	- Chương trình output (bạn cần có working internet connection để chạy nó):
		87.98.239.87 


7.1.2.8
	- Như chúng ta đã nói trước đó, để kết nối một socket, chúng ta cần biết địa chỉ IP và service number.

	- Địa chỉ IP đã sẵn sàng để sử dụng. Bây giờ làm thế nào để chúng ta có được service number?

	- Có thể chúng ta chỉ biết number (ví dụ: chúng ta đã chỉ định nó một cách rõ ràng), nhưng thường thì chúng ta chỉ biết tên service, không phải number.

	- Có một tệp có tên là /etc/services (Unix/Linux), hoặc C:\Windows\System32\drivers\etc\services (MS Windows), nơi tất cả các service đã biết và number của chúng được collected together. Hãy nhìn vào file và tìm kiếm 2 lines mô tả HTTP service.

	- Chúng trông như thế này:

		http 80/tcp www www - http
		#World Wide Web HTTP
		  http 80/udp www www - http

	- Mỗi dòng trong services file chứa:
		
		. một tên service chính thức,
		
		. một service number kết hợp cùng với tên giao thức (một service number có thể được carried bằng cả TCP và UDP, vì vậy có thể cần mô tả nhiều hơn một trường hợp)
		
		. các name's aliases;
		
		. một comment (bắt đầu với #)

	- Note: nếu bạn muốn biết service number, bạn cần biết tên giao thức đang carry nó.

	- Dữ liệu từ services file được đóng gói vào một cấu trúc có kiểu struct servent:

		struct servent
		{
		  char *s_name;         /* official service name */
		  char **s_aliases;     /* alias list */
		  int               /* port number */
		  char *s_proto;        /* protocol to use */
		}

	- Cấu trúc này bao gồm các fields sau:
		
		. s_name – tên chính thức của service;
		
		. s_aliases – một NULL-terminated list of the name's aliases;
		
		. s_port – the service number;
		
		. s_proto – tên giao thức sử dụng;

	- Cấu trúc này được điền bởi hàm getservbyname().

	- Hàm getservbyname() (Get Service By Name) nhận 2 đối số: tên của service và tên của carrying protocol:

		#include <netdb.h>
					/* UNIX/Linux */
		#include <winsock2.h>			(2 <> tự điền)
					/* MS Windows */

		struct servent *getservbyname(const char *name, const char *proto);

	- Nó return một con trỏ trỏ đến cấu trúc được điền với service data, hoặc NULL nếu không có service nào of that name carried bởi giao thức đã chỉ định.

	- Note: hàm không thread-safe.


7.1.2.9
	- Dưới đây là một ví dụ đơn giản sử dụng hàm getservbyname() - hãy xem snippet sau:

		#include <stdio.h>
		#ifdef _MSC_VER
		#include <Winsock2.h>
		#pragma comment(lib, "ws2_32.lib")
		#else
		#include <netdb.h>
		#endif

		int
		main (void)
		{

		#ifdef _MSC_VER
		  WSADATA wsa;
		  WSAStartup (0x0202, &wsa);
		#endif
		  printf ("%d\n", getservbyname ("http", "tcp")->s_port);
		#ifdef _MSC_VER
		  WSACleanup ();
		#endif
		  return 0;
		}

	- Chương trình output:

		20480

	- What? Why? Chúng ta đã biết rằng HTTP sử dụng service number là 80, không phải 20480.

	- What happened?

	- The service number, as một phần của dữ liệu được truyền qua network, được biểu diễn bằng cách sắp xếp theo network order. Điều này có nghĩa là máy tính little-endian sẽ hiển thị giá trị sai.

	- May mắn, có một bộ hàm để khắc phục vấn đề này.


7.1.2.10
	- Dưới đây là các hàm - hãy xem trong snippet sau:

		#include <arpa/inet.h>		/* UNIX/Linux */
		#include <Winsock2.>		/* MS Windows */

		uint32_t htonl (uint32_t hostlong);
		uint16_t htons (uint16_t hostshort);
		uint32_t ntohl (uint32_t netlong);
		uint16_t ntohs (uint16_t netshort);

	- Và đây là một danh sách đơn giản để làm cho tên hàm dễ hiểu:

		. h – host (endianess của máy tính)
		. n – network (order)
		. l – long;
		. s – short;
		. to – hmm... just 'to'

	- Vì vậy, hàm ntohs() chuyển đổi the network order 'short int' thành biểu diễn của host. Điều này chính xác là điều chúng ta cần. Let's use it.


7.1.2.11
	- Code sau khi fixed như sau:

		#include <stdio.h>
		#ifdef _MSC_VER
		#include <Winsock2.h>
		#pragma comment(lib, "ws2_32.lib")
		#else
		#include <netdb.h>
		#endif

		int
		main (void)
		{

		#ifdef _MSC_VER
		  WSADATA wsa;
		  WSAStartup (0x0202, &wsa);
		#endif
		  printf ("%d\n", ntohs (getservbyname ("http", "tcp")->s_port));

		#ifdef _MSC_VER
		  WSACleanup ();
		#endif
		  return 0;
		}

	- Và output của nó là:

		80

	- Phew, đây là thứ mà chúng ta đợi.


7.1.2.12
	- Có vẻ như chúng ta giờ đã có tất cả những gì chúng ta cần:

	- Địa chỉ IP của server;
	- Service number của server.

	- Chúng ta sử dụng chúng như thế nào?

	- Bạn có nhớ rằng BSD sockets được thiết kế như một phương pháp phổ quát để thiết lập giao tiếp giữa các process? Cấu trúc chính (tên là struct sockaddr) được sử dụng để lưu trữ endpoint addresses cũng là phổ quát - trông nó như sau:

		struct sockaddr {
		    unsigned short  sa_family;
		    char    sa_data[14];
		};

	- Field đầu tiên được sử dụng để lưu trữ the so address family (họ địa chỉ so) - đây là giá trị phản ánh socket's domain. Chúng ta sử dụng ký hiệu AF_INET để thiết lập nó.

	- Field thứ hai chỉ là một mảng 14 byte. Mỗi address family có thể sử dụng nó theo cách của mình.

	- Hãy xem INET sockets sử dụng nó như thế nào.

	- Cấu trúc sockaddr_in trông như sau:

		struct sockaddr_in {
		    short   sin_family;
		    unsigned short  sin_port;
		    struct  in_addr sin_addr;
		    char    sin_zero[8];
		};

	- Hãy tưởng tượng rằng cấu trúc này just put on 'struct sockaddr', và bạn sẽ thấy cách 14 byte được dành cho ba trường cuối cùng:
		
		. sin_port – một service number (Note: trường này sử dụng network order);
		
		. sin_addr – địa chỉ IP (đã thảo luận trước đó);
		
		. sin_zero – một phần chưa được sử dụng của sockaddr - tốt nhất nên zero this field trước khi sử dụng

	- Cấu trúc này chủ yếu được sử dụng bởi hàm connect(). Let's use it now.


7.1.2.13
	- Hàm connect() thực hiện những gì nó hứa hẹn - nó cố gắng kết nối socket của bạn đến service của địa chỉ IP và port number được chỉ định.

	- Hàm này cần ba tham số - hãy xem snippet sau:

		#include <sys/socket.h>		/* UNIX/Linux */
		#include <Winsock2.h>		/* MS Windows */
		int connect (int sockfd, struct sockaddr *addr, socklen_t addrlen);
		

		. sockfd – một socket đã được tạo thành công được dùng để thực hiện kết nối;
		
		. addr – một con trỏ đến một cấu trúc 'struct sockaddr' được khởi tạo đúng cách; nếu bạn sử dụng 'struct sockaddr_in' (of course you use it!), bạn sẽ cần sử dụng một typecast;
		
		. addrlen – kích thước của một cấu trúc sockaddr đầy đủ (sizeof(struct sockaddr) will do the job).

	- Hàm return 0 nếu thành công và -1 nếu ngược lại.


7.1.2.14
	- Giao thức HTTP là một trong những giao thức đơn giản nhất, nhưng vẫn quá phức tạp để thảo luận đầy đủ ở đây. Chúng tôi sẽ chỉ cho bạn cách để lấy một document gốc từ đó – nếu bạn muốn nhiều hơn, bạn sẽ cần kiểm tra một số dedicated protocol specifications (kĩ thuật giao thức chuyên dụng).

	- Một cuộc trò chuyện với HTTP server bao gồm requests - yêu cầu (được gửi bởi client) và responses (được gửi bởi server).

	- Để lấy root document từ một trang web có tên là www.site.com, client nên gửi yêu cầu đến server:

		GET / HTTP / 1.1 \ r \ n Host: www.site.com \ r \ n Connection:close \ r \ n

	- Yêu cầu này bao gồm:
	
		. Dòng chứa tên yêu cầu (GET) theo tên của source mà client muốn nhận; root document được chỉ định là một slash (/); dòng này cũng phải bao gồm phiên bản giao thức HTTP (HTTP/1.1), và phải kết thúc bằng ký tự \r\n; Note: tất cả các dòng phải kết thúc theo cùng một cách.
		
		. Dòng chứa tên trang web (www.site.com) preceded by tên tham số (Host:)
		
		. Dòng chứa tham số có tên Connection: cùng với giá trị của nó, 'close' buộc server đóng kết nối sau khi yêu cầu đầu tiên đã được served; điều này sẽ làm đơn giản code của client chúng ta;
		
		. Dòng trống là request's terminator (ký tự kết thúc yêu cầu).

	- Nếu yêu cầu là đúng, phản hồi của server sẽ bắt đầu bằng một header ít nhiều giống nhau - hãy nhìn snippet sau:

		HTTP / 1.1 200 OK Set - Cookie:startBAK = R3415742665;
		path = /;
		expires = Wed, 31 - Aug - 2016 11: 03: 41 GMT Date: Wed, 31 Aug 2016 09: 52: 30 GMT Content - Type:text /
		  html;
		charset = UTF - 8 Transfer - Encoding: chunked Connection: closeSet - Cookie:start =
		  R118743847;
		path = /;
		expires = Wed, 31 - Aug - 2016 10: 58: 46 GMT Server: Apache X - Powered - By: PHP / 5.3 .29 Expires: Thu, 19 Nov 1981 08: 52: 00 GMT Cache - Control: no - store, no - cache, must - revalidate, post - check = 0, pre - check = 0 Pragma: no - cache Link: <https:	//cppinstitute.org/wp-json/>;
		rel = "https://api.w.org/", <http:	//cppinstitute.org/>;
		rel = shortlink Set - Cookie:PHPSESSID = pulnneo0vt14fc8nm4s9hqmeq2;
		path = /Set - Cookie:wfvt_2047017364 = 57 c6a8de37ead;
		expires = Wed, 31 - Aug - 2016 10: 22:30 GMT;
		path = /;
		httponly Vary:Accept - Encoding

	- Điều quan trọng nhất là dòng đầu tiên – the 200 code nói rằng yêu cầu của chúng tôi đã được chấp nhận. Chúng tôi thực sự không muốn thấy 404 ở đây.

	- Các dòng tiếp theo mô tả các tham số đặc trưng cho máy chủ và phản hồi của nó. Chúng ta có thể skip this. The actual HTML document sẽ xuất hiện sau đó, được tách rời khỏi header bằng một dòng trống.


7.1.2.15
	- Giờ chúng ta đã sẵn sàng để trình bày code hoàn chỉnh của client. Dưới đây là phiên bản cho Unix/Linux - nhìn code sau:

		#include <stdio.h>
		#include <stdlib.h>
		#include <string.h>
		#include <errno.h>
		#include <netdb.h>
		#include <sys/socket.h>
		#include <arpa/inet.h>
		#include <unistd.h>
		#include <sys/ioctl.h>

		#define CALL(x) if(!(x) && fprintf(stderr, "'%s' failed (errno=%d)\n",#x,errno))exit(1)

		int
		main (int argc, char *argv[])
		{
		  if (argc != 2)
		    {
		      fprintf (stderr, "usage: %s site_addr\n", argv[0]);
		      return 0;
		    }

		  struct servent *sent;
		  CALL ((sent = getservbyname ("http", "tcp")) != NULL);
		  int port = sent->s_port;

		  struct protoent *pent;
		  CALL ((pent = getprotobyname ("tcp")) != NULL);

		  struct hostent *hent;
		  CALL ((hent = gethostbyname (argv[1])) != NULL);
		  printf ("%s -> %s\n", hent->h_name,
			  inet_ntoa (*((struct in_addr *) hent->h_addr)));

		  struct sockaddr_in addr;
		  addr.sin_family = AF_INET;
		  addr.sin_port = port;
		  addr.sin_addr = *((struct in_addr *) hent->h_addr);
		  memset (addr.sin_zero, 0, 8);

		  int sock;
		  CALL ((sock = socket (AF_INET, SOCK_STREAM, pent->p_proto)) > 0);

		  CALL ((connect (sock, (struct sockaddr *) &addr, sizeof (struct sockaddr)))
			== 0);

		  char buff[1024 + 1];
		  sprintf (buff, "GET / HTTP/1.1\r\nHost: %s\r\nConnection: close\r\n\r\n",
			   argv[1]);

		  CALL (write (sock, buff, strlen (buff)) == strlen (buff));

		  int readin = read (sock, buff, sizeof (buff) - 1);
		  while (readin > 0)
		    {
		      buff[readin] = '\0';
		      printf ("%s", buff);
		      readin = read (sock, buff, sizeof (buff) - 1);
		    }

		  close (sock);

		  return 0;
		}

	
		. line 11: macro CALL() được sử dụng để gọi các hàm – macro kiểm tra xem kết quả của hàm có giống như mong đợi hay không, và in thông điệp chẩn đoán nếu không; note: macro in biến errno, điều này không phải lúc nào cũng được khuyến khích, vì một số hàm (ví dụ, gethostbyname()) sử dụng biến error code riêng của chúng có tên là h_errno;
	
		. line 22: chúng ta tìm service number của HTTP service được truyền qua TCP; chúng ta lưu giá trị vào biến port (note: sử dụng network order ở đây)
	
		. line 26: chúng ta tìm protocol number của TCP;
	
		. line 29: chúng ta tìm địa chỉ IP của trang web được chỉ định trong đối số của chương trình;
	
		. line 34: chúng ta chuẩn bị một cấu trúc sockaddr_in;
	
		. line 41: chúng ta tạo một socket mới;
	
		. line 43: chúng ta thử kết nối đến HTTP server;
	
		. line 46: chúng ta chuẩn bị một request đầy đủ;
	
		. line 50: chúng ta gửi nó đến server (note: nó giống như việc ghi vào một file, phải không?)
	
		. line 52: vì server có thể gửi phản hồi của mình thành nhiều phần (cái này được gọi là chunked transmission - truyền tải phân đoạn), chúng ta cần đọc tất cả các phần, và miễn là nó thành công chúng ta đọc lại từ socket; server đóng kết nối sau khi gửi phần cuối cùng và chúng ta quan sát nó như là một end-of-file – đây là lý do tại sao chúng ta so sánh kết quả hàm read() trong khi chờ một giá trị less than zero;
	
		. line 56: chúng ta in reponse ra stdout part by part;
	
		. line 60: chúng ta đóng socket của mình.


7.1.2.16
	- Phiên bản cho MS Windows ở đây - hãy nhìn code:

		#include <stdio.h>
		#include <Winsock2.h>

		#pragma comment(lib, "ws2_32.lib")

		#define CALL(x) if(!(x) && fprintf(stderr, "'%s' failed (error=%d)\n",#x,WSAGetLastError()))exit(1)

		int main(int argc, char *argv[]) {
			
			if(argc != 2) {
				fprintf(stderr, "usage: %s site_addr\n", argv[0]);
				return 0;
			}

			WSADATA wsa;
			CALL( WSAStartup(MAKEWORD(2,2), &wsa) == 0 );
		  
			struct servent *sent;
			CALL( (sent = getservbyname("http", "tcp")) != NULL );
			int port = sent -> s_port;

			struct protoent *pent;
			CALL( (pent = getprotobyname("tcp")) != NULL );

			struct hostent *hent;
			CALL( (hent = gethostbyname(argv[1])) != NULL);	
			printf("%s -> %s\n", hent->h_name, inet_ntoa(*((struct in_addr *)hent->h_addr)));

			struct sockaddr_in addr;
			addr.sin_family = AF_INET;
			addr.sin_port = port;
			addr.sin_addr = *((struct in_addr *) hent->h_addr);
			memset(addr.sin_zero, 0, 8);

			int sock;
			CALL( (sock = socket(AF_INET, SOCK_STREAM, pent->p_proto)) > 0 );

			CALL( (connect(sock, (struct sockaddr *)&addr, sizeof(struct sockaddr))) == 0 );
			
			char buff[1024+1];
			sprintf(buff,"GET / HTTP/1.1\r\nHost: %s\r\nConnection: close\r\n\r\n", argv[1]);
			CALL ( send(sock, buff, strlen(buff), 0) == strlen(buff) );
			
			int readin = recv(sock, buff, sizeof(buff) - 1, 0);
			while(readin > 0) {
				buff[readin] = '\0';
				printf("%s", buff);
				readin = recv(sock, buff, sizeof(buff) - 1, 0);
			}

			closesocket(sock);
			WSACleanup();

			return 0;
		}

	
		. line 12: chúng ta sử dụng hàm native Winsock có tên WSAGetLastError() thay vì errno;
	
		. line 15: chúng ta khởi tạo thư viện Winsock
	
		. line 41: chúng ta sử dụng hàm send() thay vì write() (như chúng ta đã đề cập trước đó, socket trên MS Windows không phải là file); ba tham số đầu tiên đóng vai trò giống như write(), tham số cuối cùng chỉ định các options (zero means default).
	
		. line 44: chúng ta sử dụng recv() (receive) thay vì read(), giống như ở line 41;
	
		. line 51: chúng ta đóng socket của mình (chúng ta không thể sử dụng close() ở đây)

	- Test một trong các client (hoặc cả hai nếu bạn có thể) bằng cách trỏ nó đến một trong các trang web yêu thích của bạn. Nó có hoạt động không? We hope so.


7.1.3.1 Network sockets – TCP-based client-server
	- Bây giờ chúng ta sẽ viết một hệ thống hoàn chỉnh bao gồm một server và một client (tất nhiên có thể có nhiều client đang hoạt động). Server sẽ không phức tạp – nó chỉ sẽ tạo ra một giá trị integer ngẫu nhiên khi client yêu cầu.

	- Chúng ta giả sử rằng server chấp nhận các lệnh sau được gửi bởi bất kỳ client nào:

		. DRAW – server draw một number mới và gửi nó cho client;
		. QUIT – client không muốn nhận thêm number ngẫu nhiên nào nữa và muốn server ngắt kết nối;
		. EXIT – client muốn server to shut down.

	- Server trả lời client bằng ba phản hồi khác nhau:

		. OK nnnn – client's DRAW request đã được chấp nhận và server return the drawn value (nnnn)
		. OK – các lệnh EXIT hoặc QUIT của client đã được chấp nhận;
		. ERR – lệnh của client đã không được chấp nhận và đã bị bỏ qua.

	- Tất cả các lệnh và phản hồi đều kết thúc bằng chuỗi \r\n.

	- The flow diagram (Sơ đồ luồng) cho "giao thức" này được hiển thị trong hình:
		https://edube.org/learn/clp-c-programming-language-certified-professional/network-sockets-tcp-based-client-server


7.1.3.2
	- Bạn có thể đặt câu hỏi: việc viết một server có giống với việc viết một client không?

	No, it isn't. Nó hoàn toàn khác. Nó khó hơn không?

	No, nó không khó hơn xíu nào. Chắc chắn rằng nó đòi hỏi nhiều công sức hơn, nhưng không khó hơn.

	- Hãy xem biểu đồ được hiển thị trong hình ảnh:
		https://edube.org/learn/clp-c-programming-language-certified-professional/network-sockets-tcp-based-client-server-1

	- Phía bên phải hiển thị hành vi của client. Dễ ẹc – bạn đã quen thuộc với nó rồi.

	- Phía bên trái hiển thị execution path của server. Như bạn thấy, nó dài hơn đáng kể so với phía của client. Một server có nhiều thứ cần chuẩn bị trước khi nó sẵn sàng hoạt động.

	- Có vẻ phức tạp, nhưng thực sự không phải như vậy. Mọi thứ ở đây đều có logic và fairly straightforward. Hãy xem xét:
		
		1. Bước đầu tiên là tạo một socket – điều này được thực hiện theo cách tương tự như đối với client;
		
		2. Bước tiếp theo được thực hiện bởi một hàm có tên là bind(). Hãy xem nó như một loại yêu cầu mà server đưa ra cho OS. "Thưa OS," server nói, "Tôi muốn lắng nghe các client của mình bằng service number x - bạn có để tôi làm điều này không?". OS có thể đồng ý (nếu service chưa được liên kết với bất kỳ server nào khác), hoặc nó có thể không đồng ý (nếu service đã được liên kết, hoặc nếu đặc quyền của server quá yếu);
		
		3. Khi service đã được liên kết, server đưa ra yêu cầu khác. "Thưa OS, bạn có sẵn lòng lắng nghe các client của tôi không?" (đây là điều mà hàm listen() thực hiện – nó không thực sự lắng nghe, nhưng chỉ khởi đầu chức năng lắng nghe - là thứ mà sau đó được thực hiện bởi OS). Hãy nhớ rằng các kết nối đến từ các client thì in fact được nhận bởi OS, không phải bởi server chính nó, nhưng server có thể hỏi OS xem có kết nối nào đã đến không;
		
		4. Tiếp theo, server gọi hàm accept() và vào chế độ ngủ. Nó sẽ được OS đánh thức khi bất kỳ client nào muốn kết nối (tức là gọi hàm connect() tại bên client). Sự trở lại từ hàm accept() means that một kết nối mới đã đến và server hiện có khả năng trò chuyện với client đã kết nối. Server thực hiện điều này bằng cách sử dụng các hàm write() và read(), as required. Note: cặp accept()–connect() tạo thành point where server và client đồng bộ.

	- Easy? Okay, có lẽ không dễ như chúng ta muốn, nhưng chắc chắn là dễ dàng hơn so với trông như trong diagram.

	- Let’s discuss all the steps in a more formal way.


7.1.3.3
	- Hàm bind() binds the socket với service của địa chỉ cụ thể (bind: liên kết, ràng buộc) - hãy nhìn snippet sau:

		#include <sys/socket.h>		/* UNIX/Linux */
		#include <Winsock2.h>		/* MS Windows */
		int bind (int sockfd, struct sockaddr *addr, socklen_t addrlen);

	- Nó chấp nhận 3 đối số:
		
		1. Một socket để bind (trước đó đã được tạo bởi hàm socket()).
		
		2. A service's address được biểu thị bằng con trỏ đến struct sockaddr_in (note: vì bind() có thể hoạt động trên các domain khác với PF_INET, nó sử dụng một cấu trúc tổng quát hơn, tức là struct sockaddr).
		
		3. Độ dài của struct sockaddr_in (ví dụ, obtained from toán tử sizeof()).

	- Bạn có thể lo lắng một chút về một điều. What does a service address mean? The service/port number dường như ổn, nhưng liệu điều đó có nghĩa là server không biết địa chỉ IP của chính mình?

	- Vấn đề là hầu hết các máy tính đã kết nối mạng đều có nhiều hơn một địa chỉ IP. Ví dụ, máy tính cá nhân của bạn có khả năng có hai địa chỉ IP - một cho external network (mạng bên ngoài) (thường được gán bởi nhà cung cấp Internet) và một cho các internal connections, the localhost, luôn được chỉ định là 127.0.0.1.

	- Hàm bind() cần biết địa chỉ IP nào trong số những địa chỉ IP có sẵn mà nó nên sử dụng cho server của bạn, nhưng nếu bạn chắc chắn rằng bạn muốn liên kết server với tất cả chúng, bạn có thể sử dụng predefined symbol là INADDR_ANY - nó yêu cầu socket của bạn được liên kết với tất cả các IP.

	- Hàm bind() return:

		. 0 nếu thành công.
		. -1 nếu có lỗi (errno sẵn lòng hỗ trợ bạn, as usual).

	- Bạn không thể bind một địa chỉ đã được bind trước đó (không thể có nhiều hơn một server cho một service/port number).


7.1.3.3
	- Hàm listen() khởi tạo listening trên socket cụ thể - hãy nhìn snippet sau:

		#include <sys/socket.h>		/* UNIX/Linux */
		#include <Winsock2.h>		/* MS Windows */
		int listen (int sockfd, int backlog);

	- Nó chấp nhận hai đối số:
		
		1. Một socket để lắng nghe (trước đó đã được liên kết thành công bởi hàm bind()).
		
		2. Độ dài của queue mà OS sẽ giữ cho socket của bạn để tạm thời đóng băng các kết nối đến mà bạn không thể serve at the moment; bất kỳ kết nối nào vượt quá giới hạn đó sẽ bị từ chối; đừng mong đợi hệ thống đồng ý với exorbitant demands của bạn - độ dài có thể của queue không thực sự lớn; đừng nghĩ rằng nó là phương thuốc cho hiệu suất server thấp - không phải và sẽ không bao giờ là vậy.

	- Hàm listen() return:

		. 0 nếu thành công.
		. -1 nếu có lỗi (tất nhiên, bạn có thể dựa vào errno).


7.1.3.5
	- Hàm accept() đợi một connection to come và return the client's identity - hãy nhìn snippet:

		#include <sys/socket.h>		/* UNIX/Linux */
		#include <Winsock2.h>		/* MS Windows */
		int accept (int sockfd, struct sockaddr *addr, socklen_t * addrlen);

	- Nó chấp nhận ba đối số:
		
		1. Một socket with listening đã được activated thành công bởi hàm listen().
		
		2. Một pointer đến an empty 'struct sockaddr_in' (đừng quên typecast!) - cấu trúc này sẽ được hàm accept() điền thông tin về địa chỉ IP và port number của client.
		
		3. Một pointer đến một int, được set with độ dài của struct sockaddr_in trước khi gọi; hàm sẽ điền vào nó độ dài của filled structure (thực ra, cả hai giá trị bằng nhau, nhưng hãy nhớ rằng 'socket' machinery thì phổ biến hơn phần chúng tôi đang phân tích).

	- Phần thú vị nhất của hàm connect() là kết quả mà nó trả về:
		
		. -1 nếu có lỗi (không có phiền phức gì ở đây)
		
		. Một socket mới được tạo và được gán cho connection vừa được chấp nhận.

	- Trường hợp thứ hai ở trên cần thảo luận thêm.

	- Socket được truyền qua đối số đầu tiên được gọi là passive socket (socket chủ động) - nó có thể được sử dụng để lắng nghe các connection, nhưng không được sử dụng để giao tiếp với client. Để trò chuyện với client, bạn cần một socket riêng biệt - cái được returned bởi hàm (aka the connected socket). Nếu bạn muốn gửi điều gì đó đến client hoặc nhận điều gì đó từ nó, bạn phải sử dụng socket bạn nhận được từ accept(). Do đó, mỗi accepted connection đều có một socket riêng biệt của chính nó, tách biệt khỏi tất cả các connection khác đến cùng một passive socket.

	- Điều này mở ra một số additional, multi-threaded possibilities, nhưng chúng ta sẽ nói về chúng sau.

	- Vậy là có vẻ chúng ta đã sẵn sàng để triển khai drawing system của mình. Hãy bắt đầu bằng cách viết client's code.


7.1.3.6
	- Đây là phiên bản Unix/Linux của client's code:

		#include <stdio.h>
		#include <string.h>
		#include <stdlib.h>
		#include <unistd.h>
		#include <netdb.h>
		#include <sys/socket.h>

		#define CALL(x) if(counter++ && !(x))error(#x,__LINE__,counter)

		int counter = 2;

		void
		error (char *action, int line, int retc)
		{
		  fprintf (stderr, "'%s' in line #%d failed - client terminated\n", action,
			   line);
		  exit (retc);
		}

		int
		main (int argc, char *argv[])
		{
		  if (argc != 4)
		    {
		      fprintf (stderr, "usage %s server_addr service_no number_no\n",
			       argv[0]);
		      return 1;
		    }

		  int port = 0;
		  CALL (sscanf (argv[2], "%d", &port) == 1 && port >= 1 && port <= 65535);

		  int numno = 0;
		  CALL (sscanf (argv[3], "%d", &numno) == 1 && numno >= 0 && numno <= 10);

		  struct hostent *hent = NULL;
		  CALL ((hent = gethostbyname (argv[1])) != NULL);

		  struct protoent *pent;
		  CALL ((pent = getprotobyname ("tcp")) != NULL);

		  struct sockaddr_in addr;
		  addr.sin_family = AF_INET;
		  addr.sin_port = htons (port);
		  addr.sin_addr = *((struct in_addr *) hent->h_addr);
		  memset (addr.sin_zero, 0, 8);

		  int sock;
		  CALL ((sock = socket (AF_INET, SOCK_STREAM, pent->p_proto)) > 0);

		  CALL ((connect (sock, (struct sockaddr *) &addr, sizeof (struct sockaddr)))
			== 0);

		  char *draw_cmd = "DRAW\r\n", *quit_cmd = "QUIT\r\n";

		  if (numno == 0)
		    {
		      char *exitcmd = "EXIT\r\n";
		      CALL (write (sock, exitcmd, strlen (exitcmd)) == strlen (exitcmd));
		      close (sock);
		      return 0;
		    }

		  while (numno--)
		    {
		      CALL (write (sock, draw_cmd, strlen (draw_cmd)) == strlen (draw_cmd));
		      char buff[16];
		      int readin = 0;
		      CALL ((readin = read (sock, buff, sizeof (buff))) > 0);
		      buff[readin] = '\0';
		      printf ("%s\n", buff);
		      if (numno)
			sleep (1);
		    }

		  CALL (write (sock, quit_cmd, strlen (quit_cmd)) == strlen (quit_cmd));

		  close (sock);

		  return 0;
		}

	
		. line 8: chúng tôi sửa đổi macro CALL() cũ của mình một chút - chúng tôi thêm một biến đếm được tăng lên ở mỗi macro expansion; điều này giúp chúng tôi return các code lỗi khác nhau cho mỗi lý do possible; chúng tôi cũng output the number of the source line nơi mà lỗi xảy ra (chi tiết hơn sẽ được thảo luận trong phần thân hàm error() sớm);
	
		. line 12: hàm error() output thông báo lỗi ra stdout và exit chương trình với error code phù hợp;
	
		. line 23: client cần 3 đối số để bắt đầu công việc của mình: 
			. the server's address được đưa ra dưới dạng biểu tượng hoặc là một địa chỉ IP; 

			. the service number nơi server đang chờ connection của chúng ta; 

			. the number of numbers to draw; chúng tôi gán 1 ý nghĩa đặc biệt cho số 0 ở đây - nó gửi yêu cầu EXIT, buộc server dừng thực thi.
	
		. line 31: chúng tôi xem xét 'arg 2' để kiểm tra xem liệu port number có được chỉ định đúng cách không;
	
		. line 34: chúng tôi làm điều tương tự với 'arg 3' (numbers to draw)
	
		. line 37: chúng tôi apply 'arg 1' to gethostbyname() để tìm kiếm địa chỉ IP của server (note: hàm chấp nhận host address as an IP address được viết dưới dạng dấu chấm, cũng đơn giản chuyển đổi nó thành packed binary form)
	
		. line 40: chúng tôi tìm TCP number;
	
		. line 43: chúng tôi điền struct sockaddr_in với the complete service address (note hàm htons() ở line 37)
	
		. line 49: chúng tôi tạo socket;
	
		. line 51: chúng tôi cố gắng kết nối đến server của chúng tôi (server vẫn chưa tồn tại);
	
		. line 56: nếu 'arg 3' được chỉ định là 0, chúng tôi gửi yêu cầu EXIT đến server và kết thúc công việc của chúng tôi;
	
		. line 64: ngược lại, chúng tôi gửi as many DRAW commands as specified in 'arg 3';
	
		. line 69: chúng tôi đọc response của server và in nó ra stdout;
	
		. line 76: chúng tôi end connection bằng cách gửi lệnh QUIT đến server.
	
	- That’s all, folks.

	- Hãy viết lại code cho MS Windows - sẽ không mất nhiều thời gian.


7.1.3.7
	- Look, tất cả các chỉnh sửa đã được thực hiện rồi - nhìn code:

		#include <stdio.h>
		#include <Winsock2.h>

		#pragma comment(lib, "ws2_32.lib")

		#define CALL(x) if(counter++ && !(x))error(#x,__LINE__,counter)

		int counter = 2;

		void
		error (char *action, int line, int retc)
		{
		  fprintf (stderr, "'%s' in line #%d failed - client terminated\n", action,
			   line);
		  exit (retc);
		}

		int
		main (int argc, char *argv[])
		{
		  if (argc != 4)
		    {
		      fprintf (stderr, "usage %s server_addr service_no number_no\n",
			       argv[0]);
		      return 1;
		    }

		  WSADATA wsa;
		  CALL (WSAStartup (MAKEWORD (2, 2), &wsa) == 0);

		  int port = 0;
		  CALL (sscanf (argv[2], "%d", &port) == 1 && port >= 1 && port <= 65535);

		  int numno = 0;
		  CALL (sscanf (argv[3], "%d", &numno) == 1 && numno >= 0 && numno <= 10);

		  struct hostent *hent = NULL;
		  CALL ((hent = gethostbyname (argv[1])) != NULL);

		  struct protoent *pent;
		  CALL ((pent = getprotobyname ("tcp")) != NULL);

		  struct sockaddr_in addr;
		  addr.sin_family = AF_INET;
		  addr.sin_port = htons (port);
		  addr.sin_addr = *((struct in_addr *) hent->h_addr);
		  memset (addr.sin_zero, 0, 8);

		  int sock;
		  CALL ((sock = socket (AF_INET, SOCK_STREAM, pent->p_proto)) > 0);

		  CALL ((connect (sock, (struct sockaddr *) &addr, sizeof (struct sockaddr)))
			== 0);

		  char *draw_cmd = "DRAW\r\n", *quit_cmd = "QUIT\r\n";

		  if (numno == 0)
		    {
		      char *exitcmd = "EXIT\r\n";
		      CALL (send (sock, exitcmd, strlen (exitcmd), 0) == strlen (exitcmd));		/***/
		      closesocket (sock);								/***/
		      return 0;
		    }

		  while (numno--)
		    {
		      CALL (send (sock, draw_cmd, strlen (draw_cmd), 0) == strlen (draw_cmd));
		      char buff[16];
		      int readin = 0;
		      CALL ((readin = recv (sock, buff, sizeof (buff) - 1, 0)) > 0);			/***/
		      buff[readin] = '\0';
		      printf ("%s\n", buff);
		      if (numno)
			Sleep (1000);
		    }

		  CALL (send (sock, quit_cmd, strlen (quit_cmd), 0) == strlen (quit_cmd));		/***/

		  closesocket (sock);
		  WSACleanup ();

		  return 0;
		}


		. bên cạnh các bổ sung khác nhau và sử dụng #pragma, chúng tôi cũng đã thay thế tất cả các lời gọi write() bằng send(), và read() bằng recv()

		. chúng tôi cũng đã thay thế tất cả các hàm close() bằng lời gọi closesocket() - bạn biết lý do, phải không?

		. và chúng tôi cũng đã thêm Winsock initialization and clean-up - bạn có thể nhìn thấy chúng không?

	- Chúng ta không thể trì hoãn thêm được nữa. Đã đến lúc write the server.


7.1.3.8
	- Phiên bản Unix/Linux nằm ở đây - hãy xem code:

		#include <string.h>
		#include <stdio.h>
		#include <stdlib.h>
		#include <time.h>
		#include <unistd.h>
		#include <netdb.h>
		#include <sys/socket.h>
		#include <arpa/inet.h>
		#include <errno.h>

		#define CALL(x) if(counter++ && !(x))error(#x,__LINE__,counter)

		int counter = 2;

		void
		error (char *action, int line, int retc)
		{
		  fprintf (stderr, "'%s' in line #%d failed - server terminated (%d)\n",
			   action, line, errno);
		  exit (retc);
		}

		int
		main (int argc, char *argv[])
		{
		  if (argc != 2)
		    {
		      fprintf (stderr, "usage %s service_no\n", argv[0]);
		      return 1;
		    }

		  int port = 0;
		  CALL (sscanf (argv[1], "%d", &port) == 1 && port >= 1 && port <= 65535);

		  struct protoent *pent;
		  CALL ((pent = getprotobyname ("tcp")) != NULL);

		  int listen_sock;
		  CALL ((listen_sock = socket (AF_INET, SOCK_STREAM, pent->p_proto)) > 0);

		  struct sockaddr_in servaddr;
		  servaddr.sin_family = AF_INET;
		  servaddr.sin_port = htons (port);
		  servaddr.sin_addr.s_addr = htonl (INADDR_ANY);
		  memset (servaddr.sin_zero, 0, 8);

		  int opt_on = 1;
		  CALL (setsockopt
			(listen_sock, SOL_SOCKET, SO_REUSEADDR, &opt_on,
			 sizeof (opt_on)) == 0);

		  CALL (bind (listen_sock, (struct sockaddr *) &servaddr, sizeof (servaddr))
			== 0);

		  CALL (listen (listen_sock, 5) == 0);

		  for (;;)
		    {
		      struct sockaddr_in cliaddr;
		      int conn_sock = 0;
		      socklen_t cliaddrlen = sizeof (cliaddr);
		      CALL ((conn_sock =
			     accept (listen_sock, (struct sockaddr *) &cliaddr,
				     &cliaddrlen)) > 0);
		      printf ("client: %s:%d\n", inet_ntoa (cliaddr.sin_addr),
			      ntohs (cliaddr.sin_port));
		      srand (time (NULL));
		      for (;;)
			{
			  char buff[16],
			    *quit_cmd = "QUIT\r\n",
			    *exit_cmd = "EXIT\r\n",
			    *draw_cmd = "DRAW\r\n", *ok_ans = "OK\r\n", *err_ans = "ERR\r\n";
			  int readin = read (conn_sock, buff, sizeof (buff) - 1);
			  buff[readin] = '\0';
			  if (!strcmp (buff, draw_cmd))
			    {
			      char answer[100];
			      sprintf (answer, "OK %d\r\n", rand () % 10000);
			      write (conn_sock, answer, strlen (answer));
			      printf ("drawn\n");
			    }
			  else if (!strcmp (buff, quit_cmd))
			    {
			      write (conn_sock, ok_ans, strlen (ok_ans));
			      close (conn_sock);
			      printf ("quitted\n");
			      break;
			    }
			  else if (!strcmp (buff, exit_cmd))
			    {
			      write (conn_sock, ok_ans, strlen (ok_ans));
			      close (conn_sock);
			      close (listen_sock);
			      printf ("exited\n");
			      return 0;
			    }
			  else
			    {
			      write (conn_sock, err_ans, strlen (err_ans));
			      printf ("bad command: %s\n", buff);
			    }
			}
		    }
		}

		
		. line 26: máy chủ cần một đối số - một port number (chúng tôi giả định rằng nó sẽ lắng nghe tất cả các địa chỉ IP có sẵn trong hệ thống)
		
		. line 33: chúng tôi nhận đối số và kiểm tra nó;
		
		. line 39: chúng tôi tạo một socket sẽ được sử dụng để lắng nghe (đặt tên là listen_sock)
		
		. line 41: chúng tôi chuẩn bị struct sockaddr_in, được điền với server service address (note hằng số INADDR_ANY)
		
		. line 48: cần thêm một vài giải thích ở đây; hàm setsockopt() là một hàm sửa đổi settings của socket; chúng tôi sử dụng nó ở đây với một lý do quan trọng; in general, một passive socket vẫn hoạt động trong một khoảng thời gian sau khi đóng - nó có thể kích hoạt khởi động lại server mượt mà vì hàm bind() có thể thất bại (port vẫn được coi là đã được liên kết); việc setting the option 'REUSE_ADDR' turn that behavior off; các đối số chỉ định:
			
			. the socket mà setting của nó sẽ được sửa đổi;
			
			. the option level (the level được chỉ định as SOL_SOCKET liên quan đến các layer cao hơn của socket's implementation)
			
			. the option name;
			
			. a pointer đến option's value mong muốn;
			
			. độ dài của option's value;
		
		. line 52: chúng tôi thử liên kết socket của chúng tôi với port mong muốn và tất cả các địa chỉ IP có sẵn;
		
		. line 55: the listening bắt đầu ở đây - server của chúng tôi bây giờ hoạt động đầy đủ;
		
		. line 57: chúng tôi enter the main service loop;
		
		. line 62: chúng tôi đợi connection mới đến;
		
		. line 65: connection đến - chúng tôi in IP và port number của client, và socket mới được lưu trữ trong biến conn_sock;
		
		. line 68: chúng tôi enter the connected client service loop;
		
		. line 74: chúng tôi nhận lệnh của client;
		
		. line 76: chúng tôi react với lệnh DRAW: chúng tôi draw một giá trị mới và gửi nó trở lại cho client;
		
		. line 83: chúng tôi react với lệnh QUIT: chúng tôi gửi một positive response và đóng socket conn_sock;
		
		. line 90: chúng tôi react với lệnh EXIT: chúng tôi đóng các sockets và thoát khỏi chương trình;
		
		. line 100: chúng tôi rơi vào đây nếu một lệnh không hợp lệ đã được nhận.


7.1.3.9
	- Và bây giờ - như thường lệ - phiên bản MS Windows của code chúng ta:

		#include <stdio.h>
		#include <Winsock2.h>

		#pragma comment(lib, "ws2_32.lib")

		#define CALL(x) if(counter++ && !(x))error(#x,__LINE__,counter)

		int counter = 2;

		void
		error (char *action, int line, int retc)
		{
		  fprintf (stderr, "'%s' in line #%d failed - server terminated (%d)\n",
			   action, line, WSAGetLastError ());
		  exit (retc);
		}

		int
		main (int argc, char *argv[])
		{
		  if (argc != 2)
		    {
		      fprintf (stderr, "usage %s service_no\n", argv[0]);
		      return 1;
		    }

		  WSADATA wsa;
		  CALL (WSAStartup (MAKEWORD (2, 2), &wsa) == 0);

		  int port = 0;
		  CALL (sscanf (argv[1], "%d", &port) == 1 && port >= 1 && port <= 65535);

		  struct protoent *pent;
		  CALL ((pent = getprotobyname ("tcp")) != NULL);

		  int listen_sock;
		  CALL ((listen_sock = socket (AF_INET, SOCK_STREAM, pent->p_proto)) > 0);

		  struct sockaddr_in servaddr;
		  servaddr.sin_family = AF_INET;
		  servaddr.sin_port = htons (port);
		  servaddr.sin_addr.s_addr = htonl (INADDR_ANY);
		  memset (servaddr.sin_zero, 0, 8);

		  int opt_on = 1;
		  CALL (setsockopt (listen_sock, SOL_SOCKET, SO_REUSEADDR, (char *) &opt_on, sizeof (opt_on)) == 0);	/***/

		  CALL (bind (listen_sock, (struct sockaddr *) &servaddr, sizeof (servaddr))
			== 0);

		  CALL (listen (listen_sock, 5) == 0);

		  for (;;)
		    {
		      struct sockaddr_in cliaddr;
		      int conn_sock = 0;
		      int cliaddrlen = sizeof (cliaddr);			/***/
		      CALL ((conn_sock =
			     accept (listen_sock, (struct sockaddr *) &cliaddr,
				     &cliaddrlen)) > 0);
		      printf ("client: %s:%d\n", inet_ntoa (cliaddr.sin_addr),
			      ntohs (cliaddr.sin_port));
		      srand (time (NULL));
		      for (;;)
			{
			  char buff[16],
			    *quit_cmd = "QUIT\r\n",
			    *exit_cmd = "EXIT\r\n",
			    *draw_cmd = "DRAW\r\n", *ok_ans = "OK\r\n", *err_ans = "ERR\r\n";
			  int readin = recv (conn_sock, buff, sizeof (buff) - 1, 0);			/***/
			  buff[readin] = '\0';
			  if (!strcmp (buff, draw_cmd))
			    {
			      char answer[100];
			      sprintf (answer, "OK %d\r\n", rand () % 10000);
			      send (conn_sock, answer, strlen (answer), 0);			/***/
			      printf ("drawn\n");
			    }
			  else if (!strcmp (buff, quit_cmd))
			    {
			      send (conn_sock, ok_ans, strlen (ok_ans), 0);			/***/
			      closesocket (conn_sock);				/***/
			      printf ("quitted\n");
			      break;
			    }
			  else if (!strcmp (buff, exit_cmd))
			    {
			      send (conn_sock, ok_ans, strlen (ok_ans), 0);			/***/
			      closesocket (conn_sock);				/***/
			      closesocket (listen_sock);			/***/
			      WSACleanup ();
			      printf ("exited\n");
			      return 0;
			    }
			  else
			    {
			      send (conn_sock, err_ans, strlen (err_ans), 0);
			      printf ("bad command: %s\n", buff);
			    }
			}
		    }
		}

	- Chúng tôi nghĩ rằng không có gì trong code làm bạn bất ngờ.

	- Sửa đổi duy nhất cần chú ý là ở line 46 - phiên bản MS Windows của hàm setsockopt() sử dụng một kiểu khác cho đối số thứ ba (char * thay vì void *), vì vậy ở đây có typecast.

	- Chúng tôi khuyến khích bạn thực hiện thí nghiệm sau:
		
		. biên dịch code của client và server trên hệ thống của bạn;
		
		. mở 2 console windows;
		
		. trong window đầu tiên, khởi chạy server bằng cách chỉ định the service number of a high value (lớn hơn 10.000 nhưng không vượt quá 65.535 - điều này sẽ giảm thiểu rủi ro sử dụng một port number đã được liên kết trước đó), ví dụ:
		
			07.03.server 12345
		
		(sử dụng đúng tên file thực thi - phụ thuộc vào môi trường của bạn)
		
		. trong window thứ hai, khởi chạy client một vài lần, chỉ định địa chỉ IP của máy tính của bạn (cái mà được chỉ định bởi network, hoặc 127.0.0.1, hoặc đơn giản là localhost - hai từ latter là đồng nghĩa), port number của server và một number, ví dụ:

			07.03.client localhost 12345 1
			07.03.client localhost 12345 5
			07.03.client localhost 12345 0


7.1.3.10
	- Mở link để xem các ảnh minh họa:
		https://edube.org/learn/clp-c-programming-language-certified-professional/network-sockets-tcp-based-client-server-9


7.1.3.11
	- Mọi thứ dường như hoạt động tốt, nhưng server của chúng ta có một nhược điểm nghiêm trọng. Bạn có thể đoán đó là gì không?

	- Nhìn vào code và cố gắng trả lời câu hỏi sau: khi nhiều hơn một client muốn kết nối với server, điều gì sẽ xảy ra?

	- Yes, server sẽ không chấp nhận kết nối tiếp theo cho đến khi đóng kết nối trước đó.

	- Chúng tôi đã cố gắng làm điều đó - chúng tôi mở hai console windows cho hai client và chạy chúng (gần như) đồng thời. Console window của server nhìn như sau (xem link)
		https://edube.org/learn/clp-c-programming-language-certified-professional/network-sockets-tcp-based-client-server-10

	- Điều này chắc chắn không phải là cách mà một real server sẽ thực hiện. Hãy tưởng tượng xem Internet sẽ trông như thế nào nếu tất cả các server WWW hoạt động giống như server của chúng tôi. No, chúng tôi không muốn điều đó đâu.

	- Vậy... chúng ta có thể làm gì? Làm thế nào để quản lý vấn đề này? Liệu chúng ta thậm chí có thể quản lý được nó không?

	- Of course we can!

	- Bạn có nhớ chúng tôi nói với bạn về thread không? Có thể chạy một thread riêng biệt cho mỗi connecting user được không?

	- Yes, it's possible.

	- Và chúng ta có thể thực hiện điều này theo 2 cách: sử dụng Pthreads và sử dụng MS Windows threads. It ain’t rocket science. And we’ll prove it.


7.1.3.12
	- Dưới đây là multi-theaded version của server của chúng tôi - hãy nhìn code:

		#include <string.h>
		#include <stdio.h>
		#include <stdlib.h>
		#include <time.h>
		#include <unistd.h>
		#include <netdb.h>
		#include <sys/socket.h>
		#include <arpa/inet.h>
		#include <errno.h>
		#include <pthread.h>
		#define CALL(x) if(counter++ && !(x))error(#x,__LINE__,counter)
		int counter = 2;
		char *quit_cmd = "QUIT\r\n", *exit_cmd = "EXIT\r\n", *draw_cmd = "DRAW\r\n",
		  *ok_ans = "OK\r\n", *err_ans = "ERR\r\n";
		int listen_sock = 0;
		void
		error (char *action, int line, int retc)
		{
		  fprintf (stderr, "'%s' in line #%d failed - server terminated (%d)\n",
			   action, line, errno);
		  exit (retc);
		}

		void *
		serve_client (void *data)
		{
		  int conn_sock = *((int *) data);
		  char buff[16];
		  pthread_t self = pthread_self ();
		  srand (self);
		  for (;;)
		    {
		      int readin = read (conn_sock, buff, sizeof (buff) - 1);
		      buff[readin] = '\0';
		      if (!strcmp (buff, draw_cmd))
			{
			  char answer[100];
			  sprintf (answer, "OK %d\r\n", rand () % 10000);
			  write (conn_sock, answer, strlen (answer));
			  printf ("thread %lxd: drawn\n", self);
			}
		      else if (!strcmp (buff, quit_cmd))
			{
			  write (conn_sock, ok_ans, strlen (ok_ans));
			  close (conn_sock);
			  printf ("thread %lxd: quitted\n", self);
			  break;
			}
		      else if (!strcmp (buff, exit_cmd))
			{
			  write (conn_sock, ok_ans, strlen (ok_ans));
			  close (conn_sock);
			  close (listen_sock);
			  printf ("thread %lxd: exited\n", self);
			  exit (0);
			}
		      else
			{
			  write (conn_sock, err_ans, strlen (err_ans));
			  printf ("thread %lxd: bad command: %s\n", self, buff);
			}
		    }
		  return NULL;
		}

		int
		main (int argc, char *argv[])
		{
		  if (argc != 2)
		    {
		      fprintf (stderr, "usage %s service_no\n", argv[0]);
		      return 1;
		    }
		  int port = 0;
		  CALL (sscanf (argv[1], "%d", &port) == 1 && port >= 1 && port <= 65535);
		  struct protoent *pent;
		  CALL ((pent = getprotobyname ("tcp")) != NULL);
		  CALL ((listen_sock = socket (AF_INET, SOCK_STREAM, pent->p_proto)) > 0);
		  struct sockaddr_in servaddr;
		  servaddr.sin_family = AF_INET;
		  servaddr.sin_port = htons (port);
		  servaddr.sin_addr.s_addr = htonl (INADDR_ANY);
		  memset (servaddr.sin_zero, 0, 8);
		  int opt_on = 1;
		  CALL (setsockopt
			(listen_sock, SOL_SOCKET, SO_REUSEADDR, &opt_on,
			 sizeof (opt_on)) == 0);
		  CALL (bind (listen_sock, (struct sockaddr *) &servaddr, sizeof (servaddr))
			== 0);
		  CALL (listen (listen_sock, 5) == 0);
		  for (;;)
		    {
		      struct sockaddr_in cliaddr;
		      int conn_sock = 0;
		      socklen_t cliaddrlen = sizeof (cliaddr);
		      for (;;)
			{
			  CALL ((conn_sock =
				 accept (listen_sock, (struct sockaddr *) &cliaddr,
					 &cliaddrlen)) > 0);
			  printf ("client: %s:%d\n", inet_ntoa (cliaddr.sin_addr),
				  ntohs (cliaddr.sin_port));
			  int *newsock = malloc (sizeof (int));
			  pthread_t newthrd;
			  *newsock = conn_sock;
			  pthread_create (&newthrd, NULL, serve_client, newsock);
			}
		    }
		}

	- In fact, hầu hết những gì bạn thấy trong code đã quen thuộc với bạn, vì vậy lời giải thích của chúng tôi sẽ rất đơn giản:

		. line 24: đây là text của thread chịu trách nhiệm serve một connected client; như bạn có thể thấy, chúng tôi chỉ di chuyển một phần của code trước đó vào một hàm và trang trí nó với một header cho phép hàm được sử dụng như là một Pthread (note tham số và cách nó được typecasted để có được một socket từ nó)
	
		. line 106: khi một connection mới được thiết lập thành công, một connection socket được chuyển đến một thread mới được khởi chạy, trong khi listening socket ngay lập tức trở lại công việc chính của nó.


7.1.3.13
	- Cùng một concept nhưng theo kiểu MS Windows - hãy nhìn vào code sau:

		#include <stdio.h>
		#include <Winsock2.h>
		#pragma comment(lib, "ws2_32.lib")
		#define CALL(x) if(counter++ && !(x))error(#x,__LINE__,counter)
		int counter = 2;
		char *quit_cmd = "QUIT\r\n",
		  *exit_cmd = "EXIT\r\n",
		  *draw_cmd = "DRAW\r\n", *ok_ans = "OK\r\n", *err_ans = "ERR\r\n";
		int listen_sock = 0;
		void
		error (char *action, int line, int retc)
		{
		  fprintf (stderr, "'%s' in line #%d failed - server terminated (%d)\n",
			   action, line, WSAGetLastError ());
		  exit (retc);
		}

		DWORD WINAPI
		serve_client (LPVOID * data)
		{
		  int conn_sock = *((int *) data);
		  char buff[16];
		  DWORD self = GetCurrentThreadId ();
		  srand (self);
		  for (;;)
		    {
		      int readin = recv (conn_sock, buff, sizeof (buff) - 1, 0);
		      buff[readin] = '\0';
		      if (!strcmp (buff, draw_cmd))
			{
			  char answer[100];
			  sprintf (answer, "OK %d\r\n", rand () % 10000);
			  send (conn_sock, answer, strlen (answer), 0);
			  printf ("thread %xd: drawn\n", self);
			}
		      else if (!strcmp (buff, quit_cmd))
			{
			  send (conn_sock, ok_ans, strlen (ok_ans), 0);
			  closesocket (conn_sock);
			  printf ("thread %xd: quitted\n", self);
			  break;
			}
		      else if (!strcmp (buff, exit_cmd))
			{
			  send (conn_sock, ok_ans, strlen (ok_ans), 0);
			  closesocket (conn_sock);
			  WSACleanup ();
			  printf ("thread %xd: exited\n", self);
			  exit (0);
			}
		      else
			{
			  write (conn_sock, err_ans, strlen (err_ans));
			  printf ("thread %xd: bad command: %s\n", self, buff);
			}
		    }
		  return 0;
		}

		int
		main (int argc, char *argv[])
		{
		  if (argc != 2)
		    {
		      fprintf (stderr, "usage %s service_no\n", argv[0]);
		      return 1;
		    }
		  WSADATA wsa;
		  CALL (WSAStartup (MAKEWORD (2, 2), &wsa) == 0);
		  int port = 0;
		  CALL (sscanf (argv[1], "%d", &port) == 1 && port >= 1 && port <= 65535);
		  struct protoent *pent;
		  CALL ((pent = getprotobyname ("tcp")) != NULL);
		  CALL ((listen_sock = socket (AF_INET, SOCK_STREAM, pent->p_proto)) > 0);
		  struct sockaddr_in servaddr;
		  servaddr.sin_family = AF_INET;
		  servaddr.sin_port = htons (port);
		  servaddr.sin_addr.s_addr = htonl (INADDR_ANY);
		  memset (servaddr.sin_zero, 0, 8);
		  int opt_on = 1;
		  CALL (setsockopt
			(listen_sock, SOL_SOCKET, SO_REUSEADDR, (char *) &opt_on,
			 sizeof (opt_on)) == 0);
		  CALL (bind (listen_sock, (struct sockaddr *) &servaddr, sizeof (servaddr))
			== 0);
		  CALL (listen (listen_sock, 5) == 0);
		  for (;;)
		    {
		      struct sockaddr_in cliaddr;
		      int conn_sock = 0;
		      int cliaddrlen = sizeof (cliaddr);
		      for (;;)
			{
			  CALL ((conn_sock =
				 accept (listen_sock, (struct sockaddr *) &cliaddr,
					 &cliaddrlen)) > 0);
			  printf ("client: %s:%d\n", inet_ntoa (cliaddr.sin_addr),
				  ntohs (cliaddr.sin_port));
			  int *newsock = malloc (sizeof (int));
			  *newsock = conn_sock;
			  CreateThread (NULL, 0, serve_client, newsock, 0, NULL);
			}
		    }
		}

		
		. line 18: thread của chúng tôi bắt đầu ở đây...
		
		. line 101: ... và chúng tôi khởi chạy nó ở đây.
	
	- It couldn’t be simpler, could it?


7.1.3.14
	- Dưới đây là ảnh chụp màn hình cho thấy server mới của chúng tôi (phiên bản MS Windows) đang hoạt động.
		https://edube.org/learn/clp-c-programming-language-certified-professional/network-sockets-tcp-based-client-server-13

	- Bạn có thể nhận thấy sự khác biệt không?

	- Các phản hồi được gửi đến hai client khác nhau được mixed - điều này có nghĩa là server có khả năng phục vụ nhiều hơn một client cùng một lúc, và các thread đang hoạt động (hầu hết) song song để đáp ứng tất cả các incoming client.

	- Client luôn đúng - đây là chính sách mới của server chúng tôi.


7.1.4.1 Network sockets – peer-to-peer communication
	- Hãy nhìn vào diagram.
		https://edube.org/learn/clp-c-programming-language-certified-professional/network-sockets-peer-to-peer-communication

	- Như bạn có thể thấy, hình ảnh gần như symmetrical (đối xứng). The preparation phase là giống nhau ở cả hai bên. Khi so với connection-oriented transmission, chỉ có một ngoại lệ - các hàm read() và write() không còn hoạt động nữa. Bạn phải sử dụng các hàm chuyên biệt cho connectionless transmission:
		
		. sendto() để gửi một phần dữ liệu đến bên thứ hai (hàm này là một dạng tổng quát của hàm send() đã đề cập trước đó).
		
		. recvfrom() để nhận một phần dữ liệu được gửi bởi bên kia (hàm này là một dạng tổng quát của hàm recv()).

	- Let’s talk about them now.


7.1.4.2
	- Hàm sendto() có dạng như sau - hãy nhìn snippet sau:

		#include <sys/socket.h>		/* UNIX/Linux */
		#include <Winsock2.h>		/* MS Windows */

		ssize_t sendto (int sockfd,
				void *buf,
				size_t len,
				int flags, struct sockaddr *dest_addr, socklen_t addrlen);

	- Hàm sendto() gửi dữ liệu đến địa chỉ được chỉ định. Hàm chờ đến khi tất cả dữ liệu được gửi đi, nhưng việc gửi thành công không đồng nghĩa với việc có bất kỳ ai đó đã nhận được tin nhắn.

	- Hàm sử dụng các tham số sau:
		
		. Một socket để truyền dữ liệu; note: socket không cần phải được connected, nhưng phải được bound.
		
		. Một pointer đến bộ đệm nơi dữ liệu cần được gửi được lưu trữ.
		
		. Độ dài của dữ liệu.
		
		. Một bit mask chỉ định set of option được sử dụng trong quá trình gửi.
		
		. Một pointer đến cấu trúc sockaddr (actually: sockaddr_in) chứa địa chỉ của socket của bên thứ hai (địa chỉ IP và port number).
		
		. Độ dài của cấu trúc (sizeof(struct sockaddr_in) is good at this point).

	- Các possible flag được hàm chấp nhận bao gồm:
		
		. MSG_CONFIRM – được sử dụng bởi một số giao thức (như ARP, được sử dụng để gán địa chỉ IP cho địa chỉ MAC) để đảm bảo rằng bên thứ hai còn sống.
		
		. MSG_DONTROUTE – được sử dụng bởi một số giao thức (như DHCP, được sử dụng trong các mạng cục bộ để cấp phát động địa chỉ IP) để chỉ ra rằng dữ liệu không nên được routed (định tuyến) ra khỏi mạng cục bộ.
		
		. MSG_DONTWAIT – kích hoạt hàm theo cách asynchronous.
		
		. MSG_MORE – nói rằng sẽ có thêm dữ liệu để gửi; gợi ý rằng OS nên thu thập tất cả dữ liệu và gửi nó sau khi có lời gọi sendto() đầu tiên mà không có flags xảy ra.

	- Hàm return:
		
		. Số byte được gửi thành công.
		
		. -1 nếu có lỗi (errno được set để phản ánh lý do).

	- Invocation sau:

		send(sockfd, buf, len, flags);
	
	tương đương với:

		sendto(sockfd, buf, len, flags, NULL, 0);
	
	nhưng chỉ có thể được sử dụng cho connection-oriented transmission, vì không có khả năng chỉ định địa chỉ của bên thứ hai.


7.1.4.3
	- The sendto() function's header có dạng như sau:

		#include <sys/socket.h>		/* UNIX/Linux */
		#include <Winsock2.h>		/* MS Windows */

		ssize_t recvfrom (int sockfd,
				  void *buf,
				  size_t len,
				  int flags, struct sockaddr *dest_addr, socklen_t * addrlen);

	- Hàm recvfrom() nhận dữ liệu từ bất kỳ địa chỉ nào. Hàm đợi đến khi có bất kỳ dữ liệu nào được nhận.

	- Hàm sử dụng các tham số sau:
		
		. Một socket sẽ được sử dụng để nhận dữ liệu; note: socket không cần phải được connected, nhưng phải được bound.
		
		. Một pointer đến bộ đệm nơi dữ liệu nhận được sẽ được lưu trữ.
		
		. Kích thước của bộ đệm (độ dài tối đa của dữ liệu nhận được).
		
		. Một bit mask chỉ định set of options được sử dụng trong quá trình receiving.
		
		. Một pointer đến cấu trúc sockaddr (actually: sockaddr_in), nơi hàm lưu trữ địa chỉ của socket của bên thứ hai, hoặc NULL nếu bạn không muốn nhận địa chỉ.
		
		. Độ dài của cái cấu trúc mà được điền bởi hàm; nó phải được set to sizeof(struct sockaddr_in) trước khi gọi.

	- Các possible flags được hàm chấp nhận bao gồm:
		
		. MSG_DONTWAIT – gọi hàm theo cách asynchronous.
		
		. MSG_PEEK – hàm trả về dữ liệu đã nhận, nhưng không loại bỏ nó khỏi các bộ đệm hệ thống; do đó, lời gọi tiếp theo sẽ cung cấp cùng một dữ liệu.

	- Hàm return:
		
		. Số lượng received bytes thành công.
		
		. -1 nếu có lỗi (errno được set as usual).

	- Invocation sau:

		recv(sockfd, buf, len, flags);
	
	tương đương với:

		recvfrom(sockfd, buf, len, flags, NULL, NULL);


7.1.4.4
	- Bạn thích bóng bàn không?

	- Chúng tôi sẽ viết một đoạn code để chơi bóng bàn.

	- Okay, đó sẽ là một trò chơi bóng bàn rất cụ thể - bóng bàn mà không có quả bóng.

	- Hai bản sao của code sẽ đánh vào một con số thay vì một quả bóng. Họ sẽ không sử dụng vợt - thay vào đó, họ sẽ sử dụng sockets và connectionless transmission dựa trên UDP. Luật chơi của chúng tôi rất đơn giản - nếu bạn nhận được một con số, bạn phải trả lại con số đó, nhân đôi. Người chơi thứ hai cũng hành động theo cách tương tự.

	- Trò chơi kết thúc khi con số vượt quá chiều dài được đặt trước.

	- Một điều nữa. Chúng tôi sẽ quyết định ai là người serve đầu tiên. Chúng tôi cũng sẽ chọn con số đầu tiên mà không cần tung đồng xu. Nice.

	- Trò chơi sẽ trông như sau (giả sử chiều dài con số tối đa là 4), xem ảnh qua link sau:
		https://edube.org/learn/clp-c-programming-language-certified-professional/network-sockets-peer-to-peer-communication-3

	- Chương trình sẽ chấp nhận 3 hoặc 4 đối số. The one with 4 đối số sẽ serve con số đầu tiên.

	- Các đối số có ý nghĩa như sau:
	
		1. Port number riêng của đối tác - port on which chương trình đợi dữ liệu được gửi từ đối tác;
	
		2. Địa chỉ của đối tác - dạng IP hoặc biểu tượng;
	
		3. Port number của đối tác - port to which chương trình gửi dữ liệu của mình đến;
	
		4. (optional) một con số đầu tiên để serve.

	- Note: đối tác nhận bóng phải bắt đầu trước - chương trình không có cơ chế bảo vệ chống lại một chuỗi bắt đầu sai.


7.1.4.5
	- Để cho chương trình có thể hoạt động với các số rất lớn, chúng ta sẽ lưu chúng dưới dạng string. Điều này có nghĩa là chúng ta sẽ cần một hàm đặc biệt để nhân một số cho hai.

	- Dưới đây là một hàm như vậy:

		char *
		times2 (char *val)
		{
		  int len = strlen (val);
		  char *newval = malloc (len + 2);
		  newval[len + 1] = '\0';
		  int i, cy = 0;
		  for (i = len - 1; i >= 0; i--)
		    {
		      char c = 2 * (val[i] - '0') + cy;
		      cy = c >= 10;
		      c %= 10;
		      newval[i + 1] = '0' + c;
		    }
		  if (cy)
		    newval[0] = '1';
		  else
		    memmove (newval, newval + 1, len + 1);
		  return newval;
		}

	- Hàm nhận một string chứa numeric value viết dưới dạng các chữ số, từ trái sang phải, giống như một số thực tế. Mỗi lần lặp của vòng for lấy một chữ số (bắt đầu từ cuối số), chuyển đổi ký tự thành giá trị nhị phân, nhân nó cho hai, kiểm tra xem phép nhân có tạo ra hai chữ số không, và nếu có, lưu trữ một trong biến cy. Note rằng hàm cấp phát một phần của bộ nhớ cho kết quả - một byte nhiều hơn so với kích thước của đối số, cộng với không gian cho '\0'.

	- Nếu kết quả ngắn hơn, toàn bộ kết quả sẽ được di chuyển sang bên trái để tiêu thụ byte dư thừa ở đầu string.

	- Do hàm cấp phát bộ nhớ, người gọi hàm phải giải phóng nó.


7.1.4.6
	- Dưới đây là phần còn lại của đoạn code:

		#include <stdio.h>
		#include <string.h>
		#include <stdlib.h>
		#include <errno.h>
		#include <netdb.h>
		#include <sys/socket.h>
		#include <unistd.h>
		#define CALL(x) if(counter++ && !(x))error(#x,__LINE__,counter)
		#define MAX_SIZE 4
		int counter = 2;
		void
		error (char *action, int line, int retc)
		{
		  fprintf (stderr, "'%s' in line #%d failed - terminated (%d)\n", action,
			   line, errno);
		  exit (retc);
		}

		char *
		times2 (char *val)
		{
		  int len = strlen (val);
		  char *newval = malloc (len + 2);
		  newval[len + 1] = '\0';
		  int i, cy = 0;
		  for (i = len - 1; i >= 0; i--)
		    {
		      char c = 2 * (val[i] - '0') + cy;
		      cy = c >= 10;
		      c %= 10;
		      newval[i + 1] = '0' + c;
		    }
		  if (cy)
		    newval[0] = '1';
		  else
		    memmove (newval, newval + 1, len + 1);
		  return newval;
		}

		int
		main (int argc, char *argv[])
		{
		  if (argc != 4 && argc != 5)
		    {
		      fprintf (stderr, "usage: %s my_port peer_addr peer_port [value]\n",
			       argv[0]);
		      return 1;
		    }
		  int myport = 0;
		  CALL (sscanf (argv[1], "%d", &myport) == 1 && myport >= 1
			&& myport <= 65535);
		  int peerport = 0;
		  CALL (sscanf (argv[3], "%d", &peerport) == 1 && peerport >= 1
			&& peerport <= 65535);
		  unsigned first = 0;
		  if (argc == 5)
		    CALL (sscanf (argv[4], "%u", &first) == 1 && first >= 1
			  && first <= (1 << 16));
		  struct hostent *hent = NULL;
		  CALL ((hent = gethostbyname (argv[2])) != NULL);
		  struct protoent *pent;
		  CALL ((pent = getprotobyname ("udp")) != NULL);
		  struct sockaddr_in myaddr;
		  myaddr.sin_family = AF_INET;
		  myaddr.sin_port = htons (myport);
		  myaddr.sin_addr.s_addr = htonl (INADDR_ANY);
		  memset (myaddr.sin_zero, 0, 8);
		  struct sockaddr_in peeraddr;
		  peeraddr.sin_family = AF_INET;
		  peeraddr.sin_port = htons (peerport);
		  peeraddr.sin_addr = *((struct in_addr *) hent->h_addr);
		  memset (peeraddr.sin_zero, 0, 8);
		  int mysock;
		  CALL ((mysock = socket (AF_INET, SOCK_DGRAM, pent->p_proto)) > 0);
		  CALL (bind (mysock, (struct sockaddr *) &myaddr, sizeof (myaddr)) == 0);
		  char *buf = NULL, *resp = NULL;
		  for (;;)
		    {
		      if (first)
			{
			  resp = malloc (16);
			  sprintf (resp, "%u", first);
			  first = 0;
			}
		      else
			{
			  buf = malloc (MAX_SIZE + 1);
			  int recvd = 0;
			  CALL (recvd = recvfrom (mysock, buf, MAX_SIZE, 0, NULL, NULL));
			  buf[recvd] = '\0';
			  printf ("rcvd: %s\n", buf);
			  if (recvd >= MAX_SIZE)
			    break;
			  sleep (1);
			  resp = times2 (buf);
			  free (buf);
			}
		      int tosend = strlen (resp);
		      CALL (sendto
			    (mysock, resp, tosend, 0, (struct sockaddr *) &peeraddr,
			     sizeof (peeraddr)));
		      printf ("sent: %s\n", resp);
		      free (resp);
		      if (tosend >= MAX_SIZE)
			break;
		    }
		  close (mysock);
		  return 0;
		}

	- Hầu hết phần code này chắc chắn sẽ quen thuộc.

	- Các phần thú vị nhất là:
		
		. line 62: lưu ý rằng chúng ta cần một protocol number cho UDP, không phải TCP;
		
		. line 63: chúng ta chuẩn bị một cấu trúc sockaddr_in cho port của chúng ta; Note: chúng ta sẽ bind nó với tất cả các địa chỉ IP cục bộ (giống như chúng ta đã làm ở server)
		
		. line 68: chúng ta chuẩn bị một cấu trúc sockaddr_in cho port của đối tác;
		
		. line 74: chúng ta configure một socket dựa trên datagram transmission, không phải stream transmission;
		
		. line 81: nếu chúng ta là server (bên có cú đánh đầu tiên), chúng ta chuẩn bị dữ liệu để gửi đi;
		
		. line 87: nếu không, chúng ta cố gắng nhận một "quả bóng" từ đối tác;
		
		. line 99: chúng ta trả lại "quả bóng".


7.1.4.7
	- Và cuối cùng, the same code, nhưng cho nền tảng MS Windows:

		#include <stdio.h>
		#include <Winsock2.h>
		#pragma comment(lib, "ws2_32.lib")
		#define CALL(x) if(counter++ && !(x))error(#x,__LINE__,counter)
		#define MAX_SIZE 6
		int counter = 2;
		void
		error (char *action, int line, int retc)
		{
		  fprintf (stderr, "'%s' in line #%d failed - terminated (%d)\n", action,
			   line, errno);
		  exit (retc);
		}

		char *
		times2 (char *val)
		{
		  int len = strlen (val);
		  char *newval = malloc (len + 2);
		  newval[len + 1] = '\0';
		  int i, cy = 0;
		  for (i = len - 1; i >= 0; i--)
		    {
		      char c = 2 * (val[i] - '0') + cy;
		      cy = c >= 10;
		      c %= 10;
		      newval[i + 1] = '0' + c;
		    }
		  if (cy)
		    newval[0] = '1';
		  else
		    memmove (newval, newval + 1, len + 1);
		  return newval;
		}

		int
		main (int argc, char *argv[])
		{
		  if (argc != 4 && argc != 5)
		    {
		      fprintf (stderr, "usage: %s my_port peer_addr peer_port [value]\n",
			       argv[0]);
		      return 1;
		    }
		  WSADATA wsa;
		  CALL (WSAStartup (MAKEWORD (2, 2), &wsa) == 0);
		  int myport = 0;
		  CALL (sscanf (argv[1], "%d", &myport) == 1 && myport >= 1
			&& myport <= 65535);
		  int peerport = 0;
		  CALL (sscanf (argv[3], "%d", &peerport) == 1 && peerport >= 1
			&& peerport <= 65535);
		  unsigned first = 0;
		  if (argc == 5)
		    CALL (sscanf (argv[4], "%u", &first) == 1 && first >= 1
			  && first <= (1 << 16));
		  struct hostent *hent = NULL;
		  CALL ((hent = gethostbyname (argv[2])) != NULL);
		  struct protoent *pent;
		  CALL ((pent = getprotobyname ("udp")) != NULL);
		  struct sockaddr_in myaddr;
		  myaddr.sin_family = AF_INET;
		  myaddr.sin_port = htons (myport);
		  myaddr.sin_addr.s_addr = htonl (INADDR_ANY);
		  memset (myaddr.sin_zero, 0, 8);
		  struct sockaddr_in peeraddr;
		  peeraddr.sin_family = AF_INET;
		  peeraddr.sin_port = htons (peerport);
		  peeraddr.sin_addr = *((struct in_addr *) hent->h_addr);
		  memset (peeraddr.sin_zero, 0, 8);
		  int mysock;
		  CALL ((mysock = socket (AF_INET, SOCK_DGRAM, pent->p_proto)) > 0);
		  CALL (bind (mysock, (struct sockaddr *) &myaddr, sizeof (myaddr)) == 0);
		  char *buf = NULL, *resp = NULL;
		  for (;;)
		    {
		      if (first)
			{
			  resp = malloc (16);
			  sprintf (resp, "%u", first);
			  first = 0;
			}
		      else
			{
			  buf = malloc (MAX_SIZE + 1);
			  int recvd = 0;
			CALL (recvd = recvfrom (mysock, buf, MAX_SIZE, 0, NULL, NULL);
				buf[recvd] = '\0';
				printf ("rcvd: %s\n", buf);
				if (recvd >= MAX_SIZE) break;
				Sleep (1000); resp = times2 (buf); free (buf);}
			      int tosend = strlen (resp);
			      CALL (sendto
				    (mysock, resp, tosend, 0, (struct sockaddr *) &peeraddr,
				     sizeof (peeraddr))); printf ("sent: %s\n", resp);
			      free (resp); if (tosend >= MAX_SIZE) break;}
			      closesocket (mysock); WSACleanup (); return 0;}


7.1.4.8
	- Bạn có muốn xem các người chơi của chúng ta in play không? Compile code và chạy nó trong hai cửa sổ console khác nhau. Bắt đầu hai bản sao của chương trình của chúng ta, trỏ đến địa chỉ của bên đối tác, ví dụ, sử dụng các lệnh sau (MS Windows version):

		. Trong cửa sổ console đầu tiên:
			07.04.peerw 30001 localhost 30002
		
		. Trong cửa sổ console thứ hai:
			07.04.peerw 30002 localhost 30001 1
		
	- Trò chơi được chơi trên máy tính của chúng tôi trông giống như sau - nhìn vào những hình ảnh:
		https://edube.org/learn/clp-c-programming-language-certified-professional/network-sockets-peer-to-peer-communication-7

	- What an exciting game it was!

	- Như bạn có thể thấy, chúng tôi bắt đầu từ 1. Hãy thử code của chúng tôi với bất kỳ giá trị dương nào khác. Bạn cũng có thể thay đổi giá trị của biểu tượng MAX_SIZE và loại bỏ lời gọi hàm sleep()/Sleep() - trò chơi có thể trở nên vui hơn sau đó.


7.1.5.1 Network sockets – POSIX
	- Trước đó, chúng ta đã đề cập đến việc POSIX đã thay đổi một số thứ trong các socket BSD. Hãy nói về hai thứ trong đống thứ đó:

		. POSIX giới thiệu một hàm rất mạnh, tên là getaddrinfo(), có thể hoạt động như một sự thay thế cho nhiều hàm đơn giản hơn derived from BSD sockets, như gethostbyname(), getprotobyname(), ...; hàm cũng có thể hoạt động với địa chỉ IP6;
	
		. something else introduced by POSIX là inet_ntop(), một sự thay thế trực tiếp cho inet_ntoa() nhưng linh hoạt hơn (nó cũng hiểu địa chỉ IP6); hàm cũng có một sibling dưới dạng hàm inet_pton().

	- Hàm getaddrinfo() sử dụng một cấu trúc riêng biệt có tên là addrinfo - nhìn code:

		struct addrinfo
		{
		  int ai_flags;
		  int ai_family;
		  int ai_socktype;
		  int ai_protocol;
		  socklen_t ai_addrlen;
		  struct sockaddr *ai_addr;
		  char *ai_canonname;
		  struct addinfo *ai_next;
		};

	- Cấu trúc này được thiết kế để:

		. form a request cho hàm (sau đó, cấu trúc này được sử dụng as 'hints')
		
		. build a response từ hàm (response có thể chứa nhiều hơn một cấu trúc của this type; các cấu trúc này được linked vào one-way list sử dụng trường ai_next)
	
	- The field's usage có thể phụ thuộc vào cách cấu trúc này được sử dụng:
	
		. ai_flags – có thể chỉ định các additional options (chỉ được sử dụng trong 'hints')
	
		. ai_family – chỉ định address family (ví dụ: AF_INET hoặc AF_INET6)
	
		. ai_socktype – chỉ định socket type (ví dụ: SOCK_STREAM hoặc SOCK_DGRAM)
	
		. ai_protocol – chỉ định protocol number;
	
		. ai_addrlen – chiều dài của cấu trúc sockaddr được truyền vào hàm, hoặc chiều dài của cấu trúc sockaddr được built bởi hàm;
	
		. ai_addr – một pointer đến 'struct sockaddr' được đề cập ở trên;
	
		. ai_canonname – một pointer đến canonical name (tên chính xác), tên chính thức của host (vì có thể có nhiều hơn một tên được gán cho một địa chỉ IP cụ thể, một cái tên trong những tên này luôn được đánh dấu là canonical); hàm có thể tìm thấy tên chính xác nếu nó chưa biết;
	
		. ai_next – một liên kết đến cấu trúc addrinfo tiếp theo, hoặc NULL.


7.1.5.2
	- Hàm getaddrinfo() là một hàm kết hợp nhiều chức năng khác nhau dưới chỉ một cái tên. Nó cần một hàm hỗ trợ có tên là freeaddrinfo(), mà bạn phải sử dụng để safely loại bỏ các kết quả được tạo ra bởi getaddrinfo().

	- Các hàm có dạng như sau:

		#include <sys/socket.h>		/* UNIX/Linux */
		#include <netdb.h>

		#include <Winsock2.h>		/* MS Windows */

		int getaddrinfo (char *node,
				 char *service,
				 struct addrinfo *hints, struct addrinfo **res);
		void freeaddrinfo (struct addrinfo *res);

	- The getaddrinfo() accepts bốn đối số:
	
		1. node – tên của host cần được tìm kiếm, hoặc NULL nếu tên host không quan trọng;
	
		2. service – tên của service chính thức, hoặc NULL nếu tên service không quan trọng; note: tối đa một trong hai đối số này có thể là NULL;
	
		3. hints – con trỏ đến struct 'addrinfo' chỉ định hành động cần thực hiện;
	
		4. res – con trỏ đến con trỏ nơi getaddrinfo() sẽ lưu địa chỉ của response được tạo ra.

	- Hàm return zero khi thành công, hoặc một error code (có một hàm tên là gai_strerror() có thể chuyển đổi code thành một message có thể đọc được cho con người).

	- Do getaddrinfo() có thể return nhiều hơn một cấu trúc addrinfo, và thậm chí một cấu trúc đơn lẻ cũng có thể chứa con trỏ đến các phần bộ nhớ mới được cấp phát, bạn không nên tự free the response - thay vào đó, bạn nên sử dụng hàm freeaddrinfo().


7.1.5.3
	- Hàm inet_ntop() nhận 4 đối số và chuyển đổi địa chỉ IP từ 'src' thành một string được đặt trong 'dst'.
	
		. Một address family code (AF_INET hoặc AF_INET6)
	
		. Một con trỏ đến internal representation của địa chỉ IP; kiểu 'void *' cho phép hàm chấp nhận các loại socket khác nhau;
	
		. Một con trỏ đến bộ đệm nơi string representation của 'src' address sẽ được lưu trữ;
	
		. Chiều dài của bộ đệm 'dst'.

	- Hàm return:
	
		. Con trỏ dst khi thành công;
	
		. NULL khi có lỗi (biến errno cũng được set).


7.1.5.4
	- Để minh họa cách hàm getaddrinfo() hoạt động, chúng tôi đã viết lại socket program đầu tiên của chúng tôi - HTTP client.

	- Dưới đây là nửa đầu tiên của code:

		#include <stdio.h>

		#ifdef _MSC_VER
		#include <Winsock2.h>
		#include <Ws2tcpip.h>
		#pragma comment(lib, "ws2_32.lib")
		#else
		#include <arpa/inet.h>
		#include <netdb.h>
		#include <stdlib.h>
		#include <string.h>
		#include <errno.h>
		#include <netdb.h>
		#include <sys/socket.h>
		#include <arpa/inet.h>
		#include <unistd.h>
		#include <sys/ioctl.h>
		#endif

		#ifdef _MSC_VER
		#define CALL(x) if(!(x) && fprintf(stderr, "'%s' failed (error=%d)\n",#x,WSAGetLastError()))Exit(1)
		#else
		#define CALL(x) if(!(x) && fprintf(stderr, "'%s' failed (errno=%d)\n",#x,errno))Exit(1)
		#endif

		void
		Exit (int retc)
		{
		#ifdef _MSC_VER
		  WSACleanup ();
		#endif
		  exit (retc);
		}

		int
		Write (int h, char *buf, int siz)
		{
		#ifdef _MSC_VER
		  return send (h, buf, siz, 0);
		#else
		  return write (h, buf, siz);
		#endif
		}

		int
		Read (int h, char *buf, int siz)
		{
		#ifdef _MSC_VER
		  return recv (h, buf, siz, 0);
		#else
		  return read (h, buf, siz);
		#endif
		}

		int
		Close (int h)
		{
		#ifdef _MSC_VER
		  return closesocket (h);
		#else
		  return close (h);
		#endif
		}

	- Note: Chương trình chứa một số '#if' directives - chúng cho phép code được compiled bởi Unix/Linux and MS Windows compiler. Chúng tôi cũng đã thêm một số wrapper-functions that ẩn đi việc implementation phụ thuộc vào nền tảng dưới một giao diện thống nhất.

	- Hãy nhìn vào code và quyết định liệu những sửa đổi có làm cho code trở nên rõ ràng hơn không:
		
		. line 26: một wrapper cho hàm exit() - cung cấp chức năng bổ sung khi compiled cho MS Windows;
		
		. line 35: một wrapper cho hàm write() - thay thế nó bằng một send() invocation khi compiled cho MS Windows;
		
		. line 45: một wrapper cho hàm read() - thay thế nó bằng một recv() invocation khi compiled cho MS Windows;
		
		. line 55: một wrapper cho hàm close() - cung cấp chức năng bổ sung khi compiled cho MS Windows.

	- Hàm return:

		. con trỏ dst khi thành công;
		. NULL khi có lỗi (biến errno cũng được set).


7.1.5.5
	- Phần quan trọng nhất của code nằm ở đây - hãy xem code:

		#include <stdio.h>

		#ifdef _MSC_VER
		#include <Winsock2.h>
		#include <Ws2tcpip.h>
		#pragma comment(lib, "ws2_32.lib")
		#else
		#include <arpa/inet.h>
		#include <netdb.h>
		#include <stdlib.h>
		#include <string.h>
		#include <errno.h>
		#include <netdb.h>
		#include <sys/socket.h>
		#include <arpa/inet.h>
		#include <unistd.h>
		#include <sys/ioctl.h>
		#endif

		#ifdef _MSC_VER
		#define CALL(x) if(!(x) && fprintf(stderr, "'%s' failed (error=%d)\n",#x,WSAGetLastError()))Exit(1)
		#else
		#define CALL(x) if(!(x) && fprintf(stderr, "'%s' failed (errno=%d)\n",#x,errno))Exit(1)
		#endif

		void
		Exit (int retc)
		{
		#ifdef _MSC_VER
		  WSACleanup ();
		#endif
		  exit (retc);
		}

		int
		Write (int h, char *buf, int siz)
		{
		#ifdef _MSC_VER
		  return send (h, buf, siz, 0);
		#else
		  return write (h, buf, siz);
		#endif
		}

		int
		Read (int h, char *buf, int siz)
		{
		#ifdef _MSC_VER
		  return recv (h, buf, siz, 0);
		#else
		  return read (h, buf, siz);
		#endif
		}

		int
		Close (int h)
		{
		#ifdef _MSC_VER
		  return closesocket (h);
		#else
		  return close (h);
		#endif
		}

		int
		main (int argc, char *argv[])
		{
		  if (argc != 2)
		    {
		      fprintf (stderr, "usage: %s site_addr\n", argv[0]);
		      return 0;
		    }

		#ifdef _MSC_VER
		  WSADATA wsa;
		  WSAStartup (MAKEWORD (2, 2), &wsa);
		#endif

		  struct addrinfo hints, *info;

		  memset (&hints, 0, sizeof (hints));
		  hints.ai_family = AF_INET;
		  hints.ai_socktype = SOCK_STREAM;
		  hints.ai_flags = AI_CANONNAME;

		  CALL (getaddrinfo (argv[1], "http", &hints, &info) == 0);

		  char str[32];
		  inet_ntop (info->ai_family,
			     &((struct sockaddr_in *) info->ai_addr)->sin_addr, str,
			     sizeof (str) - 1);
		  printf ("%s -> %s\n", info->ai_canonname, str);

		  struct sockaddr_in addr = *((struct sockaddr_in *) info->ai_addr);

		  int sock;
		  CALL ((sock = socket (AF_INET, SOCK_STREAM, info->ai_protocol)) > 0);

		  CALL ((connect (sock, (struct sockaddr *) &addr, sizeof (struct sockaddr)))
			== 0);

		  char buff[1024 + 1];
		  sprintf (buff, "GET / HTTP/1.1\r\nHost: %s\r\nConnection: close\r\n\r\n",
			   argv[1]);

		  CALL (Write (sock, buff, strlen (buff)) == strlen (buff));

		  int readin = Read (sock, buff, sizeof (buff) - 1);
		  while (readin > 0)
		    {
		      buff[readin] = '\0';
		      printf ("%s", buff);
		      readin = Read (sock, buff, sizeof (buff) - 1);
		    }

		  Close (sock);
		  freeaddrinfo (info);
		#ifdef _MSC_VER
		  WSACleanup ();
		#endif
		  return 0;
		}

	- Note: chương trình chứa một số '#if' directives – chúng cho phép code được biên dịch bởi trình biên dịch Unix/Linux và MS Windows. Chúng tôi cũng đã thêm một số wrapper – các hàm ẩn đi implementation phụ thuộc vào nền tảng dưới một giao diện thống nhất.

	- Hãy nhìn vào code và quyết định liệu những sửa đổi có làm cho code trở nên rõ ràng hơn không:
		
		. line 79: chúng ta bắt đầu chuẩn bị hints cho getaddrinfo() invocation;
		
		. line 82: chúng ta muốn sử dụng địa chỉ IP4;
		
		. line 83: chúng ta cần một stream socket;
		
		. line 84: chúng ta muốn hàm tìm một canonical name (nếu có);
		
		. line 86: keep your fingers crossed bởi vì hàm getaddrinfo() đã được kích hoạt! Chúng ta truyền the host name (argv[1]) và service name (http) vào nó, hy vọng rằng nó sẽ return một số dữ liệu hữu ích;
		
		. line 89: chúng ta sử dụng IP4 address returned in the first info structure và sử dụng hàm inet_ntop() để in nó ra stdout;
		
		. line 94: chúng ta get the sockaddr_in structure mà getaddrinfo() đã chuẩn bị cho chúng ta; chúng ta không cần phải tự mình xây dựng nó – what a relief!
		
		. line 97: đây là cơ hội cuối cùng để sử dụng dữ liệu được derived from hàm getaddrinfo();
		
		. line 117: chúng ta free bộ nhớ mà có thể đã được cấp phát bởi hàm getaddrinfo().
	
	- Liệu code có hoạt động giống như HTTP client đầu tiên của chúng ta không? Compile it and try!



~ Module 8 ~

	In this module, you will learn about:
		
		. const variables vs. volatile variables;
		
		. goto – why and why not, advantages, disadvantages and limitations;
		
		. long (non-local) jumps: setjmp() and longjmp();
		
		. static array indices, designated initializers, compound literals, variable-length arrays, flexible array members, restrict keyword;
		
		. sequence points: why ++/-- may sometimes make you crazy?;
		
		. the asm keyword
		
		. portability issues and undefined behaviours


8.1.1.2 Miscellaneous – const, restrict and volatile
	(Đa dạng - const, restrict và volatile)

	- According to the C language standards, bất kỳ entity nào được khai báo trong chương trình đều có thể được qualified, tức là được chỉ định sở hữu một số tính năng đặc biệt. Để qualify một entity, 1, 2 hoặc 3 trong số các qualify sau phải được sử dụng trong khai báo của entity:

		const
		restrict
		volatile

	- Note: tất cả đều là keywords.

	- Each of the qualifiers này thay đổi cách entity hoạt động, và tạo thành một yêu cầu gửi đến compiler. The compiler treats the qualified name một cách đặc biệt, và điều này có thể ảnh hưởng đến cách compiler xây dựng executable code.

	- Để tránh bị cáo buộc thiên vị các qualifiers cụ thể, chúng tôi sẽ thảo luận về chúng theo thứ tự bảng chữ cái.

	- Trường hợp sử dụng đơn giản nhất của 'const' qualifier là khi nó xuất hiện trong khai báo của non-pointer variable:

		const int n = 0;

	- Nếu một biến đã được khai báo là const (we’ll use the term const-qualified variable), điều này có nghĩa là bạn chỉ có thể gán giá trị cho nó bằng cách sử dụng một initializer (bộ khởi tạo). Bạn sẽ không thể gán lại hoặc sửa đổi biến trực tiếp.

	- Nói cách khác, biến này sẽ hoạt động giống như một hằng số (theo nghĩa toán học).

	- Đoạn mã sau đây là không chính xác:

		#include <stdio.h>

		int main(void) {
		    const int n = 2;
		    printf("%d\n", n);
		    n++;					// khúc này sai
		    printf("%d\n", n);
		    return 0;
		}

		- Compiler sẽ hiển thị một thông báo lỗi ở line 6 - chúng ta đã thử tăng giá trị của const-qualified variable ở đây, điều này là không hợp lệ.


8.1.1.3
	- Từ khóa const không phải là toàn năng. Nó không thể bảo vệ giá trị của một biến mọi nơi và mọi lúc. Ví dụ, nếu bạn nhận một con trỏ đến một const-qualified variable, bạn có thể sửa đổi giá trị của nó một cách gián tiếp.

	- Chúng tôi đã show it here:

		#include <stdio.h>

		int main(void) {
		    const int n = 2;
		    int *p = &n;		// highlighted line
		    printf("%d\n", n);
		    (*p)++;
		    printf("%d\n", n);
		    return 0;
		}

	- Thử nghiệm trên dẫn chúng ta đến kết luận sau đây: từ khóa const không phải là một chiếc khiên bất diệt bảo vệ một biến khỏi những mối đe dọa đến từ bên ngoài. Nó an toàn hơn nhiều khi treat nó như một từ đồng nghĩa với thuật ngữ read-only. Điều này có nghĩa là:
		
		. bạn không được sửa đổi một const-qualified variable một cách trực tiếp;
		
		. một factor khác có thể có khả năng sửa đổi nó một cách gián tiếp.

	- Note: một compiler nên phát ra một thông báo cảnh báo cho line 5, vì việc nhận một con trỏ đến const-qualified variable thì luôn luôn có chút đáng ngờ.

	- Bây giờ là thời điểm tốt để đặt câu hỏi sau đây cho bạn - các tổ hợp (mảng, cấu trúc) có thể được const-qualified không?

	- Yes, chúng có thể:

		#include <stdio.h>

		int main(void) {
		    const int t[2] = {1, 2};
		    t[0] = 1; *(t + 0) = 1;		// highlighted line
		    printf("%d\n", t[0]);
		    printf("%d\n", t[1]);
		    return 0;
		}

	- Một const-qualified array hoạt động như thể tất cả các phần tử của nó đều là const-qualified.

	- Lines 5 và 6 sẽ gây ra compilation error.


8.1.1.4
	- Structured variables cũng có thể là const-qualified:

		#include <stdio.h>

		int main(void) {
		    const struct { int x, y; } a = {1, 2}, b = {3, 4};
		    a.x++; a.y--; b = a;		// highlighted line
		    printf("%d %d\n", a.x, a.y);
		    printf("%d %d\n", b.x, b.y);
		    return 0;
		}

	- Một const-qualified structure hoạt động như thể tất cả các trường của nó và cấu trúc, as a whole, đều là const-qualified.

	- Lines 5, 6 và 7 sẽ gây ra lỗi biên dịch.

	- Vị trí của từ khóa const không quan trọng khi bạn khai báo một biến không phải là con trỏ.

	- Hãy nhìn vào code sau:

		#include <stdio.h>

		int
		main (void)
		{
		  const int a = 1;
		  int const b = 2;
		  printf ("%d\n", a + b);
		  return 0;
		}

	- Cả hai khai báo đều hợp lệ và chương trình hoàn toàn chính xác.


8.1.1.5
	- Vị trí của từ khóa const là rất quan trọng khi bạn khai báo một biến con trỏ.

	- Hãy cẩn thận xem xét ví dụ sau:

		#include <stdio.h>

		int main(void) {
		    int a = 1, b = 2;
		    int const *p = &a;
		    a++;
		    (*p)++;				// highlighted line
		    p = &b;
		    return 0;
		}

	- Biến p là một con trỏ đến const-qualified int (để ý vị trí của từ khóa const và vị trí của const-qualified phrase).

	- Điều này có nghĩa là:
		
		. bạn không được phép sửa đổi giá trị mà p đang trỏ tới (it is actually const-qualified)
		
		. bạn được phép sửa đổi chính con trỏ p (it isn’t const-qualified)

	- Line 7 (và chỉ có line này) sẽ gây ra lỗi biên dịch.

	- Note: cả hai dạng khai báo này là tương đương nhau:

		int const *p = &a;
		const int *p = &a;

	- Chúng tôi đã thay đổi ví dụ một chút - chúng tôi đã di chuyển từ khóa const một chút sang bên phải - bạn có thể thấy không?:

		#include <stdio.h>

		int main(void) {
		    int a = 1, b = 2;
		    int *const p = &a;
		    a++;
		    (*p)++;
		    p = &b;			// highlighted line
		    return 0;
		}

	- Bây giờ biến p là một const-qualified pointer to an int (một lần nữa, hãy để ý vị trí của từ khóa và the const-qualified phrase).

	- Điều này có nghĩa là:
		
		. bạn được phép sửa đổi giá trị mà p đang trỏ tới (it isn’t const-qualified)
		
		. bạn không được phép sửa đổi chính con trỏ p (it is const-qualified)

	- Line 8 (và chỉ có line này) sẽ gây ra lỗi biên dịch.


8.1.1.6
	- Cả hai trường hợp này có thể được kết hợp lại với nhau, giống như sau:

		#include <stdio.h>

		int main(void) {
		    int a = 1, b = 2;
		    int const * const p = &a;
		    a++;
		    (*p)++; p = &b;			// highlighted line
		    return 0;
		}

	- Biến p hiện tại là một const-qualified pointer trỏ đến một const-qualified int (phải hiểu này mới đọc tiếp nha).

	- Điều này có nghĩa là:
		
		. bạn không được phép sửa đổi giá trị mà p đang trỏ tới;
		
		. bạn không được phép sửa đổi chính con trỏ p;

	- Lines 7 và 8 sẽ gây ra lỗi biên dịch.

	- Bây giờ chúng tôi sẽ kiểm tra xem liệu bạn có thể thấy sự khác biệt không - hãy xem code sau:

		#include <stdio.h>

		int
		main (void)
		{
		  char str[] = "string";
		  char const *s1 = str;
		  char *const s2 = str;
		  char const *const s3 = str;
		  s1[1] = 'S';
		  s2[2] = 'S';
		  s3[3] = 'S';
		  printf ("%s %s %s\n", s1, s2, s3);
		  s1 = "1";
		  s2 = "2";
		  s3 = "3";
		  printf ("%s %s %s\n", s1, s2, s3);
		  return 0;
		}

	- Chúng tôi muốn bạn đoán (hoặc chính xác hơn là xác định) cái nào trong số các phép gán được đặt trong lines 7 to 12 là sai.

	- Một số trong số chúng chắc chắn là sai - hãy phân tích chính xác.

	- Are you ready?


8.1.1.7
	- Chúng tôi đã mark tất cả các lines không chính xác bằng màu đỏ (xem trên edube):

		#include <stdio.h>

		int main(void) {
		    char str[] = "string";
		    char const *s1 = str;
		    char * const s2 = str;
		    char const * const s3 = str;
		    s1[1] = 'S';				// marked line
		    s2[2] = 'S';
		    s3[3] = 'S';				// marked line
		    printf("%s %s %s\n", s1, s2, s3);
		    s1 = "1";
		    s2 = "2"; s3 = "3";			// marked line
		    printf("%s %s %s\n", s1, s2, s3);
		    return 0;
		}
	
	- Is your answer the same? We hope so.

	- Hãy bình luận về nó:
		
		. s1 là một con trỏ đến một const-qualified char - bạn có thể sửa đổi chính con trỏ (line 12), nhưng bạn không được phép sửa đổi dữ liệu nó trỏ tới (line 8);
		
		. s2 là một const-qualified pointer đến một ký tự - bạn có thể sửa đổi dữ liệu được trỏ tới (line 9), nhưng bạn không được phép thay đổi chính con trỏ (line 13);
		
		. s3 là một const-qualified pointer đến một const-qualified char - bạn không được phép sửa đổi cả con trỏ và dữ liệu nó trỏ tới.

	- Note: việc loại bỏ tất cả các từ khóa const khỏi code sẽ làm cho nó đúng, nhưng đừng nghĩ rằng đó là cách giải quyết chung cho những vấn đề với các const-qualified variable.

	- Từ khóa const thường được sử dụng trong khai báo tham số của một hàm để chỉ định các tham số (chủ yếu là con trỏ) không thể thay đổi.

	- Hãy xem xét prototype của hàm sau:

		int atoi(const char *);
 
	- Hàm atoi() (từ <stdlib.h>) cố gắng chuyển đổi một string các chữ số được trỏ tới bởi đối số thành một giá trị int. Cách mà tham số được khai báo rõ ràng cho thấy rằng string sẽ không được sửa đổi theo bất kỳ cách nào.

	- So sánh với prototype của hàm sau:

		int mkstemp(char*);
	
	- Hàm mkstemp() (cũng từ <stdlib.h>) tạo một file với một unique (temporary) name. Tên được tạo ra được lưu trữ trong string được trỏ tới bởi đối số. Như bạn có thể thấy, khai báo không chứa từ khóa const.


8.1.1.8
	- Để tổng kết cuộc thảo luận của chúng ta về các const qualifier, chúng ta cần nói thêm hai điều lưu ý bổ sung.

	1. Không nên gán các 'non const-qualified pointers' with các con trỏ trỏ đến các biến const-qualified.

		. Đoạn code sau sẽ gây ra một cảnh báo từ trình biên dịch ở line 5:

			#include <stdio.h>

			int main(void) {
			    int const v = 1;
			    const *p = &v;			// marked line
			    printf("%d\n", *p);
			    return 0;
			}

	2. Một con trỏ đến 'non const-qualified variable' có thể được gán cho các con trỏ const-qualified.

		. Đoạn code này không gây lỗi hoặc cảnh báo:

			#include <stdio.h>

			int main(void) {
			    int v = 1;
			    const int *p = &v;
			    printf("%d\n", *p);
			    return 0;
			}


8.1.1.9
	- The 'restrict' qualifier có thể chỉ xuất hiện trong phần khai báo của biến con trỏ:

		int *restrict ptr = &v;

	- Vị trí của từ khóa rất quan trọng – nó phải được đặt ngay trước tên được khai báo.

	- Từ khóa actually là một lời hứa. Programmer using qualifier hứa với compiler rằng entity được trỏ tới bởi con trỏ, hoặc bởi biểu thức sử dụng con trỏ (như 'ptr + 2' hoặc 'ptr[2]'), không thể được truy cập bằng bất kỳ cách nào khác. Biết điều này, compiler có thể tạo ra code hiệu quả hơn. Nhưng có một lưu ý: nếu bạn phá vỡ lời hứa của mình, code có thể hoạt động không đúng. Đừng hứa mà không giữ lời.

	- Note: từ khóa restrict được giới thiệu trong tiêu chuẩn C99.

	- Xem xét ví dụ sau đây (một cách hơi học thuật):

		void
		inc (int *v, int *x, int *y, int *z)
		{
		  *v += *x;
		  *v += *y;
		  *v += *z;
		}

	- Hàm inc() lấy giá trị từ dereferenced pointers (lấy từ các đối số thứ hai, thứ ba và thứ tư) và cộng chúng vào giá trị được lưu trong biến được trỏ tới bởi đối số đầu tiên.

	- Easy? Not quite. Nhìn kỹ này: compiler phải xem xét khả năng rằng tất cả bốn con trỏ đều trỏ đến cùng một biến, giống như này:

		inc(&a, &a, &a, &a);

	- Do đó, code mà compiler xây dựng phải được xây dựng theo cách sau:

		. fetch *v
		. add *a
		. store *v
		. fetch *v
		. add *b
		. store *v
		. fetch *v
		. add *c
		. store *v

	- Note: hai cái mệnh đề 'store *v' và 'fetch *v'; các mệnh đề không thể bị bỏ qua nếu chúng ta muốn bảo vệ giá trị tổng cộng hiện tại trong tất cả các trường hợp có thể; nó có thể được bỏ qua nếu chúng ta chắc chắn rằng *v chỉ định một giá trị khác *a, *b hoặc *c (nói cách khác, điều kiện v != a && v != b && v != c phải được đáp ứng).

	- Việc khai báo tham số v dưới dạng một restricted pointer có nghĩa là chúng ta hoàn toàn chắc chắn rằng điều kiện đã được đáp ứng.


8.1.1.10
	- Hãy nhìn vào đoạn code đã được sửa đổi sau:

		void
		inc (int *restrict v, int *x, int *y, int *z) *
		v += *x;
		*v += *y;
		*v += *z;
		}

	- Compiler có thể rút ngắn code thực thi bằng cách đảm bảo rằng *v không liên quan gì đến bất kỳ entity nào khác (more precisely, nó độc lập với bất kỳ entity nào khác). Code đã biên dịch có thể trông như sau:

		. fetch *v
		. add *a
		. add *b
		. add *c
		. store *v

	- Code bấy giờ ngắn hơn và hiệu quả hơn.

	- Note: việc gọi một hàm bằng cách sử dụng các restricted parameters cần phải chú ý để đảm bảo rằng các con trỏ hiện tại, những con trỏ mà được truyền qua các đối số, hoạt động theo cách mong muốn.

	- Syntactically, từ khóa volatile rất gần gũi với 'const' qualifier – take a look:

		volatile int n;
		volatile int *p1;
		int *volatile p2;
		int volatile * volatile p3;

	- Semantically (Về mặt ngữ nghĩa), không có mối quan hệ họ hàng giữa chúng.

	- Vậy làm thế nào để hiểu rằng bất kỳ biến nào đó là 'volatile'? Liệu nó có thể biến mất đột ngột mà không để lại dấu vết?

	Almost like this. Really.

	- The volatile variable là một biến có giá trị có thể thay đổi ngoài sự kiểm soát của chúng ta và mà không cần sự can thiệp của chúng ta.

	- Liệu điều này có thể xảy ra không? Có tồn tại những biến như vậy trong vũ trụ mà ta đang biết sao?

	Yes and yes.

	- Hãy tưởng tượng một biến cụ thể mà có thể được truy cập bởi nhiều thread, hoặc có thể được sửa đổi bởi bất kỳ chương trình độc lập nào, hoặc chỉ là một thanh ghi phần cứng được truy cập bởi một thiết bị ngoại vi. Trong tất cả các trường hợp này, giá trị của biến có thể bị thay đổi một cách không kiểm soát và không thể dự đoán.

	- Từ khóa restrict là một lời hứa. Từ khóa volatile là một cảnh báo. Nó nói với compiler: biến này thất thường; đừng cố gắng lưu trữ nó trong thanh ghi của bộ xử lý, vì nó có thể được sửa đổi và bạn không nhận thức được; mỗi khi bạn cần giá trị của nó, hãy fetch nó từ bộ nhớ anew (một lần nữa).

	- Look, các con trỏ có thể là volatile, các giá trị mà chúng trỏ đến cũng có thể là volatile, và cả hai trường hợp này có thể được kết hợp.


8.1.1.11
	- Note: Một biến có thể là volatile và const cùng một lúc:

		const volatile int ticks;

	- Biến 'ticks' (có thể là một phần của một hardware clock) là 'volatile' (vì nó được tăng định kỳ bởi một yếu tố bên ngoài), và cũng là 'const' (vì bạn không được phép thay đổi giá trị của nó).

	- Note: từ khóa volatile không giải quyết vấn đề của critical section theo bất kỳ cách nào.

	- Một khai báo như sau:

		volatile float arith_mean;

	có thể dẫn đến một code thực thi an toàn hơn, vì giá trị của biến được fetched mỗi khi biến được đọc, nhưng nó không bảo vệ biến khỏi việc bị incorrectly updated bởi nhiều thread đang làm việc song song.

	- Đừng quên: từ khóa volatile không phải là sự thay thế cho mutex.

	- Hãy tưởng tượng một thread. Thread thực hiện một số công việc như sau:

		void athread(void){
		    external int stop;
		    while(!stop)
		        do_something();
		}

	- Biến stop được khai báo ở ngoài thread code và được khởi tạo là zero.

	- Một thread khác đang thực hiện một công việc rất tốn thời gian và khi hoàn thành, thread đó set giá trị stop thành 1 để dừng thread 'athread()':

		void otherthread(void){
		        external int stop;
		        time_consuming_job();
		        stop = 1;
		}

	- Liệu nó có hoạt động không?
		Maybe.

	- Tại sao "maybe"?

	- Bởi vì compiler có thể muốn tối ưu hóa code của hàm athread() và muốn fetch giá trị biến stop một lần và lưu trữ nó trong một thanh ghi.

	- Code sẽ không nhận ra rằng giá trị của biến đã bị thay đổi.

	What a pity.

	- Đây là giải pháp - từ khóa volatile cảnh báo compiler:

		void athread(void){
		    external volatile int stop;
		    while(!stop)
		        do_something();
		}

	- Nó sẽ không lưu trữ biến stop nữa. In effect, thread sẽ không bỏ qua cơ hội để dừng công việc của nó.


8.1.2.1 Can a program jump?
	- Có, chương trình có thể thực hiện các "nhảy" (jump).

	- Nhưng làm thế nào?

	- Một nhảy trong một chương trình là một trick làm cho chương trình dừng việc thực thi tại một nơi cụ thể và tiếp tục thực thi tại một nơi hoàn toàn khác.

	- Chúng tôi không muốn nói với bạn về điều này trước đây, vì trung thực mà nói, bạn thậm chí không cần phải biết về nó. Bạn có thể viết code một cách tinh tế và hiệu quả mà không cần đến nhảy, như bạn đã làm trước đó.

	- Nhà khoa học máy tính nổi tiếng người Hà Lan, Edsger Dijkstra (1930–2002), đã đề xuất và chứng minh định lý sau:

		. Bất kỳ chương trình nào có một điểm vào và một điểm ra có thể được viết bằng cách chỉ sử dụng ba yếu tố sau đây:
			
			1. Một chuỗi các lệnh.
			
			2. Một câu lệnh điều kiện (chúng ta gọi nó là câu lệnh if() trong C programming language).
			
			3. Một vòng lặp có điều kiện (chúng ta gọi nó là câu lệnh while() trong C programming language).

	- Như bạn có thể thấy, nhảy không được đề cập ở đây chút nào.

	- Chúng không cần thiết.

	- Nhưng chúng có thể rất hữu ích. Đôi khi. Rất hiếm. Nhưng vẫn có thể.



	- Có hai loại nhảy trong C programming language:

		. local - nhảy cục bộ
		. non-local - nhảy phi cục bộ

	- Một nhảy cục bộ (local jump) được wrapped hoàn toàn bên trong một thân hàm (nói cách khác, bạn không được phép nhảy ra khỏi một hàm sử dụng một nhảy cục bộ).

	- Một nhảy phi cục bộ có thể nhảy giữa các hàm khác nhau.

	- Form đầu tiên của nhảy được thực hiện bằng từ khoá 'goto' và các labels (nhãn).

	- Form thứ hai cần hai hàm cụ thể để thực hiện - longjmp() và setjmp().


8.1.2.2
	- Hãy xem ví dụ sau:

		#include <stdio.h>

		int
		main (void)
		{
		  int i = 5;
		here:
		  printf ("%d\n", i);
		  i--;
		  if (i > 0)
		    goto here;
		  return 0;
		}
		

		. line 5: This is what a label looks like; đó chỉ là một identifier, vai trò duy nhất của nó là đánh dấu một place cụ thể trong code (do đó có tên là nhãn); nhãn không thực hiện bất kỳ hành động nào và không cung cấp bất kì hoạt động nào khi control passes over (near?) it; tên nhãn phải là duy nhất trong một hàm; note: một nhãn không được đặt làm nhãn cho một khai báo;
		
		. line 9: Đây là một ví dụ về việc sử dụng câu lệnh goto; khi control reach đến điểm này, nó nhảy ngay lập tức đến nhãn có tên được chỉ định trong các hướng dẫn.

	- Note:
		
		. nhãn được đề cập trong câu lệnh goto phải được định nghĩa ở một nơi nào đó bên trong thân hàm; điều này cũng có nghĩa là câu lệnh goto sẽ không dẫn đến:
		
			. ngoài một hàm;
			. bên trong hàm khác.
		
		. bất kỳ nhãn nào được định nghĩa trong một hàm cụ thể không nhất thiết phải được sử dụng trong câu lệnh goto.

	- Chương trình tạo ra output sau đây:

		5
		4
		3
		2
		1

	- Một "nhảy" như trong ví dụ được gọi là một backward 'goto' (nó dẫn đến part of code trước đó).

	- Forward jumps are also possible.


8.1.2.3
	- This is how it looks:

		#include <stdio.h>

		int
		main (void)
		{
		  int i = 5;
		here:
		  printf ("%d\n", i);
		  i--;
		  if (i == 0)
		    goto there;
		  goto here;
		there:
		  return 0;
		}

	- The code chứa 2 câu lệnh goto: một backward và một forward (một nhảy lên và một nhảy xuống). Nhảy xuống bắt đầu từ line 9 và kết thúc tại line 11.

	- Chương trình tạo ra output giống như chương trình trước đó.

	- Như bạn có thể đã thấy, cả hai code có thể được thay thế bằng code khác mà không chứa câu lệnh goto.

	- Nó có thể giống như đoạn code sau:

		#include <stdio.h>

		int main(void)
		{
		  int i = 5;

		  while (i > 0)
		    {
		      printf ("%d\n", i);
		      i--;
		    }
		  return 0;
		}

	- Dijkstra có vẻ đúng.

	- Note: chúng tôi luôn khử thụt lề những cái nhãn của mình (chúng tôi đặt chúng ở mức thụt lề thấp hơn so với code kế cận, hoặc thậm chí di chuyển chúng đến mép trái - nó trông đẹp và làm cho việc đọc chúng dễ dàng hơn).


8.1.2.4
	- Một câu lệnh goto có thể dẫn đến phần bên ngoài của một câu lệnh ghép - hãy nhìn code sau:

		#include <stdio.h>

		int
		main (void)
		{
		  int i = 5;
		back:
		  while (i > 0)
		    {
		      int j = 5;
		      while (j > 0)
			{
			  printf ("%d %d\n", i, j);
			  if (i == 4 && j == 4)
			    goto out;
			  j--;
			}
		      i--;
		      goto back;
		    }
		out:
		  return 0;
		}

	- Cả forward và backward đều được cho phép ở đây.

	- Output của chương trình:

		5 5
		5 4
		5 3
		5 2
		5 1
		4 5
		4 4


8.1.2.5
	- Một câu lệnh goto có thể dẫn đến phần bên trong của một câu lệnh ghép - hãy nhìn code:

		#include <stdio.h>

		int
		main (void)
		{
		  int k = 0;
		  if (k != 0)
		    {
		      int i = 2;
		    in:
		      printf ("%d\n", i);
		    }
		  if (k == 0)
		    {
		      k = 3;
		      goto in;
		    }
		  return 0;
		}

	- Cả forward và backward đều được phép ở đây, nhưng có một yếu tố quan trọng phải được xem xét: nếu các 'nhảy' bỏ qua bất kỳ khai báo nào chứa một bộ khởi tạo, khởi tạo sẽ không xảy ra. Nói cách khác, khai báo là hợp lệ (tên được biết trong phạm vi của nó) nhưng việc khởi tạo không được thực hiện.

	- Chương trình ở ví dụ tạo ra output tương tự như sau (do đầu ra là hoàn toàn ngẫu nhiên, chúng tôi không thể hiển thị chính xác như thế nào):

		32765


8.1.2.6
	- Chung quy, việc sử dụng câu lệnh goto không được khuyến khích và được coi là một dấu hiệu của bad design. Tuy nhiên, có một tình huống mà việc đặt nó vào code của bạn là hợp lý: khi bạn muốn sử dụng nó để thoát khỏi các câu lệnh ghép lồng nhau (ví dụ: vòng lặp) nhưng - điều này quan trọng! - đó phải là một forward goto.

	- Hãy xem ví dụ sau:

		#include <stdio.h>

		int
		fun (int a, int b, int c)
		{
		  return a == b && b == c;
		}

		int
		main (void)
		{
		  int i, j, k;
		  int stop;

		  for (i = 0; i < 6; i++)
		    {
		      for (j = 2; j < 5; j++)
			{
			  for (k = 3; k < 4; k++)
			    {
			      stop = fun (i, j, k);
			      if (stop)
				break;
			    }
			  if (stop)
			    break;
			}
		      if (stop)
			break;
		    }
		  printf ("Broken\n");
		  return 0;
		}

	- Tất nhiên, hàm fun() chỉ là một hàm giả - đừng coi trọng nó.

	- Có ba vòng lặp lồng nhau. Chúng ta cần dừng chúng khi một điều kiện cụ thể được đáp ứng. Chúng tôi không sử dụng goto ở đây, vì vậy chúng tôi phải giới thiệu một biến trợ giúp có tên là stop, được kiểm tra ở mỗi nesting level. Thật không may, không có cách nào để làm cho câu lệnh 'break' to exit nhiều hơn một nesting level.

	- Nó trông không đẹp, khó đọc và khó hiểu. Đây là chỗ mà goto có thể do a good job.


8.1.2.7
	- Bạn có thể nhận thấy chúng tôi đã làm gì không? The code now is ngắn gọn và đơn giản hơn rồi - hãy xem code:

		#include <stdio.h>

		int
		fun (int a, int b, int c)
		{
		  return a == b && b == c;
		}

		int
		main (void)
		{
		  int i, j, k;

		  for (i = 0; i < 6; i++)
		    for (j = 2; j < 5; j++)
		      for (k = 3; k < 4; k++)
			if (fun (i, j, k))
			  goto out;
		out:
		  printf ("Broken\n");
		  return 0;
		}

	- Và chúng ta không cần bất kỳ biến trợ giúp nào ở đây.

	- Thank you, goto!

	- Note: Bất kể ví dụ đó, hãy treat goto như một trường hợp ngoại lệ, không phải là quy tắc. Hãy suy nghĩ kỹ trước khi sử dụng nó.


8.1.2.8
	Non-local jumps – setjmp() and longjump() functions

		. Hãy phân tích pseudocode dưới đây:

			#define ERROR (-1)

			int
			f3 (int x)
			{
			  if (x < 0)
			    return ERROR;
			:
			:
			}

			int
			f2 (int x)
			{
			  int r = f3 (x);
			  if (r == ERROR)
			    return ERROR;
			:
			:
			}

			int
			f1 (int x)
			{
			  int r = f2 (x);
			  if (r == ERROR)
			    return ERROR;
			:
			:
			}

			int
			main (void)
			{
			  int a, b;
			:
			  b = f1 (a);
			  if (b != ERROR)
			    {
			    :
			    :
			    }
			  return 0;
			}


		. Ví dụ này minh họa một scheme thường được sử dụng, trong đó một programmer gọi một hàm có thể return một giá trị cụ thể as error information (chúng tôi sử dụng -1 cho mục đích này trong code của chúng tôi). Khi một hàm như vậy nằm ở cuối một long invocation chain, điều này có thể có nghĩa là mỗi hàm đã được gọi trước đó phải kiểm tra giá trị nhận được, điều chỉnh hành vi của mình tùy thuộc vào lỗi phát hiện được và gửi thông tin lỗi trở lại.

		. Như bạn có thể thấy, hàm main() gọi f1(), f1() gọi f2(), f2() gọi f3(). The return trip (Hành trình trở lại) là một bản phản chiếu của route này: f3() trả lại một error code cho f2(), f2() trả lại nó cho f1(), f1() trả lại nó cho main().

		. Chúng tôi nghĩ rằng bạn đang thắc mắc: liệu chúng ta có thể sử dụng bất kỳ loại đường vòng nào và return từ f3() thẳng đến main(), vượt qua f2() và f1()? Cả hai hàm này sẽ không làm gì cả trong trường hợp lỗi và chúng ta không cần chúng.


8.1.2.9
	- Đây là điều chúng tôi nghĩ đến - nhìn snippet sau:

		int
		f3 (int x)
		{
		  if (x < 0)
		    returnto MAIN;
		:
		:
		}

		int
		f2 (int x)
		{
		  int r = f3 (x);
		:
		:
		}

		int
		f1 (int x)
		{
		  int r = f2 (x);
		:
		:
		}

		int
		main (void)
		{
		  int a, b;
		:
		  b = f1 (a);
		:
		MAIN:
		:
		  return 0;
		}

	- Chúng tôi thêm một lệnh không tồn tại vào code - chúng tôi đặt tên nó là 'returnto'. Chúng tôi muốn nó return từ hàm, nhưng không phải đến điểm mà nó đã được gọi, mà là đến một địa điểm được chọn tùy ý trong code, được đặt nhãn với nhãn đã chỉ định (MAIN ở đây).

	- Does it look okay? Không nói về khẩu vị, nhưng cá nhân chúng tôi, chúng tôi thích nó. Để nói một cách hoàn toàn trung thực, chúng tôi sẽ thích nó, vì không có lệnh như vậy trong C programming language, và chúng tôi không tin rằng nó sẽ tồn tại.

	- May mắn thay, còn một cách khác để thực hiện một hành động rất tương tự, nhưng để chúng tôi kể cho bạn về nó, chúng tôi cần bạn sử dụng trí tưởng tượng của mình.

	- Are you ready?

	- Hãy tưởng tượng rằng bạn có thể take a snapshot của trạng thái chương trình hiện tại. Bức ảnh sẽ chứa tất cả mọi thứ bạn có thể cần để khôi phục trạng thái chương trình: tất cả các thanh ghi của bộ xử lý; bộ đếm chương trình; con trỏ stack; ... Với bức ảnh này, bạn có thể "trở lại" đến điểm nó được tạo ra chỉ trong nháy mắt.

	- Hãy tưởng tượng rằng chúng ta tạo bức ảnh ngay trước khi gọi hàm f1(). Hãy giả sử rằng hàm f3() có thể truy cập bức ảnh (điều này dễ dàng, vì chúng ta có thể khai báo nó ở phạm vi source file hoặc truyền nó vào hàm như một đối số). Trong trường hợp đó, f3() cũng có thể khôi phục trạng thái đã lưu và kết quả là trở lại ngay lập tức đến hàm main().

	- Bạn có thể thấy "Ổn đấy, nó trông tốt, nhưng nếu nó trở lại điểm mà bức ảnh đã được tạo ra, nó đáng lẽ sẽ land ngay trước khi gọi f1(), tức là, f1() sẽ được gọi lại... và chúng ta sẽ bắt đầu một vòng lặp vô hạn."

	- Good point.

	- May mắn thay, chúng ta có thể tránh được tình huống tai hại này. Và bây giờ chúng tôi sẽ nói cho bạn biết cách.


8.1.2.10
	- Hãy bắt đầu cuộc thảo luận từ các snapshot:

		#include <setjmp.h>			(tự thêm <>)

		typedef ... jmp_buf;

	- Chúng được lưu trữ trong các biến có type jmp_buf.

	- Type này được định nghĩa trong header file tên là <setjmp.h>. Treat it as a black box. Cấu trúc nội bộ của nó có thể khác nhau trên các implementations/platforms khác nhau, và bạn không cần biết cách nó được xây dựng. Hơn nữa, bạn không muốn biết.

	- Hàm setjmp() tạo ra snapshot:

		#include <setjmp.h>		(tự thêm <>)

		int setjmp(jmp_buf env);

	- Đối số này được sử dụng để trỏ đến biến của kiểu jmp_buf nơi snapshot sẽ được lưu trữ.

	- Hàm return một giá trị rất có ý nghĩa:
		
		. zero khi hàm trở về từ việc gọi trực tiếp;
		
		. bất kỳ giá trị nào khác khi nó trở về từ việc gọi gián tiếp.

	- Okay, chúng ta hãy tiếp tục và giải thích nó:
		
		. khi bạn tự gọi hàm, nó trả về zero;
		
		. nhưng khi bạn quyết định khôi phục trạng thái đã lưu trữ (ở một nơi khác trong code của bạn), nó diễn ra như thể là hàm này đã return một lần nữa (nói cách khác, trạng thái được khôi phục đề cập đến một vị trí nào đó trong hàm setjmp(), vì vậy đây là nơi mà control được chuyển sau khi khôi phục); trong trường hợp đó, hàm phải return một giá trị khác không (và đây là cách chúng ta sẽ tránh vòng lặp vô hạn).

	- Một ví dụ sẽ giúp bạn hiểu rõ hơn (chúng tôi sẽ sớm cho bạn xem một ví dụ). 

	- Hàm longjmp() recreate trạng thái đã lưu trữ trong một snapshot:

		#include <setjmp.h>		(tự thêm <>)

		void longjmp(jmp_buf env, int val);

		
		. Đối số đầu tiên trỏ đến snapshot cần được khôi phục;
		
		. Đối số thứ hai xác định một giá trị để return một cách gián tiếp từ hàm setjmp() tương ứng.

	- Hàm không return gì vì nó thực sự không return to invoker - nó "trả về" vào nơi mà setjmp() đã được gọi - the same setjmp() that đã tạo ra snapshot.


8.1.2.11
	- Dưới đây là ví dụ như đã hứa:

		#include <stdio.h>
		#include <setjmp.h>

		jmp_buf here;

		void
		fun (int n)
		{
		  printf ("fun() got %d\n", n);
		  if (n != 0)
		    longjmp (here, n);
		  printf ("fun() exits normally\n");
		}

		int
		main (void)
		{
		  int r = setjmp (here);
		  if (r == 0)
		    {
		      printf ("about to invoke fun() for the 1st time\n");
		      fun (0);
		      printf ("returned from fun()\n");
		      printf ("about to invoke fun() for the 2nd time\n");
		      fun (1);
		      printf ("returned from fun() again\n");
		    }
		  else
		    {
		      printf ("long jump jumped here\n");
		    }
		  return 0;
		}

	
		. line 4: chúng ta khai báo một biến có tên là here - nó sẽ là nơi lưu trữ cho bức ảnh;
	
		. line 6: hàm fun() kiểm tra đối số của nó, và nếu nó không phải là không, hàm sẽ sử dụng biến here, truyền nó vào hàm longjmp(); điều này có nghĩa là hàm sẽ không trở về nơi nó được gọi, mà thay vào đó sẽ trở lại hàm setjmp() đã điền here;
	
		. line 18: chúng ta gọi hàm setjmp(); chúng ta mong đợi hàm return zero ở đây, như khi nó thường làm sau một direct (actual) invocation;
	
		. line 21: chúng ta rơi xuống đây sau một lời gọi trực tiếp của setjmp(); chúng ta gọi hàm fun() hai lần: với một đối số bằng zero (hàm sẽ trả về một cách bình thường), và với một đối số bằng một (hàm sẽ thực hiện the long jump)
	
		. line 30: chúng ta land here sau một lời gọi gián tiếp của setjmp() (lời gọi forced bởi hàm longjmp())

	- Chương trình tạo ra output sau đây:

		about to invoke fun() for the first time
		fun() got 0
		fun() exits normally
		returned from fun()
		about to invoke fun() for the second time
		fun() got 1
		long jump jumped here
		output

	- Chúng tôi muốn bạn phân tích code một cách cẩn thận. Đừng tiếp tục đọc cho đến khi bạn hiểu rõ nó.


8.1.2.12
	- Bây giờ chúng ta sẽ biến unreal pseudocode trước đó thành pseudocode thực tế và hoạt động.

	- Chúng tôi đã sử dụng setjmp() và longjmp() để thực hiện công việc của câu lệnh non-existent 'returnto' - hãy nhìn vào code:

		#include <stdio.h>
		#include <setjmp.h>

		#define ERROR (-1)

		jmp_buf retpoint;

		int
		f3 (int x)
		{
		  if (x < 0)
		    longjmp (retpoint, ERROR);
		  ;
		  return x;
		}

		int
		f2 (int x)
		{
		  int r = f3 (x);
		  ;
		  return r;
		}

		int
		f1 (int x)
		{
		  int r = f2 (x);
		  ;
		  return r;
		}

		int
		main (void)
		{
		  if (setjmp (retpoint) == 0)
		    {
		      printf ("%d\n", f1 (2));
		      printf ("%d\n", f1 (-2));
		    }
		  else
		    printf ("ERROR!\n");
		  return 0;
		}

		
		. line 6: hàm f3() phát hiện một đối số không hợp lệ - nó nhảy đến điểm retpoint ngay lập tức; f2() cũng như f1() đều sẽ không thấy kết quả của hàm;
		
		. line 14: nếu đối số lớn hơn hoặc bằng 0, hàm sẽ return giá trị của nó;
		
		. line 36: chúng ta chuẩn bị điểm retpoint;
		
		. line 38: chúng ta gọi hàm f1() với giá trị đúng của đối số;
		
		. line 39: chúng ta gọi hàm f1() với giá trị không đúng đối số;

	- Output của chương trình là:

		2
		ERROR

	- Chúng tôi hy vọng mọi thứ giờ đã rõ ràng.


8.1.2.13
	- Bộ đôi 'setjmp() / longjmp()' là một công cụ mạnh mẽ, nhưng phải sử dụng cẩn thận.

	- Nhìn vào chương trình sau:

		#include <stdio.h>
		#include <setjmp.h>

		jmp_buf buf;

		void
		f (void)
		{
		  longjmp (buf, 1);
		}

		int
		main (void)
		{
		  int x = 0;
		  if (setjmp (buf) == 0)
		    {
		      x++;
		      f ();
		    }
		  printf ("%d\n", x);
		  return 0;
		}

	- Nó có vẻ dễ hiểu và dễ dự đoán kết quả của nó, phải không? Thật không may, đó chỉ là một ảo tưởng.

	- Chúng ta có thể dự đoán output của nó không? Of course we can! Nhìn này, biến x được khởi tạo thành không. Tiếp theo, ở line 13, nó được tăng, do đó giá trị được in ra ở line 16 phải là 1.

	- Let's check it.

	- Chúng ta compile code bằng compiler gcc và clang mà không có tùy chọn bổ sung, giống như thế này:

		gcc 08.02.longjmp3.c

	hoặc

		clang 08.02.longjmp3.c

	- Sau đó, chúng ta chạy code thực thi. Đây là điều chúng ta thấy:

		1

	- Okay, không có gì lạ lẫm.

	- Chúng ta compile code một lần nữa, nhưng lần này chúng ta sử dụng the option mà force compiler sử dụng level cao nhất của code optimization, giống như này:

		gcc -O2 08.02.longjmp3.c

	hoặc

		clang -O2 08.02.longjmp3.c

	- Chúng ta chạy code thực thi một lần nữa và chúng ta thấy:

		0

	- Yes. Chính là zero.

	- Why?

	- Compiler, khi làm việc ở chế độ tối ưu hóa (optimization mode), cố gắng lưu trữ các biến được sử dụng nhiều nhất không phải trong bộ nhớ, mà là trong thanh ghi của bộ xử lý. Như bạn biết, setjmp() lưu trữ tất cả các thanh ghi trong một biến có type là jmp_buf. Hàm longjmp() khôi phục các giá trị thanh ghi để các biến được bound với các thanh ghi này sẽ recreate lại các giá trị mà chúng có trước khi setjmp() được gọi - mọi sửa đổi được thực hiện giữa setjmp() và longjmp() sẽ bị mất.

	- Có một phương pháp đơn giản để bảo vệ khỏi effect đó. Bạn có thể đoán được là gì không?

	- Yes, nếu bạn khai báo một biến như 'volatile', nó sẽ tồn tại trước những tác động tiêu cực của việc tối ưu hóa mạnh mẽ đi kèm với long jumps. Mặt khác, một biến volatile sẽ không nhanh bằng biến được lưu trữ trong thanh ghi. Cách nào cũng không tốt.

	- It’s time to summarize our “jumping” chapter.

	- Như bạn có thể thấy, một chương trình có thể nhảy, nhưng điều này không có nghĩa là nhảy luôn là thực hành tốt.

	- Better safe than sorry. (Cẩn tắc vô ưu)


8.1.3.1 Some odds and sods (Sự tập hợp của những việc nhỏ không quan trọng)
	- Bây giờ chúng tôi sẽ giới thiệu một số tính năng mới:

		. static array indices (chỉ số mảng tĩnh)
		. variable-length arrays (mảng có độ dài biến đổi)
		. flexible array members (thành viên mảng linh hoạt)
		. designated initializers (bộ khởi tạo được chỉ định)
		. compound literals (chữ ghép)

	- Những tính năng này đã được thêm vào C programming language khá gần đây. Chúng tôi không muốn thuyết phục bạn sử dụng tất cả chúng trong chương trình của bạn. Bạn có thể tự đánh giá xem chúng nên được đặt vào code của bạn hay không, và thực tế hầu hết chúng thuộc vào danh mục thường được gọi là "syntactic sugar" (syntactic sugar, aka syntactic candy, là một yếu tố không cải thiện khả năng diễn đạt hay chức năng của ngôn ngữ, nhưng có thể make developer's life easier và làm đẹp code).

	- Let's start.


8.1.3.2 Static array indices (Chỉ số mảng tĩnh)

	- Hãy xem snippet sau:

		int fun(char text[4]) { }
	
	- Liệu đoạn code này có ý nghĩa là hàm fun() chỉ có thể được gọi khi đối số là một mảng char gồm bốn phần tử?

	- Of course not. Nó không có ý nghĩa gì khác ngoài:

		void fun(char text[]);
	
	hoặc thậm chí là:

		void fun(char *text);
	
	- Do đó, chương trình dưới đây là hợp lệ và có thể được biên dịch mà không có lỗi hoặc cảnh báo - hãy xem code sau:

		#include <stdio.h>

		int
		fun (char t[4])
		{
		  return t == NULL;
		}

		int
		main (void)
		{
		  fun ("abc");
		  char a[10];
		  fun (a);
		  fun (NULL);
		  return 0;
		}

	- Như bạn thấy, chúng ta có thể treat cái khai báo tham số của hàm này chỉ như một comment hoặc một suggestion, dành cho reader hơn là compiler. Nó nói rằng hàm mong đợi một mảng có độ dài bốn ký tự, nhưng điều này không gây ra bất kỳ hậu quả ngữ nghĩa nào.


8.1.3.3
	- Hãy xem snippet đã được sửa đổi:

		int fun(char text[static 4]) { }
	
	- Đây là một tính năng mới được giới thiệu trong C programming language bởi tiêu chuẩn C99. Tính năng này được gọi là static array indices (chỉ số mảng tĩnh)

	- Như bạn thấy, trick này sử dụng từ khóa cũ là static, nhưng giờ đây từ khóa này đóng một vai trò hoàn toàn mới - nó thông báo cho compiler rằng đối số phải chứa ít nhất bốn phần tử. Điều này cũng có nghĩa là việc truyền con trỏ NULL vào hàm này bị cấm.

	- Từ khóa có thể được đặt phía trước một index trong khai báo tham số của hàm, nhưng nếu có nhiều hơn một index, chỉ có index đầu tiên có thể được đặt trước nó.

	- Ví dụ, đây là một cú pháp đúng:

		int f(int matrix[static 2][2]) { ... }
	
	và đây là một cú pháp không đúng:

		int f(int matrix[static 2][static 2]) { ... }
	
	- Hãy xem lại chương trình minh họa của chúng ta một lần nữa (chúng tôi đã thêm một static vào đó) - line 11 bây giờ là sai, và sẽ gây ra (ít nhất là) một cảnh báo từ compiler - hãy xem code:

		#include <stdio.h>

		int
		fun (char t[static 4])
		{
		  return t == NULL;
		}

		int
		main (void)
		{
		  fun ("abc");
		  char a[10];
		  fun (a);
		  fun (NULL);
		  return 0;
		}

	- Chúng tôi nghĩ bây giờ bạn có thể đã sẵn sàng hỏi về line 8. Liệu invocation này có hợp lệ không? Sau tất cả, chỉ có 3 ký tự trong đối số!

	- Of course not! Có 4 ký tự! Đừng quên '\0' được implicitly đặt ở cuối chuỗi, vì vậy invocation này là hợp lệ. Changing the line theo cách sau:

		fun("ab");
	
	sẽ khiến compiler phát ra thông báo.

	- Note: Ngoài syntactic benefits, chỉ số mảng tĩnh cũng có thể cải thiện code thực thi, nhưng đừng mong đợi có kỳ diệu.

	- Đó chỉ là một sugarcoating (lớp phủ đường) (hoặc candycoating).


8.1.3.4 Variable-length arrays
	- Hãy tưởng tượng rằng bạn phải viết một hàm cần một mảng tạm thời với kích thước không xác định. Kích thước thực sự sẽ được biết khi hàm được gọi (ví dụ: đó là độ dài của một string được truyền qua đối số).

	- Bạn có hai lựa chọn.

	- Thứ nhất, bạn có thể khai báo mảng đủ lớn để chứa tất cả các đối số có thể có.

	Just like this - nhìn code:

		int
		fun (char *arg)
		{
		  char array_big_enough[1000];
		  int i;
		  for (i = 0; arg[i] != '\0'; i++)
		    array_big_enough[i] = arg[i];
		  array_big_enough[i] = '\0';
		  return i;
		}

	- Tất nhiên, điều này không hiệu quả và không đẹp đẽ. Hơn nữa, nếu eventually hàm nhận một đối số dài hơn 999 ký tự, bạn nên chuẩn bị cho một thảm họa nhỏ.


8.1.3.5
	- Option thứ hai là cấp phát một mảng với kích thước được chọn một cách precisely.

	Dưới đây là một ví dụ:

		int
		fun (char *arg)
		{
		  char *well_fitted_array = malloc (strlen (arg) + 1);
		  int i;
		  for (i = 0; arg[i] != '\0'; i++)
		    well_fitted_array[i] = arg[i];
		  well_fitted_array[i] = '\0';
		  free (well_fitted_array);
		  return i;
		}

	- Yes, chắc chắn là it looks better. Tuy nhiên, có một vấn đề - nếu bạn quên thêm một lời gọi free() cho mỗi malloc(), bạn sẽ gây ra rò rỉ bộ nhớ. Be careful.

	- May mắn thay, bạn không cần phải cẩn thận nếu bạn sử dụng compiler tuân theo C99 (or newer, of course). Có một tính năng được gọi là Variable Length Array (mảng có độ dài thay đổi) giúp tự động hóa quá trình này và không bao giờ quên free().


8.1.3.6
	- Nhìn vào đoạn code:

		int
		fun (char *arg)
		{
		  char array[strlen (arg) + 1];
		  int i;
		  for (i = 0; arg[i] != '\0'; i++)
		    array[i] = arg[i];
		  array[i] = '\0';
		  return i;
		}

	- Điểm mấu chốt của vấn đề nằm ở line 2. Khai báo này trông hơi bất thường vì kích thước của mảng không phải là compile-time constant (hằng số thời gian biên dịch) (giá trị mà compiler có thể đánh giá during compilation), mà thay vào đó là một expression.

	- Cách khai báo ranh giới mảng như này có một số ưu điểm:
		
		. Nó elegant (không thể phủ nhận điều này)
		
		. Dễ sử dụng
		
		. Nó bảo vệ bạn khỏi rò rỉ bộ nhớ, vì compiler tự động giải phóng bộ nhớ khi hàm thoát.


8.1.3.7
	- Hơn nữa, nó có thể được sử dụng không chỉ trong phạm vi khối hàm, mà trong bất kỳ phạm vi nào - mảng sẽ tồn tại cho đến khi control leaves the block.

	- Xem ví dụ:

		#include <stdio.h>

		int
		main (void)
		{
		  int i, j;
		  for (i = 1; i < 5; i++)
		    {
		      int arr[i];
		      for (j = 0; j < i; j++)
			arr[j] = i;
		      printf ("%ld\n", sizeof arr);

		    }
		  return i;
		}

	- Mảng 'arr' được tạo mỗi khi control reachs đến line 4, và mảng biến mất khi vòng lặp kết thúc lượt chạy của nó.

	- Code xuất ra output sau:

		4
		8
		12
		16

	- Tất nhiên, cũng có một số hạn chế:
		
		. Bạn không nên sử dụng khai báo này bên ngoài một khối hàm.
		
		. Kích thước của mảng phải lớn hơn 0.
		
		. Bạn không nên sử dụng khai báo này nếu mảng được khai báo là một field của một structure, ví dụ:

			struct { int vec[n]; } S;
		
		. Không được phép nhảy vào một block chứa khai báo một variable-length array; cả hai chương trình sau đây đều là sai:

			int main(void)
			{
			  int n = 1;
			  goto inner;
			  for (;;)
			    {
			      int t[n];
			    inner:
			      t[0] = 0;
			    }
			}

		-----------------------------------------

			int main(void)
			{
			  int n = 1;
			  goto inner;
			  for (;;)
			    {
			    inner:
			      int t[n];
			      t[0] = 0;
			    }
			}


8.1.3.8 Flexible array members
	- Vì chúng ta đã nói về các cấu trúc, chúng ta có lý do chính đáng để kể thêm một số điều về chúng.

	- Tiêu chuẩn C99 giới thiệu một tính năng thú vị cho phép programmer khai báo một thành viên của cấu trúc là một mảng mà không cần khai báo kích thước của nó.

	- Xem ví dụ:

		struct vararr
		{
		  int no;
		  float vals[];
		};

	- Có hai điều cần chú ý:
		
		. Mảng phải là thành viên cuối cùng của cấu trúc.
		
		. Chỉ có thể có một mảng như vậy trong cấu trúc (of course, điều này có thể được assumed từ hạn chế trước đó).

	- Compiler registers (ghi) tên của flexible member, nhưng sẽ không cấp phát bộ nhớ cho nó. Điều này làm cho biểu thức sau:

		sizeof(struct vararr)
	
	return 4 (kích thước của tất cả các thành viên ở trước flexible array). Điều này có nghĩa là bạn không thể sử dụng các biến kiểu này một cách trực tiếp (chúng sẽ không có các flexible member). Điều này cũng có nghĩa là bạn sẽ phải tạo các cấu trúc này một cách thủ công.


8.1.3.9
	- Phân tích ví dụ sau:

		#include <stdio.h>
		#include <stdlib.h>

		int
		main (void)
		{
		  struct vararr
		  {
		    int no;
		    float vals[];
		  };

		  int size = 10;
		  struct vararr *va = malloc (sizeof (struct vararr) + size * sizeof (int));
		  va->no = size;
		  int i;
		  for (i = 0; i < size; i++)
		    va->vals[i] = i;
		  printf ("%ld\n", sizeof (*va));
		  free (va);
		  return 0;
		}

	- Chương trình sử dụng cấu trúc đã được khai báo trước đó. Chúng ta tạo một cấu trúc mới ở line 11 - note cách chúng ta chỉ định kích thước bộ nhớ được cấp phát - đó là sum của kích thước của struct varrarr (không bao gồm flexible member) và kích thước của chính flexible member.

	- Note: printf() ở line 19 outputs:

		4
	
	- Như bạn thấy, việc cấp phát nhằm đáp ứng nhu cầu của flexible member không ảnh hưởng đến kích thước của structure type ban đầu.

	- Note: một số compiler cũ hơn cho phép bạn đạt được mục tiêu tương tự bằng cách sử dụng khai báo sau:

		float vals[0];
	
	- In fact, việc thay đổi code theo cách này sẽ không ảnh hưởng đến hành vi của chương trình miễn là compiler chấp nhận mảng có kích thước bằng 0.


8.1.3.10 Designated initializers – arrays
	- Tiêu chuẩn C99 giới thiệu một số quy ước thuận tiện cho việc viết các khởi tạo (initializers) - chúng được gọi là designated initializers (khởi tạo được chỉ định). Hãy bắt đầu với mảng.

	- Một classic array initializer liệt kê các giá trị theo thứ tự mà chúng nằm trong bộ nhớ. Các phần tử được bỏ qua (các phần tử cuối cùng) được set to zero (hoặc tương đương của nó). Các phần tử dư thừa sẽ bị bỏ qua (có thể phát sinh cảnh báo).

	- Khởi tạo có thể là rỗng.

	- Chương trình sau sẽ xuất ra ba số 0:

		#include <stdio.h>

		int
		main (void)
		{
		  int vec[3] = { };
		  int i;

		  for (i = 0; i < 3; i++)
		    printf ("%d ", vec[i]);
		  printf ("\n");
		  return 0;
		}


8.1.3.11
	- Khởi tạo designated array cho phép bạn liệt kê chỉ những phần tử quan trọng với bạn, và bạn có thể liệt kê chúng theo bất kỳ thứ tự nào.

	- Khởi tạo bao gồm các phần tử theo dạng sau:

		[index] = value

	- Các phần tử được phân tách bằng dấu phẩy.

	- Tất cả các phần tử mảng bị bỏ qua sẽ được khởi tạo thành zero (hoặc tương đương của nó). Tất cả các chỉ số đã cho phải vừa với kích thước của mảng. Tất cả các chỉ số phải là duy nhất.

	- Xem ví dụ sau:

		#include <stdio.h>

		int
		main (void)
		{
		  int vec[3] = {[2] = 1,[0] = 3 };
		  int i;

		  for (i = 0; i < 3; i++)
		    printf ("%d ", vec[i]);
		  printf ("\n");
		  return 0;
		}

	- Chương trình sẽ output như sau:

		3 0 1


8.1.3.12
	- Khởi tạo mảng đa chiều đòi hỏi một form khác của index specification - nó nên phản ánh index hiện tại, ví dụ, khởi tạo của mảng ba chiều gồm các phần tử theo dạng sau:

		[index0][index1][index2] = value

	- Ví dụ sau đây:

		#include <stdio.h>

		int
		main (void)
		{
		  int arr[2][2] = {[1][0] = 2,[0][1] = 1,[1][1] = 3 };
		  int i, j;

		  for (i = 0; i < 2; i++)
		    {
		      for (j = 0; j < 2; j++)
			printf ("%d ", arr[i][j]);
		      printf ("\n");
		    }
		  return 0;
		}


	thể hiện khởi tạo của một mảng hai chiều.

	- Chương trình sẽ output:

		0 1
		2 3


8.1.3.13 Designated initializers – structures
	- A classic structure initializer liệt kê các giá trị theo thứ tự chúng nằm trong bộ nhớ. Các phần tử bị bỏ sót sẽ được đặt thành zero (hoặc giá trị tương đương của nó). Các phần tử dư thừa sẽ bị bỏ qua (có thể phát sinh cảnh báo).

	- Khởi tạo có thể empty.

	- Chương trình dưới đây sẽ xuất ra ba giá trị không (mỗi giá trị trong ba hình thức khác nhau):

		#include <stdio.h>

		struct stru
		{
		  int i;
		  float f;
		  char c;
		  ];

		  int main (void)
		  {
		    struct stru s =[];

		      printf ("%d %f '%c'\n", s.i, s.f, '0' + s.c);
		      return 0;
		  }
		  %

	- This is what it will look like:

		0 0.000000 '0'

	- Hãy nghiên cứu cẩn thận cách printf() output vào trường 's.c'.


8.1.3.14 Designated initializers – arrays
	- The designated structure initializer cho phép bạn khởi tạo chỉ các trường quan trọng và bạn có thể liệt kê chúng theo bất kỳ thứ tự nào.

	- Khởi tạo bao gồm các phần tử theo dạng sau:

		.field = value
	
	- Các phần tử được ngăn cách bằng dấu phẩy.

	- Tất cả các trường cấu trúc bị bỏ sót sẽ được khởi tạo thành zero (hoặc giá trị tương đương của nó). Tên trường phải là duy nhất.

	- Xem ví dụ:

		#include <stdio.h>

		struct stru
		{
		  int i;
		  float f;
		  char c;
		};

		int
		main (void)
		{
		  struct stru s = {.c = 5,.f = 3.1415 };

		  printf ("%d %f '%c'\n", s.i, s.f, '0' + s.c);
		  return 0;
		}

	- Output của chương trình trông như sau:

		0 3.141500 '5'
	

8.1.3.15 Combined designated initializers
	- Cả hai kỹ thuật có thể được kết hợp cho các cấu trúc chứa các mảng và cho các mảng chứa các cấu trúc.

	- Dưới đây là một ví dụ về cái đầu tiên:

		#include <stdio.h>

		struct stru
		{
		  int i;
		  float f[2];
		};

		int
		main (void)
		{
		  struct stru s = {.f[1] = -1.,.f[0] = 1 };

		  printf ("%d %f %f\n", s.i, s.f[0], s.f[1]);
		  return 0;
		}

	- Như bạn có thể thấy, các phần tử của bộ khởi tạo liên quan đến các trường của mảng trông như sau:

		.field[index] = value
	
	- Output của chương trình là:

		0 1.000000 -1.000000


8.1.3.16 Designated initializers – arrays
	- Và đây là ví dụ về loại thứ hai:

		#include <stdio.h>

		struct stru
		{
		  int i;
		  float f;
		};

		int
		main (void)
		{
		  struct stru s[2] = {[1].f = 1.,[0].i = 1 };

		  printf ("%d %f\n", s[0].i, s[0].f);
		  printf ("%d %f\n", s[1].i, s[1].f);
		  return 0;
		}

	- Như bạn có thể thấy, các phần tử của bộ khởi tạo liên quan đến các trường của cấu trúc trông như sau:

		[index].field = value
	
	- Output của chương trình:

		1 0.000000
		0 1.000000


8.1.3.17 Compound literals
	- Một bộ khởi tạo không tồn tại như một entity độc lập - nó chỉ là một mẫu được sử dụng khi một biến cụ thể được tạo ra.

	- Tiêu chuẩn C99 giới thiệu một syntax mới cho phép bộ khởi tạo đóng vai trò như một literal - dữ liệu có thể được gán cho một biến, chuyển đến hàm dưới dạng đối số, hoặc thậm chí được sửa đổi. Tính năng này được gọi là compound literal.

	- Một compound literal được chỉ định theo dạng tổng quát sau:

		((type) { initiliazer })

	- Cả type và initializer phải tương thích (tức là nếu type mô tả một mảng, thì initializer phải là một mảng).

	- The type may be:

		. một tên type;
		. một mô tả type;
		. một mảng có kích thước không xác định.
	
	- Xem ví dụ:

		#include <stdio.h>

		struct stru
		{
		  int i;
		  float f;
		};

		int
		main (void)
		{
		  struct stru s;
		  int *t, i;

		  t = ((int[3])
		       {
		       2, 1, 0});
		  s = ((struct stru)
		       {
		       1, 2.0});
		  for (i = 0; i < 3; i++)
		    printf ("%d ", t[i]);
		  printf ("\n%d %f\n", s.i, s.f);
		  return 0;
		}

	- Có hai compound literal - ở lines 9 và 10.

		. literal đầu tiên thực sự là một mảng int ba phần tử, nhưng do context được tạo ra bởi phép gán, nó được xem như một con trỏ đến phần tử đầu tiên của nó (tên mảng luôn luôn là một con trỏ trong C programming language)

		. literal thứ hai xây dựng một structure of type 'struct structure'.

	- Note: Việc không thể sử dụng các compound literal buộc bạn phải sử dụng các phép gán đơn như sau (chúng ta giả định rằng con trỏ t chứa một địa chỉ hợp lệ của một khối bộ nhớ đã cấp phát):

		t[0] = 2; t[1] = 1; t[2] = 0;
		s.i = 1; s.f = 2.0;

	- Output của chương trình là:

		2 1 0
		1 2.000000


8.1.3.18
	- Compound literal có thể sử dụng các designated literal.

	- Chương trình output các line sau:

		1 0 -1
		-1 2.000000


8.1.3.19
	- Một trong những khía cạnh hấp dẫn liên quan đến compound literal đó là: chúng là L-values (nghĩa là chúng có thể đặt bên trái của toán tử gán) và do đó, có thể được sửa đổi.

	- Treat this as a curiosity, not a suggestion.

	- Nhìn vào đoạn code kỳ quặc này:

		#include <stdio.h>

		int
		main (void)
		{
		  int i;

		  i = ((int[3])
		       {
		       [2] = 0,[1] = 1,[0] = 2})[2] += 3;
		  printf ("%d\n", i);
		  return 0;
		}

	- Compound literal tạo ra một mảng mà phần tử thứ hai của nó được sửa đổi bởi toán tử +=.

	- Phần còn lại của mảng là vô dụng. Okay, chúng tôi không muốn làm bất kỳ điều gì hợp lý với nó cả. Chúng tôi chỉ muốn cho bạn thấy cách những compound literal này hành xử khi chúng là target (không phải source!) của một phép gán.

	- Nếu bạn không muốn literal của mình có thể bị sửa đổi, bạn có thể make it a 'const' literal, just like this:

		(const int[3]){[2] = 0, [1] = 1, [0] = 2})


8.1.4.1 This and that – assembler insets
	- "C" là ngôn ngữ lập trình có mục đích chung, nhưng vị trí gốc của nó thường khá thấp, gần phần cứng và thiết bị vật lý. Nó có thể được sử dụng để triển khai thành công các OS kernel và driver thiết bị. Các compiler hiện đại có khả năng tạo ra code thực thi rất hiệu quả và nhanh chóng, nên nhu cầu sử dụng any machine or assembly language đã gần như bị loại bỏ ngày nay.

	- Gần như, nhưng không hoàn toàn.

	- Đôi khi, chúng ta cần một code hiệu quả hơn so với code do compiler tạo ra. Có những lúc, chúng ta cần viết code driver thiết bị hoạt động trên low-level hardware registers và C language có thể không đủ flexible để đạt được mục tiêu.

	- Vậy chúng ta nên làm gì?

	- Chúng ta có hai option:

		1. Chúng ta có thể viết một assembly code riêng, đặt nó vào một source file thích hợp (trong MS Windows thường sử dụng phần mở rộng .asm cho những file này, trong khi Unix/Linux thì ưa chuộng hậu tố .a) và assemble nó bằng một translator chuyên dụng; the resulting semi-compiled code này có thể được liên kết với phần còn lại của project sau đó và được sử dụng như bất kỳ đoạn code nào khác trong chương trình cuối cùng;

		2. Sử dụng option có sẵn trong hầu hết các trình biên dịch ngôn ngữ "C" hiện đại và đặt assembly code trực tiếp vào "C" source; cách nhúng assembly code vào trong một ngôn ngữ lập trình high-level như vậy thường được gọi là một assembler insert.

	- Option thứ hai có vẻ thuận tiện hơn, phải không? Bạn giữ toàn bộ code trong một phần, sử dụng một công cụ để biên dịch và liên kết project, và bạn không cần phải chuyển đổi giữa các nguồn và môi trường khác nhau.

	- Như thường lệ, có một chữ "but" trong khái niệm này. Phương pháp này hoàn toàn không được chuẩn hóa. Tất nhiên, đó là chuyện bình thường khi một assembly code cụ thể không thể sử dụng trên các nền tảng phần cứng khác nhau (ví dụ, assembly code được viết cho họ Intel x64 sẽ hoàn toàn vô dụng khi áp dụng vào bất kỳ bộ xử lý ARM nào), nhưng chúng tôi muốn nói về một điều hoàn toàn khác.

	- Các trình biên dịch khác nhau sử dụng syntax hoàn toàn không tương thích cho cùng một mục đích - vì vậy bạn không thể mong đợi code này có thể dễ dàng chuyển từ trình biên dịch này sang trình biên dịch khác.

	- There’s nothing we can do about that – sorry.

	- Bây giờ chúng tôi sẽ show cách các assembler insert hoạt động trong hai môi trường khác nhau:

		. gcc của GNU (the same các quy ước được sử dụng bởi trình biên dịch clang)
		. MS CL.

	- Đoạn code chúng ta sẽ viết được thiết kế chỉ để chạy trên bộ xử lý Intel x86/x64.

	- Chúng tôi sẽ triển khai hành động tương tự trong cả hai môi trường. Đó sẽ là một đoạn code ngắn, chia giá trị int (lấy từ biến được đặt tên là VAR) cho 2. Để làm cho code của chúng tôi hiệu quả hơn, chúng tôi sẽ thay thế phép chia tốn thời gian bằng một phép dịch bit sang phải cực kỳ nhanh chóng.

	- Bộ xử lý Intel x86 có một set of general purpose 32-bit registers, được đặt tên là EAX, EBX, ECX và EDX. Chúng tôi sẽ sử dụng thanh ghi đầu tiên trong đống này (tất nhiên, bất kỳ thanh ghi nào khác cũng có thể được sử dụng thành công).

	- Đây là những gì chúng tôi sẽ làm:

		fetch var EAX
		shift EAX to the right
		by 1 bit
		store EAX in var

	- Chúng ta cần một số kiến thức sơ bộ về các machine instructions (lệnh máy) của Intel - here it is:

		. Lệnh làm cho chuyển dữ liệu từ bộ nhớ sang thanh ghi và từ thanh ghi sang bộ nhớ được đặt tên là 'MOV' (move).

		. Lệnh dịch thanh ghi sang phải được đặt tên là SAR (shift arithmetic right)).

	- Để làm cho toàn bộ điều này trở nên phức tạp hơn, chúng ta cần nói thêm rằng có hai quy ước độc lập for coding assembler instructions:

		. Quy ước Intel nói rằng target is always first - line sau đây cause giá trị của VAR được đặt vào thanh ghi EAX:

		  MOV EAX,VAR
		
		. Quy ước AT&T nói rằng target is always last - line sau đây khiến nội dung của thanh ghi EAX được lưu trữ trong biến VAR:

		  MOV EAX, VAR

	- Hãy bắt đầu với gcc.


8.1.4.2 This and that – gcc assembler insets
	- Đây là những yếu tố cần được xem xét khi bạn viết một assembler insert cho trình biên dịch gcc/clang:
	
		. Phải tuân theo quy ước AT&T.
		
		. assembler insert phải được đặt trong một string, và string này phải được đặt trong dấu ngoặc đơn và đứng trước từ khóa 'asm'.
		
		. Vì string được xem xét như assembler code thực tế và assembler code thường được viết với một lệnh máy trên mỗi line, bạn phải bắt chước cách này bằng cách sử dụng ký tự \n.
		
		. Ngoài assembler code thực tế, 3 phần này phải được thêm vào, được phân tách bằng dấu hai chấm:
			
			. Một list các giá trị output (các biến sẽ được viết bởi assembler code)
			
			. Một list các giá trị input (các biến sẽ được đọc bởi assembler code)
			
			. Một list các thanh ghi bị ghi đè trong quá trình thực thi code của bạn (gcc cần biết các thanh ghi nào bị mất values của nó trong quá trình thực thi code của bạn)
	   
	- Let's add một số chú thích ngắn:
	
		. line 5: assembler insert bắt đầu ở đây.
	
		. line 6: hậu tố "l" sau lệnh cho biết lệnh hoạt động trên một biến 32-bit (l comes from long); '%0' đề cập đến biến đầu tiên được liệt kê trong the output/input constraint list (do đó, nó đề cập đến biến VAR); tên thanh ghi phải được preceded bởi tiền tố '%%'.
	
		. line 7: tiền tố "$" đánh dấu các immediate values (các giá trị được nhúng trong lệnh máy, không được lấy từ bộ nhớ).
	
		. line 9: tiền tố '=m' có nghĩa là đây là output constraints, và biến được chỉ định ở đây được lấy từ bộ nhớ.
	
		. line 10: tiền tố 'r' có nghĩa là đây là input constraints, và biến được chỉ định ở đây sẽ được đặt vào bộ nhớ.
	
		. line 11: chỉ định rằng code của chúng ta sẽ clobbers (dịch là ghi đè, hoặc làm mất giá trị) thanh ghi EAX.

	- Code outputs các line sau:

		-16
		255

	- Note: Mô tả của chúng tôi phải rất ngắn gọn. Hãy tham khảo tài liệu GNU để biết thêm chi tiết: 
		https://gcc.gnu.org/onlinedocs/gcc/Extended-Asm.html


8.1.4.3 This and that – CL assembler insets
	- This is how it looks khi bạn đang dealing with trình biên dịch MS CL:
		
		. Phải tuân theo quy ước Intel.
		
		. the assembler insert phải được đặt trong một compound statement, được đặt trước bởi từ khóa '__asm' (lưu ý các gạch dưới).
		
		. Vì string được treated như assembler code thực tế và assembler code thường được viết với một lệnh máy trên mỗi line, bạn phải bắt chước cách này bằng cách sử dụng ký tự '\n'.
		
		. Đặt tên biến trong dấu ngoặc đơn giống như việc dereference trong C programming language (var là một địa chỉ và [var] là giá trị tại địa chỉ đó).

	- Dưới đây là đoạn code:

		#include <stdio.h>

		int
		div2 (int x)
		{
		  int VAR = x;
		asm ("movl %0,%%eax\n" "sarl $1,%%eax\n" "movl %%eax,%0\n": "=m" (VAR): "m" (VAR):"%eax");
		  return VAR;
		}

		int
		main (void)
		{
		  printf ("%d\n", div2 (-32));
		  printf ("%d\n", div2 (511));
		  return 0;
		}

	- Như bạn có thể thấy, code này ngắn gọn và đơn giản hơn so với code được thiết kế cho gcc. Chúng tôi hy vọng rằng it needs no additional comments.

	- Code xuất ra cùng kết quả như code trước đó.

	- Để biết thêm chi tiết, hãy tham khảo tài liệu của Microsoft:
		https://learn.microsoft.com/en-us/cpp/assembler/inline/inline-assembler?view=msvc-170&redirectedfrom=MSDN


8.1.4.4 This and that – sequence points
	- Bây giờ chúng tôi muốn nói với bạn về một hiện tượng rất bí ẩn được gọi là các sequence points (điểm chuỗi). Vấn đề này thường bị đánh giá thấp và bị bỏ qua, mặc dù nó là key để hiểu cách mà C language compiler nhìn nhận các biểu thức phức tạp.

	- Hãy bắt đầu từ một đoạn code dường như đơn giản:

		#include <stdio.h>

		int
		main (void)
		{
		  int a, b;
		  a = 2;
		  b = (a + ++a) * (--a + a);
		  printf ("%d %d\n", a, b);
		  return 0;
		}

	- Phân tích nó một cách cẩn thận. Rất cực kì cẩn thận.

	- Bây giờ hãy trả lời câu hỏi này - đoạn code sẽ xuất ra cái gì?

	- Hãy nghĩ lại, nghĩ cho kĩ.


8.1.4.5
	- Hãy bắt đầu từ phần dễ hiểu hơn của câu hỏi và cố gắng đoán giá trị của biến a sau khi đánh giá biểu thức sau:

		a = 2;
		b = (a + ""++a"") * (""--a"" + a);		// phần trong "" "" là phần được marked, code không có dấu này

	- Dường như nó đơn giản: biến được tăng giá trị một lần và giảm giá trị một lần. Điều này có nghĩa là giá trị ban đầu sẽ được giữ nguyên.

	- Chúng tôi đặt cược rằng a sẽ bằng 2 - bạn đồng ý không?

	- Yes, chúng ta đúng. Hãy cố gắng tìm giá trị cuối cùng của b.

	- Chúng tôi đã hiển thị các giá trị mà (theo ý kiến của chúng tôi) nên được áp dụng vào biểu thức như giá trị hiện tại của biến a:
		xem ảnh:
			https://edube.org/learn/clp-c-programming-language-certified-professional/this-and-that-sequence-points-1

	- Bạn đồng ý không? Chúng tôi nghĩ rằng bạn sẽ đồng ý.

	- Vì vậy, chúng ta có:

		(2 + 3) * (2 + 2) = 5 * 4 = 20

	- Chúng tôi đã biên dịch code bằng ba trình biên dịch khác nhau, và đây là kết quả mà chúng tôi nhận được từ code thực thi:

		Compiler      		Output

		gcc 4.9.3     		 2 24
		clang 3.7.1   		 2 20
		cl 19.00.24210		 2 16

	- Đã xảy ra chuyện gì?

	- How is that possible?

	- Liệu có lỗi (một số hoặc tất cả) ở các trình biên dịch không? Hoặc code có vấn đề không?

	- Chúng ta phải bắt đầu từ một định nghĩa.

	- "Một sequence point là điểm trong code nơi tất cả các side effects trước đó đã xảy ra và side effects tiếp theo chưa xảy ra."

	- C programming language assumes rằng có các sequence point nơi các phần tử sau được đặt:

		. toán tử &&;
		. toán tử ||;
		. toán tử ,;
		. toán tử ?;
		. at the end of mỗi biểu thức hoàn chỉnh (điều này cũng có nghĩa là dấu chấm phẩy ';' là một sequence point)
		. trước khi gọi hàm;
		. giữa câu lệnh 'return' và nơi mà control returns to;
		. cuối mỗi khởi tạo;
		. giữa các khai báo.

	- Okay. Mọi thứ trông rất ấn tượng. Nhưng nó thực sự có nghĩa là gì?

	- Hãy áp dụng nó vào code của chúng ta.


8.1.4.6
	- Look:

		a = 2;
		b = (a + ++a) * (--a + a);

		// hai dấu ';' đang được marked

	- Có hai sequence point trong code - đều được giới hạn bởi semicolons.

	- Quy tắc này đảm bảo rằng:
		
		. Giá trị của biến a sẽ được ổn định (fully set) trước khi the control vượt qua sequence point đầu tiên;
		
		. Giá trị của biến a và b sẽ được ổn định trước khi the control vượt qua sequence point thứ hai.

	- That's clear.

	- Nhưng có một vấn đề khác, nghiêm trọng và nặng hơn.

	- Nếu bạn có nhiều hơn một side effect trong biểu thức của mình (tăng và giảm cũng thuộc loại này) thì không có gì đảm bảo về thứ tự xuất hiện của chúng. Cũng không có gì đảm bảo về thời điểm xuất hiện của các side effect đó. Chúng ta nói rằng các side effect này là unsequenced (không được sắp xếp).

	- Mỗi compiler có thể sắp xếp lại biểu thức theo cách riêng của nó, vì quy tắc duy nhất mà nó phải tuân theo là the one saying how to deal with sequence points.

	- Mọi thứ xảy ra giữa các sequence points là một điều bí ẩn (yes, đó là một metaphor, không phải là một thuật ngữ kỹ thuật).

	- Note: compiler clang sẽ phát ra cảnh báo khi nó gặp nhiều hơn một side effect trong một context mà nó có thể gây ra hành vi không dự đoán được. Đây là thông báo của nó về đoạn code của chúng ta:

		08.04.seqp.c:6:11: warning: unsequenced modification and access to 'a'

	Chúng tôi hoan nghênh điều này.

	- Điều này có nghĩa gì đối với bạn?

		. Hãy cẩn thận khi sử dụng side effect;
		. Tránh biểu thức phức tạp và khó hiểu chứa nhiều ++ và --;
		. Giữ nó đơn giản;
		. Đừng làm gì to excess.

	- Biểu thức đúng có thể trông như sau:

		b = (2 * a + 1) * (2 * a);

	- Nó trông không ấn tượng bằng, nhưng nó dễ đọc và dễ dự đoán. Vì vậy, nó tốt hơn.


8.1.4.7 This and that – unspecified and undefined behaviors
	- Chúng tôi đã cho bạn thấy rằng một chương trình có thể hoạt động khác nhau trong các trường hợp khác nhau. Những vấn đề phức tạp và không mong đợi như vậy thường được biết đến là portability issues (vấn đề về tính di động).

	- Khi chúng tôi cho bạn thấy hiện tượng này, chúng tôi đã đề cập đến một vấn đề quan trọng – sự hoàn thiện của các C programming standards.

	- Việc dự đoán tất cả các chương trình có thể xảy ra là không thể. Cũng không thể dự đoán tất cả dữ liệu mà các chương trình sẽ xử lý. Hơn nữa, các tài liệu tiêu chuẩn không thể bao gồm các tính năng cụ thể của tất cả các nền tảng phần cứng có thể.

	- Nói cách khác, tiêu chuẩn không thể hoàn chỉnh. Điều đó là không thể, và cũng vô nghĩa.

	- Đây là lý do tại sao C language standard định nghĩa hai thuật ngữ sau đây:

		. unspecified behavior - Hành vi không xác định
		. undefined behavior - Hành vi không định nghĩa

	- Hãy trích dẫn từ document gốc:

		. "Hành vi không xác định" là việc sử dụng một giá trị không xác định hoặc hành vi khác trong đó International Standard này cung cấp hai hoặc nhiều khả năng và không áp đặt yêu cầu cụ thể nào đối với khả năng được chọn trong bất kỳ trường hợp nào.

		. "Hành vi không định nghĩa" là một hành vi, khi sử dụng một cấu trúc chương trình không di động hoặc lỗi hoặc dữ liệu sai, mà International Standard không đặt ra yêu cầu cụ thể nào cho nó.

	- Tiêu chuẩn C11 chứa hơn 50 trường hợp của hành vi không xác định và hơn 200 trường hợp hành vi không định nghĩa. Điều này có nghĩa là bất kỳ chương trình nào chứa một hoặc nhiều trường hợp như vậy có thể hoạt động theo cách khác nhau khi được biên dịch và chạy trên các nền tảng và môi trường khác nhau. Nó cũng có nghĩa là một chương trình như vậy có thể chạy thành công trên nền tảng này và thất bại trên nền tảng khác.

	- Ví dụ, hiện tượng trước đó mà được tiêu chuẩn mô tả là một hành vi không xác định như sau:

		"The following is unspecified: thứ tự mà trong đó các subexpression được đánh giá và thứ tự mà trong đó các side effects xảy ra, trừ khi được chỉ định cho the function-call (), &&, ||, ? :, and comma operators". 

	- Điều đó là bình thường. Accept it.

	- Chúng tôi sẽ show cho bạn một số hành vi không xác định và không định nghĩa thú vị nhất mà tiêu chuẩn mô tả.


8.1.4.8
	"The following is unspecified: trạng thái kết thúc được returned to hosted environment nếu the return type của hàm main không tương thích với int."

	- The exit code returned bởi chương trình này là không được xác định.

		float
		main (void)
		{
		  return 3.14159265359;
		}


8.1.4.9
	"The following is unspecified: các giá trị của các bytes tương ứng với các members của union ngoại trừ member được lưu trữ vào cuối cùng."

	- Output của chương trình này không được xác định.

		#include <stdio.h>

		int
		main (void)
		{
		  union
		  {
		    int i;
		    short s;
		  } un;

		  un.s = -1;
		  printf ("%d\n", un.i);
		  return 0;
		}


8.1.4.10
	"The following is unspecified: liệu hai string ký tự có tạo ra các mảng riêng biệt không."

	- Output của chương trình này không được xác định:

		#include <stdio.h>

		int
		main (void)
		{
		  printf ("%d\n", "abc" == "abc");
		  return 0;
		}

	- Note: Chương trình không so sánh các strings - nó so sánh những con trỏ đến các strings. Điều này dẫn chúng ta đặt câu hỏi về việc liệu hai strings giống nhau có được lưu trữ trong bộ nhớ dưới dạng một hoặc hai bản sao hay không.


8.1.4.11
	"The following is undefined: giá trị của một con trỏ đến một đối tượng mà lifetime của nó đã kết thúc được sử dụng."

	- Output của chương trình sau đây là không xác định.

		#include <stdio.h>

		int *
		fun (void)
		{
		  int x = 2;
		  return &x;
		}

		int
		main (void)
		{
		  printf ("%d\n", *fun ());
		  return 0;
		}


8.1.4.12
	"The following is undefined: đối với a call to a function mà không có function prototype trong phạm vi, số lượng đối số không bằng số lượng tham số."

	- Output của chương trình sau đây là không xác định.

		#include <stdio.h>

		int
		main (void)
		{
		  printf ("%d\n", f ());
		  return 0;
		}

		int
		f (int x)
		{
		  return x;
		}


8.1.4.13
	"The following is undefined: giá trị của một con trỏ trỏ đến không gian đã bị giải phóng bởi a call to free or realloc function được sử dụng."

	- Output của chương trình sau đây là không xác định.

		#include <stdio.h>
		#include <stdlib.h>

		int
		main (void)
		{
		  int *p = malloc (sizeof (int));
		  *p = 123;
		  free (p);
		  printf ("%d\n", *p);
		  return 0;
		}


8.1.4.14
	"The following is undefined: một biểu thức được dịch chuyển bởi một số âm hoặc bởi một lượng lớn hơn hoặc bằng chiều rộng của promoted expression"

	- Output của chương trình sau đây là không xác định.

		#include <stdio.h>

		int
		main (void)
		{
		  printf ("%d\n", 1 << -1);
		  return 0;
		}


8.1.4.15
	"The following is undefined: an attempt is made to copy một object đến một overlapping object bằng cách sử dụng một hàm thư viện, ngoài chức năng được explicitly cho phép (ví dụ: memmove)."

	- Output của chương trình sau đây là không xác định.

		#include <stdio.h>
		#include <string.h>

		int
		main (void)
		{
		  int t[] = { 1, 2, 3 };
		  memcpy (t, t + 1, 2 * sizeof (int));
		  printf ("%d %d %d\n", t[0], t[1], t[2]);
		  return 0;
		}


8.1.4.6
	"The following is undefined: một định nghĩa hàm bao gồm một identifier list, nhưng các types của các tham số thì không được khai báo trong a following declaration list."

	- Output của chương trình sau đây là không xác định.

		#include <stdio.h>
		#include <string.h>

		int
		main (void)
		{
		  int t[] = { 1, 2, 3 };
		  memcpy (t, t + 1, 2 * sizeof (int));
		  printf ("%d %d %d\n", t[0], t[1], t[2]);
		  return 0;
		}
