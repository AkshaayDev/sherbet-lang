#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "lexer.cpp"

int main(int argc, char** argv) {
	if (argc == 1) {
		std::cout <<
R"(SHERBET HELP
Usage:
	sherbet <script>: Compiles the script into 'a.out' by default
)" << std::endl;
		return 0;
	}
	std::ifstream input(argv[1]);
	if (!input.is_open()) {
		std::cerr << "Error: Input script does not exist" << std::endl;
		return 1;
	}
	std::string src{
		std::istreambuf_iterator<char>(input),
		std::istreambuf_iterator<char>()
	};
	Lexer lexer(src);
	lexer.tokenize();

	std::cout << "Tokens: \n";
	for (const auto& token : lexer.tokens) {
		std::cout << "Type: " << (int)token.type << ", Val: '" << token.val
			<< "' at (" << token.line << ',' << token.col << ")\n";
	}

	if (!lexer.lexerErrors.empty()) {
		// Get lines for error logging
		std::vector<std::string> lines;
		std::string line;
		std::istringstream stream(src);
		while (std::getline(stream, line)) {
			lines.push_back(line);
		}

		std::cout << '\n' << lexer.lexerErrors.size() << " Lexer Errors found:\n";
		for (const auto& error : lexer.lexerErrors) {
			std::string lineMark = std::to_string(error.line);
			std::cerr << "\033[1m\033[31m" << "Lexer Error: " << "\033[0m"
				<< error.message << " (Line " << error.line << " Col " << error.col << ")\n\n"
				<< lineMark << "| " << lines[error.line - 1] << '\n'
				<< std::string(error.col + lineMark.size() + 1, ' ') << "^\n";
		}
		return -1;
	}
	return 0;
}

// Compile command: g++ sherbet.cpp -std=c++17 -o sherbet
// Run command: ./sherbet main.sb
