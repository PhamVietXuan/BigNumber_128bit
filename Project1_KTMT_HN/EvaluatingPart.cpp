#include "EvaluatingPart.h"

int GetBit_Thu_i(QInt x, int i)
{
	return GetBit(x.data[i / 32], i % 32);
}

void SetBit1_Thu_i(QInt& x, int i)
{
	x.data[i / 32] = SetBit1(x.data[i / 32], i % 32);
}

void SetBit0_Thu_i(QInt& x, int i)
{
	x.data[i / 32] = SetBit0(x.data[i / 32], i % 32);
}

void SetBit_Thu_i(QInt& x, int i, int bit)
{
	if (bit == 0) SetBit0_Thu_i(x, i);
	else SetBit1_Thu_i(x, i);
}

QInt optCong(QInt a, QInt b)
{
	//Khoi tao QInt KQ = 0

	QInt kq;
	InitQInt(kq);

	bool carry = 0; //Biến nhớ
	int sumBit; // lưu tổng các bit
	for (int i = 128-1; i >= 0; i--)
	{
		sumBit = GetBit_Thu_i(a, i) + GetBit_Thu_i(b, i) + carry;

		if ((sumBit & 1) == 0) SetBit0_Thu_i(kq, i);
		else SetBit1_Thu_i(kq, i);

		carry = sumBit >> 1;
	}
	return kq;
}

QInt optTru(QInt a, QInt b)
{
	return optCong(a, optBu2(b));		//Bu2() from ConvertingPart.h
}

QInt optNOT(QInt x)
{
	for (int i = 0; i < 4; i++)
		x.data[i] = ~x.data[i];		//NOT tung bit cua QInt
	return x;
}

QInt optBu2(QInt x)
{
	QInt bitCuoiLa_1;
	InitQInt(bitCuoiLa_1); //Khoi tao =  0
	SetBit1_Thu_i(bitCuoiLa_1, 128 - 1); // 000....0001 set bit 1 vao cuoi cung
	
	//Daobit + 1
	return optCong(optNOT(x), bitCuoiLa_1);
}

QInt optAND (QInt a, QInt b)
{
	QInt kq;
	for (int i = 0; i < 4; i++)
	{
		kq.data[i] = a.data[i] & b.data[i]; // lấy từng phần tử của mảng để AND
	}
	return kq;
}
QInt optOR(QInt a, QInt b)
{
	QInt kq;
	for (int i = 0; i < 4; i++)
	{
		kq.data[i] = a.data[i] | b.data[i];// lấy từng phần tử của mảng để OR
	}
	return kq;
}

QInt optXOR(QInt a, QInt b)
{
	QInt kq;
	for (int i = 0; i < 4; i++)
	{
		kq.data[i] = a.data[i] ^ b.data[i];// lấy từng phần tử của mảng để XOR
	}
	return kq;
}


//Chuyen ve DUONG het de nhan
//Sau do xet dau cho ket qua
//Nhan: (Neu bit cuoi cua b == 1 ) kq = kq + a 
//roi dich trai a, dich phai b
QInt optNhan(QInt a, QInt b)
{
	QInt kq;  InitQInt(kq);
	QInt Mot; InitQInt(Mot); Mot.data[3] = Mot.data[3] | 1;   //Khoi tao QInt = 1;

	bool KiemTraAm = false;

	if ((isNegative(a) && !isNegative(b)) || (!isNegative(a) && isNegative(b)))
	{
		KiemTraAm = true; // kiểm tra 2 số có ngược dấu hay không
	}

	if (isNegative(a))
	{
		a = optNOT(optTru(a,Mot)); // nếu âm thì chuyển về dương
	}

	if (isNegative(b))
	{
		b = optNOT(optTru(b, Mot));// nếu âm thì chuyển về dương
	}

	while(!isEqualZero(b))
	{
		//if  [ (b & 1) - 1] == 0
		if (isEqualZero(optTru(optAND(b, Mot), Mot)))
		{
			//kq = kq + a
			kq = optCong(kq, a);
		}

		//a << 1, b >> 1
		a = optDichTrai(a, 1);
		b = optDichPhai(b, 1);
	}


	if (KiemTraAm == true)
	{
		//kq = ~kq + Mot;// nếu ngược dấu thì chuyển về dạng bù 2
		kq = optCong(optNOT(kq), Mot);
	}

	return kq;
}

//Thuật toán chia
// Khởi tạo kq = 0
// DichTrai[kq,q] (bit 0 của q thành bit 127 của kq)
// Thực hiện kq = kq - m
// Kiểm tra nếu kq < 0 thì trả về kq cũ và q[bit 127] = 0 (không chia được gì)
// Ngược lại thì q[bit 127] = 1, có chia được và không cần trả về kq cũ
// Lặp lại hết độ dài q (128)
QInt optChiaLayNguyen(QInt q, QInt m)
{
	QInt kq; InitQInt(kq); //kq = 0

	if (isEqualZero(q) || isEqualZero(m))	
	{
		return kq;
	}
	else
	{
		QInt Mot; InitQInt(Mot); Mot.data[3] = Mot.data[3] | 1;   //Khoi tao QInt = 1;

		if (isEqualZero(optTru(m, Mot)))	//if b == 1, return ket qua luon
		{
			kq = q;
		}
		else
		{
			//Chuyen ve 2 so duong, sau do xet dau kq
			bool KiemTraAm = false;

			if ((isNegative(q) && !isNegative(m)) || (!isNegative(q) && isNegative(m)))
			{
				KiemTraAm = true;// kiểm tra 2 số có ngược dấu hay không
			}

			if (isNegative(q))
			{
				q = optBu2(q); // nếu âm thì chuyển về dương
			}
			if (isNegative(m))
			{
				m = optBu2(m); // nếu âm thì chuyển về dương
			}

			//Thực hiện thuật toán chia
			int k = 128;
			while (k > 0)
			{
				//1. Dich Trai [kq,q]
				kq = optDichTrai(kq, 1);						//NOTE (1 << 31)) >> 31 sẽ sai vì c dịch phải số học
				kq.data[3] = kq.data[3] | (GetBit_Thu_i(q, 0)); //Đem bit lớn nhất của a qua thành bit nhỏ nhất của kq						
				q = optDichTrai(q, 1);

				//2. Xét kq - m
				kq = optTru(kq, m);

				if (isNegative(kq))
				{
					kq = optCong(kq, m);
				}
				else
				{
					q.data[3] = q.data[3] | 1;
				}

				--k;
			}

			kq = q;

			if (KiemTraAm == true)
			{
				kq = optBu2(kq); // nếu ngược dấu thì chuyển về dạng bù 2
			}
		}
	}

	return kq;
}

//dịch lần lượt từng bit sang trái 
QInt optDichTrai (QInt &a, int number)
{
	if (number <= 0) return a; // kiểm tra giá trị a
	else {
		QInt kq;
		InitQInt(kq);	//Khoi tao bang 0

		for (int i = number; i < 128; i++)
			SetBit_Thu_i(kq, i - number, GetBit_Thu_i(a, i));	//Bit cuoi la bit thu 127
		return kq;
	}
}

//dịch lần lượt từng bit sang phải
QInt optDichPhai(QInt &a, int number)
{
	if (number <= 0) return a; // kiểm tra giá trị a
	else {
		QInt kq;
		InitQInt(kq);	//Khoi tao bang 0

		for (int i = 127; i >= number ; i--)
			SetBit_Thu_i(kq, i, GetBit_Thu_i(a, i - number));	//Bit cuoi la bit thu 127
		return kq;
	}
}

bool optBiggerThan (QInt &a, QInt &b)
{
	QInt kq = optTru(a, b); //nếu A>B thì A-B > 0
	if (isNegative(kq) == 0 && isEqualZero(kq) == 0) return true;
	else return false;
}

bool optLessThan (QInt &a, QInt &b)
{
	QInt kq = optTru(a, b);//nếu A<B thì A-B < 0
	if (isNegative(kq) == 1) return true;
	else return false;
}
bool optBiggerOrEqual (QInt &a, QInt &b)	//>=
{
	QInt kq = optTru(a,b); //nếu A>=B thì A-B >= 0
	if (isNegative(kq) == 1) return false;
	else return true;
}

bool optLessOrEqual (QInt &a, QInt &b)
{
	QInt kq = optTru(a, b); //nếu A<=B thì A-B <= 0
	if (isNegative(kq) == 1 || isEqualZero(kq) == 1) return true;
	else return false;
}

// so sánh từng phần tử của 2 mảng
bool optEqual (QInt &a, QInt &b)
{
	for (int i = 0; i < 4; i++)
	{
		if (a.data[i] != b.data[i]) return false; 
	}
	return true;
}

//Tương tự như dịch phải nhưng bit rơi ra thì lắp vào đầu còn lại của mảng
// Đầu tiên lưu giá trị của bit bị đẩy ra ngoài
// dịch bit sang phải
// gán giá trị của bit bị đẩy ra vào lại mảng
QInt optROR(QInt a, int number)
{

	for (int i = 0; i < number; i++)
	{
		int mem = 1 & a.data[3];
		a = optDichPhai(a, 1);
		SetBit_Thu_i(a, 0, mem);
	}
	return a;
}

//Tương tự như dịch trái nhưng bit rơi ra thì lắp vào đầu còn lại của mảng
// Đầu tiên lưu giá trị của bit bị đẩy ra ngoài
// dịch bit sang trái
// gán giá trị của bit bị đẩy ra vào lại mảng
QInt optROL(QInt a, int number)
{
	for (int i = 0; i < number; i++)
	{
		int mem = (1 << 31) & a.data[0];
		a = optDichTrai(a, 1);
		SetBit_Thu_i(a, 127, mem);
	}
	return a;
}

// kiểm tra lần lượt từng phẩn tử của mảng có bằng 0 hay không
bool isEqualZero(QInt x)
{
	for (int i = 0; i < 4; i++)
	{
		if (x.data[i] != 0) 
		{
			return false;
		}
	}
	return true;
}

// kiểm tra bit dấu có bằng 1 hay không
bool isNegative(QInt x)
{
	if (GetBit_Thu_i(x,0) == 1)
		return true;

	return false;
}

void optAssign(QInt& dest, QInt& src)
{
	for (int i = 0; i < 4; i++)
	{
		dest.data[i] = src.data[i]; //gán từng phần tử tương ứng của 2 mảng
	}
}