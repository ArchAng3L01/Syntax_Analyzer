#pragma once
#include <vector>
#include <string>
#include "fa.h"
#include <fstream>
#include "Node_tree.h"

using namespace std;

// class of Tree of parse
class Tree_of_parse
{
private:
	// root of tree
	//Node_tree our_root_of_tree;

public:

	Node_tree our_root_of_tree;

	void set_new_name_for_root(string new_name) {
		our_root_of_tree.set_data_of_node(new_name);
	}


	Tree_of_parse();
	Tree_of_parse(string name_of_root);
	void print(int lvl, Node_tree root, ofstream &out);
	void add_son(string name_of_son, string name_of_father,
				 Node_tree &root);
	void clear_childrens();
	void insert_subtree(Tree_of_parse &tree,
						string name_of_adding_subtree, Node_tree &current_node);

	void insert_subsons(Tree_of_parse &tree,
						string name_of_adding_sons, Node_tree &current_node);

	void copy_data_and_childrens_between_nodes(Node_tree &node_from,
											   Node_tree &node_to);
};