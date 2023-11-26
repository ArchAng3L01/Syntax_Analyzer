#pragma once
#include <string>
#include <vector>
#include "TOKEN_ELEM.h"

using namespace std;

//class of finite automation
class FA
{
private:
public:
	// vector with operation symbols
	vector<char> Operations_Symbols = {'=', '+', '-'};

	//vector with separation symbols
	vector<char> Not_Operations_Symbols = {',', '(', ')'};

	//vector with keywords
	vector<string> KeyWords = {"INTEGER", "REAL", "PROGRAM", "END",
		"RTOI", "ITOR"};

	//matrix for transition 
	vector<vector<int>> TransitFunction;

	FA();

	TOKEN_ELEM Get_Current_Token(string &str);

	bool Do_we_have_oper_symb(char& c);

	bool Do_we_have_not_oper_symb(char& c);

	bool Do_we_have_keyword(string& c);
};