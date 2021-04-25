#include <string>
#include <iostream>
#include <fstream>
#include <deque>

#include "token.h"

using namespace std;

class Token;

class Tokenizer {
	private:
		deque<string> tokens;

		void save_token(string*);
		void save_token(string);
		string read_character(char, string);
		void tokenize_op(char c, string* raw_token, istream& stream);
	public:
		Token get_token();
		void consume_token();

		void tokenize(istream&);
		~Tokenizer() {};
};