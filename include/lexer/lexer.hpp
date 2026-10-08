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
	LexerError(std::string message, int line, int col):
		message(message), line(line), col(col) {}
};

class Lexer {
private:
	std::string_view input;
	int pos;
	int line;
	int col;

	// Helper functions
	inline char peek(int offset = 0);
	inline bool eof(int offset = 0);
	inline void addTerminator();

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
	Lexer(std::string_view input):
		input(input), pos(0), line(1), col(1) {}
	void tokenize();
};

#endif
