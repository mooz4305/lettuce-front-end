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

	bool is_op_char(char);

	void save_token(const string);

	void tokenize_op(char, istream&);
public:
	Token get_token();
	void consume_token();

	void tokenize(istream&);
	void tokenize(string);

	void reset() { tokens.clear_tokens(); }
};