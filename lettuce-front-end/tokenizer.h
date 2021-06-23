#include <string>
#include <istream>
#include <sstream>
#include <deque>

#include "token.h"

using namespace std;

class Token;

class Tokenizer {
	private:
		deque<string> tokens;

		bool is_op_char(char);

		void save_token(string*);
		void save_token(string);

		void tokenize_op(char, string*, istream&);
	public:
		Token get_token();
		void consume_token();

		void tokenize(istream&);
		void tokenize(string);

		void reset() { tokens.clear(); }

		~Tokenizer() {};
};