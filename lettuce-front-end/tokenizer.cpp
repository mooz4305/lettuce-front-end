#include "tokenizer.h"

Tokenizer::Tokenizer() {
	program = "";
	scanner = Scanner();
}

bool isInteger(std::string s);
bool isBinaryOp(std::string s);

TokenName Tokenizer::findTokenName(std::string raw_token) {
	if (isInteger(raw_token)) {
		return TokenName::literal;
	}
	else if (raw_token == "True" || raw_token == "False") {
		return TokenName::literal;
	}
	else if (isBinaryOp(raw_token)) {
		return TokenName::binaryop;
	}
	else {
		return TokenName::end;
	}
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

		int pos = std::find(0, size, c);
		if (pos != size) {
			return true;
		}
	}

	return false;
}