#include "ConvertingPart.h"




void XuatQInt(QInt a)
{
	int tmp;
	for (int i = 0; i < 128; i++)
	{
		tmp = GetBit(a.data[i / 32], i % 32);
		cout << tmp;
	}
	cout << endl;
}

QInt DaoBit(QInt X)
{
	QInt temp = { 0,0,0,0 };
	for (int i = 0; i < 128; i++)
	{
		int bit = GetBit(X.data[i / 32], i % 32);
		if (bit == 0)
			temp.data[i / 32] = SetBit1(temp.data[i / 32], i % 32);
	}
	return temp;
}

int DaoBit2(int x)
{
	int temp = 0;
	for (int i = 0; i < 32; i++)
	{
		if (GetBit(x, i) == 0)
			temp = SetBit1(temp, i);
	}
	return temp;
}

QInt Bu2(QInt bit) //Dao bit + 1 
{
	QInt temp = DaoBit(bit);
	for (int i = 127; i > 0; i--)
	{
		if (GetBit(temp.data[i / 32], i % 32) == 1)
		{
			temp.data[i / 32] = SetBit0(temp.data[i / 32], i % 32);
		}
		else
		{
			temp.data[i / 32] = SetBit1(temp.data[i / 32], i % 32);
			i = 0;
		}
	}
	temp.data[0] = SetBit1(temp.data[0], 0);//Set bit dấu = 1
	return temp;
}

void chia2(string& s)// chia tu trai sang phai
{
	int phannguyen = 0;
	string temp = "";
	int contro = 0;
	while (contro < (int)s.length())
	{
		if (phannguyen < 2)
			phannguyen = phannguyen * 10 + int(s[contro++] - '0');//phan nguyen nho hon 2 tiep tuc lay them 1 so dua vao phan nguyen
		temp = temp + char((phannguyen / 2) + '0');//them phan nguyen chia duoc cua phep chia vao chuoi tam
		phannguyen %= 2;
	}
	while (temp[0] == 48)
		temp.erase(0, 1);
	s = temp;//phan nguyen cua choi ban dau sao khi chia 2
}

QInt  DectoBin(string s)
{
	QInt bit = { 0,0,0,0 };
	
	int sign = 0;// Bit dau duong :0 , am:1
	if ((s[0] == '-'))
	{
		sign = 1;
		s.erase(0, 1);//xoa ki tu '-'
	}
	int vitri = 127;
	while (s.length() > 1 || s.length() == 1 && s[0] != '0')
	{
		if (int(s[s.length() - 1]) % 2 == 1)
			bit.data[vitri / 32] = SetBit1(bit.data[vitri / 32], vitri % 32);
		vitri--;

		chia2(s);
	}
	if (sign == 1)
		return Bu2(bit);
	else
		return bit;
}

// Chuoi nhan cho 2
string Nhan2(string s)
{
	string kq = "";
	int length = s.length();
	int contro = length - 1;
	int nho = 0;
	int giatri = 0;
	while (contro >= 0)
	{
		giatri = int(s[contro--] - '0') * 2 + nho;
		if (giatri >= 10)
		{
			nho = 1;
		}
		else
		{
			nho = 0;
		}
		kq = char((giatri % 10) + '0') + kq;
	}
	if (nho == 1)
	{
		kq = '1' + kq;
	}
	return  kq;
}

// 2 luy thua n
string LuyThua2(int n)
{
	string tmp = "1";
	if (n == 0)
	{
		return tmp;
	}
	else
	{
		for (int i = 1; i <= n; i++)
		{

			string gtri = Nhan2(tmp);
			tmp = gtri;

		}
	}
	return tmp;
}

void CanBangDoDai2Chuoi(string& s1, string& s2)
{
	int length1 = s1.length();
	int length2 = s2.length();
	if (length1 > length2)
	{
		int chenhlech = length1 - length2;
		for (int i = 0; i < chenhlech; i++)
		{
			s2 = '0' + s2;
		}
	}
	else if (length2 > length1)
	{
		int chenhlech = length2 - length1;
		for (int i = 0; i < chenhlech; i++)
		{
			s1 = '0' + s1;
		}
	}
}

string CongChuoi(string s1, string s2)
{
	CanBangDoDai2Chuoi(s1, s2);
	int length = s1.length();
	int contro = length - 1;
	int nho = 0;
	string kq = "";
	while (contro >= 0)
	{
		int giatri = int(s1[contro] - '0') + int(s2[contro] - '0') + nho;
		if (giatri < 10)
			nho = 0;
		else
			nho = 1;
		kq = char((giatri % 10) + '0') + kq;
		contro--;
	}
	if (nho == 1)
	{
		kq = '1' + kq;
	}
	return kq;
}

string TruChuoi(string a, string b)
{
	CanBangDoDai2Chuoi(a, b);
	int length = a.length();
	int contro = length - 1;
	int muon = 0;
	int tri = 0;
	string kq = "";
	while (contro >= 0)
	{
		tri = int(a[contro] - '0') - int(b[contro] - '0') - muon;
		if (tri < 0)
		{
			tri = int(a[contro] - '0') + 10 - int(b[contro] - '0') - muon;
			muon = 1;
		}
		else
		{
			muon = 0;
		}
		char temp = char(tri + '0');
		kq = temp + kq;
		contro--;
	}
	return kq;
}

string BintoDec(QInt x)
{
	int mu, contro;
	string kq = "0";
	string tmp = "";

	if (GetBit(x.data[0], 0) != 1)
	{
		mu = 0;
		contro = 127;

		while (contro >= 0)
		{
			int bit = GetBit(x.data[contro / 32], contro % 32);
			if (bit == 1)
			{
				tmp = LuyThua2(mu);
			}
			kq = CongChuoi(kq, tmp);
			tmp = "";
			mu++;
			contro--;
		}
		return kq;
	}
	else
	{
		contro = 1;
		mu = 126;
		kq = LuyThua2(127);
		while (contro < 128)
		{
			int bit = GetBit(x.data[contro / 32], contro % 32);
			if (bit == 1)
			{
				tmp = LuyThua2(mu);
			}
			kq = TruChuoi(kq, tmp);
			tmp = "";
			mu--;
			contro++;
		}
		while (kq[0] == 48)
			kq.erase(0, 1);
		kq = '-' + kq;
		return kq;
	}
}

//Chuyen doi theo he co so tong quat voi 4 bit
int ChuyenDoi(string s)
{
	int mu = 3;
	int gtri = 0;
	for (int i = 0; i < 4; i++)
	{
		if (s[i] == '1')
			gtri += (int)pow(2, mu);
		mu--;
	}
	return gtri;
}

string BintoHex(QInt x)
{
	int dem = 0;//so phan tu da them vao chuoi tam
	string kq = "";
	string tmp = "";//chuoi tam chua 4 bit
	int giatri = 0;
	for (int i = 0; i < 129; i++)
	{
		if (dem == 4)
		{
			giatri = (ChuyenDoi(tmp));
			switch (giatri)
			{
			case 0:
				kq += '0';
				break;
			case 1:
				kq += '1';
				break;
			case 2:
				kq += '2';
				break;
			case 3:
				kq += '3';
				break;
			case 4:
				kq += '4';
				break;
			case 5:
				kq += '5';
				break;
			case 6:
				kq += '6';
				break;
			case 7:
				kq += '7';
				break;
			case 8:
				kq += '8';
				break;
			case 9:
				kq += '9';
				break;
			case 10:
				kq += 'A';
				break;
			case 11:
				kq += 'B';
				break;
			case 12:
				kq += 'C';
				break;
			case 13:
				kq += 'D';
				break;
			case 14:
				kq += 'E';
				break;
			case 15:
				kq += 'F';
				break;
			}
			dem = 0;
			tmp = "";
		}

		int bit = GetBit(x.data[i / 32], i % 32);
		tmp += char(bit + '0');
		dem++;

	}
	while (kq[0] == 48)
		kq.erase(0, 1);
	return kq;
}

void chia16(string& s, int& phandu)
{
	int phannguyen = 0;
	string temp = "";
	int contro = 0;
	while (contro < (int)s.length())
	{
		if (phannguyen < 16)
			phannguyen = phannguyen * 10 + int(s[contro++] - '0');
		temp = temp + char((phannguyen / 16) + '0');
		phannguyen %= 16;
	}
	while (temp[0] == 48)
		temp.erase(0, 1);
	s = temp;
	phandu = phannguyen;
}


string DectoHex(string s)
{
	int length = s.length();
	string kq = "";
	char tmp;
	int phandu;
	while (s.length() > 1 || s.length() == 1 && s[0] != '0')
	{
		chia16(s, phandu);
		switch (phandu)
		{
		case 0:
			tmp = '0';
			break;
		case 1:
			tmp = '1';
			break;
		case 2:
			tmp = '2';
			break;
		case 3:
			tmp = '3';
			break;
		case 4:
			tmp = '4';
			break;
		case 5:
			tmp = '5';
			break;
		case 6:
			tmp = '6';
			break;
		case 7:
			tmp = '7';
			break;
		case 8:
			tmp = '8';
			break;
		case 9:
			tmp = '9';
			break;
		case 10:
			tmp = 'A';
			break;
		case 11:
			tmp = 'B';
			break;
		case 12:
			tmp = 'C';
			break;
		case 13:
			tmp = 'D';
			break;
		case 14:
			tmp = 'E';
			break;
		case 15:
			tmp = 'F';
			break;
		}
		kq = tmp + kq;;
	}
	while (kq[0] == 48)
		kq.erase(0, 1);
	return kq;
}

//Bonus functions, used for operators
//Use dictionary method to map a hex string to a binanary string, and then convert it to QInt type
QInt HexToBin(string s)
{
	string result = "";

	int start = min(s.length() - 1, 32);	//128bit -> max length of hex string is 32

	for (int i = start; i >= 0; i--)
	{
		result = HexTo4Bit(s[i]) + result;
	}

	//MAKE SURE IT 128bit
	while ((int)result.length() < 128) result = "0" + result;

	QInt kq;
	InitQInt(kq);
	StringToQInt(kq, result);
	return kq;
}

int min(int a, int b)
{
	if (a > b) return b;
	return a;
}

string HexTo4Bit(char c)
{
	switch (c)
	{
	case '0':
		return "0000";
	case '1':
		return "0001";
	case '2':
		return "0010";
	case '3':
		return "0011";
	case '4':
		return "0100";
	case '5':
		return "0101";
	case '6':
		return "0110";
	case '7':
		return "0111";
	case '8':
		return "1000";
	case '9':
		return "1001";
	case 'A':
		return "1010";
	case 'B':
		return "1011";
	case 'C':
		return "1100";
	case 'D':
		return "1101";
	case 'E':
		return "1110";
	case 'F':
		return "1111";
	default:
		return "";
	}
}