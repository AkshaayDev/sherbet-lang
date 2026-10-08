#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string_view>

enum class TokenType {
	KEYWORD,
	IDENTIFIER,
	STRING,
	TERMINATOR,
	TOKEN_EOF,
};

struct Token {
	TokenType type;
	std::string_view val;
	int line;
	int col;
	Token(TokenType type, std::string_view val, int line, int col):
		type(type), val(val), line(line), col(col) {};
};

#endif
