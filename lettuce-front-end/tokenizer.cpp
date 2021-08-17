#include "tokenizer.h"

bool Tokenizer::is_op_char(char c) {
	const std::vector<char> initial_characters{ '+', '-', '*', '/', '&', '|', '=', '!', '<', '>' };

	auto pos = std::find(begin(initial_characters), end(initial_characters), c);

	if (pos != end(initial_characters)) {
		return true;
	} return false;
}

void Tokenizer::save_token(const string token_string) {
	if (!token_string.empty()) {
		Token token(token_string);
		tokens.add_token(token);
	}
}

void Tokenizer::tokenize_op(const char op_char, istream& stream) {
	string raw_token(1, op_char);
	
	char c;
	while (c = stream.peek()) {
		if (is_op_char(c)) {
			stream.get(c);
			raw_token += c;
		}
		else {
			break;
		}
	}
	save_token(raw_token);
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
	string token_string = "";
	while (stream.get(c)) {
		if (isspace(c)) {
			save_token(token_string);

			token_string.clear();
		}
		else if (c == '(' || c == ')') {
			save_token(token_string); 
			save_token(string(1, c));

			token_string.clear();
		} 
		else if (is_op_char(c)) {
			save_token(token_string);
			tokenize_op(c, stream);

			token_string.clear();
		}
		else {
			token_string.push_back(c);
		}
	}

	save_token(token_string); // save remaining token once stream ends
}


void Tokenizer::tokenize(string raw_expression) {
	stringstream stream(raw_expression);
	tokenize(stream);
}