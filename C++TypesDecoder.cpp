#include <iostream>
#include <vector>
#include <string>
using namespace std;

#define ifnt else
#define is ==

// This method returns a vector (array) of strings, each string containing one word of the Input string.
vector<string> Tokenize(const string& Input)
{
	vector<string> Result;
	for (int i = 0, j = 0; j < Input.length(); ++i)
	{
		Result.push_back(string());
		while (1)
		{
			if (Input[j] == ' ')
			{ ++j; continue; }

			if (Input[j] == '[' || Input[j] == ']' || Input[j] == '(' || Input[j] == ')' || Input[j] == '*' || Input[j] == '&' || Input[j] == ';')
			{
				if (Result[i].length() != 0)
				{
					Result.push_back(string());
					++i;
				}
				Result[i].push_back(Input[j++]);
				break;
			}
			
			Result[i].push_back(Input[j]);
			
			++j;

			if (j == Input.length())
				break;


		}
	}
	return Result;
}

// Returns index of Target in Source vector if it exists, else returns -1.
template <class Type>
size_t GetTargetIndex(vector<Type> Source, const Type& Target)
{
	vector<Type>::iterator PointerToTarget = std::find(Source.begin(), Source.end(), Target);
	return PointerToTarget == Source.end() ? -1 : std::distance(Source.begin(), PointerToTarget);
}

// Receives a tokenized string and returns a string containing text describing C++ type.
string ParseTypes(vector<string> Tokens, string Identifier)
{
	string Result = Identifier + " is ";
	int i = GetTargetIndex(Tokens, Identifier) + 1;
	if (i is 0)
		return string("Identifier not found.");
	for (;;++i)
	{
		if (Tokens[i] == ")")
		{
			int Temp = i;
			while (1)
			{
				--i;
				if (Tokens[i] == ")")
					while (Tokens[i] != "(")
						--i;

				else if (Tokens[i] == Identifier)
					continue;

				else if (Tokens[i] == "*")
				{
					Result += "pointer to ";
					Tokens[i] = ".";
				}
				else if (Tokens[i] == "&")
				{
					Result += "reference to ";
					Tokens[i] = ".";
				}
				else if (Tokens[i] == "(")
					break;
			}
			i = Temp;
		}

		else if (Tokens[i] == "(")
		{
			Result += "a function ";
			for (;;++i)
			{
				if (Tokens[i] == ")")
				{
					Result += "returning ";
					break;
				}
			}
		}

		else if (Tokens[i] == "[")
		{
			Result += "an array of size ";
			Result += Tokens[++i] + " of ";
		}

		/*else if (Tokens[i] == "]")
			continue;*/

		else if (Tokens[i] == ";")
		{
			while (1)
			{
				--i;
				if (i is -1)
					break;
				
				else if (Tokens[i] == "int")
					Result += "int ";

				else if (Tokens[i] == "float")
					Result += "float ";

				else if (Tokens[i] == "void")
					Result += "void ";

				else if (Tokens[i] == "*")
					Result += "pointer to ";

				else if (Tokens[i] == "&")
					Result += "reference to ";

			}
		}
		if (i is 0)
			break;
	}
	Result[Result.length() - 1] = '.';
	return Result;
}

int main()
{
	string X = "void (*(*f[2])())();";
	cout << X << endl;
	cout << ParseTypes(Tokenize(X), "X") << endl;
	return 0;
}
