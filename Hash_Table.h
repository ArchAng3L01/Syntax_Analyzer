#pragma once
#include "fa.h"

using namespace std;
using ll = long long;

// ����� ���� � �������� ����������� ������
class Node
{
public:
	// ���� ��� ��������� �� ������ � ������� ����
	// ����� ������� (��� ������ ���)
	Node *left_son = nullptr;
	Node *right_son = nullptr;

	// ���������� � ������� ����
	TOKEN_ELEM Information_about_current_node;
};

// ����� ���-�������
class Hash_Table
{
private:
public:
	// ����������� ��� �������
	Hash_Table();

	// ���� ��� �������
	vector<Node> hash_table;


	// ������� ������������ ������ �� ���� �� �����, ������� ��������� �-�
	ll Get_Hash_Table_Index(string &current_word);

	// �-� ���������� ������ ����� � ���
	void Adding_new_Word_in_Table(TOKEN_ELEM new_token);
};
