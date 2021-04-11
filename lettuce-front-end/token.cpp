#include "token.h"

const std::vector<char> bin_op_characters { '+', '-', '*', '/', '&', '|', '<', '>'};
const std::vector<std::string>  bin_op_strings {"==", "!=", "<=", ">="};
const std::vector<std::string> keywords{ "let", "be", "in", "if", "then", "else", "function"};

Token::Token(std::string raw_token) {
	name = find_token_name(raw_token);
	text = raw_token;
}

Token::Token(TokenName token_name, std::string raw_token) {
	name = token_name;
	text = raw_token;
}

TokenName Token::get_token_name() {
	return name;
}

std::string Token::get_token_text() {
	return text;
}

bool isInteger(std::string s) {
	for (auto c : s) {
		if (!isdigit(c)) return false;
	}
	return true;
}

bool isBinaryOp(std::string s) {
	if (s.size() == 1) {
		char c = s[0];
		int size = bin_op_characters.size();

		auto pos = std::find(begin(bin_op_characters), end(bin_op_characters), c);
		if (pos != end(bin_op_characters)) {
			return true;
		}
	}
	else {
		auto pos = std::find(begin(bin_op_strings), end(bin_op_strings), s);
		if (pos != end(bin_op_strings)) {
			return true;
		}
	}
	

	return false;
}

bool isKeyword(std::string s) {
	auto pos = std::find(begin(keywords), end(keywords), s);
	if (pos != end(keywords)) {
		return true;
	}
	else return false;
}

TokenName Token::find_token_name(std::string raw_token) {
	if (isInteger(raw_token)) {
		return TokenName::literal;
	}
	else if (raw_token == "True" || raw_token == "False") {
		return TokenName::literal;
	}
	else if (isBinaryOp(raw_token)) {
		return TokenName::binaryop;
	}
	else if (raw_token == "(" || raw_token == ")") {
		return TokenName::separator;
	}
	else if (isKeyword(raw_token)) {
		return TokenName::keyword;
	}
	else {
		return TokenName::identifier;
	}
}