/*  Project:    Lettuce Front End
    Author:     Mohammad Ozaslan
*/

#include <string>
#include <iostream>
#include <fstream>

#include "parser.h"

using namespace std;

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
        string raw_expression;

        cout << "Enter an expression to parse, or enter 'q' to quit: " << endl;
        getline(cin, raw_expression);
        while (raw_expression != "q") {
            parser.reset();

            unique_ptr<Expr> expr_ast;
            try {
                expr_ast = parser.parse(raw_expression);
            }
            catch (parse_error& e) {
                // runtime error by user, reprompt for input
                cerr << e.what() << endl;
                continue;
            }
            catch (exception& e) {
                // logic error in program, should terminate
                cerr << e.what() << endl;
                break;
            }

            cout << "Abstract Syntax Tree: " << expr_ast->print() << endl << endl;

            cout << "Enter an expression to parse, or enter 'q' to quit: " << endl;
            getline(cin, raw_expression);
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