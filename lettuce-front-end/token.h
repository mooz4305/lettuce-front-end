#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <vector>

enum class TokenName {
	keyword,	// 'let', 'in'
	// unaryop,	// ~
	separator, // '(', ')'
	identifier,
	literal,	// integers, 'True', 'False'
	binaryop,	// +, -, *, /, &, |, ==, !=
	end			// signal end of program 
};

bool isInteger(std::string s);
bool isBinaryOp(std::string s);


class Token {
private:
	TokenName name;
	std::string text;

	TokenName find_token_name(std::string raw_token);
public:
	Token() : name(TokenName::literal), text("") {};
	Token(std::string);
	Token(TokenName, std::string);
	
	TokenName get_name();
	std::string get_text();
};

#endif