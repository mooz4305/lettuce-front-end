// lettuce-front-end.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

#include "parser.h"


int main(int argc, char* argv[])
{
    string test_program = "test.txt";
    ifstream ifs;

    string file_option = "-f";
    
    if (argc == 1) {
        cout << "Enter an expression to parse, or enter 'q' to quit: " << endl;

        Tokenizer tz;
        Parser parser(tz);

        string raw_expression;
        while(getline(cin, raw_expression) && raw_expression != "q") {
            stringstream stream(raw_expression);
         
            unique_ptr<Expr> expr_ast = parser.parse(stream);
            cout << "Abstract Syntax Tree: " << expr_ast->print() << endl;
        }
    }
    else if (file_option == argv[1]) {

        if (argc != 3) {
            cout << "Usage: ./ lfe -f <file_name>" << endl;
        }
        else {
            // call parser on file <file_name>
            string file_name = argv[2];
            cout << "Parsing file " << file_name  << "..." << endl;

            ifs.open(file_name, ios_base::in);
            
            Tokenizer tz;
            Parser parser(tz);
            unique_ptr<Expr> expr_ast = parser.parse(ifs);

            cout << "Abstract Syntax Tree: " << expr_ast->print() << endl;
        }
    }
    else {
        cout << "Too many arguments. Usage: ./lfe -f <file_name> OR ./lfe <program_text>" << endl;
    }
    

    return 0;
}