#include "ReadFromFile.h"

void InitInstruction(Instruction& instance)
{
	instance.base1st = instance.base2nd = instance.arg1  = instance.arg2 = instance.opt = "";
}

Instruction ReturnInstruction(string line)
{
	Instruction instance;
	InitInstruction(instance);

	//Tokenize a data line into a vector<> data
	vector<string> data = Tokenizer::Parse(line, " ");

	//Bring data into 'instruction'
	instance.base1st = data[0];

	if ((data[1] == "2" || data[1] == "16" || data[1] == "10") && is_2Ngoi_Operator(data[2]) != true) 
	{
		instance.base2nd = data[1];
		instance.arg1 = data[2];
	}
	else if (data[1] == "~")
	{
		instance.opt = data[1];
		instance.arg1 = data[2];
	}
	else
	{
		//If not, this is an + - * / >> << AND OR XOR
		instance.arg1 = data[1];
		instance.arg2 = data[3];

		if (is_2Ngoi_Operator(data[2]))
		{
			instance.opt = data[2];
		}
		else
		{
			cout << "Error on data";
			exit(EXIT_FAILURE);
		}
	}

	return instance;
}

string Execute(Instruction &instance)
{
	if (ValidCheck(instance) == true)	//We put ValidCheck here instead of in other functions for 'Execute' function's REUSABILITY
	{
		//1. INITIALIZE
		QInt arg1QINT, arg2QINT;
		InitQInt(arg1QINT);
		InitQInt(arg2QINT);

		//2. CONVERTING PART

		if (instance.base2nd != "")
		{
			if (instance.base1st == instance.base2nd)
				return instance.arg1;	//do nothing

			else if (instance.base1st == "2" && instance.base2nd == "10")
			{
				StringToQInt(arg1QINT, instance.arg1);
				return BintoDec(arg1QINT);
			}

			else if (instance.base1st == "2" && instance.base2nd == "16")
			{
				StringToQInt(arg1QINT, instance.arg1);
				return BintoHex(arg1QINT);
			}

			else if (instance.base1st == "10" && instance.base2nd == "2")
				return QIntToString(DectoBin(instance.arg1));

			else if (instance.base1st == "10" && instance.base2nd == "16")
				return DectoHex(instance.arg1);

			else if (instance.base1st == "16" && instance.base2nd == "2")
				return QIntToString(HexToBin(instance.arg1));

			else if (instance.base1st == "16" && instance.base2nd == "10")
				return BintoDec(HexToBin(instance.arg1));

		}
		else
		{
			//3. EVALUATING PART (+ - ...)

			//3a. CONVERT TO QINT

			if (instance.base1st == "2")
			{
				StringToQInt(arg1QINT, instance.arg1);
				StringToQInt(arg2QINT, instance.arg2);
			}
			else if (instance.base1st == "10")
			{
				arg1QINT = DectoBin(instance.arg1);
				arg2QINT = DectoBin(instance.arg2);
			}
			else if (instance.base1st == "16")
			{
				arg1QINT = HexToBin(instance.arg1);
				arg2QINT = HexToBin(instance.arg2);
			}

			//3b. CALCULATE (ON QINT)
			return OperatorCaller(instance.base1st, arg1QINT, arg2QINT, instance.opt);
		}
	}
	else
	{
		return "Invalid data line";
	}
}

//Because the number of 'Instruction' can be very big. So we should read 1 line and execute it then we read the next.
//This works like a machine: Receive instruction --> Execute that -> Receive next instruction
void ReadInstructionAndExecute(string file_name)
{
	//1. FILE INPUT PART
	ifstream fileStream(file_name, ios::in);	cout << "Input file: " + file_name << endl;

	if (!fileStream)
	{
		cout << "Khong doc duoc file\n";
		exit(EXIT_FAILURE);
	}

	//2. FILE OUT PART 
	ofstream writer("output.txt", ios::out);


	//3. PROCESSING PART
	string line;

	while (!fileStream.eof())
	{
		getline(fileStream, line, '\n');

		if (line != "")
		{
			//We create an instruction from a data line. Then execute it

			Instruction instance = ReturnInstruction(line);;
			string result = Execute(instance);
			writer << result << endl;
		}
		else
		{
			writer << "empty line" << endl;
		}
	}

	//4. CLOSE FILE
	cout << "Successfully writen in 'output.txt'" << endl;
	fileStream.close();
	writer.close();
}

bool ValidCheck(Instruction &instance)
{
	//1. VALID BASEs
	if (instance.base1st != "2" && instance.base1st != "10" && instance.base1st != "16") { cout << "Found error at: invalid base1st" << endl; return false; }
	if (instance.base2nd != "2" && instance.base2nd != "10" && instance.base2nd != "16" && instance.base2nd != "") { cout << "Found error at: invalid base2nd" << endl; return false; }

	//2. VALID ARGUMENTs
	if (instance.arg1 == "") { cout << "Found error at: empty arg1" << endl; return false; }	//BASE1ST keeps ARG1 never empty

	if (instance.base1st == "2" && instance.arg1.length() > 128) { cout << "Found error at: maximum (hex)arg1 string length" << endl; return false; }
	if (instance.base2nd == "2" && instance.arg2.length() > 128) { cout << "Found error at: maximum (hex)arg2 string length" << endl; return false; }

	if (instance.base1st == "10" && instance.arg1.length() > 38) { cout << "Found error at: maximum (hex)arg1 string length" << endl; return false; }
	if (instance.base2nd == "10" && instance.arg2.length() > 38) { cout << "Found error at: maximum (hex)arg2 string length" << endl; return false; }

	if (instance.base1st == "16" && instance.arg1.length() > 32) { cout << "Found error at: maximum (hex)arg1 string length" << endl; return false; }
	if (instance.base2nd == "16" && instance.arg2.length() > 32) { cout << "Found error at: maximum (hex)arg2 string length" << endl; return false; }

	//3. VALID OPERATOR
	bool hasOPT = false;

	if (is_2Ngoi_Operator(instance.opt) || instance.opt == "~")
		hasOPT = true;

	//IF hasOPT, only have 1base but still have to check 2 argument
	if (hasOPT)
	{
		if (instance.opt != "~" && ((instance.base2nd != "" && instance.arg2 != "") || (instance.base2nd == "" && instance.arg2 == ""))) { cout << "Found error at: conflict arg2-base2nd " << endl; return false; }	//Conflict between them
		if (instance.base2nd == instance.opt) { cout << "Found error at: base2nd and opt: " << endl; return false; }	//this has to be one ON and one OFF

		if (instance.base1st == "2")
		{
			while ((int)instance.arg1.length() < 128) instance.arg1 = "0" + instance.arg1;	//ADD BIT 0 TO MAKE SURE IT 128 IN LENGTH
			
			for (int i = 0; i < (int)instance.arg1.length(); i++)
				if (instance.arg1[i] != '0' && instance.arg1[i] != '1') { cout << "Found error at: hasOPT-bin-arg1" << endl; return false; }

			//When ror rol << >>, 2 arg may not be the same base
			if (instance.opt != "ror" && instance.opt != "rol" && instance.opt != ">>" && instance.opt != "<<")
			{
				while ((int)instance.arg2.length() < 128) instance.arg2 = "0" + instance.arg2;	//ADD BIT 0 TO MAKE SURE IT 128 IN LENGTH
				
				for (int i = 0; i < (int)instance.arg2.length(); i++)
					if (instance.arg2[i] != '0' && instance.arg2[i] != '1') { cout << "Found error at: hasOPT-bin-arg2" << endl; return false; }
			}
			else //arg2 is base 10 by default
			{
				int i = 0;
				for (; i < (int)instance.arg2.length(); i++)
					if (instance.arg2[i] < '0' || instance.arg2[i] > '9') { cout << "Found error at: hasOPT-dec-arg2" << endl; return false; }
			}
		}

		//remember to check minus sign '-' at arg[0]
		//dec 0->9
		if (instance.base1st == "10")
		{
			int i = 0;
			if (instance.arg1[0] == '-') i = 1;

			for (; i < (int)instance.arg1.length(); i++)
				if (instance.arg1[i] < '0' || instance.arg1[i] > '9') { cout << "Found error at: hasOPT-dec-arg1" << endl; return false; }

			//When ror rol << >>, 2 arg may not be the same base
			if (instance.opt != "ror" && instance.opt != "rol" && instance.opt != ">>" && instance.opt != "<<")
			{
				i = 0;
				if (instance.arg2[0] == '-') i = 1;
				for (; i < (int)instance.arg2.length(); i++)
					if (instance.arg2[i] < '0' || instance.arg2[i] > '9') { cout << "Found error at: hasOPT-dec-arg2" << endl; return false; }
			}
			else //arg2 is base 10 by default
			{
				i = 0;
				for (; i < (int)instance.arg2.length(); i++)
					if (instance.arg2[i] < '0' || instance.arg2[i] > '9') { cout << "Found error at: hasOPT-dec-arg2" << endl; return false; }
			}
		}

		//hex 0->9 && A->F
		if (instance.base1st == "16")
		{
			int i = 0;
			if (instance.arg1[0] == '-') i = 1;
			if (instance.arg2[0] == '-') i = 1;

			for (; i < (int)instance.arg1.length(); i++)
			{
				if ((instance.arg1[i] < '0' || instance.arg1[i] > '9') &&
					(instance.arg1[i] < 'A' || instance.arg1[i] > 'F'))
				{
					cout << "Found error at: hasOPT-hex-arg1 " << endl;
					return false;
				}
			}

			//When ror rol << >>, 2 arg may not be the same base
			if (instance.opt != "ror" && instance.opt != "rol" && instance.opt != ">>" && instance.opt != "<<")
			{
				i = 0;

				for (; i < (int)instance.arg2.length(); i++)
				{
					if ((instance.arg2[i] < '0' || instance.arg2[i] > '9') &&
						(instance.arg2[i] < 'A' || instance.arg2[i] > 'F'))
					{
						cout << "Found error at: hasOPT-hex-arg2 " << endl;
						return false;
					}
				}
			}
			else //arg2 is base 10 by default
			{
				i = 0;
				for (; i < (int)instance.arg2.length(); i++)
					if (instance.arg2[i] < '0' || instance.arg2[i] > '9') { cout << "Found error at: hasOPT-dec-arg2" << endl; return false; }
			}
		}

	}
	else
	{
		//bin, check 0,1
		if (instance.base1st == "2")
		{
			while ((int)instance.arg1.length() < 128) instance.arg1 = "0" + instance.arg1;	//ADD BIT 0 TO MAKE SURE IT 128 IN LENGTH

			for (int i = 0; i < (int)instance.arg1.length(); i++)
				if (instance.arg1[i] != '0' && instance.arg1[i] != '1') { cout << "Found error at: nonOPT-bin-arg1" << endl; return false; }
		}

		if (instance.base2nd == "2")
		{
			while ((int)instance.arg2.length() < 128) instance.arg2 = "0" + instance.arg2;	//ADD BIT 0 TO MAKE SURE IT 128 IN LENGTH

			for (int i = 0; i < (int)instance.arg2.length(); i++)
				if (instance.arg2[i] != '0' && instance.arg2[i] != '1') { cout << "Found error at: nonOPT-bin-arg2" << endl; return false; }
		}

		//remember to check minus sign '-' at arg[0]
		//dec 0->9
		if (instance.base1st == "10")
		{
			int i = 0;
			if (instance.arg1[0] == '-') i = 1;
			for (; i < (int)instance.arg1.length(); i++)
				if (instance.arg1[i] < '0' || instance.arg1[i] > '9') { cout << "Found error at: nonOPT-dec-arg1" << endl; return false; }
		}

		if (instance.base2nd == "10")
		{
			int i = 0;
			if (instance.arg2[0] == '-') i = 1;
			for (; i < (int)instance.arg2.length(); i++)
				if (instance.arg2[i] < '0' || instance.arg2[i] > '9') { cout << "Found error at: nonOPT-dec-arg2" << endl; return false; }
		}

		//hex 0->9 && A->F
		if (instance.base1st == "16")
		{
			int i = 0;
			if (instance.arg1[0] == '-') i = 1;

			for (; i < (int)instance.arg1.length(); i++)
			{
				if ((instance.arg1[i] < '0' || instance.arg1[i] > '9') &&
					(instance.arg1[i] < 'A' || instance.arg1[i] > 'F'))
				{
					cout << "Found error at: nonOPT-hex-arg1 " << endl;
					return false;
				}
			}
		}

		if (instance.base2nd == "16")
		{
			int i = 0;
			if (instance.arg2[0] == '-') i = 1;

			for (; i < (int)instance.arg2.length(); i++)
			{
				if ((instance.arg2[i] < '0' || instance.arg2[i] > '9') &&
					(instance.arg2[i] < 'A' || instance.arg2[i] > 'F'))
				{
					cout << "Found error at: nonOPT-hex-arg2 " << endl;
					return false;
				}
			}
		}

	}


	//Valid input
	return true;
}

bool is_2Ngoi_Operator(string c)	//NOT OPERATOR '~' IS 1_Ngoi OPERATOR
{
	if (c == "+" || c == "-" || c == "*" || c == "/" ||
		c == "ror" || c == "rol" || c == ">>" || c == "<<" ||
		c == "&" || c == "|" || c == "^" ||
		c == "==" || c == ">" || c == ">=" || c == "<" || c == "<=" )
		return true;
	return false;
}

string OperatorCaller(string base, QInt& arg1, QInt& arg2, string& opt)
{
	//1. Get a boolean value

	string BooleanResult = "";

	if (opt == "==")
		return BoolToString(optEqual(arg1, arg2));
	else if (opt == ">")
		return BoolToString(optBiggerThan(arg1, arg2));
	else if (opt == ">=")
		return BoolToString(optBiggerOrEqual(arg1, arg2));
	else if (opt == "<")
		return BoolToString(optLessThan(arg1, arg2));
	else if (opt == "<=")
		return BoolToString(optLessOrEqual(arg1, arg2));

	//2. Get a QInt value

	QInt result; InitQInt(result);

	if (opt == "+")
		result = optCong(arg1, arg2);
	else if (opt == "-")
		result = optTru(arg1, arg2);
	else if (opt == "*")
		result = optNhan(arg1, arg2);
	else if (opt == "/")
		result = optChiaLayNguyen(arg1, arg2);
	else if (opt == ">>")
		result = optDichPhai(arg1, QIntToInt(arg2));
	else if (opt == "<<")
		result = optDichTrai(arg1, QIntToInt(arg2));
	else if (opt == "ror")
		result = optROR(arg1, QIntToInt(arg2));
	else if (opt == "rol")
		result = optROL(arg1, QIntToInt(arg2));
	else if (opt == "&")
		result = optAND(arg1, arg2);
	else if (opt == "|")
		result = optOR(arg1, arg2);
	else if (opt == "^")
		result = optXOR(arg1, arg2);
	else if (opt == "~")
		result = optNOT(arg1);

	//3. RETURN RESULT
	if (base == "2")
		return QIntToString(result);
	else if (base == "10")
		return BintoDec(result);
	else if (base == "16")
		return BintoHex(result);
}

string BoolToString(bool val)
{
	if (val == true) return "true";
	return "false";
}

int QIntToInt(QInt x)
{
	int res = stoi(BintoDec(x));
	return res;
}

