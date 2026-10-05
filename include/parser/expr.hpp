#ifndef EXPR_HPP
#define EXPR_HPP

#include "lexer/token.hpp"
#include "parser/astnode.hpp"

class LiteralExpr : public Expr {
public:
	Token val;
};

#endif
