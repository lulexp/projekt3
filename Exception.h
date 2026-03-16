#pragma once

#include <string>

class Exception {

};

class LexicalException : public Exception {
public:
	LexicalException(int pos, string line);

private:
	int position;
	string line;
};