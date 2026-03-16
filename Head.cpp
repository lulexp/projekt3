#include "Head.h"
#include <iostream>
#include <vector>

Head::Head(string ncount) :
	ncount(ncount) 
{}

int Head::getCount(string ncount) {
	ncount.erase(0, 2);
	return stoi(ncount);
}

void Head::execute() {
	if (!input || !output) return; //ERROR

	count = getCount(ncount);

	vector<string> arg;
	string line;
	while (getline(*input, line)) arg.push_back(line);
	for (int i = 0; i < count; i++) {
		(*output) << arg[i] << "\n";
	}
}
