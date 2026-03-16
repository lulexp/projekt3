#include "Tr.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <string.h>
#include <vector>

Tr::Tr(string op1) :
	op1(op1) 
{}

Tr::Tr(string op1, string op2) :
	op1(op1),
	op2(op2) 
{}

void Tr::execute() {
	if (!input || !output) return; //TO-DO exception;

	if (op1.empty()) return; //TO-DO error, ali nije bas ni error, samo ne treba da se izvrsi ostatak

	string arg;
	char c;
	while (input->get(c)) {
		arg.push_back(c);
	}
	op1.erase(op1.begin());

	size_t pos = 0;
	while ((pos = arg.find(op1, pos)) != string::npos) {
		if (!op2.empty()) {
			arg.replace(pos, op1.size(), op2);
			pos = pos + op2.size();
		}
		else {
			arg.erase(pos, op1.size());
		}
	}
	(*output) << arg;

	if (arg.compare(arg.size() - 1, 1, "\n") && !dynamic_cast<ofstream*>(output) && !dynamic_cast<stringstream*>(output)) cout << "\n";
	// if (output == &cout && !arg.empty()) cout << "\n";
	//if (!dynamic_cast<ofstream*>(output)) cout << "\n";
	//if (!dynamic_cast<ofstream*>(output) && !dynamic_cast<stringstream*>(output)) cout << "\n";
}
