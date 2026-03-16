#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Echo.h"
using namespace std;

Echo::Echo() {}

void Echo::execute() {
	if (!input || !output) return; //TO-DO error

	string arg;
	char c;
	while (input->get(c)) {
		arg.push_back(c);
	}
	
		(*output) << arg;
	if (arg.compare(arg.size() - 1, 1, "\n") && !dynamic_cast<ofstream*>(output) && !dynamic_cast<stringstream*>(output)) cout << "\n";

 } 