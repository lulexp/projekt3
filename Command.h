#pragma once

#include <string>
#include <iostream>

using namespace std;

class Command {
public:

	Command();

	virtual ~Command();

	virtual void execute() = 0;

	bool takesInput = 1;
	bool makesOutput = 1;

	void setInput(istream& input);
	void setOutput(ostream& output);



protected:
	//string name; mislim da je nepotrebno
	istream* input = nullptr;
	ostream* output = nullptr;
};