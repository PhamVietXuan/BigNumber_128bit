#pragma once

#include "Tokenizer.h"	//Use 'Parse' function to seperate a data string into tokens
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>	//getline
#include "QInt.h"
#include "ConvertingPart.h"
#include "EvaluatingPart.h"

using namespace std;

//Mô hình dữ liệu: base1 base2 arg1 opt arg2
//Khởi tạo trước khi sử dụng
struct Instruction
{
	string base1st;	//He co so dau tien
	string base2nd;	//He co so thu 2
	string arg1;		//So hang dau tien
	string arg2;		//So hang thu 2
	string opt; 		//operator (neu co)
};

void InitInstruction(Instruction& instance);
//Input: Biến instruction mới
//Output biến được khởi tạo
//Khởi tạo rỗng cho từng trường của biến instance

Instruction ReturnInstruction(string line);
//Input: Biến string là dòng dữ liệu đọc từ file
//Output: Một biến instruction bóc tách từ dòng dữ liệu đó
//Dùng các kĩ thuật cắt chuỗi thành các tokens

string Execute(Instruction &instance);
//Mô hình hoạt đông của cương trình là ở đây.
//Input: biến instance
//Output: Kết quả nhận được từ instruction được truyền (gồm cả lỗi)
//Đọc từng trường của instance rồi thực hiện tương ứng 

//Because the number of 'Instruction' can be very big. So we should read 1 line and execute it then we read the next.
//This works like a machine: Receive instruction --> Execute that -> Receive next instruction
void ReadInstructionAndExecute(string file_name);
//Quy trình hoạt động như sau:
//Input: 1 tên file
//Xử lí từng dòng dữ liệu 1 dựa vào hàm string Execute(Instruction &instance);

bool ValidCheck(Instruction &instance);
//Kiếm tra tính hợp lệ của dữ liệu và xử lí ngoại lê (toán tử NOT, >> << ROR ROL)
//Input: 1 instruction
//Output true hoặc false
// Dùng các câu lệnh if như bộ lọc

bool is_2Ngoi_Operator(string c);
//Input: một toán tử
//Output: true hoặc false
//Kiểm tra xem toán tử vừa nhận có phải là toán tử 2 ngôi không

string OperatorCaller(string base, QInt& arg1, QInt& arg2, string& opt);
//Input: Các thành phần của một instruction
//Output: kêt quả tính toán
// Đây là phần có toán tử mới dùng đến. Là hàm tập hợp các hàm toán tử lẻ tẻ lại

string BoolToString(bool val);
//Input: biến bool
//Output: "true" hoặc "false"
//Hàm chuyển kiểu dữ liệu từ bool sang string để in ra màn hình

int QIntToInt(QInt x);
//Input: biến Qint
//Output: giá trị int nếu chuyển thành công
//Chuyển kiểu dữ liêu sang int cho các hàm ROL ROR >> <<