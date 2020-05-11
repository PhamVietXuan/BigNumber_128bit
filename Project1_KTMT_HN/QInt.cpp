#include "QInt.h"


int GetBit(int x, int i)
{
	return (x >> (31 - i)) & 1;
}

int SetBit1(int X, int i)
{
	return (X | (1 << (31 - i)));
}

int SetBit0(int X, int i)
{
	return (X | (0 << (31 - i)));
}

void InitQInt(QInt& x)
{
	for (int i = 0; i < 4; i++) x.data[i] = 0;
}

void ScanQInt(string str, QInt& x)
{
	InitQInt(x);

	if (str.length() > 128) { cout << "Vuot qua 128 bit" << endl; return; }

	while ((int)str.length() < 128) str = "0" + str;

	for (int i = 0; i < 128; i++)
	{
		if (str[i] == '1')
			x.data[i / 32] = SetBit1(x.data[i / 32], i % 32);
	}
}

void PrintQInt(QInt x)
{
	cout << endl;

	for (int i = 0; i < 128; i++)
	{
		if (i % 32 == 0) cout << endl;
		cout << GetBit(x.data[i / 32], i % 32);
	}
	cout << endl;
}

string QIntToString(QInt x)
{
	stringstream writer;

	for (int i = 0; i < 128; i++)
	{
		writer << GetBit(x.data[i / 32], i % 32);
	}

	return writer.str();
}


void StringToQInt(QInt& x, string other)	//We will update this to operator= later
{
	ScanQInt(other, x);
}

string ToString(QInt &instance)
{
	string result = "";

	for (int i = 0; i < 128; i++)
	{
		result += GetBit(instance.data[i / 32], i % 32) + 48;	//+48 because of '0'(48) in ASCII table
	}

	return result;
}

ostream& operator<<(ostream& writer, QInt &instance)
{
	writer << ToString(instance);
	return writer;
}