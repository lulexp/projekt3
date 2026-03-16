#include "Exception.h"
#include <sstream>

string Exception::getMessage() {
	return nullptr;
}

SyntaxException::SyntaxException(int pos, string line) :
	position(pos),
	line(line) {}

/*
string SyntaxException::getMessage() {
	stringstream ss;
	ss << "Error - unexpected characters:\n"
		<< line << "\n"
		<< "At: " << position << "\n";
	return ss.str();
}
*/

//aj sad jedan goofy getMessage()

string SyntaxException::getMessage() {
	stringstream ss;
	string underline;

	while (underline.length() < position) underline.append(" ");
	underline.append("^");

	ss << "Error - unexpected characters:\n"
		<< line << "\n"
		<< underline;

	return ss.str();
}

