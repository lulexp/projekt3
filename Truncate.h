#pragma once

#include "UnaryCommand.h"
#include <string>
using namespace std;

class Truncate : public UnaryCommand {
public:
	Truncate(string filename);

	virtual void execute() override;

private:
	string filename;
};