#pragma once

#include "Command.h"

class Date : public Command {
public:
	Date();

	virtual void execute() override;
};