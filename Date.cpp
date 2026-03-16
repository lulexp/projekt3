#define _CRT_SECURE_NO_WARNINGS

#include "Date.h"
#include <ctime>
#include <iostream>
#include <fstream>

using namespace std;

Date::Date() {
	takesInput = 0;
	makesOutput = 1;
}

void Date::execute() {
	if (!output) return; //TO-DO error

	time_t time_value;
	time(&time_value);

	tm* local = localtime(&time_value);

	char buffer[11];
	strftime(buffer, sizeof(buffer), "%d.%m.%Y", local);

	output->write(buffer, sizeof(buffer));

	if (!dynamic_cast<ofstream*>(output)) cout << "\n";
}