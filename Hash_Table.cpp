#pragma once
#include <iostream>
#include "Hash_Table.h"

using namespace std;
using ll = long long;

// ���������� ����
Hash_Table::Hash_Table()
{
    // ������ �������� ��� ������� ������� �����
    // �������� ������ ����������
    hash_table = vector<Node>(1000);
}

// �-� ������������ ������ �� ���� �� �����, ������� ��������� ��� �-�
ll Hash_Table::Get_Hash_Table_Index(string &current_word)
{
    // ����� ������������� ��� ������ ����� � ������� �������
    ll index_in_table = 0;

    // ������ ����������-"���", � ������� ������� �� �����
    // �������� ���������� ����� ��� ������� �����
    ll step = 2;

    for (int i = 0; i < current_word.size(); i++)
    {
        index_in_table += (current_word[i] * step) % hash_table.size();
        index_in_table %= hash_table.size();

        // �������� ��� �� ����, ����� ���� ���������� ����� ��� �������
        // ����� �� �������
        step *= step;
    }

    // ���� ������� ����� ������, ����� ��������� ������������ ������,
    // ����� ����������� ��� ������ � ������� ������� �������
    if (index_in_table < 0)
    {
        while (index_in_table < 0)
        {
            index_in_table += hash_table.size();
        }
    }
    return index_in_table;
}

// �-� ���������� ������ ����� � �������
void Hash_Table::Adding_new_Word_in_Table(TOKEN_ELEM new_token)
{
    // ���� ������ �������� ����� � ������� �� ������ ����� �� ������
    ll index_of_current_word = Get_Hash_Table_Index(new_token.Name_of_Token);

    // ���� ��� ������� �� ��� �������� � ��� - ���������
    if (hash_table[index_of_current_word].Information_about_current_node.Name_of_Token == "bn" && hash_table[index_of_current_word].Information_about_current_node.Type_of_Token == "mb")
    {

        hash_table[index_of_current_word].Information_about_current_node = new_token;
    }
    // ����� ���� ��� ������� ��� => ��������� ����� ������� ������ ��
    // ������ � ������
    else
    {
        Node *Temp_root = new Node;

        Temp_root->Information_about_current_node =
            hash_table[index_of_current_word].Information_about_current_node;
        Temp_root->right_son = hash_table[index_of_current_word].right_son;
        hash_table[index_of_current_word].Information_about_current_node = new_token;
        hash_table[index_of_current_word].right_son = Temp_root;
        Temp_root->left_son = hash_table[index_of_current_word].left_son;
    }
}