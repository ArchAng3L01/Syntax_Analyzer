#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <fstream>
#include <string>
#include <algorithm>
#include "Syntax_Analyzator.h"
#include "Lexical_Analyzator.h"

using namespace std;

//function for start for of lexical analyzer
void Work_of_Lexical_Analyzer()
{
    // open input and output files
    ifstream input("input.txt");

    ofstream output("output.txt");

    // string variable with our input text
    string Input_text_from_file = "";

    //Create lexical analyzer
    Lexical_Analyzator Lex_Analyzator;

    //Create Hash table
    Hash_Table hash_table;

    //Read tokens from unput file and adding them to hash table
    while (true) {
        if (input.eof()) {
            break;
        }
        Lex_Analyzator.Get_new_token(input,
            hash_table);
    }

    //output our hash table in output file
    for (int i = 0; i < hash_table.hash_table.size(); ++i)
    {
        Node* Current_Node = &hash_table.hash_table[i];

        if (Current_Node->Information_about_current_node.Type_of_Token != "mb" && Current_Node->Information_about_current_node.Name_of_Token != "bn")
        {

            if (Current_Node->right_son == nullptr)
            {
                output << "(" << Current_Node->Information_about_current_node.Type_of_Token << ": " << Current_Node->Information_about_current_node.Name_of_Token << " )"
                    << " " << i << "\n";
            }
            else
            {
                vector<string> Already_Names;

                output << "(" << Current_Node->Information_about_current_node.Type_of_Token << ": ";
                output << Current_Node->Information_about_current_node.Name_of_Token;
                Already_Names.push_back(Current_Node->Information_about_current_node.Name_of_Token);

                if (Current_Node->right_son != nullptr)
                {
                    while (Current_Node->right_son != nullptr)
                    {
                        bool flag = false;
                        for (int j = 0; j < Already_Names.size(); ++j)
                        {
                            if (Current_Node->Information_about_current_node.Name_of_Token == Already_Names[j])
                            {
                                flag = true;
                            }
                        }
                        if (flag == false)
                        {
                            output << Current_Node->Information_about_current_node.Name_of_Token;
                            if (Current_Node->right_son != nullptr)
                            {
                                output << " | ";
                            }
                        }
                        Current_Node = Current_Node->right_son;
                    }
                }
                output << " ) " << i << "\n";
            }
        }
        else
        {
            continue;
        }
    }

    // close files
    input.close();
    output.close();
}

//Function for start of Syntax analyzer
void Work_of_Syntax_Analyzer() {
    // open input and output files
    ifstream input("input.txt");

    ofstream output("output.txt");

    //Create Syntax alanyzer
    Syntax_Analyzator Syn_analyzer("input.txt");

    //if our program in input file is right - let's output her tree of parse
    //in output file
    if (Syn_analyzer.Program(Syn_analyzer.Our_tree_of_parse)) {
        Syn_analyzer.print(output, Syn_analyzer.Our_tree_of_parse.our_root_of_tree,
            0);
        cout << "Tree of parse was created without problem";
    }
    //else will say, that porgramm not right
    else {
        cout << "\nWe have a little problems in our program";
    }

    //close files
    input.close();
    output.close();
}

int main()
{
    //start work of lexical analyzer
    //Work_of_Lexical_Analyzator();

    //start work of syntax analyzer
    Work_of_Syntax_Analyzer();

    return 0;
}