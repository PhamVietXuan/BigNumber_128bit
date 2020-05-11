#pragma once
#include "QInt.h"
#include "ConvertingPart.h"

//FILE NÀY CÓ 5 NHÓM HÀM

int GetBit_Thu_i(QInt x, int i);
//Input: Nhận 1 biến QInt và 1 biến số nguyên int
//Output: trả về bit thứ i của QInt x
//Cách hoạt động: Lấy bit của tương ứng trong mảng chứa kiểu dữ liệu QInt


void SetBit1_Thu_i(QInt& x, int i);
//Input: Nhận 1 biến QInt và 1 biến số nguyên int
//Output: hàm không có giá trị trả về
//Cách hoạt động: Đặt bit thứ i của QInt x thành bit 1


void SetBit0_Thu_i(QInt& x, int i);
//Input: Nhận 1 biến QInt và 1 biến số nguyên int
//Output: hàm không có giá trị trả về
//Cách hoạt động: Đặt bit thứ i của QInt x thành bit 0


void SetBit_Thu_i(QInt& x, int i, int bit);
//Input: Nhận 1 biến QInt x, 1 biến int i để xác địa chỉ của bit và 1 biến int bit để nhận bit cần gán (0 hoặc 1) 
//Output: hàm không có giá trị trả về
//Cách hoạt động: Dựa vào i tìm đến địa chỉ bit trong mảng, sau đó đặt lại bit tương ứng


QInt optBu2(QInt x);
//Input: Nhận 1 biến QInt 
//Output: trả về dạng bù 2 của QInt x
//Cách hoạt động: Đảo bit, sau đó cộng 1


bool isEqualZero(QInt x);
//Input: Nhận 1 biến QInt 
//Output: trả về true nếu QInt == 0, false nếu QInt != 0
//Cách hoạt động: kiểm tra từng phần tử trong mảng với 0


bool isNegative(QInt x);
//Input: Nhận 1 biến QInt 
//Output: trả về true nếu QInt là số âm, false nếu QInt không âm
//Cách hoạt động: Kiểm tra bit dấu của QInt


QInt optCong(QInt a, QInt b);
//Input: Nhận 2 biến QInt
//Output: kết quả a + b
//Cách hoạt động: cộng từng bit theo hàng dọc với biến nhớ carry 

QInt optTru(QInt a, QInt b);
//Input: Nhận 2 biến QInt
//Output: kết quả a - b
//Cách hoạt động: tính tổng a và số bù 2 của b

QInt optNhan(QInt a, QInt b);
//Input: Nhận 2 biến QInt
//Output: kết quả a * b
//Cách hoạt động: 
//xét dấu a và b, nếu âm thì chuyển về dương
// tạo biến QInt kq
//nếu bit cuối của b == 1 thì kq = kq + a;
//dịch trái a, dịch phải b
//lặp lại cho đến khi b == 0
//Xét dấu kết quả




QInt optChiaLayNguyen(QInt q, QInt m);
//Input: Nhận 2 biến QInt
//Output: kết quả a / b
//Cách hoạt động: 
//xét dấu a và b, nếu âm thì chuyển về dương
//tạo biến QInt kq = 0
// DichTrai[kq,q] (bit 0 của q thành bit 127 của kq)
// Thực hiện kq = kq - m
// Kiểm tra nếu kq < 0 thì kq = kq + m (q[bit 127] = 0)
// Ngược lại thì q = 1 (q[bit 127] = 1)
// Lặp lại hết độ dài q (128)
// kq = q (kq chính là thương) 
// xét dấu kết quả


QInt optAND(QInt a, QInt b);
//Inpuy: Nhận 2 biến QInt
//Output: kết quả a & b
//Cách hoạt động: lấy từng phần tử tương ứng của 2 mảng để AND với nhau


QInt optOR(QInt a, QInt b);
//Inpuy: Nhận 2 biến QInt
//Output: kết quả a | b
//Cách hoạt động: lấy từng phần tử tương ứng của 2 mảng để OR với nhau


QInt optXOR(QInt a, QInt b);
//Inpuy: Nhận 2 biến QInt
//Output: kết quả a ^ b
//Cách hoạt động: lấy từng phần tử tương ứng của 2 mảng để XOR với nhau


QInt optNOT(QInt x);
//Inpuy: Nhận 1 biến QInt
//Output: kết quả ~x
//Cách hoạt động: NOT từng bit của mảng



QInt optDichTrai(QInt& a, int number);
//Input: Nhận 1 biến QInt và 1 biến số nguyên int
//Output: trả về kết quả biến QInt a đã được dịch sang trái number bit
//Cách hoạt động: dịch lần lượt từng bit của QInt 


QInt optDichPhai(QInt& a, int number);
//Input: Nhận 1 biến QInt và 1 biến số nguyên int
//Output: trả về kết quả biến QInt a đã được dịch sang phải number bit
//Cách hoạt động: dịch lần lượt từng bit của QInt 



QInt optROR(QInt a, int number);
//Input: Nhận 1 biến QInt và 1 biến số nguyên int
//Output: trả về biến QInt a dùng phép xoay phải number lần
//Cách hoạt động: tương tự phép dịch phải, nhưng các bit bị đẩy ra ngoài được lưu lại và gán vào đầu còn lại của mảng


QInt optROL(QInt a, int number);
//Input: Nhận 1 biến QInt và 1 biến số nguyên int
//Output: trả về biến QInt a dùng phép xoay trái number lần
//Cách hoạt động: tương tự phép dịch trái, nhưng các bit bị đẩy ra ngoài được lưu lại và gán vào đầu còn lại của mảng



bool optBiggerThan(QInt& a, QInt& b);
//Input: Nhận 2 biến QInt 
//Output: trả về true nếu a > b, false nếu a = b 
//Cách hoạt động: a > b <=> a - b > 0, kiểm tra (a-b) có bằng 0 và âm hay không 


bool optLessThan(QInt& a, QInt& b);
//Input: Nhận 2 biến QInt 
//Output: trả về true nếu a < b, false nếu a >= b 
//Cách hoạt động: a < b <=> a - b < 0, kiểm tra (a-b) có âm hay không 


bool optBiggerOrEqual(QInt& a, QInt& b);
//Input: Nhận 2 biến QInt 
//Output: trả về true nếu a >= b, false nếu a < b 
//Cách hoạt động: a >= b <=> a - b >= 0, kiểm tra (a-b) âm hay không 


bool optLessOrEqual(QInt& a, QInt& b);
//Input: Nhận 2 biến QInt 
//Output: trả về true nếu a <= b, false nếu a > b 
//Cách hoạt động: a <= b <=> a - b <= 0, kiểm tra (a-b) có bằng 0 hoặc âm hay không 




bool optEqual(QInt& a, QInt& b);
//Input: Nhận 2 biến QInt 
//Output: nếu a == b thì trả về true, ngược lại trả về false
//Cách hoạt động: so sánh lần lượt từng phần phần tử tương ứng của 2 mảng



void optAssign(QInt& dest, QInt& src);
//Input: Nhận 2 biến QInt 
//Output: hàm không có giá trị trả về
//Cách hoạt động: gán lần lượt từng phần phần tử tương ứng của mảng sau(QInt src) cho mảng trước (QInt dest)




