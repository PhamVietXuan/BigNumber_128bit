#pragma once

#include <iostream>
#include <sstream> //stringstream
using namespace std;

struct QInt
{
	int data[4];
};

int SetBit1(int x, int i);
//Input s? nguy�n d�ch x v� i l� bi?n v? tr�
//Output s? nguy�n x du?c set bit 1 v�o v? tr� i
//D�ng ki thu?t &

int SetBit0(int x, int i);
//Input s? nguy�n d�ch x v� i l� bi?n v? tr�
//Output s? nguy�n x du?c set bit 0 v�o v? tr� i
//D�ng ki thu?t &

int GetBit(int x, int i);
//Input s? nguy�n d�ch x v� i l� bi?n v? tr�
//Output bit t?i v? tr� i c?a s? nguy�n x
//D�ng ki thu?t OR

void InitQInt(QInt& x);
//Input s? Qint x
//Kh?i t?o gi� tri 0 cho bi?n x

void ScanQInt(string str, QInt& x);
//Input: ki?u string l� d? li?u v� bi?n d�ch x
//K?t h?p v?i h�m d?c d? li?u d? dua d? li?u v�o 1 bi?n Qint x

void PrintQInt(QInt x);
//Input s? Qint x
//In Qint x ra m�n h�nh

string QIntToString(QInt x);
//Input s? Qint x
//Output d?ng string c?a bi?n QInt
//Chuy?n bi?n Qint v? d?ng string

void StringToQInt(QInt& x, string other);
//Input s? Qint x v� bi?n string l� d? li?u
//Chuy?n bi?n string v? Qint

string ToString(QInt &instance);
//Input s? Qint x
//Output d?ng string c?a bi?n QInt
//Chuy?n bi?n Qint v? d?ng string th�ng qua ki?u tr? v?

ostream& operator<<(ostream& writer, QInt &instance);
//Input: bi?n QInt
//To�n t? du?c n?p ch?ng d? dua d? li?u t? Qint v�o b? d?m