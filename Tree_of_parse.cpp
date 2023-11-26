#include "Tree_of_parse.h"

Tree_of_parse::Tree_of_parse()
{
	this->our_root_of_tree = Node_tree("PROGRAMM");
}

Tree_of_parse::Tree_of_parse(string name_of_root)
{
	this->our_root_of_tree = Node_tree(name_of_root);
}

void Tree_of_parse::print(int lvl, Node_tree root, ofstream& out)
{
	for (int i = 0; i < lvl; ++i) {
		out << "\t";
	}
	out << root.get_data_of_node() << "\n";
	for (int i = 0; i < root.get_Childrens_of_node().size(); ++i) {
		print(lvl + 1, root.get_Childrens_of_node()[i], out);
	}
}

//function for add sons to our node
void Tree_of_parse::add_son(string name_of_son, string name_of_father, 
	Node_tree& root)
{
	if (root.get_data_of_node() == name_of_father) {
		root.add_son_to_node(name_of_son);
	}
	else {
		for (int i = 0; i < root.get_Childrens_of_node().size(); ++i) {
			add_son(name_of_son, name_of_father,
				root.get_Childrens_of_node()[i]);
		}
	}
}

void Tree_of_parse::clear_childrens()
{
	this->our_root_of_tree.get_Childrens_of_node().clear();
}

//function for finding space in name of node
bool do_we_have_right_name(string name_of_node,
	string name_of_adding) {

	string s = "";

	for (auto symbol : name_of_node) {
		if (symbol == ' ') {
			break;
		}
		else {
			s += symbol;
		}
	}
	if (s == name_of_adding) {
		return 1;
	}
	else {
		return 0;
	}
}

//function for determine of right name of node
bool is_terminal(string name_of_node) {
	bool flag = true;
	for (auto symbol : name_of_node) {
		if (symbol == ' ') {
			flag = false;
		}
	}
	return flag;
}

//fucntion for insert an extra tree to our node
void Tree_of_parse::insert_subtree(Tree_of_parse& tree, 
	string name_of_adding_subtree, Node_tree& current_node)
{
	if (current_node.get_data_of_node().empty()) {
		return;
	}
	if (is_terminal(current_node.get_data_of_node())
		&& current_node.get_Childrens_of_node().empty()) {
		if(do_we_have_right_name(current_node.get_data_of_node(),
			name_of_adding_subtree)){
			current_node.set_data_of_node("");
			current_node.clear_sons_of_current_node();

			copy_data_and_childrens_between_nodes(tree.our_root_of_tree,
				current_node);
			return;
		}
	}
	for (auto& current_children : current_node.get_Childrens_of_node()) {
		insert_subtree(tree, name_of_adding_subtree, current_children);
	}
}

//fucntion for insert an extra sons to our node
void Tree_of_parse::insert_subsons(Tree_of_parse& tree, 
	string name_of_adding_sons, Node_tree& current_node)
{
	if (current_node.get_data_of_node().empty()) {
		return;
	}
	if (is_terminal(current_node.get_data_of_node()) 
		&& current_node.get_Childrens_of_node().empty()) {
		if (do_we_have_right_name(current_node.get_data_of_node(),
			name_of_adding_sons)) {
			current_node.get_Childrens_of_node().push_back(Node_tree());

			copy_data_and_childrens_between_nodes(tree.our_root_of_tree,
				*current_node.get_Childrens_of_node().begin());
			return;
		}
	}
	for (auto& current_children : current_node.get_Childrens_of_node()) {
		insert_subsons(tree, name_of_adding_sons, current_children);
	}
}

//function for copy name of node and childrens of this node
// to other node
void Tree_of_parse::copy_data_and_childrens_between_nodes(Node_tree& node_from, Node_tree& node_to)
{
	node_to = node_from;

	for (int i = 0; i < node_from.get_Childrens_of_node().size(); ++i) {
		copy_data_and_childrens_between_nodes(node_from.get_Childrens_of_node()[i],
			node_to.get_Childrens_of_node()[i]);
	}
}