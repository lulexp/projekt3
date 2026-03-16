#pragma once

#pragma once
#include "Command.h"

class BinaryCommand : public Command {
public:
	BinaryCommand();

	virtual void execute() = 0;

};