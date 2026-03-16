#pragma once

#include "UnaryCommand.h"
#include <string>
#include <fstream>
using namespace std;

class Batch : public UnaryCommand {
public: 
	Batch(string filename);

	virtual void execute() override;

private:
	string filename;
};