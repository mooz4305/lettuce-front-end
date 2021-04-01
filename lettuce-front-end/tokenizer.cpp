#include "tokenizer.h"

Token Tokenizer::get_token() {
	Token t;

	if (!tokens.empty()) {
		string raw_token = tokens.front();
		tokens.pop_front();
		t = Token(raw_token);
	}
	else {
		t = Token(TokenName::end, "");
	}

	return t;
}

void Tokenizer::save_token(string raw_token) {
	tokens.push_back(raw_token);
}

void Tokenizer::tokenize()
{
	char c;
	string raw_token = "";
	while (ifs.get(c)) {
		raw_token = Tokenizer::read_character(c, raw_token);
	}
	Tokenizer::read_character(' ', raw_token);
}

string Tokenizer::read_character(char c, const string raw_token) {
	if (isspace(c)) {	// whitespace separates tokens, thrown away
		if (raw_token != "") {
			Tokenizer::save_token(raw_token);
		}
		return "";
	}
	else if (c == '(' || c == ')' || isBinaryOp(string(1,c))) { // parentheses seperate tokens, but are also tokens
		if (raw_token != "") {
			Tokenizer::save_token(raw_token);
		}

		string s(1, c);
		Tokenizer::save_token(s);

		return "";
	}
	else {
		string updated_token = raw_token + c;
		return updated_token;
	}
}
