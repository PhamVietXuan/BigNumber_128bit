#include "Tokenizer.h"

vector<string> Tokenizer::Parse(string line, string seperator)
{
	vector<string> tokens;

	int startPos = 0;
	size_t foundPos = line.find(seperator, startPos);

	while (foundPos != string::npos)	//Still found
	{
		int count = foundPos - startPos;
		string token = line.substr(startPos, count);
		tokens.push_back(token);

		//Update startPos value
		startPos = foundPos + seperator.length();
	
		//Keep on finding
		foundPos = line.find(seperator, startPos);
	}

	//Handle the last element in the given string
	int count = line.length() - startPos;
	string token = line.substr(startPos, count);
	tokens.push_back(token);

	return tokens;
}