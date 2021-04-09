#include "parser.h"

unique_ptr<Expr> Parser::parse_literal(Token token) {
	string text = token.get_token_text();
	tkz.consume_token();

	unique_ptr<Expr> expr;
	if (text[0] == 'T') {
		expr = unique_ptr<Expr>(new BoolExpr(true));
	}
	else if (text[0] == 'F') {
		expr = unique_ptr<Expr>(new BoolExpr(true));
	}
	else {
		expr = unique_ptr<Expr>(new ConstExpr(stoi(token.get_token_text())));
	}

	return expr;
}

unique_ptr<Expr> Parser::parse_parens() {
	tkz.consume_token();
	
	unique_ptr<Expr> center_expr = parse_expr();
	Token lookahead = tkz.get_token();
	if (lookahead.get_token_text() == ")") {
		tkz.consume_token();
		unique_ptr<Expr> result(new ParensExpr(move(center_expr)));
		return result;
	}
	// TO DO: What if there is no closing parentheses?
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
	return parse_expr();
}

unique_ptr<Expr> Parser::parse_expr(unique_ptr<Expr> prev_expr) {
	Token token = tkz.get_token();
	TokenName name = token.get_token_name();

	switch (name) {
		case TokenName::literal: 
			return parse_expr(parse_literal(token));
		case TokenName::binaryop :
			return parse_binary_op(move(prev_expr), 0);
		case TokenName::separator :
			if (token.get_token_text() == "(")
				return parse_parens();
			else
				return prev_expr;

	}
}

// 2nd version of parse_expr()
unique_ptr<Expr> Parser::parse_expr() {
	unique_ptr<Expr> p;
	return parse_expr(move(p));
}

unique_ptr<Expr> Parser::parse_primary() {
	Token token = tkz.get_token();
	TokenName name = token.get_token_name();

	if (name == TokenName::literal) {
		return parse_literal(token);
	}
	else if (name == TokenName::separator) {
		if (token.get_token_text() == "(")
			return parse_parens();
	} 
	else {
		unique_ptr<Expr> p;
		return p;
	}
}