#pragma once

#include <string>
#include <iostream>

using namespace std;

class Exception {
public: 
	virtual string getMessage() ;
};

class SyntaxException : public Exception {
public:
	SyntaxException(int pos, string line);

	virtual string getMessage() override;

private:
	int position;
	string line;
};

