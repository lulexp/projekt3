#pragma once

#include "Command.h"
#include "NewParser.h"

#include<vector>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

class Interpreter {
public:

	void run(string line, ostream& defaultOutput, ostream& errOut);

	string getReadinessSigil();

private:
	Pipe pipe;

	Pipe getPipe(string line);

	void setupPipe();

	void runPipe();

	void cleanUp();

	istream& setInput(IOdata io);

	ostream& setOutput(IOdata io);


	istream* input;

	ostream* output;

	ostream* err_out;

	ifstream file_in;
	ofstream file_out;
	istringstream str_in;

	stringstream buffer_in;
	stringstream buffer_out;

	NewParser m_parser;

	string readiness_sigil = "$";
};

