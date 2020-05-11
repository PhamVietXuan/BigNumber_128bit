#include <iostream>
#include "ReadFromFile.h"
#include "Qfloat.h"
int main(int argc, char** argv)
{
	if (argc < 4)
	{
		cout << "Thieu Tham So. Moi nhap lai.";
		return 0;
	}
	int type = argv[3][0];
	string inputFile = argv[1];

	string outputFile = argv[2];

	if (type == '1') {//type=1: Xử lý Qint
		cout << "==============================================================================" << endl;
		cout << "                           DANG XU LY. VUI LONG CHO!\n";
		string fileName = inputFile;
		ReadInstructionAndExecute(fileName);
		cout << "\n                XU LY XONG. KET QUA DUOC LUU TRONG FILE: " << outputFile << endl;
		cout << "==============================================================================" << endl;
	}
	else if (type == '2')
	{
		
		ifstream fin;
		fin.open(inputFile);

		ofstream fout;
		fout.open(outputFile);
		cout << "==============================================================================" << endl;
		cout << "                           DANG XU LY. VUI LONG CHO!";
		while (!fin.eof())
		{
			Qfloat num;
			int radix1, radix2;
			string bigNum;
			fin >> radix1 >> radix2 >> bigNum;
			if (radix1 == 10 && radix2 == 2)
			{
				
				num.ScanQfloat(10, bigNum);
				fout << num.PrintQfloat(2) << endl;
				
			}
			else if (radix1 == 2 && radix2 == 10)
			{
				
				num.ScanQfloat(2, bigNum);
				fout << num.PrintQfloat(10) << endl;
				
			}
		}
		cout << "\n                XU LY XONG. KET QUA DUOC LUU TRONG FILE: " << outputFile<<endl;
		cout << "==============================================================================" << endl;
	}
	return 0;
}
