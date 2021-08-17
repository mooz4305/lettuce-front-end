#include <deque>
#include "token.h"

class TokenList {
	private:
		std::deque<Token> tokens;
	public:
		Token get_token();
		void  consume_token();
		void  add_token(Token);
		void  clear_tokens();
};