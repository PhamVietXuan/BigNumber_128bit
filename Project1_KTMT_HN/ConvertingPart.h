#pragma once
#include <iostream>
#include "QInt.h"
using namespace std;

//This part is belong to BUI TRAN HAI HAU

void XuatQInt(QInt a);
//Input: S? QInt
//Output: In ra màn hình s? QInt
//B?ng cách dùng phép &1 d? l?y t?ng bit

QInt DaoBit(QInt X);
//Input: S? QInt
//Output: S? QInt d?o bit c?a nó
//B?ng cách d?o t?ng bit m?t

int DaoBit2(int x);
//Input: S? Int
//Output: S? Int d?o bit c?a nó
//B?ng cách d?o t?ng bit m?t

QInt Bu2(QInt bit);
//Input: S? QInt
//Output: S? QInt bù 2 c?a nó
//B?ng cách d?o bit sau dó c?ng 1


void chia2(string& s);
//Input: chuoi
//Output: gia tri phan nguyen sau khi chia chuoi cho 2
/*Lay tung ky tu so cua chuoi tu trai sang phai dua vao bien phan nguyen
Neu phan nguyen be hon 2 thi lay them vao mot ky tu so lien ke ben phai
Phan nguyen chia cho 2
Luu gia tri nguyen cua phep chia 2 vao bien temp
Tra ve temp 
*/


QInt DectoBin(string s);
//Input: chuoi
//Output: bien Qint
/*Tao bien Qint bit voi cai phan tu bang 0
Xet dau ki tu dau cua chuoi gan cho bien sign roi xoa
Chia 2 chuoi roi xet ki tu cuoi neu le thi setbit 1 
Xet bien sign roi tra ve QInt bit tuong ung
*/



string Nhan2(string s);
//Input: chuoi
//Output: chuoi
/*Nhan tung ki tu choi tu cuoi mang ve dau mang
voi bien nho*/

string LuyThua2(int n);
//Input:bien kieu int 
//Output:chuoi
/*Goi lai ham Nhan2 voi vong lap n-1 */


void CanBangDoDai2Chuoi(string& s1, string& s2);
//Input:2 chuoi
//Output:2 chuoi
//Them ky tu 0 vao dau chuoi co do dai be hon

string CongChuoi(string s1, string s2);
//Input: 2 chuoi
//Output: 1 chuoi
/*Cong tung ky tu cua chuoi s1 voi chuoi s2 tuong ung
 Thuc hien tu ky tu cuoi ve ky tu dau voi bien nho */

string TruChuoi(string a, string b);
//Input: 2 chuoi
//Output: 1 chuoi
/*Tru tung ky tu cua chuoi a voi chuoi b tuong ung
 Thuc hien tu ky tu cuoi ve ky tu dau voi bien muon */

string BintoDec(QInt x);
//Input: bien kieu QInt
//Output: chuoi
/*Xet bit dau cua QInt
Ap dung he co so q tong quat*/


int ChuyenDoi(string s);
//Input: chuoi 4 ky tu tuong ung 4 bit
//Output: bien kieu int
/*Chuyen 4 bit nhi phan ve he thap phan
Ap dung he co so q tong quat */ 

string BintoHex(QInt x);
//Input: bien kieu QInt
//Output: chuoi he thap luc phan
/*Chuyen lan luot moi lan 4 bit tu trai sang phai vao chuoi temp
Chuyen 4 bit luu trong chuoi temp ve he thap phan -> thap luc tuong ung them vao
cuoi chuoi kq
Tra ve chuoi kq */


void chia16(string& s, int& phandu);
//Input:chuoi so chia, bien kieu int
//Output:chuoi nguyen sau khi chia 16 va phan du moi
/*Lay tung ky tu so cua chuoi tu trai sang phai dua vao bien phan nguyen
Neu phan nguyen be hon 16 thi lay them vao mot ky tu so lien ke ben phai
Phan nguyen chia cho 16
Luu gia tri nguyen cua phep chia 16 vao bien temp
Sau khi bien contro di het chuoi phan nguyen con lai se la phan du */

string DectoHex(string s);
//Input: chuoi he thap phan
//Output: chuoi he thaplucphan
/*Chia chuoi cho 16 cho den khi khong thoa dieu kien 
phan du -> chu so he thap luc phan tuong ung them vao dau chuoi kq
Tra ve chuoi kq*/

//Bonus
int min(int a, int b);
//Input 2 s? nguyên a, b
//Output s? nh? hon
//B?ng phép so sánh

string HexTo4Bit(char c);
//Input kí t? C
//Output m?t chu?i là nhóm 4bit h? 2 tuong ?ng v?i kí t? dó h? 16
//Dùng ki thu?t t? di?n và ghép xâu l?i

QInt HexToBin(string s);
//Input m?t string h? 16
//Output: m?t bi?n QInt
//Dùng hàm HexTo4Bit thao tác v?i t?ng kí t? m?t

