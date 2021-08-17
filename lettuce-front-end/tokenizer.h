#include <string>
#include <istream>
#include <sstream>
#include <deque>

#include "token.h"
#include "tokenlist.h"

using namespace std;

class Token;
class TokenList;

class Tokenizer {
private:
	TokenList tokens;
	bool is_tokenizing;

	bool is_op_char(char);

	void save_token(string*);
	void save_token(string);

	void tokenize_op(char, string*, istream&);
public:
	Token get_token();
	void consume_token();

	void tokenize(istream&);
	void tokenize(string);

	void reset() { tokens.clear_tokens(); }

	Tokenizer() : is_tokenizing(true) {};
	~Tokenizer() {};
};