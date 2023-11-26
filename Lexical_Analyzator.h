#pragma once
#include "Hash_Table.h"
#include "fa.h"
#include <vector>
#include <fstream>

//class of lexical analyzer
class Lexical_Analyzator
{
private:
public:
	Lexical_Analyzator();

	TOKEN_ELEM Get_new_token(ifstream& input, 
		Hash_Table& hash_tab);

	string get_word(ifstream& input);

	void return_word(ifstream& input, string our_word);
};