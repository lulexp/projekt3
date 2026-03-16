#pragma once

#include "UnaryCommand.h"
#include <string>

using namespace std;

class Remove : public UnaryCommand {
public:
	Remove(string filename);

	virtual void execute() override;

private:
	string filename;
};
