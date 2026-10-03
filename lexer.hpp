#ifndef LEXER_HPP
#define LEXER_HPP

#include <fstream>

class Lexer {
public:
	std::ifstream& input;
	Lexer(std::ifstream& input);
};

#endif
