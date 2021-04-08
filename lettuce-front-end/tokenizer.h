#include <string>
#include <iostream>
#include <fstream>
#include <deque>

#include "token.h"

using namespace std;

class Token;

class Tokenizer {
	private:
		ifstream& ifs;
		deque<string> tokens;

		void save_token(string);
		string read_character(char, string);
	public:
		Token get_token();
		void consume_token();

		void tokenize();

		Tokenizer(ifstream& ifs) : ifs(ifs) {};
		~Tokenizer() {};
};