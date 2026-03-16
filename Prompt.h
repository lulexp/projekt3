#pragma once

#include "UnaryCommand.h"
#include <string>
using namespace std;

class Interpreter; //forward-declaration

class Prompt : public UnaryCommand {
public:

	Prompt(string new_sigil);

	string get_Sigil();

	virtual void execute() override;

protected:
	string new_sigil;
};