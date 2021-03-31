#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class Tokenizer;
class Scanner {
	private:
		string filename;
		Tokenizer* tokenizer;
	public:
		void scan();
		Scanner();
		Scanner(string name, Tokenizer* t);
		~Scanner();
};