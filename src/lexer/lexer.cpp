#include <string>
#include <vector>
#include <string_view>
#include <unordered_set>
#include <cctype>
#include "lexer/lexer.hpp"
#include "lexer/token.hpp"

static const std::unordered_set<std::string> keywords = {
	"echo",
};
static const std::unordered_set<char> symbols = {
	'#',
	'\'',
};

char Lexer::peek(int offset) {
	if (pos + offset < input.size()) {
		return input[pos + offset];
	}
	return '\0';
}

bool Lexer::eof(int offset) {
	return pos + offset >= input.size();
}

void Lexer::addTerminator() {
	if (!tokens.empty() && (tokens.back().type != TokenType::TERMINATOR)) {
		tokens.emplace_back(TokenType::TERMINATOR, "", line, col);
	}
}

Token Lexer::nextToken() {
	while (!eof()) {
		if (std::isspace(peek())) {
			skipWhitespace();
			continue;
		}
		if (peek() == '#') {
			skipComment();
			continue;
		}
		if (peek() == '\'') {
			return tokenizeString();
		}
		return tokenizeKeywordOrIdentifier();
	}
	return Token(TokenType::TOKEN_EOF, "", line, col);
}

Token Lexer::tokenizeKeywordOrIdentifier() {
	int startLine = line, startCol = col;
	int startPos = pos;
	while (!eof() && !std::isspace(peek()) && symbols.find(peek()) == symbols.end()) {
		pos++;
		col++;
	}
	std::string_view val = input.substr(startPos, pos - startPos);
	if (keywords.find(std::string(val)) != keywords.end()) {
		return Token(TokenType::KEYWORD, val, startLine, startCol);
	}
	return Token(TokenType::IDENTIFIER, val, startLine, startCol);
}

Token Lexer::tokenizeString() {
	int startLine = line, startCol = col;
	pos++; col++;
	int startPos = pos;
	while (!eof() && peek() != '\n' && peek() != '\'') {
		pos++;
		col++;
	}
	std::string_view val;
	val = input.substr(startPos, pos - startPos);
	if (eof() || peek() == '\n') {
		lexerErrors.emplace_back("Unterminated string literal", startLine, startCol);
	} else {
		pos++; col++;
	}
	return Token(TokenType::STRING, val, startLine, startCol);
}

void Lexer::skipWhitespace() {
	while (std::isspace(peek())) {
		if (peek() == '\n') {
			addTerminator();
			line++;
			col = 1;
		} else {
			col++;
		}
		pos++;
	}
}
void Lexer::skipComment() {
	if (peek() == '#') {
		if (peek(1) != '#') {
			// Single-line comment
			while (peek() != '\n' && !eof()) {
				pos++;
				col++;
			}
			addTerminator();
		} else {
			// Multi-line comment
			int startLine = line, startCol = col;
			pos += 2;
			col += 2;
			while (!eof()) {
				if (peek() == '#' && peek(1) == '#') {
					pos += 2;
					col += 2;
					break;
				}
				if (peek() == '\n') {
					addTerminator();
					line++;
					col = 1;
				} else {
					col++;
				}
				pos++;
			}
			if (eof()) {
				lexerErrors.emplace_back("Unterminated multi-line comment", startLine, startCol);
			}
		}
	}
}


void Lexer::tokenize() {
	while (true) {
		Token token = nextToken();
		tokens.push_back(token);
		if (token.type == TokenType::TOKEN_EOF) {
			break;
		}
	}
}
