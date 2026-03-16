#pragma once

#include "Command.h"

//ideja: Time i Date bi potencijalno mogli da budu singleton-i	

class Time : public Command {
public:
	Time();

	virtual void execute() override;
};
