#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include "scanner.h"

using namespace std;

class Tokenizer {
	private:
		string program;
		Scanner scanner;
		vector<string> tokens;

		TokenName findTokenName(std::string raw_token);
	public:
		Tokenizer();

		vector<string> getTokens() {
			return tokens;
		}
		
		Tokenizer(string filename) : program(filename), scanner(filename, this) {};
		
		void tokenize() {
			scanner.scan();
		}

		string process_character(char c, const string raw_token) {
			if (isspace(c)) {	// whitespace separates tokens, thrown away
				if (raw_token != "") {
					process_token(raw_token);
				}
				return "";
			}
			else if (c == '(' || c == ')') { // parentheses seperate tokens, but are also tokens
				if (raw_token != "") {
					process_token(raw_token);
				}

				string s(1, c);
				process_token(s);

				return "";
			}
			else {
				string updated_token = raw_token + c;
				return updated_token;
			}
		}

		void process_token(string raw_token) {
			tokens.push_back(raw_token);
		}
};