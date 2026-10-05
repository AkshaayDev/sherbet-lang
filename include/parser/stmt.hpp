#ifndef STMT_HPP
#define STMT_HPP

#include "parser/astnode.hpp"

class EchoStmt : public Stmt {
public:
	Expr val;
};

#endif
