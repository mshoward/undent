#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

int main(int argc, char** argv) {
	std::fstream file{argv[1]};
	std::stringstream result;
	std::string line;
	unsigned short indentLevel = 0;

	while (getline(file, line)) {
		// Create an index into the line where text begins (remove leading whitespace)
		std::string::size_type b = 0;
		while (b < line.length() && (line[b] == 9 || line[b] == 11 || line[b] == 32)) ++b;

		// Vaguely check for closing curly brace
		auto l = line.find('}');
		auto h = line.find('#');
		auto f = line.find("//");
		if (l < h && l < f) {
			--indentLevel;
		}

		// Insert the specified number of indents and insert the substring
		for (unsigned short i = 0; i < indentLevel; ++i) result << '\t';
		result << line.substr(b) << std::endl;

		// Vaguely check for opening curly braces and adjust indent appropriately
		l = line.find('{');
		if (l < h && l < f) {
			++indentLevel;
		}
	}

	// Reopen the file, clearing contents, and write the result.
	file.close();
	file.open(argv[1], std::ios_base::out | std::ios_base::trunc);
	file.write(result.str().c_str(), result.str().size());
	file.close();
}
