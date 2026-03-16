#pragma once

#include "BinaryCommand.h"
#include <string>
using namespace std;

class CountWC : public BinaryCommand {
public:
	CountWC(string opt);

	virtual void execute() override;

private:
	int c_count = 0;
	int w_count = 0;

	string opt;
};