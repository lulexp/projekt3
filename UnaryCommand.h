#pragma once
#include "Command.h"

class UnaryCommand : public Command {
public:
	UnaryCommand();

	virtual void execute() = 0;

protected:
};