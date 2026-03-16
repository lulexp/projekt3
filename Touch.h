#pragma once

#include "UnaryCommand.h"
#include <string>

class Touch : public UnaryCommand {
public:
	Touch(string filename);

	virtual void execute() override;

private:
	string filename;

	bool fileExists(string filename);
};