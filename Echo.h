#pragma once

#include "UnaryCommand.h"
#include <string>
using namespace std;

class Echo : public UnaryCommand {
public:
	Echo();

	virtual void execute() override;
};