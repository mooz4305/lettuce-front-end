#include "parser.h"

void log_error(string message) {
	cout << "ParseError: " << message << endl;
	exit(EXIT_FAILURE);
}

unique_ptr<Expr> Parser::parse_literal(string text) {
	tkz.consume_token(); // consume the literal token

	if (text[0] == 'T')			return unique_ptr<Expr>(new BoolExpr(true));
	else if (text[0] == 'F')	return unique_ptr<Expr>(new BoolExpr(false));
	else						return unique_ptr<Expr>(new ConstExpr(stoi(text)));
}

unique_ptr<Expr> Parser::parse_parens() {
	tkz.consume_token(); // consume the '(' token

	unique_ptr<Expr> center_expr = parse_expr();
	if (!center_expr) log_error("Parentheses must enclose an expression.");

	Token lookahead = tkz.get_token();
	if (lookahead.get_token_text() == ")") {
		tkz.consume_token(); // consume the ')' token

		unique_ptr<Expr> result(new ParensExpr(move(center_expr)));
		return result;
	}
	else log_error("Missing a closing parentheses.");

}

// Using precedence climbing method, see https://en.wikipedia.org/wiki/Operator-precedence_parser
unique_ptr<Expr> Parser::parse_binary_op(unique_ptr<Expr> LHS, int min_precedence) {
	Token lookahead = tkz.get_token();
	while (lookahead.get_token_name() == TokenName::binaryop) {
		int precedence = binop_precedence.at(lookahead.get_token_text()[0]);
		if (precedence >= min_precedence) {
			Token op = lookahead;
			tkz.consume_token();
			unique_ptr<Expr> RHS = parse_primary();

			lookahead = tkz.get_token();
			while (lookahead.get_token_name() == TokenName::binaryop) {
				int next_precedence = binop_precedence.at(lookahead.get_token_text()[0]);
				if (next_precedence > precedence) {
					RHS = parse_binary_op(move(RHS), min_precedence + 1);
					lookahead = tkz.get_token();
				}
				else {
					break;
				}
			}
			
			unique_ptr<BinaryOpExpr> new_LHS(new BinaryOpExpr(op.get_token_text()[0], move(LHS), move(RHS)));
			LHS = move(new_LHS);
		}
		else {
			break;
		}
	}

	return LHS;
}

unique_ptr<Expr> Parser::parse() {
	tkz.tokenize();

	unique_ptr<Expr> expression = parse_expr(); // assuming program is a single expression

	return expression;
}

unique_ptr<Expr> Parser::parse_expr() {
	unique_ptr<Expr> expr;

	Token token = tkz.get_token();
	TokenName name = token.get_token_name();
	if (name != TokenName::end) {
			expr = parse_primary();
			if (tkz.get_token().get_token_name() == TokenName::binaryop) {
				expr = parse_binary_op(move(expr), 0);
			}
	}
	return expr;
}

// parses expressions that are not BinOp expressions
unique_ptr<Expr> Parser::parse_primary() {
	Token token = tkz.get_token();
	TokenName name = token.get_token_name();
	string text = token.get_token_text();

	switch (name) {
		case TokenName::literal:
			return parse_literal(text);
		case TokenName::separator:
			if (text == "(")
				return parse_parens();
			else log_error("Missing an opening parentheses.");
		default:
			log_error("The token '" + text + "' could not be parsed.");
	}
}