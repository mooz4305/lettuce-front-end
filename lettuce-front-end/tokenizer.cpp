#include "tokenizer.h"

bool Tokenizer::is_op_char(char c) {
	const std::vector<char> initial_characters{ '+', '-', '*', '/', '&', '|', '=', '!', '<', '>' };

	auto pos = std::find(begin(initial_characters), end(initial_characters), c);

	if (pos != end(initial_characters)) {
		return true;
	} return false;
}

void Tokenizer::save_token(string raw_token) {
	Token saved_token = Token(raw_token);
	tokens.add_token(saved_token);
}

void Tokenizer::save_token(string* raw_token) {
	string token_string = *raw_token;

	Token saved_token = Token(token_string);
	tokens.add_token(saved_token);

	*raw_token = "";
}

void Tokenizer::tokenize_op(char c, string* raw_token, istream& stream) {
	*raw_token += c;
	while (stream.get(c)) {
		if (is_op_char(c)) {
			*raw_token += c;
		}
		else {
			save_token(raw_token);
			*raw_token += c;
			break;
		}
	}
}

Token Tokenizer::get_token() {
	return tokens.get_token();
}

void Tokenizer::consume_token() {
	tokens.consume_token();
}

void Tokenizer::tokenize(istream& stream)
{
	char c;
	string raw_token = "";
	while (stream.get(c)) {
		if (isspace(c)) {
			save_token(&raw_token);
		}
		else if (c == '(' || c == ')') {
			save_token(&raw_token); 
			save_token(string(1, c));
		}
		else if (is_op_char(c)) {
			save_token(&raw_token);
			tokenize_op(c, &raw_token, stream);
		}
		else {
			raw_token += c;
		}
	}

	save_token(&raw_token); // save token once stream ends
}


void Tokenizer::tokenize(string raw_expression) {
	stringstream stream(raw_expression);
	tokenize(stream);
}