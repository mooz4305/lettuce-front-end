#include "token.h"

std::vector<char> binary_ops { '+', '-', '*', '/', '&', '|' };

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
		int size = binary_ops.size();

		auto pos = std::find(begin(binary_ops), end(binary_ops), c);
		if (pos != end(binary_ops)) {
			return true;
		}
	}

	return false;
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
	else {
		return TokenName::end;
	}
}