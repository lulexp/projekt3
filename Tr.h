#pragma once

#include "Command.h"
#include <string>
using namespace std;

class Tr : public Command {
public:
	Tr(string op1);

	Tr(string op1, string op2);

	virtual void execute() override;

private:
	string argument1;
	string op1;
	string op2 = "";

};
