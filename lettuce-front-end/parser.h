#include <vector>
#include <string>
#include <memory>  // needed for unique pointer
#include <map>

#include "tokenizer.h"

using namespace std;

class Expr {
	public:
		string expr_name = "Expr";
		virtual ~Expr() = default;
		virtual string print() { return "Unknown"; };
};

class ConstExpr : public Expr {
	private :
		int constant;
	public :
		ConstExpr(int constant) : constant(constant) {};

		string print() {
			return "Const(" + to_string(constant) + ")";
		};
};

class BoolExpr : public Expr {
	private :
		bool boolean;
	public :
		BoolExpr(bool boolean) : boolean(boolean) {}

		string print() {
			string text = boolean ? "True" : "False";
			return "Bool(" + text + ")";
		};
};

class ParensExpr : public Expr {
	private :
		unique_ptr<Expr> center_expr;
	public :
		ParensExpr(unique_ptr<Expr> center_expr) : center_expr(move(center_expr)) {}

		string print() {
			return "Parens(" + center_expr->print() +  ")";
		};
};

class BinaryOpExpr : public Expr {
	private :
		string op;
		unique_ptr<Expr> LHExpr, RHExpr;
	public :
		BinaryOpExpr(string op, unique_ptr<Expr> LHS, unique_ptr<Expr> RHS) : 
			op(op), LHExpr(move(LHS)), RHExpr(move(RHS)) {}

		string print() {
			return op + "(" + LHExpr->print() + "," + RHExpr->print() + ")";
		};
};

class IdentExpr : public Expr {
	private :
		string name;
	public :
		IdentExpr(string name) : name(name) { expr_name = "IdentExpr"; }

		string print() { return "Ident(" + name + ")"; }
};

class LetExpr : public Expr {
	private :
		unique_ptr<Expr> ident_expr, value_expr, body_expr;
	public :
		LetExpr(unique_ptr<Expr> ident_expr, unique_ptr<Expr> value_expr, unique_ptr<Expr> body_expr) :
			ident_expr(move(ident_expr)), value_expr(move(value_expr)), body_expr(move(body_expr)) {}

		string print() { 
			return "Let(" + ident_expr->print() + "," + value_expr->print() + "," + body_expr->print() + ")"; 
		}
};

// ITE == If Then Else
class ITEExpr : public Expr {
private:
	unique_ptr<Expr> conditional_expr, body_expr1, body_expr2;
public:
	ITEExpr(unique_ptr<Expr> expr1, unique_ptr<Expr> expr2, unique_ptr<Expr> expr3) :
		conditional_expr(move(expr1)), body_expr1(move(expr2)), body_expr2(move(expr3)) {}

	string print() {
		return "ITE(" + conditional_expr->print() + "," + body_expr1->print() + "," + body_expr2->print() + ")";
	}
};

class Parser {
	private :
		Tokenizer tkz;
		map<string, int> binop_precedence;
		
	public :
		unique_ptr<Expr> parse_literal(string);
		unique_ptr<Expr> parse_identifier(string);
		unique_ptr<Expr> parse_keyword();
		unique_ptr<Expr> parse_let();
		unique_ptr<Expr> parse_if();

		unique_ptr<Expr> parse_parens();
		unique_ptr<Expr> parse_primary();
		unique_ptr<Expr> parse_binary_op(unique_ptr<Expr>, int);
		

		unique_ptr<Expr> parse_expr();

		Parser(Tokenizer tkz) : tkz(tkz) {
			binop_precedence["=="] = 0;
			binop_precedence["!="] = 0;
			binop_precedence["<="] = 0;
			binop_precedence[">="] = 0;
			binop_precedence["<"] = 0;
			binop_precedence[">"] = 0;
			binop_precedence["-"] = 4;
			binop_precedence["+"] = 5;
			binop_precedence["*"] = 6;
			binop_precedence["/"] = 7;
			binop_precedence["|"] = 8;
			binop_precedence["&"] = 9;
		};
		unique_ptr<Expr> parse();


};