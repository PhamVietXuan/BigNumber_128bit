#pragma once

#include <iostream>
#include <sstream> //stringstream
using namespace std;

struct QInt
{
	int data[4];
};

int SetBit1(int x, int i);
//Input s? nguyên dích x và i là bi?n v? trí
//Output s? nguyên x du?c set bit 1 vào v? trí i
//Dùng ki thu?t &

int SetBit0(int x, int i);
//Input s? nguyên dích x và i là bi?n v? trí
//Output s? nguyên x du?c set bit 0 vào v? trí i
//Dùng ki thu?t &

int GetBit(int x, int i);
//Input s? nguyên dích x và i là bi?n v? trí
//Output bit t?i v? trí i c?a s? nguyên x
//Dùng ki thu?t OR

void InitQInt(QInt& x);
//Input s? Qint x
//Kh?i t?o giá tri 0 cho bi?n x

void ScanQInt(string str, QInt& x);
//Input: ki?u string là d? li?u và bi?n dích x
//K?t h?p v?i hàm d?c d? li?u d? dua d? li?u vào 1 bi?n Qint x

void PrintQInt(QInt x);
//Input s? Qint x
//In Qint x ra màn hình

string QIntToString(QInt x);
//Input s? Qint x
//Output d?ng string c?a bi?n QInt
//Chuy?n bi?n Qint v? d?ng string

void StringToQInt(QInt& x, string other);
//Input s? Qint x và bi?n string là d? li?u
//Chuy?n bi?n string v? Qint

string ToString(QInt &instance);
//Input s? Qint x
//Output d?ng string c?a bi?n QInt
//Chuy?n bi?n Qint v? d?ng string thông qua ki?u tr? v?

ostream& operator<<(ostream& writer, QInt &instance);
//Input: bi?n QInt
//Toán t? du?c n?p ch?ng d? dua d? li?u t? Qint vào b? d?m