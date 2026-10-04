#ifndef LEXER_HPP
#define LEXER_HPP

#include <fstream>
#include <unordered_set>
#include <string>
#include <vector>
#include <string_view>

enum class TokenType;

extern std::unordered_set<std::string> keywords;
extern std::unordered_set<char> symbols;

struct Token {
	TokenType type;
	std::string_view val;
	int line;
	int col;
	Token(TokenType type, std::string_view val, int line, int col);
};

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
