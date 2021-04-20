#include <vector>
#include <string>
#include <memory>  // needed for unique pointer
#include <map>

#include "tokenizer.h"
#include "expr.h"

using namespace std;


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
		unique_ptr<Expr> parse_fundef();
		unique_ptr<Expr> parse_funcall(unique_ptr<Expr>);


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
		unique_ptr<Expr> parse(istream&);


};