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

unique_ptr<Expr> Parser::parse_identifier(string text) {
	tkz.consume_token();


	return unique_ptr<Expr>(new IdentExpr(text));
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

unique_ptr<Expr> Parser::parse_keyword() {
	string token_text = tkz.get_token().get_token_text();

	if (token_text == "let") {
		return parse_let();
	}
	else if (token_text == "be" || token_text == "in") {
		log_error("Let expression could not be parsed.");
	} 
	else if (token_text == "if") {
		return parse_if();
	}
	else if (token_text == "then" || token_text == "else") {
		log_error("If-then-else expression could not be parsed.");
	}
	else if (token_text == "function") {
		return parse_fundef();
	} else {
		log_error("Unimplemented keyword token.");
	}
}

unique_ptr<Expr> Parser::parse_let() {
	tkz.consume_token(); // consume the let keyword
	
	unique_ptr<Expr> ident_expr = parse_expr();
	if (ident_expr->expr_name != "IdentExpr") {
		log_error("Identifier must follow the 'let' keyword.");
	}

	Token token = tkz.get_token();
	if (token.get_token_text() != "be") {
		log_error("Identifier must be followed by the 'be' keyword.");
	} 
	tkz.consume_token(); // consume the 'be' keyword

	unique_ptr<Expr> value_expr = parse_expr();
	if (!value_expr) log_error("Identifier must be set to a value expression.");

	token = tkz.get_token();
	if (token.get_token_text() != "in") {
		log_error("Value must be followed by the 'in' keyword.");
	}
	tkz.consume_token(); // consume the 'in' keyword

	unique_ptr<Expr> body_expr = parse_expr();
	if (!body_expr) {
		log_error("Body must have an expression.");
	}

	return unique_ptr<Expr>(new LetExpr(move(ident_expr), move(value_expr), move(body_expr)) );
}

unique_ptr<Expr> Parser::parse_if() {
	tkz.consume_token(); // consume the 'if' keyword

	unique_ptr<Expr> conditional_expr = parse_expr();

	Token token = tkz.get_token();
	if (token.get_token_text() != "then") {
		log_error("Conditional must be followed by 'then' keyword.");
	}
	tkz.consume_token(); // consume the 'then' keyword

	unique_ptr<Expr> then_expr = parse_expr();
	if (!then_expr) log_error("A body expression must follow 'then' keyword.");

	token = tkz.get_token();
	if (token.get_token_text() != "else") {
		log_error("Missing 'else' keyword.");
	}
	tkz.consume_token(); // consume the 'else' keyword

	unique_ptr<Expr> else_expr = parse_expr();
	if (!else_expr) log_error("A body expression must follow 'else' keyword.");

	return unique_ptr<Expr>(new ITEExpr(move(conditional_expr), move(then_expr), move(else_expr)));
}

unique_ptr<Expr> Parser::parse_fundef() {
	tkz.consume_token(); // consume the 'function' keyword

	if (tkz.get_token().get_token_text() != "(") {
		log_error("Parentheses must follow 'function' keyword.");
	}
	tkz.consume_token(); // consume the '(' token

	unique_ptr<Expr> identifier_expr = parse_expr();
	if (identifier_expr->expr_name != "IdentExpr") {
		log_error("Argument of function definition must be an identifier.");
	}
	if (tkz.get_token().get_token_text() != ")") {
		log_error("Identifier in function definition is not enclosed by a parentheses.");
	}
	tkz.consume_token(); // consume the ')' token

	unique_ptr<Expr> body_expr = parse_expr();
	if (!body_expr) log_error("Function definition must have a body expression.");
	

	return unique_ptr<Expr>(new FunDefExpr(move(identifier_expr), move(body_expr)) );
}

unique_ptr<Expr> Parser::parse_funcall(unique_ptr<Expr> ident_expr) {
	tkz.consume_token(); // consume the '(' token

	unique_ptr<Expr> arg_expr = parse_expr();
	if (!arg_expr) {
		log_error("Argument of function call must have an expression.");
	}

	if (tkz.get_token().get_token_text() != ")") {
		log_error("Argument of function call must be enclosed by a parentheses.");
	}
	tkz.consume_token(); // consume the ')' token

	return unique_ptr<Expr>(new FunCallExpr(move(ident_expr), move(arg_expr)));
}

// Using precedence climbing method, see https://en.wikipedia.org/wiki/Operator-precedence_parser
unique_ptr<Expr> Parser::parse_binary_op(unique_ptr<Expr> LHS, int min_precedence) {
	Token lookahead = tkz.get_token();
	while (lookahead.get_token_name() == TokenName::binaryop) {
		int precedence = binop_precedence.at(lookahead.get_token_text());
		if (precedence >= min_precedence) {
			Token op = lookahead;
			tkz.consume_token();
			unique_ptr<Expr> RHS = parse_primary();

			lookahead = tkz.get_token();
			while (lookahead.get_token_name() == TokenName::binaryop) {
				int next_precedence = binop_precedence.at(lookahead.get_token_text());
				if (next_precedence > precedence) {
					RHS = parse_binary_op(move(RHS), min_precedence + 1);
					lookahead = tkz.get_token();
				}
				else {
					break;
				}
			}
			
			unique_ptr<BinaryOpExpr> new_LHS(new BinaryOpExpr(op.get_token_text(), move(LHS), move(RHS)));
			LHS = move(new_LHS);
		}
		else {
			break;
		}
	}

	return LHS;
}

unique_ptr<Expr> Parser::parse(istream& stream) {
	tkz.tokenize(stream);

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
		case TokenName::identifier:
		{
			unique_ptr<Expr> ident_expr = parse_identifier(text);
			if (tkz.get_token().get_token_text() == "(") {
				ident_expr = parse_funcall(move(ident_expr));
			}
			return ident_expr;
		}
		case TokenName::keyword:
			return parse_keyword();
		default:
			log_error("The token '" + text + "' could not be parsed.");
	}
}