#pragma once

#include "BinaryCommand.h"
#include <string>
using namespace std;

class Head : public BinaryCommand {
public: 
	Head(string ncount);

	virtual void execute() override;

private:
	int getCount(string ncount);

	string ncount;
	string argument;
	int count = 0;

};