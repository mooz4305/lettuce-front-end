// lettuce-front-end.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

#include "parser.h"


int main(int argc, char* argv[])
{
    string test_program = "test.txt";
    ifstream ifs;

    string file_option = "-f";
 
    // Command: ./lfe 
    // Interpret lettuce expressions in the console
    if (argc == 1) { 
        Tokenizer tz;
        Parser parser(tz);

        cout << "Enter an expression to parse, or enter 'q' to quit: " << endl;

        string raw_expression;
        while(getline(cin, raw_expression) && raw_expression != "q") {
            parser.reset();

            unique_ptr<Expr> expr_ast = parser.parse(raw_expression);
            cout << "Abstract Syntax Tree: " << expr_ast->print() << endl;
        }
    }
    // Command: ./lfe -f <file_name>
    // Interpret lettuce expression in a given file.
    else if (file_option == argv[1]) {
        if (argc == 3) {
            // call parser on file <file_name>
            string file_name = argv[2];
            cout << "Parsing file " << file_name  << "..." << endl;

            ifs.open(file_name, ios_base::in);
            
            Tokenizer tz;
            Parser parser(tz);
            unique_ptr<Expr> expr_ast = parser.parse(ifs);

            cout << "Abstract Syntax Tree: " << expr_ast->print() << endl;
        }
        else {
            cout << "Usage: ./lfe -f <file_name>" << endl;
        }
    }
    else {
        cout << "Usage: ./lfe -f <file_name> OR ./lfe" << endl;
    }    

    return 0;
}