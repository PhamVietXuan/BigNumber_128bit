#pragma once
#include <iostream>
#include <vector>
using namespace std;

class Tokenizer
{
public:
	//Hàm dùng để tách 1 chuỗi thành các chuỗi con nếu chúng cách nhau bởi 'seperator'
	static vector<string> Parse(string line, string seperator);
};

