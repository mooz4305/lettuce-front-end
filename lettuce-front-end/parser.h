#include <vector>
#include <string>
#include <memory>  // needed for unique pointer

using namespace std;

class Expr {
	public:
		virtual ~Expr() = default;
};

class ConstExpr : public Expr {
	private :
		int constant;
	public :
		ConstExpr(int constant) : constant(constant) {}
};

class BoolExpr : public Expr {
	private :
		bool boolean;
	public :
		BoolExpr(bool boolean) : boolean(boolean) {}
};

class BinaryOpExpr : public Expr {
	private :
		char op;
		unique_ptr<Expr> LHExpr, RHExpr;
	public :
		BinaryOpExpr(char op, unique_ptr<Expr> LHS, unique_ptr<Expr> RHS) : 
			op(op), LHExpr(move(LHS)), RHExpr(move(RHS)) {}
};

class Parser {
	private :
		vector<string> tokens;
	public :
		Parser(vector<string> new_tokens) {
			tokens = new_tokens;
		}
};