#pragma once

class Expr {
public:
	string expr_name = "Expr";
	virtual ~Expr() = default;
	virtual string print() { return "Unknown Expression"; };
};

class ConstExpr : public Expr {
private:
	int constant;
public:
	ConstExpr(int constant) : constant(constant) {};

	string print() {
		return "Const(" + to_string(constant) + ")";
	};
};

class BoolExpr : public Expr {
private:
	bool boolean;
public:
	BoolExpr(bool boolean) : boolean(boolean) {}

	string print() {
		string text = boolean ? "True" : "False";
		return "Bool(" + text + ")";
	};
};

class ParensExpr : public Expr {
private:
	unique_ptr<Expr> center_expr;
public:
	ParensExpr(unique_ptr<Expr> center_expr) : center_expr(move(center_expr)) {}

	string print() {
		return "Parens(" + center_expr->print() + ")";
	};
};

class BinaryOpExpr : public Expr {
private:
	string op;
	unique_ptr<Expr> LHExpr, RHExpr;
public:
	BinaryOpExpr(string op, unique_ptr<Expr> LHS, unique_ptr<Expr> RHS) :
		op(op), LHExpr(move(LHS)), RHExpr(move(RHS)) {}

	string print() {
		return op + "(" + LHExpr->print() + "," + RHExpr->print() + ")";
	};
};

class IdentExpr : public Expr {
private:
	string name;
public:
	IdentExpr(string name) : name(name) { expr_name = "IdentExpr"; }

	string print() { return "Ident(" + name + ")"; }
};

class LetExpr : public Expr {
private:
	unique_ptr<Expr> ident_expr, value_expr, body_expr;
public:
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

class FunDefExpr : public Expr {
private:
	unique_ptr<Expr> ident_expr, body_expr;
public:
	FunDefExpr(unique_ptr<Expr> ident_expr, unique_ptr<Expr> body_expr) :
		ident_expr(move(ident_expr)), body_expr(move(body_expr)) {}

	string print() {
		return "FunDef(" + ident_expr->print() + "," + body_expr->print() + ")";
	}
};

class FunCallExpr : public Expr {
private:
	unique_ptr<Expr> ident_expr, body_expr;
public:
	FunCallExpr(unique_ptr<Expr> ident_expr, unique_ptr<Expr> body_expr) :
		ident_expr(move(ident_expr)), body_expr(move(body_expr)) {}

	string print() {
		return "FunCall(" + ident_expr->print() + "," + body_expr->print() + ")";
	}
};