#include <iostream>
#include <string>
#include <fstream>

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
	Lexer lexer(input);
	return 0;
}
