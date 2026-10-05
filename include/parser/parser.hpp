#ifndef PARSER_HPP
#define PARSER_HPP

#include <vector>
#include "parser/astnode.hpp"
#include "parser/stmt.hpp"
#include "parser/expr.hpp"

class Parser {
public:
	Parser(const std::vector<Token>& tokens):
		tokens(tokens), pos(0) {}
private:
	std::vector<Token> tokens;
	int pos;
};

#endif
