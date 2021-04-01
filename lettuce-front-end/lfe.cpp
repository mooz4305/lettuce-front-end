// lettuce-front-end.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <string>
#include <iostream>
#include <vector>

#include "tokenizer.h"

int main()
{
    string test_program = "test.txt";
    ifstream ifs;

    ifs.open(test_program, ios_base::in);
    Tokenizer tz(ifs);

    tz.tokenize();

    Token t;
    do {
        t = tz.get_token();
        if (t.get_token_name() == TokenName::binaryop) {
            cout << t.get_token_text() << endl;
        }
    } while (t.get_token_text() != "");
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
