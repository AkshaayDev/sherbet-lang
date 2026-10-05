#ifndef ASTNODE_HPP
#define ASTNODE_HPP

class ASTNode { public: virtual ~ASTNode() = default; };

class Stmt : public ASTNode {};
class Expr : public ASTNode {};

#endif
