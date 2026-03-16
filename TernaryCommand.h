#pragma once

#include "Command.h"
class TernaryCommand : public Command {
public:
	TernaryCommand();

	virtual void execute() = 0;
};