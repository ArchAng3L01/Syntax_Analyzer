#pragma once
#include <vector>
#include <string>
#include "Node_tree.h"
#include "Tree_of_parse.h"
#include "Lexical_Analyzator.h"
#include "Hash_Table.h"
#include <fstream>

using namespace std;

// ����� ��������������� �����������
class Syntax_Analyzator
{

private:
	// vector<Node> Tree_of_parse;
	// Node current_node;
	// Parser p;
public:
	// vector<Node> get_Tree_of_parse();
	// Parser get_Praser();
	// Node get_current_node();
	Tree_of_parse Our_tree_of_parse;

	Lexical_Analyzator Lex_alanyzer;

	ifstream input;

	Hash_Table hash_table;

	Syntax_Analyzator(string file_name) :
		input(file_name) {};

	// Node current_node;
	// Parser p;
	// vector<Node> Tree_of_parse;
	//  vector<Node> Tree_of_parse;
	//  Node parse();

	void print(ofstream& output, 
		Node_tree Our_node, int lvl);

	bool Begin(Tree_of_parse &Some_tree);

	bool Descriptions(Tree_of_parse& Some_tree);

	bool Descr(Tree_of_parse& Some_tree);

	bool Operators(Tree_of_parse& Some_tree);

	bool Op(Tree_of_parse& Some_tree);

	bool VarList(Tree_of_parse& Some_tree);

	bool SimpleExpr(Tree_of_parse& Some_tree);

	bool Expr(Tree_of_parse& Some_tree);

	bool End(Tree_of_parse& Some_tree);

	bool Program(Tree_of_parse &Our_tree_of_parse);
};