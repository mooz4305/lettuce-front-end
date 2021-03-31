#include "tokenizer.h"

Scanner::Scanner() {
	filename = "";
}

Scanner::Scanner(string name, Tokenizer* t) {
	filename = name;
	tokenizer = t;
}

Scanner::~Scanner() {}

void Scanner::scan()
{
	ifstream ifs;
	ifs.open(filename);

	if (ifs) {
		char c;
		string raw_token = "";
		while (ifs.get(c)) {
			raw_token = tokenizer->process_character(c, raw_token);
		}
		tokenizer->process_character(' ', raw_token);
	}
	else {
		cout << "Could not open file " << filename << endl;
	}

}
