#pragma once
#include "Lexical_Analyzator.h"
#include "fa.h"
#include <iostream>
#include <fstream>

Lexical_Analyzator::Lexical_Analyzator(){

};

//function for get word from file
string Lexical_Analyzator::get_word(ifstream& input)
{
	FA fa;
	string our_possible_word = "";

	bool flag = true;
	while (flag) {

		char c = input.get();

		if (input.eof()) {
			flag = false;
			break;
		}

		if (c == ' ' || c == '\t' || c == '\n') {
			if (!our_possible_word.empty()) {
				input.unget();
				return our_possible_word;
			}
			else {
				continue;
			}
		}

		if (fa.Do_we_have_oper_symb(c)) {
			if (!our_possible_word.empty()) {
				input.unget();
				return our_possible_word;
			}
			else {
				our_possible_word += c;
				return our_possible_word;
			}
		}

		if (fa.Do_we_have_not_oper_symb(c)) {
			if (!our_possible_word.empty()) {
				input.unget();
				return our_possible_word;
			}
			else {
				our_possible_word += c;
				return our_possible_word;
			}
		}
		our_possible_word += c;
	}
	return our_possible_word;
}

void Lexical_Analyzator::return_word(ifstream& input, string our_word)
{
	std::reverse(our_word.begin(), our_word.end());
	for (auto& symbol : our_word) {
		input.putback(symbol);
	}
}

// function for get token from input file
TOKEN_ELEM Lexical_Analyzator::Get_new_token(ifstream& input,
	Hash_Table& hash_tab)
{
	FA fa;

	string possible_word = get_word(input);

	TOKEN_ELEM Current_Token_from_file = fa.Get_Current_Token(possible_word);

	hash_tab.Adding_new_Word_in_Table(Current_Token_from_file);

	return Current_Token_from_file;
}