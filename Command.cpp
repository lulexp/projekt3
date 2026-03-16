#include "Command.h"

Command::Command() {}

Command::~Command() {}

void Command::setInput(istream& in) {
	input = &in;
}

void Command::setOutput(ostream& out) {
	output = &out;
}