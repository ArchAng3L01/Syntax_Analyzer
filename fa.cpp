
#include <iostream>
#include "fa.h"
// #include "Lexical_Analyzator.h"

using namespace std;

//function for every transitions from every state
FA::FA()
{
	TransitFunction = vector<vector<int>>(4, vector<int>(1024, 3));

	for (int i = '0'; i <= '9'; ++i)
	{
		TransitFunction[0][i] = 1;
		TransitFunction[1][i] = 1;
		TransitFunction[2][i] = 3;
	}

	for (int i = 'a'; i <= 'z'; ++i)
	{
		TransitFunction[0][i] = 2;
		TransitFunction[1][i] = 3;
		TransitFunction[2][i] = 2;
	}

	for (int i = 'A'; i <= 'Z'; ++i)
	{
		TransitFunction[0][i] = 2;
		TransitFunction[1][i] = 3;
		TransitFunction[2][i] = 2;
	}

	TransitFunction[0][(int)('.')] = 1;
	TransitFunction[1][(int)('.')] = 1;
	TransitFunction[2][(int)('.')] = 3;
};

//function for get token from operation symbol
TOKEN_ELEM Get_Operation_Symbol(
	char c, string &str, vector<char> &Operat_Symb,
	vector<string> &KeyWords, int &current_state)
{
	TOKEN_ELEM new_token;

	for (auto Op_S : Operat_Symb)
	{
		if (c == Op_S && Op_S == '=')
		{
			current_state = 0;
			str = "";
			new_token.Type_of_Token = "Assign_Operation";
			new_token.Name_of_Token = c;

			return new_token;
		}
		else if (c == Op_S && Op_S == '+')
		{

			current_state = 0;
			str = "";
			new_token.Type_of_Token = "Plus_Operation";
			new_token.Name_of_Token = c;

			return new_token;
		}
		else if (c == Op_S && Op_S == '-')
		{

			current_state = 0;
			str = "";
			new_token.Type_of_Token = "Minus_Operation";
			new_token.Name_of_Token = c;

			return new_token;
		}
	}
}

//function for get token from separate symbols
TOKEN_ELEM Get_not_oper_symb(
	char c, string &str, vector<char> &N_Operat_Symb,
	vector<string> &KeyWords, int &current_state)
{

	TOKEN_ELEM new_token;

	for (auto N_Op_S : N_Operat_Symb)
	{
		if (c == N_Op_S && N_Op_S == ',')
		{

			current_state = 0;
			str = "";
			new_token.Type_of_Token = "Comma";
			new_token.Name_of_Token = c;

			return new_token;
		}
		else if (c == N_Op_S && N_Op_S == '(')
		{

			current_state = 0;
			str = "";
			new_token.Type_of_Token = "Left_Bracket";
			new_token.Name_of_Token = c;

			return new_token;
		}
		else if (c == N_Op_S && N_Op_S == ')')
		{

			current_state = 0;
			str = "";
			new_token.Type_of_Token = "Right_Bracket";
			new_token.Name_of_Token = c;

			return new_token;
		}
	}
}

//function for set a need type of token of keywords
void Set_key_type_o_token(string& s,
	TOKEN_ELEM& new_token) {
	if (s == "INTEGER") {
		new_token.Type_of_Token = "INTEGER";
	}
	if (s == "REAL") {
		new_token.Type_of_Token = "REAL";
	}
	if (s == "PROGRAM") {
		new_token.Type_of_Token = "PROGRAM";
	}
	if (s == "END") {
		new_token.Type_of_Token = "END";
	}
	if (s == "ITOR") {
		new_token.Type_of_Token = "ITOR";
	}
	if (s == "RTOI") {
		new_token.Type_of_Token = "RTOI";
	}
}


// for determine which TOKEN_ELEM we are get on current step
TOKEN_ELEM FA::Get_Current_Token(string &str)
{

	// current state, from where we're start
	int current_state = 0;

	// line with reading words
	string s = "";

	TOKEN_ELEM new_token;

	for (auto d : str)
	{
		if (Do_we_have_oper_symb(d)) {
			new_token = Get_Operation_Symbol(d, s,
				Operations_Symbols, KeyWords, current_state);
			return new_token;
		}

		if (Do_we_have_not_oper_symb(d)) {
			new_token = Get_not_oper_symb(d, s,
				Not_Operations_Symbols, KeyWords, current_state);
			return new_token;
		}

		if (d == ' ' || d == '\t' || d == '\n')
		{
			
			if (current_state == 2)
			{
				new_token.Type_of_Token = "Id";

				for (auto k : KeyWords)
				{
					if (s == k)
					{
						//new_token.Type_of_Token = "KeyWord";
						Set_key_type_o_token(s,
							new_token);
					}
				}
				new_token.Name_of_Token = s;

				return new_token;
			}
			if (current_state == 1)
			{
				bool flag = false;
				for (int i = 0; i < s.size(); ++i)
				{
					if (s[i] == '.')
					{
						flag = true;
					}
				}
				if (flag)
				{
					new_token.Type_of_Token = "RealConst";
					new_token.Name_of_Token = s;
				}
				else
				{
					new_token.Type_of_Token = "Const";
					new_token.Name_of_Token = s;
				}

				return new_token;
			}
			if (current_state == 3)
			{
				new_token.Type_of_Token = "ERROR";
				new_token.Name_of_Token = s;

				return new_token;
			}
			current_state = 0;
			s = "";
		}
		else
		{
			current_state = TransitFunction[current_state][d];
			s += d;
		}
	}

	// ���� ����� ���� ����������� �� ��������� �� � �������,
	// �.�. �� ��� �� �� ������� => ������������ ���
	if (current_state != 0)
	{
		//TOKEN_ELEM new_token;
		if (current_state == 2)
		{
			new_token.Type_of_Token = "Id";

			for (auto k : KeyWords)
			{
				if (s == k)
				{
					Set_key_type_o_token(s,
						new_token);
				}
			}
			new_token.Name_of_Token = s;

			return new_token;
		}
		if (current_state == 1)
		{
			bool flag = false;
			for (int i = 0; i < s.size(); ++i)
			{
				if (s[i] == '.')
				{
					flag = true;
				}
			}
			if (flag)
			{
				new_token.Type_of_Token = "RealConst";
				new_token.Name_of_Token = s;
			}
			else
			{
				new_token.Type_of_Token = "Const";
				new_token.Name_of_Token = s;
			}

			return new_token;
		}
		if (current_state == 3)
		{
			new_token.Type_of_Token = "ERROR";
			new_token.Name_of_Token = s;

			return new_token;
		}
	}
	return new_token;
}

bool FA::Do_we_have_oper_symb(char& c)
{
	FA fa;
	auto Symbols = fa.Operations_Symbols;

	bool flag = false;

	for (auto elem : Symbols) {
		if (c == elem) {
			flag = true;
		}
	}
	return flag;
}

bool FA::Do_we_have_not_oper_symb(char& c)
{
	FA fa;
	auto Symbols = fa.Not_Operations_Symbols;

	bool flag = false;

	for (auto elem : Symbols) {
		if (c == elem) {
			flag = true;
		}
	}
	return flag;
}

bool FA::Do_we_have_keyword(string& c)
{
	FA fa;
	auto Symbols = fa.KeyWords;

	bool flag = false;

	for (auto elem : Symbols) {
		if (c == elem) {
			flag = true;
		}
	}
	return flag;
}