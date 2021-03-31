#include <string>
#include <vector>

enum class TokenName {
	// keyword,	// 'let', 'in'
	// unaryop,	// ~
	// separator, // '(', ')'
	// identifier
	literal,	// integers, 'True', 'False'
	binaryop,	// +, -, *, /, &, |
	end			// signal end of program 
};

std::vector<char> binary_ops = { '+', '-', '*', '/', '&', '|' };

class Token {
	private :
		TokenName name;
		std::string text;
	public :
		Token(TokenName, std::string);
		void setTokenName(TokenName name);
		TokenName getTokenName();
		std::string getTokenText();
};