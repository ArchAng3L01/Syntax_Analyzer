#include "Node_tree.h"
#include <iostream>
#include "Tree_of_parse.h"

Node_tree::Node_tree()
{
	data_of_node = "";
}

Node_tree::Node_tree(string name)
{
	this->data_of_node = name;
}

string Node_tree::get_data_of_node()
{
	return data_of_node;
}

vector<Node_tree>& Node_tree::get_Childrens_of_node()
{
	return Childrens_of_node;
}

void Node_tree::set_data_of_node(string new_name_of_node)
{
	this->data_of_node = new_name_of_node;
}

void Node_tree::add_son_to_node(string name_of_son)
{
	Node_tree new_node(name_of_son);

	this->Childrens_of_node.push_back(new_node);
}

void Node_tree::clear_sons_of_current_node()
{
	this->Childrens_of_node.clear();
}