#include "tokenizer.h"

bool is_start_binop_char(char c) {
	const std::vector<char> initial_characters{ '+', '-', '*', '/', '&', '|', '=', '!', '<', '>' };

	auto pos = std::find(begin(initial_characters), end(initial_characters), c);

	if (pos != end(initial_characters)) {
		return true;
	} return false;
}

Token Tokenizer::get_token() {
	Token t;

	if (!tokens.empty()) {
		string raw_token = tokens.front();
		t = Token(raw_token);
	}
	else {
		t = Token(TokenName::end, "");
	}

	return t;
}

void Tokenizer::consume_token() {
	if (!tokens.empty()) {
		tokens.pop_front();
	}
}

void Tokenizer::save_token(string raw_token) {
	tokens.push_back(raw_token);
}

void Tokenizer::tokenize(istream& ifs)
{
	char c;
	string raw_token = "";
	while (ifs.get(c)) {
		raw_token = Tokenizer::read_character(c, raw_token);
	}
	Tokenizer::read_character(' ', raw_token);
}

/*	get_token :
		if token queue is not empty 
			return frontmost token from queue
		if token queue is empty and tokenization is not complete,
			procure_token()
			add token to queue
			return frontmost token from queue
		else :
			return end token			


 read_token() :
		read in characters from stream:
			append character to current token

			


bool Tokenizer::is_delimiter(char c) {
	if (isspace(c))	
		return true;
	else if (c == '(' || c == ')' || is_start_binop_char(c) )
		return true;
	else
		return false;
}

Token Tokenizer::return_token() {
	string raw_token = string(1,current_char);

	if (isspace(c)) {
		return raw_token;
	} else if (c == '(' || c== '(') {
		return raw_token;
	}

	if (is_delimiter(c) && raw_token != "") {
		return raw_token;
	} else if (!isspace(c))
}

*/

string Tokenizer::read_character(char c, const string raw_token) {
	if (isspace(c)) {	// whitespace separates tokens, thrown away
		if (raw_token != "") {
			save_token(raw_token);
		}
		return "";
	}
	else if (c == '(' || c == ')' || isBinaryOp(string(1,c))) { // parentheses seperate tokens, but are also tokens
		if (raw_token != "") {
			save_token(raw_token);
		}

		string s(1, c);
		save_token(s);

		return "";
	}
	else {
		string updated_token = raw_token + c;
		return updated_token;
	}
}
