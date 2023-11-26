#pragma once
#include <vector>
#include <string>

using namespace std;

// class of Node in tree
class Node_tree
{
private:
	// information about  node
	string data_of_node;

	// vector of chidrens current node
	vector<Node_tree> Childrens_of_node;

public:
	// empty constructor
	Node_tree();

	// constructor by name
	Node_tree(string name);

	string get_data_of_node();
	vector<Node_tree>& get_Childrens_of_node();

	void set_data_of_node(string new_name_of_node);

	void add_son_to_node(string name_of_son);

	void clear_sons_of_current_node();
};