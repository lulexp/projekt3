#pragma once

#include "Command.h"
#include "UnaryCommand.h"
#include "BinaryCommand.h"
#include "TernaryCommand.h"

#include <string>
#include <vector>
#include <fstream>

using namespace std;

struct Token {
	string parameter;
	bool inQuotes;
};

struct IOdata {
	string input = ""; //inputType
	string output = ""; //outputType
	string inputString;
	string outputString;
	string inputFile;
	string outputFile;
	bool hasInputRedirect;
	bool append = false; 
};

struct ParsedCommand {
	Command* cmd;
	string cmd_name;
	bool hasInput = true;
};

struct Pipe {
	vector<ParsedCommand> p_cmds;
	IOdata io;
};




class NewParser {
public:
	NewParser();

	Pipe parseCommands(string line);
private:

	vector<Token> tokenize(string line);

	vector<vector<Token>> getSegments(vector<Token> tokens);

	Command* parseZero(vector<Token> segment);

	Command* parseUnary(vector<Token> segment);

	Command* parseBinary(vector<Token> segment);

	Command* parseTernary(vector<Token> segment);
};