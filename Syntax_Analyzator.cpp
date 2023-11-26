#include "Syntax_Analyzator.h"
#include <iostream>
#include <fstream>

//function for output our tree in file
void Syntax_Analyzator::print(ofstream& output,
	Node_tree Our_node, int lvl)
{
	for (int i = 0; i < lvl; i++)
	{
		output << '\t';
	}
	output << Our_node.get_data_of_node() << "\n";

	for (auto& n : Our_node.get_Childrens_of_node())
	{
		print(output, n, lvl + 1);
	}
}

//function for determine right work of Begin
bool Syntax_Analyzator::Begin(Tree_of_parse &Some_tree)
{
	TOKEN_ELEM current_token =
		Lex_alanyzer.Get_new_token(input, hash_table);

	if (current_token.Type_of_Token != "PROGRAM") {
		cout << "Finding " << current_token.Name_of_Token << " ";
		cout << "instead " << "PROGRAM";
		return 0;
	}

	Some_tree.add_son(current_token.Name_of_Token
		+ " " + current_token.Type_of_Token, "BEGIN",
		Some_tree.our_root_of_tree);

	current_token = Lex_alanyzer.Get_new_token(input, hash_table);

	if (current_token.Type_of_Token != "Id") {
		cout << "Finding " << current_token.Name_of_Token << " ";
		cout << "instead " << "Id";
		return 0;
	}

	Some_tree.add_son(current_token.Name_of_Token
		+ " " + current_token.Type_of_Token, "BEGIN",
		Some_tree.our_root_of_tree);

	return 1;
}

//function for determine right work of Descriptions
bool Syntax_Analyzator::Descriptions(Tree_of_parse& Some_tree)
{
	Tree_of_parse temp_root("DESCR");

	if (!Descr(temp_root)) {
		return 0;
	}

	Some_tree.insert_subsons(temp_root,
		"DESCRIPTIONS", Some_tree.our_root_of_tree);

	temp_root.clear_childrens();

	bool flag = true;

	while (flag) {
		TOKEN_ELEM	cur = Lex_alanyzer.Get_new_token(input, hash_table);

		if (cur.Type_of_Token != "INTEGER" && cur.Type_of_Token != "REAL") {
			Lex_alanyzer.return_word(input, cur.Name_of_Token);
			return 1;
		}

		Lex_alanyzer.return_word(input, cur.Name_of_Token);

		temp_root.set_new_name_for_root("DESCR");

		if (!Descr(temp_root)) {
			return 0;
		}

		Some_tree.add_son("DESCR", "DESCRIPTIONS", Some_tree.our_root_of_tree);
		Some_tree.insert_subtree(temp_root, "DESCR", Some_tree.our_root_of_tree);
		
		temp_root.clear_childrens();
	}
	return 1;
}

//function for determine right work of Descr
bool Syntax_Analyzator::Descr(Tree_of_parse& Some_tree)
{
	TOKEN_ELEM cur = Lex_alanyzer.Get_new_token(input, hash_table);

	if (cur.Type_of_Token != "INTEGER" && cur.Type_of_Token != "REAL") {
		cout << "Finded " << cur.Type_of_Token << " instead INTEGER or REAL";
		return 0;
	}

	Some_tree.add_son(cur.Name_of_Token + " " + cur.Type_of_Token,
		"DESCR", Some_tree.our_root_of_tree);

	Tree_of_parse temp_root("VARLIST");

	if (!VarList(temp_root)) {
		return 0;
	}
	
	Some_tree.add_son("VARLIST", "DESCR", Some_tree.our_root_of_tree);

	Some_tree.insert_subtree(temp_root, "VARLIST", Some_tree.our_root_of_tree);
	
	temp_root.clear_childrens();

	return 1;
}

//function for determine right work of Operators
bool Syntax_Analyzator::Operators(Tree_of_parse& Some_tree)
{
	Tree_of_parse temp_root("OP");

	if (!Op(temp_root)) {
		return 0;
	}

	Some_tree.insert_subsons(temp_root, 
		"OPERATORS", Some_tree.our_root_of_tree);

	temp_root.clear_childrens();

	while (true) {
		TOKEN_ELEM cur = Lex_alanyzer.Get_new_token(input, hash_table);

		if (cur.Type_of_Token != "Id") {
			Lex_alanyzer.return_word(input, cur.Name_of_Token);
			return 1;
		}
		Lex_alanyzer.return_word(input, cur.Name_of_Token);

		temp_root.set_new_name_for_root("OP");

		if (!Op(temp_root)) {
			return 0;
		}

		Some_tree.add_son("OP", "OPERATORS", Some_tree.our_root_of_tree);

		Some_tree.insert_subtree(temp_root, "OP", Some_tree.our_root_of_tree);

		temp_root.clear_childrens();
	}

	return 1;
}

//function for determine right work of Op
bool Syntax_Analyzator::Op(Tree_of_parse& Some_tree)
{
	Tree_of_parse temp_root;

	TOKEN_ELEM cur = Lex_alanyzer.Get_new_token(input, hash_table);

	if (cur.Type_of_Token == "Id") {
		Some_tree.add_son(cur.Name_of_Token + " " + cur.Type_of_Token,
			"OP", Some_tree.our_root_of_tree);

		cur = Lex_alanyzer.Get_new_token(input, hash_table);

		if (cur.Type_of_Token != "Assign_Operation") {
			cout << "Founded " << cur.Name_of_Token << " instead assign operation";
			return 0;
		}

		Some_tree.add_son(cur.Name_of_Token + " " + cur.Type_of_Token,
			"OP", Some_tree.our_root_of_tree);

		temp_root.clear_childrens();

		temp_root.set_new_name_for_root("EXPR");

		if (!Expr(temp_root)) {
			return 0;
		}

		Some_tree.add_son("EXPR", "OP", Some_tree.our_root_of_tree);

		Some_tree.insert_subtree(temp_root, "EXPR", Some_tree.our_root_of_tree);

		temp_root.clear_childrens();
	}
	else {
		cout << "Founded " << cur.Name_of_Token << " instead Id";
		return 0;
	}

	return 1;
}

//function for determine right work of VarList
bool Syntax_Analyzator::VarList(Tree_of_parse& Some_tree)
{
	TOKEN_ELEM cur = Lex_alanyzer.Get_new_token(input, hash_table);

	if (cur.Type_of_Token != "Id") {
		cout << "Finded " << cur.Name_of_Token << " instead Id";
		return 0;
	}

	Some_tree.add_son(cur.Name_of_Token + " " + cur.Type_of_Token,
		"VARLIST", Some_tree.our_root_of_tree);

	while (true) {
		cur = Lex_alanyzer.Get_new_token(input, hash_table);

		if (cur.Type_of_Token != "Comma") {
			Lex_alanyzer.return_word(input, cur.Name_of_Token);
			return 1;
		}

		Some_tree.add_son(cur.Name_of_Token + " " + cur.Type_of_Token,
			"VARLIST", Some_tree.our_root_of_tree);

		if (!VarList(Some_tree)) {
			return 0;
		}
	}

	return 1;
}

//function for determine right work of SimpleExpr
bool Syntax_Analyzator::SimpleExpr(Tree_of_parse& Some_tree)
{
	TOKEN_ELEM cur = Lex_alanyzer.Get_new_token(input, hash_table);

	Tree_of_parse temp_root;

	if (cur.Type_of_Token == "Left_Bracket") {
		Some_tree.add_son(cur.Name_of_Token + " " + cur.Type_of_Token,
			"SIMPLE_EXPR", Some_tree.our_root_of_tree);

		temp_root.clear_childrens();

		temp_root.set_new_name_for_root("EXPR");

		if (!Expr(temp_root)) {
			return 0;
		}

		Some_tree.add_son("EXPR", "SIMPLE_EXPR", Some_tree.our_root_of_tree);
		Some_tree.insert_subtree(temp_root, "EXPR", Some_tree.our_root_of_tree);

		cur = Lex_alanyzer.Get_new_token(input, hash_table);

		if (cur.Type_of_Token != "Right_Bracket") {
			cout << "Founded " << cur.Name_of_Token << " instead Right Bracket";
			return 0;
		}
	}
	else if (cur.Type_of_Token == "RTOI" || cur.Type_of_Token == "ITOR") {
		Some_tree.add_son(cur.Name_of_Token + " " + cur.Type_of_Token,
			"SIMPLE_EXPR", Some_tree.our_root_of_tree);

		cur = Lex_alanyzer.Get_new_token(input, hash_table);

		if (cur.Type_of_Token == "Left_Bracket") {
			Some_tree.add_son(cur.Name_of_Token + " " + cur.Type_of_Token,
				"SIMPLE_EXPR", Some_tree.our_root_of_tree);

			temp_root.clear_childrens();

			temp_root.set_new_name_for_root("EXPR");



			if (!Expr(temp_root)) {
				return 0;
			}

			Some_tree.add_son("EXPR", "SIMPLE_EXPR", Some_tree.our_root_of_tree);
			Some_tree.insert_subtree(temp_root, "EXPR", Some_tree.our_root_of_tree);

			cur = Lex_alanyzer.Get_new_token(input, hash_table);

			if (cur.Type_of_Token != "Right_Bracket") {
				cout << "Founded " << cur.Name_of_Token << " instead Right Bracket";
				return 0;
			}
		}
		else {
			cout << "Founded " << cur.Name_of_Token << " instead Left bracket";
			return 0;
		}
	}


	else if (cur.Type_of_Token != "Id" && cur.Type_of_Token != "Const"
		&& cur.Type_of_Token != "RealConst") {
		cout << "Founded " << cur.Name_of_Token << " instead numbers/functions";
		return 0;
	}

	Some_tree.add_son(cur.Name_of_Token + " " + cur.Type_of_Token,
		"SIMPLE_EXPR", Some_tree.our_root_of_tree);

	return 1;
}

//function for determine right work of Expr
bool Syntax_Analyzator::Expr(Tree_of_parse& Some_tree)
{
	Tree_of_parse temp_root;

	temp_root.clear_childrens();

	temp_root.set_new_name_for_root("SIMPLE_EXPR");

	if (!SimpleExpr(temp_root)) {
		return 0;
	}

	Some_tree.add_son("SIMPLE_EXPR", "EXPR", Some_tree.our_root_of_tree);

	Some_tree.insert_subtree(temp_root, "SIMPLE_EXPR", Some_tree.our_root_of_tree);

	TOKEN_ELEM cur = Lex_alanyzer.Get_new_token(input, hash_table);

	if (cur.Type_of_Token != "Plus_Operation" 
		&& cur.Type_of_Token != "Minus_Operation") {
		Lex_alanyzer.return_word(input, cur.Name_of_Token);
		return 1;
	}

	Some_tree.add_son(cur.Name_of_Token + " " + cur.Type_of_Token,
		"EXPR", Some_tree.our_root_of_tree);

	if (!Expr(Some_tree)) {
		return 0;
	}

	return 1;
}

//function for determine right work of End
bool Syntax_Analyzator::End(Tree_of_parse& Some_tree)
{
	TOKEN_ELEM cur = Lex_alanyzer.Get_new_token(input, hash_table);

	if (cur.Type_of_Token != "END") {
		cout << "Founded " << cur.Name_of_Token << " instead END";
		return 0;
	}

	Some_tree.add_son(cur.Name_of_Token + " " + cur.Type_of_Token,
		"END", Some_tree.our_root_of_tree);

	cur = Lex_alanyzer.Get_new_token(input, hash_table);

	if (cur.Type_of_Token != "Id") {
		cout << "Founded " << cur.Name_of_Token << " instead Id";
		return 0;
	}

	Some_tree.add_son(cur.Name_of_Token + " " + cur.Type_of_Token,
		"END", Some_tree.our_root_of_tree);

	return 1;
}

// Function for determine: are we got right program in
// input file
bool Syntax_Analyzator::Program(Tree_of_parse &Our_tree_of_parse)
{
	Tree_of_parse Temp_Root("BEGIN");

	if (!Begin(Temp_Root)) {
		return 0;
	}

	Our_tree_of_parse.insert_subsons(Temp_Root, "PROGRAMM", Our_tree_of_parse.our_root_of_tree);

	Temp_Root.clear_childrens();

	Temp_Root.set_new_name_for_root("DESCRIPTIONS");

	
	if (!Descriptions(Temp_Root)) {
		return 0;
	}

	Our_tree_of_parse.add_son("DESCRIPTIONS", "PROGRAMM",
		Our_tree_of_parse.our_root_of_tree);

	Our_tree_of_parse.insert_subtree(Temp_Root, "DESCRIPTIONS",
		Our_tree_of_parse.our_root_of_tree);

	Temp_Root.clear_childrens();

	Temp_Root.set_new_name_for_root("OPERATORS");

	if (!Operators(Temp_Root)) {
		return 0;
	}

	Our_tree_of_parse.add_son("OPERATORS", "PROGRAMM",
		Our_tree_of_parse.our_root_of_tree);

	Our_tree_of_parse.insert_subtree(Temp_Root, "OPERATORS",
		Our_tree_of_parse.our_root_of_tree);

	Temp_Root.clear_childrens();
	Temp_Root.set_new_name_for_root("END");

	if (!End(Temp_Root)) {
		return 0;
	}

	Our_tree_of_parse.add_son("END", "PROGRAMM",
		Our_tree_of_parse.our_root_of_tree);

	Our_tree_of_parse.insert_subtree(Temp_Root, "END",
		Our_tree_of_parse.our_root_of_tree);


	return (Lex_alanyzer.Get_new_token(input, hash_table).Name_of_Token == "bn");
}
