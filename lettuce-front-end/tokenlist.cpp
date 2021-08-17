#include "tokenlist.h"

Token TokenList::get_token() {
	Token token;

	if (tokens.empty()) {
		token = Token(TokenName::end, "");
	} else {
		token = tokens.front(); 
	}

	return token;
}

void TokenList::consume_token() {
	if (!tokens.empty()) {
		tokens.pop_front();
	}
}

void TokenList::add_token(Token token) {
	tokens.push_back(token);
}

void TokenList::clear_tokens() {
	tokens.clear();
}