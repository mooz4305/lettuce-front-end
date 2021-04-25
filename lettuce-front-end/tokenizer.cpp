#include "tokenizer.h"

bool is_op_char(char c) {
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

// adds token from address to queue and clears the string
void Tokenizer::save_token(string* raw_token) {
	string saved_token = *raw_token;
	if (saved_token != "")
		tokens.push_back(saved_token);
	*raw_token = "";
}

void Tokenizer::save_token(string raw_token) {
	tokens.push_back(raw_token);
}

void Tokenizer::tokenize_op(char c, string* raw_token, istream& stream) {
	save_token(raw_token);
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

void Tokenizer::tokenize(istream& ifs)
{
	char c;
	string raw_token = "";
	while (ifs.get(c)) {
		if (isspace(c)) {
			save_token(&raw_token);
		}
		else if (c == '(' || c == ')') {
			save_token(&raw_token); 
			save_token(string(1, c));
		}
		else if (is_op_char(c)) {
			tokenize_op(c, &raw_token, ifs);
		}
		else {
			raw_token += c;
		}
	}

	save_token(&raw_token);
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

/*
string Tokenizer::read_character(char c, const string raw_token) {
	if (isspace(c)) {	// whitespace separates tokens, thrown away
		if (raw_token != "") {
			save_token(raw_token);
		}
		return "";
	}
	else if (c == '(' || c == ')') { // parentheses seperate tokens, but are also tokens
		if (raw_token != "") {
			save_token(raw_token);
		}

		string s(1, c);
		save_token(s);

		return "";
	}
	else if (isBinaryOp(string(1, c)) ) {
		//
	}
	else {
		string updated_token = raw_token + c;
		return updated_token;
	}
}

*/

// get character from stream
// if char is delimiter
	// if char is unsaved delimiter
		// skip character
		// continue processsing stream
	// if char is saved delimiter
		// save the current token
		// save char as token
		// continue processsing stream
	// if char is part of operations (unary, binary, etc)
		// save the current token
		// process stream for an operation token.
		// continue processsing stream
// else 
	// append char to current_token 
	// continue processing stream.