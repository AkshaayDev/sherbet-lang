#ifndef LEXER_HPP
#define LEXER_HPP

#include <string>
#include <vector>
#include <string_view>
#include "lexer/token.hpp"

struct LexerError {
	std::string message;
	int line;
	int col;
	LexerError(std::string message, int line, int col);
};

class Lexer {
private:
	std::string_view input;
	int pos;
	int line;
	int col;

	// Helper functions
	char peek(int offset = 0);
	bool eof(int offset = 0);

	// Tokenization functions
	Token nextToken();
	Token tokenizeKeywordOrIdentifier();
	Token tokenizeString();

	// Skip functions
	void skipWhitespace();
	void skipComment();
public:
	std::vector<Token> tokens;
	std::vector<LexerError> lexerErrors;
	Lexer(std::string_view input);
	void tokenize();
};

#endif
