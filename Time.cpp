#define _CRT_SECURE_NO_WARNINGS
#include "Command.h"
#include "Time.h"
#include <ctime>
#include <iostream>
#include <fstream>
using namespace std;

Time::Time() 
{
	takesInput = 0;
	makesOutput = 1;
}

void Time::execute() {
	if (!output) return; //TO-DO error

	time_t time_value;
	time(&time_value);

	tm* local = localtime(&time_value);

	char buffer[9];
	strftime(buffer, sizeof(buffer), "%H:%M:%S", local);

	(*output) << buffer;

	if (!dynamic_cast<ofstream*>(output)) cout << "\n";
}