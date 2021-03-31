#include <string>
#include <map>

enum class TokenName {
	keyword,	// 'let', 'in'
	literal,	// integers, 'True', 'False'
	separator,	// '(', ')'
	identifier  // everything else
};

TokenName findTokenName(std::string raw_token) {
	switch (string) {
		case "let", 
	}
}

std::map<std::string, TokenName> TokenDict {
	{"let", TokenName::keyword},
	{"in", TokenName::keyword},
	{ "", TokenName::keyword },
};

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